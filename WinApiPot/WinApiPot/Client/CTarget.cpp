#include "pch.h"
#include "CTarget.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CRigidBody.h"
#include "CCameraMgr.h"

CTarget::CTarget():
	m_pTargetTex(nullptr)
{
	SetTag(GROUP_TYPE::SKILL);

	m_pTargetTex = CResMgr::GetInst()->LoadTextur(L"target", L"..\\OutPut\\bin_release\\Content\\emfact\\target.bmp");

	CreateRigidBody();
}

CTarget::~CTarget()
{
	int a = 10;
}

void CTarget::move(Vec2 _vForce)
{
	GetRigidBody()->AddForce(_vForce);
}

void CTarget::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		(int)(m_pTargetTex->Width()),
		(int)(m_pTargetTex->Height()),
		m_pTargetTex->GetDC(),
		(int)0,
		(int)0,
		(int)(m_pTargetTex->Width()),
		(int)(m_pTargetTex->Height()),
		RGB(0, 0, 0));
}

void CTarget::update()
{

}

void CTarget::finalupdate()
{
	CObject::finalupdate();
}
