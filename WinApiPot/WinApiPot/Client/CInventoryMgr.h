#pragma once

class CInventoryMgr
{
	SINGLE(CInventoryMgr);

	//Ű �Է½� �κ��丮â Ű��

public:
	void update();
	void render(HDC _dc);
	void init();//�κ��丮 ����


private:

	friend class CInventory;
};

