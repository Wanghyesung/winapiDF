#pragma once
#include "CState.h"
class CArdorTrace :
    public CState
{
public:
	CArdorTrace();
	virtual ~CArdorTrace();

public:
	virtual void enter();
	virtual void exit();
	virtual void update();

private:
	bool check_skill();

};

