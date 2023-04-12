#pragma once
#include "CState.h"
class CNaiasTrace :
    public CState
{
public:
	CNaiasTrace();
	virtual ~CNaiasTrace();

public:
	virtual void enter();
	virtual void exit();
	virtual void update();

private:
	bool check_skill();


};

