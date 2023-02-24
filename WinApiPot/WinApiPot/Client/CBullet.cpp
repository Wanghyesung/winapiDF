#include "pch.h"
#include "CBullet.h"

#include "CMonster.h"

#include "CObject.h";
#include "CPlayer.h"

#include "CCollider.h"
#include "CTimeMgr.h"

#include "CCameraMgr.h"
#include "CSkill.h"
#include "CSkillState.h"
#include "CWalkFire.h"

#include "CTexture.h"
#include "CCameraMgr.h"

#define DOWN_DIR 0.4f
#define AIR_DIR 0.6f
#define LEFT_ANIM_OFFSET 20.f



CBullet::CBullet(CPlayer* _pPlayer, ATTACK_TYPE _eAttType = ATTACK_TYPE::NORMAL) :
	m_fSpeed(600.f),
	m_pCollider(nullptr),
	m_pPlayer(_pPlayer),
	m_vDir(Vec2(0.f, 0.f)),
	m_vPos(Vec2(0.f, 0.f)),
	vDeadLine(Vec2(0.f, 0.f)),
	m_fDelTime(5.f),
	m_fCurTime(0.f)
{

	SetTag(GROUP_TYPE::SKILL);

	m_tAtt.m_fAttackDamage = 20.f;
	m_tAtt.m_fAttRigidityTime = 0.8f;
	m_tAtt.m_fAttUpperRcnt = -60.f;
	m_tAtt.m_fAttRcnt = 30.f;
	m_tAtt.m_eAttType = _eAttType;

	//충돌체 생성
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 20.f));

	//나가는 방향
	SetName(L"Bullet");
	if (m_pPlayer->playerCurState == PLAYER_STATE::ATTACK || m_pPlayer->m_bOnSkill)
	{
		m_vDir = Vec2(m_pPlayer->m_iDirX, 0).NormalRize();
		vDeadLine = Vec2(0.f, m_pPlayer->GetCollider()->GetFinalPos().y);
	}
	
	else if(m_pPlayer->playerCurState == PLAYER_STATE::ATTACK_DOWN)
	{
		m_vDir = Vec2((float)m_pPlayer->m_iDirX, DOWN_DIR).NormalRize();
		vDeadLine = Vec2(0.f, m_pPlayer->GetCollider()->GetFinalPos().y);
	}

	else if (m_pPlayer->playerCurState == PLAYER_STATE::ATTACK_AIR)
	{
		m_vDir = Vec2((float)m_pPlayer->m_iDirX, AIR_DIR).NormalRize();
		vDeadLine = m_pPlayer->GetJumPos() + m_pPlayer->GetCollider()->GetOffSetPos();
	}
	

	//총알이 발사되는 시점
	if (m_vDir.x < 0)
	{
		m_vPos = m_pPlayer->GetPos();
		m_vPos.x += m_vDir.x * 80.f - LEFT_ANIM_OFFSET;
	}
	else
	{
		m_vPos = m_pPlayer->GetPos();
		m_vPos.x += m_vDir.x * 80.f;
	}
}

CBullet::~CBullet()
{
	
}

void CBullet::render(HDC _dc)
{
	//총알 텍스쳐 가지고있으면
	CTexture* pBullet =m_pPlayer->m_pBullet;
	Vec2 vPos = CCameraMgr::GetInst()->GetRenderPos(m_vPos);
	if (pBullet != nullptr)
	{
		TransparentBlt(_dc,
			(int)(vPos.x - pBullet->Width()/ 2.f),
			(int)(vPos.y - pBullet->Height() / 2.f),
			(int)( pBullet->Width()),
			(int)( pBullet->Height()),
			pBullet->GetDC(),
			(int)0,
			(int)0,
			(int)(pBullet->Width()),
			(int)(pBullet->Height()),
			RGB(255, 255, 255));
	}

	component_render(_dc);
}

void CBullet::update()
{

	m_fCurTime += fDT;
	if (m_fCurTime >= m_fDelTime)
	{
		DeleteObject(this);
		return;
	}

	if (GetPos().y > vDeadLine.y)
	{
		DeleteObject(this);
		return;
	}

	m_vPos +=  m_vDir * m_fSpeed * fDT;
	SetPos(m_vPos);
	//내 colliderY값과 똑같아지면 삭제
}

void CBullet::OnColliderEnter(CCollider* _pOther)
{
	GROUP_TYPE tTag = _pOther->GetObj()->GetTag();

	if (tTag == GROUP_TYPE::MONSTER)
	{
		//죽으면 false
		if (((CMonster*)_pOther->GetObj())->IsActiv())
		{
			DeleteObject(this);
		}
	}
}

void CBullet::OnColliderExit(CCollider* _pOther)
{

}

void CBullet::OnCollision(CCollider* _pOther)
{

}
