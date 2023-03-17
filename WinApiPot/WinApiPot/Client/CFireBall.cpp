#include "pch.h"
#include "CFireBall.h"

#include "CCameraMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CCollider.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CGravity.h"

CFireBall::CFireBall(int iDir, Vec2 _vPos) :
	m_vPos(_vPos),
	m_iDir(iDir),
	m_fSpeed(200.f),
	m_fCurTime(0.f),
	m_fDelTime(4.f)
{
	SetName(L"FireBall");
	SetTag(GROUP_TYPE::MONSTER_SKILL);


	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));
	

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);
	m_pFireballRight = CResMgr::GetInst()->LoadTextur(L"Dragon_Fireball_right", L"..\\OutPut\\bin_release\\Content\\Texture\\Fireball_right.bmp");
	m_pFireballLeft = CResMgr::GetInst()->LoadTextur(L"Dragon_Fireball_left", L"..\\OutPut\\bin_release\\Content\\Texture\\Fireball_left.bmp");

	//불
	GetAnimator()->CreateAnimation(L"Dragon_Fireball_right", m_pFireballRight, Vec2(0.f, 0.f), Vec2(63.f, 49.f), Vec2(63.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"Dragon_Fireball_left", m_pFireballLeft, Vec2(315.f, 0.f), Vec2(63.f, 49.f), Vec2(-63.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);


}

CFireBall::~CFireBall()
{


}

void CFireBall::update()
{
	m_vPos.x += (m_iDir * m_fSpeed * fDT);
	m_fCurTime += fDT;

	if (m_fCurTime >= m_fDelTime)
	{
		DeleteObject(this);
		return;
	}

	wstring sAnimName = L"Dragon_Fireball";

	m_iDir >= 0 ? sAnimName += L"_right" : sAnimName += L"_left";
	GetAnimator()->Play(sAnimName, true);

	SetPos(m_vPos);
}

void CFireBall::render(HDC _dc)
{
	component_render(_dc);
}

bool CFireBall::IsSameJumLoc(CCollider* _pOther, CCollider* _pThis)
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

void CFireBall::OnColliderEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if (pObj->GetTag() == GROUP_TYPE::PLAYER)
	{
		//점프 상태인지 확인하고 점프상태이면 점프 위치를 기준으로

		if (pObj->GetGravity()->IsGetGravity())
		{
			if(!IsSameJumLoc(_pOther, GetCollider()))
				return;
			else
				DeleteObject(this);
		}
		else
		{
			DeleteObject(this);
		}
		
	}
}

void CFireBall::OnColliderExit(CCollider* _pOther)
{
}

void CFireBall::OnCollision(CCollider* _pOther)
{
}
