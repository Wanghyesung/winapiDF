#pragma once

class CObject;
class CTexture;

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

public:
	virtual void render(HDC _dc);
	virtual void update();//여기서 업데이트 하고 각각의 오브젝트에서 update, finalupdate
	virtual void finalupdate();

	//배경을 그린다
	void backgroundrender(HDC _dc, CTexture* _pTex, Vec2 _vStartPos);

	void RegisterPlayer(CObject* _pObj);

	virtual void Enter() = 0;//현재 씬 들어갈 때 
	virtual void Exit() = 0; //현재 씬 나갈 떄

	void SetBackGround(CTexture* _pTex) { m_pBackgroundTex = _pTex; }
	CTexture* GetBackGround() { return m_pBackgroundTex; }

	void SetBackGroundInfo(const tBackGround _tInfo) { m_tBackgroundInfo = _tInfo; }
	const tBackGround& GetBackGroundInfo() {return m_tBackgroundInfo;}

	void SetStartDrawPoint(Vec2 _v) { m_vStartDrawPos = _v; }
	Vec2 GetStartDrawPoint() {return m_vStartDrawPos;}

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

	CObject* GetPlayerObj() 
	{
		return m_pPlayer; 
	}

	friend class CSceneMgr;
};

