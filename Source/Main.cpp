
/*------------------------------------------ RTA CODE TEAM Copyright 2022 -------------------------------------------------*/

#include <windows.h>
#include <wininet.h>
#include <time.h>
#include "Stdafx.h"
#include "cMenu.h"

/*-------------------------------------------------------------------------------------------------------------------*/
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene = NULL;

typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive = NULL;

typedef HRESULT(WINAPI* tReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset oReset = NULL;



/*------------------------------------------- Declaration DrawMenuD3D ------------------------------------------------------*/
void DrawMenuD3D(LPDIRECT3DDEVICE9 pDevice)
{
	if (DrawFont == 1) 
	{
		D3DXCreateFontA(pDevice, 11, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pFont);
		DrawFont = 0;
	}

	if (Drawing == 0)
	{
		if(Mmax==0) 
		RebuildMenu(pDevice);
		MenuShow(mx,my,pDevice);
		MenuNav();
	}

	if(!g_pFont)	D3DXCreateFontA(pDevice, 15, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Hud_Small_Font", &g_pFont);//15
	if(!pLine)		D3DXCreateLine( pDevice, &pLine );
}

/*------------------------------------------- Declaration GenerateTexture ------------------------------------------------------*/
LPDIRECT3DTEXTURE9 RainbowTextTestX;
HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
    if(FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
        return E_FAIL;
    
    WORD colour16 = ((WORD)((colour32>>28)&0xF)<<12)
	            	|(WORD)(((colour32>>20)&0xF)<<8)
	             	|(WORD)(((colour32>>12)&0xF)<<4)
                 	|(WORD)(((colour32>>4)&0xF)<<0);

    D3DLOCKED_RECT d3dlr;    
    (*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
    WORD *pDst16 = (WORD*)d3dlr.pBits;

    for(int xy=0; xy < 8*8; xy++)
        *pDst16++ = colour16;

    (*ppD3Dtex)->UnlockRect(0);

    return S_OK;
}

/*------------------------------------------- Declaration DrawEndScene ------------------------------------------------------*/
HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->GetViewport(&g_ViewPort);
	DrawMenuD3D(pDevice);

	if(RainbowTexts!=100)
	{RainbowR-=2,RainbowG-=3,RainbowB-=3;}
	if(RainbowTexts!=255)
	{RainbowR+=2,RainbowG+=3,RainbowB+=4;}
	GenerateTexture(pDevice, &RainbowTextTestX,  RainbowTextTest);

	//=================================================
	PlayerHack();
	WeaponHack();
	EnemieHack();
	_PRLHack();
	_Wallhack();
	_TeleportAshley();
	_GodMode();
	_Fitur_RapidFire();
	_SpeedHack();
	SkupMe();
	//=================================================


	if(IsKeyPressed(VK_F12, 0)&1)
	{
		ExitProcess(0);
	}
	return oEndScene(pDevice);
}

/*------------------------------------------- Declaration DrawIndexPrim ------------------------------------------------------*/
HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{

if(pDevice->GetStreamSource(0, &Stream_Data, &Offset, &Stride) == D3D_OK){
Stream_Data->Release();
}
	return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

/*------------------------------------------- Declaration DrawReset ------------------------------------------------------*/
HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    if( g_pFont )
        g_pFont->OnLostDevice();

	if( pFont )
		pFont->OnLostDevice();

    if( pLine )
        pLine->OnLostDevice();

    if(oReset == D3D_OK) 
	{
		if( g_pFont )
            g_pFont->OnResetDevice();
		
		if( pFont )
			pFont->OnResetDevice();

        if( pLine )
            pLine->OnResetDevice();
	}

    return oReset(pDevice, pPresentationParameters);
}

/*------------------------------------------- Declaration HookEngine ------------------------------------------------------*/
#include "detours.h"
IDirect3D9* HookDirect3DCreate9(VOID)
{
	DWORD Base = (DWORD)LoadLibraryW(L"d3d9.dll");

	for (DWORD i = 0; i < 0x128000; i++)
	{
		if ((*(BYTE*)(Base + i + 0x00)) == 0xC7
			&& (*(BYTE*)(Base + i + 0x01)) == 0x06
			&& (*(BYTE*)(Base + i + 0x06)) == 0x89
			&& (*(BYTE*)(Base + i + 0x07)) == 0x86
			&& (*(BYTE*)(Base + i + 0x0C)) == 0x89
			&& (*(BYTE*)(Base + i + 0x0D)) == 0x86)
			return (IDirect3D9*)(Base + i + 2);
	}
	return NULL;
}

IDirect3D9* pD3D;
void __fastcall HookD3D9VIIP()
{
	while (!pD3D) { pD3D = HookDirect3DCreate9(); }
	DWORD* VD3D = (DWORD*)pD3D;
	VD3D = (DWORD*)VD3D[0];
	//----------------------------------------------------------------------------//
	oReset = (tReset)DetourFunction((PBYTE)VD3D[16], (PBYTE)hkReset);
	oEndScene = (tEndScene)DetourFunction((PBYTE)VD3D[42], (PBYTE)hkEndScene);
	oDrawIndexedPrimitive = (tDrawIndexedPrimitive)DetourFunction((PBYTE)VD3D[82], (PBYTE)hkDrawIndexedPrimitive);

}



/*--------------------------------------- Declaration Caller AllThread --------------------------------------------------*/
void ZrCCyBCallerThread()
{
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HookD3D9VIIP,NULL,NULL,NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)RIZKIKOTETHACK, NULL, NULL, NULL);
}

/*------------------------------------------- Declaration Attach Dll ------------------------------------------------------*/
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH){
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ZrCCyBCallerThread,NULL,NULL,NULL);
		Beep(1000, 100);
}
return TRUE;
}

/*======================================================= RTA CODE TEAM =======================================================*/