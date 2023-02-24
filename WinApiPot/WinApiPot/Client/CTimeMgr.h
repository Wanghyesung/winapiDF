#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr)


private:
	LARGE_INTEGER   m_llCurCount;
	LARGE_INTEGER   m_llPrevCount;
	LARGE_INTEGER   m_llFrequency;//�ʴ� ��ü ī��Ʈ

	double			m_dDT;  //�� �ð� ����ȭ ��
	double			m_dAcc;  //���� �ð���
	UINT			m_iCallCount; //�Լ� ȣ�� Ƚ��
	UINT			m_iFPS; //1�ʴ� ȣ��� Ƚ��

public:
	void update();
	void render(HDC _dc);
	void init();


public:
	float GetfDT() { return (float)m_dDT; }
	double GetDT() { return m_dDT; }

};

