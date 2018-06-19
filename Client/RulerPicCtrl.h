#pragma once
#include<opencv2\opencv.hpp> 
#include "MyRectTracker.h"

using namespace cv;
#define WM_ROICHANGE WM_USER+100
// CRulerPicCtrl

class CRulerPicCtrl : public CStatic
{
	DECLARE_DYNAMIC(CRulerPicCtrl)

public:
	CRulerPicCtrl();
	virtual ~CRulerPicCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnPaint();

    bool setImage(const char* filename);
    bool setImage(Mat mat);
    void setRulerWidth(int width);
    int getRulerWidth();
    CRect getPictrueRect();
    CRect getRect();
    void showRuler(bool bShow);
    void showROIRect(bool bShow);
    CRect getROIRect();
    void setROIRect(CRect rect);
    void setROIOffset_x(int offset_x);
    void setROIOffset_y(int offset_y);
    void setROIWidth(int width);
    void setROIHeight(int height);
private:
    int m_fontWidth;
    int m_fontHeight;
    bool m_bHasRuler;
    int m_rulerWidth;
    CRect m_rect;//¿Ø¼þ³ß´ç
    CRect mrect;//Í¼Æ¬ÇøÓò³ß´ç
    Mat m_image;
    int Mat2CImage(cv::Mat* mat, CImage &img);

    CMyRectTracker m_rectTracker;
    CRect m_rectROI;  //ROIÇøÓò
    BOOL m_IsDrawROI;
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


