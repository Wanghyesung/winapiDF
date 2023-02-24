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
	//�÷��̾� ������Ʈ�̸� �� �����̰� ��
	//finalpos�� jumpos�� �� �ö���� ���ƾ��� ������ �� ����
	CObject* pOther = _pOther->GetObj();
	if (pOther->GetName() == L"Player")
	{
		//�������̸� �׳� �����ǰ�
		Vec2 vPlayerPos = _pOther->GetFinalPos();//��ġ
		Vec2 vPlayerScale = _pOther->GetScale(); //ũ��
		Vec2 vPlayerPosition = pOther->GetPos();

		//jumpos.y + 
		Vec2 vPos = GetCollider()->GetFinalPos();//�� ��ġ
		Vec2 vScale = GetCollider()->GetScale();

		Vec2 vPlayerJumPos = pOther->GetJumPos();//�� ��¥ ���� ��ġ
		Vec2 vCloudJumPos = pOther->GetJumPos() + _pOther->GetOffSetPos() / 2.f; //�� �ݶ��̴��� �ε�ġ�� ��

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
			//y�� �ظ��� ��ġ�� �����ؼ� �� �ظ��� y�� ��ġ���� ���������� �÷��̾ �ε������� x������ �о�� �ƴϸ� y������ �о�� 
			float fBottom = (vPos.y + vScale.y / 2.f);

			Vec2 vPlayerObjPos = _pOther->GetObj()->GetPos();

			if (vPlayerPos.y < fBottom) //�غ����� �÷��̾ �������� �ε��ƴٸ�
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
				//���� ũ���� �ݳ��� ��ģ ���� �� ��ġ�� ��� ��ġ�� �Ÿ��� �� �� ��ŭ �� �÷��̾ �о

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
	//�÷��̾� ������Ʈ�̸� �� �����̰� ��
	//finalpos�� jumpos�� �� �ö���� ���ƾ��� ������ �� ����
	CObject* pOther = _pOther->GetObj();
	if (pOther->GetName() == L"Player")
	{
		//�������̸� �׳� �����ǰ�
		Vec2 vPlayerPos = _pOther->GetFinalPos();//��ġ
		Vec2 vPlayerScale = _pOther->GetScale(); //ũ��
		Vec2 vPlayerPosition = pOther->GetPos();

		//jumpos.y + 
		Vec2 vPos = GetCollider()->GetFinalPos();//�� ��ġ
		Vec2 vScale = GetCollider()->GetScale();
	
		Vec2 vPlayerJumPos = pOther->GetJumPos();//�� ��¥ ���� ��ġ
		Vec2 vCloudJumPos = pOther->GetJumPos() + _pOther->GetOffSetPos() / 2.f; //�� �ݶ��̴��� �ε�ġ�� ��

		tColliderInfo tCollInfo = GetCollider()->GetColliderInfo();
		Vec2 vPlayerVelocity = pOther->GetRigidBody()->GetVelocity();

		if (pOther->GetGravity()->IsGetGravity())
		{
			//�׳� �ݸ��̴��� �ε�ġ�� �̵� �ִϸ��̼Ǹ� ������ �������� ���� ����
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
			//y�� �ظ��� ��ġ�� �����ؼ� �� �ظ��� y�� ��ġ���� ���������� �÷��̾ �ε������� x������ �о�� �ƴϸ� y������ �о�� 
			float fBottom = (vPos.y + vScale.y / 2.f);

			Vec2 vPlayerObjPos = _pOther->GetObj()->GetPos();

			if (vPlayerPos.y < fBottom) //�غ����� �÷��̾ �������� �ε��ƴٸ�
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
				//���� ũ���� �ݳ��� ��ģ ���� �� ��ġ�� ��� ��ġ�� �Ÿ��� �� �� ��ŭ �� �÷��̾ �о

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
