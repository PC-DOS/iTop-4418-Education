#include "NetworkingControlInterface.Client.h"
#include "SettingsProvider.h"

/* Data Queue */
#define NET_DATA_QUEUE_MAX_ITEM_COUNT 40960 //Max size of data buffer, to avoid huge memory consumption
static QQueue<QString *> queDataFramesPendingSending; //Queue of data frames pending sending

/* Intenral Variables */

/* Internal Locks */
static QMutex mtxDataFramesPendingSendingLock; //For internal buffers, Initialize the lock recursivly

/* TCP Client */
TCPClient * tcpDataClient;

/* TCP Networking Data Sending Thread Worker Object */
TCPClientDataSender::TCPClientDataSender() {
    //Initialize internal variables
    bIsDataSending = false;
    bIsDataSendingStopRequested = false;
    bIsUserInitiatedDisconnection = false;
    bIsReconnecting = false;

    //Create TCP socket object and connect events
    connect(this, SIGNAL(connected()), this, SLOT(TCPClientDataSender_Connected()));
    connect(this, SIGNAL(disconnected()), this, SLOT(TCPClientDataSender_Disconnected()));
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError"); //Register QAbstractSocket::SocketError type for QueuedConnection
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(TCPClientDataSender_Error(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(readyRead()), this, SLOT(TCPClientDataSender_ReadyRead()));

#ifdef IS_TCP_SENDING_DEBUG_OUTPUT_ENABLED
    iFrameCounter = 0;
    QTimer::singleShot(10000, this, SLOT(PrintDebugInfo()));
#endif
}

TCPClientDataSender::~TCPClientDataSender() {
}

/* Data Sending Status Indicator */
bool TCPClientDataSender::IsDataSending() const {
    return bIsDataSending;
}

/* Connection Management Command Handlers */
void TCPClientDataSender::ConnectToServerRequestedEventHandler(const QString sServerIPAddressNew, quint16 iServerPortNew,
                                                               bool bIsAutoReconnectEnabledNew, unsigned int iAutoReconnectDelayNew, bool bWairForOperationToComplete) {
    sServerIPAddress = sServerIPAddressNew;
    iServerPort = iServerPortNew;
    bIsAutoReconnectEnabled = bIsAutoReconnectEnabledNew;
    iAutoReconnectDelay = iAutoReconnectDelayNew;
    bIsUserInitiatedDisconnection = false;

    connectToHost(sServerIPAddressNew, iServerPortNew);
    if (bWairForOperationToComplete) {
        waitForConnected();
    }

    return;
}

void TCPClientDataSender::DisconnectFromServerRequestedEventHandler(bool bWairForOperationToComplete) {
    disconnectFromHost();
    bIsUserInitiatedDisconnection = true;
    bIsReconnecting = false;
    if (bWairForOperationToComplete) {
        waitForDisconnected();
    }
    return;
}

void TCPClientDataSender::SetAutoReconnectOptionsRequestedEventHandler(bool bIsAutoReconnectEnabledNew, unsigned int iAutoReconnectDelayNew) {
    bIsAutoReconnectEnabled = bIsAutoReconnectEnabledNew;
    iAutoReconnectDelay = iAutoReconnectDelayNew;
    return;
}

void TCPClientDataSender::SendDataToServerRequestedEventHandler() {
    //Check if SendDataToServerRequestedEventHandler() is running, avoid recursive calling of SendDataToServerRequestedEventHandler() and segmentation faults
    if (bIsDataSending) {
        //If this is a recursive calling, simply returns
        return;
    }
    else {
        //Marks SendDataToServerRequestedEventHandler() is running
        bIsDataSending = true;
    }

    bIsDataSendingStopRequested = false;

    QString * frmCurrentSendingDataFrame = NULL;

    //Send all queued data frames to remote
    //Data sending load may be very high, thus we use a while(){} loop
    while (state() == QTcpSocket::ConnectedState) {
        //Check if data queue is empty, atomicly
        if (mtxDataFramesPendingSendingLock.tryLockInline()) { //Begin reading internal buffer
            if (!queDataFramesPendingSending.empty()) {
                frmCurrentSendingDataFrame = queDataFramesPendingSending.dequeue();
                mtxDataFramesPendingSendingLock.unlockInline(); //Don't forget to unlock me!
            }
            else {
                mtxDataFramesPendingSendingLock.unlockInline(); //Don't forget to unlock me!
                break;
            }
        }
        else {
            break;
        }

        //Check if we got null
        if (!frmCurrentSendingDataFrame) {
            continue;
        }

        //Send data
        write(frmCurrentSendingDataFrame->toLatin1()); //Convert QString to ASCII sequence
        //flush();

        //Free memory space
        delete frmCurrentSendingDataFrame;
        frmCurrentSendingDataFrame = NULL;

#ifdef IS_TCP_SENDING_DEBUG_OUTPUT_ENABLED
        //Debug
        ++iFrameCounter;
#endif

        //Process all events
        QApplication::processEvents();

        //Check if we need to stop data sending
        if (bIsDataSendingStopRequested) {
            break;
        }
    }

    bIsDataSending = false;
    return;
}

void TCPClientDataSender::StopDataSendingRequestedEventHandler() {
    bIsDataSendingStopRequested = true;
    return;
}

/* TCP Socket Event Handler Slots */
void TCPClientDataSender::TCPClientDataSender_Connected() {
    qDebug() << "TCPClient: Connected to" << sServerIPAddress << ":" << iServerPort;
    bIsReconnecting = false;
    emit SocketConnectedToServerEvent(peerName(), sServerIPAddress, iServerPort);
    return;
}

void TCPClientDataSender::TCPClientDataSender_Disconnected() {
    qDebug() << "TCPClient: Disconnected from" << sServerIPAddress << ":" << iServerPort;
    emit SocketDisconnectedFromServerEvent(peerName(), sServerIPAddress, iServerPort);
    return;
}

void TCPClientDataSender::TCPClientDataSender_Error(QAbstractSocket::SocketError errErrorInfo) {
    qDebug() << "TCPClient: Error" << errErrorInfo << ": " << errorString();
    if (state() != QTcpSocket::UnconnectedState) {
        disconnectFromHost();
        waitForDisconnected(245000);
    }
    if (bIsAutoReconnectEnabled && !bIsReconnecting && !bIsUserInitiatedDisconnection) { //Check if we need to reconnect
        qDebug() << "TCPClient: Will retry connect after" << iAutoReconnectDelay << "ms";
        QTimer::singleShot(iAutoReconnectDelay, this, SLOT(TryReconnect()));
        bIsReconnecting = true;
    }
    emit SocketErrorOccurredEvent(errErrorInfo, peerName(), sServerIPAddress, iServerPort);
    return;
}

void TCPClientDataSender::TCPClientDataSender_ReadyRead() {
    while (bytesAvailable()) {
        //Read a command line and emit a signal
        QString sData = readLine();
        if (sData.endsWith('\n')) {
            sData.remove(sData.length() - 1, 1);
        }
        if (sData.endsWith('\r')) {
            sData.remove(sData.length() - 1, 1);
        }
        emit SocketResponseReceivedFromServerEvent(sData, peerName(), sServerIPAddress, iServerPort);

        //Process events
        //QApplication::processEvents();
    }
    return;
}

/* Functional Slots */
void TCPClientDataSender::TryReconnect() {
    if (bIsUserInitiatedDisconnection) {
        return;
    }
    if (state() != QTcpSocket::ConnectingState && state() != QTcpSocket::ConnectedState) {
        qDebug() << "TCPClient: Retrying to connect to" << sServerIPAddress << ":" << iServerPort;
        connectToHost(sServerIPAddress, iServerPort);
        waitForConnected(245000);
    }
    if (state() != QTcpSocket::ConnectedState) {
        qDebug() << "TCPClient: Will retry connect after" << iAutoReconnectDelay << "ms";
        if (state() != QTcpSocket::UnconnectedState) {
            disconnectFromHost();
            waitForDisconnected(245000);
        }
        QTimer::singleShot(iAutoReconnectDelay, this, SLOT(TryReconnect()));
    }
    return;
}

#ifdef IS_TCP_SENDING_DEBUG_OUTPUT_ENABLED
/* Debug */
void TCPClientDataSender::PrintDebugInfo() {
    qDebug() << "TCPClientDataSender: Sent" << iFrameCounter << " frames in 10 sec, IsDataSending =" << bIsDataSending;
    iFrameCounter = 0;
    QTimer::singleShot(10000, this, SLOT(PrintDebugInfo()));
}
#endif

/* TCP Networking Client Wrapper */
TCPClient::TCPClient() {
    //Load settings
    TCPClient::LoadSettings();

    //Create worker object
    tcpDataSender = new TCPClientDataSender;

    //Creat thread object and move worker object (and all it's child objects) to this thread
    trdTCPDataSenderThread = new QThread;
    tcpDataSender->moveToThread(trdTCPDataSenderThread);

    //Connect events and handlers
    connect(this, SIGNAL(ConnectToServerRequestedEvent(QString, quint16, bool, unsigned int, bool)), tcpDataSender, SLOT(ConnectToServerRequestedEventHandler(QString, quint16, bool, unsigned int, bool)));
    connect(this, SIGNAL(DisconnectFromServerRequestedEvent(bool)), tcpDataSender, SLOT(DisconnectFromServerRequestedEventHandler(bool)));
    connect(this, SIGNAL(SetAutoReconnectOptionsRequestedEvent(bool, uint)), tcpDataSender, SLOT(SetAutoReconnectOptionsRequestedEventHandler(bool, uint)));
    connect(this, SIGNAL(SendDataToServerRequestedEvent()), tcpDataSender, SLOT(SendDataToServerRequestedEventHandler()));
    connect(this, SIGNAL(StopDataSendingRequestedEvent()), tcpDataSender, SLOT(StopDataSendingRequestedEventHandler()));
    connect(tcpDataSender, SIGNAL(SocketResponseReceivedFromServerEvent(QString, QString, QString, quint16)), this, SLOT(SocketResponseReceivedFromServerEventHandler(QString, QString, QString, quint16)));
    connect(tcpDataSender, SIGNAL(SocketConnectedToServerEvent(QString, QString, quint16)), this, SIGNAL(ConnectedToServerEvent(QString, QString, quint16)));
    connect(tcpDataSender, SIGNAL(SocketDisconnectedFromServerEvent(QString, QString, quint16)), this, SIGNAL(DisconnectedFromServerEvent(QString, QString, quint16)));
    connect(tcpDataSender, SIGNAL(SocketErrorOccurredEvent(QAbstractSocket::SocketError, QString, QString, quint16)), this, SIGNAL(NetworkingErrorOccurredEvent(QAbstractSocket::SocketError, QString, QString, quint16)));

    //Start child thread's own event loop
    trdTCPDataSenderThread->start();
}

TCPClient::TCPClient(const QString sServerIPAddressNew, quint16 iServerPortNew,
                     bool bIsAutoReconnectEnabledNew, unsigned int iAutoReconnectDelayNew) {
    //Save settings
    sServerIPAddress = sServerIPAddressNew;
    iServerPort = iServerPortNew;
    bIsAutoReconnectEnabled = bIsAutoReconnectEnabledNew;
    iAutoReconnectDelay = iAutoReconnectDelayNew;
    TCPClient::SaveSettings();

    //Create worker object
    tcpDataSender = new TCPClientDataSender;

    //Creat thread object
    trdTCPDataSenderThread = new QThread;
    tcpDataSender->moveToThread(trdTCPDataSenderThread);

    //Connect events and handlers
    connect(this, SIGNAL(ConnectToServerRequestedEvent(QString, quint16, bool, unsigned int, bool)), tcpDataSender, SLOT(ConnectToServerRequestedEventHandler(QString, quint16, bool, unsigned int, bool)));
    connect(this, SIGNAL(DisconnectFromServerRequestedEvent(bool)), tcpDataSender, SLOT(DisconnectFromServerRequestedEventHandler(bool)));
    connect(this, SIGNAL(SetAutoReconnectOptionsRequestedEvent(bool, uint)), tcpDataSender, SLOT(SetAutoReconnectOptionsRequestedEventHandler(bool, uint)));
    connect(this, SIGNAL(SendDataToServerRequestedEvent()), tcpDataSender, SLOT(SendDataToServerRequestedEventHandler()));
    connect(this, SIGNAL(StopDataSendingRequestedEvent()), tcpDataSender, SLOT(StopDataSendingRequestedEventHandler()));
    connect(tcpDataSender, SIGNAL(SocketResponseReceivedFromServerEvent(QString, QString, QString, quint16)), this, SLOT(SocketResponseReceivedFromServerEventHandler(QString, QString, QString, quint16)));
    connect(tcpDataSender, SIGNAL(SocketConnectedToServerEvent(QString, QString, quint16)), this, SIGNAL(ConnectedToServerEvent(QString, QString, quint16)));
    connect(tcpDataSender, SIGNAL(SocketDisconnectedFromServerEvent(QString, QString, quint16)), this, SIGNAL(DisconnectedFromServerEvent(QString, QString, quint16)));
    connect(tcpDataSender, SIGNAL(SocketErrorOccurredEvent(QAbstractSocket::SocketError, QString, QString, quint16)), this, SIGNAL(NetworkingErrorOccurredEvent(QAbstractSocket::SocketError, QString, QString, quint16)));

    //Start child thread's own event loop
    trdTCPDataSenderThread->start();
}

TCPClient::~TCPClient() {
    //Save settings
    if (TCPClient::IsConnected()) {
        TCPClient::DisconnectFromServer();
    }
    TCPClient::SaveSettings();

    //Quit child thread
    trdTCPDataSenderThread->quit();
    if (!trdTCPDataSenderThread->wait(1000)) {
        emit StopDataSendingRequestedEvent();
        if (!trdTCPDataSenderThread->wait(100)) {
            trdTCPDataSenderThread->terminate();
        }
    }

    //Delete worker object
    tcpDataSender->deleteLater();
    tcpDataSender = NULL;

    //Delete child thread
    trdTCPDataSenderThread->deleteLater();
    trdTCPDataSenderThread = NULL;
}

/* Options Management */
void TCPClient::LoadSettings() {
    SettingsContainer.beginGroup(ST_KEY_NETWORKING_PREFIX);
    sServerIPAddress = SettingsContainer.value(ST_KEY_SERVER_IP_ADDRESS, ST_DEFVAL_SERVER_IP_ADDRESS).toString();
    iServerPort = SettingsContainer.value(ST_KEY_SERVER_PORT, ST_DEFVAL_SERVER_PORT).toUInt();
    bIsAutoReconnectEnabled = SettingsContainer.value(ST_KEY_IS_AUTORECONN_ON, ST_DEFVAL_IS_AUTORECONN_ON).toBool();
    iAutoReconnectDelay = SettingsContainer.value(ST_KEY_AUTORECONN_DELAY_MS, ST_DEFVAL_AUTORECONN_DELAY_MS).toUInt();
    SettingsContainer.endGroup();
    return;
}

void TCPClient::SaveSettings() const {
    SettingsContainer.beginGroup(ST_KEY_NETWORKING_PREFIX);
    SettingsContainer.setValue(ST_KEY_SERVER_IP_ADDRESS, sServerIPAddress);
    SettingsContainer.setValue(ST_KEY_SERVER_PORT, iServerPort);
    SettingsContainer.setValue(ST_KEY_IS_AUTORECONN_ON, bIsAutoReconnectEnabled);
    SettingsContainer.setValue(ST_KEY_AUTORECONN_DELAY_MS, iAutoReconnectDelay);
    SettingsContainer.sync();
    SettingsContainer.endGroup();
    return;
}

/* TCP Socket Object Management */
bool TCPClient::IsConnected() const {
    return (tcpDataSender->state() == QTcpSocket::ConnectedState);
}

/* Connection Management */
void TCPClient::SetServerParameters(const QString sServerIPAddressNew, quint16 iServerPortNew) {
    if (TCPClient::IsValidIPAddress(sServerIPAddressNew) && TCPClient::IsValidTCPPort(iServerPortNew)) {
        //Save settings
        sServerIPAddress = sServerIPAddressNew;
        iServerPort = iServerPortNew;
        TCPClient::SaveSettings();
    }
    return;
}

const QString & TCPClient::GetServerIPAddress() const {
    return sServerIPAddress;
}

quint16 TCPClient::GetServerPort() const {
    return iServerPort;
}

void TCPClient::ConnectToServer(bool bWairForOperationToComplete) {
    emit ConnectToServerRequestedEvent(sServerIPAddress, iServerPort, bIsAutoReconnectEnabled, iAutoReconnectDelay, bWairForOperationToComplete);
    return;
}

void TCPClient::ConnectToServer(const QString sServerIPAddressNew, quint16 iServerPortNew,
                                bool bIsAutoReconnectEnabledNew, unsigned int iAutoReconnectDelayNew, bool bWairForOperationToComplete) {
    //Save settings
    sServerIPAddress = sServerIPAddressNew;
    iServerPort = iServerPortNew;
    bIsAutoReconnectEnabled = bIsAutoReconnectEnabledNew;
    iAutoReconnectDelay = iAutoReconnectDelayNew;
    TCPClient::SaveSettings();

    //Connect
    emit ConnectToServerRequestedEvent(sServerIPAddress, iServerPort, bIsAutoReconnectEnabled, iAutoReconnectDelay, bWairForOperationToComplete);
    return;
}

void TCPClient::DisconnectFromServer(bool bWairForOperationToComplete) {
    emit DisconnectFromServerRequestedEvent(bWairForOperationToComplete);
    return;
}

void TCPClient::SendDataToServer() {
    //In high frame rate mode, avoid SendDataToServerRequestedEvent() signal flooding
    if (tcpDataSender->IsDataSending()) {
        return;
    }
    emit SendDataToServerRequestedEvent();
    return;
}

void TCPClient::StopDataSending() {
    emit StopDataSendingRequestedEvent();
    return;
}

/* Data Frame Queue Management */
void TCPClient::QueueDataFrame(const QString & sData) {
    mtxDataFramesPendingSendingLock.lock(); //Begin writing internal buffer

    if (queDataFramesPendingSending.size() > NET_DATA_QUEUE_MAX_ITEM_COUNT) {
        while (!queDataFramesPendingSending.empty()) {
            delete queDataFramesPendingSending.dequeue();
        }
        qDebug() << "TCPClient: Data queue has been purged because it has exceeded the size limit.";
    }

    queDataFramesPendingSending.enqueue(new QString(sData));

    mtxDataFramesPendingSendingLock.unlock(); //Don't forget to unlock me!

    return;
}

void TCPClient::PurgeDataFrameQueue() {
    //Wait until all current sending operation is finished
    emit StopDataSendingRequestedEvent();
    while (tcpDataSender->IsDataSending()) {
        ;
        //QApplication::processEvents();
    }

    mtxDataFramesPendingSendingLock.lockInline(); //Begin writing internal buffer

    while (!queDataFramesPendingSending.empty()){
        delete queDataFramesPendingSending.dequeue();
    }
    qDebug()<<"TCPClient: Data queue has been purged by user.";

    mtxDataFramesPendingSendingLock.unlockInline(); //Don't forget to unlock me!
    return;
}

/* Options */
void TCPClient::SetAutoReconnectMode(bool bIsAutoReconnectEnabledNew) {
    bIsAutoReconnectEnabled = bIsAutoReconnectEnabledNew;
    TCPClient::SaveSettings();
    emit SetAutoReconnectOptionsRequestedEvent(bIsAutoReconnectEnabled, iAutoReconnectDelay);
    return;
}

bool TCPClient::GetIsAutoReconnectEnabled() const {
    return bIsAutoReconnectEnabled;
}

void TCPClient::SetAutoReconnectDelay(unsigned int iAutoReconnectDelayNew) {
    iAutoReconnectDelay = iAutoReconnectDelayNew;
    TCPClient::SaveSettings();
    emit SetAutoReconnectOptionsRequestedEvent(bIsAutoReconnectEnabled, iAutoReconnectDelay);
    return;
}

unsigned int TCPClient::GetAutoReconnectDelay() const {
    return iAutoReconnectDelay;
}

/* Worker Object Event Handler */
void TCPClient::SocketResponseReceivedFromServerEventHandler(QString sResponse, QString sServerName, QString sServerIPAddress, quint16 iServerPort) {
    qDebug() << "TCPClient: Response" << sResponse << "received from the remote";
    emit ResponseReceivedFromServerEvent(sResponse, sServerName, sServerIPAddress, iServerPort);
    return;
}

/* Validators */
bool TCPClient::IsValidIPAddress(const QString sIPAddress) const {
    QHostAddress hstTestAddr;
    return hstTestAddr.setAddress(sIPAddress);
}

bool TCPClient::IsValidTCPPort(quint16 iPort, bool bUseRegisteredPortsOnly) const {
    quint16 iPortIDMin = 1, iPortIDMax = 65535;
    if (bUseRegisteredPortsOnly) {
        iPortIDMin = 1024;
        iPortIDMax = 32767;
    }
    return ((iPort >= iPortIDMin) && (iPort <= iPortIDMax));
}
