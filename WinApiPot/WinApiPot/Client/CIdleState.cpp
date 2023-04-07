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

	vector<CObject*> vecPlayer = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::PLAYER);

	if (vecPlayer.size() == 0)
		return;
	else
	{
		m_pTarget = (CPlayer*)vecPlayer[0];
	}

	bool isJump = m_pTarget->GetGravity()->IsGetGravity();//�߷��� �ް��ִ��� ���� �˻� = ����������

	tMonInfo monInfo = GetMonster()->GetMonInfo();

	Vec2 vDiff;
	Vec2 vPos;
	Vec2 vTargetPos;

	if (isJump)//�������̶��
	{
		vPos = GetMonster()->GetPos();
		vTargetPos = m_pTarget->GetJumPos(); //������ �� ���� ����
	}

	else
	{
		vPos = GetMonster()->GetPos(); //�� ����
		vTargetPos = m_pTarget->GetPos(); // ��� ����
	}

	vDiff = vTargetPos - vPos;
	vDiff.x >= 0 ? SetDir(1) : SetDir(-1);

	//�� ������ �÷��̾� ������ �Ÿ��� �������� ���̺��� ª���� ���
	if ((vDiff.NormalRize() * monInfo.m_fnavigationScope).Length() >= (vTargetPos - vPos).Length())
	{
		m_eNextState = MONSTER_STATE::TRACE;
		ChangeAIState(GetAI(), MONSTER_STATE::TRACE);//�� �������� AI��ü�� �Ѱ��� (�̰� �̺�Ʈ �Ŵ��� ��������) �����Լ��� �����ϰ� �̺�Ʈ �Ŵ������� ���Ϳ� �ֱ�
	}
}


void CIdleState::enter()
{

}

void CIdleState::exit()
{
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	CState::exit();
}
