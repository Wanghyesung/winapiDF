#include "pch.h"
#include "CEvileyeTrace.h"

#include "CPlayer.h"
#include "CCollider.h"

#include "CMonster.h"
#include "CRigidBody.h"
#include "CGravity.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"

CEvileyeTrace::CEvileyeTrace():
	CState(MONSTER_STATE::TRACE),
	m_pTarget(nullptr)
{

}

CEvileyeTrace::~CEvileyeTrace()
{

}

void CEvileyeTrace::enter()
{
	vector<CObject*> vecPlayer = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::PLAYER);

	if (vecPlayer.size() == 0)
		return;
	else
	{
		m_pTarget = (CPlayer*)vecPlayer[0];
	}
	
}

void CEvileyeTrace::exit()
{
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	CState::exit();
}

void CEvileyeTrace::update()
{
	if (m_pTarget == nullptr)
		return;

	CMonster* pMon = GetMonster();

	Vec2 vPos = pMon->GetCollider()->GetFinalPos();
	Vec2 vTargetPos;
	if (m_pTarget->GetGravity()->IsGetGravity())
	{
		vTargetPos = m_pTarget->GetJumPos();
	}
	else
		vTargetPos = m_pTarget->GetCollider()->GetFinalPos();

	Vec2 vDiff = vTargetPos - vPos;

	int iDir = vDiff.y > 0.f ? 1 : -1;

	if (abs(vDiff.y) < 20.f)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}
	else
	{
		pMon->GetRigidBody()->AddForce(Vec2(0.f, iDir * pMon->GetMonInfo().m_fspeed));
	}
		
}
