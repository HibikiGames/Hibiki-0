#pragma once

namespace GameEngine
{
	class E_Timer
	{
	public:
		E_Timer();
		~E_Timer() {};

		/*
			���Ԍv���X�^�[�g
		*/
		void Start();

		/*
			Start����̌o�ߎ��Ԏ擾
			�P�ʂ�ms
		*/
		float GetTime();

	private:
		LARGE_INTEGER	m_freq;

		LARGE_INTEGER	m_start;
	};
}
