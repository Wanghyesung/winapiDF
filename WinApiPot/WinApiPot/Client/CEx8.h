#pragma once
#include "CSkillState.h"
class CEx8 :
    public CSkillState
{
public:
    CEx8();
    virtual ~CEx8();

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
    void createEx8();
};

