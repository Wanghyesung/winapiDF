#include "pch.h"
#include "CMPItem.h"


#include "CResMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"

#include "CInterfaceMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"

CMPItem::CMPItem()
{
	m_pItemTex = CResMgr::GetInst()->LoadTextur(L"MPItem", L"..\\OutPut\\bin_release\\Content\\Item\\MPItem.bmp");

	m_eItemType = ITEM_TYPE::MPITEM;

	//아이템 이미지 크기
	SetScale(Vec2(28.f, 28.f));

	SetItemName(L"MPItem");

	m_iHeight = m_pItemTex->Height();
	m_iWidth = m_pItemTex->Width();
}

CMPItem::~CMPItem()
{
	
}

void CMPItem::render(HDC _dc)
{
	Vec2 vPos = GetPos();

	//offset
	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_iWidth, m_iHeight,
		m_pItemTex->GetDC(),
		//시작지점 좌표부터 가져올 이미지 크기
		0, 0,
		m_pItemTex->Width(), m_pItemTex->Height(),
		RGB(255, 255, 255));


	CItem::render(_dc);
}

void CMPItem::update()
{
	CItem::update();
}

void CMPItem::finalupdate()
{
	CUI::finalupdate();
}

void CMPItem::UseItem()
{
	CPlayer* pPlayer = (CPlayer*)SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();

	if (pPlayer != nullptr)
	{
		if (pPlayer->m_tPlayerInfo.m_fMP > 0.f && pPlayer->m_tPlayerInfo.m_fMP < 100.f)
		{
			pPlayer->m_tPlayerInfo.m_fMP += 30.f;
			if (pPlayer->m_tPlayerInfo.m_fMP >= 100.f)
				pPlayer->m_tPlayerInfo.m_fMP = 100.f;

			--m_iItemCount;
		}
	}


	if (m_iItemCount == 0)
	{
		deleteItem();
	}
}

void CMPItem::MouseOn()
{
	CItem::MouseOn();
}

void CMPItem::MouseLbtnDown()
{
	CItem::MouseLbtnDown();
}

void CMPItem::MouseLbtnUp()
{
	CItem::MouseLbtnUp();
}

void CMPItem::MouseLbtnClicked()
{
}
