#include "pch.h"
#include "CSkillMgr.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"

#include "CScene.h"

#include "CPlayer.h"
#include "CSkill.h"

#include "CSkillState.h"
#include "CWindmill.h"
#include "CKick.h"
#include "CRandomFire.h"
#include "CWalkFire.h"
#include "CMachKick.h"
#include "CLaser.h"
#include "CRx78.h"
#include "CFire.h"

#include "CFSM.h"
#include "CPlayerState.h"

#include "CGravity.h"
#include "CFSM.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CKeyMgr.h"

#include "CInterfaceMgr.h"


CSkillMgr::CSkillMgr() :
	m_eCurStkllState(SKILL_STATE::END),
	m_fMaxSkillTime(5.f),
	m_bOnSkill(false),
	m_pPlayer(nullptr),
	m_iSkillType(2)
{

}

CSkillMgr::~CSkillMgr()
{

}

void CSkillMgr::init(SCENE_TYPE _eSceneType)
{
	if (m_pPlayer == nullptr || m_pPlayer->IsDead())
		return;

	for (UINT i = 0; i < (UINT)SKILL_STATE::END; ++i)
	{
		m_mapSkill.insert(make_pair((SKILL_STATE)i, 0.f));
	}
	initSkill(_eSceneType);
}

void CSkillMgr::initSkill(SCENE_TYPE _eSceneType)
{
	CKick* pCkick = new CKick;
	m_pPlayer->m_pSkill->AddSkill(pCkick);
	SceneMgr::GetInst()->FindScene(_eSceneType)->AddObject(pCkick, GROUP_TYPE::SKILL);

	CMachKick* pMachKick = new CMachKick;
	m_pPlayer->m_pSkill->AddSkill(pMachKick);
	SceneMgr::GetInst()->FindScene(_eSceneType)->AddObject(pMachKick, GROUP_TYPE::SKILL);

	CRandomFire* pRandomFire = new CRandomFire;
	m_pPlayer->m_pSkill->AddSkill(pRandomFire);
	SceneMgr::GetInst()->FindScene(_eSceneType)->AddObject(pRandomFire, GROUP_TYPE::SKILL);

	CWindmill* pWindMill = new CWindmill;
	m_pPlayer->m_pSkill->AddSkill(pWindMill);
	SceneMgr::GetInst()->FindScene(_eSceneType)->AddObject(pWindMill, GROUP_TYPE::SKILL);

	CWalkFire* pWalkFire = new CWalkFire;
	m_pPlayer->m_pSkill->AddSkill(pWalkFire);
	SceneMgr::GetInst()->FindScene(_eSceneType)->AddObject(pWalkFire, GROUP_TYPE::SKILL);

	//laser
	CLaser* pLaser = new CLaser;
	m_pPlayer->m_pSkill->AddSkill(pLaser);
	SceneMgr::GetInst()->FindScene(_eSceneType)->AddObject(pLaser, GROUP_TYPE::SKILL);

	CRx78* pRx78 = new CRx78;
	m_pPlayer->m_pSkill->AddSkill(pRx78);
	SceneMgr::GetInst()->FindScene(_eSceneType)->AddObject(pRx78, GROUP_TYPE::SKILL);

	CFire* pFire = new CFire;
	m_pPlayer->m_pSkill->AddSkill(pFire);
	SceneMgr::GetInst()->FindScene(_eSceneType)->AddObject(pFire, GROUP_TYPE::SKILL);

}



void CSkillMgr::update()
{
	if (m_pPlayer == nullptr || !m_pPlayer->m_bActive)
		return;

	map<SKILL_STATE, float>::iterator iter = m_mapSkill.begin();

	//스킬 쿨타임
	for (iter; iter != m_mapSkill.end(); ++iter)
	{
		if (iter->second == 0.f)
		{
			continue;
		}
		else
		{
			iter->second -= fDT;
			if (iter->second <= 0.f)
				iter->second = 0.f;
		}
	}
	
	//스킬 쿨타임 다 돌리고 키값에 따른 스킬 사용
	skillKey_update();
}

void CSkillMgr::skillKey_update()
{
	if (m_pPlayer == nullptr)
		return;

	//스킬 사용중에 C를 누르면 캔슬

	if (m_bOnSkill)
	{
		if (KEY_TAP(KEY::C))
		{
			m_pPlayer->m_pSkill->FindSkillState(m_eCurStkllState)->exit();
			m_bOnSkill = false;
			m_eCurStkllState = SKILL_STATE::END;
		}
		return;
	}
		
	else if (KEY_TAP(KEY::F))
	{
		if (m_iSkillType == 1)
			m_eCurStkllState = SKILL_STATE::RANDOM_FIRE;
		else
			m_eCurStkllState = SKILL_STATE::FIRE;
	}

	else if (KEY_TAP(KEY::D))
	{
		if (m_iSkillType == 1)
			m_eCurStkllState = SKILL_STATE::WINDMILL;
	}

	else if (KEY_TAP(KEY::S))
	{
		if (m_iSkillType == 1)
			m_eCurStkllState = SKILL_STATE::MACH_KICK;
	}

	else if (KEY_TAP(KEY::Z))
	{
		if (m_iSkillType == 1)
			m_eCurStkllState = SKILL_STATE::UPPER_KICK;
		else
			m_eCurStkllState = SKILL_STATE::RX;
	}

	else if (KEY_TAP(KEY::T))
	{
		if (m_iSkillType == 1)
			m_eCurStkllState = SKILL_STATE::WALK_FIRE;
	}

	else if (KEY_TAP(KEY::W))
	{
		if (m_iSkillType == 1)
			m_eCurStkllState = SKILL_STATE::LASER;
	}
	

	if(!IsPossibleSkill(m_eCurStkllState))//사용가능한 스킬인지
	{
		m_eCurStkllState = SKILL_STATE::END;
		return;
	}
	
}

void CSkillMgr::SetSkillTimeMax(SKILL_STATE _eSkill)
{
	//스킬 쿨타임 최대로
	map<SKILL_STATE, float>::iterator iter = m_mapSkill.find(_eSkill);

	CSkillState* pSkill = m_pPlayer->GetSkill()->FindSkillState(_eSkill);

	iter->second = pSkill->m_iSkillTime;
}


bool CSkillMgr::IsPossibleSkill(SKILL_STATE _tSkill)
{
	map<SKILL_STATE, float>::iterator iter = m_mapSkill.find(_tSkill);
	CSkillState* pSkill = m_pPlayer->m_pSkill->FindSkillState(_tSkill);
	//등록되어있는 스킬인지
	if (pSkill == nullptr)
		return false;

	//플레이어 상태값에 따른 스킬 사용 유무
	if (m_pPlayer->GetGravity()->IsGetGravity())
		return false;

	if (m_pPlayer->m_tPlayerInfo.m_fMP < pSkill->GetMP())
		return false;

	if (m_pPlayer->playerCurState == PLAYER_STATE::HIT || 
		m_pPlayer->playerCurState == PLAYER_STATE::UPPER_HIT ||
		m_pPlayer->playerCurState == PLAYER_STATE::ATTACK_SLIDING)
		return false;

	//스킬 사용
	if (iter->second == 0.f)
	{
		//내 state -> exit  skillstate-> enter
		InitState(_tSkill);
		reducedMp(_tSkill);
		return true;
	}

	return false;
}

void CSkillMgr::InitState(SKILL_STATE _tSkill)
{
	m_bOnSkill = true;//현재 스킬 상태를 나태냄
	CSkillState* pSkill = m_pPlayer->m_pSkill->FindSkillState(_tSkill);
	//m_pPlayer->m_pFSM->GetCurState()->Exit();
	m_pPlayer->m_pFSM->ChangeState(PLAYER_STATE::IDLE);
	//ChangeFSMState(m_pPlayer->m_pFSM, PLAYER_STATE::IDLE);
	pSkill->enter();
}

float CSkillMgr::GetCurSKillTime(SKILL_STATE _eSkill)
{
	map<SKILL_STATE, float>::iterator iter = m_mapSkill.find(_eSkill);

	if (iter == m_mapSkill.end())
		return 0;
	
	
	return iter->second;
}

void CSkillMgr::reducedMp(SKILL_STATE _tSkill)
{
	//MP 소모
	CSkillState* pSkill = m_pPlayer->m_pSkill->FindSkillState(_tSkill);
	m_pPlayer->m_tPlayerInfo.m_fMP -= pSkill->GetMP();
}




