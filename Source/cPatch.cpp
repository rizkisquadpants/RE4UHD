/*======================================================= RTA CODE TEAM =======================================================*/

#include "cPatch.h"




void* cPatch::memcpy_s(void* pvAddress, const void* pvBuffer, size_t stLen)
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((void*)pvAddress, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);
	void* pvRetn = memcpy((void*)pvAddress, (void*)pvBuffer, stLen);
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);
	FlushInstructionCache(GetCurrentProcess(), (void*)pvAddress, stLen);
	return pvRetn;
}

cPatch::cPatch(DWORD pAdr, BYTE* pByte, int pSize)
{
	STATUS = NORMAL;
	SIZE = pSize;
	ADR = pAdr;

	for (int i = 0; i < pSize; i++)
	{
		OFF_BYTES[i] = 0x00;
		ON_BYTES[i] = pByte[i];
	}
}

void cPatch::Patch()
{
	if (STATUS == NORMAL)
	{
		BYTE* pOFF_BYTES = (BYTE*)ADR;
		for (int i = 0; i < SIZE; i++)
		{
			OFF_BYTES[i] = pOFF_BYTES[i];
		}
		memcpy_s((void*)ADR, (const void*)ON_BYTES, SIZE);
		STATUS = PATCHED;
	}
}
void cPatch::Restore()
{
	if (STATUS == PATCHED)
	{
		memcpy_s((void*)ADR, (const void*)OFF_BYTES, SIZE);
		STATUS = NORMAL;
	}
}

/*======================================================= RTA CODE TEAM =======================================================*/