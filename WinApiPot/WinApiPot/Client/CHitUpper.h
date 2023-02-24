#pragma once
#include "CState.h"
class CHitUpper :
    public CState
{
private:
	int m_iHitAnimFrame;
	float m_fCurTime;

	float m_fDownTime;

public:
	CHitUpper();
	virtual ~CHitUpper();

public:
	void SetAnimFrame(int _iCurFrame) { m_iHitAnimFrame = _iCurFrame; }

public:
	virtual void enter(); 
	virtual void exit(); 
	virtual void update();

};

