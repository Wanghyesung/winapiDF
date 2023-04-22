#include "pch.h"
#include "CDropRobot.h"

#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimator.h"

#include "CCollider.h"

#include "CSceneMgr.h"
#include "CScene.h"

CDropRobot::CDropRobot() :
	m_fDropSpeed(500.f),
	m_hashColl{},
	m_bAttackOn(false)
{
	SetTag(GROUP_TYPE::SKILL);

	m_tAtt.m_eAttType = ATTACK_TYPE::NORMAL;
	m_tAtt.m_fAttackDamage = 20.f;
	m_tAtt.m_fAttRcnt = 200.f;
	m_tAtt.m_fAttRigidityTime = 1.f;
	m_tAtt.m_fAttUpperRcnt = -200.f;

	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	CTexture* pDropTexRight = CResMgr::GetInst()->LoadTextur(L"Drop_right", L"..\\OutPut\\bin_release\\Content\\emfact\\drop_right.bmp");
	CTexture* pDropTexLeft = CResMgr::GetInst()->LoadTextur(L"Drop_left", L"..\\OutPut\\bin_release\\Content\\emfact\\drop_left.bmp");

	CreateAnimator();
	GetAnimator()->SetRBG(0, 0, 0);
	GetAnimator()->CreateAnimation(L"Drop_right", pDropTexRight, Vec2(0.f, 0.f), Vec2(70.f, 70.f), Vec2(70.f, 0.f), Vec2(0.f, 0.f), 1.f, 3);
	GetAnimator()->CreateAnimation(L"Drop_left", pDropTexLeft, Vec2(140.f, 0.f), Vec2(70.f, 70.f), Vec2(-70.f, 0.f), Vec2(0.f, 0.f), 1.f, 3);

	const vector<CObject*>& vecMon = SceneMgr::GetInst()->GetCurSCene()->GetGroupObject(GROUP_TYPE::MONSTER);
	for (int i = 0; i < vecMon.size(); ++i)
	{
		//부딪치면 1로 바꾸게
		m_hashColl[vecMon[i]->GetCollider()->GetID()] = 0;
	}
}

CDropRobot::~CDropRobot()
{	

}

void CDropRobot::render(HDC _dc)
{
	component_render(_dc);
}

void CDropRobot::update()
{
	Vec2 vPos = GetPos();

	if (vPos.y >= m_vCreatePos.y)
	{
		create_robot();
		DeleteObject(this);
		return;
	}

	vPos += m_vDir.NormalRize() * m_fDropSpeed * fDT;
	SetPos(vPos);
}

void CDropRobot::finalupdate()
{
	CObject::finalupdate();
}

void CDropRobot::OnColliderEnter(CCollider* _pOther)
{

}

void CDropRobot::OnColliderExit(CCollider* _pOther)
{

}

void CDropRobot::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetTag() == GROUP_TYPE::MONSTER)
	{
		if (isSameYPos(_pOther) && m_hashColl[_pOther->GetID()] == 0)
		{
			m_hashColl[_pOther->GetID()] = 1;
			m_bAttackOn = true;
		}
		else
		{
			m_bAttackOn = false;
		}
	}
}

void CDropRobot::create_robot()
{
	int a = 10;
}

void CDropRobot::init_dir(int _iDir, Vec2 _vCreatePos)
{
	m_vDir = Vec2(_iDir * 0.1f, 1.f);

	wstring strDir = _iDir > 0 ? L"_right" : L"_left";
	GetAnimator()->Play(L"Drop" + strDir, true);
	m_vCreatePos = _vCreatePos + GetCollider()->GetFinalPos();
}

bool CDropRobot::isSameYPos(CCollider* _pOtherCol)
{
	float fYPos = m_vCreatePos.y;
	float fYOtherPos = _pOtherCol->GetFinalPos().y;

	float fYSclae = GetCollider()->GetScale().y;
	float fYOtherScale = _pOtherCol->GetScale().y;
	

	float fDiff = abs(fYOtherPos - fYPos);

	if (fDiff <= abs(fYOtherScale + fYSclae) / 2.f)
	{
		return true;
	}
	return false;
}
