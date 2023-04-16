#pragma once
#include "CState.h"

class CPlayer;

class CEvileyeTrace :
    public CState
{
public:
	CEvileyeTrace();
	virtual ~CEvileyeTrace();

	CPlayer* m_pTarget;

public:
	virtual void enter();
	virtual void exit();
	virtual void update();

};

