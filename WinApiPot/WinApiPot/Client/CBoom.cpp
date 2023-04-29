#include "pch.h"
#include "CBoom.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CResMgr.h"
#include "CSound.h"

CBoom::CBoom():
	m_tAtt{}
{
	SetTag(GROUP_TYPE::SKILL);

	CTexture* pBoom = CResMgr::GetInst()->LoadTextur(L"boom1", L"..\\OutPut\\bin_release\\Content\\emfact\\boom.bmp");

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);
	GetAnimator()->CreateAnimation(L"Boom", pBoom, Vec2(0.f, 0.f), Vec2(220.f, 220.f), Vec2(220.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);

	CreateCollider();
	GetCollider()->SetScale(Vec2(150.f, 150.f));

	const vector<CObject*>& vecMon = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::MONSTER);
	
	for (int i = 0; i < vecMon.size(); ++i)
	{
		UINT iTargetID = vecMon[i]->GetCollider()->GetID();
		m_hashTargetCollId[iTargetID] = 0;
	}

	GetAnimator()->Play(L"Boom", false);

	CSound* pSound = CResMgr::GetInst()->LoadSound(L"grenadegravity_exp", L"..\\OutPut\\bin_release\\Content\\Sound\\grenadegravity_exp.wav");
	pSound->Play(false);
}

CBoom::~CBoom()
{

}

void CBoom::render(HDC _dc)
{
	component_render(_dc);
}

void CBoom::update()
{

	int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
	if (iFrame == -1)
		DeleteObject(this);
}

void CBoom::finalupdate()
{
	CObject::finalupdate();
}

void CBoom::OnColliderEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER)
	{
		UINT iTargetId = _pOther->GetID();
		if (m_hashTargetCollId[iTargetId] == 0)
		{
			m_hashTargetCollId[iTargetId] = 1;
			m_bAttackOn = true;
		}
	}
}

void CBoom::OnColliderExit(CCollider* _pOther)
{

}

void CBoom::OnCollision(CCollider* _pOther)
{
	
}
