#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr() :
	m_szContenPath{},
	m_szRelativePath{}
{
}

CPathMgr::~CPathMgr()
{

}


void CPathMgr::init()
{
	//디렉토리 경로 가져오기 근데 bin폴더에 Res들을 넣을 것이기 떄문에 한단계 내려가야함
	GetCurrentDirectory(256, m_szContenPath);

	int iLen = (int)wcslen(m_szContenPath);

	for (int i = iLen - 1; i >= 0; --i)
	{
		if (m_szContenPath[i] == '\\')
		{
			m_szContenPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContenPath, 256, L"\\bin_release\\Content\\");//Content있는 곳으로 이동
}

wstring CPathMgr::GetRelativePath(const wchar_t* _str)
{
	wstring filePath = _str;

	size_t iAbslen = wcslen(m_szContenPath); //절대 경로 길이
	size_t iFullLen = filePath.length(); //전체 경로 길이 


	wstring strRelativePath = filePath.substr(iAbslen, iFullLen - iAbslen); //절대 경로가 끝나는 시점부터 상대경로의 길이값만큼 받겠다
	//전체 길이에서 절대경로를 뺀 값 

	return strRelativePath;
}
