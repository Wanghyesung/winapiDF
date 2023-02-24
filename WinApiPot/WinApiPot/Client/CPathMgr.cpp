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
	//���丮 ��� �������� �ٵ� bin������ Res���� ���� ���̱� ������ �Ѵܰ� ����������
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

	wcscat_s(m_szContenPath, 256, L"\\bin_release\\Content\\");//Content�ִ� ������ �̵�
}

wstring CPathMgr::GetRelativePath(const wchar_t* _str)
{
	wstring filePath = _str;

	size_t iAbslen = wcslen(m_szContenPath); //���� ��� ����
	size_t iFullLen = filePath.length(); //��ü ��� ���� 


	wstring strRelativePath = filePath.substr(iAbslen, iFullLen - iAbslen); //���� ��ΰ� ������ �������� ������� ���̰���ŭ �ްڴ�
	//��ü ���̿��� �����θ� �� �� 

	return strRelativePath;
}
