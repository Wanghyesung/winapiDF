#pragma once

class CScene;
class CEventMgr;
class CInterFace;

class SceneMgr
{
	SINGLE(SceneMgr)

private:
	CScene* m_pCurrScene;//ÇöÀç ¾À
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];//¸ðµç ¾À

public:
	virtual void render(HDC _dc);
	virtual void update();


public:
	void ChangeScene(SCENE_TYPE _eNext);
	CScene* GetCurSCene() { return m_pCurrScene; }

	CScene* FindScene(SCENE_TYPE _eSceneType);
	const vector<CScene*>& GetDungeonType(DUNGEON_TYPE _eDunType);

	void init();


private:

	friend class CEventMgr;
};

