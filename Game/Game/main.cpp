#include "include.h"

#include "User/Player/Player.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	//�^�C�g���ւ̑J�ڂ�o�^


	E_GameManager::GetInstance()->Run();

	UnregisterClass(nullptr, GetModuleHandleA(nullptr));

	return 0;
}
