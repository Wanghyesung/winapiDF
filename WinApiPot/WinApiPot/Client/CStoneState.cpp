#include "pch.h"
#include "CStoneState.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CMonster.h"


CStoneState::CStoneState():
	CState(MONSTER_STATE::STONE),
	m_bStart(false)
{

}

CStoneState::~CStoneState()
{

}

void CStoneState::enter()
{

}

void CStoneState::exit()
{
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	CState::exit();
}

void CStoneState::update()
{
	CMonster* pMon = GetMonster();
	tMonInfo& tMInfo = pMon->GetMonInfo();

	Vec2 vPos = pMon->GetPos();
	Vec2 vPlayerPos;
	vector<CObject*> vecPlayer = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::PLAYER);
	if (vecPlayer.size() == 0)
		return;
	else
	{
		vPlayerPos = vecPlayer[0]->GetPos();
	}

	Vec2 vDiff = vPlayerPos - vPos;

	if (tMInfo.m_fnavigationScope >= vDiff.Length())
		m_bStart = true;
	
	if(!m_bStart)
		GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);

	int iFrame = pMon->GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iFrame == -1)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}

	//if (vDiff.Length() <= tMInfo.m_fnavigationScope)
	//{
	//	ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	//}
	

}
