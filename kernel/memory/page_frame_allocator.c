#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/multiboot.h"
#include "../include/page_frame_allocator.h"
#include "../include/vga_text.h"

typedef struct SPage
{
	struct SPage *pNextPage;
} SPage;

typedef struct SLinked_List
{
	SPage *pHead;
	SPage *pTail;
} SLinked_List;

uint32_t *pu32CurrentPageFrameAddress;
uint32_t *pu32EndPageFrameAddress;

SLinked_List *pLinkedList;
uint32_t *pu32LengthOfLinkedList;

void fnPush(SPage *pPage);
uint32_t *fnPop(void);

void fnInitialisePageFrameAllocator(uint32_t u32StartOfMemory, uint32_t u32EndOfMemory)
{
	pu32CurrentPageFrameAddress = (uint32_t *)u32StartOfMemory;
	*pu32CurrentPageFrameAddress = (uint32_t)(((uint32_t *)u32StartOfMemory) + 5);

	pu32EndPageFrameAddress = ((uint32_t *)u32StartOfMemory) + 1;
	*pu32EndPageFrameAddress = u32EndOfMemory;

	pu32LengthOfLinkedList = ((uint32_t *)u32StartOfMemory) + 2;
	*pu32LengthOfLinkedList = 0;

	pLinkedList = (SLinked_List *)(((uint32_t *)u32StartOfMemory) + 3);
}

uint32_t *fnAllocPage(void)
{
	if ((*pu32CurrentPageFrameAddress + 4096) > *pu32EndPageFrameAddress)
		return (uint32_t *)-1;

	if (*pu32LengthOfLinkedList == 0)
	{
		*pu32CurrentPageFrameAddress = *pu32CurrentPageFrameAddress + 4096;

		return (uint32_t *)(*pu32CurrentPageFrameAddress - 4096);
	}

	return fnPop();
}

void fnFreePage(uint32_t *pu32PageFrameAddress)
{
	SPage *pNewPage = (SPage *)pu32PageFrameAddress;

	pNewPage->pNextPage = NULL;

	fnPush(pNewPage);
}

void fnPush(SPage *pPage)
{
	if (*pu32LengthOfLinkedList == 0)
	{
		pLinkedList->pHead = pPage;
		pLinkedList->pTail = pPage;
	}
	else
	{
		pLinkedList->pTail->pNextPage = pPage;
	}

	(*pu32LengthOfLinkedList) = (*pu32LengthOfLinkedList) + 1;
}

uint32_t *fnPop(void)
{
	SPage *pNewHead = pLinkedList->pHead->pNextPage;
	uint32_t *pu32CurrentHead = (uint32_t *)pLinkedList->pHead;
	pLinkedList->pHead = pNewHead;
	return pu32CurrentHead;
}
