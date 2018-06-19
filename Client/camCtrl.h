#pragma once
#include "resource.h"
#include "roidefine.h"
#include "afxwin.h"
#include "NetSetting.h"
#include <thread>
#include <opencv2/opencv.hpp>
#include <mutex>
#include "xiApiPlusOcv.hpp"
#include <list>
#include <string>
// camCtrl 对话框

class CClientDlg;
class camCtrl : public CDialog
{
	DECLARE_DYNAMIC(camCtrl)

public:
	camCtrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~camCtrl();

// 对话框数据
	enum { IDD = IDD_CAMCTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRoidefine();
private:
	
	CComboBox m_imagesize;// 相机分辨率
	CComboBox m_monRaw;

    CComboBox m_trigger;
    CComboBox m_selector;
    CComboBox m_gpi1;
    CComboBox m_gpo1;
    CClientDlg* m_pParentDlg;
    xiAPIplusCameraOcv m_xiCam;
    cv::VideoCapture m_capCam;

public:
	virtual BOOL OnInitDialog();
    roidefine* m_pROIDefineDlg;
    CNetSetting* m_pNetSettingDlg;
	afx_msg void OnSelchangeComImagesize();
	afx_msg void OnSelchangeMonOrRaw();
    afx_msg void OnBnClickedRoi();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    bool m_bIsInSlidering;

    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    CBrush m_brush;
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnBnClickedButtonNetsetting();
    afx_msg void OnBnClickedButtonStart();
    afx_msg void OnBnClickedButtonSave();
    void threadAcquistion(LPVOID lpParam);//线程处理函数
    void threadSave(LPVOID lpParam);
    std::mutex m_mutex;
    cv::Mat m_cvImage;
    std::list<cv::Mat> m_imagesVector;
    bool m_bSave;
    bool imageToStreamFile(cv::Mat image, std::string filename);
    afx_msg void OnBnClickedButtonExit();
    afx_msg void OnNMReleasedcaptureSliderExposuretime(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderGain(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSlideFramerate(NMHDR *pNMHDR, LRESULT *pResult);
};
