#include <random>

#include "pch.h"
#include "CThunderDown.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CCollider.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CLord.h"

CThunderDown::CThunderDown():
	pTex(nullptr),
	m_pOwner(nullptr),
	m_fDegree(0.f)
{
	SetTag(GROUP_TYPE::MONSTER_SKILL);
	SetName(L"Thunder_down");

	pTex = CResMgr::GetInst()->LoadTextur(L"Thunder_down", L"..\\OutPut\\bin_release\\Content\\emfact\\Thunder_down.bmp");

	CreateCollider();
	GetCollider()->SetScale(Vec2(200.f,100.f));
	GetCollider()->SetOffSet(Vec2(0.f, 150.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Thunder_right", pTex, Vec2(0.f, 0.f), Vec2(350.f, 500.f), Vec2(350.f, 0.f), Vec2(0.f, 0.f), 0.1f, 8);

	// �õ尪 �ޱ�
	std::random_device rDiv;

	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	std::mt19937 en(rDiv());

	// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
	std::uniform_int_distribution<int> dis(0, 360);
	m_fDegree = (float)dis(en);
}

CThunderDown::~CThunderDown()
{
}

void CThunderDown::render(HDC _dc)
{
	component_render(_dc);
}

void CThunderDown::update()
{
	if (m_pOwner == nullptr)
	{
		DeleteObject(this);
		return;
	}

	Vec2 vLordPos = m_pOwner->GetPos();
	//ȸ���� (���⺤��)
	Vec2 vNor = Rotate(vLordPos, m_fDegree);

	//���� ������ ��ġ
	SetPos(vLordPos + vNor * 300.f);
	GetAnimator()->Play(L"Thunder_right",false);
	int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();
	if (iFrame == -1)
	{
		DeleteObject(this);
		return;
	}

	if (iFrame < 2)
		GetCollider()->SetActive(false);
	else
		GetCollider()->SetActive(true);
}

void CThunderDown::OnColliderEnter(CCollider* _pOther)
{

}

void CThunderDown::OnColliderExit(CCollider* _pOther)
{
}

void CThunderDown::OnCollision(CCollider* _pOther)
{
}
