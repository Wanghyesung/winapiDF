#include "pch.h"
#include "CExclusiveTrace.h"
#include "CAttackState.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CGravity.h"
#include "CCollider.h"
#include "CRigidBody.h"

#include "CAnimation.h"
#include "CAnimator.h"

#include "CTimeMgr.h"
#include "AI.h"
#include "CRigidBody.h"

#define ATTACKRANGE 30.f

CExclusiveTrace::CExclusiveTrace():
	CState(MONSTER_STATE::TRACE)
{

}

CExclusiveTrace::~CExclusiveTrace()
{

}


void CExclusiveTrace::init_attack(UINT _iDir)
{
	vector<tMonSkill>& vecSkill = GetMonster()->GetVecSkill();
	for (int i = 0; i < vecSkill.size(); ++i)
	{
		if (vecSkill[i].m_fSkillTime <= 0.f)
		{
			vecSkill[i].m_fSkillTime = vecSkill[i].m_fMaxSkillTime;
			m_eNextState = MONSTER_STATE::ATTACK;
			GetAI()->GetState(m_eNextState)->SetDir(_iDir);
			((CAttackState*)GetAI()->GetState(m_eNextState))->SetAttackName(vecSkill[i].m_strAttackName);
			((CAttackState*)GetAI()->GetState(m_eNextState))->SetAttackFrame(vecSkill[i].m_iStartFrame); 
			ChangeAIState(GetAI(), m_eNextState);
			return;
		}
	}
}


void CExclusiveTrace::update()
{
	if (GetMonster()->IsDead())
		return;

	vector<CObject*> vecPlayer = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::PLAYER);
	
	if (vecPlayer.size() == 0)
		return;
	else
	{
		m_pTarget = (CPlayer*)vecPlayer[0];
	}
	//죽었다면 return
	//if (m_pTarget == nullptr)
	//	return;
	//else if (m_pTarget->IsDead())
	//	return;
	

	tMonInfo monInfo = GetMonster()->GetMonInfo();
	tAttackInfo tMonAttackInfo = GetMonster()->GetAttackInfo();

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

	vDiff = (vTargetPos - vPos);//길이값 

	int iDir = 0;//방향값
	vDiff.x > 0 ? iDir = 1 : iDir = -1;
	SetDir(iDir);

	//다시 idel로
	if (vDiff.Length() > monInfo.m_fnavigationScope * 1.5f)//2배 거리로
	{
		m_eNextState = MONSTER_STATE::IDLE;
		ChangeAIState(GetAI(), m_eNextState);
		return; 
	}
	

	//공격
	if (vDiff.Length() <= tMonAttackInfo.m_fAttackRange.Length())
	{
		//플레이어 y값에 맞게
		vDiff.NormalRize();
		GetMonster()->GetRigidBody()->AddForce(Vec2(0.f, vDiff.y * monInfo.m_fspeed));
		//공격
		
		if(abs(vPos.y - vTargetPos.y) <= ATTACKRANGE)
		{
			init_attack(iDir);
			return;
		}
	}

	else
	{
		vDiff.NormalRize();
		GetMonster()->GetRigidBody()->AddForce(vDiff * monInfo.m_fspeed);
	}
	

	
}


void CExclusiveTrace::exit()
{
	GetMonster()->GetAnimator()->GetCurAnimation()->SetFram(0);
}

void CExclusiveTrace::enter()
{
}
