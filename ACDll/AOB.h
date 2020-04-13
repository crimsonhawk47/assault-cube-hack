#pragma once
#include <Windows.h>
#include <iostream>
#include <Psapi.h>
#include <TlHelp32.h>


MODULEINFO GetModInfo(char* ProcessName) {
	HMODULE modHandle = GetModuleHandle((LPCSTR)ProcessName); //Gets a handle to the Process Name
	MODULEINFO modInfo = { 0 }; /*Creates a ModInfo structure used in GetModuleInformation. This will have the starting address of the module
								and the size of the module, which we need for an Aobscan*/
	GetModuleInformation(GetCurrentProcess(), modHandle, &modInfo, sizeof(MODULEINFO)); /*Since Our DLL is loaded in the process, we can
																						just get the current process and get the current
																						process, get the modulehandle we made, and store
																						the mod info in a buffer (modInf)*/
	return modInfo;
}



DWORD_PTR AobScan(char * gameName, char * aobSig, char* mask)
{
	MODULEINFO modInfo = GetModInfo(gameName); //Calling our custom GetModInfo func
	DWORD_PTR gameBase = (DWORD_PTR)modInfo.lpBaseOfDll; //Gets the base address of the module (like where the exe starts)
	DWORD gameSize = (DWORD)modInfo.SizeOfImage; //Gets the size of the module

	bool x = true;
	bool gotit = false;
	DWORD j = 0;

	while (!gotit) {
		if (j >= (gameSize - (DWORD)strlen(mask))) /*"If the offset j is bigger than the maximum gamesize that can
												   include the full mask signature. We also use the mask for strlen and 
												   not aobSig because aobSig may contain a hex value of \x00, and strlen
												   skips 0's. So we use the mask instead. */
		{
			std::cout << "Searched Entire Process" << std::endl;
			break; /*Since j is our offset from the modules base, we don't want it so big 
				   that the rest of the module won't even fit the signature*/
		}
		for (DWORD i = 0; i < (DWORD)strlen(mask); i++) /*"For i less than the mask, which should be the same
														char size as the AOB we are scanning for*/
		{
			x = true;
			x &= aobSig[i] == (((char*)gameBase) + j)[i] || mask[i] == '0'; /*x remains true as long as the aobSig we are
																			scanning for matches the gamebase sig we are scanning, 
																			OR if we indicated 0 on the mask instead of x. This means
																			we can write 0's into the mask for bytes that may change or
																			be different on program relaunch*/
			if (!x) { //If x is false, because one of the conditions above was false, increase the offset by 1 and try again
				j++;
				break;
			}

		}
		if (x) {
			gotit = true; //gotit will be our boolean for success
		}
	}
	if (gotit) return (DWORD_PTR)(((char*)gameBase) + j); //Return the offset we need to scan from. 
	else return NULL; //The function will return NULL if it failed. 

}


DWORD PatchAob(char* process, char * aobSig, char * mask, char* toWrite, int toWriteBytes, int functionBaseOffset) { //NEED TO FIX THIS, strlen(ToWrite) will not work if ToWrite has \x00
	DWORD prot1 = NULL; //Our buffer for VirtualProtect, a function that doesn't work without a buffer. 
	DWORD_PTR address = (DWORD_PTR)((char*)(AobScan(process, aobSig, mask)) + functionBaseOffset); /*Calling our AobScan func, and
																								   adding an offset in case the
																								   thing we actually want to modify
																								   is ahead or behind of
																								   the signature we found. If 
																								   functionBaseOffset was +2, we would
																								   be modifying our signature 2 bytes
																								   over. */
	if (!(address - functionBaseOffset)) //In case the address we found was null (because AobScan failed).
	{
		std::cout << "Address Found Was 0 " << std::endl;
		return 0;
	}
	std::cout << std::hex << "PatchAob's Aobscan found the address " << address << std::endl << std::dec;
	if (VirtualProtect((char*)address, toWriteBytes, PAGE_EXECUTE_READWRITE, &prot1)) { /*toWriteBytes = the number of
																						bytes we need to write. Virtual protect
																						is allowing us to write in the address space*/
		for (int i = 0; i < toWriteBytes; i++) {
			((char *)address)[i] = toWrite[i];
			std::cout << std::hex << "dec value at address " << (DWORD_PTR)((char*)address + i) << " Is now " << +(BYTE)((char*)address)[i] << std::endl << std::dec;


		}
	}
	else std::cout << "VirtualProtect Failed" << std::endl;

	return prot1;
}



