/*======================================================= RTA CODE TEAM =======================================================*/
#include "Stdafx.h"

#pragma once

class cPatch
{
private:
	DWORD   ADR;
	BYTE	OFF_BYTES[255];
	BYTE    ON_BYTES[255];
	int		SIZE;
	enum	PATCHSTATUS
	{
		NORMAL,
		PATCHED,
	};
	int		STATUS;

	void* memcpy_s(void* pvAddress, const void* pvBuffer, size_t stLen);
public:
	cPatch(DWORD pAdr, BYTE* pByte, int pSize);
	void Patch();
	void Restore();
};

/*======================================================= RTA CODE TEAM =======================================================*/