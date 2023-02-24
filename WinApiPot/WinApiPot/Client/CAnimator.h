#pragma once

class CObject;
class CAnimation;
class CTexture;
class CSkillState;

class CAnimator
{


public:
	CAnimator();
	~CAnimator();
private:
	map<wstring, CAnimation*> m_mapAnim;//내 애니메이션 넣는곳
	CAnimation* m_pCurAnim; //현재 애니메이션
	CAnimation* m_pOtherAnim;//다른 애니메이션

	CObject*	m_pOwner;
	bool		 m_bRepeat;
	
	int r, g, b;

public:
	void		CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLt, Vec2 _vSliceSzie, Vec2 _vStep, Vec2 _vOffset, float _fDuration, UINT _iframeCount);
	void		LoadAnimation(const wstring& _strRelativePath);

	void Play(const wstring& _strName, bool _bRepeat);
	void Play(const wstring& _strName, bool _bRepeat, CSkillState* _pCurSkill);
	void PlayMulti(const wstring& _strMainName, const wstring& _strOtherName, bool _bRepeat);
	

	CAnimation* FindAnimation(const wstring& _strName);

	CAnimation* GetCurAnimation() { return m_pCurAnim; }
	CAnimation* GetOtherAnimation() { return m_pOtherAnim; }

public:
	CObject* GetObj() { return m_pOwner; }

	void SetRBG(int _r, int _g, int _b);

public:
	void finalupdate();
	void render(HDC _dc);

	friend class CObject;
	friend class CAnimation;
};

