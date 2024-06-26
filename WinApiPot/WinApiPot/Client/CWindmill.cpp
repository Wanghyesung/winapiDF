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
	//내 스킬 이름 정하기
	SetSKillName(L"Player_skill_windmill");

	SetMP(4.f);

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	tAtt.m_fAttackDamage = 20.f;
	tAtt.m_fAttRcnt = 30.f;
	tAtt.m_fAttRigidityTime = 0.8f;
	tAtt.m_fAttUpperRcnt = -30.f;

	SetAttInfo(tAtt);

	SetSkillTime(5);

	SetAnimSound(L"gn_windmill");
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
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(GetSkillName())->SetFram(0);
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
	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER ||
		_pOther->GetObj()->GetTag() == GROUP_TYPE::STONE_BOX)
	{
		const vector<UINT> vecFrame = GetAttackFrame();

		int iCurFrame = GetCurFram();
		vector<UINT>& vecColl = GetOtherCollVec();
		for (int i = 0; i < vecFrame.size(); ++i)
		{
			if (vecFrame[i] == iCurFrame && vecColl[_pOther->GetID()] != iCurFrame)
			{
				vecColl[_pOther->GetID()] = iCurFrame;
				SetAttackOn(true);
				break;
			}
			else
			{
				SetAttackOn(false);
			}
		}
	}
}
