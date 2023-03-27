#include <random>

#include "pch.h"
#include "CItemMgr.h"

#include "CInventoryMgr.h"
#include "CInventory.h"
#include "CItemObject.h"

CItemMgr::CItemMgr()
{

}

CItemMgr::~CItemMgr()
{

}

//해당 타입의 아이템을 인벤토리에 넣기
void CItemMgr::GetItemObejct(CItem* _pItem)
{
	CInventory* pInven = CInventoryMgr::GetInst()->GetInventory();
	
	pInven->AddItem(_pItem);
}


//씬에 아이템 오브젝트 생성
//몬스터마다 생성되는 아이템을 다르게
//pos는 몬스터 죽은 위치
void CItemMgr::CreateItem(Vec2 _vSpawnPos)
{
	std::random_device rDiv;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 en(rDiv());

	std::uniform_int_distribution<int> dis(0, 1);
	UINT iNum = dis(en);
	
	CItemObject* pItemObj = new CItemObject;
	//해당 아이템 오브젝트에 아이템타입 알려주기
	pItemObj->setItemObj((ITEM_TYPE)iNum);

	//아이템 생성 위치
	std::mt19937 enPos(rDiv());
	std::uniform_int_distribution<int> disPos(0, 360);
	float fDegree = (float)disPos(enPos);
	Vec2 vNor = Rotate(_vSpawnPos, fDegree);

	pItemObj->SetPos(_vSpawnPos + vNor*100.f);

	CreateObject(pItemObj, GROUP_TYPE::ITEM);
}
