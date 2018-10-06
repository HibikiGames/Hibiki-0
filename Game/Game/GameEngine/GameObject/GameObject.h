#pragma once

namespace GameEngine
{
	class E_GameObject
	{
	public:
		E_GameObject();
		virtual ~E_GameObject();

		/*
			�X�V
		*/
		virtual void Update() = 0;

		/*
			�`��
		*/
		virtual void Render() = 0;

		/*
			�j��

			�쐬����j������O�ɕK���Ăяo���Ă�������
			(���������[�N�΍�)
		*/
		virtual void Release() = 0;

		/*
			���񂾁H
		*/
		bool IsDead()
		{
			return m_dead;
		}

		void DeleteReady()
		{
			m_dead = true;
		}

	private:
		bool			m_dead = false;
	};
}
