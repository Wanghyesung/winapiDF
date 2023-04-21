#include "pch.h"
#include "CFire.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CSkill.h"
#include "CPlayer.h"
#include "CTarget.h"

#include "CCollider.h"

#include "CKeyMgr.h"

#include "CRobotRx78.h"
#include "CScene.h"
#include "CSceneMgr.h"

CFire::CFire():
	CSkillState(SKILL_STATE::FIRE),
	m_pTarget(nullptr),
	m_bFire(false)
{

	SetSKillName(L"Player_skill_Fire_");

	SetSkillTime(2.f);
	SetMP(5.f);

	CreateCollider();
}

CFire::~CFire()
{

}

void CFire::Skillupdate()
{
	if (m_pTarget == nullptr)
		return;
	
	CPlayer* pPLayer = GetSkill()->GetPlayer();
	int iFrame = pPLayer->GetAnimator()->GetCurAnimation()->GetCurFrame();
	if (!m_bFire && iFrame == 3)
	{
		pPLayer->GetAnimator()->GetCurAnimation()->SetFram(3);
	}
	else if (m_bFire && iFrame == -1)
	{
		exit();
	}

	if (KEY_HOLD(KEY::F))
	{
		if (KEY_HOLD(KEY::RIGHT))
			m_pTarget->move(Vec2(300.f, 0.f));
		if (KEY_HOLD(KEY::LEFT))
			m_pTarget->move(Vec2(-300.f, 0.f));
		if (KEY_HOLD(KEY::UP))
			m_pTarget->move(Vec2(0.f, -220.f));
		if (KEY_HOLD(KEY::DOWN))
			m_pTarget->move(Vec2(0.f, 200.f));
	}

	else if (KEY_AWAY(KEY::F))
	{
		m_bFire = true;
		jump_robot();
		DeleteObject(m_pTarget);
	}
}

void CFire::init()
{

}

void CFire::exit()
{
	m_bFire = false;
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(0);
	CSkillState::exit();
}

void CFire::OnColliderEnter(CCollider* _pOther)
{

}

void CFire::OnColliderExit(CCollider* _pOther)
{
	
}

void CFire::enter()
{
	CPlayer* pPLayer = GetSkill()->GetPlayer();
	int iDir = pPLayer->GetPlayerDirX();

	wstring strSkillName = GetSkillName();
	wstring strDir = iDir > 0 ? L"right" : L"left";

	m_strSkillName = strSkillName + strDir;

	create_target();
}

void CFire::OnCollision(CCollider* _pOther)
{

}

void CFire::jump_robot()
{
	const vector<CObject*>& vecRobot =  SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::ROBOT);

	//이미지파일 크기의 반만큼 더
	int x = m_pTarget->m_pTargetTex->Width();
	int y = m_pTarget->m_pTargetTex->Height();

	for (int i = 0; i < vecRobot.size(); ++i)
	{
		if (dynamic_cast<CRobotRx78*>(vecRobot[i]))
		{
			CRobotRx78* pRobot = dynamic_cast<CRobotRx78*>(vecRobot[i]);
			pRobot->m_vTargetPos = m_pTarget->GetPos() + Vec2(x/2, y/2);
			pRobot->m_eState = ROBOTSTATE::JUMP;
			//pRobot->jump(m_pTarget->GetPos());
		}
	}
}

void CFire::create_target()
{
	m_pTarget = new CTarget;
	CPlayer* pPlayer = GetSkill()->GetPlayer();

	Vec2 vPos = pPlayer->GetCollider()->GetFinalPos();
	m_pTarget->SetPos(vPos);

	CreateObject(m_pTarget, GROUP_TYPE::SKILL);
}
