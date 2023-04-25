#include "pch.h"
#include "CParticle.h"

#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"

CParticle::CParticle():
	m_iDir(0)
{
	SetTag(GROUP_TYPE::PARTICLE);

	CreateAnimator();
	CTexture* pTexRight = CResMgr::GetInst()->LoadTextur(L"particle_right", L"..\\OutPut\\bin_release\\Content\\emfact\\particle_right.bmp");
	CTexture* pTexLeft = CResMgr::GetInst()->LoadTextur(L"particle_left", L"..\\OutPut\\bin_release\\Content\\emfact\\particle_left.bmp");

	GetAnimator()->CreateAnimation(L"Particle_right", pTexRight, Vec2(0.f,0.f), Vec2(110.f,175.f),Vec2(110.f,0.f),Vec2(0.f,0.f),0.1f,3);
	GetAnimator()->CreateAnimation(L"Particle_left", pTexLeft, Vec2(220.f, 0.f), Vec2(110.f, 175.f), Vec2(-110.f, 0.f), Vec2(0.f, 0.f), 0.1f, 3);
}

CParticle::~CParticle()
{
}

void CParticle::render(HDC _dc)
{
	component_render(_dc);
}

void CParticle::update()
{
	int iFrame = GetAnimator()->GetCurAnimation()->GetCurFrame();

	if (iFrame == -1)
	{
		DeleteObject(this);
	}
}

void CParticle::SetDir(int _iDir)
{
	wstring strDir;
	m_iDir = _iDir;
	m_iDir > 0 ? strDir = L"_right" : strDir = L"_left";
	GetAnimator()->Play(L"Particle" + strDir, false);
}
