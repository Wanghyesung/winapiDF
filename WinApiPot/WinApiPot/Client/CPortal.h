#pragma once
#include "CObject.h"
class CPortal :
    public CObject
{

public:
    CPortal();
    virtual ~CPortal();

private:
    //¿Ãµø 
    SCENE_TYPE m_eNextScene;

public:
    virtual void update();
    

    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

public:
    void SetNextScene(SCENE_TYPE _eNext) { m_eNextScene = _eNext; }
    SCENE_TYPE GetNextScene() { return m_eNextScene; }
};

