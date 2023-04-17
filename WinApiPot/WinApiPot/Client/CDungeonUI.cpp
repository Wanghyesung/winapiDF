#include "pch.h"
#include "CDungeonUI.h"

#include "CSeleteGDI.h"
#include "CCameraMgr.h"

CDungeonUI::CDungeonUI():
	m_eNextScene(SCENE_TYPE::END)
{

}

CDungeonUI::~CDungeonUI()
{
}

void CDungeonUI::MouseOn()
{
}

void CDungeonUI::MouseLbtnDown()
{
	
}

void CDungeonUI::MouseLbtnUp()
{
}

void CDungeonUI::MouseLbtnClicked()
{
	ChangeScene(m_eNextScene);
}

void CDungeonUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	CSeleteGDI brush = CSeleteGDI(_dc,BRUSH_TYPE::HOLLOW);
	CSeleteGDI pen = CSeleteGDI(_dc, PEN_TYPE::GREEN);

	Rectangle(_dc,
		vPos.x,
		vPos.y,
		vPos.x + vScale.x,
		vPos.y + vScale.y);

	CUI::render(_dc);
}
