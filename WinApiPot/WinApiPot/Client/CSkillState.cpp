#include "pch.h"
#include "CSkillState.h"

#include "CPlayer.h"
#include "CObject.h"

#include "CSkillMgr.h"
#include "CSkill.h"
#include "CCollider.h"

#include "CAnimator.h"

#include "CAnimation.h"
#include "CSceneMgr.h"
#include "CScene.h"


CSkillState::CSkillState(SKILL_STATE _eSkill) :
	m_eSkillState(_eSkill),
	m_pOwner(nullptr),
	m_iFrm(0),
	m_bOnAttack(false),
	m_vecAttackFrame{},
	m_vecOtherColl{}
{

	SetTag(GROUP_TYPE::SKILL);
}

CSkillState::~CSkillState()
{

}



void CSkillState::exit()
{
	m_vecOtherColl.clear();
	CSkillMgr::GetInst()->SetSkillTimeMax(m_eSkillState);
	CSkillMgr::GetInst()->SetCurSkill(SKILL_STATE::END);
	CSkillMgr::GetInst()->SetEndSkill(false);
	GetCollider()->SetActive(false);
}

void CSkillState::enter()
{
	//대충 크게 잡아서 100
	m_vecOtherColl.resize(100,-1);
	GetCollider()->SetActive(true);
	
}





