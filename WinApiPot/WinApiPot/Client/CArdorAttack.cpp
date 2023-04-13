#include "pch.h"
#include "CArdorAttack.h"

#include "AI.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CMonster.h"
#include "CPlayer.h"


#include "CAttackObject.h"

#include "CArdor.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CScene.h"

#include "CSound.h"

CArdorAttack::CArdorAttack():
	CState(MONSTER_STATE::ATTACK)
{
}

CArdorAttack::~CArdorAttack()
{
}

void CArdorAttack::SetAttackName(const wstring& _strName)
{
	m_strAttackName = _strName;
	CArdor* pMon = (CArdor*)GetMonster();
	tNew_Attack& tAtt = pMon->m_hashMonSkill[m_strAttackName];
	tAtt.m_fSkillTime = tAtt.m_fSkillMaxTime;
	m_tNightAttackInfo = pMon->m_hashMonSkill[m_strAttackName];
}

void CArdorAttack::update()
{
	CArdor* pMon = (CArdor*)GetMonster();
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

void CArdorAttack::enter()
{
	GetAnimSound()->Play(false);

	CArdor* pMon = (CArdor*)GetMonster();
	
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

void CArdorAttack::exit()
{
	m_iAttackCount = 0;
	m_strAttackName = L"";
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	CState::exit();
}
