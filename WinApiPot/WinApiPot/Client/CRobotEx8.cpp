#include "pch.h"
#include "CRobotEx8.h"

#include "CTimeMgr.h"

#include "CResMgr.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "CRigidBody.h"
#include "CGravity.h"

#include "CObject.h"
#include "CMonster.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CBoom.h"


CRobotEx8::CRobotEx8() :
	m_eState(ROBOTSTATE::TRACE),
	m_iDirX(1),
	m_tInfo{},
	m_fDeleteTime(7.f),
	m_fDeleteCurTime(0.f),
	m_iAttackCount(0),
	m_bBoomOn(false),
	m_bJumOn(false),
	m_vTargetPos(Vec2(0.f, 0.f))
{
	SetTag(GROUP_TYPE::ROBOT);

	CreateCollider();
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	CreateRigidBody();
	CreateGravity();
	//몬스터 정보
	m_tInfo.m_AccHP = 100.f;
	m_tInfo.m_fnavigationScope = 500.f;
	m_tInfo.m_fspeed = 150.f;

	CTexture* pRxTextRight = CResMgr::GetInst()->LoadTextur(L"ex8ex-78_right", L"..\\OutPut\\bin_release\\Content\\Texture\\ex8ex-78_right.bmp");
	CTexture* pRxTextLeft = CResMgr::GetInst()->LoadTextur(L"ex8ex-78_left", L"..\\OutPut\\bin_release\\Content\\Texture\\ex8ex-78_left.bmp");

	//크기
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Firerx78_Run_right", pRxTextRight, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"Firerx78_Run_left", pRxTextLeft, Vec2(500.f, 0.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 6);

	GetAnimator()->CreateAnimation(L"Firerx78_Attack_right", pRxTextRight, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"Firerx78_Attack_left", pRxTextLeft, Vec2(500.f, 100.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 4);

	GetAnimator()->Play(L"Firerx78_Run_right", true);
}

CRobotEx8::~CRobotEx8()
{

}

void CRobotEx8::render(HDC _dc)
{
	component_render(_dc);
}

void CRobotEx8::update()
{
	if (m_bBoomOn)
		return;


	m_fDeleteCurTime += fDT;
	if (m_fDeleteCurTime >= m_fDeleteTime)
	{
		m_eState = ROBOTSTATE::BOOM;
	}

	update_state();

	switch (m_eState)
	{
	
	case ROBOTSTATE::ATTACK:
	{
		attack();
	}
	break;
	case ROBOTSTATE::BOOM:
	{
		createBoom();
	}
	break;

	case ROBOTSTATE::JUMP:
	{
		jump();
	}


	}
}

void CRobotEx8::finalupdate()
{
	CObject::finalupdate();
}


void CRobotEx8::attack()
{
	int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iFrame == 3)
	{
		m_eState = ROBOTSTATE::BOOM;
	}
}


void CRobotEx8::createBoom()
{
	CBoom* pBoom = new CBoom;

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	tAtt.m_fAttackDamage = 50.f;
	tAtt.m_fAttRcnt = 200.f;
	tAtt.m_fAttRigidityTime = 1.f;
	tAtt.m_fAttUpperRcnt = -200.f;

	pBoom->SetAttackInfo(tAtt);

	Vec2 vPos = GetCollider()->GetFinalPos();
	pBoom->SetPos(vPos);
	CreateObject(pBoom, GROUP_TYPE::SKILL);

	m_bBoomOn = true;
	DeleteObject(this);
}

void CRobotEx8::jump()
{

	Vec2 vPos = GetCollider()->GetFinalPos();
	Vec2 vDiff = m_vTargetPos - vPos;

	if (!m_bJumOn)
	{
		m_bJumOn = true;
		m_fJumSpeed = vDiff.Length();
	}

	int m_iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
	if (vDiff.Length() >= 10.f && m_iFrame == 3)
	{
		GetAnimator()->GetCurAnimation()->SetFram(3);
	}
	else if (m_iFrame == 3)
	{
		m_eState = ROBOTSTATE::BOOM;
		return;
	}

	GetRigidBody()->AddForce((Vec2(vDiff.NormalRize() * m_fJumSpeed * 1.5)));

}


void CRobotEx8::update_state()
{
	wstring strDir = m_iDirX > 0 ? L"_right" : L"_left";

	switch (m_eState)
	{
	case ROBOTSTATE::TRACE:
	{
		wstring strMotion = L"Firerx78_Run" + strDir;
		GetAnimator()->Play(strMotion, true);
	}
	break;

	case ROBOTSTATE::ATTACK:
	{
		wstring strMotion = L"Firerx78_Attack" + strDir;
		GetAnimator()->Play(strMotion, false);
	}
	break;

	case ROBOTSTATE::JUMP:
	{
		wstring strMotion = L"Firerx78_Attack" + strDir;
		GetAnimator()->Play(strMotion, false);
	}
	}
}

void CRobotEx8::OnColliderEnter(CCollider* _pOther)
{
	
}

void CRobotEx8::OnColliderExit(CCollider* _pOther)
{

}

void CRobotEx8::OnCollision(CCollider* _pOther)
{

}