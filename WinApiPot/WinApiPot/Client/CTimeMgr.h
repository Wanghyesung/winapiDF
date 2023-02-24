#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr)


private:
	LARGE_INTEGER   m_llCurCount;
	LARGE_INTEGER   m_llPrevCount;
	LARGE_INTEGER   m_llFrequency;//초당 전체 카운트

	double			m_dDT;  //내 시간 동기화 값
	double			m_dAcc;  //누적 시간값
	UINT			m_iCallCount; //함수 호출 횟수
	UINT			m_iFPS; //1초당 호출된 횟수

public:
	void update();
	void render(HDC _dc);
	void init();


public:
	float GetfDT() { return (float)m_dDT; }
	double GetDT() { return m_dDT; }

};

