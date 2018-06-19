#pragma once
#include "stdafx.h"

struct CAMERA_PARA
{
    int maxOffset_x;
    int minOffset_x;
    int incOffset_x;
    int maxOffset_y;
    int minOffset_y;
    int incOffset_y;
    int maxWidth;
    int minWidth;
    int incWidth;
    int maxHeight;
    int minHeight;
    int incHeight;
};

struct CAMERA_SETTING
{
    int camStatus;
    CRect rectROI;
};

struct NET_PARA
{
    CString strLocalIP;
    USHORT sLocalPort;
    CString strRemoteIP;
    USHORT sRemotePort;
};