#pragma once
class CRes
{
private:
	wstring m_strKey;//키 값
	wstring m_strRelativePath; //상대경로

public:
	void SetKey(const wstring& _str) { m_strKey = _str; }
	const wstring& GetKey() {return m_strKey;}
	
	//set이 왜 필요하지
	void SetRelativePath(const wstring& _str) { m_strRelativePath = _str; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	CRes();
	virtual ~CRes();
};

