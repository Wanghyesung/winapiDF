#include "pch.h"
#include "CMonFactory.h"

#include "CRigidBody.h"


#include "CMonster.h"
#include "CDragon.h"
#include "CBlueDragon.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CNearAttack.h"
#include "CExclusiveTrace.h"
#include "CDefenseState.h"
#include "CHitState.h"
#include "CHitUpper.h"
#include "CDeadState.h"

CMonster* CMonFactory::CraeteMonster(MON_TYPE _monType, Vec2 _vPos, SCENE_TYPE _eSceneType)
{
	CMonster* pMon = nullptr;
	switch (_monType)
	{
	case MON_TYPE::BLUE_DRAGON:
	{
		pMon = new CBlueDragon;
		pMon->SetTag(GROUP_TYPE::MONSTER);
		pMon->SetPos(_vPos);
		//pMon->SetScale(Vec2(50.f, 50.f));
		tAttackInfo m_tAtt = {};
		m_tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
		m_tAtt.m_fAttRcnt = 50.f;
		m_tAtt.m_fAttackDamage = 8.f;
		m_tAtt.m_fAttRigidityTime = 0.5f;
		m_tAtt.m_fAttUpperRcnt = -60.f;
		tMonSkill tSkill1 = { eMonsterAttackType::NORMAL,m_tAtt,L"_Normal_Attack", 2, 3.f, 5.f};
		pMon->add_skill(tSkill1);
		m_tAtt.m_fAttackDamage = 12.f;
		m_tAtt.m_fAttRigidityTime = 1.f;
		tMonSkill tSkill2 = { eMonsterAttackType::NORMAL,m_tAtt ,L"_Attack", 4, 7.f, 5.f };
		pMon->add_skill(tSkill2);
		//내 공격 오브젝트 추가
		pMon->set_attackobj(_eSceneType);

		tMonInfo info = {};
		info.m_fnavigationScope = 400.f;
		info.m_iHp = 100;
		info.m_fspeed = 150.f;
		pMon->SettMonInfo(info);
		
		tHitInfo tHitInfo = {};
		tHitInfo.m_iMaxHitFrame = 5;
		pMon->SetHitInfo(tHitInfo);

		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(50.f, 20.f);
		tAttackInfo.m_fAttackTime = 4.f;
		tAttackInfo.m_fAttackDamage = 10.f;
		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);
		
		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->AddState(new CNearAttack);
		pAI->AddState(new CHitState);
		pAI->AddState(new CHitUpper);
		pAI->AddState(new CDeadState);
		pAI->AddState(new CDefenseState);
		pAI->SetCurState(MONSTER_STATE::IDLE);
		pMon->SetAI(pAI);

	}
	break;
	case MON_TYPE::RANGE:
		break;

	case MON_TYPE::DRAGON:
	{
		pMon = new CDragon;
		tAttackInfo m_tAtt = {};
		m_tAtt.m_eAttType = ATTACK_TYPE::UPPER;
		m_tAtt.m_fAttRcnt = 50.f;
		m_tAtt.m_fAttackDamage = 5.f;
		m_tAtt.m_fAttRigidityTime = 0.5f;
		m_tAtt.m_fAttUpperRcnt = -60.f;

		tMonSkill tSkill = { eMonsterAttackType::NORMAL,m_tAtt,L"_Normal_Attack", 1, 5.f, 5.f};
		pMon->add_skill(tSkill);

		pMon->SetPos(_vPos);
		//pMon->SetScale(Vec2(50.f, 50.f));
		pMon->SetTag(GROUP_TYPE::MONSTER);

		tMonInfo info = {};
		info.m_fnavigationScope = 400.f;
		info.m_iHp = 100;
		info.m_fspeed = 150.f;
		pMon->SettMonInfo(info);

		tHitInfo tHitInfo = {};
		tHitInfo.m_iMaxHitFrame = 3;
		pMon->SetHitInfo(tHitInfo);


		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(300.f,25.f);
		tAttackInfo.m_fAttackTime = 5.f;
		//tAttackInfo.m_fAttackDamage = 50.f;
		pMon->SetAttackInfo(tAttackInfo);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CExclusiveTrace);
		pAI->AddState(new CAttackState);

		pAI->AddState(new CHitState);
		pAI->AddState(new CHitUpper);
		pAI->AddState(new CDeadState);

		pAI->SetCurState(MONSTER_STATE::IDLE);
		pMon->SetAI(pAI);
	}
	break;

	}


	assert(pMon);

	return pMon;
}

CMonFactory::~CMonFactory()
{
}


