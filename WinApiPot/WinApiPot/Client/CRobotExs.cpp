#include "pch.h"
#include "CRobotExs.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CCollider.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CExsFire.h"

#include "CSound.h"

CRobotExs::CRobotExs():
	m_fDeleteCurTime(0.f),
	m_fDeleteTime(10.f),
	m_iCreateCount(0)
{
	SetTag(GROUP_TYPE::ROBOT);

	CreateCollider();
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	CreateRigidBody();
	CreateGravity();
	//몬스터 정보
	m_tInfo.m_AccHP = 100.f;

	CTexture* pRxTextRight = CResMgr::GetInst()->LoadTextur(L"exs_right", L"..\\OutPut\\bin_release\\Content\\Texture\\exs_right.bmp");
	CTexture* pRxTextLeft = CResMgr::GetInst()->LoadTextur(L"exs_left", L"..\\OutPut\\bin_release\\Content\\Texture\\exs_left.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"exs_right", pRxTextRight, Vec2(0.f, 0.f), Vec2(200.f, 150.f), Vec2(200.f, 0.f), Vec2(0.f, 0.f), 0.14f, 8);
	GetAnimator()->CreateAnimation(L"exs_left", pRxTextLeft, Vec2(1400.f, 0.f), Vec2(200.f, 150.f), Vec2(-200.f, 0.f), Vec2(0.f, 0.f), 0.14f, 8);

	CResMgr::GetInst()->LoadSound(L"p_viper_shot_01", L"..\\OutPut\\bin_release\\Content\\Sound\\p_viper_shot_01.wav");
}

CRobotExs::~CRobotExs()
{

}

void CRobotExs::render(HDC _dc)
{
	component_render(_dc);
}

void CRobotExs::update()
{
	m_fDeleteCurTime += fDT;
	if (m_fDeleteTime <= m_fDeleteCurTime)
	{
		DeleteObject(this);
	}


	int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iFrame == 7 && m_iCreateCount==0)
	{
		create_fire();
		m_iCreateCount = 1;
	}
	else if(iFrame != 7)
	{
		m_iCreateCount = 0;
	}
}

void CRobotExs::finalupdate()
{
	CObject::finalupdate();
}

void CRobotExs::OnColliderEnter(CCollider* _pOther)
{

}

void CRobotExs::OnColliderExit(CCollider* _pOther)
{
}

void CRobotExs::OnCollision(CCollider* _pOther)
{
}

void CRobotExs::init_dir(int _iDir)
{
	m_iDirX = _iDir;

	wstring strDir = _iDir > 0 ? L"_right" : L"_left";
	GetAnimator()->Play(L"exs"+strDir, true);
}

void CRobotExs::create_fire()
{
	CSound* pSound = CResMgr::GetInst()->FindSound(L"p_viper_shot_01");
	pSound->Play(false);

	CExsFire* pFire = new CExsFire;

	Vec2 vCreatePos = GetPos() + Vec2(m_iDirX * 30.f, -40.f);
	pFire->SetPos(vCreatePos);
	pFire->init_dir(m_iDirX);

	CreateObject(pFire, GROUP_TYPE::SKILL);
}
