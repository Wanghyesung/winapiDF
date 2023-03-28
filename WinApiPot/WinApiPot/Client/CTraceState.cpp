#include "pch.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CNearAttack.h"
#include "CStandOffAttack.h"
#include "CAttackObject.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CRigidBody.h"
#include "AI.h"
#include "CGravity.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CCollider.h"


CTraceState::CTraceState():
	CState(MONSTER_STATE::TRACE),
	m_pTarget(nullptr)
{

}

CTraceState::~CTraceState()
{

}


bool CTraceState::init_attack(int _iDir)
{
	vector<tMonSkill>& vecSkill = GetMonster()->GetVecSkill();
	for (int i = 0; i < vecSkill.size(); ++i)
	{
		if (vecSkill[i].m_fSkillTime <= 0.f && vecSkill[i].m_eSkillType == eMonsterAttackType::NORMAL)
		{
			vecSkill[i].m_fSkillTime = vecSkill[i].m_fMaxSkillTime;
			m_eNextState = MONSTER_STATE::ATTACK;
			GetAI()->GetState(m_eNextState)->SetDir(_iDir);
			((CNearAttack*)GetAI()->GetState(m_eNextState))->SetAttackName(vecSkill[i].m_strAttackName);
			((CNearAttack*)GetAI()->GetState(m_eNextState))->SetAttackFrame(vecSkill[i].m_iStartFrame, vecSkill[i].m_iEndFrame);
			GetAI()->GetCMonster()->GetSKillObj()->SetCurAttackIndex(i);
			ChangeAIState(GetAI(), m_eNextState);
			return true;
		}
	}
	return false;
}

bool CTraceState::init_skill(int _iDir)
{
	vector<tMonSkill>& vecSkill = GetMonster()->GetVecSkill();
	for (int i = 0; i < vecSkill.size(); ++i)
	{
		if (vecSkill[i].m_fSkillTime <= 0.f && vecSkill[i].m_eSkillType == eMonsterAttackType::SKILL)
		{
			//스킬 초기화
			vecSkill[i].m_fSkillTime = vecSkill[i].m_fMaxSkillTime;
			m_eNextState = MONSTER_STATE::ATTACK_STAND;
			GetAI()->GetState(m_eNextState)->SetDir(_iDir);
			((CStandOffAttack*)GetAI()->GetState(m_eNextState))->SetAttackName(vecSkill[i].m_strAttackName);
			((CStandOffAttack*)GetAI()->GetState(m_eNextState))->SetAttackFrame(vecSkill[i].m_iStartFrame, vecSkill[i].m_iEndFrame);
			ChangeAIState(GetAI(), m_eNextState);
			return true;
		}
	}
	return false;
}

void CTraceState::update()
{
	if (GetMonster()->IsDead())
		return;

	m_pTarget = (CPlayer*)SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();

	tMonInfo& monInfo = GetMonster()->GetMonInfo();
	tAttackInfo attackInfo = GetMonster()->GetAttackInfo();

	Vec2 vDiff;
	Vec2 vPos;
	Vec2 vTargetPos;

	bool isJump = m_pTarget->GetGravity()->IsGetGravity();//중력을 받고있는지 먼저 검사 = 점프중인지

	if (isJump)//점프중이라면
	{
		vPos = GetMonster()->GetPos();
		vTargetPos = m_pTarget->GetJumPos() + m_pTarget->GetCollider()->GetOffSetPos(); //점프할 떄 착지 지점
	}

	else
	{
		vPos = GetMonster()->GetPos();  //내 지점
		vTargetPos = m_pTarget->GetCollider()->GetFinalPos(); // 상대 지점
	}

	vDiff = vTargetPos - vPos;

	int iDir = 0;
	vDiff.x > 0 ? iDir = 1 : iDir = -1;

	SetDir(iDir);

	//다시 idel로
	if (vDiff.Length() > monInfo.m_fnavigationScope * 1.5f)//2배 거리로
	{
		m_eNextState = MONSTER_STATE::IDLE;
		ChangeAIState(GetAI(),m_eNextState);
		return;
	}
	
	//여기에 스킬 공격 넣기 스킬이 없다면 0d

	if (abs(vDiff.x) <= attackInfo.m_fSkillRange.x &&
		abs(vDiff.y) <= attackInfo.m_fSkillRange.y)
	{
		if(init_skill(iDir))
			return;
	}

	if (abs(vDiff.x) <= attackInfo.m_fAttackRange.x &&
			abs(vDiff.y) <= attackInfo.m_fAttackRange.y)
	{
		if(init_attack(iDir))
			return;
	}
	

	if (abs(vDiff.x) > attackInfo.m_fAttackRange.x ||
		abs(vDiff.y) > attackInfo.m_fAttackRange.y)
	{
		if (vDiff.IsZero())
			vDiff = Vec2(0.f, 0.f);
		else
			vDiff = vDiff.NormalRize() * monInfo.m_fspeed;

		GetMonster()->GetRigidBody()->AddForce(vDiff);
	}
	

}



void CTraceState::exit()
{
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
	CState::exit();
}

void CTraceState::enter()
{

}
