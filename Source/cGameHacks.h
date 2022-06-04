/*======================================================= RTA CODE TEAM =======================================================*/

#include <windows.h>
#include "cColor.h"
#include "cOptions.h"
#include "cClass.h"
#include "KeyPresent.h"
#include "cPatch.h"

#pragma once

//===============================================================================================================================
//															MODULE GAME
//===============================================================================================================================
DWORD GameProc = (DWORD)GetModuleHandleA("bio4.exe");
DWORD DINPUT = (DWORD)GetModuleHandleA("DINPUT8.dll");
//===============================================================================================================================
//															MODULE GAME
//===============================================================================================================================


//===============================================================================================================================
//													BASE ADDRESS BY RIZKIKOTET
//===============================================================================================================================
#define BaseMoney			(GameProc + 0x85BE88)
#define BasePoints			(GameProc + 0x86D84C)
#define BasePointsKill		(GameProc + 0x86D864)
#define BaseTimer			(GameProc + 0x84D818)

#define MainCordX			((*(DWORD*)(GameProc + 0x7FCB08) + 0x94))
#define MainCordY			((*(DWORD*)(GameProc + 0x7FCB08) + 0x9C))
#define MainCordZ			((*(DWORD*)(GameProc + 0x7FCB08) + 0x98))
#define Main2CordX			((*(DWORD*)(GameProc + 0x8537E0) + 0x94))
#define Main2CordY			((*(DWORD*)(GameProc + 0x8537E0) + 0x9C))
#define Main2CordZ			((*(DWORD*)(GameProc + 0x8537E0) + 0x98))

#define AddrInfiniteHP1		(GameProc + 0x1B5B34)
#define AddrInfiniteHP2		(GameProc + 0x1B5C53)
#define NoDamage1			((*(DWORD*)(GameProc + 0x7FCB08) + 0x32C))
#define NoDamage2			((*(DWORD*)(GameProc + 0x8537E0) + 0x32C))
#define AddrWallHack		(GameProc + 0x192D60)
#define AddrSpeedHack		((*(DWORD*)(GameProc +  0x7FCB08) + 0x298))

#define CurntWeapon			(GameProc + 0x86D764) 
#define AddrBypassPRL1		((*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(GameProc + 0x007FCB08) + 0x374) + 0x64) + 0x30) + 0x1BC) + 0x84) + 0x54) + 0x37C))
#define AddrBypassPRL2		((*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(GameProc + 0x007FCB08) + 0x374) + 0x64) + 0x30) + 0x1BC) + 0x84) + 0x54) + 0x374))
#define AddrAmmo			(GameProc + 0x3087C3)
#define AddrAmmoStack		(GameProc + 0x3059E1)
#define AddrBow				(GameProc + 0x308664)
#define AddrGrenade			(GameProc + 0x307EAA)
#define AddrRapidFire		((*(DWORD*)(GameProc + 0x7FCB08) + 0xFE))

#define AddrOneHit			(GameProc + 0x1B5D6E)
#define AddrFreezeEnemi		(GameProc + 0x29077)
//===============================================================================================================================
//													BASE ADDRESS BY RIZKIKOTET
//===============================================================================================================================



//===============================================================================================================================
//													PATCH MEMORY BY RIZKIKOTET
//===============================================================================================================================
cPatch InfiniteHp1		(AddrInfiniteHP1,		(BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
cPatch InfiniteHp2		(AddrInfiniteHP2,		(BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
cPatch WallHack			(AddrWallHack,			(BYTE*)"\xC3", 1);
cPatch InfiniteAmmo		(AddrAmmoStack,			(BYTE*)"\x90\x90\x90\x90", 4);
cPatch NoReload			(AddrAmmo,				(BYTE*)"\x90\x90\x90\x90", 4);
cPatch InfiniteGrenade	(AddrGrenade,			(BYTE*)"\x90\x90\x90\x90", 4);
cPatch InfiniteBow		(AddrBow,				(BYTE*)"\x90\x90\x90\x90", 4);
cPatch OneHit			(AddrOneHit,			(BYTE*)"\xC7\x86\x24\x03\x00\x00\x00\x00\x00\x00\x90\x90\x90\x90\x90", 15);
cPatch FreezeEnemi		(AddrFreezeEnemi,		(BYTE*)"\x90\x90", 2);
//===============================================================================================================================
//													PATCH MEMORY BY RIZKIKOTET
//===============================================================================================================================


bool GetStatus()
{
	DWORD Base = GameProc + 0xE3D718;
	unsigned long xBase = *(DWORD*)(Base);
	if (xBase > 0)
	{
		return true;
	}
	return false;
}


void SkupMe()
{

	
}

DWORD  RIZKIKOTETHACK() {
	while (1)
	{
		if (GetStatus())
		{


			if (opt_Money == 1)
			{
				int setMoney = 999999999;
				*(DWORD*)BaseMoney = setMoney;
			}

			if (opt_Time == 1)
			{
				FLOAT curTimer = 3600;
				*(FLOAT*)BaseTimer = curTimer;
			}

			if (opt_PointsHack == 1)
			{
				int setMoney = 999999999;
				*(DWORD*)BasePoints = setMoney;
			}

			if (opt_PointsKill == 1)
			{
				int setMoney = 999999999;
				*(DWORD*)BasePointsKill = setMoney;
			}
		}
		Sleep(10);
	}

	return 0;
}

void PlayerHack()
{
	if (GetStatus())
	{

		if (opt_InfiniteHealth == 1)
		{
			InfiniteHp1.Patch();
			InfiniteHp2.Patch();
		}
		else
		{
			InfiniteHp1.Restore();
			InfiniteHp2.Restore();
		}
	}
}
void _GodMode()
{
	int ONNoDamage = 32768;
	int OFFNoDamage = 0;

	if (GetStatus())
	{
		if (opt_Invincible == 1)
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)NoDamage1, &ONNoDamage, sizeof(ONNoDamage), NULL);
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)NoDamage2, &ONNoDamage, sizeof(ONNoDamage), NULL);
		}
		else
		{
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)NoDamage1, &OFFNoDamage, sizeof(OFFNoDamage), NULL);
			WriteProcessMemory(GetCurrentProcess(), (LPVOID)NoDamage2, &OFFNoDamage, sizeof(OFFNoDamage), NULL);

		}
	}
}
void _TeleportAshley()
{
	if (GetStatus())
	{
		if (opt_Teleport == 1)
		{

			if (GetAsyncKeyState(VK_HOME))
			{
				*(FLOAT*)Main2CordX = *(FLOAT*)MainCordX;
				*(FLOAT*)Main2CordY = *(FLOAT*)MainCordY;
				*(FLOAT*)Main2CordZ = *(FLOAT*)MainCordZ;
			}

		}
	}
}

void _Wallhack()
{
	if (GetStatus())
	{
		if (opt_WalkThroughWall == 1)
		{
			WallHack.Patch();
		}
		else
		{
			WallHack.Restore();
		}

		FLOAT ReadCoordZ = *(FLOAT*)MainCordZ;

		if (opt_SetUpDown == 1)
		{
			if (GetAsyncKeyState(0x49))
			{
				FLOAT SetUP = ReadCoordZ + 1000;
				*(FLOAT*)MainCordZ = SetUP;
			}

			if (GetAsyncKeyState(0x4B))
			{
				FLOAT SetDown = ReadCoordZ - 1000;
				*(FLOAT*)MainCordZ = SetDown;
			}
		}
	}
}


void _SpeedHack()
{
	if (GetStatus())
	{
		if (opt_SpeedHack == 2)
		{
			*(FLOAT*)AddrSpeedHack = 3;
		}

		if (opt_SpeedHack == 1)
		{
			*(FLOAT*)AddrSpeedHack = 2;
		}

		if (opt_SpeedHack == 0)
		{
			*(FLOAT*)AddrSpeedHack = 1;
		}
	}
}


void WeaponHack()
{
	if (GetStatus())
	{
		if (opt_InfiniteAmmo == 1)
		{
			InfiniteAmmo.Patch();
		}
		else
		{
			InfiniteAmmo.Restore();
		}

		if (opt_NoReload == 1)
		{
			NoReload.Patch();
		}
		else
		{
			NoReload.Restore();
		}

		if (opt_InfiniteLauncher == 1)
		{
			InfiniteGrenade.Patch();
		}
		else
		{
			InfiniteGrenade.Restore();
		}

		if (opt_InfiniteBow == 1)
		{
			InfiniteBow.Patch();
		}
		else
		{
			InfiniteBow.Restore();
		}
	}
}


void _PRLHack() {
	try
	{

		if (GetStatus())
		{
			if (opt_MaxPRL == 1)
			{
				if (*(DWORD*)CurntWeapon == 65)
				{
					FLOAT By1 = 20;
					FLOAT By2 = 45;
					*(FLOAT*)AddrBypassPRL1 = By1;
					*(FLOAT*)AddrBypassPRL2 = By2;
				}
			}
		}
	}
	catch (const std::exception&)
	{

	}

}

void _Fitur_RapidFire() {



	//=========================================//
	//             FITUR FIRESPEED             // 
	//=========================================//
	if (GetStatus())
	{
		if (opt_RapidFire == 1)
		{
			if (GetAsyncKeyState(VK_LBUTTON)) {
				__try
				{
					if (*(DWORD*)AddrRapidFire == 257)
					{
						*(DWORD*)AddrRapidFire = 257;
					}
					if (*(DWORD*)AddrRapidFire == 258)
					{
						*(DWORD*)AddrRapidFire = 257;
					}
				}
				__except (EXCEPTION_EXECUTE_HANDLER)
				{
					Sleep(50);
				}
			}
		}
	}
	Sleep(0 * 5);
}
void EnemieHack()
{

	if (GetStatus())
	{

		if (opt_OneHitKill == 1)
		{
			OneHit.Patch();
		}
		else
		{
			OneHit.Restore();
		}

		if (opt_FrezzeEnemie == 1)
		{
			FreezeEnemi.Patch();
		}
		else
		{
			FreezeEnemi.Restore();
		}
	}
}

/*======================================================= RTA CODE TEAM =======================================================*/