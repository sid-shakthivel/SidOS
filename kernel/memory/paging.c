#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/paging.h"
#include "../include/vga_text.h"
#include "../include/multiboot.h"
#include "../include/string.h"

extern uint32_t __kernel_end;

extern void fnEnablePaging();
extern void fnLoadPageDirectory(uint32_t *pu32PageDirectory);

uint32_t *pu32rgPageDirectory;
uint32_t *pu32rgPageTables;

uint32_t u32PageSize = 1024;

void fnSetEntry(uint32_t *pu32PageLocation, uint32_t u32MemoryLocation, uint8_t u8isKernel, uint8_t u8isWriteable)
{
	*pu32PageLocation = u32MemoryLocation & 0xFFFFF000;

	//	Setting Cache Disable Bit To 1
	*pu32PageLocation |= 1 << 4;

	*pu32PageLocation |= u8isKernel << 2;
	*pu32PageLocation |= u8isWriteable << 1;

	//	Setting Present Bit To 1
	*pu32PageLocation |= 1 << 0;
}

void fnIdentityMap(void)
{
	//	Set Up Page Directory With Page Table Entries

	uint32_t u32CurrentPageTable = (uint32_t)pu32rgPageTables;

	for (uint32_t *pu32CurrentPageDirectoryEntry = pu32rgPageDirectory; pu32CurrentPageDirectoryEntry < pu32rgPageTables; ++pu32CurrentPageDirectoryEntry)
	{
		fnSetEntry(pu32CurrentPageDirectoryEntry, u32CurrentPageTable, 1, 1);
		u32CurrentPageTable += 4096;
	}

	// Setup Page Tables - Map All Physical Addresses To Virtual Ones

	for (uint32_t u32CurrentPageFrame = 0; u32CurrentPageFrame < 0x00000000021acfff; u32CurrentPageFrame += 1024)
	{
		uint32_t *pu32Index = (uint32_t *)pu32rgPageTables + (u32CurrentPageFrame / 4096);
		fnSetEntry(pu32Index, u32CurrentPageFrame, 1, 1);
	}
}

uint32_t fnInitialisePaging(uint32_t u32SizeOfTarBall)
{
	uint32_t u32StartOfMemory = (uint32_t)&__kernel_end + (1024 * 4) + (1024 * 4 * 1024);

	pu32rgPageDirectory = (uint32_t *)&__kernel_end;
	pu32rgPageTables = pu32rgPageDirectory + u32PageSize;

	fnIdentityMap();

	fnLoadPageDirectory(pu32rgPageDirectory);

	fnEnablePaging();

	printf("TAR BALL IS %d AND START OF MEMORY IS %d\n", u32SizeOfTarBall, u32StartOfMemory);

	return u32StartOfMemory + u32SizeOfTarBall + 1;
}

uint32_t fnCalculateMaximumMemory(multiboot_info_t *pMBD)
{
	SMultibootSegment *pEntry = (SMultibootSegment *)(pMBD->mmap_addr);

	uint32_t u32MaxMemory = 0;

	while ((multiboot_uint32_t)pEntry < pMBD->mmap_addr + pMBD->mmap_length)
	{
		if (pEntry->lliAddress == 0x100000)
		{
			u32MaxMemory = (uint32_t)pEntry->lliAddress + (uint32_t)pEntry->lliLength;
			break;
		}
		pEntry = (SMultibootSegment *)((uint32_t)pEntry + pEntry->uiSize + sizeof(pEntry->uiSize));
	}

	return u32MaxMemory;
}