#include "pch.h"
#include "CEvileye.h"

#include "CTimeMgr.h"

#include "AI.h"
#include "CState.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CCollider.h"
#include "CBullet.h"
#include "CSkillState.h"
#include "CHitState.h"
#include "CDeadState.h"
#include "CItemMgr.h"

CEvileye::CEvileye():
	m_hashSkillTime{},
	m_eMonState(MONSTER_STATE::IDLE),
	m_strMonDir(L"_right")
{
	CreateAnimator();
	
	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 90.f));
	GetCollider()->SetOffSet(Vec2(0.f, 0.f));

	CTexture* pTexRight = CResMgr::GetInst()->LoadTextur(L"evileye_right", L"..\\OutPut\\bin_release\\Content\\Texture\\evileye_right.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTextur(L"evileye_left", L"..\\OutPut\\bin_release\\Content\\Texture\\evileye_left.bmp");

	GetAnimator()->CreateAnimation(L"evileye_idle_right", pTexRight, Vec2(0.f, 0.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), Vec2(0.f, 0.f), 0.2f, 7);
	GetAnimator()->CreateAnimation(L"evileye_skill_right", pTexRight, Vec2(0.f, 200.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), Vec2(0.f, 0.f), 0.2f, 7);
	GetAnimator()->CreateAnimation(L"evileye_hit_right", pTexRight, Vec2(0.f, 400.f), Vec2(200.f, 200.f), Vec2(200.f, 0.f), Vec2(0.f, 0.f), 0.2f, 3);
									
	GetAnimator()->CreateAnimation(L"evileye_idle_left", pTexLeft, Vec2(1200.f, 0.f), Vec2(200.f, 200.f), Vec2(-200.f, 0.f), Vec2(0.f, 0.f), 0.2f, 7);
	GetAnimator()->CreateAnimation(L"evileye_skill_left", pTexLeft, Vec2(1200.f, 200.f), Vec2(200.f, 200.f), Vec2(-200.f, 0.f), Vec2(0.f, 0.f), 0.2f, 7);
	GetAnimator()->CreateAnimation(L"evileye_hit_left", pTexLeft, Vec2(1200.f, 400.f), Vec2(200.f, 200.f), Vec2(-200.f, 0.f), Vec2(0.f, 0.f), 0.2f, 3);

	GetAnimator()->Play(L"evileye_idle" + m_strMonDir, true);
}

CEvileye::~CEvileye()
{

}

void CEvileye::update()
{
	if (IsDead())
	{
		DeleteObject(this);
		return;
	}

	update_skilltime();

	update_state();

	AI* pAI = GetAI();

	if (pAI != nullptr)
	{
		pAI->update();
	}

}

void CEvileye::init_skill()
{
	tEvileyeSkill tSkill1;
	tSkill1.m_fCurTime = 5.f;
	tSkill1.m_fMaxTime = 5.f;
	tSkill1.m_iStartFrame = 3;
	m_hashSkillTime.insert(make_pair((UINT)EVILSKILL::LASER, tSkill1));

	//tEvileyeSkill tSkill2;
	//tSkill2.m_fCurTime = 10.f;
	//tSkill2.m_fMaxTime = 10.f;
	//tSkill2.m_iStartFrame = 3;
	//m_hashSkillTime.insert(make_pair((UINT)EVILSKILL::SHOT, tSkill2));
}

void CEvileye::update_skilltime()
{
	AI* pAI = GetAI();

	unordered_map<UINT, tEvileyeSkill>::iterator iter = m_hashSkillTime.begin();

	for (; iter != m_hashSkillTime.end(); ++iter)
	{
		if (m_eMonState == MONSTER_STATE::HIT||
			m_eMonState == MONSTER_STATE::ATTACK)
			break;

		if (iter->second.m_fCurTime > 0.f)
		{
			iter->second.m_fCurTime -= fDT;
			if (iter->second.m_fCurTime < 0.f)
				iter->second.m_fCurTime = 0.f;
		}
	}
}

void CEvileye::update_state()
{
	AI* pAI = GetAI();
	m_eMonState = pAI->GetCurState()->GetType();

	wstring strMotion;
	switch (m_eMonState)
	{
	case MONSTER_STATE::IDLE:
	{
		strMotion = L"evileye_idle" + m_strMonDir;
		GetAnimator()->Play(strMotion, true);
	}
		break;
	case MONSTER_STATE::ATTACK:
	{
		strMotion = L"evileye_skill" + m_strMonDir;
		GetAnimator()->Play(strMotion, false);
	}
		break;
	case MONSTER_STATE::HIT:
	{
		strMotion = L"evileye_hit" + m_strMonDir;
		GetAnimator()->Play(strMotion, false);
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CHitState*)GetAI()->GetState(MONSTER_STATE::HIT))->SetAnimFrame(iFrame);
	}
		break;
	case MONSTER_STATE::DEAD:
	{
		strMotion = L"evileye_hit" + m_strMonDir;
		GetAnimator()->Play(strMotion, false);
		SetActiv(false);//비활성화 (공격 관통하게)
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		((CDeadState*)GetAI()->GetState(MONSTER_STATE::DEAD))->SetAnimFrame(iFrame);
	}
		break;
	
	}
}

void CEvileye::SetDir(int _iDir)
{
	_iDir > 0 ? m_strMonDir = L"_right" : m_strMonDir = L"_left";
}

void CEvileye::shotEye()
{

}

void CEvileye::createEye()
{

}

void CEvileye::createLaser()
{

}

void CEvileye::render(HDC _dc)
{
	component_render(_dc);
}

void CEvileye::OnColliderEnter(CCollider* _pOther)
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

void CEvileye::OnColliderExit(CCollider* _pOther)
{

}

void CEvileye::OnCollision(CCollider* _pOther)
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

void CEvileye::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	AI* pAI = GetAI();
	MONSTER_STATE m_tMonState = pAI->GetCurState()->GetType();

	CCollider* pCollider = GetCollider();

	tHitInfo& tHitInfo = GetHitInfo();
	tMonInfo& tMonInfo = GetMonInfo();

	tHitInfo.m_fHitRcnt = 0.f;
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




