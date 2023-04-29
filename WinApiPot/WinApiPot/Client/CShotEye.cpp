#include "pch.h"
#include "CShotEye.h"

#include "CCollider.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimator.h"

#include "CRigidBody.h"
#include "CGravity.h"

#include "CEvileye.h"
#include "CTimeMgr.h"

CShotEye::CShotEye() :
	m_bAttackOn(false),
	m_bDelOn(false),
	m_pOwner(nullptr),
	m_vLookAt(Vec2(0.f, 0.f)),
	m_fDeleteTime(5.f),
	m_fCurTime(0.f)
{
	SetTag(GROUP_TYPE::MONSTER_SKILL);

	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	//CreateRigidBody();

	CTexture* pTex_right = CResMgr::GetInst()->LoadTextur(L"Evil_shot_right", L"..\\OutPut\\bin_release\\Content\\emfact\\shoteye_right.bmp");
	CTexture* pTex_left = CResMgr::GetInst()->LoadTextur(L"Evil_shot_left", L"..\\OutPut\\bin_release\\Content\\emfact\\shoteye_left.bmp");

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);
	GetAnimator()->CreateAnimation(L"Evil_shot_right", pTex_right, Vec2(0.f, 0.f), Vec2(65.f, 65.f), Vec2(65.f, 0.f), Vec2(0.f, 0.f), 0.15f, 7);
	GetAnimator()->CreateAnimation(L"Evil_shot_left", pTex_left, Vec2(390.f, 0.f), Vec2(65.f, 65.f), Vec2(-65.f, 0.f), Vec2(0.f, 0.f), 0.15f, 7);

	m_tAtt.m_eAttType = ATTACK_TYPE::UPPER;
	m_tAtt.m_fAttackDamage = 10.f;
	m_tAtt.m_fAttRcnt = 50.f;
	m_tAtt.m_fAttUpperRcnt = -60.f;
	m_tAtt.m_fAttRigidityTime = 0.5f;
}

CShotEye::~CShotEye()
{
}

void CShotEye::render(HDC _dc)
{
	component_render(_dc);
}

void CShotEye::update()
{
	if (m_bDelOn)
		return;

	m_fCurTime += fDT;
	if (m_fCurTime >= m_fDeleteTime)
	{
		m_bDelOn = true;
		GetCollider()->SetActive(false);
		DeleteObject(this);
		return;
	}

	GetAnimator()->Play(L"Evil_shot" + m_strLaserDir, true);                                                                                                                                                                                                                                                                                                                                                                                                                               

	Vec2 vPos = GetPos();
	Vec2 vTemPos = Vec2(m_vLookAt.x * m_iDir,m_vLookAt.y);

	vTemPos.NormalRize();
	vPos += (vTemPos * fDT * 200.f);

	SetPos(vPos);
}

void CShotEye::OnColliderEnter(CCollider* _pOther)
{
	if (m_bDelOn)
		return;

	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::PLAYER)
	{
		//점프 상태인지 확인하고 점프상태이면 점프 위치를 기준으로

		if (pObj->GetGravity()->IsGetGravity())
		{
			if (!IsSameJumLoc(_pOther, GetCollider()))
				return;
			else
			{
				m_bDelOn = true;
				DeleteObject(this);
			}
				
		}
		else
		{
			m_bDelOn = true;
			DeleteObject(this);
		}

	}
}

void CShotEye::OnColliderExit(CCollider* _pOther)
{

}

void CShotEye::OnCollision(CCollider* _pOther)
{

}

bool CShotEye::IsSameJumLoc(CCollider* _pOther, CCollider* _pThis)
{
	Vec2 vOffset = _pOther->GetOffSetPos();//상대 offset
	Vec2 vJumPos = _pOther->GetObj()->GetJumPos() + vOffset; //상대 점프위치 + offset
	Vec2 vOtherScale = _pOther->GetScale();

	Vec2 vScale = GetCollider()->GetScale();
	Vec2 vPos = GetCollider()->GetFinalPos();

	if (abs(vPos.x - vJumPos.x) > abs((vScale.x + vOtherScale.x) / 2.f) ||
		abs(vPos.y - vJumPos.y) > abs((vScale.y + vOtherScale.y) / 2.f))
	{
		return false;
	}

	return true;
}

void CShotEye::init_pos(Vec2 _vPos)
{
	if (m_pOwner == nullptr || !m_pOwner->IsActiv())
	{
		return;
	}

	Vec2 vEvilPos = m_pOwner->GetPos();

	SetPos(vEvilPos);
	m_vLookAt = _vPos;
}
