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

uint32_t u32PageLeft = 4096;

void fnSetFreeNode(SFreeNode *pFreeNode, uint32_t u32Size,SFreeNode *pPreviousNode, SFreeNode *pNextNode) {
	pFreeNode->u32Size = u32Size;

	pFreeNode->pPrevious = pPreviousNode;
	pFreeNode->pNext = pNextNode;

	u32PageLeft = pFreeNode->u32Size;
}

uint32_t *malloc(uint32_t u32Size) {
	u32Size /= 4;

//	Get first node that fits

	SFreeNode *pCurrentNode = pHead;
	while (pCurrentNode != NULL) {
		if (pCurrentNode->u32Size >= u32Size) {
			break;
		}
		pCurrentNode = pCurrentNode->pNext;
	}

	if (pCurrentNode == NULL) {
		uint32_t *pu32MemoryAddress = fnAllocPage();

//		Set free node
		SFreeNode *pNewNode = (SFreeNode *) (pu32MemoryAddress + u32Size + 1);
		fnSetFreeNode(pNewNode, (4096 - (u32Size * 4 + sizeof(SFreeNode))), NULL, NULL);
		pTail = pNewNode;
		pHead = pNewNode;

		*pu32MemoryAddress = u32Size;

		u32PageLeft = pNewNode->u32Size;

		printf("PAGES LEFT IS %d\n", u32PageLeft);

		return (pu32MemoryAddress + 1);
	}

//	Clear Old Node
	fnSetFreeNode(pCurrentNode, u32PageLeft, NULL, NULL);

//	Setup new node
	uint32_t *pu32MemoryAddress = (uint32_t *) pCurrentNode;

	*pu32MemoryAddress = u32Size;
	pu32MemoryAddress += 1;

	SFreeNode *pNewNode = (SFreeNode *) (pu32MemoryAddress + u32Size);

	fnSetFreeNode(pNewNode, (u32PageLeft - (u32Size * 4 + sizeof(SFreeNode))), NULL, NULL);

	printf("PAGES LEFT IS %d\n", u32PageLeft);

	pTail = pNewNode;
	pHead = pNewNode;

	u32PageLeft = pNewNode->u32Size;

	return pu32MemoryAddress;
}

void free(uint32_t *pNode) {
	uint32_t u32Size = *(--pNode);

//	Setup new node
	SFreeNode *pNewNode = (SFreeNode *) pNode;

	fnSetFreeNode(pNewNode, u32Size, pTail, NULL);

	pTail->pNext = pNewNode;
	pTail = pNewNode;
}

void fnPrintFreeList() {
	printf("PRINTING FREE LIST\n");
	SFreeNode *pCurrentNode = pHead;
	while (pCurrentNode != NULL) {
		printf("CURRENT NODE IS AT %x AND SIZE IS %d\n", pCurrentNode, pCurrentNode->u32Size);
		pCurrentNode = pCurrentNode->pNext;
	}
}