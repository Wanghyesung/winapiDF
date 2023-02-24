#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"

#include "CBullet.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CPathMgr.h";

#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"
#include "CCollider.h"
#include "CGravity.h"

#include "CSkill.h"
#include "CFSM.h"
#include "CPlayerState.h"

#include "CCameraMgr.h"
#include "CTimeMgr.h"
#include "CSkill.h"
#include "CSkillState.h"
#include "CSkillMgr.h"

#include "CFireBall.h"

CPlayer::CPlayer() :
	m_tPlayerInfo{},
	playerCurState(PLAYER_STATE::IDLE),
	playerPrevState(PLAYER_STATE::IDLE),
	playerCurSkill(SKILL_STATE::END),
	m_fRunTime(0.3f),
	m_fCurTime(0.f),
	m_iCurPushKey((UINT)KEY::LAST),
	m_iDirX(1),
	m_iDirY(1),
	m_iKeyStack(0),
	m_pBullet(nullptr),
	m_pFireMotion(nullptr),
	m_pSkill(nullptr)
{
	CTexture* m_pTexRight = CResMgr::GetInst()->LoadTextur(L"Player_Motion_Right", L"Texture\\montion_right.bmp");//애니메이션 파일 넣기
	CTexture* m_pTexLeft = CResMgr::GetInst()->LoadTextur(L"Player_Motion_Left", L"Texture\\montion_left.bmp");//애니메이션 파일 넣기
	CTexture* m_pTexHitRight = CResMgr::GetInst()->LoadTextur(L"Player_Hit_Right", L"Texture\\motion_hit_right.bmp");
	CTexture* m_pTexHitLeft = CResMgr::GetInst()->LoadTextur(L"Player_Hit_Left", L"Texture\\motion_hit_left.bmp");
	CTexture* m_pTexRightAttack = CResMgr::GetInst()->LoadTextur(L"Player_Motion_Right_Attack", L"Texture\\motion_attack_right.bmp");
	CTexture* m_pTexLeftAttack = CResMgr::GetInst()->LoadTextur(L"Player_Motion_Left_Attack", L"Texture\\motion_attack_left.bmp");
	CTexture* m_pRightAttackJum = CResMgr::GetInst()->LoadTextur(L"Player_Motion_Right_Attack_Jum", L"Texture\\jump_attack_right.bmp");
	CTexture* m_pLeftAttackJum = CResMgr::GetInst()->LoadTextur(L"Player_Motion_Left_Attack_Jum", L"Texture\\jump_attack_left.bmp");
	CTexture* m_pRightSkillA = CResMgr::GetInst()->LoadTextur(L"Player_SkillA_Right", L"Texture\\skillA_right.bmp");
	CTexture* m_pLeftSkillA = CResMgr::GetInst()->LoadTextur(L"Player_SkillA_Left", L"Texture\\skillA_left.bmp");
	CTexture* m_pRandomFire = CResMgr::GetInst()->LoadTextur(L"Player_Skill_randomfire", L"Texture\\random_fire.bmp");
	CTexture* m_pWalkFire = CResMgr::GetInst()->LoadTextur(L"Player_Skill_walkfire", L"Texture\\walk_fire.bmp");
	m_pBullet = CResMgr::GetInst()->LoadTextur(L"Bullet", L"Texture\\bullet.bmp");//총알
	//m_pFireMotion = CResMgr::GetInst()->LoadTextur(L"Bullet", L"Texture\\fire.bmp");//발사 임펙트

	//공격 텍스트


	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Player_idle_right", m_pTexRight, Vec2(0.f, 0.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.2f, 10);
	GetAnimator()->FindAnimation(L"Player_idle_right")->Create(m_pTexRight, Vec2(0.f, 252.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"Player_walk_right", m_pTexRight, Vec2(0.f, 1008.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.2f, 8);
	GetAnimator()->CreateAnimation(L"Player_run_right", m_pTexRight, Vec2(0.f, 756.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.2f, 8);
	GetAnimator()->CreateAnimation(L"Player_jump_down_right", m_pTexRight, Vec2(1140.f, 504.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 2);
	GetAnimator()->CreateAnimation(L"Player_jump_up_right", m_pTexRight, Vec2(0.f, 504.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"Player_jump_air_right", m_pTexRight, Vec2(912.f, 504.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.2f, 1);

	//피격
	GetAnimator()->CreateAnimation(L"Player_Hit_right", m_pTexHitRight, Vec2(0.f, 0.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->CreateAnimation(L"Player_Hit_left", m_pTexHitLeft, Vec2(912.f, 0.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.1f, 5);

	GetAnimator()->CreateAnimation(L"Player_idle_left", m_pTexLeft, Vec2(2052.f, 0.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.2f, 10);
	GetAnimator()->FindAnimation(L"Player_idle_left")->Create(m_pTexLeft, Vec2(2052.f, 252.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"Player_walk_left", m_pTexLeft, Vec2(2052.f, 1008.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.2f, 8);
	GetAnimator()->CreateAnimation(L"Player_run_left", m_pTexLeft, Vec2(2052.f, 756.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.2f, 8);
	GetAnimator()->CreateAnimation(L"Player_jump_down_left", m_pTexLeft, Vec2(912.f, 504.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.1f, 2);
	GetAnimator()->CreateAnimation(L"Player_jump_up_left", m_pTexLeft, Vec2(2052.f, 504.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"Player_jump_air_left", m_pTexLeft, Vec2(1140.f, 504.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.1f, 1);

	//공격모션
	GetAnimator()->CreateAnimation(L"Player_attack_down_right", m_pTexRightAttack, Vec2(0.f, 0.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.07f, 10);
	GetAnimator()->FindAnimation(L"Player_attack_down_right")->Create(m_pTexRightAttack, Vec2(0.f, 252.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.07f, 6);
	GetAnimator()->CreateAnimation(L"Player_attack_right", m_pTexRightAttack, Vec2(0.f, 504.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.07f, 10);
	GetAnimator()->FindAnimation(L"Player_attack_right")->Create(m_pTexRightAttack, Vec2(0.f, 756.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.07f, 6);
	GetAnimator()->CreateAnimation(L"Player_attack_sliding_right", m_pTexRightAttack, Vec2(0.f, 1008.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"Player_attack_jump_right", m_pRightAttackJum, Vec2(0.f, 0.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 6);

	GetAnimator()->CreateAnimation(L"Player_attack_down_left", m_pTexLeftAttack, Vec2(2052.f, 0.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.07f, 10);
	GetAnimator()->FindAnimation(L"Player_attack_down_left")->Create(m_pTexLeftAttack, Vec2(2052.f, 252.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.07f, 6);
	GetAnimator()->CreateAnimation(L"Player_attack_left", m_pTexLeftAttack, Vec2(2052.f, 504.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.07f, 10);
	GetAnimator()->FindAnimation(L"Player_attack_left")->Create(m_pTexLeftAttack, Vec2(2052.f, 756.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.07f, 6);
	GetAnimator()->CreateAnimation(L"Player_attack_sliding_left", m_pTexLeftAttack, Vec2(2052.f, 1008.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"Player_attack_jump_left", m_pLeftAttackJum, Vec2(1140.f, 0.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.1f, 6);
	//-40은 offset

	//스킬 모션 어우 어지러워
	//A
	GetAnimator()->CreateAnimation(L"Player_skill_kick_right", m_pRightSkillA, Vec2(0.f, 0.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"Player_skill_punisher_right", m_pRightSkillA, Vec2(0.f, 252.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 10);
	GetAnimator()->FindAnimation(L"Player_skill_punisher_right")->Create(m_pRightSkillA, Vec2(0.f, 504.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"Player_skill_mach_kick_right", m_pRightSkillA, Vec2(0.f, 756.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.07f, 6);
	GetAnimator()->CreateAnimation(L"Player_skill_windmill", m_pRightSkillA, Vec2(0.f, 1008.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 6);

	GetAnimator()->CreateAnimation(L"Player_skill_kick_left", m_pLeftSkillA, Vec2(2052.f, 0.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"Player_skill_punisher_left", m_pLeftSkillA, Vec2(2052.f, 252.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.1f, 10);
	GetAnimator()->FindAnimation(L"Player_skill_punisher_left")->Create(m_pLeftSkillA, Vec2(2052.f, 504.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"Player_skill_mach_kick_left", m_pLeftSkillA, Vec2(2052.f, 756.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.07f, 6);


	//random
	GetAnimator()->CreateAnimation(L"Player_skill_randomfire", m_pRandomFire, Vec2(0.f, 0.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 10);
	GetAnimator()->FindAnimation(L"Player_skill_randomfire")->Create(m_pRandomFire, Vec2(0.f, 252.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);
	GetAnimator()->FindAnimation(L"Player_skill_randomfire")->Create(m_pRandomFire, Vec2(0.f, 504.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 10);
	GetAnimator()->FindAnimation(L"Player_skill_randomfire")->Create(m_pRandomFire, Vec2(0.f, 756.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 5);

	//walkfire
	GetAnimator()->CreateAnimation(L"Player_skill_walkfire_stand_right", m_pWalkFire, Vec2(0.f, 0.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"Player_skill_walkfire_walk_right", m_pWalkFire, Vec2(0.f, 252.f), Vec2(228.f, 252.f), Vec2(228.f, 0.f), Vec2(0.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"Player_skill_walkfire_stand_left", m_pWalkFire, Vec2(1596.f, 504.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"Player_skill_walkfire_walk_left", m_pWalkFire, Vec2(1596.f, 756.f), Vec2(228.f, 252.f), Vec2(-228.f, 0.f), Vec2(-40.f, 0.f), 0.1f, 7);


	GetAnimator()->Play(L"Player_idle_right", true);

	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 60.f));
	GetCollider()->SetOffSet(Vec2(-20.f, 75.f));

	//CCameraMgr::GetInst()->SetTargetObj(this);

	CreateRigidBody();
	CreateGravity();
	CreateSkill();
}

CPlayer::~CPlayer()
{
	if (m_pSkill != nullptr)
	{
		delete m_pSkill;
	}

	if (m_pFSM != nullptr)
	{
		delete m_pFSM;
	}
}

void CPlayer::CreateFSM(CFSM* _pFSM)
{
	m_pFSM = _pFSM;
	m_pFSM->m_pOwner = this;
}

void CPlayer::update()
{
	//움직이기 전에 현재 스킬 사용이 되었는지 확인
	m_bOnSkill = CSkillMgr::GetInst()->IsOnSkill();
	update_doubleKey();

	if (m_pSkill != nullptr && m_bOnSkill)
	{
		m_pSkill->update();//내 현제 스킬 업데이트
		updateSkillState();
	}

	else if (m_pFSM != nullptr)
	{
		m_pFSM->update();
		updateState();
	}

}

void CPlayer::finalupdate()
{
	CObject::finalupdate();
}



void CPlayer::render(HDC _dc)
{
	component_render(_dc);
}

void CPlayer::updateState()
{
	CPlayerState* pPlayerState = m_pFSM->GetPlayerState();
	playerCurState = pPlayerState->GetType();
	CAnimator* pAninmaotr = GetAnimator();

	//방향잡기
	wstring strMotion = L"";
	wstring strOtherMtion = L"";
	wstring strDir = L"";
	wstring strOtherDir = L"";
	if (m_iDirX > 0)
	{
		strDir = L"_right";
		strOtherDir = L"_left";
	}
	else
	{
		strDir = L"_left";
		strOtherDir = L"_right";
	}


	switch (playerCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		strMotion = L"Player_idle";
		strMotion += strDir;
		pAninmaotr->Play(strMotion, true);
	}
	break;
	case PLAYER_STATE::WALK:
	{
		strMotion = L"Player_walk";
		strMotion += strDir;
		strOtherMtion = L"Player_walk" + strOtherDir;
		pAninmaotr->PlayMulti(strMotion, strOtherMtion, true);
	}
	break;
	case PLAYER_STATE::RUN:
	{
		strMotion = L"Player_run";
		strMotion += strDir;
		pAninmaotr->Play(strMotion, true);
	}
	break;
	case PLAYER_STATE::ATTACK:
	{
		strMotion = L"Player_attack";
		strMotion += strDir;
		strOtherMtion = L"Player_attack_down" + strDir;
		pAninmaotr->PlayMulti(strMotion, strOtherMtion, false);
		int iCurFram = pAninmaotr->GetCurAnimation()->GetCurFrame();
		m_pFSM->GetCurState()->SetCurFrame(iCurFram);
	}
	break;
	case PLAYER_STATE::ATTACK_DOWN:
	{
		strMotion = L"Player_attack_down";
		strMotion += strDir;
		strOtherMtion = L"Player_attack" + strDir;
		pAninmaotr->PlayMulti(strMotion, strOtherMtion, false);
		int iCurFram = pAninmaotr->GetCurAnimation()->GetCurFrame();
		m_pFSM->GetCurState()->SetCurFrame(iCurFram);
	}
	break;
	case PLAYER_STATE::ATTACK_SLIDING:
	{
		strMotion = L"Player_attack_sliding";
		strMotion += strDir;
		pAninmaotr->Play(strMotion, true);
	}
	break;
	case PLAYER_STATE::ATTACK_AIR:
	{
		strMotion = L"Player_attack_jump";
		strMotion += strDir;
		pAninmaotr->Play(strMotion, false);
		int iCurFram = pAninmaotr->GetCurAnimation()->GetCurFrame();
		m_pFSM->GetCurState()->SetCurFrame(iCurFram);
	}
	break;
	case PLAYER_STATE::JUMP:
	{
		strMotion = L"Player_jump_up";
		strMotion += strDir;
		strOtherMtion = L"Player_jump_up" + strOtherDir;
		pAninmaotr->PlayMulti(strMotion, strOtherMtion, false);
		int iCurFram = pAninmaotr->GetCurAnimation()->GetCurFrame();
		m_pFSM->GetCurState()->SetCurFrame(iCurFram);
	}
	break;
	case PLAYER_STATE::JUMP_AIR:
	{
		strMotion = L"Player_jump_air";
		strMotion += strDir;
		pAninmaotr->Play(strMotion, true);
	}
	break;
	case PLAYER_STATE::JUMP_DOWN:
	{
		strMotion = L"Player_jump_down";
		strMotion += strDir;
		pAninmaotr->Play(strMotion, false);
		int iCurFram = pAninmaotr->GetCurAnimation()->GetCurFrame();
		m_pFSM->GetCurState()->SetCurFrame(iCurFram);
	}
	break;

	case PLAYER_STATE::HIT:
	{
		strMotion = L"Player_Hit";
		strMotion += strDir;
		pAninmaotr->Play(strMotion, false);
		int iCurFram = pAninmaotr->GetCurAnimation()->GetCurFrame();
		m_pFSM->GetCurState()->SetCurFrame(iCurFram);
	}
	break;

	case PLAYER_STATE::SKILL:
		break;
	case PLAYER_STATE::DEAD:
		break;

	}
}

void CPlayer::updateSkillState()
{
	CAnimator* pAninmaotr = GetAnimator();
	playerCurSkill = CSkillMgr::GetInst()->GetCurSkill();

	//방향잡기 
	wstring strMotion = m_pSkill->GetCurSkill()->GetSkillName();
	wstring strDir = L"";

	if (m_iDirX > 0)
	{
		strDir = L"right";
	}
	else
		strDir = L"left";


	switch (playerCurSkill)
	{
	case SKILL_STATE::RANDOM_FIRE:
	{
		int iCurFram = pAninmaotr->FindAnimation(strMotion)->GetCurFrame();
		GetSkill()->GetCurSkill()->SetCurFram(iCurFram);
		pAninmaotr->Play(strMotion, false);
	}
	break;
	case SKILL_STATE::UPPER_KICK:
	{
		strMotion += strDir;
		int iCurFram = pAninmaotr->FindAnimation(strMotion)->GetCurFrame();
		GetSkill()->GetCurSkill()->SetCurFram(iCurFram);
		pAninmaotr->Play(strMotion, false);
	}
	break;

	case SKILL_STATE::MACH_KICK:
	{
		strMotion += strDir;
		int iCurFram = pAninmaotr->FindAnimation(strMotion)->GetCurFrame();
		GetSkill()->GetCurSkill()->SetCurFram(iCurFram);
		pAninmaotr->Play(strMotion, false);
	}
	break;

	case SKILL_STATE::WINDMILL:
	{
		int iCurFram = pAninmaotr->FindAnimation(strMotion)->GetCurFrame();
		GetSkill()->GetCurSkill()->SetCurFram(iCurFram);
		pAninmaotr->Play(strMotion, false);
	}
	break;
	case SKILL_STATE::WALK_FIRE:
	{
		pAninmaotr->Play(strMotion, true);
	}
	break;
	case SKILL_STATE::BUFF:
	{

	}
	break;
	case SKILL_STATE::END:
	{

	}
	break;
	}

}



void CPlayer::CreateBullet(CPlayer* _pPlayer, ATTACK_TYPE _eAttType)
{
	CBullet* pBullet = new CBullet(_pPlayer, _eAttType);
	CreateObject(pBullet, GROUP_TYPE::BULLET);

}
void CPlayer::HitPlayer(CCollider* _pOther, const tAttackInfo& _tAttInfo)
{
	m_tPlayerHit.m_fHitRcnt = _tAttInfo.m_fAttRcnt;
	m_tPlayerHit.m_fHitRigidityTime = _tAttInfo.m_fAttRigidityTime;
	m_tPlayerHit.m_fHitUpperRcnt = _tAttInfo.m_fAttUpperRcnt;

	float fDir = GetCollider()->GetFinalPos().x - _pOther->GetFinalPos().x;
	if (fDir > 0.f)
		fDir = 1.f;
	else
		fDir = -1.f;

	CGravity* pGravity = GetGravity();
	ATTACK_TYPE eAttackType = _tAttInfo.m_eAttType;
	if (playerCurState == PLAYER_STATE::UPPER_HIT || pGravity->IsGetGravity())
		eAttackType = ATTACK_TYPE::UPPER;

	switch (eAttackType)
	{
	case ATTACK_TYPE::UPPER:
	{
		m_tPlayerHit.m_fHitDir = fDir;
		GetGravity()->SetGravity(true);
		if (GetJumPos().IsZero())
			SetJumPos(GetCollider()->GetFinalPos());
		GetRigidBody()->SetVelocity(Vec2(0.f, m_tPlayerHit.m_fHitUpperRcnt));
		//GetRigidBody()->SetAccelA(Vec2(0.f, _tAtt.m_fAttUpperAcc));
		ChangeFSMState(m_pFSM, PLAYER_STATE::UPPER_HIT);
	}
	break;
	case ATTACK_TYPE::NORMAL:
	{
		m_tPlayerHit.m_fHitDir = fDir;
		ChangeFSMState(m_pFSM, PLAYER_STATE::HIT);
	}
	break;
	}

	//m_tPlayerInfo.m_iHP -= _tAttInfo.m_fAttackDamage;
}

void CPlayer::OnColliderEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if (pObj->GetTag() == GROUP_TYPE::MONSTER_SKILL
		&& m_tPlayerInfo.m_iHP != 0)
	{
		if (dynamic_cast<CFireBall*>(pObj))
		{
			CFireBall* pFire = dynamic_cast<CFireBall*>(pObj);
			HitPlayer(_pOther, pFire->GetAttInfo());
		}
	}

	//if (m_tPlayerInfo.m_iHP == 0)
	//{
	//	ChangeFSMState(m_pFSM, PLAYER_STATE::DEAD);
	//}
}

void CPlayer::OnColliderExit(CCollider* _pOther)
{

}

void CPlayer::OnCollision(CCollider* _pOther)
{

}


void CPlayer::CreateSkill()
{
	m_pSkill = new CSkill;
	m_pSkill->m_pOwner = this;
}

void CPlayer::update_doubleKey()
{
	if (GetGravity()->IsGetGravity())
	{
		m_iKeyStack = 0;
		return;
	}

	m_fCurTime += fDT;
	if (m_bIsOnDobuleKey)
	{
		m_fCurTime = 0.f;
	}

	if (m_fCurTime >= m_fRunTime && !m_bIsOnDobuleKey)
	{
		//지정 시간이 지나면 더블키 스택을 0으로 현재 키 또한 0으로 초기화
		m_iCurPushKey = (UINT)KEY::LAST;
	}

	if (KEY_TAP(KEY::LEFT))
	{
		m_iCurPushKey = (UINT)KEY::LEFT;
		if (m_iCurPushKey == m_iPrePushKey)
		{
			++m_iKeyStack;
		}
		else
		{
			m_iKeyStack = 1;
			m_fCurTime = 0.f;
		}
	}

	else if (KEY_AWAY(KEY::LEFT))
	{
		if (m_bIsOnDobuleKey)
		{
			m_iCurPushKey = (UINT)KEY::LAST;
			m_iKeyStack = 0;
		}
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		m_iCurPushKey = (UINT)KEY::RIGHT;
		if (m_iCurPushKey == m_iPrePushKey)
		{
			++m_iKeyStack;
		}
		else
		{
			m_iKeyStack = 1;
			m_fCurTime = 0.f;
		}
	}

	else if (KEY_AWAY(KEY::RIGHT))
	{
		if (m_bIsOnDobuleKey)
		{
			m_iCurPushKey = (UINT)KEY::LAST;
			m_iKeyStack = 0;
		}

	}



	if (m_iKeyStack >= 2)
		m_bIsOnDobuleKey = true;
	else
		m_bIsOnDobuleKey = false;

	m_iPrePushKey = m_iCurPushKey;
}