#include "pch.h"
#include "CCoinMgr.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CCore.h"
#include "CTexture.h"


CCoinMgr::CCoinMgr():
	m_bIsDead(false),
	m_vecCoinCountTex{},
	m_vecCountTex{},
	m_fResTime(9.99f),
	m_iCoinCount(2)
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
}

void CCoinMgr::Resurrection()
{
	if (m_iCoinCount == 0)
		return;

	m_iCoinCount -= 1;

	//CreatePlayer()
	m_bIsDead = false;

}
