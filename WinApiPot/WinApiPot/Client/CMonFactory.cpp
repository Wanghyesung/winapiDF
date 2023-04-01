#include "pch.h"
#include "CMonFactory.h"

#include "CRigidBody.h"


#include "CMonster.h"
#include "CDragon.h"
#include "CBlueDragon.h"
#include "CBrDragon.h"
#include "CKnight.h"
#include "CLord.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CNearAttack.h"
#include "CStandOffAttack.h"
#include "CExclusiveTrace.h"
#include "CUltimateState.h"
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
		pMon->SetScale(Vec2(50.f, 50.f));
		tAttackInfo m_tAtt = {};
		m_tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
		m_tAtt.m_fAttRcnt = 50.f;
		m_tAtt.m_fAttackDamage = 8.f;
		m_tAtt.m_fAttRigidityTime = 0.5f;
		m_tAtt.m_fAttUpperRcnt = -60.f;
		tMonSkill tSkill1 = { eMonsterAttackType::NORMAL, m_tAtt,L"_Normal_Attack", 2, 20, 3.f, 5.f};
		pMon->add_skill(tSkill1);
		m_tAtt.m_fAttackDamage = 12.f;
		m_tAtt.m_fAttRigidityTime = 0.7f;
		tMonSkill tSkill2 = { eMonsterAttackType::NORMAL, m_tAtt ,L"_Attack", 4, 20, 7.f, 5.f };
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

		//몬스터 공격
		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(50.f, 20.f);
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

	case MON_TYPE::BROWN_DRAGON:
	{
		pMon = new CBrDragon;
		pMon->SetTag(GROUP_TYPE::MONSTER);
		pMon->SetPos(_vPos);
		pMon->SetScale(Vec2(50.f, 50.f));
		tAttackInfo m_tAtt = {};
		m_tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
		m_tAtt.m_fAttRcnt = 50.f;
		m_tAtt.m_fAttackDamage = 12.f;
		m_tAtt.m_fAttRigidityTime = 0.5f;
		m_tAtt.m_fAttUpperRcnt = -60.f;
		tMonSkill tSkill1 = { eMonsterAttackType::NORMAL, m_tAtt,L"_Normal_Attack", 2, 20, 3.f, 5.f };
		pMon->add_skill(tSkill1);
		m_tAtt.m_fAttackDamage = 18.f;
		m_tAtt.m_fAttRigidityTime = 0.7f;
		tMonSkill tSkill2 = { eMonsterAttackType::NORMAL, m_tAtt ,L"_Attack", 4, 20, 7.f, 5.f };
		pMon->add_skill(tSkill2);
		//내 공격 오브젝트 추가
		pMon->set_attackobj(_eSceneType);

		tMonInfo info = {};
		info.m_fnavigationScope = 400.f;
		info.m_iHp = 100;
		info.m_fspeed = 220.f;
		pMon->SettMonInfo(info);

		tHitInfo tHitInfo = {};
		tHitInfo.m_iMaxHitFrame = 5;
		pMon->SetHitInfo(tHitInfo);

		//몬스터 공격
		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(50.f, 20.f);
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
		pAI->SetCurState(MONSTER_STATE::IDLE);
		pMon->SetAI(pAI);
	}
	break;

	case MON_TYPE::LORD:
	{
		pMon = new CLord;
		pMon->SetTag(GROUP_TYPE::MONSTER);
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.m_fnavigationScope = 400.f;
		info.m_iHp = 100;
		info.m_fspeed = 70.f;
		pMon->SettMonInfo(info);

		tHitInfo tHitInfo = {};
		tHitInfo.m_iMaxHitFrame = 2;
		pMon->SetHitInfo(tHitInfo);

		//몬스터 스킬 추가
		tAttackInfo m_tAtt = {};
		m_tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
		m_tAtt.m_fAttRcnt = 50.f;
		m_tAtt.m_fAttackDamage = 15.f;
		m_tAtt.m_fAttRigidityTime = 0.5f;
		m_tAtt.m_fAttUpperRcnt = -60.f;
		tMonSkill tSkill1 = {eMonsterAttackType::NORMAL, m_tAtt,L"_Normal_Attack", 4, 7, 3.f, 5.f };
		pMon->add_skill(tSkill1);
		//Lord_Skill
		
		tAttackInfo m_tAtt2 = {};
		m_tAtt2.m_eAttType = ATTACK_TYPE::NORMAL;
		m_tAtt2.m_fAttRcnt = 1.f;
		m_tAtt2.m_fAttackDamage = 2.f;
		m_tAtt2.m_fAttRigidityTime = 0.4f;
		m_tAtt2.m_fAttUpperRcnt = -60.f;
		tMonSkill tSkill2 = { eMonsterAttackType::SKILL, m_tAtt2,L"_Skill", 3, 20, 12.f, 12.f };
		pMon->add_skill(tSkill2);

		pMon->set_attackobj(_eSceneType);

		//몬스터 공격
		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(50.f, 20.f);
		//스킬이면 attackobj없이 그냥 오브젝트 생성
		tAttackInfo.m_fSkillRange = Vec2(400.f, 100.f);
		tAttackInfo.m_fAttackDamage = 10.f;
		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->AddState(new CNearAttack);
		pAI->AddState(new CStandOffAttack);
		pAI->AddState(new CUltimateState);
		pAI->AddState(new CDeadState);
		pAI->SetCurState(MONSTER_STATE::IDLE);
		pMon->SetAI(pAI);
	}
		break;

	case MON_TYPE::DRAGON:
	{
		pMon = new CDragon;
		//몬스터 스킬 공격
		tAttackInfo m_tAtt = {};
		m_tAtt.m_eAttType = ATTACK_TYPE::UPPER;
		m_tAtt.m_fAttRcnt = 50.f;
		m_tAtt.m_fAttackDamage = 5.f;
		m_tAtt.m_fAttRigidityTime = 0.5f;
		m_tAtt.m_fAttUpperRcnt = -60.f;

		tMonSkill tSkill = { eMonsterAttackType::NORMAL, m_tAtt, L"_Normal_Attack", 1, 20, 5.f, 5.f};
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

		//몬스터 공격
		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(300.f,25.f);
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

	case MON_TYPE::KNIGHT_RED:
	{
		pMon = new CBrDragon;
		pMon->SetTag(GROUP_TYPE::MONSTER);
		pMon->SetPos(_vPos);
		//pMon->SetScale(Vec2(50.f, 50.f));
		
		pMon->set_attackobj(_eSceneType);

		tMonInfo info = {};
		info.m_fnavigationScope = 400.f;
		info.m_iHp = 100;
		info.m_fspeed = 140.f;
		pMon->SettMonInfo(info);

		tHitInfo tHitInfo = {};
		tHitInfo.m_iMaxHitFrame = 5;
		pMon->SetHitInfo(tHitInfo);


		//몬스터 공격
		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(50.f, 20.f);
		tAttackInfo.m_fAttackDamage = 10.f;
		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		AI* pAI = new AI;
		
		pAI->SetCurState(MONSTER_STATE::STONE);
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


