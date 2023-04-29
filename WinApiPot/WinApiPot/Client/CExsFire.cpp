#include "pch.h"
#include "CExsFire.h"

#include "CCameraMgr.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CGravity.h"

#include "CTexture.h"

#include "CResMgr.h"

CExsFire::CExsFire():
	m_fSpeed(300.f),
	m_fCurTime(0.f),
	m_fDelTime(5.f)
{
	SetTag(GROUP_TYPE::SKILL);

	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	m_pFireballRight = CResMgr::GetInst()->LoadTextur(L"exsBullet_right", L"..\\OutPut\\bin_release\\Content\\emfact\\exs_bullet_right.bmp");
	m_pFireballLeft = CResMgr::GetInst()->LoadTextur(L"exsBullet_left", L"..\\OutPut\\bin_release\\Content\\emfact\\exs_bullet_left.bmp");

	m_tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	m_tAtt.m_fAttackDamage = 25.f;
	m_tAtt.m_fAttRcnt = 200.f;
	m_tAtt.m_fAttRigidityTime = 0.8f;
	m_tAtt.m_fAttUpperRcnt = -200.f;
}

CExsFire::~CExsFire()
{
}

void CExsFire::update()
{
	m_fCurTime += fDT;
	if (m_fCurTime >= m_fDelTime)
	{
		DeleteObject(this);
		return;
	}

	Vec2 vPos = GetPos();
	
	vPos.x += (m_fSpeed * m_iDir * fDT);

	SetPos(vPos);

}

void CExsFire::render(HDC _dc)
{
	CTexture* pBulletTex = m_iDir > 0 ? m_pFireballRight : m_pFireballLeft;

	Vec2 vPos = GetPos();
	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc,
		(int)(vPos.x),
		(int)(vPos.y),
		(int)(pBulletTex->Width()),
		(int)(pBulletTex->Height()),
		pBulletTex->GetDC(),
		(int)0,
		(int)0,
		(int)(pBulletTex->Width()),
		(int)(pBulletTex->Height()),
		RGB(255, 255, 255));

	CObject::component_render(_dc);
}

bool CExsFire::IsSameJumLoc(CCollider* _pOther)
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

void CExsFire::init_dir(int _iDir)
{
	m_iDir = _iDir;

	GetCollider()->SetOffSet(Vec2(35.f, 10.f));
}

void CExsFire::OnColliderEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if (pObj->GetTag() == GROUP_TYPE::MONSTER)
	{
		//점프 상태인지 확인하고 점프상태이면 점프 위치를 기준으로
		if (pObj->GetGravity() != nullptr &&
			pObj->GetGravity()->IsGetGravity())
		{
			if (!IsSameJumLoc(_pOther))
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

void CExsFire::OnColliderExit(CCollider* _pOther)
{
}

void CExsFire::OnCollision(CCollider* _pOther)
{
}
