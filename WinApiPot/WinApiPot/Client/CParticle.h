#pragma once
#include "CObject.h"
class CParticle :
    public CObject
{
public:
    CParticle();
    virtual ~CParticle();

private:
    int m_iDir;

public:
    virtual void render(HDC _dc);
    virtual void update();

    void SetDir(int _iDir);
};

