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
	virtual ~CScene();//���������� ����

private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; //�� ������Ʈ Ŭ�������� �ٷ�� ��
	CObject*		 m_pPlayer; //�� �÷��̾�

	wstring			m_strName; //���� �̸�

	CTexture*		m_pBackgroundTex;
	Vec2			m_vStartDrawPos; //�׸� �̹����� ������
	tBackGround     m_tBackgroundInfo;

public:
	virtual void render(HDC _dc);
	virtual void update();//���⼭ ������Ʈ �ϰ� ������ ������Ʈ���� update, finalupdate
	virtual void finalupdate();

	//����� �׸���
	void backgroundrender(HDC _dc, CTexture* _pTex, Vec2 _vStartPos);

	void RegisterPlayer(CObject* _pObj);

	virtual void Enter() = 0;//���� �� �� �� 
	virtual void Exit() = 0; //���� �� ���� ��

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
	void AddObject(CObject* _pObj , GROUP_TYPE _eType)//�׷� ������Ʈ �ֱ�
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);//�� �� ������Ʈ �迭 �ȿ� �־��ֱ�
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) {return m_arrObj[(UINT)_eType];}

	CObject* GetPlayerObj() 
	{
		return m_pPlayer; 
	}

	friend class CSceneMgr;
};

