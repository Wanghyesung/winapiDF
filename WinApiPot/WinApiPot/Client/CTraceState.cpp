#include "pch.h"
#include "CTraceState.h"
#include "CAttackState.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CRigidBody.h"
#include "AI.h"
#include "CGravity.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CCollider.h"


CTraceState::CTraceState():
	CState(MONSTER_STATE::TRACE)
{

}

CTraceState::~CTraceState()
{

}

void CTraceState::update()
{
	if (GetMonster()->IsDead())
		return;


	m_pTarget = (CPlayer*)SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();


	tMonInfo& monInfo = GetMonster()->GetMonInfo();
	tAttackInfo attackInfo = GetMonster()->GetAttackInfo();

	Vec2 vDiff;
	Vec2 vPos;
	Vec2 vTargetPos;

	bool isJump = m_pTarget->GetGravity()->IsGetGravity();//중력을 받고있는지 먼저 검사 = 점프중인지

	if (isJump)//점프중이라면
	{
		vPos = GetMonster()->GetPos();
		vTargetPos = m_pTarget->GetJumPos(); //점프할 떄 착지 지점
	}

	else
	{
		vPos = GetMonster()->GetPos();  //내 지점
		vTargetPos = m_pTarget->GetCollider()->GetFinalPos(); // 상대 지점
	}

	vDiff = vTargetPos - vPos;
	vDiff.x > 0 ? SetDir(1) : SetDir(-1);


	//다시 idel로
	if (vDiff.Length() > monInfo.m_fnavigationScope * 1.5f)//2배 거리로
	{
		m_eNextState = MONSTER_STATE::IDLE;
		ChangeAIState(GetAI(),m_eNextState);
		return;
	}

	//일직선상에서 내 공격범위안에 들어오면 그때 공격
	

	if (vDiff.IsZero())
		vDiff = Vec2(0.f, 0.f);
	else
		vDiff = vDiff.NormalRize() * monInfo.m_fspeed;

	GetMonster()->GetRigidBody()->AddForce(vDiff);

}

void CTraceState::exit()
{
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	CState::exit();
}

void CTraceState::enter()
{

}
