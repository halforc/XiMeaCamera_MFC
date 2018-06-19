// roidefine.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "camCtrl.h"
#include "roidefine.h"
#include "afxdialogex.h"
#include "ClientDlg.h"

// roidefine �Ի���

IMPLEMENT_DYNAMIC(roidefine, CDialog)

roidefine::roidefine(CWnd* pParent /*=NULL*/)
	: CDialog(roidefine::IDD, pParent)

{
    m_pDlg = (CClientDlg*)pParent;
	//m_offset_x.SetBuddy(GetDlgItem(IDC_OFFSET_X_EDIT));
	//m_offset_y.SetBuddy(GetDlgItem(IDC_OFFSET_Y_EIDT));
	//m_width.SetBuddy(GetDlgItem(IDC_WIDTH_EDIT));
	//m_height.SetBuddy(GetDlgItem(IDC_HEIGHT_EDIT));

	//m_offset_x.SetRange(0, 640);
	//m_offset_y.SetRange(0, 512);
	//m_width.SetRange(320, 640);
	//m_height.SetRange(256, 512);

	//m_offset_x.SetBase(16);
	//m_offset_y.SetBase(2);
	//m_width.SetBase(16);
	//m_height.SetBase(2);

	//m_offset_x.SetPos(0);
	//m_offset_y.SetPos(0);

}

roidefine::~roidefine()
{
}

void roidefine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(roidefine, CDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OFFSET_X, &roidefine::OnDeltaposOffsetX)
    ON_NOTIFY(UDN_DELTAPOS, IDC_OFFSET_Y, &roidefine::OnDeltaposOffsetY)
    ON_NOTIFY(UDN_DELTAPOS, IDC_WIDTH, &roidefine::OnDeltaposWidth)
    ON_NOTIFY(UDN_DELTAPOS, IDC_HEIGHT, &roidefine::OnDeltaposHeight)
    ON_BN_CLICKED(IDOK, &roidefine::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &roidefine::OnBnClickedCancel)
    ON_WM_CLOSE()
    ON_EN_KILLFOCUS(IDC_OFFSET_X_EDIT, &roidefine::OnEnKillfocusOffsetXEdit)
    ON_EN_KILLFOCUS(IDC_OFFSET_Y_EDIT, &roidefine::OnEnKillfocusOffsetYEdit)
    ON_EN_KILLFOCUS(IDC_WIDTH_EDIT, &roidefine::OnEnKillfocusWidthEdit)
    ON_EN_KILLFOCUS(IDC_HEIGHT_EDIT, &roidefine::OnEnKillfocusHeightEdit)
END_MESSAGE_MAP()


// roidefine ��Ϣ�������



void roidefine::OnDeltaposOffsetX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iData = GetDlgItemInt(IDC_OFFSET_X_EDIT);
	if (pNMUpDown->iDelta == -1)  // �����ֵΪ-1 , ˵�������Spin�����ϼ�ͷ
	{
        iData += m_pDlg->m_cameraPara.incOffset_x;
	}
	else if (pNMUpDown->iDelta == 1)  // �����ֵΪ, ˵�������Spin�����¼�ͷ
	{
        iData -= m_pDlg->m_cameraPara.incOffset_x;
	}
    if(iData > m_pDlg->m_cameraPara.maxOffset_x) {
        iData = m_pDlg->m_cameraPara.maxOffset_x;
    }
    if(iData < m_pDlg->m_cameraPara.minOffset_x) {
        iData = m_pDlg->m_cameraPara.minOffset_x;
    }
    SetDlgItemInt(IDC_OFFSET_X_EDIT, iData);
	*pResult = 0;
    ::PostMessage(GetParent()->m_hWnd, WM_ROICHANGE, (WPARAM)1, iData);
}

void roidefine::OnDeltaposOffsetY(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iData = GetDlgItemInt(IDC_OFFSET_Y_EDIT);
    if(pNMUpDown->iDelta == -1)  // �����ֵΪ-1 , ˵�������Spin�����ϼ�ͷ
    {
        iData += m_pDlg->m_cameraPara.incOffset_y;
    } else if(pNMUpDown->iDelta == 1)  // �����ֵΪ, ˵�������Spin�����¼�ͷ
    {
        iData -= m_pDlg->m_cameraPara.incOffset_y;
    }
    if(iData > m_pDlg->m_cameraPara.maxOffset_y) {
        iData = m_pDlg->m_cameraPara.maxOffset_y;
    }
    if(iData < m_pDlg->m_cameraPara.minOffset_y) {
        iData = m_pDlg->m_cameraPara.minOffset_y;
    }
    SetDlgItemInt(IDC_OFFSET_Y_EDIT, iData);
    *pResult = 0;
    ::PostMessage(GetParent()->m_hWnd, WM_ROICHANGE, (WPARAM)2, iData);
}

void roidefine::OnDeltaposWidth(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iData = GetDlgItemInt(IDC_WIDTH_EDIT);
    if(pNMUpDown->iDelta == -1)  // �����ֵΪ-1 , ˵�������Spin�����ϼ�ͷ
    {
        iData += m_pDlg->m_cameraPara.incWidth;
    } else if(pNMUpDown->iDelta == 1)  // �����ֵΪ, ˵�������Spin�����¼�ͷ
    {
        iData -= m_pDlg->m_cameraPara.incWidth;
    }
    if(iData > m_pDlg->m_cameraPara.maxWidth) {
        iData = m_pDlg->m_cameraPara.maxWidth;
    }
    if(iData < m_pDlg->m_cameraPara.minWidth) {
        iData = m_pDlg->m_cameraPara.minWidth;
    }
    SetDlgItemInt(IDC_WIDTH_EDIT, iData);
    *pResult = 0;
    ::PostMessage(GetParent()->m_hWnd, WM_ROICHANGE, (WPARAM)3, iData);
}

void roidefine::OnDeltaposHeight(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iData = GetDlgItemInt(IDC_HEIGHT_EDIT);
    if(pNMUpDown->iDelta == -1)  // �����ֵΪ-1 , ˵�������Spin�����ϼ�ͷ
    {
        iData += m_pDlg->m_cameraPara.incHeight;
    } else if(pNMUpDown->iDelta == 1)  // �����ֵΪ, ˵�������Spin�����¼�ͷ
    {
        iData -= m_pDlg->m_cameraPara.incHeight;
    }
    if(iData > m_pDlg->m_cameraPara.maxHeight) {
        iData = m_pDlg->m_cameraPara.maxHeight;
    }
    if(iData < m_pDlg->m_cameraPara.minHeight) {
        iData = m_pDlg->m_cameraPara.minHeight;
    }
    SetDlgItemInt(IDC_HEIGHT_EDIT, iData);
    *pResult = 0;
    ::PostMessage(GetParent()->m_hWnd, WM_ROICHANGE, (WPARAM)4, iData);
}


void roidefine::updateROIInfo(CRect& rect)
{
    SetDlgItemInt(IDC_OFFSET_X_EDIT, rect.left);
    SetDlgItemInt(IDC_OFFSET_Y_EDIT, rect.top);
    SetDlgItemInt(IDC_WIDTH_EDIT, rect.Width());
    SetDlgItemInt(IDC_HEIGHT_EDIT, rect.Height());
}


void roidefine::OnBnClickedOk()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    static CRect rect;
    rect.left = GetDlgItemInt(IDC_OFFSET_X_EDIT);
    rect.top = GetDlgItemInt(IDC_OFFSET_Y_EDIT);
    rect.right = rect.left + GetDlgItemInt(IDC_WIDTH_EDIT);
    rect.bottom = rect.top + GetDlgItemInt(IDC_HEIGHT_EDIT);
    ::PostMessage(GetParent()->m_hWnd, WM_CLOSE_ROIDEFINE, (WPARAM)&rect,(LPARAM)IDOK);
    CDialog::OnOK();
}

void roidefine::OnBnClickedCancel()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    ::PostMessage(GetParent()->m_hWnd, WM_CLOSE_ROIDEFINE, (WPARAM)0,(LPARAM)IDCANCEL);
    CDialog::OnCancel();
}


BOOL roidefine::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    updateROIInfo(m_pDlg->m_cameraSetting.rectROI);
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}



void roidefine::OnClose()
{
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
    ::PostMessage(GetParent()->m_hWnd, WM_CLOSE_ROIDEFINE, (WPARAM)this, (LPARAM)0);
    CDialog::OnClose();
}

void roidefine::OnEnKillfocusOffsetXEdit()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void roidefine::OnEnKillfocusOffsetYEdit()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void roidefine::OnEnKillfocusWidthEdit()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void roidefine::OnEnKillfocusHeightEdit()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}
