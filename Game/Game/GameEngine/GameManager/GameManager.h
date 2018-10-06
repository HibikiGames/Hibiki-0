#pragma once

#include "../GameObject/GameObject.h"

constexpr auto PRIO_MAX = 32;

namespace GameEngine
{
	class E_GameManager
	{
	public:
		~E_GameManager();

		/*
			インスタンス取得
		*/
		static E_GameManager* GetInstance()
		{
			static E_GameManager ins;

			return &ins;
		}

		/*
			このクラスでゲーム開始から終了まで実行
		*/
		void Run();

		/*
			オブジェクトリストに新規追加

			priority...更新＆描画優先度(大きいほど遅い)
		*/
		template<class T>
		T* NewGo(int prio)
		{
			T* new_obj = new T;

			m_obj[prio].push_back(new_obj);

			return new_obj;
		}

		/*
			オブジェクトリストから削除(準備)

			毎フレームの最後でDeleteObjectによって消される
		*/
		template<class T>
		void DeleteGo(T* ins)
		{
			ins->DeleteReady();
		}

		/*
			破棄

			作成元を破棄する前に必ず呼び出してください
			(メモリリーク対策)
		*/
		void Release();

	private:
		E_GameManager() {};

		/*
			ゲームオブジェクトを実際に消すのはここ
		*/
		void DeleteObject();

		std::vector<E_GameObject*>				m_obj[PRIO_MAX + 1];
	};

}