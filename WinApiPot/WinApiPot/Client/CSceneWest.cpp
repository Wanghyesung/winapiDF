#include "pch.h"
#include "CSceneWest.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CSkillMgr.h"
#include "CColliderMgr.h"
#include "CCameraMgr.h"

CSceneWest::CSceneWest():
	m_eType(SCENE_TYPE::WEST_COAST)
{
}

CSceneWest::~CSceneWest()
{
}

void CSceneWest::render(HDC _dc)
{
	Vec2 StartPos = Vec2(0.f, 0.f);//�׸��� ó���� �׸� ��ġ
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

	//������� ��� �����
	tBackGround tInfo = {};
	tInfo.fRightWidth = m_pBackGround->Width();
	tInfo.fBottomHeight = m_pBackGround->Height();
	tInfo.fLeftWidth = GetStartDrawPoint().x;
	tInfo.fTopHeight = GetStartDrawPoint().y;
	SetBackGroundInfo(tInfo);
	//�÷��̾� �������̽��� �� �ٲܶ� ����X
	SetInterFace();

	CObject* pObj = CreatePlayer(Vec2(500.f, 650.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	RegisterPlayer(pObj);
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());
	CSkillMgr::GetInst()->init(m_eType);
}

void CSceneWest::Enter()
{
	CCameraMgr::GetInst()->SetTargetObj((CPlayer*)GetPlayerObj()); //vResolution / 2.f
	CCameraMgr::GetInst()->init();
	//���� ���� ��ų �ʱ�ȭ
	CSkillMgr::GetInst()->SetPlayer((CPlayer*)GetPlayerObj());


	CColliderMgr::GetInst()->ChekGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
}

void CSceneWest::Exit()
{
	CColliderMgr::GetInst()->Reset();
}

