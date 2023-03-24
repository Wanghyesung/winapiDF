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
	m_iSkillTime(0),
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
	//내 충돌체 모아둔 벡터 초기화
	m_vecOtherColl.clear();
	//내 스킬 쿨타임 최대로
	CSkillMgr::GetInst()->SetSkillTimeMax(m_eSkillState);
	//현재 스킬 end로
	CSkillMgr::GetInst()->SetCurSkill(SKILL_STATE::END);
	//스킬이 끝났을을 알림
	CSkillMgr::GetInst()->SetEndSkill(false);
	//내 충돌체 비활성화
	GetCollider()->SetActive(false);
}

void CSkillState::enter()
{
	//대충 크게 잡아서 100
	m_vecOtherColl.resize(100,-1);
	GetCollider()->SetActive(true);
	
}





