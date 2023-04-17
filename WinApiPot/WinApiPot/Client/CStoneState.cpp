#include "pch.h"
#include "CStoneState.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CMonster.h"

#include "CTimeMgr.h"

CStoneState::CStoneState() :
	CState(MONSTER_STATE::STONE),
	m_bStart(false),
	m_fCurTime(0.f),
	m_fMoveTime(0.2f),
	m_fMoveValue(2.f),
	m_iMoveDir(1),
	m_vStartPos(Vec2(0.f,0.f))
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
	if (m_vStartPos == Vec2(0.f, 0.f))
		m_vStartPos = pMon->GetPos();

	m_fCurTime -= fDT;

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
		pMon->GetAnimator()->GetCurAnimation()->SetFram(0);

	int iFrame = pMon->GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iFrame == -1)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	}
	else
	{
		if (m_fCurTime <= 0.f && m_bStart)
		{
		 	float fValue = m_vStartPos.x + m_iMoveDir * m_fMoveValue;
			m_iMoveDir *= -1;
			m_fCurTime = m_fMoveTime;
			GetMonster()->SetPos(Vec2(fValue,m_vStartPos.y));
		}
	}

	//if (vDiff.Length() <= tMInfo.m_fnavigationScope)
	//{
	//	ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
	//}
	

}
