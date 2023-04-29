#include "pch.h"
#include "CCreateEye.h"

#include "CCollider.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CEvileye.h"

#include "CGravity.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"

#include "CEvilLaser.h"

#include "CSound.h"

CCreateEye::CCreateEye():
	m_bAttackOn(false),
	m_iFrame(0),
	m_iAttackCount(0),
	m_pTarget(nullptr)
{
	CTexture* pTex = CResMgr::GetInst()->LoadTextur(L"eye", L"..\\OutPut\\bin_release\\Content\\emfact\\eye.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"eye", pTex, Vec2(0.f, 0.f), Vec2(90.f, 90.f), Vec2(90.f, 0.f), Vec2(0.f, 0.f), 1.f, 1);
	GetAnimator()->FindAnimation(L"eye")->Create(pTex, Vec2(90.f, 0.f), Vec2(90.f, 90.f), Vec2(90.f, 0.f), Vec2(0.f, 0.f), 0.2f, 9);
	GetAnimator()->FindAnimation(L"eye")->Create(pTex, Vec2(0.f, 90.f), Vec2(90.f, 90.f), Vec2(90.f, 0.f), Vec2(0.f, 0.f), 0.2f, 2);
}

CCreateEye::~CCreateEye()
{

}

void CCreateEye::render(HDC _dc)
{
	component_render(_dc);
}

void CCreateEye::update()
{
	if (m_iFrame == -1)
	{
		DeleteObject(this);
		return;
	}

	GetAnimator()->Play(L"eye", false);

	m_iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
	if (m_iFrame >= 8 && m_iAttackCount == 0)
	{
		create_laser();
		m_iAttackCount++;
	}

}

void CCreateEye::OnColliderEnter(CCollider* _pOther)
{

}

void CCreateEye::OnColliderExit(CCollider* _pOther)
{

}

void CCreateEye::OnCollision(CCollider* _pOther)
{

}

bool CCreateEye::IsSameJumLoc(CCollider* _pOther, CCollider* _pThis)
{
	return false;
}

void CCreateEye::init_pos()
{
	vector<CObject*> vecPlayer = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::PLAYER);

	if (vecPlayer.size() == 0)
		return;
	else
	{
		m_pTarget = (CPlayer*)vecPlayer[0];
	}


	if (m_pTarget->GetGravity()->IsGetGravity())
	{
		SetPos(m_pTarget->GetJumPos());
	}

	else
		SetPos(m_pTarget->GetCollider()->GetFinalPos());
}

void CCreateEye::create_laser()
{
	CEvilLaser* pLaser = new CEvilLaser;
	pLaser->m_pOwner = this;
	pLaser->set_DirUp();
	CSound* pSound = CResMgr::GetInst()->FindSound(L"eye_shot");
	pSound->Play(false);
	CreateObject(pLaser, GROUP_TYPE::MONSTER_SKILL);
	//pLaser->m_pOwner = 
}
