#pragma once
//보스 잡으면 다른 몬스터들 잡고 continueUI 생성
//활성화 상태가 아니면 그리지말기

class CClearUI;

class CDungeonMgr
{
	SINGLE(CDungeonMgr);

private:
	vector<CClearUI*> m_vecClearUI;
	
	SCENE_TYPE m_eCurScene;
	DUNGEON_TYPE m_eCurDunType;

public:
	void SetActive(SCENE_TYPE _eSceneType, bool _bActive) { m_vecClearUI[(UINT)_eSceneType]->m_bActive = _bActive; m_eCurScene = _eSceneType; }
	void init();

public:
	void map_clear();
	void SetDunType(DUNGEON_TYPE _eDunType) { m_eCurDunType = _eDunType; }

private:
	void restart_scene();
	void exit_dungeon();
	void change_dungeon();
};

