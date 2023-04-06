#include "pch.h"
#include "CLaser.h"

#include "CSkill.h"
#include "CPlayer.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CCollider.h"

#include "CTexture.h"
#include "CResMgr.h"

CLaser::CLaser():
	CSkillState(SKILL_STATE::LASER),
	m_fOffSet(500.f),
	m_iAttackFrame(-1),
	m_bStart(false)
{
	//플레이어 애니메이션 이름
	SetSKillName(L"Player_skill_laser_");

	SetMP(10.f);

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::UPPER;
	tAtt.m_fAttackDamage = 70.f;
	tAtt.m_fAttRcnt = 200.f;
	tAtt.m_fAttRigidityTime = 1.3f;
	tAtt.m_fAttUpperRcnt = -80.f;

	SetAttInfo(tAtt);

	SetSkillTime(1);

	CTexture* pLaserTexRight = CResMgr::GetInst()->LoadTextur(L"Laser_right", L"..\\OutPut\\bin_release\\Content\\Texture\\laser_right.bmp");
	CTexture* pLaserTexLeft = CResMgr::GetInst()->LoadTextur(L"Laser_left", L"..\\OutPut\\bin_release\\Content\\Texture\\laser_left.bmp");

	//내 스킬 애니메이션 이름
	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);
	GetAnimator()->CreateAnimation(L"Laser_right", pLaserTexRight, Vec2(0.f, 0.f), Vec2(730.f, 250.f), Vec2(0.f, 250.f), Vec2(0.f, 0.f), 0.1f, 9);
	GetAnimator()->CreateAnimation(L"Laser_left", pLaserTexLeft, Vec2(0.f, 0.f), Vec2(730.f, 250.f), Vec2(0.f, 250.f), Vec2(0.f, 0.f), 0.1f, 9);
}

CLaser::~CLaser()
{
	
}

void CLaser::Skillupdate()
{

	CPlayer* pPlayer = GetSkill()->GetPlayer();
	Vec2 pPlayerPos = pPlayer->GetPos();
	//SetPos(pPlayerPos);

	int iDir = pPlayer->GetPlayerDirX();

	float fFinalPos = m_vCollOffSet.x + iDir * m_fOffSet;
	SetPos(pPlayerPos + (Vec2(fFinalPos, m_vCollOffSet.y)));

	wstring strSkillName = GetSkillName();
	wstring strDir = iDir > 0 ? L"right" : L"left";

	m_strSkillName = strSkillName + strDir;
	m_strLaserName = L"Laser_" + strDir;
	
	CAnimator* pPlayerAnim = pPlayer->GetAnimator();
	CAnimator* pAnim = GetAnimator();
	int iFrame = GetCurFram();
	if (iFrame >= 5)
	{
		pAnim->Play(m_strLaserName, false);
		m_bStart = true;
		if (pAnim->GetCurAnimation()->GetCurFrame() < 7 &&
			!pAnim->GetCurAnimation()->IsFinish())
		{
			pPlayerAnim->FindAnimation(m_strSkillName)->SetFram(5);
		}
	}

	if (pPlayerAnim->FindAnimation(m_strSkillName)->IsFinish())
	{
		exit();
		return;
	}
}

void CLaser::init()
{
	CreateCollider();
	GetCollider()->SetActive(false);

	AddAttackFrame(4);

	m_vCollSize = Vec2(730.f, 60.f);
	m_vCollOffSet = Vec2(-20.f, 30.f);
	GetCollider()->SetScale(m_vCollSize);
	GetCollider()->SetOffSet(m_vCollOffSet);
}

void CLaser::exit()
{
	//플레이어
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(0);

	//레이저
	GetAnimator()->FindAnimation(m_strLaserName)->SetFram(0);

	CSkillState::exit();
	m_iAttackFrame = -1;
	m_bStart = false;
}

void CLaser::enter()
{
	//GetAnimator()->FindAnimation(L"Laser_right")->SetFram(0);

	CSkillState::enter();
}

void CLaser::render(HDC _dc)
{
	if (m_bStart)
	{
		component_render(_dc);
	}
}

void CLaser::finalupdate()
{
	if (m_bStart)
	{
		CObject::finalupdate();
	}
}

void CLaser::OnColliderEnter(CCollider* _pOther)
{

}

void CLaser::OnColliderExit(CCollider* _pOther)
{

}

void CLaser::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER ||
		_pOther->GetObj()->GetTag() == GROUP_TYPE::STONE_BOX)
	{
		const vector<UINT> vecFrame = GetAttackFrame();
		//상대방 콜리이더 ID를 vec에 저장
		vector<UINT>& vecColl = GetOtherCollVec();
		int iCurFrame = GetCurFram();

		//드래곤 오브젝트 딜
		for (int i = 0; i < vecFrame.size(); ++i)
		{
			//콜라이더ID에 해당하는 벡터의 값이 내 프레임과 달라야지 딜
			if (vecFrame[i] == iCurFrame && vecColl[_pOther->GetID()] != iCurFrame)
			{
				vecColl[_pOther->GetID()] = iCurFrame;
				SetAttackOn(true);
				break;
			}
			else
			{
				SetAttackOn(false);
			}
		}
	}
}
