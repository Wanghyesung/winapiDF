#include "pch.h"
#include "CCoinMgr.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"
#include "CPlayer.h"

#include "CCore.h"
#include "CTexture.h"

#include "CCameraMgr.h"
#include "CSkillMgr.h"

#include "CDungeonMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CInterfaceMgr.h"

CCoinMgr::CCoinMgr():
	m_bIsDead(false),
	m_vecCoinCountTex{},
	m_vecCountTex{},
	m_fResTime(9.99f),
	m_iCoinCount(5)
{
	m_vecCoinCountTex.resize(10);
	m_vecCountTex.resize(10);
}

CCoinMgr::~CCoinMgr()
{

}

void CCoinMgr::init()
{
	for (int i = 0; i < 10; ++i)
	{
		wstring strNum = std::to_wstring(i);
		m_vecCoinCountTex[i] = CResMgr::GetInst()->LoadTextur(L"coin" + strNum, L"..\\OutPut\\bin_release\\Content\\coin\\coin" + strNum + L".bmp");
		m_vecCountTex[i] = CResMgr::GetInst()->LoadTextur(L"cnt" + strNum, L"..\\OutPut\\bin_release\\Content\\coin\\cnt" + strNum + L".bmp");
	}

	m_pCoinTex = CResMgr::GetInst()->LoadTextur(L"coinTex" , L"..\\OutPut\\bin_release\\Content\\coin\\coin.bmp");

}

void CCoinMgr::render(HDC _dc)
{
	if (!m_bIsDead)
	{
		return;
	}

	Vec2 vMidPos = CCore::GetInst()->GetResolution()/2.f;

	TransparentBlt(_dc,
		(int)vMidPos.x - 145.f, (int)vMidPos.y,
		300, 120,
		m_pCoinTex->GetDC(),
		0, 0,
		m_pCoinTex->Width(), m_pCoinTex->Height(),
		RGB(255, 255, 255));

	//코인 개수
	TransparentBlt(_dc,
		(int)vMidPos.x + 30, (int)vMidPos.y + 57,
		25,30,
		m_vecCoinCountTex[m_iCoinCount]->GetDC(),
		0, 0,
		m_vecCoinCountTex[m_iCoinCount]->Width(), m_vecCoinCountTex[m_iCoinCount]->Height(),
		RGB(0, 0, 0));


	int iCount = (int)m_fResTime;
	if (iCount < 0.f)
		return;

	TransparentBlt(_dc,
		(int)vMidPos.x - 70.f, (int)vMidPos.y - 200.f,
		150, 150,
		m_vecCountTex[iCount]->GetDC(),
		0, 0,
		m_vecCountTex[iCount]->Width(), m_vecCountTex[iCount]->Height(),
		RGB(0, 0, 0));

}

void CCoinMgr::update()
{
	if (!m_bIsDead)
	{
		return;
	}

	m_fResTime -= fDT;

	if (KEY_TAP(KEY::X))
	{
		Resurrection();
	}

	if (m_fResTime < 0.f)
	{
		m_bIsDead = false;
		m_fResTime = 9.99f;
		CDungeonMgr::GetInst()->SetDunType(DUNGEON_TYPE::NONE);
		CObject* pPlayer = SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();
		((CPlayer*)pPlayer)->m_bActive = true;
		((CPlayer*)pPlayer)->resetvalue();
		CInterfaceMgr::GetInst()->SetTargetMon(L"NULL");
		ChangeScene(SCENE_TYPE::WEST_COAST);
	}
}

void CCoinMgr::StartUpdate(Vec2 _vDeadPos)
{
	m_bIsDead = true; 
	m_vResPos = _vDeadPos; 
	CObject* pPlayer = SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();
	((CPlayer*)pPlayer)->m_bActive = false;
}

void CCoinMgr::Resurrection()
{
	if (m_iCoinCount == 0)
		return;

	m_iCoinCount -= 1;

	//죽은지점에서 피 100으로 부활
	CObject* pPlayer = SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();
	((CPlayer*)pPlayer)->m_bActive = true;
	((CPlayer*)pPlayer)->m_bOnResur = true;
	((CPlayer*)pPlayer)->resetvalue();

	pPlayer->SetPos(m_vResPos);
	
	m_fResTime = 9.99f;
	m_bIsDead = false;

}
