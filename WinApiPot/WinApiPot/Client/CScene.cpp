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


CScene::CScene():
	m_pPlayer(nullptr),
	m_pBackgroundTex(nullptr)
{

}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i]그룹의 j 물체 삭제 
			delete m_arrObj[i][j];
		}
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
	CTexture* m_pBackGround = _pTex;
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
	BitBlt(_dc,
		(int)(m_vStartDrawPos.x),
		(int)(m_vStartDrawPos.y),
		(int)(_pTex->Width()),
		(int)(_pTex->Height()),
		_pTex->GetDC(),
		0, 0,
		SRCCOPY);
}

void CScene::SetInterFace()
{
	CInterFace* pInterFace = new CInterFace();
	pInterFace->SetScale(Vec2(500.f, 120.f));
	pInterFace->SetPos(Vec2(400.f, 580.f));

	CHP* pHP = new CHP;
	pHP->SetScale(Vec2(75.f, 97.f));
	pHP->SetPos(Vec2(13.f, 14.f));
	pInterFace->AddChildUI(pHP);

	CMP* pMP = new CMP;
	pMP->SetScale(Vec2(75.f, 97.f));
	pMP->SetPos(Vec2(403.f, 14.f));
	pInterFace->AddChildUI(pMP);

	AddObject(pInterFace, GROUP_TYPE::UI);

	CInterfaceMgr::GetInst()->SetInterFace(pInterFace);

}





void CScene::RegisterPlayer(CObject* _pObj)
{
	m_pPlayer = _pObj;
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



