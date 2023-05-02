#include "pch.h"
#include "SceneTower_4.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CMonFactory.h"
#include "CMonster.h"
#include "CMonInterface.h"

#include "CGate.h"
#include "CDragonObj.h"
#include "CCrystalPillar.h"

#include "CCollider.h"

#include "CCameraMgr.h"
#include "CColliderMgr.h"
#include "CSkillMgr.h"

#include "CPlayer.h"
#include "CStoneBox.h"


#include "CInventory.h"
#include "CMPItem.h"
#include "CHPItem.h"
#include "CInventoryMgr.h"

#include "CTemWall.h"

#include "CSound.h"

SceneTower_4::SceneTower_4():
	m_eType(SCENE_TYPE::DUNGEON_4)
{
	SetDungeonType(DUNGEON_TYPE::LORD);
}

SceneTower_4::~SceneTower_4()
{
}

void SceneTower_4::Init()
{
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"dungeon_4", L"..\\OutPut\\bin_release\\Content\\Tile\\tile_4.bmp");
	SetBackGround(m_pBackGround);

	//������� ��� �����
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() - 180;
	tInfo.fLeftWidth = GetStartDrawPoint().x + 40;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);

	m_pBackSound
		= CResMgr::GetInst()->LoadSound(L"draconian_tower", L"..\\OutPut\\bin_release\\Content\\Sound\\draconian_tower.wav");



	CObject* pObj = CreatePlayer(Vec2(300.f, 450.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(672.f, 110.f));
	pTemWall->GetCollider()->SetScale(Vec2(1344.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);

	CDragonObj* pStone = new CDragonObj;
	pStone->SetPos(Vec2(30.f, 450.f));
	pStone->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone, GROUP_TYPE::STONE_BOX);

	CDragonObj* pStone3 = new CDragonObj;
	pStone3->SetPos(Vec2(30.f, 550.f));
	pStone3->GetCollider()->SetScale(Vec2(50.f, 50.f));
	AddObject(pStone3, GROUP_TYPE::STONE_BOX);

	CMonster* pBrDragon4_1 = CMonFactory::CraeteMonster(MON_TYPE::BROWN_DRAGON, Vec2(500.f, 500.f), m_eType);
	pBrDragon4_1->SetName(L"brDragon_4_1");
	CMonInterface* pBrDragonInter4_1 = new CMonInterface(pBrDragon4_1->GetName(),44);
	pBrDragonInter4_1->SetScale(Vec2(626, 29));
	pBrDragonInter4_1->SetPos(Vec2(40, 20));
	AddObject(pBrDragonInter4_1, GROUP_TYPE::UI);
	AddObject(pBrDragon4_1, GROUP_TYPE::MONSTER);

	CMonster* pDragon4_1 = CMonFactory::CraeteMonster(MON_TYPE::DRAGON, Vec2(500.f, 550.f), m_eType);
	pDragon4_1->SetName(L"CDragon_4_1");
	//�� ���� �������̽��� �� ���� �̸� �ֱ�
	CMonInterface* pDragonInter4_1 = new CMonInterface(pDragon4_1->GetName(),15);
	pDragonInter4_1->SetScale(Vec2(626, 29));
	pDragonInter4_1->SetPos(Vec2(40, 20));
	AddObject(pDragonInter4_1, GROUP_TYPE::UI);
	AddObject(pDragon4_1, GROUP_TYPE::MONSTER);

	CMonster* pDragon4_2 = CMonFactory::CraeteMonster(MON_TYPE::DRAGON, Vec2(800.f, 440.f), m_eType);
	pDragon4_2->SetName(L"CDragon_4_2");
	//�� ���� �������̽��� �� ���� �̸� �ֱ�
	CMonInterface* pDragonInter4_2 = new CMonInterface(pDragon4_2->GetName(),15);
	pDragonInter4_2->SetScale(Vec2(626, 29));
	pDragonInter4_2->SetPos(Vec2(40, 20));
	AddObject(pDragonInter4_2, GROUP_TYPE::UI);
	AddObject(pDragon4_2, GROUP_TYPE::MONSTER);

	//���� ���� ���
	CGate* pGate = new CGate(L"up", false);
	pGate->SetPos(Vec2(500.f, 365.f));
	pGate->GetCollider()->SetScale(Vec2(70.f, 70.f));
	pGate->SetNextScene(SCENE_TYPE::DUNGEON_5);
	AddObject(pGate, GROUP_TYPE::GATE);
}

void SceneTower_4::InitMonster()
{
	GetPlayerObj()->SetPos(Vec2(300.f, 450.f));
	
	CMonster* pBrDragon4_1 = CMonFactory::CraeteMonster(MON_TYPE::BROWN_DRAGON, Vec2(500.f, 500.f), m_eType);
	pBrDragon4_1->SetName(L"brDragon_4_1");
	CMonInterface* pBrDragonInter4_1 = new CMonInterface(pBrDragon4_1->GetName(), 44);
	pBrDragonInter4_1->SetScale(Vec2(626, 29));
	pBrDragonInter4_1->SetPos(Vec2(40, 20));
	AddObject(pBrDragonInter4_1, GROUP_TYPE::UI);
	AddObject(pBrDragon4_1, GROUP_TYPE::MONSTER);
	
	CMonster* pDragon4_1 = CMonFactory::CraeteMonster(MON_TYPE::DRAGON, Vec2(500.f, 550.f), m_eType);
	pDragon4_1->SetName(L"CDragon_4_1");
	//�� ���� �������̽��� �� ���� �̸� �ֱ�
	CMonInterface* pDragonInter4_1 = new CMonInterface(pDragon4_1->GetName(), 15);
	pDragonInter4_1->SetScale(Vec2(626, 29));
	pDragonInter4_1->SetPos(Vec2(40, 20));
	AddObject(pDragonInter4_1, GROUP_TYPE::UI);
	AddObject(pDragon4_1, GROUP_TYPE::MONSTER);
	
	CMonster* pDragon4_2 = CMonFactory::CraeteMonster(MON_TYPE::DRAGON, Vec2(800.f, 440.f), m_eType);
	pDragon4_2->SetName(L"CDragon_4_2");
	//�� ���� �������̽��� �� ���� �̸� �ֱ�
	CMonInterface* pDragonInter4_2 = new CMonInterface(pDragon4_2->GetName(), 15);
	pDragonInter4_2->SetScale(Vec2(626, 29));
	pDragonInter4_2->SetPos(Vec2(40, 20));
	AddObject(pDragonInter4_2, GROUP_TYPE::UI);
	AddObject(pDragon4_2, GROUP_TYPE::MONSTER);
}

void SceneTower_4::render(HDC _dc)
{
	backgroundrender(_dc, GetBackGround(), Vec2(0.f, 0.f));

	CScene::render(_dc);
}

void SceneTower_4::update()
{
	CScene::update();
}

void SceneTower_4::Enter()
{
	m_pBackSound->Play(true);

	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj()); //vResolution / 2.f
	CCameraMgr::GetInst()->init();
	//���� ���� ��ų �ʱ�ȭ
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());


	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::STONE_BOX);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GATE);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::WALL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::BULLET, GROUP_TYPE::STONE_BOX);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::SKILL, GROUP_TYPE::STONE_BOX);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::STONE_PILLAR);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::SPINNER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::CRYSTAL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::BULLET, GROUP_TYPE::CRYSTAL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::SKILL, GROUP_TYPE::CRYSTAL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER_SKILL);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::BULLET, GROUP_TYPE::MONSTER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::SKILL, GROUP_TYPE::MONSTER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::ROBOT);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::DROUP);
	//CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::MONSTER);
}

void SceneTower_4::Exit()
{
	m_pBackSound->Stop(true);

	CColliderMgr::GetInst()->Reset();
}


