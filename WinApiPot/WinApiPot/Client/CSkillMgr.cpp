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

#include "CGravity.h"
#include "CFSM.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CKeyMgr.h"

#define MAX_SKILLTIME 5.f;

CSkillMgr::CSkillMgr() :
	m_eCurStkllState(SKILL_STATE::END),
	m_fMaxSkillTime(5.f),
	m_bOnSkill(false),
	m_pPlayer(nullptr)
{

}

CSkillMgr::~CSkillMgr()
{

}

void CSkillMgr::init()
{
	if (m_pPlayer == nullptr || m_pPlayer->IsDead())
		return;

	for (UINT i = 0; i < (UINT)SKILL_STATE::END; ++i)
	{
		m_mapSkill.insert(make_pair((SKILL_STATE)i, 0.f));
	}
	initSkill();
}

void CSkillMgr::initSkill()
{
	CKick* pCkick = new CKick;
	m_pPlayer->m_pSkill->AddSkill(pCkick);
	SceneMgr::GetInst()->GetCurSCene()->AddObject(pCkick, GROUP_TYPE::SKILL);

	CMachKick* pMachKick = new CMachKick;
	m_pPlayer->m_pSkill->AddSkill(pMachKick);
	SceneMgr::GetInst()->GetCurSCene()->AddObject(pMachKick, GROUP_TYPE::SKILL);

	CRandomFire* pRandomFire = new CRandomFire;
	m_pPlayer->m_pSkill->AddSkill(pRandomFire);
	SceneMgr::GetInst()->GetCurSCene()->AddObject(pRandomFire, GROUP_TYPE::SKILL);

	CWindmill* pWindMill = new CWindmill;
	m_pPlayer->m_pSkill->AddSkill(pWindMill);
	SceneMgr::GetInst()->GetCurSCene()->AddObject(pWindMill, GROUP_TYPE::SKILL);

	CWalkFire* pWalkFire = new CWalkFire;
	m_pPlayer->m_pSkill->AddSkill(pWalkFire);
	SceneMgr::GetInst()->GetCurSCene()->AddObject(pWalkFire, GROUP_TYPE::SKILL);
}

void CSkillMgr::update()
{
	if (m_pPlayer == nullptr)
		return;

	map<SKILL_STATE, float>::iterator iter = m_mapSkill.begin();

	//��ų ��Ÿ��
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
	
	//��ų ��Ÿ�� �� ������ Ű���� ���� ��ų ���
	skillKey_update();
}

void CSkillMgr::skillKey_update()
{
	if (m_pPlayer == nullptr)
		return;

	//��ų ����߿� C�� ������ ĵ��
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
		m_eCurStkllState = SKILL_STATE::RANDOM_FIRE;
	}

	else if (KEY_TAP(KEY::D))
	{
		m_eCurStkllState = SKILL_STATE::WINDMILL;
	}

	else if (KEY_TAP(KEY::S))
	{
		m_eCurStkllState = SKILL_STATE::MACH_KICK;
	}

	else if (KEY_TAP(KEY::Z))
	{
		m_eCurStkllState = SKILL_STATE::UPPER_KICK;
	}

	else if (KEY_TAP(KEY::T))
	{
		m_eCurStkllState = SKILL_STATE::WALK_FIRE;
	}
	

	if(!IsPossibleSkill(m_eCurStkllState))//��밡���� ��ų����
	{
		m_eCurStkllState = SKILL_STATE::END;
		return;
	}


	map<SKILL_STATE, float>::iterator iter = m_mapSkill.find(m_eCurStkllState);
	m_bOnSkill = true;//���� ��ų ���¸� ���³�
	
}

void CSkillMgr::SetSkillTimeMax(SKILL_STATE _eSkill)
{
	map<SKILL_STATE, float>::iterator iter = m_mapSkill.find(_eSkill);

	iter->second = m_fMaxSkillTime;
}

bool CSkillMgr::IsPossibleSkill(SKILL_STATE _tSkill)
{
	map<SKILL_STATE, float>::iterator iter = m_mapSkill.find(_tSkill);

	//��ϵǾ��ִ� ��ų����
	if (m_pPlayer->m_pSkill->FindSkillState(_tSkill) == nullptr)
	{
		return false;
	}

	//�÷��̾� ���°��� ���� ��ų ��� ����
	if (m_pPlayer->GetGravity()->IsGetGravity())
		return false;

	//��ų ���
	if (iter->second == 0.f)
	{
		//����� �����ϸ� �� ��ų�� enter() ȣ��
		m_pPlayer->m_pSkill->FindSkillState(_tSkill)->enter();
		return true;
	}

	return false;
}



