#include "pch.h"
#include "CWalkFire.h"

#include "CSkillMgr.h"
#include "CSkill.h"
#include "CSceneMgr.h"

#include "CCollider.h"
#include "CObject.h"
#include "CPlayer.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CRigidBody.h"

CWalkFire::CWalkFire():
	CSkillState(SKILL_STATE::WALK_FIRE),
	m_iFireCount(22),
	m_iMaxTime(0.15f),
	m_iCurTime(0.f),
	m_iDir(1)
{
	SetSKillName(L"Player_skill_walkfire");
}

CWalkFire::~CWalkFire()
{
}

void CWalkFire::Skillupdate()
{
	wstring strResult = L"Player_skill_walkfire";

	m_iCurTime += fDT;
	CPlayer* pPlayer = GetSkill()->GetPlayer();
	CRigidBody* pRigidy = pPlayer->GetRigidBody();
	//방향을 잡고
	pPlayer->SetPlayerDirX(m_iDir);
	if (KEY_TAP(KEY::Z))
	{
		m_iDir *= -1;
	}
	//속도를 가지는지
	
	if (IS_HOLD_MOVE_KEY)
	{
		strResult += L"_walk";
		if (KEY_HOLD(KEY::LEFT))
			pRigidy->AddForce(Vec2(-200.f,0.f));
		if (KEY_HOLD(KEY::RIGHT))
			pRigidy->AddForce(Vec2(200.f, 0.f));
		if (KEY_HOLD(KEY::DOWN))
			pRigidy->AddForce(Vec2(0.f, 200.f));
		if (KEY_HOLD(KEY::UP))
			pRigidy->AddForce(Vec2(0.f, -200.f));
	}
	else
	{
		strResult += L"_stand";
	}

	if (m_iDir > 0)
	{
		strResult += L"_right";
	}
	else
	{
		strResult += L"_left";
	}

	SetSKillName(strResult);
	

	if (KEY_TAP(KEY::X) || KEY_HOLD(KEY::X) && m_iCurTime>=m_iMaxTime)
	{
		//여기서 쏘고
		pPlayer->CreateBullet(pPlayer);
		--m_iFireCount;
		m_iCurTime = 0.f;
	}

	if (m_iFireCount <= 0)
	{
		CSkillMgr::GetInst()->SetEndSkill(false);
		exit();
		m_iFireCount = 22;
	}

}


void CWalkFire::init()
{
	CreateCollider();
}

void CWalkFire::enter()
{
	CSkillState::enter();
	m_iDir = GetSkill()->GetPlayer()->GetPlayerDirX();
}




