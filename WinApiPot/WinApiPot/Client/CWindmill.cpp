#include "pch.h"
#include "CWindmill.h"


#include "CAnimation.h"


#include "CCollider.h"

#include "CTimeMgr.h"
#include "CSkillMgr.h"

#include "CSkill.h"
#include "CPlayer.h"
#include "CObject.h"

#define FIRST_ATTACK 0
#define SECOND_ATTACK 3

CWindmill::CWindmill() :
	CSkillState(SKILL_STATE::WINDMILL),
	m_iAttackFrame(-1)
{
	//�� ��ų �̸� ���ϱ�
	SetSKillName(L"Player_skill_windmill");

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	tAtt.m_fAttackDamage = 20.f;
	tAtt.m_fAttRcnt = 30.f;
	tAtt.m_fAttRigidityTime = 0.8f;
	tAtt.m_fAttUpperRcnt = -30.f;

	SetAttInfo(tAtt);
}

CWindmill::~CWindmill()
{
}

void CWindmill::Skillupdate()
{

	CPlayer* pPlayer = GetSkill()->GetPlayer();
	Vec2 pPlayerPos = pPlayer->GetPos();
	SetPos(pPlayerPos);

	CAnimator* pAnim = pPlayer->GetAnimator();
	wstring strSkillName = GetSkillName();


	if (pAnim->FindAnimation(strSkillName)->IsFinish())
	{
		pAnim->FindAnimation(strSkillName)->SetFram(0);
		exit();
		return;
	}

}


void CWindmill::init()
{
	CreateCollider();
	GetCollider()->SetActive(false);

	AddAttackFrame(FIRST_ATTACK);
	AddAttackFrame(SECOND_ATTACK);

	m_vCollSize = Vec2(100.f, 50.f);
	m_vCollOffSet = Vec2(-20.f, 75.f);
	GetCollider()->SetScale(m_vCollSize);
	GetCollider()->SetOffSet(m_vCollOffSet);
}

void CWindmill::exit()
{
	CSkillState::exit();
	m_iAttackFrame = -1;
}

void CWindmill::OnColliderEnter(CCollider* _pOther)
{

}

void CWindmill::OnColliderExit(CCollider* _pOther)
{

}

void CWindmill::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER)
	{
		const vector<UINT> vecFrame = GetAttackFrame();
		int iCurFrame = GetCurFram();

		for (int i = 0; i < vecFrame.size(); ++i)
		{
			if (vecFrame[i] == iCurFrame && m_iAttackFrame != i)
			{
				m_iAttackFrame = i;
				SetAttackOn(TRUE);
				break;
			}
			else
			{
				SetAttackOn(FALSE);
			}
		}
	}
}
