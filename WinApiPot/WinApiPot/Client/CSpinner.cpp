#include "pch.h"
#include "CSpinner.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CCameraMgr.h"

#include "CCollider.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CGravity.h"

#include "CAnimation.h"
#include "CAnimator.h"

CSpinner::CSpinner()
{
	m_tAttackInfo.m_eAttType = ATTACK_TYPE::NORMAL;
	m_tAttackInfo.m_fAttRcnt = 50.f;
	m_tAttackInfo.m_fAttackDamage = 8.f;
	m_tAttackInfo.m_fAttRigidityTime = 0.5f;
	m_tAttackInfo.m_fAttUpperRcnt = -60.f;

	CreateCollider();

	SetTag(GROUP_TYPE::SPINNER);

	CTexture* CTex = CResMgr::GetInst()->LoadTextur(L"spinner", L"..\\OutPut\\bin_release\\Content\\Object\\spinner.bmp");

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);
	GetAnimator()->CreateAnimation(L"spinner", CTex, Vec2(0.f, 0.f), Vec2(64.f, 206.f), Vec2(64.f, 0.f), Vec2(0.f, 0.f), 0.1f, 4);

	GetAnimator()->Play(L"spinner", true);
}

CSpinner::~CSpinner()
{

}

void CSpinner::render(HDC _dc)
{
	component_render(_dc);
}

void CSpinner::update()
{

}

void CSpinner::finalupdate()
{
	CObject::finalupdate();
}

void CSpinner::OnColliderEnter(CCollider* _pOther)
{

}

void CSpinner::OnColliderExit(CCollider* _pOther)
{

}

void CSpinner::OnCollision(CCollider* _pOther)
{

}
