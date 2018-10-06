#include "../../include.h"

namespace GameEngine
{
	void E_Window::Create(const char* name, int width, int height)
	{
		//�E�B���h�E�N���X�̍쐬
		WNDCLASSEX windowClass = {
					sizeof(WNDCLASSEX),	//�\���̂̃������T�C�Y
					CS_CLASSDC,	//�E�C���h�E�N���X�̃X�^�C��
					E_Window::MessageProcedure,	//�E�B���h�E�v���V�[�W���̃A�h���X
					0L,	//�⏕�������B�ʏ�͎g��Ȃ��̂�0
					0L,	//�⏕�������B�ʏ�͎g��Ȃ��̂�0
					GetModuleHandle(NULL),	//�C���X�^���X�n���h��
					NULL,	//�g�p����A�C�R�����w��B�s�v�Ȃ�NULL
					LoadCursor(NULL,IDC_ARROW),	//�g�p����}�E�X�J�[�\�����w��B�s�v�Ȃ�NULL
					NULL,	//�E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�B�s�v�Ȃ�NULL
					NULL,	//�E�B���h�E�̃��j���[��ݒ�B�s�v�Ȃ�NULL
					"game",	//�E�B���h�E�N���X��
					NULL	//�g�p�A�C�R���̏��A�C�R���̏��B�s�v�Ȃ�NULL
		};

		//�Ǝ��̃A�C�R���̐ݒ�i�g��Ȃ���Ζ����Ă������j
		windowClass.hIcon = LoadIcon(GetModuleHandle(NULL), "ICON");

		//���W�X�^�[�ɓo�^
		RegisterClassEx(&windowClass);

		//��`���쐬
		SetRect(&m_rectangle, 0, 0, width, height);

		// ��`���ɂ��E�B���h�E��`���v�Z
		AdjustWindowRect(&m_rectangle, WS_OVERLAPPEDWINDOW, FALSE);

		//�E�B���h�E�̍쐬
		m_handle = CreateWindow(
			"game",	//�o�^����Ă���N���X��
			name,	//�E�B���h�E��
			WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
			0,	//�E�B���h�E�̉������̈ʒu
			0,	//�E�B���h�E�̏c�����̈ʒu
			m_rectangle.right - m_rectangle.left,	//�E�B���h�E�̕�
			m_rectangle.bottom - m_rectangle.top,	//�E�B���h�E�̍���
			GetDesktopWindow(),	//�e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
			NULL,	//���j���[�n���h���܂��͎q�E�B���h�EID
			windowClass.hInstance,	//�A�v���P�[�V�����C���X�^���X�̃n���h��
			NULL	//�E�B���h�E�쐬�f�[�^
		);

		//�E�B���h�E�̋�`���擾
		GetWindowRect(m_handle, &m_rectangle);

		//�\��
		Show();

		//�E�C���h�E�̍X�V
		UpdateWindow(m_handle);
	}

	void E_Window::Show() const
	{
		//�E�B���h�E�̕\��
		ShowWindow(m_handle, SW_SHOW);
	}

	HWND E_Window::GetHandle() const
	{
		return m_handle;
	}

	bool E_Window::MessageHandling()
	{
		//���b�Z�[�W�����邩�m�F
		if (PeekMessage(&m_message, NULL, 0, 0, PM_NOREMOVE))
		{
			//���b�Z�[�W�擾
			if (!GetMessage(&m_message, NULL, 0, 0))
			{
				return false;
			}

			//���b�Z�[�W�̓ǂݎ��
			TranslateMessage(&m_message);

			//���b�Z�[�W����
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

			//�`��

			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			//�I�����b�Z�[�W���M
			PostQuitMessage(0);

			return 0;
		}

		//�f�t�H���g�E�B���h�E�v���V�[�W������
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
