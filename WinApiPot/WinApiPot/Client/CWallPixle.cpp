#include "pch.h"
#include "CWallPixle.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CGravity.h"
#include "CCollider.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CCameraMgr.h"

CWallPixle::CWallPixle():
	m_pPixleTex(nullptr)
{
	SetTag(GROUP_TYPE::TILE);

	m_pPixleTex = CResMgr::GetInst()->LoadTextur(L"westPixle", L"..\\OutPut\\bin_release\\Content\\background\\WestCoastPixel.bmp");
}

CWallPixle::~CWallPixle()
{

}



void CWallPixle::update()
{
	CObject* pPlayer = SceneMgr::GetInst()->GetCurSCene()->GetPlayerObj();

	Vec2 vPlayerFinalPos = pPlayer->GetCollider()->GetFinalPos();
	Vec2 vPlayerPos = pPlayer->GetPos();

	COLORREF color = m_pPixleTex->GetPixel(vPlayerFinalPos.x, vPlayerFinalPos.y);

	 //pPlayer->GetRigidBody();

	if (color == RGB(255, 0, 255))
	{
		vPlayerPos.y += 1.f;
		pPlayer->SetPos(vPlayerPos);
	}

}

void CWallPixle::render(HDC _dc)
{
	Vec2 StartRenderPos = CCameraMgr::GetInst()->GetRenderPos(Vec2(0.f,0.f)); //배경 이미지를 그릴 좌상단 시작점

	BitBlt(_dc,
		(int)(StartRenderPos.x),
		(int)(StartRenderPos.y),
		(int)(m_pPixleTex->Width()),
		(int)(m_pPixleTex->Height()),
		m_pPixleTex->GetDC(),
		0, 0,
		SRCCOPY);
}

void CWallPixle::finalupdate()
{
	CObject::finalupdate();

}

void CWallPixle::OnColliderEnter(CCollider* _pOther)
{

}

void CWallPixle::OnColliderExit(CCollider* _pOther)
{

}

void CWallPixle::OnCollision(CCollider* _pOther)
{

}
