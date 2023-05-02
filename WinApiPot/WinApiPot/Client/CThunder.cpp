#include "pch.h"
#include "CThunder.h"

#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CGravity.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CLord.h"

#include "AI.h"
#include "CState.h"

CThunder::CThunder():
	m_iFrame(0),
	m_fMaxTime(3.f),
	m_fTime(0.f),
	vOffset(Vec2(450.f,-50.f))
{

	SetTag(GROUP_TYPE::MONSTER_SKILL);

	SetName(L"Thunder");

	CreateCollider();
	GetCollider()->SetScale(Vec2(700.f, 100.f));

	CTexture* pTex_right = CResMgr::GetInst()->LoadTextur(L"Thunder2_right", L"..\\OutPut\\bin_release\\Content\\emfact\\Thuner2_right.bmp");
	CTexture* pTex_left = CResMgr::GetInst()->LoadTextur(L"Thunder2_left", L"..\\OutPut\\bin_release\\Content\\emfact\\Thuner2_left.bmp");


	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);
	GetAnimator()->CreateAnimation(L"Thunder_right", pTex_right, Vec2(0.f, 0.f), Vec2(900.f, 400.f), Vec2(900.f, 0.f), Vec2(0.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"Thunder_left", pTex_left, Vec2(2700.f, 0.f), Vec2(900.f, 400.f), Vec2(-900.f, 0.f), Vec2(0.f, 0.f), 0.1f, 4);
}

CThunder::~CThunder()
{

}

void CThunder::render(HDC _dc)
{
	component_render(_dc);
}

void CThunder::update()
{
	if (m_pOwner == nullptr || m_pOwner->GetMonInfo().m_iHp<=0.f)
	{
		DeleteObject(this);
		return;
	}
	m_fTime += fDT;
	if (m_fTime >= m_fMaxTime)
	{
		DeleteObject(this);
		return;
	}

	wstring strDir = L"";
	int iDir = m_pOwner->GetAI()->GetCurState()->GetDir();
	iDir < 0 ? strDir = L"_left" : strDir = L"_right";

	//내 몬스터 위치에 방향에 offset값 더하기 
	Vec2 vLordPos = m_pOwner->GetCollider()->GetFinalPos();
	vLordPos.x += iDir * vOffset.x;
	vLordPos.y += vOffset.y;

	SetPos(vLordPos);

	GetAnimator()->Play(L"Thunder" + strDir, true);
	
}

void CThunder::OnColliderEnter(CCollider* _pOther)
{

}



void CThunder::OnColliderExit(CCollider* _pOther)
{
}

void CThunder::OnCollision(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::PLAYER)
	{
		if (pObj->GetGravity()->IsGetGravity())
		{
			if (!IsSameJumLoc(_pOther, GetCollider()))
				return;
		}
		
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		if (m_iFrame != iFrame)
		{
			//한 프레임당 한번씩만 맞게
			m_bAttackOn = true;
			m_iFrame = iFrame;
		}
		else
		{
			m_bAttackOn = false;
		}
		
	}
}

bool CThunder::IsSameJumLoc(CCollider* _pOther, CCollider* _pThis)
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
