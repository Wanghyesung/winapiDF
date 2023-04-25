#include "pch.h"
#include "CKnight.h"

#include "CResMgr.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CState.h"
#include "AI.h"

#include "CTimeMgr.h"

#include "CObject.h"
#include "CSkillState.h"
#include "CBullet.h"
#include "CBoom.h"
#include "CDropRobot.h"
#include "CExsFire.h"

#include "CCollider.h"

#include "CKnightAttack.h"

#include "CHitState.h"
#include "CHitUpper.h"
#include "CDeadState.h"
#include "CGravity.h"

#include "CAttackObject.h"

CKnight::CKnight():
	m_strTexName(L"Knight"),//기본 이미지
	m_vTexScale(Vec2(0.f,0.f)),
	m_vTexOffset(Vec2(0.f,0.f))
{	
}

CKnight::~CKnight()
{

}

void CKnight::init_skill()
{
	//스킬 초기화
	tAttackInfo tAttackInfo1 = {};
	tAttackInfo1.m_eAttType = ATTACK_TYPE::NORMAL;
	tAttackInfo1.m_fAttackDamage = 8.f;
	tAttackInfo1.m_fAttRcnt = 50.f;
	tAttackInfo1.m_fAttUpperRcnt = -60.f;
	tAttackInfo1.m_fAttRigidityTime = 0.5f;
	tNew_Attack tAttack1 = {Vec2(50.f,50.f),Vec2(60.f,0.f),Vec2(50.f,50.f),2,3,5.f, 5.f,tAttackInfo1};
	m_hashMonSkill.insert(make_pair(m_strTexName + L"_normal1_attack", tAttack1));


	tAttackInfo tAttackInfo2 = {};
	tAttackInfo2.m_eAttType = ATTACK_TYPE::NORMAL;
	tAttackInfo2.m_fAttackDamage = 12.f;
	tAttackInfo2.m_fAttRcnt = 70.f;
	tAttackInfo2.m_fAttUpperRcnt = -60.f;
	tAttackInfo2.m_fAttRigidityTime = 0.5f;
	tNew_Attack tAttack2 = { Vec2(75.f,50.f),Vec2(60.f,0.f),Vec2(80.f,30.f),2,3, 8.f, 8.f, tAttackInfo2 };
	m_hashMonSkill.insert(make_pair(m_strTexName + L"_normal2_attack", tAttack2));
}

void CKnight::init(const wstring& _strName)
{
	m_strTexName = _strName;
	//float fSizeX;
	//if (m_strTexName == L"Knight")
	//	fSizeX = 250.f;
	//else 
	//	fSizeX = 300.f;

	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 90.f));
	GetCollider()->SetOffSet(Vec2(0.f, 0.f));

	CreateGravity();

	CreateAnimator();

	CTexture* pTexRight = CResMgr::GetInst()->LoadTextur(m_strTexName + L"_right", L"..\\OutPut\\bin_release\\Content\\Texture\\" + m_strTexName + L"_right.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTextur(m_strTexName + L"_left", L"..\\OutPut\\bin_release\\Content\\Texture\\" + m_strTexName + L"_left.bmp");
	CTexture* pTexStart = CResMgr::GetInst()->LoadTextur(m_strTexName + L"_Start", L"..\\OutPut\\bin_release\\Content\\Texture\\" + m_strTexName + L"_start.bmp");

	GetAnimator()->CreateAnimation(m_strTexName + L"_start", pTexStart, Vec2(0.f, 0.f), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(m_vTexScale.x, 0.f), m_vTexOffset, 0.15f, 10);
	GetAnimator()->FindAnimation(m_strTexName + L"_start")->Create(pTexStart, Vec2(0.f, m_vTexScale.y), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(m_vTexScale.x, 0.f), m_vTexOffset, 0.15f, 2);

	GetAnimator()->CreateAnimation(m_strTexName + L"_idle_right", pTexRight, Vec2(0.f, 0.f), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(m_vTexScale.x, 0.f), m_vTexOffset, 0.1f, 1);
	GetAnimator()->CreateAnimation(m_strTexName + L"_walk_right", pTexRight, Vec2(0.f, m_vTexScale.y), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(m_vTexScale.x, 0.f), m_vTexOffset, 0.1f, 6);
	GetAnimator()->CreateAnimation(m_strTexName + L"_normal1_attack_right", pTexRight, Vec2(0.f, m_vTexScale.y * 2), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(m_vTexScale.x, 0.f), m_vTexOffset, 0.2f, 5);
	GetAnimator()->CreateAnimation(m_strTexName + L"_normal2_attack_right", pTexRight, Vec2(0.f, m_vTexScale.y * 3), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(m_vTexScale.x, 0.f), m_vTexOffset, 0.2f, 6);
	GetAnimator()->CreateAnimation(m_strTexName + L"_hit_right", pTexRight, Vec2(0.f, m_vTexScale.y * 4), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(m_vTexScale.x, 0.f), m_vTexOffset, 0.1f, 5);
	GetAnimator()->CreateAnimation(m_strTexName + L"_defense_right", pTexRight, Vec2(0.f, m_vTexScale.y * 5), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(m_vTexScale.x, 0.f), m_vTexOffset, 0.1f, 3);
	//GetAnimator()->CreateAnimation(L"Knight_start_right", pTexRight, Vec2(0.f, 900.f), Vec2(250.f, 150.f), Vec2(250.f, 0.f), Vec2(0.f, 0.f), 0.2f, 10);

	m_vTexOffset.x *= -1;
	GetAnimator()->CreateAnimation(m_strTexName + L"_idle_left", pTexLeft, Vec2(m_vTexScale.x * 9, 0.f), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(-m_vTexScale.x, 0.f), m_vTexOffset, 0.1f, 1);
	GetAnimator()->CreateAnimation(m_strTexName + L"_walk_left", pTexLeft, Vec2(m_vTexScale.x * 9, m_vTexScale.y), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(-m_vTexScale.x, 0.f), m_vTexOffset, 0.1f, 6);
	GetAnimator()->CreateAnimation(m_strTexName + L"_normal1_attack_left", pTexLeft, Vec2(m_vTexScale.x * 9, m_vTexScale.y * 2), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(-m_vTexScale.x, 0.f), m_vTexOffset, 0.2f, 5);
	GetAnimator()->CreateAnimation(m_strTexName + L"_normal2_attack_left", pTexLeft, Vec2(m_vTexScale.x * 9, m_vTexScale.y * 3), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(-m_vTexScale.x, 0.f), m_vTexOffset, 0.2f, 6);
	GetAnimator()->CreateAnimation(m_strTexName + L"_hit_left", pTexLeft, Vec2(m_vTexScale.x * 9, m_vTexScale.y * 4), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(-m_vTexScale.x, 0.f), m_vTexOffset, 0.1f, 5);
	GetAnimator()->CreateAnimation(m_strTexName + L"_defense_left", pTexLeft, Vec2(m_vTexScale.x * 9, m_vTexScale.y * 5), Vec2(m_vTexScale.x, m_vTexScale.y), Vec2(-m_vTexScale.x, 0.f), m_vTexOffset, 0.1f, 3);
	//GetAnimator()->CreateAnimation(L"Knight_start_left", pTexLeft, Vec2(2250.f, 900.f), Vec2(250.f, 150.f), Vec2(-250.f, 0.f), Vec2(0.f, 0.f), 0.2f, 10);


	init_skill();

	GetAnimator()->Play(m_strTexName + L"_start", false);
}


void CKnight::update()
{
	if (IsDead())
	{
		CAttackObject* pMonSkill = GetSKillObj();
		if (pMonSkill->GetCollider()->IsActive())
		{
			pMonSkill->SetColActive(false);
		}
		DeleteObject(this);
		return;
	}

	unordered_map<wstring, tNew_Attack>::iterator iter = m_hashMonSkill.begin();
	
	//스킬 쿨타임 감소
	for (; iter != m_hashMonSkill.end(); ++iter)
	{
		if (m_eMonState == MONSTER_STATE::ATTACK)
			break;

		tNew_Attack& tAttck = iter->second;
		if (tAttck.m_fSkillTime != 0.f)
		{
			tAttck.m_fSkillTime -= fDT;
			if (tAttck.m_fSkillTime < 0.f)
			{
				tAttck.m_fSkillTime = 0.f;
			}
				
		}
	}

	//내 애니메이션 실행하고 업데이트
	update_state();

	//FSM업데이트
	AI* pAI = GetAI();
	if (pAI != nullptr)
	{
		pAI->update();
	}

	CAttackObject* pMonSkill = GetSKillObj();
	if (pMonSkill->GetCollider()->IsActive())
	{
		pMonSkill->Skill_update();
	}

	
}

void CKnight::render(HDC _dc)
{
	component_render(_dc);
}

void CKnight::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	if (m_eMonState == MONSTER_STATE::STONE)
		return;

	GetSKillObj()->SetColActive(false);

	CMonster::hit(_pOther, _tAtt);
}

void CKnight::update_state()
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
	case MONSTER_STATE::STONE:
	{
		strMotion = m_strTexName + L"_start";
		pAnim->Play(strMotion, false);
	}
	break;

	case MONSTER_STATE::IDLE:
	{
		strMotion = m_strTexName + L"_idle" + sDir;
		pAnim->Play(strMotion, true);
	}
	break;
	case MONSTER_STATE::TRACE:
	{
		strMotion = m_strTexName + L"_walk" + sDir;
		pAnim->Play(strMotion, true);
	}
	break;
	case MONSTER_STATE::ATTACK:
	{
		strMotion = ((CKnightAttack*)pState)->GetAttackName();
		strMotion += sDir;
		pAnim->Play(strMotion, false);
	}
	break;
	case MONSTER_STATE::DEFENSE:
	{
		strMotion = m_strTexName + L"_defense" + sDir;
		pAnim->Play(strMotion, false);
	}
	break;
	case MONSTER_STATE::HIT:
	{
		strMotion = m_strTexName + L"_hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitState*)GetAI()->GetState(MONSTER_STATE::HIT))->SetAnimFrame(iFrame);
	}
	break;
	case MONSTER_STATE::UPPER_HIT:
	{
		strMotion = m_strTexName + L"_hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitUpper*)GetAI()->GetState(MONSTER_STATE::UPPER_HIT))->SetAnimFrame(iFrame);
		((CHitUpper*)GetAI()->GetState(MONSTER_STATE::UPPER_HIT))->SetAnimName(strMotion);
	}
	break;
	case MONSTER_STATE::DEAD:
	{
		strMotion = m_strTexName + L"_hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
		SetActiv(false);//비활성화 (공격 관통하게)
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CDeadState*)GetAI()->GetState(MONSTER_STATE::DEAD))->SetAnimFrame(iFrame);
	}
	break;
	}


}

void CKnight::OnColliderEnter(CCollider* _pOther)
{
	tMonInfo& tMonInfo = GetMonInfo();
	CObject* pobj = _pOther->GetObj();

	if (pobj->GetTag() == GROUP_TYPE::SKILL
		&& tMonInfo.m_iHp != 0)
	{
		if (dynamic_cast<CBullet*>(pobj))
		{
			CBullet* pBullet = dynamic_cast<CBullet*>(pobj);
			hit(pBullet->GetCollider(), pBullet->GetAttInfo());
		}

		else if (dynamic_cast<CBoom*>(pobj))
		{
			CBoom* pBoom = dynamic_cast<CBoom*>(pobj);
			hit(pBoom->GetCollider(), pBoom->GetAttInfo());
		}

		else if (dynamic_cast<CExsFire*>(pobj))
		{
			CExsFire* pFire = dynamic_cast<CExsFire*>(pobj);
			hit(pFire->GetCollider(), pFire->GetAttInfo());
		}
	}

	if (tMonInfo.m_iHp <= 0.f)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
	}
}

void CKnight::OnColliderExit(CCollider* _pOther)
{

}

void CKnight::OnCollision(CCollider* _pOther)
{
	//CMonster::OnCollision(_pOther);

	tMonInfo& tMonInfo = GetMonInfo();
	CObject* pobj = _pOther->GetObj();

	if (pobj->GetTag() == GROUP_TYPE::SKILL
		&& tMonInfo.m_iHp != 0)
	{
		if (dynamic_cast<CSkillState*>(pobj))
		{
			CSkillState* pSkill = dynamic_cast<CSkillState*>(pobj);

			if (!pSkill->IsAttackOn())
				return;

			hit(pSkill->GetCollider(), pSkill->GetAttInfo());
		}
		else if (dynamic_cast<CDropRobot*>(pobj))
		{
			CDropRobot* pRobot = dynamic_cast<CDropRobot*>(pobj);
			if (!pRobot->IsAttackOn())
				return;

			hit(pRobot->GetCollider(), pRobot->GetAttInfo());
		}

		if (tMonInfo.m_iHp <= 0)
		{
			ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
		}
	}
}
