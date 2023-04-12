#include "pch.h"
#include "CNaiasAttack.h"

#include "AI.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CMonster.h"
#include "CPlayer.h"

#include "CNaias.h"
#include "CAttackObject.h"

#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CScene.h"

#include "CSound.h"

CNaiasAttack::CNaiasAttack():
	CState(MONSTER_STATE::ATTACK)
{
}

CNaiasAttack::~CNaiasAttack()
{
}

void CNaiasAttack::SetAttackName(const wstring& _strName)
{
	m_strAttackName = _strName;
	CNaias* pMon = (CNaias*)GetMonster();
	tNew_Attack& tAtt = pMon->m_hashMonSkill[m_strAttackName];
	tAtt.m_fSkillTime = tAtt.m_fSkillMaxTime;
	m_tNightAttackInfo = pMon->m_hashMonSkill[m_strAttackName];
}

void CNaiasAttack::update()
{
	CNaias* pMon = (CNaias*)GetMonster();
	tNew_Attack& tAtt = pMon->m_hashMonSkill[m_strAttackName];

	CAttackObject* pAttackObj = pMon->GetSKillObj();

	Vec2 vPos = pMon->GetPos();
	Vec2 vPlayerPos;

	int m_iFrame = pMon->GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (m_iFrame == -1)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
		return;
	}

	if (m_iFrame == tAtt.m_iStartAttackFrame && m_iAttackCount < 1)
	{
		++m_iAttackCount;
		pAttackObj->SetColActive(true);
		pAttackObj->SetAttInfo(m_tNightAttackInfo.m_tAttackInfo);
		pAttackObj->SetAttackRange(tAtt.m_vOffset.x, tAtt.m_vAttackSacle);
	}
	else if (m_iFrame == tAtt.m_iEndAttackFrame)
	{
		pAttackObj->SetColActive(false);
	}

}

void CNaiasAttack::enter()
{
	//GetAnimSound()->Play(false);

	CNaias* pMon = (CNaias*)GetMonster();

	Vec2 vPos = pMon->GetPos();
	Vec2 vPlayerPos;

	vector<CObject*> vecPlayer = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::PLAYER);
	if (vecPlayer.size() == 0)
		return;
	else
	{
		vPlayerPos = vecPlayer[0]->GetPos();
	}
	Vec2 vDiff = (vPlayerPos - vPos);//길이값 

	int iDir = 0;//방향값
	vDiff.x > 0 ? iDir = 1 : iDir = -1;
	SetDir(iDir);
}

void CNaiasAttack::exit()
{
	m_iAttackCount = 0;
	m_strAttackName = L"";
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	CState::exit();
}
