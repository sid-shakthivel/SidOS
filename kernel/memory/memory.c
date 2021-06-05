#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/memory.h"
#include "../include/page_frame_allocator.h"
#include "../include/vga_text.h"

typedef struct SFreeNode {
	struct SFreeNode *pPrevious;
	struct SFreeNode *pNext;
	uint32_t u32Size;
} SFreeNode;

SFreeNode *pHead = NULL;
SFreeNode *pTail = NULL;
uint32_t u32LengthOfLinkedList = 1;

uint32_t u32PageLeft = 4096;

SFreeNode *fnSetFreeNode(uint32_t *pu32MemoryAddress, uint32_t u32SizeLeft, SFreeNode *pPreviousNode, SFreeNode *pNextNode, uint8_t u8Flag, uint32_t u32Size) {
	SFreeNode *pNewNode;
	if (u8Flag == 1) {
		pNewNode = (SFreeNode *) (pu32MemoryAddress + u32Size + 1);
	} else {
		pNewNode = (SFreeNode *) pu32MemoryAddress;
	}

	pNewNode->u32Size = u32SizeLeft;

	pNewNode->pPrevious = pPreviousNode;
	pNewNode->pNext = pNextNode;

	u32PageLeft = pNewNode->u32Size;

	return pNewNode;
}

uint32_t *malloc(uint32_t u32Size) {
	u32Size /= 4;

	SFreeNode *pCurrentNode = pHead;
	while (pCurrentNode != NULL) {
		if (pCurrentNode->u32Size > (u32Size * 4)) {
			break;
		}
		pCurrentNode = pCurrentNode->pNext;
	}

	SFreeNode *pNewNode;
	uint32_t *pu32MemoryAddress;

	uint32_t u32OldSize;
	if (pCurrentNode == NULL) {
		pu32MemoryAddress = fnAllocPage();
		pNewNode = fnSetFreeNode(pu32MemoryAddress, (4096 - (u32Size * 4 + sizeof(SFreeNode))), NULL, NULL, 1, u32Size);
	} else {
		pu32MemoryAddress = (uint32_t *) pCurrentNode;
		u32OldSize = pCurrentNode->u32Size;
		pCurrentNode->pPrevious->pNext = pCurrentNode->pNext;
		pCurrentNode->pNext->pPrevious = pCurrentNode->pPrevious;
		pNewNode = fnSetFreeNode(pu32MemoryAddress, (u32PageLeft - (u32Size * 4)), NULL, NULL, 1, u32Size);
	}

	if (u32LengthOfLinkedList < 2) {
		pTail = pNewNode;
		pHead = pNewNode;
	} else {
		pNewNode->pNext = pHead;
		pNewNode->u32Size =  (u32OldSize - (u32Size * 4));
		pHead->pPrevious = pNewNode;
		pHead = pNewNode;
	}

	*pu32MemoryAddress = u32Size * 4;

	return (pu32MemoryAddress + 1);
}

void free(uint32_t *pNode) {
	uint32_t u32Size = *(--pNode);

	SFreeNode *pNewNode = fnSetFreeNode(pNode, (u32Size - sizeof(SFreeNode)), NULL, NULL, 0, u32Size);

	pNewNode->pNext = pHead;
	pHead->pPrevious = pNewNode;
	pHead = pNewNode;

	u32LengthOfLinkedList++;
}

void fnPrintFreeList() {
	printf("PRINTING FREE LIST\n");
	SFreeNode *pCurrentNode = pHead;
	while (pCurrentNode != NULL) {
		printf("CURRENT NODE IS AT %x AND SIZE IS %d\n", pCurrentNode, pCurrentNode->u32Size);
		pCurrentNode = pCurrentNode->pNext;
	}
}