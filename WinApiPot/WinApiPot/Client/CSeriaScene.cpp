#include "pch.h"
#include "CSeriaScene.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CPathMgr.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CCameraMgr.h"
#include "CSkillMgr.h"
#include "CColliderMgr.h"

#include "CPortal.h"
#include "CTemWall.h"

#include "CMPItem.h"
#include "CHPItem.h"
#include "CInventory.h"
#include "CInventoryMgr.h"

#include "CCollider.h"

#include "CSound.h"

CSeriaScene::CSeriaScene():
	m_eType(SCENE_TYPE::SERIA_SCENE)
{

}

CSeriaScene::~CSeriaScene()
{

}

void CSeriaScene::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//�׸��� ó���� �׸� ��ġ
	SetStartDrawPoint(StartPos);

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

	CScene::render(_dc);

}
void CSeriaScene::Init()
{
	CTexture* pBackGround = CResMgr::GetInst()->LoadTextur(L"Seria", L"..\\OutPut\\bin_release\\Content\\background//seria2.bmp");

	SetBackGround(pBackGround);

	tBackGround tInfo = {};
	tInfo.fRightWidth = pBackGround->Width();
	tInfo.fBottomHeight = pBackGround->Height()-90;
	tInfo.fLeftWidth = GetStartDrawPoint().x;
	tInfo.fTopHeight = GetStartDrawPoint().y;

	SetBackGroundInfo(tInfo);

	//����
	//CSound* pSeriaSound
	//	= CResMgr::GetInst()->LoadSound(L"MainTheme", L"..\\Resources\\Sound\\BGTheme.wav");
	//pSeriaSound->Play(true);

	CObject* pObj = CreatePlayer(Vec2(450.f, 650.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	CreateInterFace();

	CInventory* pInven = new CInventory;
	CHPItem* pItemHP = new CHPItem;
	pInven->AddItem(pItemHP);
	CMPItem* pItemMP = new CMPItem;
	pInven->AddItem(pItemMP);

	AddObject(pInven, GROUP_TYPE::UI);

	RegisterPlayer(pObj);

	CPortal* pPortal_1 = new CPortal;
	pPortal_1->SetName(L"Start_Portal");
	pPortal_1->SetPos(Vec2(800.f, 850.f));
	pPortal_1->GetCollider()->SetScale(Vec2(140.f, 50.f));
	pPortal_1->SetNextScene(SCENE_TYPE::START_SCENE);
	//��Ż ũ��� �������� �����ڿ��� ����
	AddObject(pPortal_1, GROUP_TYPE::PORTAL);

	CTemWall* pTemWall = new CTemWall;
	pTemWall->SetPos(Vec2(800.f, 250.f));
	pTemWall->GetCollider()->SetScale(Vec2(1600.f, 600.f));
	AddObject(pTemWall, GROUP_TYPE::WALL);

}

void CSeriaScene::Enter()
{
	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj()); //vResolution / 2.f
	CCameraMgr::GetInst()->init();
	//���� ���� ��ų �ʱ�ȭ
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());

	CInventoryMgr::GetInst()->init();

	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PORTAL, GROUP_TYPE::PLAYER);
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::WALL, GROUP_TYPE::PLAYER);
}

void CSeriaScene::Exit()
{
	DeleteGroup(GROUP_TYPE::SKILL);

	CColliderMgr::GetInst()->Reset();
}


