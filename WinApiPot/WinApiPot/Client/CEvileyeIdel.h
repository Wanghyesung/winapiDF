#pragma once
#include "CState.h"
class CEvileyeIdel :
    public CState
{
public:
	CEvileyeIdel();
	virtual ~CEvileyeIdel();

private:
	CPlayer* m_pTarget;

private:
	void check_skill();

public:
	virtual void enter();
	virtual void exit();
	virtual void update();
};

