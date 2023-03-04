#pragma once
#include "CState.h"

class CDefenseState : public CState
{
public:
	CDefenseState();
	virtual ~CDefenseState();

public:
	virtual void enter();
	virtual void exit();
	virtual void update();

private:
	float m_fDefDuration;
	float m_fCurTime;
};

