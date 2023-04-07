#pragma once
#include "CState.h"
class CHitUpper :
    public CState
{
private:
	int m_iHitAnimFrame;
	float m_fCurTime;

	float m_fDownTime;

	wstring m_strMotionName;
public:
	CHitUpper();
	virtual ~CHitUpper();

public:
	void SetAnimFrame(int _iCurFrame) { m_iHitAnimFrame = _iCurFrame; }

	void SetAnimName(const wstring& _strName) { m_strMotionName = _strName; }
public:
	virtual void enter(); 
	virtual void exit(); 
	virtual void update();

};

