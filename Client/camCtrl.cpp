// camCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "camCtrl.h"
#include "afxdialogex.h"
#include "resource.h"
#include "ClientDlg.h"

// camCtrl 对话框

IMPLEMENT_DYNAMIC(camCtrl, CDialog)

camCtrl::camCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(camCtrl::IDD, pParent)
    , m_pROIDefineDlg(nullptr)
    , m_pNetSettingDlg(nullptr)
    , m_bSave(false)
{
    m_pParentDlg = (CClientDlg*)pParent;
}

camCtrl::~camCtrl()
{
}

void camCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_IMAGESIZE, m_imagesize);
	DDX_Control(pDX, IDC_MON_OR_RAW, m_monRaw);
	DDX_Control(pDX, IDC_TRIG, m_trigger);
	DDX_Control(pDX, IDC_SELECTOR, m_selector);
	DDX_Control(pDX, IDC_GPI1, m_gpi1);
	DDX_Control(pDX, IDC_GPO1, m_gpo1);
}

BEGIN_MESSAGE_MAP(camCtrl, CDialog)

	ON_BN_CLICKED(IDC_ROIDEFINE, &camCtrl::OnBnClickedRoidefine)
	ON_CBN_SELCHANGE(IDC_COM_IMAGESIZE, &camCtrl::OnSelchangeComImagesize)
	ON_CBN_SELCHANGE(IDC_MON_OR_RAW, &camCtrl::OnSelchangeMonOrRaw)
    ON_BN_CLICKED(IDC_ROI, &camCtrl::OnBnClickedRoi)
    ON_WM_HSCROLL()
    ON_WM_PAINT()
    ON_WM_CTLCOLOR()
    ON_WM_DRAWITEM()
    ON_BN_CLICKED(IDC_BUTTON_NETSETTING, &camCtrl::OnBnClickedButtonNetsetting)
    ON_BN_CLICKED(IDC_BUTTON_START, &camCtrl::OnBnClickedButtonStart)
    ON_BN_CLICKED(IDC_BUTTON_SAVE, &camCtrl::OnBnClickedButtonSave)
    ON_BN_CLICKED(IDC_BUTTON_EXIT, &camCtrl::OnBnClickedButtonExit)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_EXPOSURETIME, &camCtrl::OnNMReleasedcaptureSliderExposuretime)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_GAIN, &camCtrl::OnNMReleasedcaptureSliderGain)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDE_FRAMERATE, &camCtrl::OnNMReleasedcaptureSlideFramerate)
END_MESSAGE_MAP()

BOOL camCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_brush.CreateSolidBrush(RGB(236, 243, 246));
	//相机分辨率
	m_imagesize.AddString(_T("1280*1024"));
	m_imagesize.AddString(_T("640*512"));
	m_imagesize.SetCurSel(0);

	//Raw
	m_monRaw.AddString(_T("Mono8"));
	m_monRaw.AddString(_T("Mono16"));
	m_monRaw.AddString(_T("Raw8"));
	m_monRaw.AddString(_T("Raw16"));
	m_monRaw.SetCurSel(0);

	//触发方式
	m_trigger.AddString(_T("Off"));
	m_trigger.AddString(_T("Rising"));
	m_trigger.AddString(_T("Falling edge"));
	m_trigger.AddString(_T("Software"));
	m_trigger.SetCurSel(0);

	//选择器
	m_selector.AddString(_T("Frame start"));
	m_selector.AddString(_T("Exposure active"));
	m_selector.AddString(_T("Frame burst start"));
	m_selector.AddString(_T("Frame burst active"));
	m_selector.AddString(_T("Multitle exposure"));
	m_selector.SetCurSel(0);

	//GPI
	m_gpi1.AddString(_T("Off"));
	m_gpi1.AddString(_T("Trigger"));
	m_gpi1.SetCurSel(0);

	//GPO
	m_gpo1.AddString(_T("Off"));
	m_gpo1.AddString(_T("On"));
	m_gpo1.AddString(_T("Frame active(neg.)"));
	m_gpo1.AddString(_T("Exposure active"));
	m_gpo1.AddString(_T("Exposure active(neg.)"));
	m_gpo1.AddString(_T("Frame trigger wait"));
	m_gpo1.AddString(_T("Frame trigger wait(neg.)"));
	m_gpo1.AddString(_T("Exposure pulse"));
	m_gpo1.AddString(_T("Exposure pulse(neg.)"));
	m_gpo1.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void camCtrl::OnBnClickedRoidefine()
{
    if(m_pROIDefineDlg == nullptr) {
        CClientDlg* pDlg = (CClientDlg*)m_pParentWnd;
        pDlg->m_picCtrl.setROIRect(pDlg->m_cameraSetting.rectROI);
        pDlg->m_picCtrl.showROIRect(true);
        m_pROIDefineDlg = new roidefine(pDlg);
        m_pROIDefineDlg->Create(IDD_ROIDEFINE, pDlg);
        m_pROIDefineDlg->SetWindowText(_T("ROI设置"));
	    m_pROIDefineDlg->ShowWindow(SW_SHOW);
    } 
}

void camCtrl::OnSelchangeComImagesize()
{

	//    if(camClose == m_camCtrl->getCameraStatus())
	//        return;
	//    switch (index) {
	//    case 0:
	//        m_camCtrl->getCameraHandle()->SetDownsampling(XI_DWN_1x1);

	//        break;
	//    case 1:
	//        m_camCtrl->getCameraHandle()->SetDownsampling(XI_DWN_2x2);
	//        break;
	//    default:
	//        break;
	//    }
	//        updateFrameRateInfo();
	int nSel;
	nSel = m_imagesize.GetCurSel();// 获取组合框控件的列表框中选中项的索引 
	switch (nSel)
	{
	case 0:
		break;
	case 1:
		break;

	default:
		break;
	}
}

void camCtrl::OnSelchangeMonOrRaw()
{
	//    if(camClose == m_camCtrl->getCameraStatus())
	//        return;
	//    qDebug()<<"onComImageTypeChanged"<<index;
	int index;
	index = m_monRaw.GetCurSel();
	//    m_camCtrl->setImageFormat(index);
}

void camCtrl::OnBnClickedRoi()
{
    // TODO:  在此添加控件通知处理程序代码
}


//void camCtrl::OnEnKillfocusEdit3()
//{
//    // TODO:  在此添加控件通知处理程序代码
//    //((CSliderCtrl*)GetDlgItem(IDC_SLIDER1))->SetPos(GetDlgItemInt(IDC_EDIT3));
//}


void camCtrl::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    //CRect rect;
    //GetClientRect(&rect);
    //dc.FillSolidRect(rect, RGB(236, 243, 246));
    //dc.SetBkMode(TRANSPARENT);
    // TODO:  在此处添加消息处理程序代码
    // 不为绘图消息调用 CDialog::OnPaint()
}


HBRUSH camCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  在此更改 DC 的任何特性
    if(nCtlColor == CTLCOLOR_DLG) {
        return m_brush;
    }
    if(nCtlColor == CTLCOLOR_STATIC) {
        pDC->SetTextColor(RGB(0, 0, 0));
        pDC->SetBkColor(RGB(236, 243, 246));
        hbr = (HBRUSH)m_brush;
    }
    if(nCtlColor == CTLCOLOR_EDIT) {
        pDC->SetTextColor(RGB(0, 0, 0));
        pDC->SetBkMode(TRANSPARENT);
        hbr = (HBRUSH)m_brush;
    }
    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    return hbr;
}


void camCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    if(lpDrawItemStruct->CtlType == ODT_BUTTON)         //checking for the button 
    {
        CDC dc;
        RECT rect;
        dc.Attach(lpDrawItemStruct->hDC);   // Get the Button DC to CDC
        rect = lpDrawItemStruct->rcItem;     //Store the Button rect to our local rect.
        dc.Draw3dRect(&rect, RGB(255, 255, 255), RGB(0, 0, 0));
        dc.FillSolidRect(&rect, RGB(236, 243, 246));//Here you can define the required color to appear on the Button.
        UINT state = lpDrawItemStruct->itemState; //This defines the state of the Push button either pressed or not
        if((state & ODS_SELECTED)) {
            dc.DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);

        } else {
            dc.DrawEdge(&rect, EDGE_RAISED, BF_RECT);
        }
        dc.SetTextColor(RGB(0, 0, 0));
        dc.SetBkColor(RGB(236, 243, 246));
        TCHAR buffer[MAX_PATH];           //To store the Caption of the button.
        ZeroMemory(buffer, MAX_PATH);     //Intializing the buffer to zero
        ::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH); //Get the Caption of Button Window 
        dc.DrawText(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//Redraw the Caption of Button Window 
        dc.Detach(); // Detach the Button DC
    }
    CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void camCtrl::OnBnClickedButtonNetsetting()
{
    // TODO:  在此添加控件通知处理程序代码
    if(m_pNetSettingDlg == nullptr) {
        CClientDlg* pDlg = (CClientDlg*)m_pParentWnd;
        m_pNetSettingDlg = new CNetSetting(pDlg);
        m_pNetSettingDlg->Create(IDD_NETSETTING, pDlg);
        m_pNetSettingDlg->SetWindowText(_T("网络设置"));
        m_pNetSettingDlg->ShowWindow(SW_SHOW);
    }
}


void camCtrl::OnBnClickedButtonStart()
{
    // TODO:  在此添加控件通知处理程序代码
    if(!m_pParentDlg->m_bIsRunning) {
        m_pParentDlg->m_bIsRunning = true;
        SetDlgItemText(IDC_BUTTON_START, "关闭");
        m_xiCam.OpenFirst();
        m_xiCam.SetExposureTime(1000);
        m_xiCam.SetAcquisitionTimingMode(XI_ACQ_TIMING_MODE_FRAME_RATE);//设置帧率模式
        m_xiCam.SetRegion_selector(0); // default is 0
        m_xiCam.SetOffsetX(240);
        m_xiCam.SetOffsetY(192);
        m_xiCam.SetWidth(800);
        m_xiCam.SetHeight(640);
        m_xiCam.SetFrameRate(400.0f);
        m_xiCam.SetExposureTime(1000); 

        m_xiCam.StartAcquisition();
        //m_capCam.open(0);
        std::thread acquisitionThread = std::thread(&camCtrl::threadAcquistion, this, nullptr);
        acquisitionThread.detach();
    } else {
        m_pParentDlg->m_bIsRunning = false;
        SetDlgItemText(IDC_BUTTON_START, "开始");
        cv::waitKey(200);
        m_capCam.release();
        m_xiCam.StopAcquisition();
        m_xiCam.Close();
    }
}


void camCtrl::OnBnClickedButtonSave()
{
    // TODO:  在此添加控件通知处理程序代码
    if(!m_bSave) {
        m_bSave = true;
        SetDlgItemText(IDC_BUTTON_SAVE, "停止");
        GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
        std::thread saveThread = std::thread(&camCtrl::threadSave, this, nullptr);
        saveThread.detach();
    } else {
        m_bSave = false;
        SetDlgItemText(IDC_BUTTON_SAVE, "保存");
    }
}

void camCtrl::threadAcquistion(LPVOID lpParam)
{
    m_pParentDlg->SetTimer(0, 100, nullptr);
    XI_IMG_FORMAT format;
    while (true)
    {
        m_mutex.lock();
        if(!m_pParentDlg->m_bIsRunning)
            break;
        m_mutex.unlock();
        m_cvImage = m_xiCam.GetNextImageOcvMat();
        format = m_xiCam.GetImageDataFormat();
        if(format == XI_RAW16 || format == XI_MONO16)
            cv::normalize(m_cvImage, m_cvImage, 0, 65536, cv::NORM_MINMAX, -1, cv::Mat()); // 0 - 65536, 16 bit unsigned integer range
        //m_capCam >> m_cvImage;
        if(m_cvImage.empty())
            continue;
        m_capCam >> m_cvImage;
        if(m_bSave) {
            m_imagesVector.push_back(m_cvImage);
        }
    }
    m_pParentDlg->KillTimer(0);
    m_pParentDlg->m_picCtrl.setImage(cv::imread("img.jpg"));
}

bool camCtrl::imageToStreamFile(cv::Mat image, std::string filename)
{
    if(image.empty())
        return false;
    const char *filenamechar = filename.c_str();
    FILE *fpw;
    errno_t err = fopen_s(&fpw, filenamechar, "wb");//如果没有则创建，如果存在则从头开始写  
    if(err != 0) {
        fclose(fpw);
        return false;
    }
    int channl = image.channels();//第一个字节  通道  
    int rows = image.rows;     //四个字节存 行数  
    int cols = image.cols;   //四个字节存 列数  

    fwrite(&channl, sizeof(char), 1, fpw);
    fwrite(&rows, sizeof(char), 4, fpw);
    fwrite(&cols, sizeof(char), 4, fpw);
    char* dp = (char*)image.data;
    if(channl == 3) {
        for(int i = 0; i < rows*cols; i++) {
            fwrite(&dp[i * 3], sizeof(char), 1, fpw);
            fwrite(&dp[i * 3 + 1], sizeof(char), 1, fpw);
            fwrite(&dp[i * 3 + 2], sizeof(char), 1, fpw);
        }
    } else if(channl == 1) {
        for(int i = 0; i < rows*cols; i++) {
            fwrite(&dp[i], sizeof(char), 1, fpw);
        }
    }
    fclose(fpw);
    return true;
}


void camCtrl::threadSave(LPVOID lpParam)
{
    int num = 0;
    CTime mTime;
    std::string path;
    bool flag = true;
    while(true) {
        if(m_imagesVector.size() > 0) {
            if(flag) {
                mTime = CTime::GetCurrentTime();
                CString curdata;
                curdata = mTime.Format("%Y_%m_%d");
                path = curdata.GetBuffer();
                CString  strFolderPath = ".//" + curdata + "//";
                if(!PathIsDirectory(strFolderPath)) {
                    if(!CreateDirectory(strFolderPath, NULL)) {
                        AfxMessageBox(_T("保存路径创建失败！"));
                        return;
                    }
                }
                flag = false;
            }
            cv::Mat img = m_imagesVector.front();
            std::string filename = path + "//picture " + std::to_string(num);
            imageToStreamFile(img, filename);
            num++;
            m_imagesVector.pop_front();
        } else {
            if(m_bSave)
                continue;
            else
                break;
        }
    }
    GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
}

void camCtrl::OnBnClickedButtonExit()
{
    // TODO:  在此添加控件通知处理程序代码
    ::PostMessage(GetParent()->m_hWnd, WM_CLOSE, 0, 0);
}

void camCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    if(pScrollBar->GetDlgCtrlID() == IDC_SLIDER_EXPOSURETIME) {
        // nPos就是此时滑杆的位置，显示到 CEdit 就可以了 
        char temp[30];
        sprintf_s(temp, 30, "%d", nPos);
        GetDlgItem(IDC_EDIT_EXPO)->SetWindowText(temp);
        if(m_pParentDlg->m_bIsRunning) {
            m_xiCam.SetExposureTime(nPos);
        }

    }
    if(pScrollBar->GetDlgCtrlID() == IDC_SLIDER_GAIN) {
        // nPos就是此时滑杆的位置，显示到 CEdit 就可以了 
        char temp[30];
        sprintf_s(temp, 30, "%d", nPos);
        //或者 获取 Slider 当前位置 
        //sprintf_s(temp, 30, "%d", ((CSliderCtrl*)pScrollBar)->GetPos());
        GetDlgItem(IDC_EDIT_GAIN)->SetWindowText(temp);
        if(m_pParentDlg->m_bIsRunning) {
            m_xiCam.SetGain(nPos);
        }
    }
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void camCtrl::OnNMReleasedcaptureSliderExposuretime(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  在此添加控件通知处理程序代码
    CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXPOSURETIME);
    SetDlgItemInt(IDC_EDIT_EXPO, pSlider->GetPos());
    if(m_pParentDlg->m_bIsRunning) {
        m_xiCam.SetExposureTime(pSlider->GetPos());
    }
    *pResult = 0;
}


void camCtrl::OnNMReleasedcaptureSliderGain(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  在此添加控件通知处理程序代码
    if(!m_pParentDlg->m_bIsRunning)
        return;
    CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_GAIN);
    SetDlgItemInt(IDC_EDIT_GAIN, pSlider->GetPos());
    if(m_pParentDlg->m_bIsRunning) {
        m_xiCam.SetGain(pSlider->GetPos());
    }
    *pResult = 0;
}


void camCtrl::OnNMReleasedcaptureSlideFramerate(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  在此添加控件通知处理程序代码
    if(!m_pParentDlg->m_bIsRunning)
        return;
    CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDE_FRAMERATE);
    SetDlgItemInt(IDC_EDIT_FRAME, pSlider->GetPos());
    if(m_pParentDlg->m_bIsRunning) {
        m_xiCam.SetFrameRate(pSlider->GetPos());
    }
    *pResult = 0;
}
