#pragma once
//보스 잡으면 다른 몬스터들 잡고 continueUI 생성
//활성화 상태가 아니면 그리지말기

class CClearUI;
class CChangeUI;
class CReStartUI;
class CTownUI;
class CGate;
class CTexture;

class CDungeonMgr
{
	SINGLE(CDungeonMgr);

private:
	vector<CClearUI*> m_vecClearUI;
	
	SCENE_TYPE m_eCurScene;
	DUNGEON_TYPE m_eCurDunType;

	//방문한 맵 확인
	vector<UINT> m_vecVisited;

	CTexture* m_pPlayerIconTex;
	CTexture* m_pBossIconTex;
	CTexture* m_pMiniMapTex;
	CTexture* m_pLineTex;
	CTexture* m_pLineLastTex;
	CTexture* m_pminMap_;

	Vec2 m_vIconPos;
	Vec2 m_vCurPos;

	bool m_bRenderOn;

public:
	void SetActive(SCENE_TYPE _eSceneType, bool _bActive); 
	void init();
	//맵 들어갈 때 던전 크기 확인
	void init_map();

public:
	void map_clear();
	void SetDunType(DUNGEON_TYPE _eDunType) { m_eCurDunType = _eDunType; }

	void render(HDC _dc);

private:
	void restart_scene();
	void exit_dungeon();
	void change_dungeon();

	void reinit();

	void move_icon(Vec2 _vDir);

	friend class CChangeUI;
	friend class CReStartUI;
	friend class CTownUI;
	friend class CScene_Start;
	friend class SceneBoss;
	friend class CEvilBossScene;
	friend class CGate;
};

