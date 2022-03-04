#ifndef WATERMARK_H_
#define WATERMARK_H_

#include <windows.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

void putTextZH(Mat &dst, const char* str, Point org, Scalar color, int fontSize,
               const char *fn = "Arial", bool italic = false, bool underline = false);

class Watermark{
private:
    
    char* str;
    Point org;
    int fontFace ;
    int fontSize ;
    Scalar color;
    int bold;
    int lineType;
    bool bottomLeftOrigin;
    
    
public:
    Watermark(char* str, Point org=Point(100,150), int fontFace=2, int fontSize=1, Scalar color= Scalar(0,0,0), int bold=1, int lineType=8, bool bottomLeftOrigin=false){
        this->str=str;
        this->org=org;
        this->fontFace=fontFace;
        this->fontSize=fontSize;
        this->bold=bold;
        this->lineType=lineType;
        this->bottomLeftOrigin=bottomLeftOrigin;
        this->color=color;
        
    }
    //修改各参数
    void changeText(char *str){this->str=str;};
    void changeOrg(Point org){this->org=org;};
    void changefF(int fontFace){this->fontFace=fontFace;};
    void changefS(int fontSize){this->fontSize=fontSize;};
    void changeBold(int bold){this->bold=bold;};
    void changeLT(int lineType){this->lineType=lineType;};
    void changebL(bool bottomLeftOrigin){this->bottomLeftOrigin=bottomLeftOrigin;};
    void changeCL(Scalar color){this->color=color;};
    
    void putTextyw(){
        putText(cv::mat_ , str, org, fontFace, fontSize, color, bold,lineType,bottomLeftOrigin);
    }
    /*img – 显示文字所在图像.
     text – 待显示的文字.
     org – 文字在图像中的左下角 坐标.
     font – 字体结构体.
     fontFace – 字体类型， 可选择字体：FONT_HERSHEY_SIMPLEX, FONT_HERSHEY_PLAIN, FONT_HERSHEY_DUPLEX,FONT_HERSHEY_COMPLEX, FONT_HERSHEY_TRIPLEX, FONT_HERSHEY_COMPLEX_SMALL, FONT_HERSHEY_SCRIPT_SIMPLEX, orFONT_HERSHEY_SCRIPT_COMPLEX,以上所有类型都可以配合 FONT_HERSHEY_ITALIC使用，产生斜体效果。
     fontSize – 字体大小，该值和字体内置大小相乘得到字体大小
     color – 文本颜色（默认颜色存储通道为BGR）
     bold – 写字的线的粗细，类似于0.38的笔尖和0.5的笔尖
     lineType – 线性.
     bottomLeftOrigin – true, 图像数据原点在左下角. Otherwise, 图像数据原点在左上角.*/
    
    void putTextzw(){putTextZH(cv::mat_,str,org,color,fontSize);}
    /*img – 显示文字所在图像.
     str – 待显示的文字.
     org – 文字在图像中的左下角 坐标.
     fontFace – 字体结构体.
     fontSize – 字体大小，该值和字体内置大小相乘得到字体大小
     itatic - 决定文字是否为斜体；
     underline - 决定文字是否有下划线
     */
    
};


void GetStringSize(HDC hDC, const char* str, int* w, int* h)
{
    SIZE size;
    GetTextExtentPoint32A(hDC, str, strlen(str), &size);
    if (w != 0) *w = size.cx;
    if (h != 0) *h = size.cy;
}

void putTextZH(Mat &dst, const char* str, Point org, Scalar color, int fontSize, const char* fn="华文行楷", bool italic, bool underline)
{
    CV_Assert(dst.data != 0 && (dst.channels() == 1 || dst.channels() == 3));
    
    int x, y, r, b;
    if (org.x > dst.cols || org.y > dst.rows) return;
    x = org.x < 0 ? -org.x : 0;
    y = org.y < 0 ? -org.y : 0;
    
    LOGFONTA lf;
    lf.lfHeight = -fontSize;
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = 5;
    lf.lfItalic = italic;   //斜体
    lf.lfUnderline = underline; //下划线
    lf.lfStrikeOut = 0;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfOutPrecision = 0;
    lf.lfClipPrecision = 0;
    lf.lfQuality = PROOF_QUALITY;
    lf.lfPitchAndFamily = 0;
    strcpy_s(lf.lfFaceName, fn);
    
    HFONT hf = CreateFontIndirectA(&lf);
    HDC hDC = CreateCompatibleDC(0);
    HFONT hOldFont = (HFONT)SelectObject(hDC, hf);
    
    int strBaseW = 0, strBaseH = 0;
    int singleRow = 0;
    char buf[1 << 12];
    strcpy_s(buf, str);
    char *bufT[1 << 12];  // 这个用于分隔字符串后剩余的字符，可能会超出。
    //处理多行
    {
        int nnh = 0;
        int cw, ch;
        
        const char* ln = strtok_s(buf, "\n",bufT);
        while (ln != 0)
        {
            GetStringSize(hDC, ln, &cw, &ch);
            strBaseW = max(strBaseW, cw);
            strBaseH = max(strBaseH, ch);
            
            ln = strtok_s(0, "\n",bufT);
            nnh++;
        }
        singleRow = strBaseH;
        strBaseH *= nnh;
    }
    
    if (org.x + strBaseW < 0 || org.y + strBaseH < 0)
    {
        SelectObject(hDC, hOldFont);
        DeleteObject(hf);
        DeleteObject(hDC);
        return;
    }
    
    r = org.x + strBaseW > dst.cols ? dst.cols - org.x - 1 : strBaseW - 1;
    b = org.y + strBaseH > dst.rows ? dst.rows - org.y - 1 : strBaseH - 1;
    org.x = org.x < 0 ? 0 : org.x;
    org.y = org.y < 0 ? 0 : org.y;
    
    BITMAPINFO bmp = { 0 };
    BITMAPINFOHEADER& bih = bmp.bmiHeader;
    int strDrawLineStep = strBaseW * 3 % 4 == 0 ? strBaseW * 3 : (strBaseW * 3 + 4 - ((strBaseW * 3) % 4));
    
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = strBaseW;
    bih.biHeight = strBaseH;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB;
    bih.biSizeImage = strBaseH * strDrawLineStep;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;
    
    void* pDibData = 0;
    HBITMAP hBmp = CreateDIBSection(hDC, &bmp, DIB_RGB_COLORS, &pDibData, 0, 0);
    
    CV_Assert(pDibData != 0);
    HBITMAP hOldBmp = (HBITMAP)SelectObject(hDC, hBmp);
    
    //color.val[2], color.val[1], color.val[0]
    SetTextColor(hDC, RGB(255, 255, 255));
    SetBkColor(hDC, 0);
    //SetStretchBltMode(hDC, COLORONCOLOR);
    
    strcpy_s(buf, str);
    const char* ln = strtok_s(buf, "\n",bufT);
    int outTextY = 0;
    while (ln != 0)
    {
        TextOutA(hDC, 0, outTextY, ln, strlen(ln));
        outTextY += singleRow;
        ln = strtok_s(0, "\n",bufT);
    }
    uchar* dstData = (uchar*)dst.data;
    int dstStep = dst.step / sizeof(dstData[0]);
    unsigned char* pImg = (unsigned char*)dst.data + org.x * dst.channels() + org.y * dstStep;
    unsigned char* pStr = (unsigned char*)pDibData + x * 3;
    for (int tty = y; tty <= b; ++tty)
    {
        unsigned char* subImg = pImg + (tty - y) * dstStep;
        unsigned char* subStr = pStr + (strBaseH - tty - 1) * strDrawLineStep;
        for (int ttx = x; ttx <= r; ++ttx)
        {
            for (int n = 0; n < dst.channels(); ++n){
                double vtxt = subStr[n] / 255.0;
                int cvv = vtxt * color.val[n] + (1 - vtxt) * subImg[n];
                subImg[n] = cvv > 255 ? 255 : (cvv < 0 ? 0 : cvv);
            }
            
            subStr += 3;
            subImg += dst.channels();
        }
    }
    
    SelectObject(hDC, hOldBmp);
    SelectObject(hDC, hOldFont);
    DeleteObject(hf);
    DeleteObject(hBmp);
    DeleteDC(hDC);
}
#endif
