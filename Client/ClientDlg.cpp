
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientDlg 对话框



CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CClientDlg::IDD, pParent)
, s_psever(&listener)
, m_bIsRunning(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_cameraPara.maxOffset_x = 640;
    m_cameraPara.maxOffset_y = 512;
    m_cameraPara.maxWidth = 800;
    m_cameraPara.maxHeight = 640;

    m_cameraPara.incOffset_x = m_cameraPara.incWidth = 16;
    m_cameraPara.incOffset_y = m_cameraPara.incHeight = 2;
    m_cameraSetting.rectROI = CRect(0,0,320, 256);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC, m_picCtrl);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_MESSAGE(WM_ROICHANGE, OnROIRectChanged)
    ON_MESSAGE(WM_CLOSE_ROIDEFINE, OnROIDefineDlgClosed)
    ON_MESSAGE(WM_CLOSE_NETSETTING, OnNetSettingDlgClosed)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
    //SkinH_Attach();
	listener.m_pDlg = this;
   
	m_picCtrl.MoveWindow(0, 0, 880, 720);//800*640 + 40*2的刻度尺
    m_picCtrl.setImage(cv::imread("img.jpg"));

	cameraCtrl = new camCtrl(this);
	cameraCtrl->Create(IDD_CAMCTRL, this);

    CRect rect;
    cameraCtrl->GetClientRect(&rect);
    cameraCtrl->MoveWindow(880, 0, rect.Width(),rect.Height(), FALSE);
	cameraCtrl->ShowWindow(SW_SHOW);

    this->MoveWindow(0, 0, 880 + rect.Width(), 800);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CClientDlg::OnBnClickedConnect()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	s_psever->SetMaxPackSize(0x01FFFFF);
//	s_psever->SetPackHeaderFlag(0x169);
//	if (!s_psever->Start("127.0.0.1", 5555, 1, "0.0.0.0")){
//		MessageBox("start error!!");
//	}
//	
//	cam.OpenFirst();
//	cam.SetWidth(640);
//	cam.SetHeight(480);
//	cam.SetExposureTime(10000);
//	cam.StartAcquisition();
//
//	/*cap.open(0);
//	format = cam.GetImageDataFormat();*/
//	SetTimer(0, 100, nullptr);
//}

void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	/*cap >> m_image;
	cv::cvtColor(m_image, m_desImgl, CV_RGB2GRAY);
	s_psever->Send((LPBYTE)m_desImgl.data, m_desImgl.cols * m_desImgl.rows);*/

	//Mat cv_mat_image = cam.GetNextImageOcvMat();
	//if (format == XI_RAW16 || format == XI_MONO16){
	//	normalize(cv_mat_image, cv_mat_image, 0, 65536, NORM_MINMAX, -1, Mat());
	//}

	//s_psever->Send(cv_mat_image.data, cv_mat_image.cols*cv_mat_image.rows);

    if(m_bIsRunning) {
        m_picCtrl.setImage(cameraCtrl->m_cvImage);
    }
	CDialogEx::OnTimer(nIDEvent);
}


LRESULT CClientDlg::OnROIRectChanged(WPARAM wParam, LPARAM lParam)
{
    CRect rect;
    int iFrom = (int)wParam;
    switch(iFrom) {
        case 0:
            rect = *(CRect*)lParam;
            cameraCtrl->m_pROIDefineDlg->updateROIInfo(rect);
            break;
        case 1:
            m_picCtrl.setROIOffset_x((int)lParam);
            break;
        case 2:
            m_picCtrl.setROIOffset_y((int)lParam);
            break;
        case 3:
            m_picCtrl.setROIWidth((int)lParam);
            break;
        case 4:
            m_picCtrl.setROIHeight((int)lParam);
            break;
        default:
            break;
    }
    return 0;
}

LRESULT CClientDlg::OnROIDefineDlgClosed(WPARAM wParam, LPARAM lParam)
{
    if(IDOK == (int)lParam) {
        m_cameraSetting.rectROI = *(CRect*)wParam;
    }
    m_picCtrl.showROIRect(false);
    delete cameraCtrl->m_pROIDefineDlg;
    cameraCtrl->m_pROIDefineDlg = nullptr;

    return 0;
}

LRESULT CClientDlg::OnNetSettingDlgClosed(WPARAM wParam, LPARAM lParam)
{
    if(IDOK == (int)lParam) {
        m_netPara = *(NET_PARA*)wParam;
        TRACE(m_netPara.sRemotePort + "&&" + m_netPara.sLocalPort);
    }
    delete cameraCtrl->m_pNetSettingDlg;
    cameraCtrl->m_pNetSettingDlg = nullptr;
    return 0;
}