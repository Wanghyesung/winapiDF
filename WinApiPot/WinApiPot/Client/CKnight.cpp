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
#include "CCollider.h"


CKnight::CKnight()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 90.f));
	GetCollider()->SetOffSet(Vec2(0.f, 0.f));

	CreateGravity();

	CreateAnimator();

	CTexture* pTexRight = CResMgr::GetInst()->LoadTextur(L"Knight_right", L"..\\OutPut\\bin_release\\Content\\Texture\\Knight_right.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTextur(L"Knight_left", L"..\\OutPut\\bin_release\\Content\\Texture\\Knight_left.bmp");

	GetAnimator()->CreateAnimation(L"Knight_idle_right",pTexRight,Vec2(0.f,0.f),Vec2(250.f,150.f), Vec2(250.f,0.f),Vec2(0.f,0.f),0.1f,1);
	GetAnimator()->CreateAnimation(L"Knight_walk_right", pTexRight, Vec2(0.f, 150.f), Vec2(250.f, 150.f), Vec2(250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"Knight_noraml1_attack_right", pTexRight, Vec2(0.f, 300.f), Vec2(250.f, 150.f), Vec2(250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"Knight_normal2_attack_right", pTexRight, Vec2(0.f, 450.f), Vec2(250.f, 150.f), Vec2(250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"Knight_hit_right", pTexRight, Vec2(0.f, 600.f), Vec2(250.f, 150.f), Vec2(250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"Knight_defense_right", pTexRight, Vec2(0.f, 750.f), Vec2(250.f, 150.f), Vec2(250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"Knight_start_right", pTexRight, Vec2(0.f, 900.f), Vec2(250.f, 150.f), Vec2(250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 10);

	GetAnimator()->CreateAnimation(L"Knight_idle_left", pTexLeft, Vec2(2250.f, 0.f), Vec2(250.f, 150.f), Vec2(-250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"Knight_walk_left", pTexLeft, Vec2(2250.f, 150.f), Vec2(250.f, 150.f), Vec2(-250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"Knight_noraml1_attack_left", pTexLeft, Vec2(2250.f, 300.f), Vec2(250.f, 150.f), Vec2(-250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"Knight_normal2_attack_left", pTexLeft, Vec2(2250.f, 450.f), Vec2(250.f, 150.f), Vec2(-250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"Knight_hit_left", pTexLeft, Vec2(2250.f, 600.f), Vec2(250.f, 150.f), Vec2(-250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"Knight_defense_left", pTexLeft, Vec2(2250.f, 750.f), Vec2(250.f, 150.f), Vec2(-250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"Knight_start_left", pTexLeft, Vec2(2250.f, 900.f), Vec2(250.f, 150.f), Vec2(-250.f, 0.f), Vec2(0.f, 0.f), 0.1f, 10);

	init_skill();
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
	tKnight_Attack tAttack1 = {Vec2(40.f,40.f),Vec2(20.f,0.f),Vec2(40.f,40.f),2,3,5.f, 5.f,tAttackInfo1};
	m_hashMonSkill.insert(make_pair(L"Knight_noraml1_attack", tAttack1));


	tAttackInfo tAttackInfo2 = {};
	tAttackInfo2.m_eAttType = ATTACK_TYPE::NORMAL;
	tAttackInfo2.m_fAttackDamage = 12.f;
	tAttackInfo2.m_fAttRcnt = 70.f;
	tAttackInfo2.m_fAttUpperRcnt = -60.f;
	tAttackInfo2.m_fAttRigidityTime = 0.5f;
	tKnight_Attack tAttack2 = { Vec2(60.f,30.f),Vec2(20.f,0.f),Vec2(60.f,30.f),2,3, 8.f, 8.f, tAttackInfo2 };
	m_hashMonSkill.insert(make_pair(L"Knight_noraml2_attack", tAttack2));
}


void CKnight::update()
{
	unordered_map<wstring, tKnight_Attack>::iterator iter = m_hashMonSkill.begin();
	
	//스킬 쿨타임 감소
	for (; iter != m_hashMonSkill.end(); ++iter)
	{
		if (m_eMonState == MONSTER_STATE::ATTACK)
			break;

		tKnight_Attack& tAttck = iter->second;
		if (tAttck.m_fSkillTime != 0.f)
		{
			tAttck.m_fSkillTime -= fDT;
			if (tAttck.m_fSkillTime < 0.f)
			{
				tAttck.m_fSkillTime = 0.f;
			}
				
		}
	}

	//FSM업데이트
	AI* pAI = GetAI();
	if (pAI != nullptr)
	{
		pAI->update();
	}

	update_state();
}

void CKnight::render(HDC _dc)
{
	component_render(_dc);
}

void CKnight::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
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
	case MONSTER_STATE::IDLE:
	{
		strMotion = L"Knight_idle" + sDir;
		pAnim->Play(strMotion, true);
	}
	break;
	case MONSTER_STATE::TRACE:
	{
		strMotion = L"Knight_walk" + sDir;
		pAnim->Play(strMotion, true);
	}
	break;
	case MONSTER_STATE::ATTACK:
	{
		//strMotion = L"Knight_idle" + sDir;
		//pAnim->Play(strMotion, true);
	}
	break;
	case MONSTER_STATE::DEFENSE:
	{
		strMotion = L"Knight_defense" + sDir;
		pAnim->Play(strMotion, false);
	}
	break;
	case MONSTER_STATE::HIT:
	{
		strMotion = L"Knight_hit" + sDir;
		pAnim->Play(strMotion, false);
	}
	break;
	case MONSTER_STATE::UPPER_HIT:
	{
		strMotion = L"Knight_hit" + sDir;
		pAnim->Play(strMotion, false);
	}
	break;
	case MONSTER_STATE::DEAD:
	{
		strMotion = L"Knight_hit" + sDir;
		pAnim->Play(strMotion, false);
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

		if (tMonInfo.m_iHp == 0)
		{
			ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
		}
	}
}
