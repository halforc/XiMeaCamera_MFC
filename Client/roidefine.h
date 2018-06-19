#pragma once

#define WM_CLOSE_ROIDEFINE WM_USER+103
#define  WM_ROIRECT_CHANGED WM_USER + 104
// roidefine 对话框

class CClientDlg;
class roidefine : public CDialog
{
	DECLARE_DYNAMIC(roidefine)

public:
	roidefine(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~roidefine();

// 对话框数据
	enum { IDD = IDD_ROIDEFINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposOffsetX(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeltaposOffsetY(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeltaposWidth(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeltaposHeight(NMHDR *pNMHDR, LRESULT *pResult);

	CSpinButtonCtrl m_offset_x;
	CSpinButtonCtrl m_offset_y;
	CSpinButtonCtrl m_width;
	CSpinButtonCtrl m_height;

    CClientDlg* m_pDlg;
    void updateROIInfo(CRect& rect);
    afx_msg void OnBnClickedOk();

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnClose();
    afx_msg void OnEnKillfocusOffsetXEdit();
    afx_msg void OnEnKillfocusOffsetYEdit();
    afx_msg void OnEnKillfocusWidthEdit();
    afx_msg void OnEnKillfocusHeightEdit();
};
