#include "../../include.h"

namespace GameEngine
{
	E_GameManager::~E_GameManager()
	{
		E_DirectX11::GetInstance()->Release();
	}

	void GameEngine::E_GameManager::Run()
	{
		//�E�B���h�E����
		E_Window::GetInstance()->Create("�Q�[��", WIND_DPI_W, WIND_DPI_H);

		//�X���b�v�`�F�C���̐���
		if (!E_DirectX11::GetInstance()->Init())
		{
			return;
		}

		//�^�C�}�[
		E_Timer time;
		time.Start();

		while (E_Window::GetInstance()->MessageHandling())
		{
			//�w�i������
			E_DirectX11::GetInstance()->Clear();

			//�e�I�u�W�F�N�g�̍X�V&�`��
			for (int prio = 0; prio <= PRIO_MAX; prio++)
			{
				for (auto d : m_obj[prio])
				{
					//�Q�[���I�u�W�F�N�g�̍X�V
					if (d != nullptr)
					{
						d->Update();
					}

					//�Q�[���I�u�W�F�N�g�̉�ʕ`��
					if (d != nullptr)
					{
						d->Update();
					}
				}
			}

			//����Ȃ��Ȃ����I�u�W�F�N�g�̍폜
			DeleteObject();

			//��ʍX�V
			E_DirectX11::GetInstance()->Update();

			//FPS�l�ɒ���
			if (S_TO_MS(FPS_60) < time.GetTime())
			{
				time.Start();
			}
		}

		//�e��j��
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
		//�f�[�^�̕ύX�����������H
		bool isChanged = false;

		//�Q�[���I�u�W�F�N�g���X�g����폜
		for (int prio = 0; prio <= PRIO_MAX; prio++)
		{
			int new_size = 0;
			for (auto d : m_obj[prio])
			{
				if (d->IsDead())
				{
					//����
					d->Release();
					delete d;

					isChanged = true;
				}
				else
				{
					//����f�[�^�͎�O�Ɉړ����Ă���
					m_obj[prio][new_size] = d;
					new_size++;
				}
			}



			//�f�[�^�ɕύX���Ȃ���Έȉ��̏������΂�
			if (!isChanged) continue;

			//�T�C�Y���C��
			m_obj[prio].resize(new_size);

			//�Q�[�����s���̃��������[�N��h��
			//�X���b�v�Z�@�ɂ��Q�[���I�u�W�F�N�g���X�g�̗e�ʂ����炷
			vector<E_GameObject*>(m_obj[prio]).swap(m_obj[prio]);
		}
	}
}
