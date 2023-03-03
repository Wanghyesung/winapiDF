#include "pch.h"
#include "CBlueDragon.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CGravity.h"

#include "CResMgr.h"

#include "CTexture.h"


#include "AI.h"
#include "CState.h"

CBlueDragon::CBlueDragon():
	m_eMonState(MONSTER_STATE::IDLE)
{

	CreateCollider();
	GetCollider()->SetScale(Vec2(70.f, 70.f));
	GetCollider()->SetOffSet(Vec2(0.f, 30.f));

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);

	CreateGravity();
	
	
	//ÀÌ¹ÌÁö

	CTexture* pRightMotion =  CResMgr::GetInst()->LoadTextur(L"BDragon_Monster_right", L"..\\OutPut\\bin_release\\Content\\Texture\\bdragon_right.bmp");
	CTexture* pLeftMotion = CResMgr::GetInst()->LoadTextur(L"BDragon_Monster_left", L"..\\OutPut\\bin_release\\Content\\Texture\\bdragon_left.bmp");
	// 308 172
	// 2156 1376
	// 1848 0
	//right 

	GetAnimator()->CreateAnimation(L"BDragon_Idle_right", pRightMotion, Vec2(0.f, 344.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"BDragon_Normal_Attack_right", pRightMotion, Vec2(0.f, 0.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"BDragon_Attack_right", pRightMotion, Vec2(0.f, 172.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Defense_right", pRightMotion, Vec2(0.f, 344.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"BDragon_Move_Back_right", pRightMotion, Vec2(0.f, 516.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Move_right", pRightMotion, Vec2(0.f, 688.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Motion_Hit_right", pRightMotion, Vec2(0.f, 1032.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 2);
	GetAnimator()->FindAnimation(L"BDragon_Motion_Hit_right")->Create(pRightMotion, Vec2(0.f, 1204.f), Vec2(308.f, 172.f), Vec2(308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	
	
	//left
	GetAnimator()->CreateAnimation(L"BDragon_Idle_left", pLeftMotion, Vec2(1848.f, 344.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"BDragon_Normal_Attack_left", pLeftMotion, Vec2(1848.f, 0.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"BDragon_Attack_left", pLeftMotion, Vec2(1848.f, 172.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Defense_left", pLeftMotion, Vec2(1848.f, 344.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"BDragon_Move_Back_left", pLeftMotion, Vec2(1848.f, 516.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Move_left", pLeftMotion, Vec2(1848.f, 688.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 7);
	GetAnimator()->CreateAnimation(L"BDragon_Motion_Hit_left", pLeftMotion, Vec2(1848.f, 1032.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 2);
	GetAnimator()->FindAnimation(L"BDragon_Motion_Hit_left")->Create(pLeftMotion, Vec2(1848.f, 1032.f), Vec2(308.f, 172.f), Vec2(-308.f, 0.f), Vec2(0.f, 0.f), 0.1f, 2);

	GetAnimator()->Play(L"BDragon_Idle_right", true);

}

CBlueDragon::~CBlueDragon()
{

}

void CBlueDragon::update()
{
	CMonster::update();

	if (GetAI() != nullptr)
	{
		GetAI()->update();
	}

	update_state();
}


void CBlueDragon::render(HDC _dc)
{
	component_render(_dc);
}

void CBlueDragon::hit(CCollider* _pOther, const tAttackInfo& _tAtt)
{
	CMonster::hit(_pOther, _tAtt);
}

void CBlueDragon::update_state()
{
	CState* pState = GetAI()->GetCurState();
	m_eMonState = pState->GetType();

	CAnimator* pAnim = GetAnimator();

	int iDir = pState->GetDir();
	wstring sDir;
	if (iDir >= 0)
		sDir = L"_right";
	else
		sDir = L"_left";

	wstring strMotion;

	switch (m_eMonState)
	{
	case MONSTER_STATE::IDLE:
	{
		strMotion = L"BDragon_Idle" + sDir;
		pAnim->Play(strMotion, true);
	}
		break;

	case MONSTER_STATE::TRACE:
	{
		strMotion = L"BDragon_Move";
		strMotion += sDir;
		pAnim->Play(strMotion, true);
	}
		break;
	case MONSTER_STATE::ATTACK:
	{
		strMotion = L"BDragon_Normal_Attack";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
	}
		break;

	case MONSTER_STATE::ATTACK2:
	{
		strMotion = L"BDragon_Attack";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
	}
	break;

	case MONSTER_STATE::DEFENFS:
	{
		strMotion = L"BDragon_Defense";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
	}

	case MONSTER_STATE::HIT:
	{
		strMotion = L"BDragon_Idle";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
	}
		break;
	case MONSTER_STATE::UPPER_HIT:
	{
		strMotion = L"BDragon_Motion_Hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
	}
		break;
	case MONSTER_STATE::DEAD:
	{
		strMotion = L"BDragon_Motion_Hit";
		strMotion += sDir;
		pAnim->Play(strMotion, false);
	}
		break;
	}

}

void CBlueDragon::OnColliderEnter(CCollider* _pOther)
{

}

void CBlueDragon::OnColliderExit(CCollider* _pOther)
{

}

void CBlueDragon::OnCollision(CCollider* _pOther)
{

}
