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
	if (m_bAttive)//���߻����̸�
	{
		//���⼭ finaljumpos�� ���ٸ� ���� ���� && ó�� ������ ���� ��ġ�� �Ȱ��� �ʾƾ���
		bool IsSame = abs(m_pOwner->GetJumPos().x - m_pOwner->GetFinalJumPos().x) < 0.8f  &&
			m_pOwner->GetJumPos().y - m_pOwner->GetFinalJumPos().y <= 0.f;
		if (IsSame)
		{
		
			m_bAttive = false;
			m_pOwner->GetRigidBody()->SetDown(false);
			m_pOwner->SetFinalJumPos(Vec2(0.f, 0.f));//finaljumpos �ʱ�ȭ������� �� �� �� ���� �ȱ׷��� �������� ������ IsSame�� true�� ��
			m_pOwner->SetJumPos(Vec2(0.f, 0.f));
			return;
		}

		//���߿� ���⼭ ��ü�� ������ ���� �ӵ����� �ٸ��� �ؼ� �ָ� ��
		m_pOwner->GetRigidBody()->SetGravity(Vec2(0.f,600.f));//������ �߷� �ֱ� 600�� �ٰ���

	}
}


