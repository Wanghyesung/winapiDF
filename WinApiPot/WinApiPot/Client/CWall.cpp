#include "pch.h"
#include "CWall.h"

#include "CObject.h"
#include "CCollider.h"

#include "CTimeMgr.h"

#include "CRigidBody.h"
#include "CGravity.h"


CWall::CWall()
{
	CreateCollider();
	//GetCollider()->SetOffSet(Vec2());
}

CWall::~CWall()
{
}

void CWall::render(HDC _dc)
{
	component_render(_dc);
}

void CWall::update()
{
	
}


void CWall::OnColliderEnter(CCollider* _pOther)
{
	//플레이어 오브젝트이면 못 움지이게 함
	//finalpos랑 jumpos도 못 올라오게 막아야지 오차가 안 생김
	CObject* pOther = _pOther->GetObj();
	if (pOther->GetName() == L"Player")
	{
		//점프중이면 그냥 점프되게
		Vec2 vPlayerPos = _pOther->GetFinalPos();//위치
		Vec2 vPlayerScale = _pOther->GetScale(); //크기
		Vec2 vPlayerPosition = pOther->GetPos();

		//jumpos.y + 
		Vec2 vPos = GetCollider()->GetFinalPos();//내 위치
		Vec2 vScale = GetCollider()->GetScale();

		Vec2 vPlayerJumPos = pOther->GetJumPos();//내 진짜 점프 위치
		Vec2 vCloudJumPos = pOther->GetJumPos() + _pOther->GetOffSetPos() / 2.f; //내 콜라이더가 부딪치는 곳

		tColliderInfo tCollInfo = GetCollider()->GetColliderInfo();
		Vec2 vPlayerVelocity = pOther->GetRigidBody()->GetVelocity();

		//
		if (pOther->GetGravity()->IsGetGravity())
		{
			if (vCloudJumPos.y + 20.f < tCollInfo.fBottomHeight)
			{
				float fLen = abs(vPos.x - vPlayerJumPos.x);
				float fValue = (vPlayerScale.x / .2f + vScale.x / 2.f) - fLen;

				Vec2 vNor = (vPlayerJumPos - vPos).NormalRize();
				int iDir = 0;
				if (vNor.x > 0.f)
					iDir = 1;
				else
					iDir = -1;
				vPlayerPosition.x -= vPlayerVelocity.x * fDT;
				pOther->SetPos(vPlayerPosition);
				vPlayerJumPos.x -= vPlayerVelocity.x * fDT;
				pOther->SetJumPos(vPlayerJumPos);
			}

			else if (vCloudJumPos.y + 2.f < tCollInfo.fBottomHeight)
			{
				vPlayerJumPos.y -= pOther->GetRigidBody()->GetNgravityPos();
				pOther->SetJumPos(vPlayerJumPos);
			}
	
		}

		else
		{
			//y축 밑면의 위치를 조사해서 그 밑면의 y축 위치보다 높은곳에서 플레이어가 부딪쳤으면 x쪽으로 밀어내고 아니면 y쪽으로 밀어내기 
			float fBottom = (vPos.y + vScale.y / 2.f);

			Vec2 vPlayerObjPos = _pOther->GetObj()->GetPos();

			if (vPlayerPos.y < fBottom) //밑변보다 플레이어가 높으곳에 부딪쳤다면
			{
				float fLen = abs(vPos.x - vPlayerPos.x);
				float fValue = (vScale.x / 2.f + vPlayerScale.x / 2.f) - fLen;

				Vec2 vNorDiff = (vPlayerPos - vPos).NormalRize();
				int iDir = 0;
				if (vNorDiff.x > 0.f)
					iDir = 1;
				else
					iDir = -1;

				vPlayerObjPos.x += fValue * vNorDiff.x;
			}
			else
			{
				//서로 크기의 반끼리 합친 값에 내 위치와 상대 위치의 거리를 뺀 값 만큼 내 플레이어를 밀어냄

				float fLen = abs(vPos.y - vPlayerPos.y);
				float fValue = (vScale.y / 2.f + vPlayerScale.y / 2.f) - fLen;

				Vec2 vNorDiff = (vPlayerPos - vPos).NormalRize();
				int iDir = 0;
				if (vNorDiff.y > 0.f)
					iDir = 1;
				else
					iDir = -1;

				vPlayerObjPos.y += fValue * vNorDiff.y;

			}
			pOther->SetPos(vPlayerObjPos);
		}
	}
}

void CWall::OnColliderExit(CCollider* _pOther)
{
	
}

void CWall::OnCollision(CCollider* _pOther)
{
	//플레이어 오브젝트이면 못 움지이게 함
	//finalpos랑 jumpos도 못 올라오게 막아야지 오차가 안 생김
	CObject* pOther = _pOther->GetObj();
	if (pOther->GetName() == L"Player")
	{
		//점프중이면 그냥 점프되게
		Vec2 vPlayerPos = _pOther->GetFinalPos();//위치
		Vec2 vPlayerScale = _pOther->GetScale(); //크기
		Vec2 vPlayerPosition = pOther->GetPos();

		//jumpos.y + 
		Vec2 vPos = GetCollider()->GetFinalPos();//내 위치
		Vec2 vScale = GetCollider()->GetScale();
	
		Vec2 vPlayerJumPos = pOther->GetJumPos();//내 진짜 점프 위치
		Vec2 vCloudJumPos = pOther->GetJumPos() + _pOther->GetOffSetPos() / 2.f; //내 콜라이더가 부딪치는 곳

		tColliderInfo tCollInfo = GetCollider()->GetColliderInfo();
		Vec2 vPlayerVelocity = pOther->GetRigidBody()->GetVelocity();

		if (pOther->GetGravity()->IsGetGravity())
		{
			//그냥 콜리이더에 부딪치면 이동 애니메이션만 나오고 움직임을 주지 말까
			if (vCloudJumPos.y +20.f < tCollInfo.fBottomHeight)
			{
				float fLen = abs(vPos.x - vPlayerJumPos.x);
				float fValue = (vPlayerScale.x / .2f + vScale.x / 2.f) - fLen;

				Vec2 vNor = (vPlayerJumPos - vPos).NormalRize();
				int iDir = 0;
				if (vNor.x > 0.f)
					iDir = 1;
				else
					iDir = -1;
				vPlayerPosition.x -= vPlayerVelocity.x * fDT;
				pOther->SetPos(vPlayerPosition);
				vPlayerJumPos.x -= vPlayerVelocity.x* fDT;
				pOther->SetJumPos(vPlayerJumPos);
			}

			else if(vCloudJumPos.y + 2.f < tCollInfo.fBottomHeight)
			{
				vPlayerJumPos.y -= pOther->GetRigidBody()->GetNgravityPos();
				pOther->SetJumPos(vPlayerJumPos);
			}

			//if (vCloudJumPos.y < tCollInfo.fBottomHeight)
			//{
			//	vPlayerJumPos.y -= pOther->GetRigidBody()->GetNgravityPos();
			//	pOther->SetJumPos(vPlayerJumPos);
			//}

			
		}

		else
		{
			//y축 밑면의 위치를 조사해서 그 밑면의 y축 위치보다 높은곳에서 플레이어가 부딪쳤으면 x쪽으로 밀어내고 아니면 y쪽으로 밀어내기 
			float fBottom = (vPos.y + vScale.y / 2.f);

			Vec2 vPlayerObjPos = _pOther->GetObj()->GetPos();

			if (vPlayerPos.y < fBottom) //밑변보다 플레이어가 높으곳에 부딪쳤다면
			{
				float fLen = abs(vPos.x - vPlayerPos.x);
				float fValue = (vScale.x / 2.f + vPlayerScale.x / 2.f) - fLen;

				Vec2 vNorDiff = (vPlayerPos - vPos).NormalRize();
				int iDir = 0;
				if (vNorDiff.x > 0.f)
					iDir = 1;
				else
					iDir = -1;

				vPlayerObjPos.x += fValue * vNorDiff.x;
			}
			else
			{
				//서로 크기의 반끼리 합친 값에 내 위치와 상대 위치의 거리를 뺀 값 만큼 내 플레이어를 밀어냄

				float fLen = abs(vPos.y - vPlayerPos.y);
				float fValue = (vScale.y / 2.f + vPlayerScale.y / 2.f) - fLen;

				Vec2 vNorDiff = (vPlayerPos - vPos).NormalRize();
				int iDir = 0;
				if (vNorDiff.y > 0.f)
					iDir = 1;
				else
					iDir = -1;

				vPlayerObjPos.y += fValue * vNorDiff.y;

			}
			pOther->SetPos(vPlayerObjPos);
		}
	}
}
