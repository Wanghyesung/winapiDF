#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CGravity.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTexture.h"
#include "CCollider.h"




CRigidBody::CRigidBody() :
	//m_bAttiveGravity(false),
	//m_fCurTIme(0.f),
	m_bDown(false),
	m_vPreJumPos(Vec2(0.f,0.f)),
	m_bAccel(false),
	m_pOwner(nullptr),
	m_fFricCoeff(500.f),
	m_fMass(1.f),
	m_vMaxVelocity(Vec2(700.f, 600.f))
{
}

CRigidBody::~CRigidBody()
{

}


void CRigidBody::finalupdate()
{
	float fForce = m_vFore.Length();
	Vec2  vForce = m_vFore;

	if (0.f != fForce)
	{
		vForce.NormalRize();//����
		float m_fAccel = fForce / m_fMass; //���ӵ�

		m_vAccel = vForce * m_fAccel; //�� �ӵ��� �� ���� ���� * �� �Ǽ� ���ӵ�
	}

	//�߷� ���� ��ü�� ������ ����
	if (m_pOwner->GetGravity()->IsGetGravity())//(�߷��� ��������)
	{
		m_vNgravityPos = m_vAccel.y * fDT;

		m_vAccel += m_vGravity;

		m_vVelocity += m_vAccel * fDT; //IsPass(Vec2 _v)�Լ��� m_vVelocity���� �־ �� �Լ����� �̸� �ѹ� ���������� ���� �Ѿ��ٸ� �ش� ���⿡ ���� 0�� ��
	}

	else if (m_bAccel)
	{
		m_vAccel += m_vAccelA;//�߰� ���ӵ�

		m_vVelocity += m_vAccel * fDT;

		Vec2 vNor = -m_vVelocity;
		vNor.NormalRize();
		Vec2 vFric = vNor * m_fFricCoeff * fDT; //������ ����

		if ( Vec2(m_vVelocity.x + vFric.x ,0.f).Length() <= vFric.Length() + 200.f)
		{
			m_vVelocity = Vec2(0.f, 0.f);
			m_bAccel = false;
		}
		else
		{
			m_vVelocity.x += vFric.x;
		}

	}

	else//�߷��� ���ٸ�
	{
		m_vAccel += m_vAccelA;

		m_vVelocity = m_vAccel * fDT; // velocity�� �� ������ �� ���
	}

	//�������� ����� �ص� �� �� ����


	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);//�ڽ��� x�� ������ ���⺤�͸� ���Ѵ� �׸��� �ִ밪�� ���̸�ŭ�� �����ش�
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);//�ڽ��� x�� ������ ���⺤�͸� ���Ѵ� �׸��� �ִ밪�� ���̸�ŭ�� �����ش�
	}

	//�������� �ִ��� ������ Ȯ�� �� �������� ������ �������� ������ ����

	//������ �ʱ�ȭ

	move();

	m_vAccel = Vec2(0.f, 0.f);
	m_vFore = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);
	//m_vGravity = Vec2(0.f, 0.f);//�̰� �� �ʱ�ȭ����?
}



void CRigidBody::move()
{

	float fSpeed = m_vVelocity.Length();
	//���� ���� ������ �� ������ �����
	if (!fSpeed == 0)
	{

		Vec2 vDir = m_vVelocity;
		vDir.NormalRize();

		Vec2 vPos = m_pOwner->GetPos();

		if (m_pOwner->GetGravity()->IsGetGravity()) //���������� ��
		{
			
			//if (m_fCurTIme > 1.f)
				//int a = 1;
			//m_fCurTIme += fDT;//�ð� ����..

			m_vCurJumPos = vPos;

			Vec2 finalJumPos = m_pOwner->GetFinalJumPos();
			Vec2 jumPos =  m_pOwner->GetJumPos();

			//�����ؼ� ������ �� �߷¿� ���� �����Ӱ� �߷¾��� x�� y���� ������ ���
			if (m_bDown)
			{
				vPos += m_vVelocity * fDT;
				m_pOwner->SetPos(vPos);

				finalJumPos = vPos;//Vec2(m_vVelocity.x * fDT, m_vVelocity.y * fDT);//finalpos�� x�̵����� y�ӵ����� ����
				m_pOwner->SetFinalJumPos(finalJumPos);

				jumPos += (Vec2(m_vVelocity.x * fDT, m_vNgravityPos));//jumpos�� x,y�� �̵������� ����
				m_pOwner->SetJumPos(jumPos);
			}

			//�����ؼ� �ö� �� �߷¾��� x�� y���� ������ ���
			else
			{
				vPos += m_vVelocity * fDT;
				m_pOwner->SetPos(vPos);

				jumPos += (Vec2(m_vVelocity.x * fDT, m_vNgravityPos));//jumpos�� x,y�� �̵������� ����
				
				m_pOwner->SetJumPos(jumPos);

				//620, 380

				if ((m_vCurJumPos.y - m_vPreJumPos.y) > 0)//���� �������� ��ġ�� �� �������� ��ġ���� ���� ��� 
				{	
					if (!m_vPreJumPos.IsZero())
					{
						m_bDown = true;
						m_pOwner->SetFinalJumPos(Vec2(vPos.x, vPos.y));
					}
				}
			}
			m_vPreJumPos = m_vCurJumPos;
		}
		
		else if (m_bAccel)
		{
			vPos += m_vVelocity * fDT;
			m_pOwner->SetPos(vPos);
		}
		//���� �ɷ��� �� ������
		//else if (((CPlayer*)m_pOwner)->IsSlidingNow() && m_pOwner->GetName() == L"Player")
		//{
		//	vPos += m_vVelocity * fDT; //* fDT;
		//	m_pOwner->SetPos(vPos);
		//}

		//�������� �ƴϸ�
		else 
		{
			vPos += m_vVelocity;// *fDT;
			m_pOwner->SetPos(vPos);
		}

		IsOutRangeMap(); //�� ������ �Ѿ���� ���
	}

}

void CRigidBody::IsOutRangeMap()
{
	tBackGround tMapInfo = SceneMgr::GetInst()->GetCurSCene()->GetBackGroundInfo();
	//Vec2 vfinalPos = m_pOwner->GetCollider()->GetFinalPos();
	Vec2 vPos = m_pOwner->GetPos();
	//Vec2 vCollOffsetPos = m_pOwner->GetCollider()->GetOffSetPos();

	Vec2 vVelocity = GetVelocity();


	bool bIsXpass = vPos.x <= tMapInfo.fLeftWidth || vPos.x >= tMapInfo.fRightWidth;
	bool bIsYpass = vPos.y >= tMapInfo.fBottomHeight || vPos.y <= tMapInfo.fTopHeight;

	if (bIsXpass)
	{
		if (m_pOwner->GetGravity()->IsGetGravity())
		{
			Vec2 vJumPos = m_pOwner->GetJumPos();
			m_pOwner->SetJumPos(Vec2(vJumPos.x - vVelocity.x * fDT, vJumPos.y));//�� ��� velocity�� �ݴ�� �ָ� �ɵ�
			vPos.x += -vVelocity.x * fDT;
		}
		else
		{
			if (vPos.x >= tMapInfo.fRightWidth)
			{
				vPos.x = tMapInfo.fRightWidth;
			}
			else
			{
				vPos.x = tMapInfo.fLeftWidth;
			}
		}
	}

	if (bIsYpass)
	{

		if (m_pOwner->GetGravity()->IsGetGravity())
		{
			Vec2 vJumPos = m_pOwner->GetJumPos();
			//x�ʸ� ���´� y�����δ� ���� �����ϰ� �Ұ��� ������ �߷°��� �� y�������� ���������
			m_pOwner->SetJumPos(Vec2(vJumPos.x, vJumPos.y + m_vNgravityPos));//Ngravity���� �� ������ �Ѿ�� �����ϳ�
			vPos.y += -vVelocity.y * fDT;
		}
		else
		{
			if (vPos.y >= (float)tMapInfo.fBottomHeight)
			{
				vPos.y = (float)tMapInfo.fBottomHeight;
			}
			else
			{
				vPos.y = (float)tMapInfo.fTopHeight;
			}
		}
	}
	
	m_pOwner->SetPos(vPos);
}




