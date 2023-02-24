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
		vForce.NormalRize();//방향
		float m_fAccel = fForce / m_fMass; //가속도

		m_vAccel = vForce * m_fAccel; //내 속도는 내 힘의 방향 * 내 실수 가속도
	}

	//중력 없는 물체면 오류가 나옴
	if (m_pOwner->GetGravity()->IsGetGravity())//(중력이 가해지면)
	{
		m_vNgravityPos = m_vAccel.y * fDT;

		m_vAccel += m_vGravity;

		m_vVelocity += m_vAccel * fDT; //IsPass(Vec2 _v)함수에 m_vVelocity값을 넣어서 그 함수에서 미리 한번 움직여보고 맵을 넘었다면 해당 방향에 값을 0을 줌
	}

	else if (m_bAccel)
	{
		m_vAccel += m_vAccelA;//추가 가속도

		m_vVelocity += m_vAccel * fDT;

		Vec2 vNor = -m_vVelocity;
		vNor.NormalRize();
		Vec2 vFric = vNor * m_fFricCoeff * fDT; //마찰력 적용

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

	else//중력이 없다면
	{
		m_vAccel += m_vAccelA;

		m_vVelocity = m_vAccel * fDT; // velocity는 매 프레임 값 계산
	}

	//마찰력은 적용안 해도 될 것 같음


	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);//자신의 x축 방향의 방향벡터를 구한다 그리고 최대값의 길이만큼을 곱해준다
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);//자신의 x축 방향의 방향벡터를 구한다 그리고 최대값의 길이만큼을 곱해준다
	}

	//마찰력이 있는지 없는지 확인 후 마찰력을 적용할 물제에만 마찰력 적용

	//끝나면 초기화

	move();

	m_vAccel = Vec2(0.f, 0.f);
	m_vFore = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);
	//m_vGravity = Vec2(0.f, 0.f);//이걸 왜 초기화했지?
}



void CRigidBody::move()
{

	float fSpeed = m_vVelocity.Length();
	//맵의 범위 밖으로 못 나가게 만들기
	if (!fSpeed == 0)
	{

		Vec2 vDir = m_vVelocity;
		vDir.NormalRize();

		Vec2 vPos = m_pOwner->GetPos();

		if (m_pOwner->GetGravity()->IsGetGravity()) //점프상태일 떄
		{
			
			//if (m_fCurTIme > 1.f)
				//int a = 1;
			//m_fCurTIme += fDT;//시간 제기..

			m_vCurJumPos = vPos;

			Vec2 finalJumPos = m_pOwner->GetFinalJumPos();
			Vec2 jumPos =  m_pOwner->GetJumPos();

			//점패해서 내려갈 때 중력에 의한 움직임과 중력없이 x와 y갑의 움직임 계산
			if (m_bDown)
			{
				vPos += m_vVelocity * fDT;
				m_pOwner->SetPos(vPos);

				finalJumPos = vPos;//Vec2(m_vVelocity.x * fDT, m_vVelocity.y * fDT);//finalpos에 x이동값과 y속도값만 더함
				m_pOwner->SetFinalJumPos(finalJumPos);

				jumPos += (Vec2(m_vVelocity.x * fDT, m_vNgravityPos));//jumpos에 x,y의 이동값만을 더함
				m_pOwner->SetJumPos(jumPos);
			}

			//점프해서 올라갈 때 중력없이 x와 y값의 움직임 계산
			else
			{
				vPos += m_vVelocity * fDT;
				m_pOwner->SetPos(vPos);

				jumPos += (Vec2(m_vVelocity.x * fDT, m_vNgravityPos));//jumpos에 x,y의 이동값만을 더함
				
				m_pOwner->SetJumPos(jumPos);

				//620, 380

				if ((m_vCurJumPos.y - m_vPreJumPos.y) > 0)//지금 프레임의 위치가 전 프레임의 위치보다 낮을 경우 
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
		//여기 걸려서 안 움직여
		//else if (((CPlayer*)m_pOwner)->IsSlidingNow() && m_pOwner->GetName() == L"Player")
		//{
		//	vPos += m_vVelocity * fDT; //* fDT;
		//	m_pOwner->SetPos(vPos);
		//}

		//점프중이 아니면
		else 
		{
			vPos += m_vVelocity;// *fDT;
			m_pOwner->SetPos(vPos);
		}

		IsOutRangeMap(); //맵 밖으로 넘어갔는지 계산
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
			m_pOwner->SetJumPos(Vec2(vJumPos.x - vVelocity.x * fDT, vJumPos.y));//걍 줬던 velocity다 반대로 주면 될듯
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
			//x쪽만 막는다 y쪽으로는 점프 가능하게 할것임 하지만 중력값을 뺀 y움직임은 막아줘야함
			m_pOwner->SetJumPos(Vec2(vJumPos.x, vJumPos.y + m_vNgravityPos));//Ngravity값이 맵 밖으로 넘어가면 뺴야하나
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




