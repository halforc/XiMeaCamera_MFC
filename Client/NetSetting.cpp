// NetSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "NetSetting.h"
#include "afxdialogex.h"
#include "ClientDlg.h"

// CNetSetting �Ի���

IMPLEMENT_DYNAMIC(CNetSetting, CDialog)

CNetSetting::CNetSetting( CWnd* pParent /*=NULL*/)
	: CDialog(CNetSetting::IDD, pParent)
{
    m_pParentDlg = (CClientDlg*)pParent;
}

CNetSetting::~CNetSetting()
{
}

void CNetSetting::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LISTRECV, m_lsRecv);
}


BEGIN_MESSAGE_MAP(CNetSetting, CDialog)
    ON_BN_CLICKED(IDC_BUTTONCONNECT, &CNetSetting::OnBnClickedButtonconnect)
    ON_BN_CLICKED(IDOK, &CNetSetting::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTONSEND, &CNetSetting::OnBnClickedButtonsend)
END_MESSAGE_MAP()


// CNetSetting ��Ϣ�������


BOOL CNetSetting::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��

    SetDlgItemText(IDC_REMOTEIP, m_pParentDlg->m_netPara.strRemoteIP);
    SetDlgItemInt(IDC_REMOTEPORT, m_pParentDlg->m_netPara.sRemotePort);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}


void CNetSetting::OnBnClickedButtonconnect()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CString strLocalIP, strRemoteIP;
    int remotePort = GetDlgItemInt(IDC_REMOTEPORT);
    GetDlgItemText(IDC_REMOTEIP, strRemoteIP);
    if(!m_pParentDlg->s_psever->Start(strRemoteIP,
        remotePort, 1, "0.0.0.0")) {
        TCHAR localIP[30];
        int addrLen;
        USHORT localPort;
        m_pParentDlg->s_psever->GetLocalAddress(localIP, addrLen, localPort);
        strLocalIP.Format(_T("����IP��ַ:%s  �˿�:%d"), localIP, localPort);
        SetDlgItemText(IDC_STATIC_INFO, strLocalIP);
    } else {
        MessageBox("start error!!");
    }
}


void CNetSetting::OnBnClickedOk()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    para.sRemotePort = GetDlgItemInt(IDC_REMOTEPORT);
    //para.sLocalPort = GetDlgItemInt(IDC_LOCALPORT);
    GetDlgItemText(IDC_REMOTEIP, para.strRemoteIP);
    ::PostMessage(GetParent()->m_hWnd, WM_CLOSE_NETSETTING, (WPARAM)&para, (LPARAM)IDOK);
    CDialog::OnOK();
}


void CNetSetting::OnBnClickedButtonsend()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CString strSendMes;
    GetDlgItemText(IDC_EDITSEND, strSendMes);
    int iLength = strSendMes.GetLength();
    m_pParentDlg->s_psever->Send((BYTE*)strSendMes.GetBuffer(iLength),iLength);
}
