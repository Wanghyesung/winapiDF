#pragma once

class CMonster;

class MonInterFaceMgr
{
	SINGLE(MonInterFaceMgr);

public:
	float FindMonsterHp(const wstring& _strName);

private:
	void SetTargetMonHp(float _fHp);

private:
	map<wstring, float> m_mapMonInterFace;
	CMonster* m_pTargetMon;

};

