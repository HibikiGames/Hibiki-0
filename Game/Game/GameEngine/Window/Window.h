#pragma once

/*
	ウィンドウ生成をするクラス

	シングルトンになっている
*/

namespace GameEngine
{
	class E_Window
	{
	public:
		~E_Window() {};

		/*
			Windowインスタンスを取得
		*/
		static E_Window* GetInstance()
		{
			static E_Window ins;

			return &ins;
		}

		/*
			ウィンドウ生成
		*/
		void Create(const char* name, int width, int height);

		/*
			ウィンドウを表示
		*/
		void Show() const;

		/*
			ハンドルを取得
		*/
		HWND GetHandle() const;

		/*
			メッセージ処理

			trueで続行
		*/
		bool MessageHandling();

		/*
			メッセージプロシージャ

			コールバック関数
			ゲームの終了を監視
		*/
		static LRESULT WINAPI MessageProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		//シングルトンのためprivate
		E_Window() {};

		//ウィンドウハンドル
		HWND m_handle;

		//メッセージ
		MSG m_message;

		//矩形
		RECT m_rectangle;
	};
}
