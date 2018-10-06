#include "../../include.h"

namespace GameEngine
{
	E_Timer::E_Timer()
	{
		QueryPerformanceFrequency(&m_freq);
	}

	void E_Timer::Start()
	{
		QueryPerformanceCounter(&m_start);
	}

	float E_Timer::GetTime()
	{
		LARGE_INTEGER	now;

		QueryPerformanceCounter(&now);

		return S_TO_MS(((float)now.QuadPart - (float)m_start.QuadPart) / (float)m_freq.QuadPart);
	}
}
