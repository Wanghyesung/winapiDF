#pragma once

class CObject;
class CTexture;
class CInterFace;

struct tBackGround 
{
	float fLeftWidth;
	UINT fRightWidth;
	float fTopHeight;
	UINT fBottomHeight;
};


class CScene
{
public:
	CScene();
	virtual ~CScene();//연속적으로 삭제

private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; //내 오브젝트 클래스들을 다루는 곳
	CObject*		 m_pPlayer; //내 플레이어

	wstring			m_strName; //씬의 이름

	CTexture*		m_pBackgroundTex;
	Vec2			m_vStartDrawPos; //그릴 이미지의 시작점
	tBackGround     m_tBackgroundInfo;

	DUNGEON_TYPE     m_eDungeonType;

public:
	virtual void render(HDC _dc);
	virtual void update();//여기서 업데이트 하고 각각의 오브젝트에서 update, finalupdate
	virtual void finalupdate();

	void RegisterPlayer(CObject* _pObj);

	//배경
	void backgroundrender(HDC _dc, CTexture* _pTex, Vec2 _vStartPos);
	void Tile_render(HDC _dc, CTexture* _pTex);

	virtual void Enter() = 0;//현재 씬 들어갈 때 
	virtual void Exit() = 0; //현재 씬 나갈 떄
	virtual void Init() = 0; //한번만 실행

	//맵의 몬스터 다시 생성
	virtual void InitMonster() {};

	void SetBackGround(CTexture* _pTex) { m_pBackgroundTex = _pTex; }
	CTexture* GetBackGround() { return m_pBackgroundTex; }


	//벽 콜라이더 만들면 삭제
	void SetBackGroundInfo(const tBackGround _tInfo) { m_tBackgroundInfo = _tInfo; }
	const tBackGround& GetBackGroundInfo() {return m_tBackgroundInfo;}

	void SetStartDrawPoint(Vec2 _v) { m_vStartDrawPos = _v; }
	Vec2 GetStartDrawPoint() { return m_vStartDrawPos; }

	void SetDungeonType(DUNGEON_TYPE _eDunType) { m_eDungeonType = _eDunType; }
	//인터페이스
public:
	void CreateInterFace();

public:
	void DeleteAll();
	void DeleteGroup(GROUP_TYPE _eGruup);

public:
	const wstring& GetName() { return m_strName; }
	void SetName(const wstring& _strName) { m_strName = _strName; }
	
public:
	void AddObject(CObject* _pObj , GROUP_TYPE _eType)//그룹 오브젝트 넣기
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);//내 씬 오브젝트 배열 안에 넣어주기
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) {return m_arrObj[(UINT)_eType];}
	vector<CObject*>& GetGroupUI() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

	CObject* GetPlayerObj() 
	{
		return m_pPlayer; 
	}

	
	//init은 초기화할때 1번 (몬스터 생성)
	//enter은 씬 바뀔때마다 계속 (충돌)
protected:

	friend class SceneMgr;
};

