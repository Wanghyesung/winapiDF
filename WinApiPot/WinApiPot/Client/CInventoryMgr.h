#pragma once

class CInventoryMgr
{
	SINGLE(CInventoryMgr);

	//키 입력시 인벤토리창 키기

public:
	void update();
	void render(HDC _dc);
	void init();//인벤토리 생성


private:

	friend class CInventory;
};

