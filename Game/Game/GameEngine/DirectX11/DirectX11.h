#pragma once

/*
	DirectX11に使用する関数
*/

namespace GameEngine
{
	class E_DirectX11
	{
	public:
		~E_DirectX11() {};

		/*
			破棄

			作成元を破棄する前に必ず呼び出してください
			(メモリリーク対策)
		*/
		void Release();

		static E_DirectX11* GetInstance()
		{
			static E_DirectX11 ins;

			return &ins;
		}

		/*
			初期化

			falseで失敗
		*/
		bool Init();

		/*
			画面の背景クリア
		*/
		bool Clear();

		/*
			画面の更新
		*/
		bool Update();

		/*
			デバイスの取得
		*/
		ID3D11Device* GetDevice()
		{
			return m_device;
		}

		/*
			コンテキスト取得
		*/
		ID3D11DeviceContext* GetContext()
		{
			return m_context;
		}

		/*
			ビューポート取得
		*/
		D3D11_VIEWPORT* GetViewPort()
		{
			return &m_Viewport;
		}

		/*
			レンダーターゲットビューを取得
		*/
		ID3D11RenderTargetView* GetTargetView()
		{
			return m_RenderTargetView;
		}

		ID3D11DepthStencilView* GetDS_View()
		{
			return m_DepthStencilView;
		}

	private:
		/*
			Init群
		*/

		/*
			デバイスとスワップチェインの作成

			trueで成功
		*/
		bool CreateDeviceAndSwapChain();

		/*
			レンダーターゲットビューの作成

			trueで成功
		*/
		bool CreateRenderTargetView();

		/*
			深度/ステンシルバッファの作成

			trueで成功
		*/
		bool CreateDepthStencil();


	private:
		E_DirectX11() {};

		ID3D11Device			*m_device = nullptr;
		ID3D11DeviceContext		*m_context = nullptr;
		IDXGISwapChain			*m_swap_chain = nullptr;				//スワップチェイン
		ID3D11RenderTargetView	*m_RenderTargetView = nullptr;
		ID3D11Texture2D			*m_DepthStencilTexture = nullptr;
		ID3D11DepthStencilView	*m_DepthStencilView = nullptr;
		D3D11_VIEWPORT			m_Viewport;								//ビューポート

		XMVECTOR				m_Eye;									//カメラ座標
		XMVECTOR				m_At;									//注視点
		XMVECTOR				m_Up;									//上方向
	};
}
