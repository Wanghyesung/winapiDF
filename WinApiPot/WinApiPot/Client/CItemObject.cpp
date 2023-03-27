#include "pch.h"
#include "CItemObject.h"

#include "CResMgr.h"

#include "CCollider.h"

#include "CTexture.h"
#include "CCameraMgr.h"
#include "CItemMgr.h"

#include "CGravity.h"

#include "CHPItem.h"
#include "CMPItem.h"

CItemObject::CItemObject():
	m_bOnMap(true),
	m_pItemTex(nullptr),
	m_eItemType(ITEM_TYPE::NONE),
	m_pItem(nullptr)
{
	//m_pItemTex = CResMgr::GetInst()->LoadTextur(L"")

	CreateCollider();
	GetCollider()->SetScale(Vec2(30.f, 30.f));
	GetCollider()->SetOffSet(Vec2(15.f, 12.f));
}

CItemObject::~CItemObject()
{
	//캐릭터가 안먹고 맵에 남아있다면
	if (m_pItem != nullptr && m_bOnMap)
		delete m_pItem;
}

void CItemObject::update()
{

}

void CItemObject::setItemObj(ITEM_TYPE _eItemType)
{
	m_eItemType = _eItemType;
	//텍스쳐 넣기
	wstring strName;
	switch (m_eItemType)
	{
	case ITEM_TYPE::HPITEM:
	{
		strName = L"HPItemObj";
		m_pItemTex = CResMgr::GetInst()->LoadTextur(strName, L"..\\OutPut\\bin_release\\Content\\Item\\" + strName + L".bmp");
		m_pItem = new CHPItem;
	}
		break;
	case ITEM_TYPE::MPITEM:
	{
		strName = L"MPItemObj";
		m_pItemTex = CResMgr::GetInst()->LoadTextur(strName, L"..\\OutPut\\bin_release\\Content\\Item\\" + strName + L".bmp");
		m_pItem = new CMPItem;
	}
		break;
	}

}

void CItemObject::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

	if (m_pItemTex == nullptr)
		assert(nullptr);

	TransparentBlt(_dc,
		(int)(vPos.x),
		(int)(vPos.y),
		(int)(m_pItemTex->Width()),
		(int)(m_pItemTex->Height()),
		m_pItemTex->GetDC(),
		(int)0,
		(int)0,
		(int)(m_pItemTex->Width()),
		(int)(m_pItemTex->Height()),
		RGB(255, 255, 255));

	component_render(_dc);
}

void CItemObject::finalupdate()
{
	CObject::finalupdate();
}

void CItemObject::OnColliderEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();

	if (pObj->GetTag() == GROUP_TYPE::PLAYER &&
		!pObj->GetGravity()->IsGetGravity())
	{
		CItemMgr::GetInst()->GetItemObejct(m_pItem);

		m_bOnMap = false;
		DeleteObject(this);
	}
}

void CItemObject::OnColliderExit(CCollider* _pOther)
{

}

void CItemObject::OnCollision(CCollider* _pOther)
{
	
}
