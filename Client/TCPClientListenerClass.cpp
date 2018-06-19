#include "stdafx.h"
#include"TCPClientListenerClass.h"
#include "ClientDlg.h"

EnHandleResult TCPClientListenerClass::OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult TCPClientListenerClass::OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
    if(m_pDlg->cameraCtrl->m_pNetSettingDlg != nullptr) {
        CString str(pData);
        m_pDlg->cameraCtrl->m_pNetSettingDlg->m_lsRecv.AddString(str);
        m_pDlg->cameraCtrl->m_pNetSettingDlg->UpdateData(TRUE);
    }    

//    CString str2 = "recv ack" + str;
 //   pSender->Send((BYTE*)str2.GetBuffer(str2.GetLength()), str2.GetLength());

    //BYTE * rb = new BYTE[iLength + 1];
    //memcpy(rb, pData, iLength);
    //rb[iLength] = 0x00;
    //printf("Receive from NO%d:%s\n", dwConnID, rb);
    //delete rb;
	return HR_OK;
}

EnHandleResult TCPClientListenerClass::OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	return HR_OK;
}

EnHandleResult TCPClientListenerClass::OnShutdown(ITcpClient* pSender)
{
	return HR_OK;
}