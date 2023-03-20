#pragma once

class CInventory;

class CInventoryMgr
{
	SINGLE(CInventoryMgr);

	//키 입력시 인벤토리창 키기

public:
	void update();
	void render(HDC _dc);
	void init();//인벤토리 생성


private:
	CInventory* m_pTargetInven;//현재 씬의 인벤토리

	friend class CInventory;
};

