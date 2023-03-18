#pragma once

class CInterFace;
class CMonInterface;

class CInterfaceMgr
{
	SINGLE(CInterfaceMgr);

	//플레이어는 인터페이스 1개
	//몬스터 인터페이스는 hash테이블로 여러개 보유
public:
	void ChangeInterFaceValue(float _fHPValue, float _fMPValue);
	void ChangeMonInterFaceValue(const wstring& _strName, float _fHpValue);

public:
	void SetInterFace(CInterFace* _pInterFace) { m_pPlayerInterFace = _pInterFace; }
	void TargetRender(HDC _dc);

	void AddMonInterface(const wstring& _strName, CMonInterface* _pMonInterface) { m_hashMonInterface.insert(make_pair(_strName, _pMonInterface)); }
	void SetTargetMon(const wstring& _strName);//현재 타겟 몬스터
	CMonInterface* FindTargetMon(const wstring& _strName);//해당 몬스터 인터페이스를 가져온다

private:
	CInterFace* m_pPlayerInterFace;
	CMonInterface* m_pTargetMon;

	//map<wstring, CMonInterface*>m_mapMonInterface;
	unordered_map<wstring, CMonInterface*> m_hashMonInterface;

	void deleteInterface(const wstring& _strName);

	friend class CMonInterface;
};

