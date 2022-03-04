//#include "stdafx.h"
#include "CvxText.h"

#include <wchar.h>
#include <assert.h>
#include <locale.h>
#include <ctype.h>


#ifdef _DEBUG
#pragma comment(lib, "freetype.lib")
#else
#pragma comment(lib, "freetype.lib")
#endif 

//====================================================================
//====================================================================

// 打开字库

CvxText::CvxText(const char *freeType)
{
   assert(freeType != NULL);

   // 打开字库文件, 创建一个字体

   if(FT_Init_FreeType(&m_library)) throw;
   if(FT_New_Face(m_library, freeType, 0, &m_face)) throw;

   // 设置字体输出参数

   restoreFont();

   FT_Set_Pixel_Sizes(this->m_face,16,24);

   // 设置C语言的字符集环境

   setlocale(LC_ALL, "");
}

// 释放FreeType资源

CvxText::~CvxText()
{
   FT_Done_Face    (m_face);
   FT_Done_FreeType(m_library);
}

// 设置字体参数:
//
// font         - 字体类型, 目前不支持
// size         - 字体大小/空白比例/间隔比例/旋转角度
// underline   - 下画线
// diaphaneity   - 透明度

void CvxText::getFont(int *type, cv::Scalar *size, bool *underline, float *diaphaneity)
{
   if(type) *type = m_fontType;
   if(size) *size = m_fontSize;
   if(underline) *underline = m_fontUnderline;
   if(diaphaneity) *diaphaneity = m_fontDiaphaneity;
}

void CvxText::setFont(int *type, cv::Scalar *size, bool *underline, float *diaphaneity)
{
   // 参数合法性检查

   if(type)
   {
      if(type >= 0) m_fontType = *type;
   }
   if(size)
   {
      m_fontSize.val[0] = fabs(size->val[0]);
      m_fontSize.val[1] = fabs(size->val[1]);
      m_fontSize.val[2] = fabs(size->val[2]);
      m_fontSize.val[3] = fabs(size->val[3]);
   }
   if(underline)
   {
      m_fontUnderline   = *underline;
   }
   if(diaphaneity)
   {
      m_fontDiaphaneity = *diaphaneity;
   }
}

// 恢复原始的字体设置

void CvxText::restoreFont()
{
   m_fontType = 0;            // 字体类型(不支持)

   m_fontSize.val[0] = 20;      // 字体大小
   m_fontSize.val[1] = 0.5;   // 空白字符大小比例
   m_fontSize.val[2] = 0.1;   // 间隔大小比例
   m_fontSize.val[3] = 0;      // 旋转角度(不支持)

   m_fontUnderline   = false;   // 下画线(不支持)

   m_fontDiaphaneity = 1.0;   // 色彩比例(可产生透明效果)

   // 设置字符大小

   FT_Set_Pixel_Sizes(m_face, (int)m_fontSize.val[0], 0);
}

// 输出函数(颜色默认为黑色)

int CvxText::putText(cv::Mat *img, const char    *text, cv::Point pos)
{
   return putText(img, text, pos, CV_RGB(255,255,255));
}
int CvxText::putText(cv::Mat *img, const wchar_t *text, cv::Point pos)
{
   return putText(img, text, pos, CV_RGB(255,255,255));
}

//

int CvxText::putText(cv::Mat *img, const char    *text, cv::Point pos, cv::Scalar color)
{
   if(img == NULL) return -1;
   if(text == NULL) return -1;

   //

   int i;
   for(i = 0; text[i] != '\0'; ++i)
   {
      wchar_t wc = text[i];

      // 解析双字节符号

      if(!isascii(wc)) mbtowc(&wc, &text[i++], 2);

      // 输出当前的字符

      putWChar(img, wc, pos, color);
   }
   return i;
}
int CvxText::putText(cv::Mat *img, const wchar_t *text, cv::Point pos, cv::Scalar color)
{
   if(img == NULL) return -1;
   if(text == NULL) return -1;

   //

   int i;
   for(i = 0; text[i] != '\0'; ++i)
   {
      // 输出当前的字符

      putWChar(img, text[i], pos, color);
   }
   return i;
}

// 输出当前字符, 更新m_pos位置

void CvxText::putWChar(cv::Mat *img, wchar_t wc, cv::Point &pos, cv::Scalar color)
{
   // 根据unicode生成字体的二值位图

   FT_UInt glyph_index = FT_Get_Char_Index(m_face, wc);
   FT_Load_Glyph(m_face, glyph_index, FT_LOAD_DEFAULT);
   FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_MONO);

   //

   FT_GlyphSlot slot = m_face->glyph;


   // 行列数
   int rows = slot->bitmap.rows;
   int cols = slot->bitmap.width;

   //

   for(int i = 0; i < rows; ++i)
   {
      for(int j = 0; j < cols; ++j)
      {
         int off  = ((1)? i: (rows-1-i))
            * slot->bitmap.pitch + j/8;

         if(slot->bitmap.buffer[off] & (0xC0 >> (j%8)))
         {

			int r = (1)? pos.y - (rows-1-i): pos.y + i;;
			int c = pos.x + j;
			
			r=r-slot->bitmap_top+rows;
//			c=c+slot->bitmap_left;
			

            if(r >= 0 && r < img->rows
               && c >= 0 && c < img->cols)
            {
				cv::Scalar scalar = cv::Scalar(img->at<cv::Vec4b>(r, c)[0], img->at<cv::Vec4b>(r, c)[1], img->at<cv::Vec4b>(r, c)[2], img->at<cv::Vec4b>(r, c)[3]);

               // 进行色彩融合

               float p = m_fontDiaphaneity;
               for(int k = 0; k < 4; ++k)
               {
                  scalar.val[k] = scalar.val[k]*(1-p) + color.val[k]*p;
               }

			   img->at<cv::Vec4b>(r, c)[0] = scalar[0];
			   img->at<cv::Vec4b>(r, c)[1] = scalar[1];
			   img->at<cv::Vec4b>(r, c)[2] = scalar[2];
			   img->at<cv::Vec4b>(r, c)[3] = scalar[3];
            }
         }
      } // end for
   } // end for

   // 修改下一个字的输出位置

   double space = m_fontSize.val[0]*m_fontSize.val[1];
   double sep   = m_fontSize.val[0]*m_fontSize.val[2];

// pos.x += (int)((cols? cols: space) + sep);
   pos.x += slot->advance.x >> 6;
}

FT_Error CvxText::SetFontSizes( FT_UInt pixel_width,FT_UInt pixel_height )
{
	return FT_Set_Pixel_Sizes(this->m_face,pixel_width,pixel_height);
}
#if 0
int main(int argc, char *argv[])
{
	// 定义CvxApplication对象

	CvxApplication app(argc, argv);

	// 打开一个影象

	cv::Mat *img = cvLoadImage("test.jpg", 1);

	// 输出汉字

	{
		// "wqy-zenhei.ttf"为文泉驿正黑体

		CvText text("wqy-zenhei.ttf");

		const char *msg = "在OpenCV中输出汉字！";

		float p = 0.5;
		text.setFont(NULL, NULL, NULL, &p);   // 透明处理

		text.putText(img, msg, cvPoint(100, 150), CV_RGB(255,0,0));
	}
	// 定义窗口，并显示影象

	CvxWindow myWin("myWin");
	myWin.showImage(img);

	// 进入消息循环

	return app.exec();
}
#endif 