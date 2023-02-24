#include "pch.h"
#include "CExclusiveTrace.h"
#include "CAttackState.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CGravity.h"
#include "CCollider.h"
#include "CRigidBody.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeMgr.h"
#include "AI.h"
#include "CRigidBody.h"

#define ATTACKRANGE 30.f

CExclusiveTrace::CExclusiveTrace():
	CState(MONSTER_STATE::TRACE),
	m_fCurAttackTime(0.f)
{

}

CExclusiveTrace::~CExclusiveTrace()
{

}


void CExclusiveTrace::update()
{
	if (GetMonster()->IsDead())
		return;


	m_pTarget = (CPlayer*)SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();

	m_fCurAttackTime += fDT;

	tMonInfo monInfo = GetMonster()->GetMonInfo();
	tAttackInfo tMonAttackInfo = GetMonster()->GetAttackInfo();

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

	vDiff = (vTargetPos - vPos);//길이값 

	int iDir = 0;//방향값
	vDiff.x > 0 ? iDir = 1 : iDir = -1;
	SetDir(iDir);

	//다시 idel로
	if (vDiff.Length() > monInfo.m_fnavigationScope * 1.5f)//2배 거리로
	{
		m_eNextState = MONSTER_STATE::IDLE;
		m_fCurAttackTime = 0.f;
		ChangeAIState(GetAI(), m_eNextState);
		return; 
	}
	


	if (vDiff.Length() <= tMonAttackInfo.m_fAttackRange.Length())
	{
		//공격 사거리에 들면 플레이어 오브젝트 y축에 맞게 내려감
		if (!isJump)
		{
			vDiff.NormalRize();
			GetMonster()->GetRigidBody()->AddForce(Vec2(0.f, vDiff.y * monInfo.m_fspeed));
		}

		//공격 
		if (tMonAttackInfo.m_fAttackTime <= m_fCurAttackTime && 
			abs(vPos.y - vTargetPos.y) <= ATTACKRANGE)
		{
			m_eNextState = MONSTER_STATE::ATTACK;
			GetAI()->GetState(m_eNextState)->SetDir(iDir);
			m_fCurAttackTime = 0.f;
			ChangeAIState(GetAI(), m_eNextState);
		}
	}
	else
	{
		vDiff.NormalRize();
		GetMonster()->GetRigidBody()->AddForce(vDiff * monInfo.m_fspeed);
	}
	

	
}


void CExclusiveTrace::exit()
{
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
}

void CExclusiveTrace::enter()
{
}
