#include "pch.h"
#include "CKick.h"

#include "CSkill.h"
#include "CSkillMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CSound.h"

#define FIRST_ATTACK 1

CKick::CKick() :
	CSkillState(SKILL_STATE::UPPER_KICK),
	m_fOffSet(30.f),
	m_iAttackFrame(-1)
{
	SetSKillName(L"Player_skill_kick_");

	SetMP(3.f);

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::UPPER;
	tAtt.m_fAttackDamage = 40.f;
	tAtt.m_fAttRcnt = 40.f;
	tAtt.m_fAttRigidityTime = 1.3f;
	tAtt.m_fAttUpperRcnt = -400.f;
	tAtt.m_fAttUpperAcc = -600.f;

	SetAttInfo(tAtt);

	SetSkillTime(4);

	//스킬 사운드
	SetAnimSound(L"gn_kick");
}

CKick::~CKick()
{

}

void CKick::Skillupdate()
{

	////방향 잡기 + 방향에 따라 충돌체 offset 바꾸기
	CPlayer* pPlayer = GetSkill()->GetPlayer();
	Vec2 pPlayerPos = pPlayer->GetPos();
	SetPos(pPlayerPos);

	CAnimator* pAnim = pPlayer->GetAnimator();
	int iDir = pPlayer->GetPlayerDirX();

	float fFinalPos = m_vCollOffSet.x + iDir * m_fOffSet;
	wstring strSkillName = GetSkillName();

	if (iDir > 0)
	{
		GetCollider()->SetOffSet(Vec2(fFinalPos, m_vCollOffSet.y));
		m_strSkillName = strSkillName + L"right";
	}
	else
	{
		GetCollider()->SetOffSet(Vec2(fFinalPos, m_vCollOffSet.y));
		m_strSkillName = strSkillName + L"left";
	}



	if (pAnim->FindAnimation(m_strSkillName)->IsFinish())
	{
		exit();
		return;
	}

}



void CKick::init()
{
	CreateCollider();
	GetCollider()->SetActive(false);

	AddAttackFrame(FIRST_ATTACK);

	m_vCollSize = Vec2(60.f, 70.f);
	m_vCollOffSet = Vec2(-20.f, 70.f);
	GetCollider()->SetScale(m_vCollSize);
	GetCollider()->SetOffSet(m_vCollOffSet);
}

void CKick::exit()
{
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(0);
	CSkillState::exit();
	m_iAttackFrame = -1;
}

void CKick::enter()
{
	CSkillState::enter();
}

void CKick::OnColliderEnter(CCollider* _pOther)
{

}

void CKick::OnColliderExit(CCollider* _pOther)
{

}

void CKick::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER ||
		_pOther->GetObj()->GetTag() == GROUP_TYPE::STONE_BOX)
	{
		const vector<UINT>& vecFrame = GetAttackFrame();
		vector<UINT>& vecColl = GetOtherCollVec();

		//int a = sizeof(vecColl);

		int iCurFrame = GetCurFram();

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
