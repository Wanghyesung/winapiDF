#pragma once

class CInterFace;
class CMonInterface;

class CInterfaceMgr
{
	SINGLE(CInterfaceMgr);

	//�÷��̾�� �������̽� 1��
	//���� �������̽��� hash���̺�� ������ ����
public:
	void ChangeInterFaceValue(float _fHPValue, float _fMPValue);
	void ChangeMonInterFaceValue(const wstring& _strName, float _fHpValue);

public:
	void SetInterFace(CInterFace* _pInterFace) { m_pPlayerInterFace = _pInterFace; }
	void TargetRender(HDC _dc);

	void AddMonInterface(const wstring& _strName, CMonInterface* _pMonInterface) { m_hashMonInterface.insert(make_pair(_strName, _pMonInterface)); }
	void SetTargetMon(const wstring& _strName);//���� Ÿ�� ����
	CMonInterface* FindTargetMon(const wstring& _strName);//�ش� ���� �������̽��� �����´�

private:
	CInterFace* m_pPlayerInterFace;
	CMonInterface* m_pTargetMon;

	//map<wstring, CMonInterface*>m_mapMonInterface;
	unordered_map<wstring, CMonInterface*> m_hashMonInterface;

	void deleteInterface(const wstring& _strName);

	friend class CMonInterface;
};

