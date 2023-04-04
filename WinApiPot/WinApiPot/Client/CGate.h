#pragma once
#include "CObject.h"
class CGate :
    public CObject
{
public:
    CGate(const wstring& _strDir, bool _bIsBoss);
    virtual ~CGate();

private:
    //�̵� 
    SCENE_TYPE m_eNextScene;
    wstring m_strDir;
    wstring m_strBoss;

    CTexture* CTex;
    CTexture* CTexDoor;
    CTexture* CUpStairs;

    //��Ȱ��ȭ�Ǹ� ������ X
    bool m_bActive;

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

public:
    void SetNextScene(SCENE_TYPE _eNext) { m_eNextScene = _eNext; }
    SCENE_TYPE GetNextScene() { return m_eNextScene; }


};

