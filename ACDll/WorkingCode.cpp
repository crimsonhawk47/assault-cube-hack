#include <windows.h>
#include <iostream>
void mainHack();

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);		//disables attach and detach notifications
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mainHack, NULL, NULL, NULL);	//creates a new thread and starts at function mainHack()
	}
	else if (dwReason == DLL_PROCESS_DETACH) {

	}
	return TRUE;
}

void mainHack()
{
	AllocConsole();						//attaches console	
	freopen("CONOUT$", "w", stdout);	//sets cout to be used with our newly created console
	std::cout << "We Can Use Console For Debugging!\n";

	DWORD* health = (DWORD*)((*(DWORD*)(0x51E20C)) + 0xF8);	//creates a pointer that stores the address of pointer to local player
	//int* health = (int*)(*localPlayer + 0xF8);	//creates a pointer to health

	std::cout << *health << std::endl;	//prints our health value
	*(int*)health = 200;

	std::cout << *health << std::endl;
}