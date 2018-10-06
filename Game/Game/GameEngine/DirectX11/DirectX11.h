#pragma once

/*
	DirectX11�Ɏg�p����֐�
*/

namespace GameEngine
{
	class E_DirectX11
	{
	public:
		~E_DirectX11() {};

		/*
			�j��

			�쐬����j������O�ɕK���Ăяo���Ă�������
			(���������[�N�΍�)
		*/
		void Release();

		static E_DirectX11* GetInstance()
		{
			static E_DirectX11 ins;

			return &ins;
		}

		/*
			������

			false�Ŏ��s
		*/
		bool Init();

		/*
			��ʂ̔w�i�N���A
		*/
		bool Clear();

		/*
			��ʂ̍X�V
		*/
		bool Update();

		/*
			�f�o�C�X�̎擾
		*/
		ID3D11Device* GetDevice()
		{
			return m_device;
		}

		/*
			�R���e�L�X�g�擾
		*/
		ID3D11DeviceContext* GetContext()
		{
			return m_context;
		}

		/*
			�r���[�|�[�g�擾
		*/
		D3D11_VIEWPORT* GetViewPort()
		{
			return &m_Viewport;
		}

		/*
			�����_�[�^�[�Q�b�g�r���[���擾
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
			Init�Q
		*/

		/*
			�f�o�C�X�ƃX���b�v�`�F�C���̍쐬

			true�Ő���
		*/
		bool CreateDeviceAndSwapChain();

		/*
			�����_�[�^�[�Q�b�g�r���[�̍쐬

			true�Ő���
		*/
		bool CreateRenderTargetView();

		/*
			�[�x/�X�e���V���o�b�t�@�̍쐬

			true�Ő���
		*/
		bool CreateDepthStencil();


	private:
		E_DirectX11() {};

		ID3D11Device			*m_device = nullptr;
		ID3D11DeviceContext		*m_context = nullptr;
		IDXGISwapChain			*m_swap_chain = nullptr;				//�X���b�v�`�F�C��
		ID3D11RenderTargetView	*m_RenderTargetView = nullptr;
		ID3D11Texture2D			*m_DepthStencilTexture = nullptr;
		ID3D11DepthStencilView	*m_DepthStencilView = nullptr;
		D3D11_VIEWPORT			m_Viewport;								//�r���[�|�[�g

		XMVECTOR				m_Eye;									//�J�������W
		XMVECTOR				m_At;									//�����_
		XMVECTOR				m_Up;									//�����
	};
}
