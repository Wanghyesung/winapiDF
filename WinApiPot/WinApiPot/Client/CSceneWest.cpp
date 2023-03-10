#include "pch.h"
#include "CSceneWest.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CSkillMgr.h"
#include "CColliderMgr.h"
#include "CCameraMgr.h"
#include "CPortal.h"
#include "CCollider.h"

CSceneWest::CSceneWest():
	m_eType(SCENE_TYPE::WEST_COAST)
{
}

CSceneWest::~CSceneWest()
{
}

void CSceneWest::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//그림을 처음에 그릴 위치
	SetStartDrawPoint(StartPos);

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

	CScene::render(_dc);
}

void CSceneWest::update()
{
	CScene::update();
}
void CSceneWest::Init()
{
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"west", L"..\\OutPut\\bin_release\\Content\\background\\WestCoast.bmp");
	SetBackGround(m_pBackGround);

	//배경정보 담고 만들기
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height();
	tInfo.fLeftWidth = GetStartDrawPoint().x;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);
	//플레이어 인터페이스는 씬 바꿀때 삭제X
	SetInterFace();

	CObject* pObj = CreatePlayer(Vec2(500.f, 650.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);


	CPortal* pPortal_1 = new CPortal;
	pPortal_1->SetName(L"Port_Portal");
	pPortal_1->SetPos(Vec2(2450.f, 650.f));
	pPortal_1->GetCollider()->SetScale(Vec2(50.f, 200.f));
	pPortal_1->SetNextScene(SCENE_TYPE::FIRST_DUNGEON);
	//포탈 크기는 고정으로 생성자에서 만듬
	AddObject(pPortal_1, GROUP_TYPE::PORTAL);

}

void CSceneWest::Enter()
{
	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj()); //vResolution / 2.f
	CCameraMgr::GetInst()->init();
	//현재 씬에 스킬 초기화
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());


	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
}

void CSceneWest::Exit()
{
	CColliderMgr::GetInst()->Reset();
}

