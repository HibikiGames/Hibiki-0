#pragma once

namespace GameEngine
{
	class E_Timer
	{
	public:
		E_Timer();
		~E_Timer() {};

		/*
			時間計測スタート
		*/
		void Start();

		/*
			Startからの経過時間取得
			単位はms
		*/
		float GetTime();

	private:
		LARGE_INTEGER	m_freq;

		LARGE_INTEGER	m_start;
	};
}
