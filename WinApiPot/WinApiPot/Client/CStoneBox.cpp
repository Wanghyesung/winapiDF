#include "pch.h"
#include "CStoneBox.h"

#include "CTexture.h"

#include "CResMgr.h"
#include "CCameraMgr.h"
#include "CTimeMgr.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CRigidBody.h"


CStoneBox::CStoneBox()
{
	CreateCollider();

	SetTag(GROUP_TYPE::STONE_BOX);

	CTex = CResMgr::GetInst()->LoadTextur(L"StoneBox", L"..\\OutPut\\bin_release\\Content\\Object\\stonebox.bmp");
}

CStoneBox::~CStoneBox()
{

}

void CStoneBox::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

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

	CObject::component_render(_dc);
}

void CStoneBox::update()
{

}

void CStoneBox::finalupdate()
{
	CObject::finalupdate();
}

void CStoneBox::OnColliderEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::BULLET ||
		pObj->GetTag() == GROUP_TYPE::SKILL)
	{
		//현재씬의 이 오브젝트 삭제
		DeleteObject(this);
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

		

		if(!pPlayer->GetGravity()->IsGetGravity())
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

void CStoneBox::OnColliderExit(CCollider* _pOther)
{
	
}

void CStoneBox::OnCollision(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::BULLET ||
		pObj->GetTag() == GROUP_TYPE::SKILL)
	{
		//현재씬의 이 오브젝트 삭제
		DeleteObject(this);
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
