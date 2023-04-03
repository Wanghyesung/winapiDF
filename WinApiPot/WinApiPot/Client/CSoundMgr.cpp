#include "pch.h"
#include "CSoundMgr.h"

#include "CCore.h"

LPDIRECTSOUND8 CSoundMgr::mSoundDevice;

CSoundMgr::CSoundMgr()
{

}

CSoundMgr::~CSoundMgr()
{

}

bool CSoundMgr::Initialize()
{
	if (FAILED(DirectSoundCreate8(NULL, &mSoundDevice, NULL)))
	{
		MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// ���� ����̽� �������� ����.
	HWND hWnd = CCore::GetInst()->GetMainHwnd();
	if (FAILED(mSoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
	{
		MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}