#include "pch.h"
#include "CMultiHead.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "CSkill.h"
#include "CPlayer.h"

#define SHOT_MOTION 1

CMultiHead::CMultiHead():
	CSkillState(SKILL_STATE::MULTI_HEAD),
	m_fCurExitTime(0.f),
	m_fExitTime(1.0f),
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
	tAtt.m_fAttRcnt = 200.f;
	tAtt.m_fAttRigidityTime = 1.3f;
	tAtt.m_fAttUpperRcnt = -80.f;
	
	SetAttInfo(tAtt);

	//SetAnimSound(L"gn_mvshot");
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
	if (pAnim->FindAnimation(m_strSkillName)->GetCurFrame() == 3 && m_iAttackCount < 4)
		pAnim->FindAnimation(m_strSkillName)->SetFram(3);
	else if (pAnim->FindAnimation(m_strSkillName)->GetCurFrame() == 3 && m_iAttackCount >= 4)
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
	m_strPreStateName = L"";
	m_iAttackCount = 0;
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
	m_iDirX > 0 ? m_vCollOffSet = Vec2(100.f, 0.f) : m_vCollOffSet = Vec2(-100.f, 0.f);
	GetCollider()->SetOffSet(m_vCollOffSet);

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
}
