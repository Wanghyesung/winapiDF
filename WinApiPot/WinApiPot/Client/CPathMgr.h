#pragma once

class CPathMgr
{
	SINGLE(CPathMgr)

private:
	wchar_t m_szContenPath[256];//������
	wchar_t m_szRelativePath[256];//�����

public:
	void init();

	wchar_t* GetContenPath() { return m_szContenPath; }
	wstring GetRelativePath(const wchar_t* _str);



};

