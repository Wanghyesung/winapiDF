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

	bool isJump = m_pTarget->GetGravity()->IsGetGravity();//�߷��� �ް��ִ��� ���� �˻� = ����������

	if (isJump)//�������̶��
	{
		vPos = GetMonster()->GetPos();
		vTargetPos = m_pTarget->GetJumPos(); //������ �� ���� ����
	}

	else
	{
		vPos = GetMonster()->GetPos();  //�� ����
		vTargetPos = m_pTarget->GetCollider()->GetFinalPos(); // ��� ����
	}

	vDiff = vTargetPos - vPos;
	vDiff.x > 0 ? SetDir(1) : SetDir(-1);


	//�ٽ� idel��
	if (vDiff.Length() > monInfo.m_fnavigationScope * 1.5f)//2�� �Ÿ���
	{
		m_eNextState = MONSTER_STATE::IDLE;
		ChangeAIState(GetAI(),m_eNextState);
		return;
	}

	//�������󿡼� �� ���ݹ����ȿ� ������ �׶� ����
	

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
