#include "../../include.h"

namespace GameEngine
{
	void E_Window::Create(const char* name, int width, int height)
	{
		//ウィンドウクラスの作成
		WNDCLASSEX windowClass = {
					sizeof(WNDCLASSEX),	//構造体のメモリサイズ
					CS_CLASSDC,	//ウインドウクラスのスタイル
					E_Window::MessageProcedure,	//ウィンドウプロシージャのアドレス
					0L,	//補助メモリ。通常は使わないので0
					0L,	//補助メモリ。通常は使わないので0
					GetModuleHandle(NULL),	//インスタンスハンドル
					NULL,	//使用するアイコンを指定。不要ならNULL
					LoadCursor(NULL,IDC_ARROW),	//使用するマウスカーソルを指定。不要ならNULL
					NULL,	//ウインドウのクライアント領域の背景色を設定。不要ならNULL
					NULL,	//ウィンドウのメニューを設定。不要ならNULL
					"game",	//ウィンドウクラス名
					NULL	//使用アイコンの小アイコンの情報。不要ならNULL
		};

		//独自のアイコンの設定（使わなければ無くてもいい）
		windowClass.hIcon = LoadIcon(GetModuleHandle(NULL), "ICON");

		//レジスターに登録
		RegisterClassEx(&windowClass);

		//矩形を作成
		SetRect(&m_rectangle, 0, 0, width, height);

		// 矩形情報によりウィンドウ矩形を計算
		AdjustWindowRect(&m_rectangle, WS_OVERLAPPEDWINDOW, FALSE);

		//ウィンドウの作成
		m_handle = CreateWindow(
			"game",	//登録されているクラス名
			name,	//ウィンドウ名
			WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル
			0,	//ウィンドウの横方向の位置
			0,	//ウィンドウの縦方向の位置
			m_rectangle.right - m_rectangle.left,	//ウィンドウの幅
			m_rectangle.bottom - m_rectangle.top,	//ウィンドウの高さ
			GetDesktopWindow(),	//親ウィンドウまたはオーナーウィンドウのハンドル
			NULL,	//メニューハンドルまたは子ウィンドウID
			windowClass.hInstance,	//アプリケーションインスタンスのハンドル
			NULL	//ウィンドウ作成データ
		);

		//ウィンドウの矩形を取得
		GetWindowRect(m_handle, &m_rectangle);

		//表示
		Show();

		//ウインドウの更新
		UpdateWindow(m_handle);
	}

	void E_Window::Show() const
	{
		//ウィンドウの表示
		ShowWindow(m_handle, SW_SHOW);
	}

	HWND E_Window::GetHandle() const
	{
		return m_handle;
	}

	bool E_Window::MessageHandling()
	{
		//メッセージがあるか確認
		if (PeekMessage(&m_message, NULL, 0, 0, PM_NOREMOVE))
		{
			//メッセージ取得
			if (!GetMessage(&m_message, NULL, 0, 0))
			{
				return false;
			}

			//メッセージの読み取り
			TranslateMessage(&m_message);

			//メッセージ処理
			DispatchMessage(&m_message);
		}

		return true;
	}

	LRESULT __stdcall E_Window::MessageProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		HDC         hdc;
		PAINTSTRUCT ps;

		switch (msg)
		{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			//描画

			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			//終了メッセージ送信
			PostQuitMessage(0);

			return 0;
		}

		//デフォルトウィンドウプロシージャ処理
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
