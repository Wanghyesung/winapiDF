#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
}

CTexture* CResMgr::LoadTextur(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}

	//경로값 가져오기
	//wstring strFilePath = CPathMgr::GetInst()->GetContenPath();
	//strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(_strRelativePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);
	
	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::CreatTexture(const wstring& _strKey, UINT _Width, UINT _Height)
{

	CTexture* m_pTex = FindTexture(_strKey);
	if (m_pTex != nullptr)
	{
		return m_pTex;
	}
	
	m_pTex = new CTexture;//없으면 새로운 텍스쳐
	m_pTex->Create(_Width, _Height);//텍스쳐 만들기
	m_pTex->SetKey(_strKey);


	m_mapTex.insert(make_pair(_strKey, m_pTex));

	return m_pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return nullptr;
	

	return (CTexture*)iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	CSound* pSound = FindSound(_strKey);

	if (pSound != nullptr)
	{
		return pSound;
	}

	// 해당 리소스가 없다면
	pSound = new CSound;
	if (FAILED(pSound->Load(_strRelativePath)))
	{
		assert(false);
		return nullptr;
	}

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);
	m_mapTex.insert(make_pair(_strKey, pSound));

	return pSound;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return nullptr;

	return (CSound*)iter->second;
}
