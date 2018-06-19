#pragma once
#include "dataTypeDefine.h"
#include "afxwin.h"

// CNetSetting 对话框
#define WM_CLOSE_NETSETTING WM_USER+105
class CClientDlg;
class CNetSetting : public CDialog
{
	DECLARE_DYNAMIC(CNetSetting)

public:
	CNetSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNetSetting();

// 对话框数据
	enum { IDD = IDD_NETSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();


public:
    afx_msg void OnBnClickedButtonconnect();
    afx_msg void OnBnClickedOk();
    CClientDlg* m_pParentDlg;
    afx_msg void OnBnClickedButtonsend();
    CListBox m_lsRecv;
private:
    NET_PARA para;
};
