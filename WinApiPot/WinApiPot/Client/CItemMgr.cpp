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

//�ش� Ÿ���� �������� �κ��丮�� �ֱ�
void CItemMgr::GetItemObejct(CItem* _pItem)
{
	CInventory* pInven = CInventoryMgr::GetInst()->GetInventory();
	
	pInven->AddItem(_pItem);
}


//���� ������ ������Ʈ ����
//���͸��� �����Ǵ� �������� �ٸ���
//pos�� ���� ���� ��ġ
void CItemMgr::CreateItem(Vec2 _vSpawnPos)
{
	std::random_device rDiv;

	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	std::mt19937 en(rDiv());

	std::uniform_int_distribution<int> dis(0, 1);
	UINT iNum = dis(en);
	
	CItemObject* pItemObj = new CItemObject;
	//�ش� ������ ������Ʈ�� ������Ÿ�� �˷��ֱ�
	pItemObj->setItemObj((ITEM_TYPE)iNum);

	//������ ���� ��ġ
	std::mt19937 enPos(rDiv());
	std::uniform_int_distribution<int> disPos(0, 360);
	float fDegree = (float)disPos(enPos);
	Vec2 vNor = Rotate(_vSpawnPos, fDegree);

	pItemObj->SetPos(_vSpawnPos + vNor*100.f);

	CreateObject(pItemObj, GROUP_TYPE::ITEM);
}
