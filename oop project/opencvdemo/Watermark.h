#ifndef WATERMARK_H_
#define WATERMARK_H_

//#include <windows.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

cv::Mat mat_ = imread("../Image/1.jpg");
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
        putText(mat_ , str, org, fontFace, fontSize, color, bold,lineType,bottomLeftOrigin);
    }
	//void putText(Mat& img, const char* str, Point org, int fontFace, double fontSize, Scalar color, int bold=1, int lineType=8, bool bottomLeftOrigin=false );
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
   // void putTextzw(){putTextZH(srcImage ,str,org,color,fontSize);}
    /*img – 显示文字所在图像.
     str – 待显示的文字.
     org – 文字在图像中的左下角 坐标.
     fontFace – 字体结构体.
     fontSize – 字体大小，该值和字体内置大小相乘得到字体大小
     itatic - 决定文字是否为斜体；
     underline - 决定文字是否有下划线
     */




};
#endif