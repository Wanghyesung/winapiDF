#include "pch.h"
#include "CGate.h"

#include "CCollider.h"
#include "CObject.h"

#include "CGravity.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCameraMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

CGate::CGate(const wstring& _strDir) :
	m_strDir(_strDir),
	CTex(nullptr),
	CTexDoor(nullptr),
	m_eNextScene(SCENE_TYPE::END),
	m_bActive(true)
{
	SetTag(GROUP_TYPE::GATE);

	CreateCollider();

	wstring strPath = L"..\\OutPut\\bin_release\\Content\\Object\\";
	wstring strName = L"gate_" + _strDir;
	wstring strResult = strPath + strName + L".bmp";
	wstring strDoorResult = strPath + strName + L"_door.bmp";

	//gate + ¹æÇâ ¹®
	CTex = CResMgr::GetInst()->LoadTextur(strResult, strResult);
	CTexDoor = CResMgr::GetInst()->LoadTextur(strDoorResult,strDoorResult);
}

CGate::~CGate()
{

}

void CGate::update()
{
	
	//if (!m_bActive)
	//	return;
	//
	//const vector<CObject*>& MonVec = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::MONSTER);
	//if (MonVec.size() == 0)
	//	m_bActive = false;
}

void CGate::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc,
		(int)(vPos.x - CTex->Width() / 2.f),
		(int)(vPos.y - CTex->Height() / 2.f),
		(int)(CTex->Width()),
		(int)(CTex->Height()),
		CTex->GetDC(),
		(int)0,
		(int)0,
		(int)(CTex->Width()),
		(int)(CTex->Height()),
		RGB(0, 0, 0));

	if (m_bActive)
	{
		TransparentBlt(_dc,
			(int)(vPos.x - CTexDoor->Width() / 2.f),
			(int)(vPos.y - CTexDoor->Height() / 2.f),
			(int)(CTexDoor->Width()),
			(int)(CTexDoor->Height()),
			CTexDoor->GetDC(),
			(int)0,
			(int)0,
			(int)(CTexDoor->Width()),
			(int)(CTexDoor->Height()),
			RGB(0, 0, 0));
	}
	component_render(_dc);
}

void CGate::OnColliderEnter(CCollider* _pOther)
{
	CObject* pObj = _pOther->GetObj();
	if (pObj->GetTag() == GROUP_TYPE::PLAYER && !m_bActive)
	{
		if (pObj->GetGravity()->IsGetGravity())
			return;

		ChangeScene(m_eNextScene);
	}
}

void CGate::OnColliderExit(CCollider* _pOther)
{

}

void CGate::OnCollision(CCollider* _pOther)
{

}
