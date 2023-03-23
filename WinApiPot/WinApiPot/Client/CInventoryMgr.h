#pragma once

class CInventory;

class CInventoryMgr
{
	SINGLE(CInventoryMgr);

	//Ű �Է½� �κ��丮â Ű��

public:
	void update();
	void render(HDC _dc);
	void init();//�κ��丮 ����

	CInventory* Exit();//���� �� �� ���� ���� �������̽� ����� ���� ���� ���� �������̽� ��ȯ
	void Enter(CInventory* _pInven);

	CInventory* GetInventory() { return m_pTargetInven; }

private:
	CInventory* m_pTargetInven;//���� ���� �κ��丮

	friend class CInventory;
};

