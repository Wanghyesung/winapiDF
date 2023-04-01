#pragma once
#include "CState.h"
class CStoneState :
    public CState
{
public:
	CStoneState();
	virtual ~CStoneState();


public:
	virtual void enter();
	virtual void exit();
	virtual void update();
};

