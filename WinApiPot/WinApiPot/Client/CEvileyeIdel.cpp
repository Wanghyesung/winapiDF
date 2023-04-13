#include "pch.h"
#include "CEvileyeIdel.h"

#include "CEvileye.h"
#include "CEvileyeAttack.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"

#include "CAnimator.h"
#include "CAnimation.h"

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
		if (iter->second.m_fCurTime < 0.f)
		{
			iter->second.m_fCurTime = iter->second.m_fMaxTime;
			((CEvileyeAttack*)GetAI()->GetState(MONSTER_STATE::ATTACK))->setSkill(iter->first);
			ChangeAIState(GetAI(), MONSTER_STATE::ATTACK);
			return;
		}
	}
}

void CEvileyeIdel::update()
{
	CEvileye* pEvil = (CEvileye*)GetMonster();

	const tAttackInfo& tAtt = pEvil->GetAttackInfo();

	if (m_pTarget != nullptr)
	{
		//���� ���� �ȿ� ��� ����
		Vec2 vDiff = (m_pTarget->GetPos() - pEvil->GetPos());
		if (Vec2(abs(vDiff.x), abs(vDiff.y)) <= tAtt.m_fAttackRange)
		{
			check_skill();
		}
	}

}

void CEvileyeIdel::enter()
{
	vector<CObject*> vecPlayer = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::PLAYER);

	if (vecPlayer.size() == 0)
		return;
	else
	{
		m_pTarget = (CPlayer*)vecPlayer[0];
	}
}

void CEvileyeIdel::exit()
{
	CState::exit();
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
}

