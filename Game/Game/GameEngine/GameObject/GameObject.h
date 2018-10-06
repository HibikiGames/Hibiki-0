#pragma once

namespace GameEngine
{
	class E_GameObject
	{
	public:
		E_GameObject();
		virtual ~E_GameObject();

		/*
			更新
		*/
		virtual void Update() = 0;

		/*
			描画
		*/
		virtual void Render() = 0;

		/*
			破棄

			作成元を破棄する前に必ず呼び出してください
			(メモリリーク対策)
		*/
		virtual void Release() = 0;

		/*
			死んだ？
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
