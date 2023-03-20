#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CKeyMgr.h"

#include "CUI.h"
CUIMgr::CUIMgr():
	m_pFoucseUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	//현재 마우스 위에 올라온 UI 가져오기
	m_pFoucseUI = GetFoucseUI();

	if (!m_pFoucseUI)
		return;

	// 마우스 위에 UI중에서 가장 우선순위(가장 밑에 있는)가 높은 UI 가져오기
	CUI* pTargetUI = GetTargetUI(m_pFoucseUI);

	bool KeyTap = KEY_TAP(KEY::LBTN);
	bool KeyAway = KEY_AWAY(KEY::LBTN);
	

	if (pTargetUI != nullptr)
	{
		//누르면
		pTargetUI->MouseOn();

		if (KeyTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbntDown = true;
		}

		else if (KeyAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbntDown)
			{
				pTargetUI->MouseLbtnClicked();
			}
			pTargetUI->m_bLbntDown = false;
		}
	}
}

void CUIMgr::SetFoucseUI(CUI* _pUI)
{
	
	if (m_pFoucseUI == _pUI || _pUI == nullptr)
	{
		m_pFoucseUI = _pUI;
		return;
	}

	m_pFoucseUI = _pUI;
	vector<CObject*> vecUI = SceneMgr::GetInst()->GetCurSCene()->GetGroupUI();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (*iter == m_pFoucseUI)
			break;
	}


	//가장 뒤로 보냄
	vecUI.erase(iter);
	//렌더링 할 때 가장 앞에 있어야 함
	vecUI.push_back(m_pFoucseUI);

}

CUI* CUIMgr::GetFoucseUI()
{
	vector<CObject*>& vecUI = SceneMgr::GetInst()->GetCurSCene()->GetGroupUI();

	bool bIsLbntTap = KEY_TAP(KEY::LBTN);

	CUI* pFoucseUI = m_pFoucseUI;

	if (!bIsLbntTap)
		return pFoucseUI;
	
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)(*iter))->IsMosueOn())
		{
			targetiter = iter;
		}
	}

	if (vecUI.end() == targetiter)
		return nullptr;

	pFoucseUI = ((CUI*)*targetiter);
	
	vecUI.erase(targetiter);
	vecUI.push_back(pFoucseUI);

	return pFoucseUI;
	
}

CUI* CUIMgr::GetTargetUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> vecNoeTarget;

	queue.clear();
	vecNoeTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMosueOn())
		{
			if (pTargetUI != nullptr)
			{
				vecNoeTarget.push_back(pUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoeTarget.push_back(pUI);
		}

		const vector<CUI*> vecChildUI = pUI->GetChildVecUI();
		for (int i = 0; i < vecChildUI.size(); ++i)
		{
			queue.push_back(vecChildUI[i]);
		}
	}

	if (bLbtnAway)
	{
		for (int i = 0; i < vecNoeTarget.size(); ++i)
		{
			vecNoeTarget[i]->m_bLbntDown = false;
		}
	}


	return pTargetUI;
}
