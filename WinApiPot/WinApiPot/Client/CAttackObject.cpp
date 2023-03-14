#include "pch.h"
#include "CAttackObject.h"

#include "CMonster.h"
#include "CCollider.h"
#include "AI.h"
#include "CState.h"

CAttackObject::CAttackObject() :
	m_pOwner(nullptr),
	m_fAttackRange(50.f),
	m_iCurAttackIndex(0)
{
	SetName(L"MonAttackObject");
	SetTag(GROUP_TYPE::MONSTER_SKILL);

	CreateCollider();
	GetCollider()->SetScale(Vec2(60.f, 60.f));

	GetCollider()->SetActive(false);
}

CAttackObject::CAttackObject(Vec2 _vScale):
	m_pOwner(nullptr),
	m_fAttackRange(50.f),
	m_iCurAttackIndex(0)
{
	SetName(L"MonAttackObject");
	SetTag(GROUP_TYPE::MONSTER_SKILL);

	CreateCollider();
	GetCollider()->SetScale(_vScale);

	GetCollider()->SetActive(false);
}

CAttackObject::~CAttackObject()
{

}

void CAttackObject::Skill_update()
{
	//내 몬스터 오브젝트의 위치
	CCollider* pCollider = GetCollider();
	//내 콜라이더가 비활성이면 반환
	if (!pCollider->IsActive())
		return;

	SetPos(m_pOwner->GetCollider()->GetFinalPos());

	//방향잡기
	int iDir = m_pOwner->GetAI()->GetCurState()->GetDir();
	Vec2 vFinalPos = pCollider->GetFinalPos();
	GetCollider()->SetOffSet(Vec2(iDir * m_fAttackRange, 0.f));
}

void CAttackObject::render(HDC _dc)
{
	if (!GetCollider()->IsActive())
		return;

	component_render(_dc);
}

void CAttackObject::SetColActive(bool _b)
{
	GetCollider()->SetActive(_b);
}

const tAttackInfo& CAttackObject::GetAttInfo()
{
	vector<tMonSkill>& vecSkill = m_pOwner->GetVecSkill();
	//스킬 벡터에 몇번째 스킬인지
	return vecSkill[m_iCurAttackIndex].m_MonAttackInfo;
}

void CAttackObject::SetAttackRange(float _fXRange, Vec2 _vCollScale)
{
	m_fAttackRange = _fXRange;
	GetCollider()->SetScale(_vCollScale);
}

void CAttackObject::OnColliderEnter(CCollider* _pOther)
{
	int a = 10;
}

void CAttackObject::OnColliderExit(CCollider* _pOther)
{

}

void CAttackObject::OnCollision(CCollider* _pOther)
{
}
