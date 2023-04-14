#include "pch.h"
#include "CEvilLaser.h"

#include "CCollider.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CEvileye.h"

#include "CGravity.h"

CEvilLaser::CEvilLaser():
	m_pOwner(nullptr),
	m_bAttackOn(false),
	m_iDir(0),
	m_tAtt{}
{
	SetTag(GROUP_TYPE::MONSTER_SKILL);

	CreateCollider();
	GetCollider()->SetScale(Vec2(820.f, 50.f));

	CTexture* pTex_right = CResMgr::GetInst()->LoadTextur(L"Evil_laser_right", L"..\\OutPut\\bin_release\\Content\\emfact\\monLaser_right.bmp");
	CTexture* pTex_left = CResMgr::GetInst()->LoadTextur(L"Evil_laser_left", L"..\\OutPut\\bin_release\\Content\\emfact\\monLaser_left.bmp");
	CTexture* pTex_up = CResMgr::GetInst()->LoadTextur(L"Evil_laser_up", L"..\\OutPut\\bin_release\\Content\\emfact\\monLaser_up.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Evil_laser_right", pTex_right, Vec2(0.f, 0.f), Vec2(900.f, 160.f), Vec2(0.f, 160.f), Vec2(0.f, 0.f), 0.15f, 4);
	GetAnimator()->CreateAnimation(L"Evil_laser_left", pTex_left, Vec2(0.f, 0.f), Vec2(900.f, 160.f), Vec2(0.f, 160.f), Vec2(0.f, 0.f), 0.15f, 4);
	GetAnimator()->CreateAnimation(L"Evil_laser_up", pTex_up, Vec2(0.f, 0.f), Vec2(160.f, 900.f), Vec2(160.f, 0.f), Vec2(4.f, -410.f), 0.15f, 4);


	m_tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	m_tAtt.m_fAttackDamage = 10.f;
	m_tAtt.m_fAttRcnt = 50.f;
	m_tAtt.m_fAttUpperRcnt = -60.f;
	m_tAtt.m_fAttRigidityTime = 0.5f;
}

CEvilLaser::~CEvilLaser()
{

}

void CEvilLaser::render(HDC _dc)
{
	component_render(_dc);
}

void CEvilLaser::update()
{
	if (m_pOwner == nullptr)
	{
		DeleteObject(this);
		return;
	}

	Vec2 vEvilPos = m_pOwner->GetPos();
	
	//int iDir = 0;
	//if (m_strLaserDir == L"_right")
	//	iDir = 1;
	//else
	//	iDir = -1;
	
	float fOffsetX = m_iDir * 450.f;
	vEvilPos.x += fOffsetX;
	//float fOffsetY = 1 * 450.f;
	//vEvilPos.y -= fOffsetY;
	SetPos(vEvilPos);

	GetAnimator()->Play(L"Evil_laser" + m_strLaserDir, false);
	m_iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
	if (m_iFrame == -1)
	{
		DeleteObject(this);
		return;
	}
}

void CEvilLaser::OnColliderEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::PLAYER)
	{
		if (pObj->GetGravity()->IsGetGravity())
		{
			if (!IsSameJumLoc(_pOther, GetCollider()))
				return;
		}

		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		if (m_iFrame != iFrame)
		{
			//한 프레임당 한번씩만 맞게
			m_bAttackOn = true;
			m_iFrame = iFrame;
		}
		else
		{
			m_bAttackOn = false;
		}

	}
}

void CEvilLaser::OnColliderExit(CCollider* _pOther)
{

}

void CEvilLaser::OnCollision(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::PLAYER)
	{
		if (pObj->GetGravity()->IsGetGravity())
		{
			if (!IsSameJumLoc(_pOther, GetCollider()))
				return;
		}

		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		if (m_iFrame != iFrame)
		{
			//한 프레임당 한번씩만 맞게
			m_bAttackOn = true;
			m_iFrame = iFrame;
		}
		else
		{
			m_bAttackOn = false;
		}

	}
}

bool CEvilLaser::IsSameJumLoc(CCollider* _pOther, CCollider* _pThis)
{
	Vec2 vOffset = _pOther->GetOffSetPos();//상대 offset
	Vec2 vJumPos = _pOther->GetObj()->GetJumPos() + vOffset; //상대 점프위치 + offset
	Vec2 vOtherScale = _pOther->GetScale();

	Vec2 vScale = GetCollider()->GetScale();
	Vec2 vPos = GetCollider()->GetFinalPos();

	if (abs(vPos.x - vJumPos.x) > abs((vScale.x + vOtherScale.x) / 2.f) ||
		abs(vPos.y - vJumPos.y) > abs((vScale.y + vOtherScale.y) / 2.f))
	{
		return false;
	}

	return true;
}

void CEvilLaser::setDir(int _iDir)
{
	m_iDir = _iDir;
	GetCollider()->SetOffSet(Vec2(m_iDir * 40.f, 0.f));
}

void CEvilLaser::set_DirUp()
{
	GetCollider()->SetScale(Vec2(50.f, 820.f));
	//위쪽으로
	GetCollider()->SetOffSet(Vec2(0.f,-430.f));
	m_strLaserDir = L"_up";
	m_iDir = 0;
}
