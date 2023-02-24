#include "pch.h"
#include "CObject.h"

#include "CCollider.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CRigidBody.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CSkill.h"
#include "CSkillState.h"

CObject::CObject() :
	m_vPos{},
	m_vSclae{},
	m_bAlive(true),
	m_pTex(nullptr),
	m_pAnim(nullptr),
	m_pRigidBody(nullptr),
	m_pCollider(nullptr),
	m_pGravity(nullptr)
{
}

CObject::~CObject()
{
	if (nullptr != m_pAnim)
	{
		delete m_pAnim;
	}

	if (nullptr != m_pRigidBody)
	{
		delete m_pRigidBody;
	}

	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}

 	if (nullptr != m_pGravity)
	{
		delete m_pGravity;
	}
}

void CObject::render(HDC _dc)
{
	Rectangle(_dc,
		(int)(m_vPos.x - m_vSclae.x / 2),
		(int)(m_vPos.y - m_vSclae.y / 2),
		(int)(m_vPos.x + m_vSclae.x / 2),
		(int)(m_vPos.y + m_vSclae.y / 2));

	component_render(_dc);
}

void CObject::finalupdate()
{

	if (m_pCollider != nullptr)
	{
		m_pCollider->finalupdate();
	}

	if (m_pAnim != nullptr)
	{
		m_pAnim->finalupdate();
	}
	
	if (m_pGravity != nullptr)
	{
		m_pGravity->finalupdate();
	}

	if (m_pRigidBody != nullptr)
	{
		m_pRigidBody->finalupdate();
	}


}

void CObject::component_render(HDC _dc)
{
	if (m_pAnim != nullptr)
	{
		m_pAnim->render(_dc);
	}

	if (m_pCollider != nullptr)
	{
		m_pCollider->render(_dc);
	}


}

void CObject::CreateAnimator()
{
	m_pAnim = new CAnimator;
	m_pAnim->m_pOwner = this;
}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}


