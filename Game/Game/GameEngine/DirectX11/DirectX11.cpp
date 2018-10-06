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
		// SwapChain�̏��w��.
		DXGI_SWAP_CHAIN_DESC desc = {};

		// �I�t�X�N���[���͂������H
		desc.BufferCount = 1;

		// ��������c���𑜓x.
		desc.BufferDesc.Width = WIND_DPI_W;
		desc.BufferDesc.Height = WIND_DPI_H;

		// �`���̌`��
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// ���t���b�V�����[�g - Denomintor������.
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;

		// ��������MSAA�̐ݒ�
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		// �E�B���h�E���[�h���H
		desc.Windowed = true;

		// �E�B���h�E�n���h��
		desc.OutputWindow = E_Window::GetInstance()->GetHandle();

		// ��������́A���Ɏw�肵�Ȃ��Ă�����(0��������Ԃ̂܂܂ł���)�Ǝv�������.
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	// �X�g�A�A�v���ł�DISCARD����Ȃ�SEQUENTIAL���肩�H.
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// �t���X�N���[���A�E�B���h�E��؂�ւ����ۂɎ����ύX�����悤�ɂȂ饥�����Ȃ���.
		// ���Adesc.Flags�ł͎�����]�̃I�t��GDI�̎g�p���\�ɂ���Ȃǂ̎w�肪����.

		// ��������@�\���x��
		// �Ƃ肠�������x���������ɋL�q���Ă���.
		D3D_FEATURE_LEVEL features[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};

		// �߂�l��HRESULT�Ŗ߂��Ă���̂ŁAFAILED�}�N���ɐH�킹��ΐ��ۂ������饥��}�N����.
		if (FAILED(
			D3D11CreateDeviceAndSwapChain(
				nullptr,	// �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr�ŁAIDXGIAdapter�̃A�h���X��n��.
				D3D_DRIVER_TYPE_HARDWARE,	// �h���C�o�̃^�C�v��n���B����ȊO�͊�{�I�Ƀ\�t�g�E�F�A�����ŁA�ǂ����Ă��Ƃ�������f�o�O�p�ɗp����ׂ�.
				nullptr,	// ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵���ۂɁA���̏������s��DLL�̃n���h����n���B����ȊO���w�肵�Ă���ۂɂ͕K��nullptr��n��.
				0,			// ���炩�̃t���O���w�肷��B�ڂ�����D3D11_CREATE_DEVICE�񋓌^�Ō���������.
				nullptr,	// ���͂�����D3D_FEATURE_LEVEL�񋓌^�̔z���^����Bnullptr�ɂ��邱�Ƃŏ�Lfeature�Ɠ����̓��e�̔z�񂪎g�p�����.
				0,			// ��L�����ŁA�����Œ�`�����z���^���Ă����ꍇ�A���̔z��̗v�f���������ɋL�q����.
				D3D11_SDK_VERSION,	// SDK�̃o�[�W�����B�K�����̒l.
				&desc,		// DXGI_SWAP_CHAIN_DESC�\���̂̃A�h���X��ݒ肷��B�����Őݒ肵���\�����ɐݒ肳��Ă���p�����[�^��SwapChain���쐬�����.
				&m_swap_chain,	// �쐬�����������ꍇ�ɁA����SwapChain�̃A�h���X���i�[����|�C���^�ϐ��ւ̃A�h���X�B�����Ŏw�肵���|�C���^�ϐ��o�R��SwapChain�𑀍삷��.
				&m_device,	// ��L�Ƃقړ��l�ŁA������ɂ�Device�̃|�C���^�ϐ��̃A�h���X��ݒ肷��.
				nullptr,		// ���ۂɍ쐬�ɐ�������D3D_FEATURE_LEVEL���i�[���邽�߂�D3D_FEATURE_LEVEL�񋓌^�ϐ��̃A�h���X��ݒ肷��.
				&m_context	// SwapChain��Device�Ɠ��l�ɁA������ɂ�Context�̃|�C���^�ϐ��̃A�h���X��ݒ肷��.
			)
		)) {
			// ���s�����ꍇ����ǂ����悤���Ȃ��BDirectX 11���g���Ȃ���DXGI_SWAP_CHAIN_DESC�ɕs�K�؂Ȓl�������Ă��饥�.
			return false;
		}

		return true;
	}

	bool E_DirectX11::CreateRenderTargetView()
	{
		ID3D11Texture2D			*BackBuffer;

		// �����_�����O�^�[�Q�b�g���쐬����
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
		//�[�x�o�b�t�@�e�N�X�`�����쐬
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

		// �[�x�o�b�t�@�^�[�Q�b�g���쐬����
		D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
		ZeroMemory(&dsDesc, sizeof(dsDesc));
		dsDesc.Format = txDesc.Format;
		dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsDesc.Texture2D.MipSlice = 0;
		if (FAILED(m_device->CreateDepthStencilView(m_DepthStencilTexture, &dsDesc, &m_DepthStencilView)))
		{
			return false;
		}

		//�r���[�|�[�g�ݒ�
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
		//�e��j��
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
		//��ʍX�V
		m_swap_chain->Present(0, 0);

		return true;
	}
}
