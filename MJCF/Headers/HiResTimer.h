#include <intrin.h>

#ifndef MJCF_HIRESTIMER
#define MJCF_HIRESTIMER

class HiResTimer
{
public:
	HiResTimer() : m_qwStart(0), m_qwStop(0) {
		if( QueryPerformanceFrequency((LARGE_INTEGER*)&m_qwFreq) == FALSE )
			__debugbreak();
	}

	~HiResTimer() {}

	void Start(void) {
		QueryPerformanceCounter((LARGE_INTEGER*)&m_qwStart);
	}

	void Stop(void) {
		QueryPerformanceCounter((LARGE_INTEGER*)&m_qwStop);
	}

	void Reset(void) {
		m_qwStart = m_qwStop = 0;
	}

	float GetTime(void) const {
		if(m_qwFreq)
			return (float)((m_qwStop - m_qwStart) / (float)m_qwFreq);
		else
			return 0;
	}

protected:
	__int64 m_qwStart, m_qwStop, m_qwFreq;
};

#endif