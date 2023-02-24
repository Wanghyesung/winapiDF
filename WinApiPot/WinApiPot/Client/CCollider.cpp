#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"
#include "CSeleteGDI.h"

#include "CCameraMgr.h"

UINT CCollider::g_iNextId = 0;

CCollider::CCollider() :
	m_pOwner(nullptr),
	offsetPos(Vec2(0.f,0.f)),
	m_iID(g_iNextId++),
	m_bActive(true),
	m_iCol(0),
	tOtherCollInfo{},
	m_tCollSize{}
{

}

CCollider::CCollider(const CCollider& _origin):
	m_pOwner(nullptr),
	m_iID(g_iNextId++),
	m_bActive(_origin.m_bActive),
	m_iCol(_origin.m_iCol),
	m_vScale(_origin.m_vScale),
	tOtherCollInfo{}
{

}

CCollider::~CCollider()
{

}

void CCollider::SetColliderInfo()
{
	//처음 포지션 위치로
	m_tCollSize.fBottomHeight = m_pOwner->GetPos().y + m_vScale.y / 2.f;
	m_tCollSize.fTopHeight = m_pOwner->GetPos().y - m_vScale.y / 2.f;
	m_tCollSize.fLeftWidth = m_pOwner->GetPos().x - m_vScale.x / 2.f;
	m_tCollSize.fRightWidth = m_pOwner->GetPos().x + m_vScale.x / 2.f;
}

void CCollider::finalupdate()
{
	if (!m_bActive)
		return;

	Vec2 vPos = m_pOwner->GetPos();
	finalPos = vPos + offsetPos;

	assert(m_iCol >= 0);
}

void CCollider::render(HDC _dc)
{
	if (!m_bActive)
		return;


	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if(m_iCol)
		ePen = PEN_TYPE::RED;
	
	CSeleteGDI p(_dc, ePen);
	CSeleteGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

	Rectangle(_dc,
		(int)(vPos.x - vScale.x / 2.f),
		(int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f),
		(int)(vPos.y + vScale.y / 2.f));

}

void CCollider::OnColliderEnter(CCollider* _pOther)
{
	if (m_pOwner != nullptr)
	{
		++m_iCol;
		m_pOwner->OnColliderEnter(_pOther);
	}
}

void CCollider::OnColliderExit(CCollider* _pOther)
{
	if (m_pOwner != nullptr)
	{
		--m_iCol;
		m_pOwner->OnColliderExit(_pOther);
	}
}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}
