#pragma once
#include "CState.h"

class CPlayer;

class CIdleState :
    public CState
{
public:
    CIdleState();
    virtual ~CIdleState();

private:
    float m_fNavigationScope; //ã�� �Ÿ�
    float m_fTtime;//���� �ð��� ������ Ž�� 
    float m_fCurTime;//���� �ð�
    CPlayer* m_pTarget;//Ÿ��

    MONSTER_STATE m_eNextState;

public:
    virtual void update();
    virtual void enter();
    virtual void exit();

    void SetNavigationScope(float _f) { m_fNavigationScope = _f; }

};

