#include "pch.h"
#include "CRobotFire78.h"

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


CRobotFire78::CRobotFire78() :
	m_eState(ROBOTSTATE::TRACE),
	m_iDirX(1),
	m_pTarget(nullptr),
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

	CTexture* pRxTextRight = CResMgr::GetInst()->LoadTextur(L"Firerx78_right", L"..\\OutPut\\bin_release\\Content\\Texture\\Firerx-78_right.bmp");
	CTexture* pRxTextLeft = CResMgr::GetInst()->LoadTextur(L"Firerx78_left", L"..\\OutPut\\bin_release\\Content\\Texture\\Firerx-78_left.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Firerx78_Run_right", pRxTextRight, Vec2(0.f, 0.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"Firerx78_Run_left", pRxTextLeft, Vec2(500.f, 0.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 6);

	GetAnimator()->CreateAnimation(L"Firerx78_Attack_right", pRxTextRight, Vec2(0.f, 100.f), Vec2(100.f, 100.f), Vec2(100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"Firerx78_Attack_left", pRxTextLeft, Vec2(500.f, 100.f), Vec2(100.f, 100.f), Vec2(-100.f, 0.f), Vec2(0.f, 0.f), 0.1f, 4);

	GetAnimator()->Play(L"Firerx78_Run_right", true);
}

CRobotFire78::~CRobotFire78()
{

}

void CRobotFire78::render(HDC _dc)
{
	component_render(_dc);
}

void CRobotFire78::update()
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
	case ROBOTSTATE::TRACE:
	{
		trace();
	}
	break;
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

void CRobotFire78::finalupdate()
{
	CObject::finalupdate();
}


void CRobotFire78::attack()
{

	if (m_pTarget == nullptr)
	{
		if (!setTarget());
		return;
	}

	int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iFrame == 3)
	{
		m_eState = ROBOTSTATE::BOOM;
	}

	else
	{
		if (m_pTarget->GetMonInfo().m_iHp <= 0.f)
			return;
		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vTargetPos = m_pTarget->GetCollider()->GetFinalPos();

		Vec2 vDiff = vTargetPos - vPos;

		GetRigidBody()->AddForce(vDiff.NormalRize() * 100.f);
	}

}

void CRobotFire78::createBoom()
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

void CRobotFire78::jump()
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

	Vec2 vPosition = GetPos();
	vPosition = vPosition + (vDiff.NormalRize() * m_fJumSpeed * 1.5 * fDT);
	//GetRigidBody()->AddForce((Vec2(vDiff.NormalRize() * m_fJumSpeed * 1.5)));
	SetPos(vPosition);
}

void CRobotFire78::trace()
{

	if (m_pTarget == nullptr || !m_pTarget->IsActiv())
	{
		if (!setTarget());
		return;
	}

	if (m_pTarget->GetMonInfo().m_iHp <= 0.f)
	{
		setTarget();
		return;
	}

	Vec2 vPos = GetCollider()->GetFinalPos();
	Vec2 vTargetPos = m_pTarget->GetCollider()->GetFinalPos();

	Vec2 vDiff = vTargetPos - vPos;

	vDiff.x > 0 ? m_iDirX = 1 : m_iDirX = -1;

	GetRigidBody()->AddForce(vDiff.NormalRize() * m_tInfo.m_fspeed);
}


bool CRobotFire78::setTarget()
{
	const vector<CObject*>& vecMonster = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::MONSTER);

	//내 탐색 범위에서 제일 가까운 몬스터로 이동
	float fMinValue = m_tInfo.m_fnavigationScope;

	if (vecMonster.size() == 0)
		return false;

	for (int i = 0; i < vecMonster.size(); ++i)
	{
		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vTarget = vecMonster[i]->GetCollider()->GetFinalPos();

		Vec2 vDiff = vTarget - vPos;
		if (vDiff.Length() <= fMinValue)
		{
			fMinValue = vDiff.Length();

			if (vecMonster[i]->IsDead())
				continue;

			m_pTarget = (CMonster*)vecMonster[i];
		}
	}

	//if (m_pTarget != nullptr)
	//{
	//	Vec2 vPos = GetCollider()->GetFinalPos();
	//	Vec2 vTargetPos = m_pTarget->GetCollider()->GetFinalPos();
	//
	//	Vec2 vDiff = vTargetPos - vPos;
	//
	//	vDiff.x > 0 ? m_iDirX = 1 : m_iDirX = -1;
	//}

	if (fMinValue == m_tInfo.m_fnavigationScope)
		return false;
	else
		return true;
}

void CRobotFire78::update_state()
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

void CRobotFire78::OnColliderEnter(CCollider* _pOther)
{
	if (m_iAttackCount == 1 || m_eState == ROBOTSTATE::JUMP)
		return;

	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER && m_iAttackCount == 0)
	{
		++m_iAttackCount;
		m_eState = ROBOTSTATE::ATTACK;

		if (GetGravity()->IsGetGravity())
		{
			GetGravity()->SetGravity(false);
		}
	}
}

void CRobotFire78::OnColliderExit(CCollider* _pOther)
{

}

void CRobotFire78::OnCollision(CCollider* _pOther)
{
	if (m_iAttackCount == 1 || m_eState == ROBOTSTATE::JUMP)
		return;

	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER && m_iAttackCount == 0)
	{
		++m_iAttackCount;
		m_eState = ROBOTSTATE::ATTACK;

		if (GetGravity()->IsGetGravity())
		{
			GetGravity()->SetGravity(false);
		}
	}
}