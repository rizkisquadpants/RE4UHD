#include "hack.h"
#include <chrono>
#include <future>
#include <random>
#include <type_traits>
#include <cstdint>
#include <regex>
#include <filesystem>
#include <charconv>
#include <Windows.h>
//#include <winsqlite/winsqlite3.h>
#include <d3dx9.h>
#include <tlhelp32.h>
#ifndef NDEBUG
#include <iostream>
#endif


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
#define BaseHealth			(GameProc + 0x805F3C)
#define BaseAddrRotation	(GameProc + 0x7FCB08)

#define BaseMoney			(GameProc + 0x85BE88)
#define BasePoints			(GameProc + 0x86D84C)
#define BasePointsKill		(GameProc + 0x86D864)
#define BaseTimer			(GameProc + 0x84D818)
#define BaseGreenHerb		(GameProc + 0x3064BD)
#define BaseRedHerb			(GameProc + 0x308287)
#define BaseYelowHerb		(GameProc + 0x30828D)
#define BaseHerbGRY			(GameProc + 0x3064A1)

#define BaseDifficulty			((*(DWORD*)(BaseHealth) + 0x847C))
#define BaseAshleyPresent		((*(DWORD*)(BaseHealth) + 0x5028))
#define BaseCostume				((*(DWORD*)(BaseHealth) + 0x4FC9))
#define BaseCharacter			((*(DWORD*)(BaseHealth) + 0x4FC8))
#define BaseStatus				((*(DWORD*)(BaseHealth) + 0x20))

#define BaseScaneX				((*(DWORD*)(BaseHealth) + 0x2C))
#define BaseScaneY				((*(DWORD*)(BaseHealth) + 0x30))
#define BaseScaneZ				((*(DWORD*)(BaseHealth) + 0x34))

#define BaseRotation			((*(DWORD*)(BaseHealth) + 0x38))
#define AdrRotation			    ((*(DWORD*)(BaseAddrRotation) + 0xA4))



#define BaseGetMerchent		(GameProc + 0x877484)


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
#define AddrAshleyLuis		(GameProc + 0x282A6C)

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
cPatch InfGreenHerb(BaseGreenHerb, (BYTE*)"\x90\x90\x90\x90", 4);
cPatch InfRedHerb(BaseRedHerb, (BYTE*)"\x90\x90\x90\x90", 4);
cPatch InfYelowHerb(BaseYelowHerb, (BYTE*)"\x90\x90\x90\x90", 4);
cPatch InfGRYHerb(BaseHerbGRY, (BYTE*)"\x81\x47\x02\x99\x00\x00\x00\x90\x90", 9);
cPatch InfiniteHp1(AddrInfiniteHP1, (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
cPatch InfiniteHp2(AddrInfiniteHP2, (BYTE*)"\x90\x90\x90\x90\x90\x90\x90", 7);
cPatch AshleyToLuis(AddrAshleyLuis, (BYTE*)"\x90\x90\x48\x90\x90\x6A\x04", 7);
cPatch WallHack(AddrWallHack, (BYTE*)"\xC3", 1);
cPatch InfiniteAmmo(AddrAmmoStack, (BYTE*)"\x90\x90\x90\x90", 4);
cPatch NoReload(AddrAmmo, (BYTE*)"\x90\x90\x90\x90", 4);
cPatch InfiniteGrenade(AddrGrenade, (BYTE*)"\x90\x90\x90\x90", 4);
cPatch InfiniteBow(AddrBow, (BYTE*)"\x90\x90\x90\x90", 4);
cPatch OneHit(AddrOneHit, (BYTE*)"\xC7\x86\x24\x03\x00\x00\x00\x00\x00\x00\x90\x90\x90\x90\x90", 15);
cPatch FreezeEnemi(AddrFreezeEnemi, (BYTE*)"\x90\x90", 2);
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


bool RapidFire;

bool opt_InfiniteHealth;
bool opt_Invincible;
bool opt_Teleport;
bool opt_WalkThroughWall;
int opt_SpeedHack;
bool opt_SetUpDown;
bool opt_AshleyPresnets;

bool opt_InfiniteAmmo;
bool opt_NoReload;
bool opt_InfiniteLauncher;
bool opt_InfiniteBow;
bool opt_MaxPRL;
bool opt_RapidFire;

bool opt_OneHitKill;
bool opt_FrezzeEnemie;


void MainHack()
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


		int ONNoDamage = 32768;
		int OFFNoDamage = 0;
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

		if (opt_Teleport == 1)
		{

			if (GetAsyncKeyState(VK_HOME))
			{
				*(FLOAT*)Main2CordX = *(FLOAT*)MainCordX;
				*(FLOAT*)Main2CordY = *(FLOAT*)MainCordY;
				*(FLOAT*)Main2CordZ = *(FLOAT*)MainCordZ;
			}

		}

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

		if (RapidFire)
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

namespace Features
{


	namespace HealthBaseOffsets
	{
		enum : std::uint32_t
		{
			Status = 0x20, //0x3: playing; 0x106: pause; 0x4: Changing scene
			Scene = 0x28,
			SceneEntryX = 0x2C, //Player coordinates when the map loads
			SceneEntryY = 0x30,
			SceneEntryZ = 0x34,
			Rotation = 0x38,
			VisibilityFlags = 0x58,
			PlayerX = 0x124,
			PlayerY = 0x128,
			PlayerZ = 0x12C,
			Money = 0x4FA8,
			Health = 0x4FB4,
			MaxHealth = 0x4FB6,
			FirepowerIndex = 0x4FC0,
			FiringSpeed = 0x4FC4,
			Character = 0x4FC8, //0: Leon | 1: Ashley | 2: Ada | 3: HUNK | 4: Krauser | 5: Wesker
			Costume = 0x4FC9, //Leon { 0:Jacket, 1:Normal, 2:Vest, 3:RPD, 4:Mafia } | Ashley { 0:Normal, 1:Popstar, 2:Armor } | Ada { 0:RE2, 1:Spy, 3:Normal } | HUNK { 0:Normal } | Krauser { 0:Normal } | Wesker { 0:Normal }
			AshleyPresent = 0x5028, //0x04000000: Ashley; 0: !Ashley
			Difficulty = 0x847C //0: Amateur?, 3: Easy, 5: Normal, 6: Professional. Firepower is halved in Amateur, but capacity is doubled.
		};
	}

	namespace PlayerBaseOffsets
	{
		enum : std::uint32_t
		{
			EquippedItemId = 0xC,
			EquippedItem = 0x10,
			Inventory = 0x14,
			InventorySize = 0x1C
		};
	}

	namespace DoorListOffsets
	{
		enum : std::uint32_t
		{
			Type = 0x35
		};
	}

	enum class GameState : std::uint32_t
	{
		Playing = 0x3,
		ChangingScene = 0x4,
		Pause = 0x106
	};

	struct Entity
	{
		Pointer mVTable;
		char mPadding1[0x4];
		Entity* mNext;
		float mMatrix1[3][4];
		float mMatrix2[3][4];
		char mPadding2[0x28];
		Coordinates mCoords;
		char mPadding3[0x4];
		float mRotation;
		char mPadding4[0x4];
		Coordinates mScale1;
		Coordinates mScale2;
		char mPadding5[0x38];
		std::uint8_t mMeleeFlag; //4 == meleeing
		std::uint8_t mMovementFlag; //0 == Still | 1 == Walking forward | 2 == Walking backwards | 3 == Running | 4 == Turning | 5 == Quickturning
		std::uint8_t mRunningFlag; //1 == Not running | 3 == Running
		std::uint8_t mAimingFlag; //1 == Aiming
		char mPadding6[0x10];
		Coordinates mCoords2;
		char mPadding7[0x128];
		Coordinates mCoords3;
		char mPadding8[0x94];
		Coordinates mCoords4; //seems to be the center of the model
		char mPadding9[0x34];
		std::uint16_t mHealth;
		std::uint16_t mHealthLimit;
	}; //highest known offset: 0x79C

	static_assert(offsetof(Features::Entity, Features::Entity::mVTable) == 0x0);
	static_assert(offsetof(Features::Entity, Features::Entity::mNext) == 0x8);
	static_assert(offsetof(Features::Entity, Features::Entity::mMatrix1) == 0xC);
	static_assert(offsetof(Features::Entity, Features::Entity::mMatrix2) == 0x3C);
	static_assert(offsetof(Features::Entity, Features::Entity::mCoords) == 0x94);
	static_assert(offsetof(Features::Entity, Features::Entity::mRotation) == 0xA4);
	static_assert(offsetof(Features::Entity, Features::Entity::mScale1) == 0xAC);
	static_assert(offsetof(Features::Entity, Features::Entity::mScale2) == 0xB8);
	static_assert(offsetof(Features::Entity, Features::Entity::mMeleeFlag) == 0xFC);
	static_assert(offsetof(Features::Entity, Features::Entity::mMovementFlag) == 0xFD);
	static_assert(offsetof(Features::Entity, Features::Entity::mRunningFlag) == 0xFE);
	static_assert(offsetof(Features::Entity, Features::Entity::mAimingFlag) == 0xFF);
	static_assert(offsetof(Features::Entity, Features::Entity::mCoords2) == 0x110);
	static_assert(offsetof(Features::Entity, Features::Entity::mCoords3) == 0x244);
	static_assert(offsetof(Features::Entity, Features::Entity::mCoords4) == 0x2E4);
	static_assert(offsetof(Features::Entity, Features::Entity::mHealth) == 0x324);
	static_assert(offsetof(Features::Entity, Features::Entity::mHealthLimit) == 0x326);

	struct Camera
	{
		float mMatrix1[3][4];
		float mCameraMatrix[3][4];
		char mPadding1[0x4];
		float mWidth;
		char mPadding2[0x10];
		float mHeight;
		char mPadding3[0x14];
		float mUnknownFloat1;
		char mPadding4[0x8];
		float mUnknownFloat2;
		char mPadding5[0x4];
		Coordinates mCameraCoordinates;
		Coordinates mUnknownCoordinates;
		char mPadding6[0x4];
		float mFov;
		float mRotationMatrix[3][3];
	};

	static_assert(offsetof(Features::Camera, Features::Camera::mMatrix1) == 0x0);
	static_assert(offsetof(Features::Camera, Features::Camera::mCameraMatrix) == 0x30);
	static_assert(offsetof(Features::Camera, Features::Camera::mWidth) == 0x64);
	static_assert(offsetof(Features::Camera, Features::Camera::mHeight) == 0x78);
	static_assert(offsetof(Features::Camera, Features::Camera::mUnknownFloat1) == 0x90);
	static_assert(offsetof(Features::Camera, Features::Camera::mUnknownFloat2) == 0x9C);
	static_assert(offsetof(Features::Camera, Features::Camera::mCameraCoordinates) == 0xA4);
	static_assert(offsetof(Features::Camera, Features::Camera::mUnknownCoordinates) == 0xB0);
	static_assert(offsetof(Features::Camera, Features::Camera::mFov) == 0xC0);
	static_assert(offsetof(Features::Camera, Features::Camera::mRotationMatrix) == 0xC4);

	namespace
	{
		constexpr float kPi = 3.14159265358979323846264f;
		constexpr const wchar_t* kProcessName = L"bio4.exe";
		IDirect3DDevice9** gDirect3D9Device; //bio4.exe+CECB28
		ID3DXFont* gOverlayFont;
		ID3DXSprite* gOverlaySprite;
		std::uint32_t* gD3DDeviceVTable; //d3d9.dll+5A102
		float* gAspectRatio; //bio4.exe+71377C
		Camera* gCamera; //bio4.exe+19F5B7
		Pointer gHealthBase; //bio4.exe+806F3C
		Pointer gPlayerBase; //bio4.exe+870FD4
		void* gClipFunctionHookLocation; //bio4.exe+194C58
		Pointer gTmpFireRate; //bio4.exe+70F8BC
		Pointer gLinkedList; //bio4.exe+E6E608
		Pointer gTypewriterProcedure; //bio4.exe+563FF0
		Entity** gEntityList; //bio4.exe+7FDB18
		Pointer gEnemyVTable; //bio4.exe+71035C. VTable for enemies that can be meelee'd
		Entity** gPlayerNode; //bio4.exe+857054
		void* gRadioFunctionPatchLocation; //bio4.exe+369D66
		void(__cdecl* gOriginalClipFunction)(Entity* entity, void*); //bio4.exe+192E40
		void(__cdecl* gOpenMerchant)(std::int32_t, std::int32_t);
		HRESULT(__stdcall* gEndSceneOriginal)(IDirect3DDevice9*);
		HRESULT(__stdcall* gResetOriginal)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	}



	void SuspendProcess(std::wstring_view processName, bool freeze)
	{
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (Process32First(snapshot, &entry))
		{
			HANDLE currentThread = GetCurrentThread();
			do
			{
				if (entry.szExeFile == processName.data())
				{
					THREADENTRY32 thEntry;
					thEntry.dwSize = sizeof(THREADENTRY32);
					HANDLE ThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, entry.th32ProcessID);

					if (Thread32First(ThreadSnapshot, &thEntry))
					{
						do
						{
							if (HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, false, thEntry.th32ThreadID); hThread && hThread != currentThread)
							{
								if (freeze && thEntry.th32OwnerProcessID == entry.th32ProcessID)
									SuspendThread(hThread);
								else
									if (thEntry.th32OwnerProcessID == entry.th32ProcessID)
										ResumeThread(hThread);

								CloseHandle(hThread);
							}
						} while (Thread32Next(ThreadSnapshot, &thEntry));
					}
					CloseHandle(ThreadSnapshot);
					CloseHandle(snapshot);
					return;
				}
			} while (Process32Next(snapshot, &entry));
		}

		CloseHandle(snapshot);
		return;
	}

	void __cdecl ClippingFunctionHook(Entity* entity, void* arg2)
	{
		if (entity != *gPlayerNode)
			gOriginalClipFunction(entity, arg2);
	}

	bool Initialize()
	{
		Pointer clippingFunctionCall;
		std::vector<std::future<void>> scanFutures;

		scanFutures.push_back(std::async(std::launch::async, patternScan<IDirect3DDevice9**>, std::ref(gDirect3D9Device), "A1 ????????  8B 08  8B 91 70010000  56  50  FF D2  89 77 04", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<std::uint32_t*>, std::ref(gD3DDeviceVTable), "C7 06 ????????  89 86 ????????  89 86 ????????  89 86 ????????  89 86 ????????", L"d3d9.dll"));
		scanFutures.push_back(std::async(std::launch::async, patternScan<float*>, std::ref(gAspectRatio), "D9 05 ????????  D9 5C 24 04  D9 81 ????????  8B CE", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<Camera*>, std::ref(gCamera), "B9 ????????  5B E9  ????????  CC", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<Pointer>, std::ref(gHealthBase), "A1 ????????  83 C0 60  6A 10  50  E8", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<Pointer>, std::ref(gPlayerBase), "B9 ????????  E8 ????????  8B 35 ????????  81", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<Pointer>, std::ref(clippingFunctionCall), "E8 ????????  D9 86 ????????  8B 4D 10", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<Pointer>, std::ref(gTmpFireRate), "D9 05 ????????  D9 45 D4  D8D1  DFE0  DDD9  F6 C4 41", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<Pointer>, std::ref(gLinkedList), "BB ????????  E8 ????????  89 45 FC  EB 03  8B 45 FC", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<Pointer>, std::ref(gTypewriterProcedure), "55  8B EC  A1 ????????  81 88 28500000 00080000", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<Entity**>, std::ref(gEntityList), "8B 35 ????????  85 F6  74 43  8B C6", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<Pointer>, std::ref(gEnemyVTable), "C7 06 ????????  8B C6  5E  5D  C2 0400  33 C0  5E  5D  C2 0400  CCCCCCCCCCCCCCCCCCCC 55  8B EC  56  8B 75 08  85 F6  74 0D  8B CE  E8 ????????  C7 06 ????????  5E  5D  C3  CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC  C7 05 ???????? ????????  C7 05 ???????? ????????  C3", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<decltype(gOpenMerchant)>, std::ref(gOpenMerchant), "55  8B EC  A1 ????????  B9 00000004", kProcessName));
		scanFutures.push_back(std::async(std::launch::async, patternScan<void*>, std::ref(gRadioFunctionPatchLocation), "8B 92 DC010000  03 CF  51", kProcessName));

		for (auto& future : scanFutures)
			future.wait();

		if (!(gDirect3D9Device && gD3DDeviceVTable && gAspectRatio && gCamera && gHealthBase && gPlayerBase && clippingFunctionCall && gTmpFireRate && gLinkedList && gTypewriterProcedure && gEntityList && gEnemyVTable && gOpenMerchant && gRadioFunctionPatchLocation))
			return false;

		gDirect3D9Device = getValue<IDirect3DDevice9**>(addBytes(gDirect3D9Device, 1));
		if (D3DXCreateFontA(*gDirect3D9Device, 18, 9, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &gOverlayFont) != S_OK)
			return false;
		if (D3DXCreateSprite(*gDirect3D9Device, &gOverlaySprite) != S_OK)
			return false;
		gAspectRatio = getValue<float*>(addBytes(gAspectRatio, 2));
		gCamera = pointerPath<Camera>(gCamera, 1, 4);
		gHealthBase = pointerPath<std::remove_pointer_t<Pointer>>(gHealthBase, 0x1, 0x0);
		gPlayerBase = getValue<Pointer>(gPlayerBase + 1);
		gTmpFireRate = getValue<Pointer>(gTmpFireRate + 2);
		gLinkedList = getValue<Pointer>(gLinkedList + 1);
		gPlayerNode = getValue<Entity**>(addBytes(gEntityList, 17));
		gEntityList = getValue<Entity**>(addBytes(gEntityList, 2));
		gEnemyVTable = getValue<Pointer>(gEnemyVTable + 2);
		gD3DDeviceVTable = getValue<std::uint32_t*>(addBytes(gD3DDeviceVTable, 2));
		gClipFunctionHookLocation = follow(clippingFunctionCall);
		gOriginalClipFunction = follow<decltype(gOriginalClipFunction)>(gClipFunctionHookLocation);
		gEndSceneOriginal = getValue<decltype(gEndSceneOriginal)>(gD3DDeviceVTable + 42);
		gResetOriginal = getValue<decltype(gResetOriginal)>(gD3DDeviceVTable + 16);

		return true;
	}

	void Terminate()
	{
		gOverlaySprite->Release();
		gOverlayFont->Release();
		SkipRadioCutscenes(false);
		ToggleClipping(false);
		ToggleFastTmp(false);
	}

	// ==============================   MAIN HACK ==============================
	std::float_t GetTime()
	{
		return *(FLOAT*)BaseTimer;
	}

	void SetTime(std::float_t value)
	{
		*(FLOAT*)BaseTimer = value;
	}
	void SetMoney(std::uint32_t value)
	{
		setValue<std::uint32_t>(gHealthBase + HealthBaseOffsets::Money, value);
	}

	std::uint32_t GetMoney()
	{
		return getValue<std::uint32_t>(gHealthBase + HealthBaseOffsets::Money);
	}

	void SetPoints(std::uint32_t value)
	{
		*(DWORD*)BasePoints = value;
	}
	std::uint32_t GetPoints()
	{
		return *(DWORD*)BasePoints;
	}

	void SetPointsKill(std::uint32_t value)
	{
		*(DWORD*)BasePointsKill = value;
	}
	std::uint32_t GetPointsKill()
	{
		return *(DWORD*)BasePointsKill;
	}

	void SetDifficulty(Difficulty value)
	{
		setValue<Difficulty>(gHealthBase + HealthBaseOffsets::Difficulty, value);
	}

	Difficulty GetDifficulty()
	{
		return getValue<Difficulty>(gHealthBase + HealthBaseOffsets::Difficulty);
	}

	void OpenTypewriter(TypewriterMode mode)
	{
		Pointer node = getValue<Pointer>(gLinkedList + 0x34);
		node = getValue<Pointer>(node + 0x14);
		node += 0x18;

		setValue<TypewriterMode>(node + 0x14, mode);
		setValue<Pointer>(node + 0x33C, gTypewriterProcedure);
		setValue<std::uint8_t>(node + 4, 1);
	}

	void OpenMerchant()
	{
		gOpenMerchant(0x10, 0);
	}

	void SkipRadioCutscenes(bool skip)
	{
		static const char jumpInstruction[] = { '\xE9', '\x1A', '\x02', '\x00', '\x00', '\x90' };
		static const char originalCode[] = { '\x8B', '\x92', '\xDC', '\x01', '\x00', '\x00' };

		setValue(gRadioFunctionPatchLocation, skip ? jumpInstruction : originalCode);
	}

	bool IsRadioSkipEnabled()
	{
		return getValue<std::uint8_t>(gRadioFunctionPatchLocation) == 0xE9;
	}

	// =========================================================================================

	// ============================== PLAYER HACK
	std::optional<Coordinates*> GetPlayerCoordinates()
	{
		std::optional<Coordinates*> result;

		if (Entity* playerEntity = *gPlayerNode)
			result = &playerEntity->mCoords;

		return result;
	}

	void SetHealth(std::uint16_t health)
	{
		setValue(gHealthBase + HealthBaseOffsets::Health, health);
	}

	std::uint16_t GetHealth()
	{
		return getValue<std::uint16_t>(gHealthBase + HealthBaseOffsets::Health);
	}

	void SetHealthLimit(std::uint16_t limit)
	{
		setValue(gHealthBase + HealthBaseOffsets::MaxHealth, limit);
	}

	std::uint16_t GetHealthLimit()
	{
		return getValue<std::uint16_t>(gHealthBase + HealthBaseOffsets::MaxHealth);
	}


	bool IsAshleyPresent()
	{
		return getValue<std::uint32_t>(gHealthBase + HealthBaseOffsets::AshleyPresent) & 0x04000000;
	}

	void ToggleAshley(bool toggle)
	{
		if (Entity* playerEntity = *gPlayerNode)
		{
			setValue<std::uint32_t>(gHealthBase + HealthBaseOffsets::AshleyPresent, toggle ? 0x04000000 : 0);
			setValue<Coordinates>(gHealthBase + HealthBaseOffsets::SceneEntryX, playerEntity->mCoords);
			setValue<float>(gHealthBase + HealthBaseOffsets::Rotation, playerEntity->mRotation);
			setValue<GameState>(gHealthBase + HealthBaseOffsets::Status, GameState::ChangingScene);
		}
	}

	void ToggleInfiniteHealth(bool toggle)
	{
		opt_InfiniteHealth = toggle ? true : false;
	}

	void ToggleInvincible(bool toggle)
	{
		opt_Invincible = toggle ? true : false;
	}

	std::float_t GetSpeedPlayer()
	{
		return *(FLOAT*)AddrSpeedHack;
	}

	void SetSpeedPlayer(std::float_t value)
	{
		*(FLOAT*)AddrSpeedHack = value;
	}

	void ToggleClipping(bool toggle)
	{
		opt_WalkThroughWall = toggle ? true : false;
	}

	void ToggleStUpDown(bool toggle)
	{
		opt_SetUpDown = toggle ? true : false;
	}

	void ToggleAshleyTeleport(bool toggle)
	{
		opt_Teleport = toggle ? true : false;
	}
	// =========================================================================================

	// ============================== WAPON HACK

	void ToggleInfiniteAmmo(bool toggle)
	{
		opt_InfiniteAmmo = toggle ? true : false;
	}

	void ToggleAmmoNoReload(bool toggle)
	{
		opt_NoReload = toggle ? true : false;
	}

	void ToggleBow(bool toggle)
	{
		opt_InfiniteBow = toggle ? true : false;
	}

	void ToggleInfiniteGrenade(bool toggle)
	{
		opt_InfiniteLauncher = toggle ? true : false;
	}

	void ToggleAutoMaxPRL(bool toggle)
	{
		opt_MaxPRL = toggle ? true : false;
	}

	void ToggleFastTmp(bool toggle)
	{
		DWORD oldProtect;

		if (VirtualProtect(gTmpFireRate, sizeof(float), PAGE_READWRITE, &oldProtect))
		{
			*(float*)gTmpFireRate = toggle ? 1.5f : 3.0f;
			VirtualProtect(gTmpFireRate, sizeof(float), oldProtect, &oldProtect);
		}
	}

	bool IsFastTmpEnabled()
	{
		return *(float*)gTmpFireRate == 1.5f;
	}

	void ToggleRapidFire(bool toggle)
	{
		RapidFire = toggle ? true : false;
	}

	// =========================================================================================

	// ============================== ENEMIE HACK

	void ToggleFrezeeEnemie(bool toggle)
	{
		opt_FrezzeEnemie = toggle ? true : false;
	}

	void ToggleOneHitKill(bool toggle)
	{
		opt_OneHitKill = toggle ? true : false;
	}

}
