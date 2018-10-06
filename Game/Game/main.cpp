#include "include.h"

#include "User/Player/Player.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	//ƒ^ƒCƒgƒ‹‚Ö‚Ì‘JˆÚ‚ð“o˜^


	E_GameManager::GetInstance()->Run();

	UnregisterClass(nullptr, GetModuleHandleA(nullptr));

	return 0;
}
