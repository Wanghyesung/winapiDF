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
		for (int i = 0; i < (int)KEY::LAST; ++i)//��� Ű�� ��
		{
			if (GetAsyncKeyState(g_arrKey[i]) & 0x8000)
			{

				if (m_vecKey[i].bPrevPush)//���� �����ӿ��� ���Ⱦ��ٸ�
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}

				else//���� �����ӿ��� ���ȴٸ�
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}

			else//�̹� �����ӿ��� ������ �ʾҴٸ�
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
		GetCursorPos(&ptPos);//���� ��ũ���� ���콺 ��ǥ

		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);//��ũ������ �� ���μ��� ��ǥ�� ��

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}

	else//��Ŀ���� �� �Ǿ�����
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
