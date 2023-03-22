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

	CInventory* Exit();//나갈 때 내 현재 씬에 인터페이스 지우고 다음 씬을 위한 인터페이스 반환
	void Enter(CInventory* _pInven);

private:
	CInventory* m_pTargetInven;//현재 씬의 인벤토리

	friend class CInventory;
};

