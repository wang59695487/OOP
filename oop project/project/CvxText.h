//====================================================================
//====================================================================
//
// �ļ�: CvxText.h
//
// ˵��: OpenCV�������
//
// ʱ��: 
//
// ����: ����ɼ
//       chaishushan#gmail.com
//       chaishushan.googlepages.com
//
//====================================================================
//====================================================================

#ifndef OPENCV_CVX_TEXT_2007_08_31_H
#define OPENCV_CVX_TEXT_2007_08_31_H

/**
* \file CvxText.h
* \brief OpenCV��������ӿ�
*
* ʵ���˺���������ܡ�
*/
#include <opencv2/opencv.hpp> 
//#include <highgui.h>

#include <ft2build.h>
#include FT_FREETYPE_H

/**
* \class CvxText
* \brief OpenCV���������
*
* OpenCV��������֡��ֿ���ȡ�����˿�Դ��FreeFype�⡣����FreeFype��
* GPL��Ȩ�����Ŀ⣬��OpenCV��Ȩ����һ�£����Ŀǰ��û�кϲ���OpenCV
* ��չ���С�
*
* ��ʾ���ֵ�ʱ����Ҫһ�������ֿ��ļ����ֿ��ļ�ϵͳһ�㶼�Դ��ˡ�
* ������õ���һ����Դ���ֿ⣺����Ȫ�������塱��
*
* ����"OpenCV��չ��"��ϸ�������
* http://code.google.com/p/opencv-extension-library/
*
* ����FreeType��ϸ�������
* http://www.freetype.org/
*
* ���ӣ�
*
* \code
int main(int argc, char *argv[])
{
   // ����CvxApplication����

   CvxApplication app(argc, argv);

   // ��һ��Ӱ��

   cv::Mat *img = cvLoadImage("test.jpg", 1);

   // �������

   {
      // "wqy-zenhei.ttf"Ϊ��Ȫ��������

      CvText text("wqy-zenhei.ttf");

      const char *msg = "��OpenCV��������֣�";

      float p = 0.5;
      text.setFont(NULL, NULL, NULL, &p);   // ͸������

      text.putText(img, msg, cvPoint(100, 150), CV_RGB(255,0,0));
   }
   // ���崰�ڣ�����ʾӰ��

   CvxWindow myWin("myWin");
   myWin.showImage(img);

   // ������Ϣѭ��

   return app.exec();
}
* \endcode
*/

class CvxText  
{
  
   CvxText& operator=(const CvxText&);

public:

   /**
    * װ���ֿ��ļ�
    */

   CvxText(const char *freeType);
   virtual ~CvxText();

   FT_Error SetFontSizes(FT_UInt  pixel_width,FT_UInt  pixel_height );

   //================================================================
   //================================================================

   /**
    * ��ȡ���塣Ŀǰ��Щ�����в�֧�֡�
    *
    * \param font        ��������, Ŀǰ��֧��
    * \param size        �����С/�հױ���/�������/��ת�Ƕ�
    * \param underline   �»���
    * \param diaphaneity ͸����
    *
    * \sa setFont, restoreFont
    */

   void getFont(int *type,
      cv::Scalar *size=NULL, bool *underline=NULL, float *diaphaneity=NULL);

   /**
    * �������塣Ŀǰ��Щ�����в�֧�֡�
    *
    * \param font        ��������, Ŀǰ��֧��
    * \param size        �����С/�հױ���/�������/��ת�Ƕ�
    * \param underline   �»���
    * \param diaphaneity ͸����
    *
    * \sa getFont, restoreFont
    */

   void setFont(int *type,
      cv::Scalar *size=NULL, bool *underline=NULL, float *diaphaneity=NULL);

   /**
    * �ָ�ԭʼ���������á�
    *
    * \sa getFont, setFont
    */

   void restoreFont();

   //================================================================
   //================================================================

   /**
    * �������(��ɫĬ��Ϊ��ɫ)����������������ַ���ֹͣ��
    *
    * \param img  �����Ӱ��
    * \param text �ı�����
    * \param pos  �ı�λ��
    *
    * \return ���سɹ�������ַ����ȣ�ʧ�ܷ���-1��
    */

   int putText(cv::Mat *img, const char    *text, cv::Point pos);

   /**
    * �������(��ɫĬ��Ϊ��ɫ)����������������ַ���ֹͣ��
    *
    * \param img  �����Ӱ��
    * \param text �ı�����
    * \param pos  �ı�λ��
    *
    * \return ���سɹ�������ַ����ȣ�ʧ�ܷ���-1��
    */

   int putText(cv::Mat *img, const wchar_t *text, cv::Point pos);

   /**
    * ������֡���������������ַ���ֹͣ��
    *
    * \param img   �����Ӱ��
    * \param text  �ı�����
    * \param pos   �ı�λ��
    * \param color �ı���ɫ
    *
    * \return ���سɹ�������ַ����ȣ�ʧ�ܷ���-1��
    */

   int putText(cv::Mat *img, const char    *text, cv::Point pos, cv::Scalar color);

   /**
    * ������֡���������������ַ���ֹͣ��
    *
    * \param img   �����Ӱ��
    * \param text  �ı�����
    * \param pos   �ı�λ��
    * \param color �ı���ɫ
    *
    * \return ���سɹ�������ַ����ȣ�ʧ�ܷ���-1��
    */
   int putText(cv::Mat *img, const wchar_t *text, cv::Point pos, cv::Scalar color);

   //================================================================
   //================================================================

private:

   // �����ǰ�ַ�, ����m_posλ��

   void putWChar(cv::Mat *img, wchar_t wc, cv::Point &pos, cv::Scalar color);

   //================================================================
   //================================================================

private:

   FT_Library   m_library;   // �ֿ�
   FT_Face      m_face;      // ����

   //================================================================
   //================================================================

   // Ĭ�ϵ������������

   int         m_fontType;
   cv::Scalar   m_fontSize;
   bool      m_fontUnderline;
   float      m_fontDiaphaneity;

   //================================================================
   //================================================================
};

#endif // OPENCV_CVX_TEXT_2007_08_31_H
