#include "pch.h"
#include "CDeadState.h"

#include "CMonster.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "AI.h"
#include "CSound.h"
#include "CInterfaceMgr.h"
#include "CItemMgr.h"

CDeadState::CDeadState():
	CState(MONSTER_STATE::DEAD),
	m_iCurFrame(0)
{

}

CDeadState::~CDeadState()
{

}

void CDeadState::update()
{
	//프레임 다 돌면 -1
	if (m_iCurFrame == -1)
	{
		GetMonster()->SetDead();
		
		wstring strMonName = GetMonster()->GetName();
		CInterfaceMgr::GetInst()->deleteInterface(strMonName);
		//아이템 생성
		Vec2 vItemPos = GetMonster()->GetPos();
		CItemMgr::GetInst()->CreateItem(vItemPos);
	}
}

void CDeadState::enter()
{
	if(GetAI()->GetPreState()->GetType() != MONSTER_STATE::DEAD)
		GetAnimSound()->Play(false);
}

void CDeadState::exit()
{
	CState::exit();
}
