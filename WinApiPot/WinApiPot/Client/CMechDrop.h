#pragma once
#include "CSkillState.h"
class CMechDrop :
    public CSkillState
{
public:
    CMechDrop();
    virtual ~CMechDrop();

private:
    CTexture* m_pMechTex;

    wstring m_strSkillName;

    bool m_bStart;

    int m_iMoveDir;
    float m_fMoveValue;

    float m_fCreateTime;
    float m_fCurTime;

    UINT m_iCreateCount;

public:
    virtual void render(HDC _dc);

    virtual void Skillupdate();
    virtual void init();
    virtual void exit();
    virtual void enter();

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

private:
    void create_dropmech(Vec2 _vCreatePos);




};

