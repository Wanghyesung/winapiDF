#include "pch.h"
#include "CArdor.h"

#include "CTimeMgr.h"

#include "AI.h"
#include "CAttackObject.h"

#include "CCollider.h"

#include "CState.h"
#include "CArdorAttack.h"

#include "CHitState.h"
#include "CDeadState.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CBullet.h"
#include "CSkillState.h"

#include "CItemMgr.h"

CArdor::CArdor() :
	m_hashMonSkill{},
	m_eMonState(MONSTER_STATE::IDLE)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(60.f, 60.f));
	GetCollider()->SetOffSet(Vec2(0.f, 0.f));

	CreateGravity();

	CreateAnimator();

	CTexture* pTexRight = CResMgr::GetInst()->LoadTextur(L"ardor_right", L"..\\OutPut\\bin_release\\Content\\Texture\\ardor_right.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTextur(L"ardor_left", L"..\\OutPut\\bin_release\\Content\\Texture\\ardor_left.bmp");


	GetAnimator()->CreateAnimation(L"ardor_idle_right", pTexRight, Vec2(0.f, 0.f), Vec2(170.f, 180.f), Vec2(170.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"ardor_run_right", pTexRight, Vec2(0.f, 0.f), Vec2(170.f, 180.f), Vec2(170.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"ardor_attack1_right", pTexRight, Vec2(0.f, 180.f), Vec2(170.f, 180.f), Vec2(170.f, 0.f), Vec2(0.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"ardor_hit_right", pTexRight, Vec2(0.f, 360.f), Vec2(170.f, 180.f), Vec2(170.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);

	GetAnimator()->CreateAnimation(L"ardor_idle_left", pTexLeft, Vec2(1020.f, 0.f), Vec2(170.f, 180.f), Vec2(-170.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"ardor_run_left", pTexLeft, Vec2(1020.f, 0.f), Vec2(170.f, 180.f), Vec2(-170.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"ardor_attack1_left", pTexLeft, Vec2(1020.f, 180.f), Vec2(170.f, 180.f), Vec2(-170.f, 0.f), Vec2(0.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"ardor_hit_left", pTexLeft, Vec2(1020.f, 360.f), Vec2(170.f, 180.f), Vec2(-170.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);

	init_skill();

	GetAnimator()->Play(L"ardor_idle_right", true);
}

CArdor::~CArdor()
{
}

void CArdor::update()
{
	if (IsDead())
	{
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

	update_state();

	AI* pAI = GetAI();

	if (pAI != nullptr)
	{
		pAI->update();
	}

	CAttackObject* pAttackObj = GetSKillObj();

	if (pAttackObj->GetCollider()->IsActive())
	{
		pAttackObj->Skill_update();
	}


}

void CArdor::render(HDC _dc)
{
	component_render(_dc);
}

void CArdor::update_state()
{
	AI* pAI = GetAI();
	CState* pState = pAI->GetCurState();
	CAnimator* pAnim = GetAnimator();

	m_eMonState = pState->GetType();
	int iDir = pState->GetDir();

	wstring strMotion;
	wstring strDir = iDir > 0 ? L"_right" : L"_left";

	switch (m_eMonState)
	{
	case MONSTER_STATE::IDLE:
	{
		strMotion = L"ardor_idle" + strDir;
		pAnim->Play(strMotion, true);
	}
	break;
	case MONSTER_STATE::TRACE:
	{
		strMotion = L"ardor_run" + strDir;
		pAnim->Play(strMotion, true);
	}
	break;
	case MONSTER_STATE::ATTACK:
	{
		strMotion = ((CArdorAttack*)pState)->GetAttackName();
		strMotion += strDir;
		pAnim->Play(strMotion, false);
	}
	break;
	case MONSTER_STATE::HIT:
	{
		strMotion = L"ardor_hit" + strDir;
		pAnim->Play(strMotion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitState*)GetAI()->GetState(MONSTER_STATE::HIT))->SetAnimFrame(iFrame);
	}
	break;
	case MONSTER_STATE::DEAD:
	{
		strMotion = L"ardor_hit" + strDir;
		pAnim->Play(strMotion, false);
		SetActiv(false);//비활성화 (공격 관통하게)
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CDeadState*)GetAI()->GetState(MONSTER_STATE::DEAD))->SetAnimFrame(iFrame);
	}
	break;
	}
}

void CArdor::init_skill()
{
	tAttackInfo tAttackInfo1 = {};
	tAttackInfo1.m_eAttType = ATTACK_TYPE::NORMAL;
	tAttackInfo1.m_fAttackDamage = 8.f;
	tAttackInfo1.m_fAttRcnt = 50.f;
	tAttackInfo1.m_fAttUpperRcnt = -60.f;
	tAttackInfo1.m_fAttRigidityTime = 0.5f;
	tNew_Attack tAttack1 = { Vec2(60.f,60.f),Vec2(60.f,0.f),Vec2(50.f,50.f),1,2,5.f, 5.f,tAttackInfo1 };
	m_hashMonSkill.insert(make_pair(L"ardor_attack1", tAttack1));


	/*tAttackInfo tAttackInfo2 = {};
	tAttackInfo2.m_eAttType = ATTACK_TYPE::NORMAL;
	tAttackInfo2.m_fAttackDamage = 12.f;
	tAttackInfo2.m_fAttRcnt = 70.f;
	tAttackInfo2.m_fAttUpperRcnt = -60.f;
	tAttackInfo2.m_fAttRigidityTime = 0.5f;
	tNew_Attack tAttack2 = { Vec2(75.f,75.f),Vec2(0.f,0.f),Vec2(80.f,30.f),0,5, 8.f, 8.f, tAttackInfo2 };
	m_hashMonSkill.insert(make_pair(L"naias_attack2", tAttack2));*/
}

void CArdor::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	AI* pAI = GetAI();
	MONSTER_STATE m_tMonState = pAI->GetCurState()->GetType();

	CCollider* pCollider = GetCollider();

	tHitInfo& tHitInfo = GetHitInfo();
	tMonInfo& tMonInfo = GetMonInfo();

	tHitInfo.m_fHitRcnt = _tAtt.m_fAttRcnt;
	tHitInfo.m_fHitRigidityTime = _tAtt.m_fAttRigidityTime;
	tHitInfo.m_fHitUpperRcnt = _tAtt.m_fAttUpperRcnt;

	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::SKILL
		&& tMonInfo.m_iHp > 0)
	{
		float fDir = GetCollider()->GetFinalPos().x - _pOther->GetFinalPos().x;
		if (fDir > 0.f)
			fDir = 1.f;
		else
			fDir = -1.f;

		tHitInfo.m_fHitDir = fDir;
		ChangeAIState(pAI, MONSTER_STATE::HIT);

		//띄움판정 없이
		tMonInfo.m_iHp -= _tAtt.m_fAttackDamage;
		if (tMonInfo.m_iHp <= 0.f)
		{
			tMonInfo.m_iHp = 0.f;
			//아이템 생성
			CItemMgr::GetInst()->CreateItem(GetPos());
		}
		update_MonInterFace();
	}

}

void CArdor::OnColliderEnter(CCollider* _pOther)
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

void CArdor::OnColliderExit(CCollider* _pOther)
{
}

void CArdor::OnCollision(CCollider* _pOther)
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

		if (tMonInfo.m_iHp <= 0)
		{
			ChangeAIState(GetAI(), MONSTER_STATE::DEAD);
		}
	}
}
