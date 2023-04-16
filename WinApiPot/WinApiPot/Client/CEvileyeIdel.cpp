#include "pch.h"
#include "CEvileyeIdel.h"

#include "CEvileye.h"
#include "CEvileyeAttack.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CGravity.h"

#include "AI.h"

CEvileyeIdel::CEvileyeIdel():
	CState(MONSTER_STATE::IDLE)
{

}

CEvileyeIdel::~CEvileyeIdel()
{

}

void CEvileyeIdel::check_skill()
{
	CEvileye* pEvil = (CEvileye*)GetMonster();

	unordered_map<UINT, tEvileyeSkill>::iterator iter = pEvil->m_hashSkillTime.begin();

	for (; iter != pEvil->m_hashSkillTime.end(); ++iter)
	{
		if (iter->second.m_fCurTime == 0.f)
		{
			iter->second.m_fCurTime = iter->second.m_fMaxTime;
			UINT i = iter->first;
			((CEvileyeAttack*)GetAI()->GetState(MONSTER_STATE::ATTACK))->setSkill(iter->first);
			ChangeAIState(GetAI(), MONSTER_STATE::ATTACK);
			return;
		}
	}
}

void CEvileyeIdel::update()
{
	vector<CObject*> vecPlayer = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::PLAYER);

	if (vecPlayer.size() == 0)
		return;
	else
	{
		m_pTarget = (CPlayer*)vecPlayer[0];
	}


	CEvileye* pEvil = (CEvileye*)GetMonster();
	Vec2 vPos = pEvil->GetCollider()->GetFinalPos();
	Vec2 vTargetPos;

	if (m_pTarget->GetGravity()->IsGetGravity())
	{
		vTargetPos = m_pTarget->GetJumPos();
	}
	else
		vTargetPos = m_pTarget->GetCollider()->GetFinalPos();

	Vec2 vDiff = vTargetPos - vPos;

	if (abs(vDiff.y) > 25.f)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::TRACE);
		return;
	}

	const tAttackInfo& tAtt = pEvil->GetAttackInfo();
	if (m_pTarget != nullptr)
	{
		//공격 범위 안에 들면 공격
		Vec2 vDiff = (m_pTarget->GetPos() - pEvil->GetPos());
		if (Vec2(abs(vDiff.x), abs(vDiff.y)) <= tAtt.m_fAttackRange)
		{
			check_skill();
		}
	}


}

void CEvileyeIdel::enter()
{
	
}

void CEvileyeIdel::exit()
{
	CState::exit();
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
}

