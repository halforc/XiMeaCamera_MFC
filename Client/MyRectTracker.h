#pragma once
#include "afxext.h"
class CMyRectTracker :
    public CRectTracker
{
public:
    CMyRectTracker();
    ~CMyRectTracker();

    void Draw(CDC * pDC, CPen * pen);
};

