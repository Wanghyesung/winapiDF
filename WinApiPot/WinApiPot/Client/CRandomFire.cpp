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
#include "CMath.h"

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
	tAtt.m_fAttackDamage = 3.f;
	tAtt.m_fAttRcnt = 15.f;
	tAtt.m_fAttRigidityTime = 0.3f;
	tAtt.m_fAttUpperRcnt = -40.f;

	SetAttInfo(tAtt);

	//난사 애니메이션
	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);
	CTexture* m_pRadomFireMotion = CResMgr::GetInst()->LoadTextur(L"Radomfire_0", L"..\\OutPut\\bin_release\\Content\\Texture\\randomfire1.bmp");
	GetAnimator()->CreateAnimation(L"Radomfire0", m_pRadomFireMotion, Vec2(0.f, 0.f), Vec2(273.f, 261.f), Vec2(273.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	//회전시켜서 offset값 바꾸기
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

	//GetAnimator()->FindAnimation(L"Radomfire0")->
	//Vec2 v90 =  Rotate(GetPos(),1) * 200.f;

	GetAnimator()->Play(L"Radomfire0",true);
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
	GetAnimator()->SetRepeat(false);
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
	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER ||
		_pOther->GetObj()->GetTag() == GROUP_TYPE::STONE_BOX)
	{
		const vector<UINT> vecFrame = GetAttackFrame();
		vector<UINT>& vecColl = GetOtherCollVec();
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
