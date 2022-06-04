/*======================================================= RTA CODE TEAM =======================================================*/
#include <windows.h>
#include "cGameHacks.h"

/*-------------------------------------------------------------------------------------------------------------------*/
int Drawing		= 0;
int Mpos		= 0;	
int Mmax		= 0;
int DrawFont	= 1;
int Mvisible	= 1;
int Mxofs		= 25.0f;
int Mysize		= 15.0f;
int my			= 59; // Up Down
int	mx			= 110; // Right Left
char Mtitle[81]	= "";

LPDIRECT3DVERTEXBUFFER9 Stream_Data;
UINT Offset = 0;
UINT Stride = 0;
LPDIRECT3DDEVICE9 npDevice, pGDevice; 

/*-------------------------------------------------------------------------------------------------------------------*/
char *Moptfolder          []   = {"Open", "Close"}; 
char* ONOF[] = { "•", "On" };
char* ONOF2[] = { "Normal", "X2", "X3" };
char *ONOF3[]   = {"•", "20%", "30%","40%","50%"};

/*-------------------------------------------------------------------------------------------------------------------*/
#define 		MENUMAXINDEX	100
#define 		MENUFOLDER		1
#define 		MENUTEXT		2
#define 		MENUITEM		3
#define			MENUCAT			4
#define			COLORFOLDER		D3DCOLOR_ARGB(255, 127, 255, 212)
#define			COLORTEXT		D3DCOLOR_ARGB(255, 255, 255, 000)
#define			COLORON			D3DCOLOR_ARGB(255, 255, 255, 255)
#define			COLOROFF		D3DCOLOR_ARGB(255, 245, 000, 000)
#define			COLORCURENT		D3DCOLOR_ARGB(255, 255, 255, 255)

struct{
int  *var;
int  maxvalue;
int  typ;
char *txt;
char **opt;
}


D3MENU[MENUMAXINDEX];
LPD3DXFONT pFont;
/*------------------------------------------- Declaration AddText ------------------------------------------------------*/
void AddItem(char *txt,  char **opt, int *var, int maxvalue, int typ)
{
	D3MENU[Mmax].typ=typ;
	D3MENU[Mmax].txt=txt;
	D3MENU[Mmax].opt=opt;
	D3MENU[Mmax].var=var;
	D3MENU[Mmax].maxvalue=maxvalue;
	Mmax++;
}

/*------------------------------------------- Declaration AddText ------------------------------------------------------*/
void AddText(char *txt, char *opt)
{
	D3MENU[Mmax].typ=MENUTEXT;
	D3MENU[Mmax].txt=txt;
	D3MENU[Mmax].opt=(char **)opt;
	D3MENU[Mmax].var=0;
	D3MENU[Mmax].maxvalue=0;
	Mmax++;
}

/*------------------------------------------- Declaration TextR ------------------------------------------------------*/
void DrawTextR(int x,int y,DWORD color,char *text)
{
    RECT rect, rect1, rect2, rect3, rect4, rect5;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect1, x-1, y, x-1, y );
    SetRect( &rect2, x, y, x, y );
	SetRect( &rect3, x, y+1, x, y+1 );
    SetRect( &rect4, x, y, x, y );
	SetRect( &rect5, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont->DrawTextA(NULL,text,-1,&rect5, DT_LEFT|DT_NOCLIP, color );
    pFont->DrawTextA(NULL,text,-1,&rect,  DT_LEFT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect1, DT_LEFT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect2, DT_LEFT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect3, DT_LEFT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect4, DT_LEFT|DT_WORDBREAK, BLACK );
}

/*------------------------------------------- Declaration TextL ------------------------------------------------------*/
void DrawTextL(int x,int y,DWORD color,char *text)
{
	RECT rect, rect1, rect2, rect3, rect4, rect5;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect1, x-1, y, x-1, y );
    SetRect( &rect2, x, y, x, y );
	SetRect( &rect3, x, y+1, x, y+1 );
    SetRect( &rect4, x, y, x, y );
	SetRect( &rect5, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont->DrawTextA(NULL,text,-1,&rect5, DT_RIGHT|DT_NOCLIP, color );
    pFont->DrawTextA(NULL,text,-1,&rect,  DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect1, DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect2, DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect3, DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect4, DT_RIGHT|DT_WORDBREAK, BLACK );
}

/*------------------------------------------- Declaration TextC ------------------------------------------------------*/
void DrawTextC(int x,int y,DWORD color,char *text )
{
    RECT rect, rect2;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect2, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont->DrawTextA(NULL,text,-1,&rect2, DT_CENTER|DT_NOCLIP, 0x00000000 );
    pFont->DrawTextA(NULL,text,-1,&rect, DT_CENTER|DT_NOCLIP, color );
}

/*------------------------------------------- Declaration MenuShow ------------------------------------------------------*/
void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	int i, val;
	DWORD color;
	DWORD texty;
	char text[100];
	if (!Mvisible) return;
	for (i=0; i<Mmax; i++) 
	{
		val=(D3MENU[i].var)?(*D3MENU[i].var):0;
		sprintf(text, "%s", D3MENU[i].txt);
		if (i==Mpos){
			if(RainbowTexts!=100)
			{RainbowR-=2,RainbowG-=3,RainbowB-=3;}
			if(RainbowTexts!=255)
			{RainbowR+=2,RainbowG+=3,RainbowB+=4;}
			color=RainbowTextTest;
			texty=RainbowTextTest;
			sprintf(text, "=> %s", D3MENU[i].txt);
		}
		else if (D3MENU[i].typ==MENUFOLDER){
			color=COLORFOLDER;
			texty=COLORFOLDER;
		}
		else if (D3MENU[i].typ==MENUTEXT){
			color=COLORTEXT;
			texty=COLORTEXT;
		}
		else{
			color=(val)?COLORON:COLOROFF;
			texty=(val)?COLORCURENT:COLORCURENT;
		}
		if (D3MENU[i].opt)
		{
			if (D3MENU[i].typ==MENUITEM){
				DrawTextL(x+3, y, texty,text);
				y = y + 2;
			}else{
				DrawTextL(x+3, y, texty,text);
			}
		}
		if (D3MENU[i].opt) {
			if (D3MENU[i].typ==MENUTEXT)
				DrawTextR((x+Mxofs), y, color,(char *)D3MENU[i].opt);
			else
				DrawTextR((x+Mxofs), y, color,(char *)D3MENU[i].opt[val]);
		}
		y+=Mysize;
	}
}

/*------------------------------------------- Declaration MenuNavigation ------------------------------------------------------*/
void MenuNav(void)
{
	if (IsKeyPressed(VK_INSERT, 0)&1)
	{
		Mvisible=(!Mvisible);
	}
	if (!Mvisible) return;
	if (IsKeyPressed(VK_UP, 0)&1) {
		do {
			Mpos--;
			if (Mpos<0)  Mpos=Mmax-1;
		} 
		while (D3MENU[Mpos].typ==MENUTEXT);	
	}else if (IsKeyPressed(VK_DOWN, 0)&1) {
		do {
			Mpos++;
			if (Mpos==Mmax) Mpos=0;
		} while (D3MENU[Mpos].typ==MENUTEXT);		
	} else if (D3MENU[Mpos].var) {
		int dir=0;
		if ( ( IsKeyPressed(VK_LEFT, 0)&1 ) && *D3MENU[Mpos].var > 0 ) dir=-1;
		if ( ( IsKeyPressed(VK_RIGHT, 0)&1 ) && *D3MENU[Mpos].var < (D3MENU[Mpos].maxvalue-1)) dir=1;
		if (dir) {
			*D3MENU[Mpos].var += dir;
			if (D3MENU[Mpos].typ==MENUFOLDER) Mmax=0;
			if (D3MENU[Mpos].typ==MENUCAT) Mmax=0;  
		}
	}
}

/*------------------------------------------- Declaration Date ------------------------------------------------------*/
char* GetDate()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	char *logbuf = new char[ 256 ];
	sprintf(logbuf,": %d-%d-%d" ,st.wDay,st.wMonth,st.wYear);
	return logbuf;
}

/*------------------------------------------- Declaration Time ------------------------------------------------------*/
char* GetTime()
{
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime(&current_time);
	char *logbuf = new char[ 256 ];
	sprintf(logbuf, ": %02d:%02d:%02d", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec );
	return logbuf;
}

/*------------------------------------------- Declaration Menu ------------------------------------------------------*/
void RebuildMenu(LPDIRECT3DDEVICE9 pDevice)
{
/*------------------------------------------- Declaration Title ------------------------------------------------------*/
	AddText("RTA CODE TEAM"		,"Update @2022 - v1.0.0.3");
	AddText("Game Name :"	,"Resident Evil 4 Ultimate HD Edition");
	AddText("Version :", "1.0.6");
/*------------------------------------------- Declaration D3D ------------------------------------------------------*/
	AddItem("Visual Info"				, Moptfolder, &Direct_INFO, 2, MENUFOLDER);
	if(Direct_INFO)
	{
	  AddText("Date"												, GetDate());
	  AddText("Time"												, GetTime());
    }

	AddItem("Menu Main"					, Moptfolder, &Direct_MAIN, 2, MENUFOLDER);
	if(Direct_MAIN)
	{
		AddItem("Unlimited Money"		, ONOF, &opt_Money, 2, MENUCAT);
		AddItem("Freeze Time"			, ONOF, &opt_Time, 2, MENUCAT);
		AddText("", "");
		AddText("Mercenaries", "");
		AddItem("Points Full"			, ONOF, &opt_PointsHack, 2, MENUCAT);
		AddItem("Poinst Kill"			, ONOF, &opt_PointsKill, 2, MENUCAT);
	}

	AddItem("Menu Player"				, Moptfolder, &Direct_PLAYER, 2, MENUFOLDER);
	if(Direct_PLAYER)
	{
		AddItem("Infinite Health"		, ONOF, &opt_InfiniteHealth, 2, MENUCAT);
		AddItem("Invincible"			, ONOF, &opt_Invincible, 2, MENUCAT);
		AddItem("Walkthrough Wall"		, ONOF, &opt_WalkThroughWall, 2, MENUCAT);
		AddItem("Set Player Up Down"	, ONOF, &opt_SetUpDown, 2, MENUCAT);
		if (opt_SetUpDown)
		{
			AddText("", "Gunakan Tombol I Untuk Naik Dan Tombol K Untuk Turun");
			AddText("", "");
		}
		AddItem("Teleport Ahley"		, ONOF, &opt_Teleport, 2, MENUCAT);
		if (opt_Teleport)
		{
			AddText("", "Tutorial Menggunakan Teleport Ahley");
			AddText("", "  > Onkan Fiture Walkthrough Wall");
			AddText("", "  > Gunakan Hotkey HOME Untuk Menteleport Ashley Ke Sisi Main Player");
			AddText("", "");
		}
		AddItem("Movement Speed"		, ONOF2, &opt_SpeedHack, 3, MENUCAT);
	}

	AddItem("Menu Weapon"				, Moptfolder, &Direct_WEAPON, 2, MENUFOLDER);
	if(Direct_WEAPON)
	{
		AddItem("Infinite Ammo"			, ONOF, &opt_InfiniteAmmo, 2, MENUCAT);
		AddItem("No Reload"				, ONOF, &opt_NoReload, 2, MENUCAT);
		AddItem("Infinite Bow"			, ONOF, &opt_InfiniteBow, 2, MENUCAT);
		AddItem("Infinite Grenade"		, ONOF, &opt_InfiniteLauncher, 2, MENUCAT);
		AddItem("P.R.L Always MAX"		, ONOF, &opt_MaxPRL, 2, MENUCAT);
		AddItem("Rapid Fire"			, ONOF, &opt_RapidFire, 2, MENUCAT);

	}

	AddItem("Menu Enemie"				, Moptfolder, &Direct_ENEMIE, 2, MENUFOLDER);
	if(Direct_ENEMIE)
	{
		AddItem("One Hit Kill"			, ONOF, &opt_OneHitKill, 2, MENUCAT);
		AddItem("Freeze Enemy"			, ONOF, &opt_FrezzeEnemie, 2, MENUCAT);
	  
	}

	/*------------------------------------------- Declaration Title ------------------------------------------------------*/
	AddText("", "");
	AddText("Show / Hide Menu", " INSERT");
	AddText("Fast Exit Game", " F12");
}

/*======================================================= RTA CODE TEAM =======================================================*/
