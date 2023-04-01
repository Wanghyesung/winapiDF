#include "pch.h"
#include "CStoneState.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CMonster.h"


CStoneState::CStoneState():
	CState(MONSTER_STATE::STONE)
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
	Vec2 vPlayerPos = SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj()->GetPos();

	Vec2 vDiff = vPlayerPos - vPos;

	if (vDiff.Length() <= tMInfo.m_fnavigationScope)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}

}
