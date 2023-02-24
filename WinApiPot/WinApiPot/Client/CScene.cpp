#include "pch.h"
#include "CScene.h"

#include "CCore.h"

#include "CObject.h"


#include "CTexture.h"
#include "CCameraMgr.h"
#include "CGravity.h"

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

void CScene::RegisterPlayer(CObject* _pObj)
{
	m_pPlayer = _pObj;
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if (i == (UINT)GROUP_TYPE::SKILL)
		{
			int a = 10;
		}
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eGruup)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eGruup]);
}



