
// ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "dataTypeDefine.h"

#include "RulerPicCtrl.h"
#include "TCPClientListenerClass.h"
#include "camCtrl.h"
#include <opencv2/opencv.hpp>

#include "xiApiPlusOcv.hpp"

#include "resource.h"



#pragma comment(lib,"HPSocket.lib")

// CClientDlg �Ի���
class CClientDlg : public CDialogEx
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//xiAPIplusCameraOcv cam;
	CRulerPicCtrl m_picCtrl;
	CTcpPackClientPtr s_psever;
	TCPClientListenerClass listener;
	
	cv::VideoCapture cap;
	cv::Mat m_image;
	cv::Mat m_desImgl;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg LRESULT OnROIRectChanged(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnROIDefineDlgClosed(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnNetSettingDlgClosed(WPARAM wParam, LPARAM lParam);
	XI_IMG_FORMAT format;
	camCtrl* cameraCtrl;

    CAMERA_SETTING m_cameraSetting;
    CAMERA_PARA m_cameraPara;
    bool m_bIsRunning;
    NET_PARA m_netPara;
private:

};
