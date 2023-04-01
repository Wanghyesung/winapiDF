#pragma once
#include "CState.h"


class CKnightTrace :
    public CState
{
public:
	CKnightTrace();
	virtual ~CKnightTrace();

public:
	virtual void enter();
	virtual void exit();
	virtual void update();

private:
	bool check_skill();

};


