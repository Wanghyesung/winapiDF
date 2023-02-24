#include "pch.h"
#include "CIdleState.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "AI.h"
#include "CGravity.h"

CIdleState::CIdleState() :
	CState(MONSTER_STATE::IDLE),
	m_pTarget(nullptr)
{

}

CIdleState::~CIdleState()
{

}

void CIdleState::update()
{	
	//m_fCurTime += fDT;

	//순찰을 함
	//if (m_fCurTime >= 5.f)
	//{
	//	exit();
	//	m_eNextState = MONSTER_STATE::PATROL;
	//	GetAI()->ChangeState(m_eNextState);
	//}

	m_pTarget = (CPlayer*)(SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj());

	bool isJump = m_pTarget->GetGravity()->IsGetGravity();//중력을 받고있는지 먼저 검사 = 점프중인지

	tMonInfo monInfo = GetMonster()->GetMonInfo();

	Vec2 vDiff;
	Vec2 vPos;
	Vec2 vTargetPos;

	if (isJump)//점프중이라면
	{
		vPos = GetMonster()->GetPos();
		vTargetPos = m_pTarget->GetJumPos(); //점프할 떄 착지 지점
	}

	else
	{
		vPos = GetMonster()->GetPos(); //내 지점
		vTargetPos = m_pTarget->GetPos(); // 상대 지점
	}

	vDiff = vTargetPos - vPos;
	vDiff.x >= 0 ? SetDir(1) : SetDir(-1);

	//내 지저과 플레이어 지점의 거리가 지정해준 길이보다 짧아진 경우
	if ((vDiff.NormalRize() * monInfo.m_fnavigationScope).Length() >= (vTargetPos - vPos).Length())
	{
		m_eNextState = MONSTER_STATE::TRACE;
		ChangeAIState(GetAI(), MONSTER_STATE::TRACE);//내 소유주인 AI객체를 넘겨줌 (이거 이벤트 매니저 만들어야함) 전역함수로 설정하고 이벤트 매니저한테 벡터에 넣기
	}
}


void CIdleState::enter()
{

}

void CIdleState::exit()
{
	CState::exit();
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
}
