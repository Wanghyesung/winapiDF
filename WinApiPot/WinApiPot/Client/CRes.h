#pragma once
class CRes
{
private:
	wstring m_strKey;//Ű ��
	wstring m_strRelativePath; //�����

public:
	void SetKey(const wstring& _str) { m_strKey = _str; }
	const wstring& GetKey() {return m_strKey;}
	
	//set�� �� �ʿ�����
	void SetRelativePath(const wstring& _str) { m_strRelativePath = _str; }
	const wstring& GetRelativePath() { return m_strRelativePath; }

public:
	CRes();
	virtual ~CRes();
};

