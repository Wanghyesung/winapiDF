#include "pch.h"
#include "CSceneBack.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CInterFace.h"
#include "CCameraMgr.h"
#include "CSkillMgr.h"
#include "CColliderMgr.h"
#include "CObject.h"
#include "CPlayer.h"

#include "CPortal.h"

CSceneBack::CSceneBack():
	m_eType(SCENE_TYPE::SCENE_BACKSTREET)
{
}
CSceneBack::~CSceneBack()
{
}
void CSceneBack::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//�׸��� ó���� �׸� ��ġ
	SetStartDrawPoint(StartPos);

	CScene::backgroundrender(_dc, GetBackGround(), StartPos);

	CScene::render(_dc);
}

void CSceneBack::update()
{
	CScene::update();
}



void CSceneBack::Init()
{
	//�ް��
	CTexture* m_pBackGround = CResMgr::GetInst()->LoadTextur(L"BackStreet", L"..\\OutPut\\bin_release\\Content\\background\\backstreet.bmp");
	SetBackGround(m_pBackGround);

	//������� ��� �����
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height() -110;
	tInfo.fLeftWidth = GetStartDrawPoint().x +40;
	tInfo.fTopHeight = GetStartDrawPoint().y ;
	SetBackGroundInfo(tInfo);
	//�÷��̾� �������̽��� �� �ٲܶ� ����X
	//GetInterFace();


	CObject* pObj = CreatePlayer(Vec2(300.f, 650.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);

	CPortal* pPortal_1 = new CPortal;
	pPortal_1->SetName(L"Port_Portal");
	pPortal_1->SetPos(Vec2(300.f, 850.f));
	pPortal_1->SetNextScene(SCENE_TYPE::START_SCENE);
	//��Ż ũ��� �������� �����ڿ��� ����
	AddObject(pPortal_1, GROUP_TYPE::PORTAL);

}

void CSceneBack::Enter()
{
	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj()); //vResolution / 2.f
	CCameraMgr::GetInst()->init();
	//���� ���� ��ų �ʱ�ȭ
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	
	
	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);

}

void CSceneBack::Exit()
{
	//DeleteGroup(GROUP_TYPE::SKILL);

	CColliderMgr::GetInst()->Reset();
}


