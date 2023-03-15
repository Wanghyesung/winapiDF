#include "pch.h"
#include "CThunder.h"

#include "CTexture.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CCollider.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CLord.h"

#include "AI.h"
#include "CState.h"

CThunder::CThunder():
	m_iFrame(0),
	m_fMaxTime(3.f),
	m_fTime(0.f),
	vOffset(Vec2(400.f,-50.f))
{

	SetTag(GROUP_TYPE::MONSTER_SKILL);

	SetName(L"Thunder");

	CreateCollider();
	GetCollider()->SetScale(Vec2(700.f, 150.f));

	CTexture* pTex_right = CResMgr::GetInst()->LoadTextur(L"Thunder1_right", L"..\\OutPut\\bin_release\\Content\\emfact\\Thuner1_right.bmp");
	CTexture* pTex_left = CResMgr::GetInst()->LoadTextur(L"Thunder1_left", L"..\\OutPut\\bin_release\\Content\\emfact\\Thuner1_left.bmp");


	CreateAnimator();
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
	if (m_pOwner == nullptr || !m_pOwner->IsActiv())
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
		int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
		if (m_iFrame != iFrame)
		{
			m_bAttackOn = true;
			m_iFrame = iFrame;
		}
		else
		{
			m_bAttackOn = false;
		}
	}
}
