#include <iostream>
#include "Watermark.h"

using namespace std;
using namespace cv;

int main() {
    char *t="you are a fool";
    Watermark watermark(t);

    if (!mat_.data) {
        std::cout << "Image not loaded";
        return -1;
    }
    String text = "you are a fool";
    int font_type = 4;
    int font_size = 1;
    Scalar color = (255,255,255);
    int bold = 1;
    //putText(srcImage,text,Point(120,150), font_type, font_size, color,bold);
    //putText(srcImage,text2,Point(10,150), font_type, font_size, color,bold);
    watermark.putTextyw();
    imshow("[img]", mat_);
    waitKey(0);
    return 0;
}