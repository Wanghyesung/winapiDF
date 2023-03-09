#include "pch.h"
#include "CInterfaceMgr.h"

#include "CInterFace.h"
#include "CMonInterface.h"

CInterfaceMgr::CInterfaceMgr():
	m_pPlayerInterFace(nullptr),
	m_pTargetMon(nullptr)
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

void CInterfaceMgr::ChangeMonInterFaceValue(const wstring& _strName, float _fHpValue)
{
	CMonInterface* pTarger = FindTargetMon(_strName);
	if (pTarger == nullptr)
		return;

	pTarger->changeValue(_fHpValue);
}

CMonInterface* CInterfaceMgr::FindTargetMon(const wstring& _strName)
{
	unordered_map<wstring, CMonInterface*>::iterator iter = m_hashMonInterface.find(_strName);

	if (iter != m_hashMonInterface.end())
	{
		return iter->second;
	}

	return nullptr;
}



void CInterfaceMgr::TargetRender(HDC _dc)
{
	if (m_pTargetMon != nullptr)
	{
		m_pTargetMon->renderHp(_dc);
	}
}

void CInterfaceMgr::SetTargetMon(const wstring& _strName)
{
	CMonInterface* pTarget = FindTargetMon(_strName);

	if (pTarget != nullptr)
	{
		m_pTargetMon = pTarget;
	}
}
