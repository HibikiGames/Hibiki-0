#pragma once

#include "../GameObject/GameObject.h"

constexpr auto PRIO_MAX = 32;

namespace GameEngine
{
	class E_GameManager
	{
	public:
		~E_GameManager();

		/*
			�C���X�^���X�擾
		*/
		static E_GameManager* GetInstance()
		{
			static E_GameManager ins;

			return &ins;
		}

		/*
			���̃N���X�ŃQ�[���J�n����I���܂Ŏ��s
		*/
		void Run();

		/*
			�I�u�W�F�N�g���X�g�ɐV�K�ǉ�

			priority...�X�V���`��D��x(�傫���قǒx��)
		*/
		template<class T>
		T* NewGo(int prio)
		{
			T* new_obj = new T;

			m_obj[prio].push_back(new_obj);

			return new_obj;
		}

		/*
			�I�u�W�F�N�g���X�g����폜(����)

			���t���[���̍Ō��DeleteObject�ɂ���ď������
		*/
		template<class T>
		void DeleteGo(T* ins)
		{
			ins->DeleteReady();
		}

		/*
			�j��

			�쐬����j������O�ɕK���Ăяo���Ă�������
			(���������[�N�΍�)
		*/
		void Release();

	private:
		E_GameManager() {};

		/*
			�Q�[���I�u�W�F�N�g�����ۂɏ����̂͂���
		*/
		void DeleteObject();

		std::vector<E_GameObject*>				m_obj[PRIO_MAX + 1];
	};

}