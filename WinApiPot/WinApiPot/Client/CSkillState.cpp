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
	//�� �浹ü ��Ƶ� ���� �ʱ�ȭ
	m_vecOtherColl.clear();
	//�� ��ų ��Ÿ�� �ִ��
	CSkillMgr::GetInst()->SetSkillTimeMax(m_eSkillState);
	//���� ��ų end��
	CSkillMgr::GetInst()->SetCurSkill(SKILL_STATE::END);
	//��ų�� �������� �˸�
	CSkillMgr::GetInst()->SetEndSkill(false);
	//�� �浹ü ��Ȱ��ȭ
	GetCollider()->SetActive(false);
}

void CSkillState::enter()
{
	//���� ũ�� ��Ƽ� 100
	m_vecOtherColl.resize(100,-1);
	GetCollider()->SetActive(true);
	
}





