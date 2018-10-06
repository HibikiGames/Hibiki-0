#include "../../include.h"

namespace GameEngine
{
	E_GameManager::~E_GameManager()
	{
		E_DirectX11::GetInstance()->Release();
	}

	void GameEngine::E_GameManager::Run()
	{
		//ウィンドウ生成
		E_Window::GetInstance()->Create("ゲーム", WIND_DPI_W, WIND_DPI_H);

		//スワップチェインの生成
		if (!E_DirectX11::GetInstance()->Init())
		{
			return;
		}

		//タイマー
		E_Timer time;
		time.Start();

		while (E_Window::GetInstance()->MessageHandling())
		{
			//背景初期化
			E_DirectX11::GetInstance()->Clear();

			//各オブジェクトの更新&描画
			for (int prio = 0; prio <= PRIO_MAX; prio++)
			{
				for (auto d : m_obj[prio])
				{
					//ゲームオブジェクトの更新
					if (d != nullptr)
					{
						d->Update();
					}

					//ゲームオブジェクトの画面描画
					if (d != nullptr)
					{
						d->Update();
					}
				}
			}

			//いらなくなったオブジェクトの削除
			DeleteObject();

			//画面更新
			E_DirectX11::GetInstance()->Update();

			//FPS値に調整
			if (S_TO_MS(FPS_60) < time.GetTime())
			{
				time.Start();
			}
		}

		//各種破棄
		E_DirectX11::GetInstance()->Release();
		E_GameManager::Release();
	}

	void E_GameManager::Release()
	{
		for (int prio = 0; prio <= PRIO_MAX; prio++)
		{
			while (!m_obj[prio].empty())
			{
				delete m_obj[prio].back();
				m_obj[prio].pop_back();
			}
		}

	}
	void E_GameManager::DeleteObject()
	{
		//データの変更があったか？
		bool isChanged = false;

		//ゲームオブジェクトリストから削除
		for (int prio = 0; prio <= PRIO_MAX; prio++)
		{
			int new_size = 0;
			for (auto d : m_obj[prio])
			{
				if (d->IsDead())
				{
					//消す
					d->Release();
					delete d;

					isChanged = true;
				}
				else
				{
					//いるデータは手前に移動していく
					m_obj[prio][new_size] = d;
					new_size++;
				}
			}



			//データに変更がなければ以下の処理を飛ばす
			if (!isChanged) continue;

			//サイズを修正
			m_obj[prio].resize(new_size);

			//ゲーム実行中のメモリリークを防ぐ
			//スワップ技法によりゲームオブジェクトリストの容量を減らす
			vector<E_GameObject*>(m_obj[prio]).swap(m_obj[prio]);
		}
	}
}
