#include "pch.h"
#include "CRobotEx8.h"

#include "CCameraMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
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
	m_eState(ROBOTSTATE::WAIT),
	m_iDirX(1),
	m_tInfo{},
	m_fDeleteTime(4.f),
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

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"ex8ex_wait_right", pRxTextRight, Vec2(0.f, 0.f), Vec2(150.f, 150.f), Vec2(150.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"ex8ex_wait_left", pRxTextLeft, Vec2(300.f, 0.f), Vec2(150.f, 150.f), Vec2(-150.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
									 
	GetAnimator()->CreateAnimation(L"ex8ex_Attack_right", pRxTextRight, Vec2(0.f, 150.f), Vec2(150.f, 150.f), Vec2(150.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"ex8ex_Attack_left", pRxTextLeft, Vec2(600.f, 150.f), Vec2(150.f, 150.f), Vec2(-150.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);

	GetAnimator()->Play(L"ex8ex_wait_right", true);
}

CRobotEx8::~CRobotEx8()
{

}

void CRobotEx8::render(HDC _dc)
{
	component_render(_dc);

	//여기 머리 위에 시간 나오게
	if (m_eState == ROBOTSTATE::BOOM ||
		m_eState == ROBOTSTATE::JUMP)
		return;

	render_time(_dc);
}

void CRobotEx8::update()
{
	if (m_bBoomOn)
		return;

	update_state();

	switch (m_eState)
	{
	
	case ROBOTSTATE::WAIT:
	{
		wait();
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

void CRobotEx8::wait()
{
	m_fDeleteTime -= fDT;
	if (0.f >= m_fDeleteTime)
	{
		m_eState = ROBOTSTATE::BOOM;
	}
}


void CRobotEx8::createBoom()
{
	CBoom* pBoom = new CBoom;

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	tAtt.m_fAttackDamage =60.f;
	tAtt.m_fAttRcnt = 300.f;
	tAtt.m_fAttRigidityTime = 1.2f;
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
	if (vDiff.Length() >= 10.f && m_iFrame == 4)
	{
		GetAnimator()->GetCurAnimation()->SetFram(4);
	}
	else if (m_iFrame == 4)
	{
		m_eState = ROBOTSTATE::BOOM;
		return;
	}

	Vec2 vPosition = GetPos();
	vPosition = vPosition + (vDiff.NormalRize() * m_fJumSpeed * 1.5 * fDT);
	//GetRigidBody()->AddForce((Vec2(vDiff.NormalRize() * m_fJumSpeed * 1.5)));
	SetPos(vPosition);

}


void CRobotEx8::render_time(HDC _dc)
{
	if (m_fDeleteTime < 0.f)
		return;
	Vec2 vPos = GetPos();
	vPos.y -= 50.f;
	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

	
	render_second(_dc);

	CTexture* p00Tex = CResMgr::GetInst()->FindTexture(L"ex800");
	TransparentBlt(_dc,
		(int)(vPos.x + 20),
		(int)(vPos.y),
		(int)(p00Tex->Width()),
		(int)(p00Tex->Height()),
		p00Tex->GetDC(),
		(int)0,
		(int)0,
		(int)(p00Tex->Width()),
		(int)(p00Tex->Height()),
		RGB(255, 255, 255));

	render_millisecond(_dc);
}

void CRobotEx8::render_second(HDC _dc)
{
	Vec2 vPos = GetPos();
	vPos.y -= 50.f;
	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

	wstring strSNum = std::to_wstring(((UINT)m_fDeleteTime));
	CTexture* pSTex = CResMgr::GetInst()->FindTexture(L"ex8" + strSNum);//3
	CTexture* pS0Tex = CResMgr::GetInst()->FindTexture(L"ex80");//0


	//초
	TransparentBlt(_dc,
		(int)(vPos.x - 14),
		(int)(vPos.y),
		(int)(pS0Tex->Width()),
		(int)(pS0Tex->Height()),
		pS0Tex->GetDC(),
		(int)0,
		(int)0,
		(int)(pS0Tex->Width()),
		(int)(pS0Tex->Height()),
		RGB(255, 255, 255));

	TransparentBlt(_dc,
		(int)(vPos.x),
		(int)(vPos.y),
		(int)(pSTex->Width()),
		(int)(pSTex->Height()),
		pSTex->GetDC(),
		(int)0,
		(int)0,
		(int)(pSTex->Width()),
		(int)(pSTex->Height()),
		RGB(255, 255, 255));
}

void CRobotEx8::render_millisecond(HDC _dc)
{
	Vec2 vPos = GetPos();
	vPos.y -= 50.f;
	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

	//0.32
	float fms = m_fDeleteTime;
	fms = fms - (UINT)m_fDeleteTime;
	fms *= 100;

	UINT fims = (UINT)fms;
	fims /= 10;

	wstring strMSNum = std::to_wstring((fims));
	CTexture* pSMTex = CResMgr::GetInst()->FindTexture(L"ex8s" + strMSNum);//3

	TransparentBlt(_dc,
		(int)(vPos.x + 26),
		(int)(vPos.y),
		(int)(pSMTex->Width()),
		(int)(pSMTex->Height()),
		pSMTex->GetDC(),
		(int)0,
		(int)0,
		(int)(pSMTex->Width()),
		(int)(pSMTex->Height()),
		RGB(255, 255, 255));

	fims = (UINT)fms;
	fims %= 10;
	strMSNum = std::to_wstring((fims));
	CTexture* pSM1Tex = CResMgr::GetInst()->FindTexture(L"ex8s" + strMSNum);//3
	TransparentBlt(_dc,
		(int)(vPos.x + 37),
		(int)(vPos.y),
		(int)(pSM1Tex->Width()),
		(int)(pSM1Tex->Height()),
		pSM1Tex->GetDC(),
		(int)0,
		(int)0,
		(int)(pSM1Tex->Width()),
		(int)(pSM1Tex->Height()),
		RGB(255, 255, 255));
}

void CRobotEx8::update_state()
{
	wstring strDir = m_iDirX > 0 ? L"_right" : L"_left";

	switch (m_eState)
	{
	case ROBOTSTATE::WAIT:
	{
		wstring strMotion = L"ex8ex_wait" + strDir;
		GetAnimator()->Play(strMotion, true);
	}
	break;

	case ROBOTSTATE::JUMP:
	{
		wstring strMotion = L"ex8ex_Attack" + strDir;
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