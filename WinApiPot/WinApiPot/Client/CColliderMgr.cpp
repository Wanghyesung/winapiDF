#include "pch.h"
#include "CColliderMgr.h"


#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

#include "CSkill.h"
#include "CSkillState.h"

CColliderMgr::CColliderMgr():
	m_mapColInfo{}
{

}

CColliderMgr::~CColliderMgr()
{

}


void CColliderMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}


}

void CColliderMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* m_pCurScene = SceneMgr::GetInst()->GetCurSCene();

	const vector<CObject*>& m_LarrObject = m_pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& m_RarrObject = m_pCurScene->GetGroupObject(_eRight);

	map<ULONGLONG, bool>::iterator iter;


	for (int i = 0; i < m_LarrObject.size(); ++i)
	{
		if (m_LarrObject[i]->GetCollider() == nullptr)
			continue;

		for (int j = 0; j < m_RarrObject.size(); ++j)
		{
			if ((m_RarrObject[j]->GetCollider() == nullptr ||
				m_LarrObject[i] == m_RarrObject[j]))// ex) 내 플레이어랑 내 플레이어일 떄, 비활성일 떄 collider가 없을 떄
				continue;

			CCollider* m_lCollider = m_LarrObject[i]->GetCollider();
			CCollider* m_rCollider = m_RarrObject[j]->GetCollider();

			COLLIDER_ID ID;
			ID.LEFT_ID = m_lCollider->GetID();
			ID.RIGT_ID = m_rCollider->GetID();
	

			//이전 프레임의 정보를 알야하가기 때문에 map으로
			iter = m_mapColInfo.find(ID.ID);

			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(make_pair(ID.ID,false));
				iter = m_mapColInfo.find(ID.ID);
			}


			if (iter->second &&
				(!m_lCollider->IsActive() || !m_rCollider->IsActive()))
			{
				//만약 active가 false인데 이전프레임에서 충돌중이였다면 exit호출하고 false로 바꾸고 빠져나가기
				m_lCollider->OnColliderExit(m_rCollider);
				m_rCollider->OnColliderExit(m_lCollider);
				iter->second = false;
				continue;
			}

			else if (!m_lCollider->IsActive() || !m_rCollider->IsActive())
				continue;


			if (IsCollision(m_lCollider, m_rCollider))
			{
				if (iter->second)//이전 프레임에서도 부딪쳤다
				{
					if (m_LarrObject[i]->IsDead() || m_RarrObject[j]->IsDead())
					{
						m_lCollider->OnColliderExit(m_rCollider);
						m_rCollider->OnColliderExit(m_lCollider);
						iter->second = false;
					}

					else
					{
						m_lCollider->OnCollision(m_rCollider);
						m_rCollider->OnCollision(m_lCollider);
					}
				}

				else//저번 프레임에서는 안 부딪쳤다
				{
					if (!m_LarrObject[i]->IsDead() && !m_RarrObject[j]->IsDead())
					{
						m_lCollider->OnColliderEnter(m_rCollider);
						m_rCollider->OnColliderEnter(m_lCollider);
						iter->second = true;
					}
				}
			}

			else
			{
				//죽었다면 그냥 알아서 없어지게 냅두기
				if (iter->second)
				{
					iter->second = false;
					m_lCollider->OnColliderExit(m_rCollider);
					m_rCollider->OnColliderExit(m_lCollider);
				}
			}
		}
	}
}




bool CColliderMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLPos = _pLeftCol->GetFinalPos();
	Vec2 vLScale = _pLeftCol->GetScale();

	Vec2 vRPos = _pRightCol->GetFinalPos();
	Vec2 vRScale = _pRightCol->GetScale();
	
	//전체 길이 - 
	//크기 /2 끼리의 합 < 두 물체 끼리리의 거리 = 그럼 겹침
	
	if (abs(vLPos.x - vRPos.x) <= abs((vRScale.x + vLScale.x) /2.f) &&
		abs(vLPos.y - vRPos.y) <= abs((vRScale.y + vLScale.y) / 2.f))
	{
		return true;
	}
	return false;
}

void CColliderMgr::ChekGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iRow > iCol)//iRow가 더 작아야함 열
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	//만약에 체크가 되어있는 상태이면 없애야함

	if (m_arrCheck[iRow] & (1 << iCol))//이미 들어가 있다면
	{           
		m_arrCheck[iRow] &= ~(1 << iCol);//비트 0으로 다시 만들기
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);//1을 컬럼만큼 밀어서 벡터에 넣기
	}
}


