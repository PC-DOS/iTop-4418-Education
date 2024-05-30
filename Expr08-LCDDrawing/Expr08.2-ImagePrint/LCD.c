#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>


//14byte文件头
typedef struct {
    char cfType[2]; //文件类型，"BM"(0x4D42)
    long cfSize; //文件大小（字节）
    long cfReserved; //保留，值为0
    long cfDataOffset; //数据区相对于文件头的偏移量（字节）
}__attribute__((packed)) BitmapFileHeader;
//__attribute__((packed))的作用是告诉编译器取消结构在编译过程中的优化对齐

//40byte信息头
typedef struct {
    char ciSize[4]; //BITMAPFILEHEADER所占的字节数
    long ciWidth; //宽度
    long ciHeight; //高度
    char ciPlanes[2]; //目标设备的位平面数，值为1
    int ciBitCount; //每个像素的位数
    char ciCompress[4]; //压缩说明
    char ciSizeImage[4]; //用字节表示的图像大小，该数据必须是4的倍数
    char ciXPelsPerMeter[4]; //目标设备的水平像素数/米
    char ciYPelsPerMeter[4]; //目标设备的垂直像素数/米
    char ciClrUsed[4]; //位图使用调色板的颜色数
    char ciClrImportant[4]; //指定重要的颜色数，当该域的值等于颜色数时（或者等于0时），表示所有颜色都一样重要
}__attribute__((packed)) BitmapInfoHeader;

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    //unsigned short reserved;
}__attribute__((packed)) Pixel24Bit; //颜色模式RGB

BitmapFileHeader fhFileHead;
BitmapInfoHeader ihInfoHead;

static char * lpFrameBuffer = 0;
static int iScreenResolutionWidth = 0;
static int iScreenResolutionHeight = 0;
static int iScreenBitsPerPixel = 0;
static int iScreenBytesPerPixel = 0;

int PrintBitmap24BitToScreen();

int main(int argc, char *argv[]) {
    //Check if file path is given. Added by Picsell Dois (t.c.d.)
    if (argv[1]==NULL){
        printf("Error: File to display must be specified.\n");
        printf("\n");
        printf("Usage:\nLCD file\n\n");
        return 0;
    }

    int hFrameBufferFile = 0;
    struct fb_var_screeninfo nfoScreenInfoVariable;
    struct fb_fix_screeninfo nfoScreenInfoFixed;
    long int iScreenTotalSizeInByte = 0;

    //打开显示设备
    hFrameBufferFile = open("/dev/fb0", O_RDWR);
    if (!hFrameBufferFile) {
        printf("Error: cannot open framebuffer device.\n");
        exit(1);
    }

    if (ioctl(hFrameBufferFile, FBIOGET_FSCREENINFO, &nfoScreenInfoFixed)) {
        printf("Error：reading fixed information.\n");
        exit(2);
    }

    if (ioctl(hFrameBufferFile, FBIOGET_VSCREENINFO, &nfoScreenInfoVariable)) {
        printf("Error: reading variable information.\n");
        exit(3);
    }

    printf("Pixel Param: R:%d,G:%d,B:%d \n", nfoScreenInfoVariable.red, nfoScreenInfoVariable.green, nfoScreenInfoVariable.blue);

    printf("Screen Info: %dx%d, %dbpp\n", nfoScreenInfoVariable.xres, nfoScreenInfoVariable.yres, nfoScreenInfoVariable.bits_per_pixel);
    iScreenResolutionWidth = nfoScreenInfoVariable.xres;
    iScreenResolutionHeight = nfoScreenInfoVariable.yres;
    iScreenBitsPerPixel = nfoScreenInfoVariable.bits_per_pixel;
    iScreenBytesPerPixel = iScreenBitsPerPixel / 8;

    //计算屏幕的总大小（字节）
    iScreenTotalSizeInByte = nfoScreenInfoVariable.xres * nfoScreenInfoVariable.yres * nfoScreenInfoVariable.bits_per_pixel / 8;
    printf("iScreenTotalSizeInByte = %d byte\n",iScreenTotalSizeInByte);

    //对象映射
    lpFrameBuffer = (char *)mmap(0, iScreenTotalSizeInByte, PROT_READ | PROT_WRITE, MAP_SHARED, hFrameBufferFile, 0);
    if ((int)lpFrameBuffer == -1)
    {
        printf("Error: failed to map framebuffer device to memory.\n");
        exit(4);
    }


    //Initialize framebuffer to 0 (black), added by Picsell Dois (t.c.d.)
    memset(lpFrameBuffer, 0, iScreenTotalSizeInByte);

    printf("sizeof(BitmapFileHeader) = %d\n", sizeof(BitmapFileHeader));

    printf("Begin drawing bitmap to screen\n");

    //显示图像
    PrintBitmap24BitToScreen(argv[1]);

    //删除对象映射
    munmap(lpFrameBuffer, iScreenTotalSizeInByte);
    close(hFrameBufferFile);

    return 0;
}

int PrintBitmap24BitToScreen(char * sFilePath)
{
    FILE * hBitmapFile;
    int iReadResult;
    int iCurrentDrawingLineX = 0;
    int iCurrentDrawingLineY = 0;
    long int iCurrentDrawingLocation = 0, iBytesPerLine = 0;

    hBitmapFile = fopen(sFilePath, "rb");
    if (hBitmapFile == NULL) {
        return(-1);
    }

    iReadResult = fread(&fhFileHead, sizeof(BitmapFileHeader), 1, hBitmapFile);
    if (iReadResult != 1) {
        printf("Error: Failed to read file header\n");
        fclose(hBitmapFile);
        return(-2);
    }

    //检测是否是BMP图像
    if (memcmp(fhFileHead.cfType, "BM", 2) != 0) {
        printf("Error: File type mismatch, must be a 24-bit BMP file\n");
        fclose(hBitmapFile);
        return(-3);
    }

    iReadResult = fread((char *)&ihInfoHead, sizeof(BitmapInfoHeader),1, hBitmapFile);
    if (iReadResult != 1) {
        printf("Error: Failed to read info header\n");
        fclose(hBitmapFile);
        return(-4);
    }

    //跳转的数据区
    printf("fhFileHead.cfDataOffset=%d\n", fhFileHead.cfDataOffset);
    fseek(hBitmapFile, fhFileHead.cfDataOffset, SEEK_SET);

    //尺寸
    printf("ihInfoHead.ciWidth=%d\n", ihInfoHead.ciWidth);
    printf("ihInfoHead.ciHeight=%d\n", ihInfoHead.ciHeight);
    printf("ihInfoHead.ciBitCount=%d\n", ihInfoHead.ciBitCount);

    //每行字节数
    iBytesPerLine = (ihInfoHead.ciWidth * ihInfoHead.ciBitCount + 31) / 32 * 4;
    printf("iBytesPerLine=%d\n", iBytesPerLine);

    //Zero value filled by BMP structrue (see https://www.bilibili.com/read/cv34494181/)
    int nZeroBytePerLine = 0;
    nZeroBytePerLine = iBytesPerLine - (ihInfoHead.ciWidth * ihInfoHead.ciBitCount) / 8;
    printf("nZeroBytePerLine=%d\n", nZeroBytePerLine);

    iCurrentDrawingLineX = 0;
    iCurrentDrawingLineY = 0;
    //向FrameBuffer中写BMP图片
    while (!feof(hBitmapFile)) {
        //24-Bit pixel
        Pixel24Bit pixCurrentPixel;
        char chrNull;

        iCurrentDrawingLocation = iCurrentDrawingLineX * iScreenBytesPerPixel + (ihInfoHead.ciHeight - iCurrentDrawingLineY - 1) * iScreenResolutionWidth * iScreenBytesPerPixel;

        //显示每一个像素
        iReadResult = fread((char *)(&pixCurrentPixel), 1, sizeof(Pixel24Bit), hBitmapFile);
        if (iReadResult != sizeof(Pixel24Bit)) {
            break;
        }
        *(lpFrameBuffer + iCurrentDrawingLocation + 0) = pixCurrentPixel.blue;
        *(lpFrameBuffer + iCurrentDrawingLocation + 1) = pixCurrentPixel.green;
        *(lpFrameBuffer + iCurrentDrawingLocation + 2) = pixCurrentPixel.red;
        *(lpFrameBuffer + iCurrentDrawingLocation + 3) = 0;

        //Update drawing pos
        ++iCurrentDrawingLineX;
        if (iCurrentDrawingLineX == ihInfoHead.ciWidth) {

            //Skip zero bytes
            int i;
            for (i = 0; i < nZeroBytePerLine; ++i) {
                fread((char *)(&chrNull), 1, 1, hBitmapFile);
            }
            
            //Move to next line
            iCurrentDrawingLineX = 0;
            ++iCurrentDrawingLineY;
            if(iCurrentDrawingLineY == ihInfoHead.ciHeight) {
                break;
            }
        }
    }
    fclose(hBitmapFile);
    return(0);
}
