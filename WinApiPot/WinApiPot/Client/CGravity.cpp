#include "pch.h"
#include "CGravity.h"

#include "CObject.h"
#include "CRigidBody.h"

#include "CPlayer.h"

#include "CAnimator.h"
#include "CAnimation.h"

CGravity::CGravity():
	m_pOwner(nullptr),
	m_bAttive(false),
	stack(0)
{
}

CGravity::~CGravity()
{
}

void CGravity::finalupdate()
{
	if (m_bAttive)//공중상태이면
	{
		//여기서 finaljumpos와 같다면 점프 해제 && 처음 시작한 점프 위치와 똑같지 않아야함
		bool IsSame = abs(m_pOwner->GetJumPos().x - m_pOwner->GetFinalJumPos().x) < 0.8f  &&
			m_pOwner->GetJumPos().y - m_pOwner->GetFinalJumPos().y <= 0.f;
		if (IsSame)
		{
		
			m_bAttive = false;
			m_pOwner->GetRigidBody()->SetDown(false);
			m_pOwner->SetFinalJumPos(Vec2(0.f, 0.f));//finaljumpos 초기화해줘야지 또 뛸 수 있음 안그러면 변수값이 다음에 IsSame에 true가 됨
			m_pOwner->SetJumPos(Vec2(0.f, 0.f));
			return;
		}

		//나중에 여기서 물체의 질량에 따른 속도값도 다르게 해서 주면 됨
		m_pOwner->GetRigidBody()->SetGravity(Vec2(0.f,600.f));//밑으로 중력 주기 600씩 줄거임

	}
}


