#include "pch.h"
#include "CKnightAttack.h"

#include "AI.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKnight.h"
#include "CMonster.h"
#include "CPlayer.h"

#include "CAttackObject.h"

CKnightAttack::CKnightAttack():
	CState(MONSTER_STATE::ATTACK),
	m_strAttackName(L"")
{
}

CKnightAttack::~CKnightAttack()
{

}

void CKnightAttack::SetAttackName(const wstring& _strName)
{
	m_strAttackName = _strName;
	CKnight* pMon = (CKnight*)GetMonster();
	tKnight_Attack& tAtt = pMon->m_hashMonSkill[m_strAttackName];
	tAtt.m_fSkillTime = tAtt.m_fSkillMaxTime;
}

void CKnightAttack::update()
{
	CKnight* pMon = (CKnight*)GetMonster();
	tKnight_Attack& tAtt = pMon->m_hashMonSkill[m_strAttackName];

	CAttackObject* pAttackObj = pMon->GetSKillObj();

	int m_iFrame = pMon->GetAnimator()->GetCurAnimation()->GetCurFrame();

	//스킬 오브젝트 수정하기
	//tAtt.m_iStartAttackFrame;
	//pAttackObj->SetColActive(true);
	//
	//tAtt.m_iEndAttackFrame;
	//pAttackObj->SetColActive(false);

}

void CKnightAttack::enter()
{

}

void CKnightAttack::exit()
{
	m_strAttackName = L"";
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	CState::exit();
}

