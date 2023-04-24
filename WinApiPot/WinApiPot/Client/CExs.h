#pragma once
#include "CSkillState.h"
class CExs :
    public CSkillState
{
public:
    CExs();
    virtual ~CExs();

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
    void createExs();
};

