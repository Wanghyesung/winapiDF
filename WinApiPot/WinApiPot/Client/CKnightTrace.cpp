#include "pch.h"
#include "CKnightTrace.h"

#include "AI.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CKnight.h"
#include "CMonster.h"
#include "CPlayer.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CGravity.h"

#include "CKnightAttack.h"

CKnightTrace::CKnightTrace():
	CState(MONSTER_STATE::TRACE)
{

}

CKnightTrace::~CKnightTrace()
{

}

void CKnightTrace::enter()
{

}

void CKnightTrace::exit()
{
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	CState::exit();
}

void CKnightTrace::update()
{
	CMonster* pMon = GetMonster();
	tMonInfo& tMInfo = pMon->GetMonInfo();

	CObject* pPlayer = SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();

	Vec2 vPos = pMon->GetPos();
	Vec2 vPlayerPos = pPlayer->GetPos();

	Vec2 vDiff = (vPlayerPos - vPos);//길이값 

	bool isJump = pPlayer->GetGravity()->IsGetGravity();


	if (isJump)//점프중이라면
	{
		vPos = GetMonster()->GetPos();
		vPlayerPos = pPlayer->GetJumPos() + pPlayer->GetCollider()->GetOffSetPos(); //점프할 떄 착지 지점
	}

	else
	{
		vPos = GetMonster()->GetPos();  //내 지점
		vPlayerPos = pPlayer->GetCollider()->GetFinalPos(); // 상대 지점
	}

	int iDir = 0;//방향값
	vDiff.x > 0 ? iDir = 1 : iDir = -1;
	SetDir(iDir);

	
	if (vDiff.Length() > tMInfo.m_fnavigationScope)
	{
		ChangeAIState(GetAI(), MONSTER_STATE::IDLE);
		return;
	}

	else if (check_skill())
	{
		return;
	}
	
	vDiff.NormalRize();
	GetMonster()->GetRigidBody()->AddForce(vDiff * tMInfo.m_fspeed);
	
}

bool CKnightTrace::check_skill()
{
	CKnight* pMon = (CKnight*)GetMonster();
	unordered_map<wstring, tKnight_Attack>::iterator iter = pMon->m_hashMonSkill.begin();

	for (; iter != pMon->m_hashMonSkill.end(); ++iter)
	{
		if (iter->second.m_fSkillTime == 0.f)
		{
			ChangeAIState(GetAI(), MONSTER_STATE::ATTACK);
			((CKnightAttack*)GetAI()->GetCurState())->SetAttackName(iter->first);
			return true;
		}
	}
	return false;
}
