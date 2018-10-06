#include "../../include.h"

namespace GameEngine
{
	bool E_DirectX11::Init()
	{
		return
			CreateDeviceAndSwapChain() &&
			CreateRenderTargetView() &&
			CreateDepthStencil()
			;
	}

	bool E_DirectX11::CreateDeviceAndSwapChain()
	{
		// SwapChainの情報指定.
		DXGI_SWAP_CHAIN_DESC desc = {};

		// オフスクリーンはいくつだ？
		desc.BufferCount = 1;

		// ここから縦横解像度.
		desc.BufferDesc.Width = WIND_DPI_W;
		desc.BufferDesc.Height = WIND_DPI_H;

		// 描画先の形式
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// リフレッシュレート - Denomintorが分母.
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;

		// ここからMSAAの設定
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		// ウィンドウモードか？
		desc.Windowed = true;

		// ウィンドウハンドル
		desc.OutputWindow = E_Window::GetInstance()->GetHandle();

		// ここからは、特に指定しなくてもいい(0初期化状態のままでいい)と思われるもの.
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	// ストアアプリではDISCARDじゃなくSEQUENTIAL限定か？.
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// フルスクリーン、ウィンドウを切り替えた際に自動変更されるようになる･･･いらないか.
		// 他、desc.Flagsでは自動回転のオフやGDIの使用を可能にするなどの指定がある.

		// ここから機能レベル
		// とりあえずレベル高い順に記述しておく.
		D3D_FEATURE_LEVEL features[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};

		// 戻り値はHRESULTで戻ってくるので、FAILEDマクロに食わせれば成否が分かる･･･マクロか.
		if (FAILED(
			D3D11CreateDeviceAndSwapChain(
				nullptr,	// どのビデオアダプタを使用するか？既定ならばnullptrで、IDXGIAdapterのアドレスを渡す.
				D3D_DRIVER_TYPE_HARDWARE,	// ドライバのタイプを渡す。これ以外は基本的にソフトウェア実装で、どうしてもという時やデバグ用に用いるべし.
				nullptr,	// 上記をD3D_DRIVER_TYPE_SOFTWAREに設定した際に、その処理を行うDLLのハンドルを渡す。それ以外を指定している際には必ずnullptrを渡す.
				0,			// 何らかのフラグを指定する。詳しくはD3D11_CREATE_DEVICE列挙型で検索検索ぅ.
				nullptr,	// 実はここでD3D_FEATURE_LEVEL列挙型の配列を与える。nullptrにすることで上記featureと同等の内容の配列が使用される.
				0,			// 上記引数で、自分で定義した配列を与えていた場合、その配列の要素数をここに記述する.
				D3D11_SDK_VERSION,	// SDKのバージョン。必ずこの値.
				&desc,		// DXGI_SWAP_CHAIN_DESC構造体のアドレスを設定する。ここで設定した構造愛に設定されているパラメータでSwapChainが作成される.
				&m_swap_chain,	// 作成が成功した場合に、そのSwapChainのアドレスを格納するポインタ変数へのアドレス。ここで指定したポインタ変数経由でSwapChainを操作する.
				&m_device,	// 上記とほぼ同様で、こちらにはDeviceのポインタ変数のアドレスを設定する.
				nullptr,		// 実際に作成に成功したD3D_FEATURE_LEVELを格納するためのD3D_FEATURE_LEVEL列挙型変数のアドレスを設定する.
				&m_context	// SwapChainやDeviceと同様に、こちらにはContextのポインタ変数のアドレスを設定する.
			)
		)) {
			// 失敗した場合･･･どうしようもない。DirectX 11が使えないかDXGI_SWAP_CHAIN_DESCに不適切な値が入っている･･･.
			return false;
		}

		return true;
	}

	bool E_DirectX11::CreateRenderTargetView()
	{
		ID3D11Texture2D			*BackBuffer;

		// レンダリングターゲットを作成する
		if (FAILED(m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer)))
		{
			return false;
		}

		if (FAILED(m_device->CreateRenderTargetView(BackBuffer, NULL, &m_RenderTargetView)))
		{
			return false;
		}

		return true;
	}

	bool E_DirectX11::CreateDepthStencil()
	{
		//深度バッファテクスチャを作成
		D3D11_TEXTURE2D_DESC txDesc;
		ZeroMemory(&txDesc, sizeof(txDesc));
		txDesc.Width = WIND_DPI_W;
		txDesc.Height = WIND_DPI_H;
		txDesc.MipLevels = 1;
		txDesc.ArraySize = 1;
		txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		txDesc.SampleDesc.Count = 1;
		txDesc.SampleDesc.Quality = 0;
		txDesc.Usage = D3D11_USAGE_DEFAULT;
		txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		txDesc.CPUAccessFlags = 0;
		txDesc.MiscFlags = 0;
		if (FAILED(m_device->CreateTexture2D(&txDesc, NULL, &m_DepthStencilTexture)))
		{
			return false;
		}

		// 深度バッファターゲットを作成する
		D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
		ZeroMemory(&dsDesc, sizeof(dsDesc));
		dsDesc.Format = txDesc.Format;
		dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsDesc.Texture2D.MipSlice = 0;
		if (FAILED(m_device->CreateDepthStencilView(m_DepthStencilTexture, &dsDesc, &m_DepthStencilView)))
		{
			return false;
		}

		//ビューポート設定
		m_Viewport.TopLeftX = 0;
		m_Viewport.TopLeftY = 0;
		m_Viewport.Width = (FLOAT)WIND_DPI_W;
		m_Viewport.Height = (FLOAT)WIND_DPI_H;
		m_Viewport.MinDepth = 0.0f;
		m_Viewport.MaxDepth = 1.0f;

		return true;
	}

	void E_DirectX11::Release()
	{
		//各種破棄
		if (m_context)
		{
			m_context->ClearState();
		}

		SAFE_RELEASE(m_RenderTargetView);
		SAFE_RELEASE(m_DepthStencilView);
		SAFE_RELEASE(m_DepthStencilTexture);
		SAFE_RELEASE(m_swap_chain);
		SAFE_RELEASE(m_context);
		SAFE_RELEASE(m_device);
	}

	bool E_DirectX11::Clear()
	{
		if (m_device == nullptr)			return false;
		if (m_context == nullptr)			return false;
		if (m_swap_chain == nullptr)		return false;
		if (m_RenderTargetView == nullptr)	return false;

		m_context->ClearRenderTargetView(m_RenderTargetView, Colors::Blue);
		m_context->ClearDepthStencilView(m_DepthStencilView,
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		return true;
	}

	bool E_DirectX11::Update()
	{
		//画面更新
		m_swap_chain->Present(0, 0);

		return true;
	}
}
