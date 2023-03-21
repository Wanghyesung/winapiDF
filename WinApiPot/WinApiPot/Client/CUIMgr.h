#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* m_pFoucseUI;

public:
	void update();
	void SetFoucseUI(CUI* _pUI);
	void MoveFrontChildUI(CUI* pUI);

public:
	CUI* GetFoucseUI();
	CUI* GetTargetUI(CUI* _pParentUI);



};

