#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"
#include "CTimeMgr.h"

int g_arrKey[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU,//ALT,
	VK_CONTROL,//CTRL,
	VK_LSHIFT,//LSHIFT,
	VK_SPACE,//SPACE,
	VK_RETURN,//ENTER,
	VK_ESCAPE,//ESC,

	VK_LBUTTON,
	VK_RBUTTON,
};



CKeyMgr::CKeyMgr()
{

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
}

void CKeyMgr::update()
{

	HWND hwd = GetFocus();

	if (hwd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)//모든 키들 값
		{
			if (GetAsyncKeyState(g_arrKey[i]) & 0x8000)
			{

				if (m_vecKey[i].bPrevPush)//이전 프레임에서 눌렸었다면
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}

				else//현재 프레임에서 눌렸다면
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}

			else//이번 프레임에서 눌리지 않았다면
			{
				if (m_vecKey[i].bPrevPush)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}

				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}
		}

		POINT ptPos = {};
		GetCursorPos(&ptPos);//현재 스크린상 마우스 좌표

		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);//스크린에서 내 프로세스 좌표로 줌

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}

	else//포커싱이 안 되어있음
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
