#include "pch.h"
#include "CPortal.h"

#include "CObject.h"
#include "CCollider.h"

#include "CEventMgr.h"
#include "CGravity.h"


CPortal::CPortal()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(80.f, 50.f));

	SetName(L"WC");
}

CPortal::~CPortal()
{

}


void CPortal::update()
{
	
}

void CPortal::OnColliderEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if (pObj->GetName() == L"Player")
	{
		if (pObj->GetGravity()->IsGetGravity())
			return;

		//ChangeScene();

		//tEvent eve = {};
		//eve.eEventType = EVENT_TYPE::SCENE_CHANGE;
		//eve.lParm = (DWORD_PTR)m_eNextScene;
		//
		//CEventMgr::GetInst()->AddEvent(eve);
	}
}

void CPortal::OnColliderExit(CCollider* _pOther)
{

}

void CPortal::OnCollision(CCollider* _pOther)
{
	
}
