#pragma once
#include "CSkillState.h"
class CRx78 :
    public CSkillState
{
public:
    CRx78();
    virtual ~CRx78();

private:
    float m_fCreateTime;
    float m_fCurTime;

    wstring m_strSkillName;

public:
    virtual void Skillupdate();
    virtual void init();
    virtual void exit();
    virtual void enter();

private:
    void createRx78();
};

