#include "pch.h"
#include "CAttackState.h"

#include "CMonster.h"
#include "CObject.h"
#include "CPlayer.h"

#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CEventMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CFireBall.h"

CAttackState::CAttackState():
	CState(MONSTER_STATE::ATTACK),
	m_iAttCount(0),
	m_iAttackFrame(0)
{

}

CAttackState::~CAttackState()
{

}

void CAttackState::enter()
{
	
}

void CAttackState::exit()
{
	CState::exit();
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	m_iAttCount = 0;
}

void CAttackState::update()
{

	CMonster* m_pMon = GetMonster();
	vector<tMonSkill>& vecSkill = m_pMon->GetVecSkill();
	if (m_pMon->IsDead())
	{
		return;
	}
	
	int iCurFrame = m_pMon->GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iCurFrame == -1)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
		return;
	}


	if (iCurFrame == m_iAttackFrame && m_iAttCount < 1)
	{
		++m_iAttCount;
		int iDir = GetDir();
		CFireBall* fireBall = new CFireBall(iDir, m_pMon->GetPos());
		const vector<tMonSkill>& vecSkill = GetMonster()->GetVecSkill();
		fireBall->SetAttackInfo(vecSkill[0].m_MonAttackInfo);
		CreateObject(fireBall,GROUP_TYPE::MONSTER_SKILL);
		//여기서 불덩이 생성
	}


}

