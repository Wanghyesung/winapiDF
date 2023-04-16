#include "pch.h"
#include "CTemWall.h"

#include "CCollider.h"
#include "CPlayer.h"

#include "CCameraMgr.h"
#include "CRigidBody.h"
#include "CGravity.h"

#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

CTemWall::CTemWall()
{
	SetTag(GROUP_TYPE::WALL);
	CreateCollider();
}

CTemWall::~CTemWall()
{

}

void CTemWall::update()
{

}

void CTemWall::render(HDC _dc)
{
	component_render(_dc);
}

void CTemWall::finalupdate()
{
	CObject::finalupdate();
}

void CTemWall::OnColliderEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::PLAYER ||
		pObj->GetTag() == GROUP_TYPE::MONSTER);
	{
		Vec2 vPlayerPos = pObj->GetPos();
		Vec2 vPlayerJumPos = pObj->GetJumPos();
		Vec2 vPlayerCollOffset = pObj->GetCollider()->GetOffSetPos();
		Vec2 vPlayerFinalPos = pObj->GetCollider()->GetFinalPos();
		Vec2 vPlayerScale = pObj->GetCollider()->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		if (pObj->GetGravity() &&
			pObj->GetGravity()->IsGetGravity())
		{
			if (vPlayerJumPos.y + vPlayerCollOffset.y - vPlayerScale.y / 2.f <= vPos.y + vScale.y / 2.f)
			{
				float fLenX = abs(vPos.x - (vPlayerJumPos.x + vPlayerCollOffset.x - vPlayerScale.x / 2.f));
				float fLenY = abs(vPos.y - (vPlayerJumPos.y + vPlayerCollOffset.y - vPlayerScale.y / 2.f));

				float fValueX = ((vScale.x) / 2.f) - fLenX;
				float fValueY = ((vScale.y) / 2.f) - fLenY;

				int iDir = 0;
				if (fValueX <= fValueY)
				{
					(vPos.x - vPlayerFinalPos.x) > 0 ? iDir = 1 : iDir = -1;
					vPlayerJumPos.x -= iDir * fValueX;
					//vPlayerJumPos.x -= iDir * 1;
				}
				else
				{
					(vPos.y - vPlayerFinalPos.y) > 0 ? iDir = 1 : iDir = -1;
					vPlayerJumPos.y -= iDir * fValueY;
					//vPlayerJumPos.y -= iDir * 1;
				}

				pObj->SetJumPos(vPlayerJumPos);
			}
		}

		else
		{
			float fLenX = abs(vPos.x - vPlayerFinalPos.x);
			float fLenY = abs(vPos.y - vPlayerFinalPos.y);

			float fValueX = ((vScale.x + vPlayerScale.x) / 2.f) - fLenX;
			float fValueY = ((vScale.y + vPlayerScale.y) / 2.f) - fLenY;

			int iDir = 0;
			if (fValueX <= fValueY)
			{
				(vPos.x - vPlayerFinalPos.x) > 0 ? iDir = 1 : iDir = -1;
				vPlayerPos.x -= iDir * fValueX;
				//vPlayerPos.x -= iDir * 1;
			}
			else
			{
				(vPos.y - vPlayerFinalPos.y) > 0 ? iDir = 1 : iDir = -1;
				vPlayerPos.y -= iDir * fValueY;
				//vPlayerPos.y -= iDir * 1;
			}

			pObj->SetPos(vPlayerPos);
		}

	}



}

void CTemWall::OnColliderExit(CCollider* _pOther)
{

}

void CTemWall::OnCollision(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::PLAYER ||
		pObj->GetTag() == GROUP_TYPE::MONSTER);
	{
		Vec2 vPlayerPos = pObj->GetPos();
		Vec2 vPlayerJumPos = pObj->GetJumPos();
		Vec2 vPlayerCollOffset = pObj->GetCollider()->GetOffSetPos();
		Vec2 vPlayerFinalPos = pObj->GetCollider()->GetFinalPos();
		Vec2 vPlayerScale = pObj->GetCollider()->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		if (pObj->GetGravity() &&
			pObj->GetGravity()->IsGetGravity())
		{
			if (vPlayerJumPos.y + vPlayerCollOffset.y - vPlayerScale.y / 2.f <= vPos.y + vScale.y / 2.f)
			{
				float fLenX = abs(vPos.x - (vPlayerJumPos.x + vPlayerCollOffset.x - vPlayerScale.x / 2.f));
				float fLenY = abs(vPos.y - (vPlayerJumPos.y + vPlayerCollOffset.y - vPlayerScale.y / 2.f));

				float fValueX = ((vScale.x) / 2.f) - fLenX;
				float fValueY = ((vScale.y) / 2.f) - fLenY;

				int iDir = 0;
				if (fValueX <= fValueY)
				{
					(vPos.x - vPlayerFinalPos.x) > 0 ? iDir = 1 : iDir = -1;
					vPlayerJumPos.x -= iDir * fValueX;
					//vPlayerJumPos.x -= iDir * 1;
				}
				else
				{
					(vPos.y - vPlayerFinalPos.y) > 0 ? iDir = 1 : iDir = -1;
					vPlayerJumPos.y -= iDir * fValueY;
					//vPlayerJumPos.y -= iDir * 1;
				}

				pObj->SetJumPos(vPlayerJumPos);
			}
		}

		else
		{
			float fLenX = abs(vPos.x - vPlayerFinalPos.x);
			float fLenY = abs(vPos.y - vPlayerFinalPos.y);

			float fValueX = ((vScale.x + vPlayerScale.x) / 2.f) - fLenX;
			float fValueY = ((vScale.y + vPlayerScale.y) / 2.f) - fLenY;

			int iDir = 0;
			if (fValueX <= fValueY)
			{
				(vPos.x - vPlayerFinalPos.x) > 0 ? iDir = 1 : iDir = -1;
				vPlayerPos.x -= iDir * fValueX;
				//vPlayerPos.x -= iDir * 1;
			}
			else
			{
				(vPos.y - vPlayerFinalPos.y) > 0 ? iDir = 1 : iDir = -1;
				vPlayerPos.y -= iDir * fValueY;
				//vPlayerPos.y -= iDir * 1;
			}

			pObj->SetPos(vPlayerPos);
		}

	}
}
