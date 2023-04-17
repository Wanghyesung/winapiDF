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

	float m_fMoveValue;

	float m_fMoveTime;
	float m_fCurTime;

	int m_iMoveDir;

	Vec2 m_vStartPos;

public:
	virtual void enter();
	virtual void exit();
	virtual void update();
};

