#pragma once

class CRes;
class CTexture;

class CResMgr
{
	SINGLE(CResMgr)

private:
	map<wstring, CRes*>m_mapTex;//내 텍스쳐 저장 공간


public:
	CTexture* LoadTextur(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* CreatTexture(const wstring& _strKey, UINT _Width, UINT _Height);
	CTexture* FindTexture(const wstring& _strKey);





};

