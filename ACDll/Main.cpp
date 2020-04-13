#include <Windows.h>
#include <iostream>

int UIMain();

//DWORD WINAPI Main_Thread(LPVOID lpParam) {
//	UIMain();
//	return S_OK;
//}

BOOL WINAPI DllMain(HMODULE hModule, DWORD _reason, LPVOID lpReserved)
{
	if (_reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0x1000, (LPTHREAD_START_ROUTINE)UIMain, 0, 0, NULL);
	}
	return true;
}

int UIMain() {
	//AllocConsole();						//attaches console	
	//freopen("CONOUT$", "w", stdout);	//sets cout to be used with our newly created console
	//std::cout << "We Can Use Console For Debugging!\n";

	int* health = (int*)0x010EA5A8;	//creates a pointer that stores the address of pointer to local player

	

	//std::cout << *health;	//prints our health value
	return *health;
}