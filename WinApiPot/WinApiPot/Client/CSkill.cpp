#include "pch.h"
#include "CSkill.h"

#include "CPlayer.h"
#include "CSkillMgr.h"
#include "CSkillState.h"

#include "CCollider.h"
#include "CPlayer.h"

CSkill::CSkill():
	m_pCurSkill(nullptr),
	m_pOwner(nullptr),
	m_iDir(1)
{
	
}

CSkill::~CSkill()
{
	
}

void CSkill::update()
{
	m_pCurSkill = FindSkillState(CSkillMgr::GetInst()->GetCurSkill());
	if (m_pCurSkill == nullptr)
	{
		return;
	}
	//플레이어 방향잡기
	m_iDir = m_pOwner->GetPlayerDirX();

	m_pCurSkill->Skillupdate();
}

void CSkill::AddSkill(CSkillState* _pSkillState)
{
	_pSkillState->init();
	_pSkillState->m_pOwner = this;
	
	SKILL_STATE eSkillState = _pSkillState->GetSkillState();
	m_mapSkill.insert(make_pair(eSkillState, _pSkillState));
}

CSkillState* CSkill::FindSkillState(SKILL_STATE _eSkillState)
{
	if (_eSkillState == SKILL_STATE::END)
		return nullptr;

	map<SKILL_STATE, CSkillState*>::iterator iter = m_mapSkill.find(_eSkillState);

	if (iter == m_mapSkill.end())
	{
		return nullptr;
	}
	
	return iter->second;
}

