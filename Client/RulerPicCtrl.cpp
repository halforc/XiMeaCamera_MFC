// RulerPicCtrl.cpp : 实现文件
//

#include "stdafx.h"
//#include "XiMeaClient.h"
#include "RulerPicCtrl.h"


// CRulerPicCtrl

IMPLEMENT_DYNAMIC(CRulerPicCtrl, CStatic)

CRulerPicCtrl::CRulerPicCtrl() : 
m_fontWidth(8),
m_fontHeight(20),
m_bHasRuler(TRUE),
m_rulerWidth(40),
m_IsDrawROI(FALSE)
{
    m_rectTracker.m_nStyle = CRectTracker::resizeOutside | CRectTracker::solidLine;
    m_rectTracker.m_sizeMin = CSize(160, 128);
}

CRulerPicCtrl::~CRulerPicCtrl()
{
}


BEGIN_MESSAGE_MAP(CRulerPicCtrl, CStatic)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CRulerPicCtrl 消息处理程序
void CRulerPicCtrl::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO:  在此处添加消息处理程序代码
    // 不为绘图消息调用 CStatic::OnPaint()
    GetClientRect(&m_rect);

    CPaintDC *pDC = &dc;
    pDC->SetBkMode(TRANSPARENT);

    /*内存绘图*/
    CDC memDC;
    memDC.CreateCompatibleDC(&dc);
    CBitmap m_MemMap;
    m_MemMap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
    memDC.SelectObject(&m_MemMap);
    memDC.FillSolidRect(m_rect, RGB(236, 243, 246));
    memDC.SetBkMode(TRANSPARENT);

    if(m_bHasRuler) {
        mrect.top = m_rect.top + m_rulerWidth;
        mrect.left = m_rect.left + m_rulerWidth;
        mrect.bottom = m_rect.bottom - m_rulerWidth;
        mrect.right = m_rect.right - m_rulerWidth;
    } else {
        mrect = m_rect;
    }

    if(!m_image.empty()) {
        CImage image;

        cv::Size winSize(mrect.right - mrect.left, mrect.bottom - mrect.top);
        cv::Mat cvImgTmp(winSize, CV_8UC3);
        //Resize the source to the size of the destination image if necessary  

        if(m_image.size() != winSize) {
            cv::resize(m_image, cvImgTmp, winSize);
        } else {
            cvImgTmp = m_image;
        }
        Mat2CImage(&cvImgTmp, image);
        image.Draw(memDC, mrect);
    }

    if(m_bHasRuler) {
        CFont font;
        font.CreateFont(
            m_fontHeight, // nHeight  
            m_fontWidth, // nWidth  
            0, // nEscapement  
            0, // nOrientation  
            FW_NORMAL, // nWeight  
            FALSE, // bItalic  
            FALSE, // bUnderline  
            0, // cStrikeOut  
            ANSI_CHARSET, // nCharSet  
            OUT_DEFAULT_PRECIS, // nOutPrecision  
            CLIP_DEFAULT_PRECIS, // nClipPrecision  
            DEFAULT_QUALITY, // nQuality  
            DEFAULT_PITCH | FF_SWISS,
            _T("Arial") // nPitchAndFamily Arial  
            );
        
        CFont* oldFont = memDC.SelectObject(&font);

        //指定标尺宽度  
        int width = mrect.Width();
        int height = mrect.Height();
        int wMid = mrect.left + width / 2;
        int hMid = mrect.top + height / 2;
        //画刻度线  
        int degree = 0;
        CString string;
        memDC.SetBkMode(TRANSPARENT);//消除白色背景 
        //大刻度：32  小刻度：4  每个大刻度包含8个小刻度

        memDC.SetTextAlign(TA_CENTER | TA_TOP);//将刻度线数字标注在刻度线的下方  
        //画大刻度  大刻度 10   小刻度 5
        for(; wMid + degree <= mrect.right; degree += 32) {
            //下右方 
            memDC.MoveTo(wMid + degree, mrect.bottom);
            memDC.LineTo(wMid + degree, mrect.bottom + 10);
            //上右方
            memDC.MoveTo(wMid + degree, mrect.top);
            memDC.LineTo(wMid + degree, mrect.top - 10);

            string.Format(_T("%d"), (degree) / 32);
            memDC.TextOut(wMid + degree, mrect.bottom + 10, string); //画出数字标注  
            memDC.TextOut(wMid + degree, mrect.top - 10 - m_fontHeight, string); //画出数字标注  

            //下左方 
            memDC.MoveTo(wMid - degree, mrect.bottom);
            memDC.LineTo(wMid - degree, mrect.bottom + 10);
            //上左方
            memDC.MoveTo(wMid - degree, mrect.top);
            memDC.LineTo(wMid - degree, mrect.top - 10);

            string.Format(_T("%d"), (-1 * degree) / 32);
            memDC.TextOut(wMid - degree, mrect.bottom + 10, string); //画出数字标注  
            memDC.TextOut(wMid - degree, mrect.top - 10 - m_fontHeight, string); //画出数字标注  
        }
        //上下小刻度
        for(degree = 4; wMid + degree <= mrect.right; degree += 4) {
            //右方
            memDC.MoveTo(wMid + degree, mrect.bottom);
            memDC.LineTo(wMid + degree, mrect.bottom + 5);


            memDC.MoveTo(wMid + degree, mrect.top);
            memDC.LineTo(wMid + degree, mrect.top - 5);

            //左方
            memDC.MoveTo(wMid - degree, mrect.bottom);
            memDC.LineTo(wMid - degree, mrect.bottom + 5);

            memDC.MoveTo(wMid - degree, mrect.top);
            memDC.LineTo(wMid - degree, mrect.top - 5);
        }
        //左右刻度尺
        memDC.SetTextAlign(TA_RIGHT);//将刻度线数字标注在刻度线的左方  
        for(degree = 0; hMid + degree <= mrect.bottom; degree += 32) {
            //左方 
            memDC.MoveTo(mrect.left, hMid + degree);
            memDC.LineTo(mrect.left - 10, hMid + degree);
            //右方
            memDC.MoveTo(mrect.right, hMid + degree);
            memDC.LineTo(mrect.right + 10, hMid + degree);
            string.Format(_T("%d"), (-1 * degree) / 32);
            memDC.TextOut(mrect.left - 10, hMid + degree - m_fontHeight / 2, string); //画出数字标注  
            memDC.TextOut(mrect.right + 10 + 2 * m_fontWidth, hMid + degree - m_fontHeight / 2, string); //画出数字标注  

            memDC.MoveTo(mrect.left, hMid - degree);
            memDC.LineTo(mrect.left - 10, hMid - degree);
            memDC.MoveTo(mrect.right, hMid - degree);
            memDC.LineTo(mrect.right + 10, hMid - degree);
            string.Format(_T("%d"), (1 * degree) / 32);
            memDC.TextOut(mrect.left - 10, hMid - degree - m_fontHeight / 2, string); //画出数字标注  
            memDC.TextOut(mrect.right + 10 + 2 * m_fontWidth, hMid - degree - m_fontHeight / 2, string); //画出数字标注  

        }
        for(degree = 4; hMid + degree <= mrect.bottom; degree += 4) {
            memDC.MoveTo(mrect.left, hMid + degree);
            memDC.LineTo(mrect.left - 5, hMid + degree);
            memDC.MoveTo(mrect.right, hMid + degree);
            memDC.LineTo(mrect.right + 5, hMid + degree);

            memDC.MoveTo(mrect.left, hMid - degree);
            memDC.LineTo(mrect.left - 5, hMid - degree);
            memDC.MoveTo(mrect.right, hMid - degree);
            memDC.LineTo(mrect.right + 5, hMid - degree);
        }
    }
    
    if(m_IsDrawROI) {
        HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH oldBrush = (HBRUSH)memDC.SelectObject(hBrush);
        //设置边界
        m_rectTracker.m_rect = m_rectROI;
        //坐标映射;L逻辑 ---> D设备
        memDC.LPtoDP(&m_rectTracker.m_rect);
        //画图形的边界

        CPen Pen(PS_SOLID, 1, RGB(255, 0, 0));
        m_rectTracker.Draw(&memDC, &Pen);

        memDC.SelectObject(oldBrush);
        DeleteObject(hBrush);
    }
    /*复制到界面dc*/
    pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), &memDC, 0, 0, SRCCOPY);

    /*清理内存*/
    m_MemMap.DeleteObject();
    memDC.DeleteDC();
}

bool CRulerPicCtrl::setImage(const char* filename)
{
    return setImage(cv::imread(filename));
}

bool CRulerPicCtrl::setImage(Mat mat)
{
    if(mat.empty())
        return false;
    m_image = mat;
    InvalidateRect(mrect);
    return true;
}

void CRulerPicCtrl::setRulerWidth(int width)
{
    GetClientRect(&m_rect);
    if(width > 10 && width < m_rect.Width() / 4) {
        m_rulerWidth = width;
        m_fontWidth = (m_rulerWidth - 10) / 8 * 3;
        m_fontHeight = m_rulerWidth - 10;
        Invalidate();
    }
}

CRect CRulerPicCtrl::getPictrueRect()
{
    return mrect;
}

int CRulerPicCtrl::Mat2CImage(cv::Mat* mat, CImage &img)
{
    if(!mat || mat->empty())
        return -1;
    int nBPP = mat->channels() * 8;
    img.Create(mat->cols, mat->rows, nBPP);
    if(nBPP == 8) {
        static RGBQUAD pRGB[256];
        for(int i = 0; i < 256; i++)
            pRGB[i].rgbBlue = pRGB[i].rgbGreen = pRGB[i].rgbRed = i;
        img.SetColorTable(0, 256, pRGB);
    }
    uchar* psrc = mat->data;
    uchar* pdst = (uchar*)img.GetBits();
    int imgPitch = img.GetPitch();
    for(int y = 0; y < mat->rows; y++) {
        memcpy(pdst, psrc, mat->cols*mat->channels());
        psrc += mat->step;
        pdst += imgPitch;
    }
    return 0;
}

CRect CRulerPicCtrl::getRect()
{
    return m_rect;
}

void CRulerPicCtrl::showRuler(bool bShow)
{
    m_bHasRuler = bShow;
    Invalidate();
}


void CRulerPicCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    int ret = m_rectTracker.HitTest(point);
    if(ret >= 0)//判断是否要画调整边框
    {
        m_IsDrawROI = TRUE;
        InvalidateRect(&m_rectTracker.m_rect);
        //Invalidate();
        if(ret == CRectTracker::hitMiddle)//只有当鼠标在中间按下,才限制鼠标移动区域
        {
            POINT pos;
            GetCursorPos(&pos);
            ScreenToClient(&pos);
            CRect ClientRect = mrect;
            ClientRect.left += pos.x - m_rectROI.left;
            ClientRect.top += pos.y - m_rectROI.top;
            ClientRect.right -= m_rectROI.right - pos.x;
            ClientRect.bottom -= m_rectROI.bottom - pos.y;
            ClientToScreen(&ClientRect);
            ClipCursor(&ClientRect);
        } else//在调整矩形时也不能调整到外面去.
        {
            POINT pos;
            GetCursorPos(&pos);
            ScreenToClient(&pos);
            //GetClientRect(&mrect);
            CRect rect = mrect;
            ClientToScreen(&rect);
            ClipCursor(&rect);
        }
    } 

    //此函数会拦截掉鼠标消息,所以要在这个函数后面写鼠标弹起要处理的事件.
    if(m_rectTracker.Track(this, point, false, NULL)) {
        //鼠标弹起后才执行下面的程序
        //CClientDC   dc(this);
        static CRect rect;
        rect = m_rectTracker.m_rect;
        if(m_bHasRuler) {
            rect.OffsetRect(-1 * m_rulerWidth,-1 * m_rulerWidth);
        }
        rect.left = (rect.left + 8) / 16 * 16;
        rect.top = (rect.top + 1) / 2 * 2;
        rect.right = (rect.right + 8) / 16 * 16;
        rect.bottom = (rect.bottom + 1) / 2 * 2;
        ::PostMessage(GetParent()->m_hWnd, WM_ROICHANGE, 0, (LPARAM)&rect);

        m_rectTracker.m_rect = rect;
        if(m_bHasRuler) {
            m_rectTracker.m_rect.OffsetRect(m_rulerWidth, m_rulerWidth);
        }
        m_rectROI = m_rectTracker.m_rect;

        Invalidate(true);


        ClipCursor(NULL);
    } else {
        //鼠标弹起后执行下面的程序.
        ClipCursor(NULL);
    }
    CStatic::OnLButtonDown(nFlags, point);
}


BOOL CRulerPicCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    if(m_IsDrawROI && pWnd == this && m_rectTracker.SetCursor(this, nHitTest))//
    {
        return TRUE;
    }
    return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CRulerPicCtrl::showROIRect(bool bShow)
{
    m_IsDrawROI = bShow;
    Invalidate();
}

CRect CRulerPicCtrl::getROIRect()
{
    return m_rectROI;
}

void CRulerPicCtrl::setROIRect(CRect rect)
{
    m_rectROI = rect;
    if(m_bHasRuler) {
        m_rectROI.OffsetRect(m_rulerWidth, m_rulerWidth);
    }
    Invalidate();
}

void CRulerPicCtrl::setROIOffset_x(int offset_x)
{
    if(m_bHasRuler) {
        offset_x += m_rulerWidth;
    }
    int iWidth = m_rectROI.Width();
    m_rectROI.left = offset_x;
    m_rectROI.right = m_rectROI.left + iWidth;
    Invalidate();
}

void CRulerPicCtrl::setROIOffset_y(int offset_y)
{
    if(m_bHasRuler) {
        offset_y += m_rulerWidth;
    }
    int iHeight = m_rectROI.Height();
    m_rectROI.top = offset_y;
    m_rectROI.bottom = m_rectROI.top + iHeight;;
    Invalidate();
}

void CRulerPicCtrl::setROIWidth(int width)
{
    m_rectROI.right = m_rectROI.left +  width;
    Invalidate();
}

void CRulerPicCtrl::setROIHeight(int height)
{
    m_rectROI.bottom = m_rectROI.top + height;
    Invalidate();
}

