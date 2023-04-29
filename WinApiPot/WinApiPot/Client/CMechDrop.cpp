#include "pch.h"
#include "CMechDrop.h"

#include "CCameraMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CPlayer.h"
#include "CSkill.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CCollider.h"
#include "CDropRobot.h"
#include "CSound.h"


CMechDrop::CMechDrop():
	CSkillState(SKILL_STATE::DROP),
	m_bStart(false),
	m_iMoveDir(0),
	m_iCreateCount(0),
	m_fMoveValue(350.f),
	m_fCreateTime(0.3f),
	m_fCurTime(0.f)
{
	CreateCollider();
	
	SetSKillName(L"Player_skill_Fire_");

	SetSkillTime(2.f);
	SetMP(5.f);

	SetTag(GROUP_TYPE::SKILL);

	SetAnimSound(L"dropship_radio_01");
}

CMechDrop::~CMechDrop()
{
}

void CMechDrop::render(HDC _dc)
{
	if (m_bStart)
	{
		Vec2 vPos = GetPos();
		vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

		TransparentBlt(_dc,
			(int)(vPos.x - m_pMechTex->Width() / 2.f),
			(int)(vPos.y),
			(int)(m_pMechTex->Width()),
			(int)(m_pMechTex->Height()),
			m_pMechTex->GetDC(),
			(int)0,
			(int)0,
			(int)(m_pMechTex->Width()),
			(int)(m_pMechTex->Height()),
			RGB(255, 255, 255));
	}
}

void CMechDrop::Skillupdate()
{
	if (m_iCreateCount == 8)
	{
		exit();
		return;
	}

	CPlayer* pPlayer = GetSkill()->GetPlayer();

	int iFrame = pPlayer->GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iFrame >= 4)
	{
		m_bStart = true;
		pPlayer->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(4);
	}

	if (m_bStart)
	{
		m_fCurTime += fDT;

		Vec2 vPos = GetPos();
		vPos.x += m_iMoveDir * m_fMoveValue * fDT;

		SetPos(vPos);

		//여기서 발
		Vec2 vCreatePos = vPos;

		if (m_fCurTime >= m_fCreateTime)
		{
			m_fCurTime = 0.f;
			Vec2 m_fDiffPos = Vec2(m_iMoveDir * 50.f,100.f);
			for (int i = 0; i < 2; ++i)
			{
				create_dropmech(vCreatePos);
				vCreatePos -= m_fDiffPos;
				++m_iCreateCount;
			}
		}
	}

}

void CMechDrop::init()
{
	CResMgr::GetInst()->LoadTextur(L"Mech_right", L"..\\OutPut\\bin_release\\Content\\emfact\\mechdrop_right.bmp");
	CResMgr::GetInst()->LoadTextur(L"Mech_left", L"..\\OutPut\\bin_release\\Content\\emfact\\mechdrop_left.bmp");
}

void CMechDrop::exit()
{
	m_fCurTime = 0.f;
	m_iCreateCount = 0;
	m_bStart = false;
	CSkillState::exit();
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(0);
}

void CMechDrop::enter()
{
	CSkillState::enter();


	CPlayer* pPlayer = GetSkill()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetCollider()->GetFinalPos();

	SetPos(vPlayerPos);

	int iDirX = pPlayer->GetPlayerDirX();
	iDirX > 0 ? m_iMoveDir = 1 : m_iMoveDir = -1;
	//플레이어 방향에서 오른쪽으로 움직임   왼쪽으로

	wstring strDir = iDirX > 0 ? L"right" : L"left";
	wstring strSkillName = GetSkillName();
	m_strSkillName = strSkillName + strDir;

	m_pMechTex = CResMgr::GetInst()->FindTexture(L"Mech_" + strDir);
}

void CMechDrop::OnColliderEnter(CCollider* _pOther)
{
}

void CMechDrop::OnColliderExit(CCollider* _pOther)
{
}

void CMechDrop::OnCollision(CCollider* _pOther)
{
}

//생성될 위치
void CMechDrop::create_dropmech(Vec2 _vCreatePos)
{
	Vec2 vAddPos = _vCreatePos - GetPos();
	//맵 가장 위에서 생성
	CDropRobot* pDropRobot = new CDropRobot;
	pDropRobot->SetPos(Vec2(_vCreatePos.x, 0.f) + vAddPos);

	//170도 정도에 떨어지게
	pDropRobot->init_dir(m_iMoveDir, _vCreatePos);

	CreateObject(pDropRobot, GROUP_TYPE::DROUP);
}
