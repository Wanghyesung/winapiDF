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
	m_fOffSet(410.f),
	m_iAttackFrame(-1),
	m_iAttackCount(1),
	m_bStart(false)
{
	//�÷��̾� �ִϸ��̼� �̸�
	SetSKillName(L"Player_skill_laser_");

	SetMP(10.f);

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::UPPER;
	tAtt.m_fAttackDamage = 70.f;
	tAtt.m_fAttRcnt = 200.f;
	tAtt.m_fAttRigidityTime = 1.3f;
	tAtt.m_fAttUpperRcnt = -200.f;
	tAtt.m_fAttUpperAcc = -600.f;

	SetAttInfo(tAtt);

	SetSkillTime(1);

	CTexture* pLaserTexRight = CResMgr::GetInst()->LoadTextur(L"Laser_right", L"..\\OutPut\\bin_release\\Content\\Texture\\laser_right.bmp");
	CTexture* pLaserTexLeft = CResMgr::GetInst()->LoadTextur(L"Laser_left", L"..\\OutPut\\bin_release\\Content\\Texture\\laser_left.bmp");

	//�� ��ų �ִϸ��̼� �̸�
	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);
	GetAnimator()->CreateAnimation(L"Laser_right", pLaserTexRight, Vec2(0.f, 0.f), Vec2(730.f, 250.f), Vec2(0.f, 250.f), Vec2(0.f, 0.f), 0.11f, 9);
	GetAnimator()->CreateAnimation(L"Laser_left", pLaserTexLeft, Vec2(0.f, 0.f), Vec2(730.f, 250.f), Vec2(0.f, 250.f), Vec2(0.f, 0.f), 0.11f, 9);
}

CLaser::~CLaser()
{
	
}

void CLaser::Skillupdate()
{
	CPlayer* pPlayer = GetSkill()->GetPlayer();

	int iFrame = GetCurFram();

	if (iFrame == -1)
	{
		exit();
		return;
	}

	if (iFrame >= 3)
	{
		m_bStart = true;
		GetAnimator()->Play(m_strLaserName, false);
	}

	if (iFrame >= 5)
	{
		int iLaserFrame = GetAnimator()->FindAnimation(m_strLaserName)->GetCurFrame();
		if (iLaserFrame == -1)
			return;
		if (iLaserFrame <= 3)
		{
			pPlayer->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(5);
		}
	}

}

void CLaser::init()
{
	CreateCollider();
	GetCollider()->SetActive(false);

	for (int i = 4; i <= 7; ++i)
	{
		AddAttackFrame(i);
	}
	m_vCollSize = Vec2(640.f, 60.f);
	GetCollider()->SetScale(m_vCollSize);
}

void CLaser::exit()
{
	//�÷��̾�
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(0);

	//������
	GetAnimator()->FindAnimation(m_strLaserName)->SetFram(0);

	m_bStart = false;

	CSkillState::exit();
}

void CLaser::enter()
{
	CSkillState::enter();

	CPlayer* pPlayer = GetSkill()->GetPlayer();
	int iDir = pPlayer->GetPlayerDirX();

	Vec2 vPlayerPos = pPlayer->GetPos();
	if (iDir > 0)
	{
		m_strSkillName = L"Player_skill_laser_right";
		m_strLaserName = L"Laser_right";
		m_vCollOffSet = Vec2(45.f, 0.f);
		SetPos(vPlayerPos + Vec2(m_fOffSet * iDir, 15.f));
	}
	else
	{
		m_strSkillName = L"Player_skill_laser_left";
		m_strLaserName = L"Laser_left";
		m_vCollOffSet = Vec2(-45.f, 0.f);
		SetPos(vPlayerPos + Vec2((m_fOffSet + 40) * iDir, 15.f));
	}

	GetCollider()->SetOffSet(m_vCollOffSet);

	
}

void CLaser::render(HDC _dc)
{
	if(m_bStart)
		component_render(_dc);
}

void CLaser::finalupdate()
{	
	if (m_bStart)
		CObject::finalupdate();	
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
		if (m_bStart == false)
			return;

		const vector<UINT> vecFrame = GetAttackFrame();
		//���� �ݸ��̴� ID�� vec�� ����
		vector<UINT>& vecColl = GetOtherCollVec();

		//�� ������ ���� �ִϸ��̼�
		int iCurFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();

		//�巡�� ������Ʈ ��
		for (int i = 0; i < vecFrame.size(); ++i)
		{
			//�ݶ��̴�ID�� �ش��ϴ� ������ ���� �� ���ü��� �޶����
			//���� ������ �����Ӱ� �Ȱ��ƾ� ��
			if (vecFrame[i] == iCurFrame && vecColl[_pOther->GetID()] != m_iAttackCount)
			{
				vecColl[_pOther->GetID()] = m_iAttackCount;
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
