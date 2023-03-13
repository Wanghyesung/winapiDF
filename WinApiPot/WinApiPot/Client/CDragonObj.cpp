#include "pch.h"
#include "CDragonObj.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CCameraMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CGravity.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CSkillState.h"
#include "CBullet.h"

CDragonObj::CDragonObj():
	m_bActive(true),
	m_fHp(100.f),
	m_fCurTime(0.f),
	m_fTime(5.f)
{
	SetTag(GROUP_TYPE::STONE_BOX);

	CreateCollider();
	
	GetCollider()->SetScale(Vec2(50.f, 50.f));
	GetCollider()->SetOffSet(Vec2(0.f, 20.f));


	//GetAnimator()->CreateAnimation();
	CTex = CResMgr::GetInst()->LoadTextur(L"dragonObj", L"..\\OutPut\\bin_release\\Content\\Object\\dragon.bmp");
	CTex1 = CResMgr::GetInst()->LoadTextur(L"dragonObj1", L"..\\OutPut\\bin_release\\Content\\Object\\dragon_1.bmp");

	CreateAnimator();

}

CDragonObj::~CDragonObj()
{

}

void CDragonObj::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

	if (m_bActive)
	{
		TransparentBlt(_dc,
			(int)(vPos.x - CTex->Width() / 2.f),
			(int)(vPos.y - CTex->Height() / 2.f),
			(int)(CTex->Width()),
			(int)(CTex->Height()),
			CTex->GetDC(),
			(int)0,
			(int)0,
			(int)(CTex->Width()),
			(int)(CTex->Height()),
			RGB(0, 0, 0));
	}
	else
	{
		TransparentBlt(_dc,
			(int)(vPos.x - CTex1->Width() / 2.f),
			(int)(vPos.y - CTex1->Height() / 2.f),
			(int)(CTex1->Width()),
			(int)(CTex1->Height()),
			CTex1->GetDC(),
			(int)0,
			(int)0,
			(int)(CTex1->Width()),
			(int)(CTex1->Height()),
			RGB(0, 0, 0));
	}
	component_render(_dc);
}

void CDragonObj::update()
{
	m_fCurTime += fDT;
	if (m_fCurTime <= m_fTime)
	{
		m_fCurTime = 0.f;
		//불덩이
	}
}

void CDragonObj::finalupdate()
{
	CObject::finalupdate();
}

void CDragonObj::OnColliderEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if ((pObj->GetTag() == GROUP_TYPE::BULLET ||
		pObj->GetTag() == GROUP_TYPE::SKILL) && m_bActive)
	{
		if (dynamic_cast<CBullet*>(pObj))
		{
			CBullet* pBullet = dynamic_cast<CBullet*>(pObj);
			m_fHp -= pBullet->GetAttInfo().m_fAttackDamage;
		}
		else
		{
			CSkillState* pSkill = dynamic_cast<CSkillState*>(pObj);
			m_fHp -= pSkill->GetAttInfo().m_fAttackDamage;
		}

		if (m_fHp <= 0.f)
			m_bActive = false;
	}

	if (pObj->GetTag() == GROUP_TYPE::PLAYER)
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//내 위치 크기
		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		//상대 위치 크기
		Vec2 vOtherPos = _pOther->GetFinalPos();
		Vec2 vPlayerScale = _pOther->GetScale();
		Vec2 vJumPos = pPlayer->GetJumPos();



		if (!pPlayer->GetGravity()->IsGetGravity())
		{
			float fLenX = abs(vPos.x - vOtherPos.x);
			float fLenY = abs(vPos.y - vOtherPos.y);

			float fValueX = ((vScale.x + vPlayerScale.x) / 2.f) - fLenX;
			float fValueY = ((vScale.y + vPlayerScale.y) / 2.f) - fLenY;

			Vec2 vPlayerPos = pPlayer->GetPos();

			int iDir = 0;
			if (fValueX <= fValueY)
			{
				(vPos.x - vOtherPos.x) > 0 ? iDir = 1 : iDir = -1;
				vPlayerPos.x -= iDir * fValueX;
			}
			else
			{
				(vPos.y - vOtherPos.y) > 0 ? iDir = 1 : iDir = -1;
				vPlayerPos.y -= iDir * fValueY;
			}

			pPlayer->SetPos(vPlayerPos);

		}
	}
}

void CDragonObj::OnColliderExit(CCollider* _pOther)
{

}

void CDragonObj::OnCollision(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if ((pObj->GetTag() == GROUP_TYPE::BULLET ||
		pObj->GetTag() == GROUP_TYPE::SKILL) && m_bActive)
	{
		if (dynamic_cast<CBullet*>(pObj))
		{
			CBullet* pBullet = dynamic_cast<CBullet*>(pObj);
			m_fHp -= pBullet->GetAttInfo().m_fAttackDamage;
		}
		else
		{
			CSkillState* pSkill = dynamic_cast<CSkillState*>(pObj);
			m_fHp -= pSkill->GetAttInfo().m_fAttackDamage;
		}

		if (m_fHp <= 0.f)
			m_bActive = false;
	}

	if (pObj->GetTag() == GROUP_TYPE::PLAYER)
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);

		//내 위치 크기
		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		//상대 위치 크기
		Vec2 vOtherPos = _pOther->GetFinalPos();
		Vec2 vPlayerScale = _pOther->GetScale();
		Vec2 vJumPos = pPlayer->GetJumPos();



		if (!pPlayer->GetGravity()->IsGetGravity())
		{
			float fLenX = abs(vPos.x - vOtherPos.x);
			float fLenY = abs(vPos.y - vOtherPos.y);

			float fValueX = ((vScale.x + vPlayerScale.x) / 2.f) - fLenX;
			float fValueY = ((vScale.y + vPlayerScale.y) / 2.f) - fLenY;

			Vec2 vPlayerPos = pPlayer->GetPos();

			int iDir = 0;
			if (fValueX <= fValueY)
			{
				(vPos.x - vOtherPos.x) > 0 ? iDir = 1 : iDir = -1;
				vPlayerPos.x -= iDir * fValueX;
			}
			else
			{
				(vPos.y - vOtherPos.y) > 0 ? iDir = 1 : iDir = -1;
				vPlayerPos.y -= iDir * fValueY;
			}

			pPlayer->SetPos(vPlayerPos);

		}
	}
}
