#include "pch.h"
#include "CMonster.h"

#include "AI.h"

#include "CCameraMgr.h"
#include "CCollider.h";

#include "CGravity.h"

#include "CRigidBody.h"

#include "CTimeMgr.h"

CMonster::CMonster() :
	m_tMonInfo{},
	m_bHit(false),
	m_bActiv(true)
	//m_fHitTime(0.5f),
	//m_fHitCurTime(0.f)
{
	//CreateCollider();
	//GetCollider()->SetScale(Vec2(40.f, 40.f));
	//
	//CreateGravity();
}

CMonster::~CMonster()
{
	if (m_AI != nullptr)
	{
		delete m_AI;
	}
}


void CMonster::update()
{

	if (m_bHit)
		return;
	
	if (m_AI != nullptr)
	{
		m_AI->update();
	}
}

void CMonster::render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();
	//
	//vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);
	//
	//Rectangle(_dc,
	//	(int)(vPos.x - vScale.x/ 2.f),
	//	(int)(vPos.y - vScale.y / 2.f),
	//	(int)(vPos.x + vScale.x / 2.f),
	//	(int)(vPos.y + vScale.y / 2.f));

	component_render(_dc);
}

void CMonster::SetAI(AI* _AI)
{
	m_AI = _AI;
	m_AI->m_pOwner = this;
}



void CMonster::OnColliderEnter(CCollider* _pOther)
{
	
}

void CMonster::OnColliderExit(CCollider* _pOther)
{
	
}

void CMonster::OnCollision(CCollider* _pOther)
{

}


