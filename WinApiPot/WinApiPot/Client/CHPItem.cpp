#include "pch.h"
#include "CHPItem.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CKeyMgr.h"

#include "CPlayer.h"
#include "CScene.h"
#include "CSceneMgr.h"



CHPItem::CHPItem():
	m_fHealValue(30.f)
{
	m_pItemTex = CResMgr::GetInst()->LoadTextur(L"HPItem", L"..\\OutPut\\bin_release\\Content\\Item\\HPItem.bmp");

	m_eItemType = ITEM_TYPE::HPITEM;

	//������ �̹��� ũ��
	SetScale(Vec2(28.f, 28.f));


	SetItemName(L"HPItem");

	m_iHeight = m_pItemTex->Height();
	m_iWidth = m_pItemTex->Width();

}

CHPItem::~CHPItem()
{
}

void CHPItem::render(HDC _dc)
{
	//if (!m_bActive)
	//	return;

	Vec2 vPos = GetFinalPos();

	//offset
	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_iWidth, m_iHeight,
		m_pItemTex->GetDC(),
		//�������� ��ǥ���� ������ �̹��� ũ��
		0, 0,
		m_pItemTex->Width(), m_pItemTex->Height(),
		RGB(255, 255, 255));


	CItem::render(_dc);

}

void CHPItem::update()
{
	CItem::update();
}

void CHPItem::finalupdate()
{
	CUI::finalupdate();
}

void CHPItem::UseItem()
{
	//���� ���̱�
	CPlayer* pPlayer = (CPlayer*)SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();

	if (pPlayer != nullptr)
	{
		if (pPlayer->m_tPlayerInfo.m_fHP > 0.f && pPlayer->m_tPlayerInfo.m_fHP < 100.f)
		{
			pPlayer->m_tPlayerInfo.m_fHP += 30.f;
			if (pPlayer->m_tPlayerInfo.m_fHP >= 100.f)
				pPlayer->m_tPlayerInfo.m_fHP = 100.f;

			--m_iItemCount;
		}
	}


	if (m_iItemCount == 0)
	{
		deleteItem();
	}
}

void CHPItem::MouseOn()
{
	CItem::MouseOn();
}

void CHPItem::MouseLbtnDown()
{
	CItem::MouseLbtnDown();
}

void CHPItem::MouseLbtnUp()
{
	//���� �� ��ġ�� �°� ����
	CItem::MouseLbtnUp();
}

void CHPItem::MouseLbtnClicked()
{
	
}
