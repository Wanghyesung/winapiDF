#include "pch.h"
#include "CInterfaceMgr.h"

#include "CInterFace.h"

CInterfaceMgr::CInterfaceMgr():
	m_pPlayerInterFace(nullptr)
{

}

CInterfaceMgr::~CInterfaceMgr()
{

}

void CInterfaceMgr::ChangeInterFaceValue(float _fHPValue, float _fMPValue)
{
	if (m_pPlayerInterFace == nullptr)
		return;

	m_pPlayerInterFace->ChangeValue(_fHPValue, _fMPValue);
}
