#pragma once

#include "CScene.h"

class CTower_1 :
    public CScene
{
public:
    CTower_1();
    virtual ~CTower_1();

public:
    virtual void Enter();//���� �� �� �� 
    virtual void Exit(); //���� �� ���� ��

public:
    virtual void render(HDC _dc);
    virtual void update();

private:

};

