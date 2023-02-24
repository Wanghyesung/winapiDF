#pragma once
#include "CAnimator.h"

struct tAnimFrm
{
    Vec2 vLt;
    Vec2 vSlice;//자를 사이즈
    Vec2 vOffset;//내 위치에서 얼마나 높일지
    float fDuration;
};

class CAnimation :
    public CAnimator
{
public:
    CAnimation();
    virtual ~CAnimation();

private:
    CAnimator*  m_pAnimator;
    wstring    m_strName;
    
    CTexture*  m_pTex;
    vector<tAnimFrm> m_vecFrm;

    int m_iCurFrm;
    float m_fAccTime;

    bool m_bFinish;

public:
    bool IsFinish() { return m_bFinish; }

    const wstring& GetName() { return m_strName; }

    tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
    int GetCurFrame() { return m_iCurFrm; }
    UINT GetMaxFrame() { return (UINT)m_vecFrm.size(); }

    void SetFram(int _iFrameIdx)
    {   
        m_bFinish = false;
        m_iCurFrm = _iFrameIdx;
        m_fAccTime = 0.f;
    }

    void SetFram(int _iFrameIdx,bool _bTimeInit)
    {
        if (_bTimeInit)
        {
            m_bFinish = false;
            m_iCurFrm = _iFrameIdx;
            m_fAccTime = 0.f;
        }
        else
        {
            m_bFinish = false;
            m_iCurFrm = _iFrameIdx;
        }
    }

private:
    void SetName(const wstring& _strName) { m_strName = _strName; }

    void AddAccTime(float _fAccTime) { m_fAccTime += _fAccTime; }

public:
    void update();
    void render(HDC _dc);

    //나중에 세이브랑 로드도 구현해야함

    void Save(const wstring& _strRelativePath);
    void Load(const wstring& _strRelativePath);

    void Create(CTexture* _pTex, Vec2 _vLt, Vec2 _vSliceSzie, Vec2 _vStep, Vec2 _vOffset, float _fDuration, UINT _iframeCount);

friend class CAnimator;
friend class CRandomFire;
};

