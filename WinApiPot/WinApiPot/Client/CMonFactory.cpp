#include "pch.h"
#include "CMonFactory.h"

#include "CRigidBody.h"


#include "CMonster.h"
#include "CDragon.h"
#include "CBlueDragon.h"
#include "CBrDragon.h"
#include "CKnight.h"
#include "CLord.h"
#include "CNaias.h"
#include "CArdor.h"
#include "CEvileye.h"
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

//이블아이
#include "CEvileyeIdel.h"
#include "CEvileyeAttack.h"
#include "CEvileyeTrace.h"

//나이트
#include "CStoneState.h"
#include "CKnightAttack.h"
#include "CKnightTrace.h"

//나이아스
#include "CNaiasAttack.h"
#include "CNaiasTrace.h"

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
	
		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);
		
		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);

		CNearAttack* pAtt = new CNearAttack;
		pAtt->SetAnimSound(L"drgm_atk");
		pAI->AddState(pAtt);

		CHitState* pHit = new CHitState;
		pHit->SetAnimSound(L"drgm_dmg");
		pAI->AddState(pHit);

		CHitUpper* pHitUp = new CHitUpper;
		pHitUp->SetAnimSound(L"drgm_dmg");
		pAI->AddState(pHitUp);

		CDeadState* pDead = new CDeadState;
		pDead->SetAnimSound(L"drgm_die");
		pAI->AddState(pDead);

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
		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		CNearAttack* pAtt = new CNearAttack;
		pAtt->SetAnimSound(L"drgm_atk");
		pAI->AddState(pAtt);

		CHitState* pHit = new CHitState;
		pHit->SetAnimSound(L"drgm_dmg");
		pAI->AddState(pHit);

		CHitUpper* pHitUp = new CHitUpper;
		pHitUp->SetAnimSound(L"drgm_dmg");
		pAI->AddState(pHitUp);

		CDeadState* pDead = new CDeadState;
		pDead->SetAnimSound(L"drgm_die");
		pAI->AddState(pDead);
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

	  	CNearAttack* pAtt = new CNearAttack;
		pAtt->SetAnimSound(L"zieg_laser");
		pAI->AddState(pAtt);

		CStandOffAttack* pStand = new CStandOffAttack;
		pStand->SetAnimSound(L"zieg_spark");
		pAI->AddState(pStand);

		pAI->AddState(new CUltimateState);

		CDeadState* pDead = new CDeadState;
		pDead->SetAnimSound(L"zieg_die");
		pAI->AddState(pDead);

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

		CAttackState* pAtt = new CAttackState;
		pAtt->SetAnimSound(L"fdrg_fire");
		pAI->AddState(pAtt);

        CHitState* pHit	= new CHitState;
		pHit->SetAnimSound(L"fdrg_dmg");
		pAI->AddState(pHit);

		CHitUpper* pHitUp = new CHitUpper;
		pHitUp->SetAnimSound(L"fdrg_dmg");
		pAI->AddState(pHitUp);

		CDeadState* pDead = new CDeadState;
		pDead->SetAnimSound(L"fdrg_die");
		pAI->AddState(pDead);

		pAI->SetCurState(MONSTER_STATE::IDLE);
		pMon->SetAI(pAI);
	}
	break;

	case MON_TYPE::KNIGHT_RED:
	{
		pMon = new CKnight;
		((CKnight*)pMon)->setTexScale(Vec2(250.f, 150.f));
		((CKnight*)pMon)->init(L"Knight");
		pMon->SetTag(GROUP_TYPE::MONSTER);
		pMon->SetPos(_vPos);
		//pMon->SetScale(Vec2(50.f, 50.f));
		
		pMon->set_attackobj(_eSceneType);

		tMonInfo info = {};
		info.m_fnavigationScope = 400.f;
		info.m_iHp = 100;
		info.m_fspeed = 200.f;
		pMon->SettMonInfo(info);

		tHitInfo tHitInfo = {};
		tHitInfo.m_iMaxHitFrame = 5;
		pMon->SetHitInfo(tHitInfo);


		//몬스터 공격
		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(50.f, 20.f);
		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		AI* pAI = new AI;
		pAI->AddState(new CStoneState);
		pAI->AddState(new CIdleState);
		pAI->AddState(new CKnightTrace);

		CKnightAttack* pKnightAtt = new CKnightAttack;
		pKnightAtt->SetAnimSound(L"hunt_atk");
		pAI->AddState(pKnightAtt);

		CHitState* pHit = new CHitState;
		pHit->SetAnimSound(L"hunt_comm");
		pAI->AddState(pHit);

		CHitUpper* pHitUp = new CHitUpper;
		pHitUp->SetAnimSound(L"hunt_comm");
		pAI->AddState(pHitUp);

		CDeadState* pDead = new CDeadState;
		pDead->SetAnimSound(L"hunt_die");
		pAI->AddState(pDead);

		pAI->SetCurState(MONSTER_STATE::STONE);
		pMon->SetAI(pAI);
	}
	break;

	case MON_TYPE::KNIGHT_BROWN:
	{
		pMon = new CKnight;
		((CKnight*)pMon)->setTexScale(Vec2(300.f, 150.f));
		((CKnight*)pMon)->init(L"Knight2");
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
		
		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		AI* pAI = new AI;
		pAI->AddState(new CStoneState);
		pAI->AddState(new CIdleState);
		pAI->AddState(new CKnightTrace);

		CKnightAttack* pKnightAtt = new CKnightAttack;
		pKnightAtt->SetAnimSound(L"hunt_atk");
		pAI->AddState(pKnightAtt);

		CHitState* pHit = new CHitState;
		pHit->SetAnimSound(L"hunt_comm");
		pAI->AddState(pHit);

		CHitUpper* pHitUp = new CHitUpper;
		pHitUp->SetAnimSound(L"hunt_comm");
		pAI->AddState(pHitUp);

		CDeadState* pDead = new CDeadState;
		pDead->SetAnimSound(L"hunt_die");
		pAI->AddState(pDead);

		pAI->SetCurState(MONSTER_STATE::STONE);
		pMon->SetAI(pAI);

	}
	break;

	case MON_TYPE::KNIGHT_GREEN:
	{
		pMon = new CKnight;
		((CKnight*)pMon)->setTexScale(Vec2(300.f, 200.f));
		((CKnight*)pMon)->setTexOffset(Vec2(10.f, -40.f));
		((CKnight*)pMon)->init(L"Knight3");
		pMon->SetTag(GROUP_TYPE::MONSTER);
		pMon->SetPos(_vPos);
		//pMon->SetScale(Vec2(50.f, 50.f));

		pMon->set_attackobj(_eSceneType);

		tMonInfo info = {};
		info.m_fnavigationScope = 500.f;
		info.m_iHp = 100;
		info.m_fspeed = 170.f;
		pMon->SettMonInfo(info);

		tHitInfo tHitInfo = {};
		tHitInfo.m_iMaxHitFrame = 5;
		pMon->SetHitInfo(tHitInfo);


		//몬스터 공격
		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(50.f, 20.f);

		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		AI* pAI = new AI;
		pAI->AddState(new CStoneState);
		pAI->AddState(new CIdleState);
		pAI->AddState(new CKnightTrace);

		CKnightAttack* pKnightAtt = new CKnightAttack;
		pKnightAtt->SetAnimSound(L"hunt_atk");
		pAI->AddState(pKnightAtt);

		CHitState* pHit = new CHitState;
		pHit->SetAnimSound(L"hunt_comm");
		pAI->AddState(pHit);

		CHitUpper* pHitUp = new CHitUpper;
		pHitUp->SetAnimSound(L"hunt_comm");
		pAI->AddState(pHitUp);

		CDeadState* pDead = new CDeadState;
		pDead->SetAnimSound(L"hunt_die");
		pAI->AddState(pDead);

		pAI->SetCurState(MONSTER_STATE::STONE);
		pMon->SetAI(pAI);

	}
	break;

	case MON_TYPE::NAIAS:
	{
		pMon = new CNaias;
		pMon->SetTag(GROUP_TYPE::MONSTER);
		pMon->SetPos(_vPos);
		//pMon->SetScale(Vec2(50.f, 50.f));

		pMon->set_attackobj(_eSceneType);

		tMonInfo info = {};
		info.m_fnavigationScope = 300.f;
		info.m_iHp = 100;
		info.m_fspeed = 150.f;
		pMon->SettMonInfo(info);

		tHitInfo tHitInfo = {};
		tHitInfo.m_iMaxHitFrame = 6;
		pMon->SetHitInfo(tHitInfo);


		//몬스터 공격 범위
		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(60.f, 30.f);

		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		AI* pAI = new AI;
	
		pAI->AddState(new CIdleState);
		pAI->AddState(new CNaiasTrace);

		CNaiasAttack* pNaiasAttack = new CNaiasAttack;
		pNaiasAttack->SetAnimSound(L"watersoul_atk_1");
		pAI->AddState(pNaiasAttack);

		CHitState* pHit = new CHitState;
		pHit->SetAnimSound(L"sfish_dmg");
		pAI->AddState(pHit);

		/*CHitUpper* pHitUp = new CHitUpper;
		pHitUp->SetAnimSound(L"hunt_comm");
		pAI->AddState(pHitUp);*/

		CDeadState* pDead = new CDeadState;
		pDead->SetAnimSound(L"sfish_die");
		pAI->AddState(pDead);

		pAI->SetCurState(MONSTER_STATE::IDLE);
		pMon->SetAI(pAI);
	}
	break;

	case MON_TYPE::ARDOR:
	{
		pMon = new CArdor;
		pMon->SetTag(GROUP_TYPE::MONSTER);
		pMon->SetPos(_vPos);
		//pMon->SetScale(Vec2(50.f, 50.f));

		pMon->set_attackobj(_eSceneType);

		tMonInfo info = {};
		info.m_fnavigationScope = 300.f;
		info.m_iHp = 100;
		info.m_fspeed = 140.f;
		pMon->SettMonInfo(info);

		tHitInfo tHitInfo = {};
		tHitInfo.m_iMaxHitFrame = 7;
		pMon->SetHitInfo(tHitInfo);


		//몬스터 공격 범위
		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(60.f, 40.f);

		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		AI* pAI = new AI;

		pAI->AddState(new CIdleState);
		pAI->AddState(new CNaiasTrace);

		CNaiasAttack* pNaiasAttack = new CNaiasAttack;
		pNaiasAttack->SetAnimSound(L"watersoul_atk_1");
		pAI->AddState(pNaiasAttack);

		CHitState* pHit = new CHitState;
		pHit->SetAnimSound(L"sfish_dmg");
		pAI->AddState(pHit);

		/*CHitUpper* pHitUp = new CHitUpper;
		pHitUp->SetAnimSound(L"hunt_comm");
		pAI->AddState(pHitUp);*/

		CDeadState* pDead = new CDeadState;
		pDead->SetAnimSound(L"sfish_die");
		pAI->AddState(pDead);

		pAI->SetCurState(MONSTER_STATE::IDLE);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::EVILEYE:
	{
		pMon = new CEvileye;
		//오른쪽 방향 이블아이
		((CEvileye*)pMon)->SetDir(1);
		pMon->SetTag(GROUP_TYPE::MONSTER);
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.m_iHp = 100;
		info.m_fspeed = 50.f;
		pMon->SettMonInfo(info);

		tHitInfo tHitInfo = {};
		tHitInfo.m_iMaxHitFrame = 3;
		pMon->SetHitInfo(tHitInfo);


		//몬스터 공격 범위
		tAttackInfo tAttackInfo = {};
		tAttackInfo.m_fAttackRange = Vec2(900.f, 600.f);

		pMon->SetAttackInfo(tAttackInfo);


		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		AI* pAI = new AI;

		pAI->AddState(new CEvileyeIdel);

		pAI->AddState(new CEvileyeAttack);

		pAI->AddState(new CEvileyeTrace);

		CHitState* pHit = new CHitState;
		pHit->SetAnimSound(L"hunt_comm");
		pAI->AddState(pHit);

		/*CHitUpper* pHitUp = new CHitUpper;
		pHitUp->SetAnimSound(L"hunt_comm");
		pAI->AddState(pHitUp);*/

		CDeadState* pDead = new CDeadState;
		pDead->SetAnimSound(L"evil_shout");
		pAI->AddState(pDead);

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


