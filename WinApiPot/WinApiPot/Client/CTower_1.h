#pragma once

#include "CScene.h"

class CTower_1 :
    public CScene
{
public:
    CTower_1();
    virtual ~CTower_1();

public:
    virtual void Enter();//현재 씬 들어갈 때 
    virtual void Exit(); //현재 씬 나갈 떄

private:

};

