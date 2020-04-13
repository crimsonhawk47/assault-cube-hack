#pragma once


class cWeaponStats {
public:
	char reloadTimeOffsets[0x108]; //0x00
	INT16 reloadTime; //0x108
	INT16 fireSpeed; //0x10A
	char kickbackOffset[0xa]; //0x10C
	INT16 kickback; //0x116
	char recoilOffset[0x8]; //0x118
	INT16 recoil1; //120
	INT16 recoil2; //122
	char autoBoolOffset[0x4]; //124
	INT16 autoBool; //128
};

class cAmmoStruct {
public:
	int currentWeaponAmmo; //0x00
};

class cCurrentWeapon {
public:
	char weaponStatsOffset[0xC]; //0x00
	cWeaponStats * oWeaponStats; //0xC
	char ammoStructOffset[0x4]; //0x10
	cAmmoStruct * oAmmoStruct; //0x14
};

class cPlayer {
public:
	char healthoffset[0xf8]; //0x00
	int health; //0xF8
	char currentWeaponOffset[0x288]; //0xFC
	cCurrentWeapon * oCurrentWeapon; //0x384
};

class gameBase {
public:
	cPlayer* oPlayer; //0x00

};

