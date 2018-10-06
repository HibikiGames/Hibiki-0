#pragma once

/*
	�E�B���h�E����������N���X

	�V���O���g���ɂȂ��Ă���
*/

namespace GameEngine
{
	class E_Window
	{
	public:
		~E_Window() {};

		/*
			Window�C���X�^���X���擾
		*/
		static E_Window* GetInstance()
		{
			static E_Window ins;

			return &ins;
		}

		/*
			�E�B���h�E����
		*/
		void Create(const char* name, int width, int height);

		/*
			�E�B���h�E��\��
		*/
		void Show() const;

		/*
			�n���h�����擾
		*/
		HWND GetHandle() const;

		/*
			���b�Z�[�W����

			true�ő��s
		*/
		bool MessageHandling();

		/*
			���b�Z�[�W�v���V�[�W��

			�R�[���o�b�N�֐�
			�Q�[���̏I�����Ď�
		*/
		static LRESULT WINAPI MessageProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		//�V���O���g���̂���private
		E_Window() {};

		//�E�B���h�E�n���h��
		HWND m_handle;

		//���b�Z�[�W
		MSG m_message;

		//��`
		RECT m_rectangle;
	};
}
