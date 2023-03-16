#include "pch.h"
#include "CLord.h"

#include "AI.h"
#include "CState.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CNearAttack.h"
#include "CStandOffAttack.h"
#include "CHitState.h"
#include "CAttackObject.h"
#include "CThunder.h"
#include "CThunderDown.h"

#include "CBullet.h"
#include "CSkillState.h"
#include "CDeadState.h"

CLord::CLord():
	m_eMonState(MONSTER_STATE::IDLE),
	m_fUltimateTime(20.f),
	m_fUltimateCurTime(0.f)
{
	SetTag(GROUP_TYPE::MONSTER);
	//이름은 몬팩토리에서

	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 90.f));
	GetCollider()->SetOffSet(Vec2(0.f, -20.f));

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);

	CTexture* pRightTex = CResMgr::GetInst()->LoadTextur(L"Lord_right", L"..\\OutPut\\bin_release\\Content\\Texture\\lord_right.bmp");
	CTexture* pLeftTex = CResMgr::GetInst()->LoadTextur(L"Lord_left", L"..\\OutPut\\bin_release\\Content\\Texture\\lord_left.bmp");

	//right
	GetAnimator()->CreateAnimation(L"Lord_Idle_right", pRightTex, Vec2(0.f, 750.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 0.2f, 6);
	GetAnimator()->CreateAnimation(L"Lord_Skill_right", pRightTex, Vec2(0.f, 250.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 0.2f, 7);
	GetAnimator()->FindAnimation(L"Lord_Skill_right")->Create(pRightTex, Vec2(2100.f, 250.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 2.f, 1);
	GetAnimator()->CreateAnimation(L"Lord_Hit_right", pRightTex, Vec2(0.f, 500.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 0.2f, 2);
	GetAnimator()->CreateAnimation(L"Lord_Normal_Attack_right", pRightTex, Vec2(0.f, 0.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 0.1f, 11);
	GetAnimator()->CreateAnimation(L"Lord_ultimate_right", pRightTex, Vec2(0.f, 1000.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 0.2f, 7);
	GetAnimator()->FindAnimation(L"Lord_ultimate_right")->Create(pRightTex, Vec2(0.f, 2100.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(20.f, 0.f), 5.f, 1);
	//스킬 마지막 공격은 druation 길게

	//left
	GetAnimator()->CreateAnimation(L"Lord_Idle_left", pLeftTex, Vec2(3000.f, 750.f), Vec2(300.f, 250.f), Vec2(-300.f, 0.f), Vec2(-20.f, 0.f), 0.2f, 6);
	GetAnimator()->CreateAnimation(L"Lord_Skill_left", pLeftTex, Vec2(3000.f, 250.f), Vec2(300.f, 250.f), Vec2(-300.f, 0.f), Vec2(-20.f, 0.f), 0.2f, 7);
	GetAnimator()->FindAnimation(L"Lord_Skill_left")->Create(pLeftTex, Vec2(900.f, 250.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(-20.f, 0.f), 2.f, 1);
	GetAnimator()->CreateAnimation(L"Lord_Hit_left", pLeftTex, Vec2(3000.f, 500.f), Vec2(300.f, 250.f), Vec2(-300.f, 0.f), Vec2(-20.f, 0.f), 0.2f, 2);
	GetAnimator()->CreateAnimation(L"Lord_Normal_Attack_left", pLeftTex, Vec2(3000.f, 0.f), Vec2(300.f, 250.f), Vec2(-300.f, 0.f), Vec2(-20.f, 0.f), 0.1f, 11);
	GetAnimator()->CreateAnimation(L"Lord_ultimate_left", pLeftTex, Vec2(3000.f, 1000.f), Vec2(300.f, 250.f), Vec2(-300.f, 0.f), Vec2(-20.f, 0.f), 0.2f, 7);
	GetAnimator()->FindAnimation(L"Lord_ultimate_left")->Create(pLeftTex, Vec2(900.f, 1000.f), Vec2(300.f, 250.f), Vec2(300.f, 0.f), Vec2(-20.f, 0.f), 5.f, 1);
}

CLord::~CLord()
{

}

void CLord::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	tMonInfo& m_tInfo = GetMonInfo();
	
	float fDamage = _tAtt.m_fAttackDamage;
	m_tInfo.m_iHp -= (fDamage / 5.f);
	//CMonster::hit(_pOther, _tAtt);
}



void CLord::update()
{
	if (IsDead())
	{
		DeleteObject(this);
		return;
	}
	AI* pAI = GetAI();
	MONSTER_STATE eMonState = pAI->GetCurState()->GetType();

	if (pAI != nullptr)
	{
		pAI->update();
	}
	if (m_fUltimateCurTime >= m_fUltimateTime && eMonState == MONSTER_STATE::TRACE)
	{
		m_fUltimateCurTime = 0.f;
		eMonState = MONSTER_STATE::ULTIMATE;
		ChangeAIState(pAI, eMonState);
	}
	else if (eMonState != MONSTER_STATE::ULTIMATE)
	{
		//일반 스킬 쿨타임
		CMonster::update();
		m_fUltimateCurTime += fDT;
	}


	CAttackObject* pMonSkill = GetSKillObj();
	if (pMonSkill->GetCollider()->IsActive())
	{
		pMonSkill->Skill_update();
	}

	update_state();
}

void CLord::update_state()
{
	CState* pState = GetAI()->GetCurState();
	m_eMonState = pState->GetType();

	CAnimator* pAnim = GetAnimator();

	int iDir = pState->GetDir();
	wstring sDir;
	if (iDir >= 0)
		sDir = L"_right";
	else
		sDir = L"_left";

	wstring strMotion;

	switch (m_eMonState)
	{
	case MONSTER_STATE::IDLE:
	{
		strMotion = L"Lord_Idle" + sDir;
		pAnim->Play(strMotion,true);
	}
		break;
	case MONSTER_STATE::TRACE:
	{
		strMotion = L"Lord_Idle";
		strMotion += sDir;
		pAnim->Play(strMotion, true);
	}
		break;
	case MONSTER_STATE::ATTACK:
	{
		strMotion = ((CNearAttack*)pState)->GetAttackName();
		strMotion = L"Lord" + strMotion + sDir;
		pAnim->Play(strMotion, false);
	}
		break;
	//원거리 공격
	case MONSTER_STATE::ATTACK_STAND:
	{
		strMotion = ((CStandOffAttack*)pState)->GetAttackName();
		strMotion = L"Lord" + strMotion + sDir;
		pAnim->Play(strMotion, false);
	}
		break;
	case MONSTER_STATE::ULTIMATE:
	{
		strMotion = L"Lord_ultimate" + sDir;
		pAnim->Play(strMotion, false);
	}
	break;

	case MONSTER_STATE::DEAD:
	{
		strMotion = L"Lord_Hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		SetActiv(false);//비활성화 (공격 관통하게)
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CDeadState*)GetAI()->GetState(MONSTER_STATE::DEAD))->SetAnimFrame(iFrame);
	}
		break;
	}
}

void CLord::render(HDC _dc)
{

	component_render(_dc);
}

CThunder* CLord::CreateThunder()
{
	CThunder* pThunder = nullptr;
	const vector<tMonSkill>& vecSkill = GetVecSkill();
	for (int i = 0; i < vecSkill.size(); ++i)
	{
		if (vecSkill[i].m_strAttackName == L"_Skill")
		{
			pThunder = new CThunder;
			pThunder->m_pOwner = this;
			pThunder->SetAttackInfo(vecSkill[i].m_MonAttackInfo);
		}
	}

	return pThunder;
}

CThunderDown* CLord::CreateThunderDown()
{
	//여기에 공격력 저장
	CThunderDown* pThunderDown = new CThunderDown;
	pThunderDown->m_pOwner = this;

	tAttackInfo m_tAtt = {};
	m_tAtt.m_eAttType = ATTACK_TYPE::UPPER;
	m_tAtt.m_fAttRcnt = 100.f;
	m_tAtt.m_fAttackDamage = 100.f;
	m_tAtt.m_fAttRigidityTime = 0.5f;
	m_tAtt.m_fAttUpperRcnt = -70.f;

	pThunderDown->SetAttackInfo(m_tAtt);

	return pThunderDown;
}

void CLord::OnColliderEnter(CCollider* _pOther)
{
	tMonInfo& tMonInfo = GetMonInfo();
	CObject* pobj = _pOther->GetObj();

	if (pobj->GetTag() == GROUP_TYPE::SKILL
		&& tMonInfo.m_iHp > 0)
	{
		if (dynamic_cast<CBullet*>(pobj))
		{
			CBullet* pBullet = dynamic_cast<CBullet*>(pobj);
			hit(pBullet->GetCollider(), pBullet->GetAttInfo());
		}
	}

	if (tMonInfo.m_iHp <= 0.f)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
	}
}

void CLord::OnColliderExit(CCollider* _pOther)
{

}

void CLord::OnCollision(CCollider* _pOther)
{
	tMonInfo& tMonInfo = GetMonInfo();
	CObject* pobj = _pOther->GetObj();

	if (pobj->GetTag() == GROUP_TYPE::SKILL
		&& tMonInfo.m_iHp > 0)
	{
		if (dynamic_cast<CSkillState*>(pobj))
		{
			CSkillState* pSkill = dynamic_cast<CSkillState*>(pobj);

			if (!pSkill->IsAttackOn())
				return;

			hit(pSkill->GetCollider(), pSkill->GetAttInfo());
		}

		if (tMonInfo.m_iHp == 0)
		{
			ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
		}
	}
}
