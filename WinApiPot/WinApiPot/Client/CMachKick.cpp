#include "pch.h"
#include "CMachKick.h"

#include "CCollider.h"

#include "CSkillMgr.h"
#include "CSkill.h"
#include "CPlayer.h"

#include "CAnimator.h"
#include "CAnimation.h"

#define FIRST_ATTACK 2

CMachKick::CMachKick() :
	CSkillState(SKILL_STATE::MACH_KICK),
	m_fOffSet(30.f),
	m_iAttackFrame(-1)
{
	SetSKillName(L"Player_skill_mach_kick_");

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	tAtt.m_fAttackDamage = 40.f;
	tAtt.m_fAttRcnt = 200.f;
	tAtt.m_fAttRigidityTime = 1.3f;
	tAtt.m_fAttUpperRcnt = -30.f;

	SetAttInfo(tAtt);
}

CMachKick::~CMachKick()
{
}

void CMachKick::Skillupdate()
{

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
		strSkillName += L"right";
	}
	else
	{
		GetCollider()->SetOffSet(Vec2(fFinalPos, m_vCollOffSet.y));
		strSkillName += L"left";
	}


	if (pAnim->FindAnimation(strSkillName)->IsFinish())
	{
		pAnim->FindAnimation(strSkillName)->SetFram(0);
		exit();
		return;
	}

}

void CMachKick::init()
{

	CreateCollider();
	GetCollider()->SetActive(false);

	AddAttackFrame(FIRST_ATTACK);

	m_vCollSize = Vec2(100.f, 40.f);
	m_vCollOffSet = Vec2(-20.f, 70.f);
	GetCollider()->SetScale(m_vCollSize);
	GetCollider()->SetOffSet(m_vCollOffSet);
}

void CMachKick::exit()
{
	CSkillState::exit();
	m_iAttackFrame = -1;
}

void CMachKick::OnColliderEnter(CCollider* _pOther)
{
}

void CMachKick::OnColliderExit(CCollider* _pOther)
{
}

void CMachKick::OnCollision(CCollider* _pOther)
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
