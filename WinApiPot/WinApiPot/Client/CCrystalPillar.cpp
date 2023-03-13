#include "pch.h"
#include "CCrystalPillar.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CCameraMgr.h"

#include "CCollider.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CGravity.h"

#include "CAnimation.h"
#include "CAnimator.h"

CCrystalPillar::CCrystalPillar() 
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	SetTag(GROUP_TYPE::STONE_BOX);

	CTexture* pTex = CResMgr::GetInst()->LoadTextur(L"crystalpillar", L"..\\OutPut\\bin_release\\Content\\Object\\crystal_pillar.bmp");
	CTexture* pInTex = CResMgr::GetInst()->LoadTextur(L"inactive", L"..\\OutPut\\bin_release\\Content\\Object\\crystal_pillar_destroyed.bmp");

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);
	GetAnimator()->CreateAnimation(L"crystal_pillar", pTex, Vec2(0.f, 0.f), Vec2(30.f, 91.f), Vec2(30.f, 0.f), Vec2(0.f, 0.f), 0.15f, 6);
	GetAnimator()->CreateAnimation(L"inactive_crystal", pInTex, Vec2(0.f, 0.f), Vec2(32.f, 79.f), Vec2(32.f, 0.f), Vec2(0.f, 0.f), 0.15f, 1);

	GetAnimator()->Play(L"crystal_pillar", true);
}

CCrystalPillar::~CCrystalPillar()
{
}

void CCrystalPillar::render(HDC _dc)
{
	component_render(_dc);
}

void CCrystalPillar::update()
{

}

void CCrystalPillar::finalupdate()
{
	CObject::finalupdate();
}

void CCrystalPillar::OnColliderEnter(CCollider* _pOther)
{	
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::BULLET ||
		pObj->GetTag() == GROUP_TYPE::SKILL)
	{
		GetAnimator()->Play(L"inactive_crystal", true);
		return;
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

void CCrystalPillar::OnColliderExit(CCollider* _pOther)
{
}

void CCrystalPillar::OnCollision(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::BULLET ||
		pObj->GetTag() == GROUP_TYPE::SKILL)
	{
		GetAnimator()->Play(L"inactive_crystal", true);
		return;
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
