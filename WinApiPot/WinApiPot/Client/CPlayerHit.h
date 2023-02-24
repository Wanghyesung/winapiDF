#pragma once
#include "CPlayerState.h"
class CPlayerHit :
    public CPlayerState
{
public:
    CPlayerHit();
    virtual ~CPlayerHit();

private:
    bool m_bHit;
    float m_fCurTime;

public:
    virtual void Enter();
    virtual void Exit();
    virtual void update();


public:
    bool IsHit() { return m_bHit; }
private:



};

