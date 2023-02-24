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
				m_LarrObject[i] == m_RarrObject[j]))// ex) �� �÷��̾�� �� �÷��̾��� ��, ��Ȱ���� �� collider�� ���� ��
				continue;

			CCollider* m_lCollider = m_LarrObject[i]->GetCollider();
			CCollider* m_rCollider = m_RarrObject[j]->GetCollider();

			COLLIDER_ID ID;
			ID.LEFT_ID = m_lCollider->GetID();
			ID.RIGT_ID = m_rCollider->GetID();
	

			//���� �������� ������ �˾��ϰ��� ������ map����
			iter = m_mapColInfo.find(ID.ID);

			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(make_pair(ID.ID,false));
				iter = m_mapColInfo.find(ID.ID);
			}


			if (iter->second &&
				(!m_lCollider->IsActive() || !m_rCollider->IsActive()))
			{
				//���� active�� false�ε� ���������ӿ��� �浹���̿��ٸ� exitȣ���ϰ� false�� �ٲٰ� ����������
				m_lCollider->OnColliderExit(m_rCollider);
				m_rCollider->OnColliderExit(m_lCollider);
				iter->second = false;
				continue;
			}

			else if (!m_lCollider->IsActive() || !m_rCollider->IsActive())
				continue;


			if (IsCollision(m_lCollider, m_rCollider))
			{
				if (iter->second)//���� �����ӿ����� �ε��ƴ�
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

				else//���� �����ӿ����� �� �ε��ƴ�
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
				//�׾��ٸ� �׳� �˾Ƽ� �������� ���α�
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
	
	//��ü ���� - 
	//ũ�� /2 ������ �� < �� ��ü �������� �Ÿ� = �׷� ��ħ
	
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

	if (iRow > iCol)//iRow�� �� �۾ƾ��� ��
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	//���࿡ üũ�� �Ǿ��ִ� �����̸� ���־���

	if (m_arrCheck[iRow] & (1 << iCol))//�̹� �� �ִٸ�
	{           
		m_arrCheck[iRow] &= ~(1 << iCol);//��Ʈ 0���� �ٽ� �����
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);//1�� �÷���ŭ �о ���Ϳ� �ֱ�
	}
}


