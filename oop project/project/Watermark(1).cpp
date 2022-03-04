#include "Watermark.h"

#include <opencv2/opencv.hpp>
Watermark::Watermark()
	:text_(),
	org_(cv::Point(0, 0)), font_face_(2), font_size_(1), color_(cv::Scalar(0, 0, 0)),
	bold_(1), line_type_(8)
{

}

void Watermark::renderText(cv::Mat& mat)
{
	putText(mat, text_.data(), org_, font_face_, font_size_, color_, bold_, line_type_, false);
}