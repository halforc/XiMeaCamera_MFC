#pragma once
#include"HPSocket.h"
#include"SocketInterface.h"
#include"HPTypeDef.h"

class CClientDlg;
class TCPClientListenerClass :public CTcpClientListener
{
public:
	virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual EnHandleResult OnShutdown(ITcpClient* pSender);
    CClientDlg* m_pDlg;
private:

};
