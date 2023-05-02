#include "pch.h"
#include "CScene.h"

#include "CCore.h"

#include "CObject.h"


#include "CTexture.h"
#include "CCameraMgr.h"
#include "CGravity.h"

#include "CHP.h"
#include "CMP.h"
#include "CInterFace.h"
#include "CInterfaceMgr.h"
#include "CInvenIcon.h"
#include "CSkillIcon.h"

#include "CResMgr.h"
#include "CMonInterface.h"
#include "CHP.h"


CScene::CScene():
	m_pPlayer(nullptr),
	m_pBackgroundTex(nullptr),
	m_eDungeonType(DUNGEON_TYPE::NONE)
{

}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			delete m_arrObj[i][j];
			m_arrObj[i][j] = nullptr;
		}
		m_arrObj[i].clear();
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();
		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				//delete하기 전에 내 벡터에서 지우기
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			//죽었으면 update할 필요가 없음 
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
		}
	}
}



void CScene::backgroundrender(HDC _dc, CTexture* _pTex, Vec2 _vStartPos)
{
	Vec2 StartRenderPos = CCameraMgr::GetInst()->GetRenderPos(_vStartPos); //배경 이미지를 그릴 좌상단 시작점

	BitBlt(_dc,
		(int)(StartRenderPos.x),
		(int)(StartRenderPos.y),
		(int)(_pTex->Width()),
		(int)(_pTex->Height()),
		_pTex->GetDC(),
		0, 0,
		SRCCOPY);
}

void CScene::Tile_render(HDC _dc, CTexture* _pTex)
{
	Vec2 RenderPos = CCameraMgr::GetInst()->GetRenderPos(m_vStartDrawPos);
	Vec2 vCenter = Vec2(_pTex->Width() / .2f, _pTex->Height() / 2.f);

	TransparentBlt(_dc,
		(int)(RenderPos.x),
		(int)(RenderPos.y),
		(int)(_pTex->Width()),
		(int)(_pTex->Height()),
		_pTex->GetDC(),
		(int)(0),
		(int)(0),
		(int)(_pTex->Width()),
		(int)(_pTex->Height()),
		RGB(0, 0, 0));

	/*TransparentBlt(_dc,
		(int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f),
		(int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f),
		(int)(m_vecFrm[m_iCurFrm].vSlice.x),
		(int)(m_vecFrm[m_iCurFrm].vSlice.y),
		m_pTex->GetDC(),
		(int)(m_vecFrm[m_iCurFrm].vLt.x),
		(int)(m_vecFrm[m_iCurFrm].vLt.y),
		(int)(m_vecFrm[m_iCurFrm].vSlice.x),
		(int)(m_vecFrm[m_iCurFrm].vSlice.y),
		RGB(m_pAnimator->r, m_pAnimator->g, m_pAnimator->b));*/
}


void CScene::RegisterPlayer(CObject* _pObj)
{
	m_pPlayer = _pObj;
}

void CScene::CreateInterFace()
{
	CInterFace* pInterFace = new CInterFace;
	//pInterFace->SetScale(Vec2(500.f, 120.f));
	pInterFace->SetPos(Vec2(0.f, 599.f));

	CHP* pHP = new CHP;
	//pHP->SetScale(Vec2(75.f, 97.f));
	pHP->SetPos(Vec2(9.f, 10.f));
	pInterFace->AddChildUI(pHP);

	CMP* pMP = new CMP;
	pMP->SetPos(Vec2(1195.f, 10.f));
	pInterFace->AddChildUI(pMP);

	CInvenIcon* pInvenIcon = new CInvenIcon;
	pInvenIcon->SetPos(Vec2(668.f, 42.f));
	pInterFace->AddChildUI(pInvenIcon);

	CSkillIcon* pSkillIcon = new CSkillIcon;
	pSkillIcon->SetPos(Vec2(573.f, 42.f));
	pInterFace->AddChildUI(pSkillIcon);

	AddObject(pInterFace, GROUP_TYPE::UI);

	CInterfaceMgr::GetInst()->SetInterFace(pInterFace);
}


void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eGruup)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eGruup]);
}



