#include "pch.h"
#include "CMultiHead.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CSkill.h"
#include "CPlayer.h"
#include "CRigidBody.h"
#include "CParticle.h"

#include "CResMgr.h"
#include "CSound.h"

#define SHOT_MOTION 1

CMultiHead::CMultiHead():
	CSkillState(SKILL_STATE::MULTI_HEAD),
	m_fCurExitTime(0.f),
	m_fExitTime(1.0f),
	m_iCurAttackCount(-1),
	m_iAttackCount(0),
	m_fChangeTime(0.5f),
	m_fCurChangeTime(0.f),
	m_iDirX(1),
	m_iDirY(0),
	m_strPreStateName(L"")
{
	SetMP(8.f);
	
	SetSKillName(L"Player_skill_multihead");
	
	SetSkillTime(3);

	tAttackInfo tAtt = {};
	tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	tAtt.m_fAttackDamage = 10.f;
	tAtt.m_fAttRcnt = 100.f;
	tAtt.m_fAttRigidityTime = 1.3f;
	tAtt.m_fAttUpperRcnt = -80.f;
	
	SetAttInfo(tAtt);

	//SetAnimSound(L"gn_mvshot");
	SetAnimSound(L"gn_multihead_0");
	SetAnimSound(L"gn_multihead_1");
	SetAnimSound(L"gn_multihead_2");
	SetAnimSound(L"gn_multihead_3");
	SetAnimSound(L"gn_multihead_4");
	SetAnimSound(L"gn_multihead_ready");
}

CMultiHead::~CMultiHead()
{

}

void CMultiHead::Skillupdate()
{
	bool bInputKey = false;

	m_fCurExitTime += fDT;
	m_fCurChangeTime -= fDT;

	if (m_fCurExitTime > m_fExitTime)
	{
		exit();
		return;
	}

	wstring strResult = L"Player_skill_multihead";
	m_iDirX > 0 ? strResult += L"_right" : strResult += L"_left";
	if (m_fCurChangeTime <= 0.f)
	{
		if (KEY_TAP(KEY::RIGHT) || KEY_HOLD(KEY::RIGHT))
		{
			change_Dir(1, 0);
			m_iDirX > 0  ? strResult += L"_f" : strResult += L"_b";
			bInputKey = true;
			m_fCurChangeTime = m_fChangeTime;
		}
		else if (KEY_TAP(KEY::LEFT) || KEY_HOLD(KEY::LEFT))
		{
			change_Dir(-1, 0);
			m_iDirX > 0 ? strResult += L"_b" : strResult += L"_f";
			bInputKey = true;
			m_fCurChangeTime = m_fChangeTime;
		}

		else if (KEY_TAP(KEY::UP) || KEY_HOLD(KEY::UP))
		{
			change_Dir(0, -1);
			strResult += L"_u";
			bInputKey = true;
			m_fCurChangeTime = m_fChangeTime;
		}

		else if (KEY_TAP(KEY::DOWN) || KEY_HOLD(KEY::DOWN))
		{
			change_Dir(0, 1);
			strResult += L"_d";
			bInputKey = true;
			m_fCurChangeTime = m_fChangeTime;
		}

		if (bInputKey)
		{
			SetSKillName(strResult);
			m_strSkillName = GetSkillName();
			m_strPreStateName = m_strSkillName;
		}
	}
	
	if (!bInputKey)
	{
		if (m_strPreStateName != L"")
			SetSKillName(m_strPreStateName);
		else
			SetSKillName(strResult + L"_f");
		m_strSkillName = GetSkillName();
	}

	CAnimator* pAnim = GetSkill()->GetPlayer()->GetAnimator();
	int iFrame = pAnim->FindAnimation(m_strSkillName)->GetCurFrame();


	if (iFrame == 3 && m_iAttackCount < 5)
		pAnim->FindAnimation(m_strSkillName)->SetFram(3);
	else if (m_iAttackCount >= 5)
		exit();

}

void CMultiHead::update()
{ 

}

void CMultiHead::init()
{
	CreateCollider();
	GetCollider()->SetActive(false);

	AddAttackFrame(SHOT_MOTION);

	m_vCollSize = Vec2(250.f, 250.f);
	GetCollider()->SetScale(m_vCollSize);
}

void CMultiHead::exit()
{
	CSound* pSound = CResMgr::GetInst()->FindSound(L"gn_multihead_4");
	pSound->Play(false);

	m_strPreStateName = L"";
	SetSKillName(L"Player_skill_multihead");
	m_iAttackCount = 0;
	m_iCurAttackCount = -1;
	m_fCurExitTime = 0.f;
	m_fCurChangeTime = 0.f;
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(0);
	CSkillState::exit();
}

void CMultiHead::enter()
{
	CPlayer* pPlayer = GetSkill()->GetPlayer();
	Vec2 vPos = pPlayer->GetCollider()->GetFinalPos();
	SetPos(vPos);

	m_iDirX = pPlayer->GetPlayerDirX();
	wstring strSkillName = GetSkillName();
	//m_iDirX > 0 ? m_vCollOffSet = Vec2(100.f, 0.f) : m_vCollOffSet = Vec2(-100.f, 0.f);
	//GetCollider()->SetOffSet(m_vCollOffSet);
	m_iDirX > 0 ? strSkillName += L"_right" : strSkillName += L"_left";
	Vec2 vVel = pPlayer->GetRigidBody()->GetVelocity();
	if (vVel == Vec2(0.f, 0.f))
	{
		m_iDirX > 0 ? m_vCollOffSet = Vec2(100.f, 0.f) : m_vCollOffSet = Vec2(-100.f, 0.f);
		GetCollider()->SetOffSet(m_vCollOffSet);
	}
	//x쪽 먼저 우선순위
	if (vVel.x != 0.f)
	{
		if (vVel.x > 0)
		{
			m_vCollOffSet = Vec2(100.f, 0.f);
			m_iDirX > 0 ? strSkillName += L"_f" : strSkillName += L"_b";
		}
		else
		{
			m_vCollOffSet = Vec2(-100.f, 0.f);
			m_iDirX > 0 ? strSkillName += L"_b" : strSkillName += L"_f";
		}
			
	}
	else
	{
		if (vVel.y > 0)
		{
			m_vCollOffSet = Vec2(0.f, 110.f);
			strSkillName += L"_d";
		}

		else
		{
			m_vCollOffSet = Vec2(0.f, -160.f);
			strSkillName += L"_u";
		}

	}
	SetSKillName(strSkillName);
	m_strSkillName = strSkillName;
	CSkillState::enter();
}

void CMultiHead::OnColliderEnter(CCollider* _pOther)
{
}

void CMultiHead::OnColliderExit(CCollider* _pOther)
{
}

void CMultiHead::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER ||
		_pOther->GetObj()->GetTag() == GROUP_TYPE::STONE_BOX)
	{
		const vector<UINT> vecFrame = GetAttackFrame();
		//상대방 콜리이더 ID를 vec에 저장
		vector<UINT>& vecColl = GetOtherCollVec();
		int iCurFrame = GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->GetCurFrame();

		//드래곤 오브젝트 딜
		for (int i = 0; i < vecFrame.size(); ++i)
		{
			//콜라이더ID에 해당하는 벡터의 값이 내 프레임과 달라야지 딜
			if (vecFrame[i] == iCurFrame && vecColl[_pOther->GetID()] != m_iAttackCount)
			{
				vecColl[_pOther->GetID()] = m_iAttackCount;
				SetAttackOn(true);
				create_particle(_pOther->GetFinalPos());
				break;
			}
			else
			{
				SetAttackOn(false);
			}
		}
	}
}

void CMultiHead::change_Dir(int _iDirX, int _iDirY)
{
	if (m_strSkillName == L"")
		return;

	//x방향
	if (_iDirX != 0)
	{
		if (_iDirX > 0)
		{	
			m_vCollOffSet = Vec2(100.f, 0.f);
			GetCollider()->SetOffSet(m_vCollOffSet);
		}
		else
		{
			m_vCollOffSet = Vec2(-100.f, 0.f);
			GetCollider()->SetOffSet(m_vCollOffSet);
		}
	}
	//y방향
	else
	{
		if (_iDirY > 0)
		{
			m_vCollOffSet = Vec2(0.f, 110.f);
			GetCollider()->SetOffSet(m_vCollOffSet);
		}
		else
		{
			m_vCollOffSet = Vec2(0.f, -160.f);
			GetCollider()->SetOffSet(m_vCollOffSet);
		}
	}

	//if (m_iDirX < 0)
	//{
	//	//이미지 offset때문에 추가
	//	m_vCollOffSet.x += 40.f;
	//	GetCollider()->SetOffSet(m_vCollOffSet);
	//}

	//다른 방향으로 바뀌면 이전 방향 애니메이면 초기화
	GetSkill()->GetPlayer()->GetAnimator()->FindAnimation(m_strSkillName)->SetFram(0);
	++m_iAttackCount;
	m_fCurExitTime = 0.f;

	if (m_iAttackCount != m_iCurAttackCount && m_iAttackCount < 5)
	{
		wstring strNum = std::to_wstring(m_iAttackCount - 1);
		CSound* pSound = CResMgr::GetInst()->FindSound(L"gn_multihead_" + strNum);
		pSound->Play(false);
	}
}

void CMultiHead::create_particle(Vec2 _vPos)
{
	CParticle* pParticle = new CParticle;
	pParticle->SetPos(_vPos);

	Vec2 vPos = GetCollider()->GetFinalPos();
	if (vPos.x - _vPos.x > 0)
		pParticle->SetDir(1);
	else
		pParticle->SetDir(-1);

	CreateObject(pParticle, GROUP_TYPE::PARTICLE);
}
