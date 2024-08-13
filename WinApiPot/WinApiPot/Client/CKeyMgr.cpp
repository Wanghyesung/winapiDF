#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"
#include "CTimeMgr.h"

#include "CResMgr.h"

int g_arrKey[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	0x31,//1
	0x32,//2
	0x33,//3
	0x34,//4
	0x35,//5
	0x36,

	'Q','W','E','R','T','Y','U','I','O','P','A','S',
	'D','F','G','Z','X','C','V','B',

	VK_MENU,//ALT,
	VK_CONTROL,//CTRL,
	VK_LSHIFT,//LSHIFT,
	VK_SPACE,//SPACE,
	VK_RETURN,//ENTER,
	VK_ESCAPE,//ESC,

	VK_LBUTTON,
	VK_RBUTTON,
};



CKeyMgr::CKeyMgr():
	m_vecKeyTex{}
{
	//1 2 3 4 5 6 z s d f t w
	m_vecKeyTex.resize(12);
}
CKeyMgr::~CKeyMgr()
{

}



void CKeyMgr::init()
{
	for (UINT i = 0; i < (int)KEY::LAST; ++i)//
	{
		m_vecKey.push_back(KeyInfo{KEY_STATE::NONE , false });
	}


	//키 텍스쳐 관련 초기화
	for (UINT i = 0; i < 6; ++i)
	{
		wstring strNum = std::to_wstring(i + 1);
		m_vecKeyTex[i] = CResMgr::GetInst()->LoadTextur(L"KeyNum" + strNum, L"..\\OutPut\\bin_release\\Content\\Key\\" + strNum + L".bmp");
	}

	//내 인터페이스에 키입력 순서
	wstring strKey[6] = {L"z", L"s" , L"d" , L"f" , L"t", L"w"};
	
	for (UINT i = 0; i < 6; ++i)
	{
		CTexture* pTex = CResMgr::GetInst()->LoadTextur(L"KeyNum" + strKey[i], L"..\\OutPut\\bin_release\\Content\\Key\\" + strKey[i] + L".bmp");
		m_vecKeyTex[6 + i] = pTex;
	}

}

void CKeyMgr::update()
{
	HWND hwd = GetFocus();
	if (hwd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrKey[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
					m_vecKey[i].eState = KEY_STATE::HOLD;
				else
					m_vecKey[i].eState = KEY_STATE::TAP;

				m_vecKey[i].bPrevPush = true;
			}
			else
			{
				if (m_vecKey[i].bPrevPush)
					m_vecKey[i].eState = KEY_STATE::AWAY;
				else
					m_vecKey[i].eState = KEY_STATE::NONE;

				m_vecKey[i].bPrevPush = false;
			}
		}
		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}

	else
	{
		for (UINT i = 0; i < (UINT)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}

			else if(m_vecKey[i].eState == KEY_STATE::AWAY)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}

CTexture* CKeyMgr::GetKeyTex(const wstring& _strKey)
{
	CTexture* pTex = CResMgr::GetInst()->FindTexture(L"KeyNum" + _strKey);

	if (pTex != nullptr)
	{
		return pTex;
	}

	return nullptr;
}
