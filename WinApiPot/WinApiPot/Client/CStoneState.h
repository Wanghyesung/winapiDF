#pragma once
#include "CState.h"
class CStoneState :
    public CState
{
public:
	CStoneState();
	virtual ~CStoneState();

private:
	bool m_bStart;

public:
	virtual void enter();
	virtual void exit();
	virtual void update();
};

