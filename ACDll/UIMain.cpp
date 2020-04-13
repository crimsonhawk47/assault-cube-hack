#include <Windows.h>
#include <iostream>
#include "ghFunctions.h"
#include "AOB.h"
#include <ctime>

void mainHack();
DWORD_PTR baseAddress = 0x51E20C;


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);		//disables attach and detach notifications
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mainHack, NULL, NULL, NULL);	//creates a new thread and starts at function mainHack()
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



char toWrite[] = "\x90\x90";
char aobSignature[] = "\x0C\x0F\xBF\x88\x0A\x01\x00\x00\x8B\x56\x18\x89\x0A\x8b\x76\x14\xFF\x0E\x57\x8B\x7C\x24\x14\x8D\x74\x24\x28";//27 members plus null
char mask[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxx";
char gameName[] = "ac_client.exe";




void mainHack()
{
	AllocConsole();						
	freopen("CONOUT$", "w", stdout);	
	std::cout << "We Can Use Console For Debugging!\n";


	gameBase * x = (gameBase*)0x51E20C;
	//x->oPlayer->health = 9999;
	
	while (!(x->oPlayer))
		Sleep(120);

	if (!(x->oPlayer->oCurrentWeapon))
	std::cout << "There is no Current Weapon. Fire your weapon" << std::endl;
	while (!(x->oPlayer->oCurrentWeapon)&&(x->oPlayer)) {
		Sleep(120);
	}
	std::cout << "Weapon Was Found" << std::endl;
	if (x->oPlayer->oCurrentWeapon)
	{
		//x->oPlayer->oCurrentWeapon->oAmmoStruct->currentWeaponAmmo = 3000;
		//x->oPlayer->oCurrentWeapon->oWeaponStats->reloadTime = 300;
		//x->oPlayer->oCurrentWeapon->oWeaponStats->fireSpeed = 50;
		//x->oPlayer->oCurrentWeapon->oWeaponStats->recoil1 = 0;
		//x->oPlayer->oCurrentWeapon->oWeaponStats->recoil2 = 0;
		//x->oPlayer->oCurrentWeapon->oWeaponStats->kickback = 0;
		std::cout << "It Worked" << std::endl;
		MODULEINFO modInfo = GetModInfo((char*)"ac_client.exe");
		std::cout << "Address of modInfo.lpBaseOfDll   " << modInfo.lpBaseOfDll << std::endl;
		std::cout << "Address of modInfo.SizeOfImage   " << modInfo.SizeOfImage << std::endl;
		std::cout << "Address of modInfo.EntryPoint    " << modInfo.EntryPoint << std::endl;

		

		while (!GetAsyncKeyState(VK_INSERT)) {
			if (GetAsyncKeyState(VK_F1)) {
				PatchAob(gameName, aobSignature, mask, toWrite, 2, 16);
				Sleep(120);
				
			}
			if (GetAsyncKeyState(VK_F2)) {
				PatchAob(gameName, aobSignature, mask, toWrite, 2, 16);
				Sleep(120);

			}
			Sleep(60);
		}
	}


}

