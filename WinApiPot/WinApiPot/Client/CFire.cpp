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
#include "CRobotFire78.h"
#include "CRobotEx8.h"
#include "CScene.h"
#include "CSceneMgr.h"

CFire::CFire():
	CSkillState(SKILL_STATE::FIRE),
	m_pTarget(nullptr),
	m_bFire(false),
	m_vStartPos(Vec2(0.f,0.f))
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
		if (m_bFire)
			return;

		if (KEY_HOLD(KEY::RIGHT))
			m_pTarget->move(Vec2(500.f, 0.f));
		if (KEY_HOLD(KEY::LEFT))
			m_pTarget->move(Vec2(-500.f, 0.f));
		if (KEY_HOLD(KEY::UP))
			m_pTarget->move(Vec2(0.f, -380.f));
		if (KEY_HOLD(KEY::DOWN))
			m_pTarget->move(Vec2(0.f, 380.f));
	}

	else if (KEY_AWAY(KEY::F))
	{
		if (m_bFire)
			return;

		m_bFire = true;
		if (m_vStartPos == m_pTarget->GetPos())
			fire_robot();
		else
			jump_robot();

		DeleteObject(m_pTarget);
	}
}

void CFire::init()
{

}

void CFire::exit()
{
	m_vStartPos = Vec2(0.f, 0.f);
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

	m_vStartPos = m_pTarget->GetPos();
}

void CFire::OnCollision(CCollider* _pOther)
{

}

void CFire::jump_robot()
{
	const vector<CObject*>& vecRobot =  SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::ROBOT);
	if (vecRobot.size() == 0)
		return;

	//이미지파일 크기의 반만큼 더
	int x = m_pTarget->m_pTargetTex->Width();
	int y = m_pTarget->m_pTargetTex->Height();

	for (int i = 0; i < vecRobot.size(); ++i)
	{
		if (dynamic_cast<CRobotRx78*>(vecRobot[i]))
		{
			CRobotRx78*  pRobot = dynamic_cast<CRobotRx78*>(vecRobot[i]);
			if (pRobot->m_eState == ROBOTSTATE::ATTACK)
				continue;

			pRobot->m_vTargetPos = m_pTarget->GetPos() + Vec2(x / 2, y / 2);

			if ((pRobot->m_vTargetPos - pRobot->GetPos()).x > 0.f)
				pRobot->m_iDirX = 1;
			else
				pRobot->m_iDirX = -1;

			pRobot->m_eState = ROBOTSTATE::JUMP;
		}
			
		else if (dynamic_cast<CRobotFire78*>(vecRobot[i]))
		{
			CRobotFire78* pRobot = dynamic_cast<CRobotFire78*>(vecRobot[i]);
			if (pRobot->m_eState == ROBOTSTATE::ATTACK)
				continue;

			pRobot->m_vTargetPos = m_pTarget->GetPos() + Vec2(x / 2, y / 2);

			if ((pRobot->m_vTargetPos - pRobot->GetPos()).x > 0.f)
				pRobot->m_iDirX = 1;
			else
				pRobot->m_iDirX = -1;

			pRobot->m_eState = ROBOTSTATE::JUMP;
		}

		if (dynamic_cast<CRobotEx8*>(vecRobot[i]))
		{
			CRobotEx8* pRobot = dynamic_cast<CRobotEx8*>(vecRobot[i]);
			pRobot->m_vTargetPos = m_pTarget->GetPos() + Vec2(x / 2, y / 2);

			if ((pRobot->m_vTargetPos - pRobot->GetPos()).x > 0.f)
				pRobot->m_iDirX = 1;
			else
				pRobot->m_iDirX = -1;
			pRobot->m_eState = ROBOTSTATE::JUMP;
		}
	}
}

void CFire::fire_robot()
{
	const vector<CObject*>& vecRobot = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::ROBOT);

	for (int i = 0; i < vecRobot.size(); ++i)
	{

		if (dynamic_cast<CRobotRx78*>(vecRobot[i]))
		{
			CRobotRx78* pRobot = dynamic_cast<CRobotRx78*>(vecRobot[i]);
			if (pRobot->m_eState == ROBOTSTATE::ATTACK)
				continue;

			pRobot->m_eState = ROBOTSTATE::BOOM;
		}

		else if (dynamic_cast<CRobotFire78*>(vecRobot[i]))
		{
			CRobotFire78* pRobot = dynamic_cast<CRobotFire78*>(vecRobot[i]);
			if (pRobot->m_eState == ROBOTSTATE::ATTACK)
				continue;

			pRobot->m_eState = ROBOTSTATE::BOOM;
		}

		if (dynamic_cast<CRobotEx8*>(vecRobot[i]))
		{
			CRobotEx8* pRobot = dynamic_cast<CRobotEx8*>(vecRobot[i]);
			
			pRobot->m_eState = ROBOTSTATE::BOOM;
		}
	}

}

void CFire::create_target()
{
	m_pTarget = new CTarget;
	CPlayer* pPlayer = GetSkill()->GetPlayer();

	Vec2 vPos = pPlayer->GetCollider()->GetFinalPos();
	vPos.x -= 110.f;
	m_pTarget->SetPos(vPos);

	CreateObject(m_pTarget, GROUP_TYPE::SKILL);
}
