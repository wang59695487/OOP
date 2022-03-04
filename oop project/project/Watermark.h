#ifndef WATERMARK_H
#define WATERMARK_H

#include <windows.h>
#include <string>
#include <opencv2/opencv.hpp>

class Watermark{
 
public:
	Watermark();

	void                renderText(cv::Mat& mat);

	const std::string&  getText() const;
	const int&          getX() const;
	const int&          getY() const;
	const int&          getFontSize() const;

	void                setParameters(const std::string& text,
		                              const int& pos_x, const int& pos_y,
		                              const int& font_size);
	void                resetParameters();

private:

	std::string text_;
	int x_;
	int y_;
	int font_size_;

	int font_face_;
	cv::Scalar color_;
	int line_type_;
	int is_bold_;
};

inline Watermark::Watermark()
	:text_(""),
	x_(0), y_(100),
	font_size_(10), font_face_(1),
	color_(0.0, 0.0, 1.0, 1.0),
	line_type_(8), is_bold_(false)
{}

inline void Watermark::renderText(cv::Mat& mat)
{
	if (mat.empty() || text_.empty()) return;
	cv::putText(mat, text_, cv::Point(x_, y_), font_face_, font_size_, color_, is_bold_, line_type_);
}

inline const std::string& Watermark::getText() const
{
	return text_;
}

inline const int& Watermark::getX() const
{
	return x_;
}

inline const int& Watermark::getY() const
{
	return y_;
}

inline const int& Watermark::getFontSize() const
{
	return font_size_;
}

inline void  Watermark::setParameters(const std::string& text,
	                                  const int& pos_x, const int& pos_y,
	                                  const int& font_size)
{
	text_ = text;
	x_ = pos_x;	y_ = pos_y;
	font_size_ = font_size;
}

inline void  Watermark::resetParameters()
{
	text_ = "";
	x_ = 0;	y_ = 100;
	font_size_ = 10;
}
#endif // !WATERMARK_H
