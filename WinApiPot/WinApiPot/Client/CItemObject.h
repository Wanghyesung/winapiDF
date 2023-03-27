#pragma once
#include "CObject.h"

class CMonster;
class CItem;

class CItemObject :
    public CObject
{
public:
	CItemObject();
	virtual ~CItemObject();

private:
	CTexture* m_pItemTex;
	ITEM_TYPE m_eItemType;

	CItem* m_pItem;

	bool m_bOnMap;

private:
	void setItemObj(ITEM_TYPE _eItemType);

public:
	virtual void render(HDC _dc);
	virtual void update();//»ó¼Ó
	virtual void finalupdate();

public:
	virtual void OnColliderEnter(CCollider* _pOther);
	virtual void OnColliderExit(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	
	friend class CItemMgr;

};

