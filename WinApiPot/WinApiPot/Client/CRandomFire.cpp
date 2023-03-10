#include "pch.h"
#include "CRandomFire.h"

#include "CCollider.h"

#include "CSkillMgr.h"
#include "CSkill.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

#define ATTACK_RANGE 30

CRandomFire::CRandomFire() :
	CSkillState(SKILL_STATE::RANDOM_FIRE),
	m_fAccTime(0.3f),
	m_fCurTime(0.f),
	m_iAttackFrame(-1)
{
	SetSKillName(L"Player_skill_randomfire");

	SetMP(8.f);

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	tAtt.m_fAttackDamage = 10.f;
	tAtt.m_fAttRcnt = 15.f;
	tAtt.m_fAttRigidityTime = 0.3f;
	tAtt.m_fAttUpperRcnt = -40.f;

	SetAttInfo(tAtt);

	//난사 애니메이션
	CreateAnimator();
	CTexture* m_pRadomFireMotion = CResMgr::GetInst()->LoadTextur(L"Radomfire_0", L"..\\OutPut\\bin_release\\Content\\Texture\\randomfire.bmp");
	GetAnimator()->CreateAnimation(L"Radomfire0", m_pRadomFireMotion, Vec2(0.f, 0.f), Vec2(241.f, 247.f), Vec2(241.f, 0.f), Vec2(100.f, 0.f), 0.1f, 6);
}

CRandomFire::~CRandomFire()
{
}

void CRandomFire::Skillupdate()
{
	CPlayer* pPlayer = GetSkill()->GetPlayer();
	Vec2 pPlayerPos = pPlayer->GetPos();
	SetPos(pPlayerPos);

	CAnimator* pAnim = pPlayer->GetAnimator();

	float fFinalPos = m_vCollOffSet.x + m_fOffSet;
	wstring strSkillName = GetSkillName();
	GetCollider()->SetOffSet(Vec2(fFinalPos, m_vCollOffSet.y));

	m_fCurTime += fDT;

	GetAnimator()->Play(L"Radomfire0", false);

	if (((KEY_TAP(KEY::X) || KEY_HOLD(KEY::X))) &&
		m_fCurTime >= m_fAccTime)
	{
		m_fCurTime = 0.f;
		pAnim->FindAnimation(strSkillName)->AddAccTime(0.1f);
	}

	if (pAnim->FindAnimation(strSkillName)->IsFinish())
	{
		pAnim->FindAnimation(strSkillName)->SetFram(0);
		exit();
		return;
	}
}

void CRandomFire::init()
{
	CreateCollider();
	GetCollider()->SetActive(false);

	for (int i = 0; i < ATTACK_RANGE; ++i)
	{
		AddAttackFrame(i);
	}

	m_vCollSize = Vec2(200.f, 150.f);
	m_vCollOffSet = Vec2(-20.f, 30.f);
	GetCollider()->SetScale(m_vCollSize);
	GetCollider()->SetOffSet(m_vCollOffSet);
}

void CRandomFire::exit()
{
	CSkillState::exit();
	m_iAttackFrame = -1;
}

void CRandomFire::OnColliderEnter(CCollider* _pOther)
{
}

void CRandomFire::OnColliderExit(CCollider* _pOther)
{
}

void CRandomFire::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER)
	{
		const vector<UINT> vecFrame = GetAttackFrame();
		vector<UINT>& vecColl = GetOtherCollVec();
		int iCurFrame = GetCurFram();


		for (int i = 0; i < vecFrame.size(); ++i)
		{
			if (vecFrame[i] == iCurFrame && vecColl[_pOther->GetID()] != iCurFrame)
			{
				vecColl[_pOther->GetID()] = iCurFrame;
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
