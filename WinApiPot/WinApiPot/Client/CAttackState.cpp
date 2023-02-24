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
	m_iAttCount(0)
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
	if (m_pMon->IsDead())
	{
		return;
	}

	//if (m_pMon->IsHit())
	//{ 
	//	m_iAttCount = 0;
	//	ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	//	m_pMon->GetAnimator()->GetCurAnimation()->SetFram(0);
	//	return;
	//}
	
	//프레임 2번 나가나보네
	int iCurFrame = m_pMon->GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iCurFrame == -1)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
		return;
	}

	for (int i = 0; i < m_vAttackFrame.size(); ++i)
	{
		if (iCurFrame == m_vAttackFrame[i] && m_iAttCount<1)
		{
			++m_iAttCount;
			int iDir = GetDir();
			CFireBall* fireBall = new CFireBall(iDir, m_pMon->GetPos());
			CreateObject(fireBall,GROUP_TYPE::FIREBALL);
			//여기서 불덩이 생성
		}
	}

}

