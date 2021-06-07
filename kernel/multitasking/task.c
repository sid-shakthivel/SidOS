#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/task.h"
#include "../include/page_frame_allocator.h"
#include "../include/string.h"
#include "../include/vga_text.h"
#include "../include/memory.h"
#include "../include/string.h"
#include "../include/timer.h"

SLinkedList *LinkedListOfTasks;
STask *pCurrentTask;

void fnInitialiseTasks() {
	LinkedListOfTasks = (SLinkedList *) malloc(sizeof(SLinkedList));
}

STask *fnCreateNewTask(char *szName, int(*fnFunc)())
{
	STask *pNewTask = (STask *) malloc(sizeof(STask));
	pNewTask->szName = szName;
	pNewTask->szStatus = "STARTED";

	uint32_t *pu32ESP = (uint32_t *)fnAllocPage() + 512;
	pNewTask->pu32ESP = (uint32_t *)pu32ESP - 14;

	//	IRET Stuff
	*(--pu32ESP) = 0; // Stack Alignment
	*(--pu32ESP) = 0x10; // SS
	*(--pu32ESP) = (uint32_t)pNewTask->pu32ESP; // ESP
	*(--pu32ESP) = 0x202; // EFLAGS
	*(--pu32ESP) = 0x8; // CS
	*(--pu32ESP) = (uint32_t) fnFunc; // EIP

//	General Registers
	*(--pu32ESP) = 0; // EAX
	*(--pu32ESP) = 0; // ECX
	*(--pu32ESP) = 0; // EDX
	*(--pu32ESP) = 0; // EBX
	*(--pu32ESP) = 0; // ESP
	*(--pu32ESP) = (uint32_t)pNewTask->pu32ESP; // EBP
	*(--pu32ESP) = 0; // ESI
	*(--pu32ESP) = 0; // EDI

	if (LinkedListOfTasks->u32Length == 0) {
		LinkedListOfTasks->pHead = pNewTask;
		LinkedListOfTasks->pTail = pNewTask;
	} else {
		pNewTask->pNext = NULL;
		pNewTask->pPrevious = LinkedListOfTasks->pTail;
		LinkedListOfTasks->pTail->pNext = pNewTask;
		LinkedListOfTasks->pTail = pNewTask;
	}

	LinkedListOfTasks->u32Length++;

	pCurrentTask = LinkedListOfTasks->pHead->pNext;

	return pNewTask;
}

STask *fnReturnNewTask() {
	if (LinkedListOfTasks->u32Length <= 1) {
		return NULL;
	}

	if (pCurrentTask->pNext == NULL) {
		pCurrentTask = LinkedListOfTasks->pHead;
	} else {
		pCurrentTask = pCurrentTask->pNext;
	}
	return pCurrentTask;
}

void fnDeleteTask(char *szName) {
	--LinkedListOfTasks->u32Length;

	STask *pCurrentTask = LinkedListOfTasks->pHead->pNext;

	if (strcmp(LinkedListOfTasks->pHead->szName, szName)) {
		STask *pOldHead = LinkedListOfTasks->pHead;
		LinkedListOfTasks->pHead = LinkedListOfTasks->pHead->pNext;
		LinkedListOfTasks->pHead->pPrevious = NULL;
		free((uint32_t *)pOldHead);
		return;
	}

	if (strcmp(LinkedListOfTasks->pTail->szName, szName)) {
		LinkedListOfTasks->pTail = LinkedListOfTasks->pTail->pPrevious;
		free((uint32_t *)pCurrentTask);
		return;
	}

	while (pCurrentTask != NULL) {
		if (strcmp(szName, pCurrentTask->szName)) {
			pCurrentTask->pPrevious->pNext = pCurrentTask->pNext;
			pCurrentTask->pNext->pPrevious = pCurrentTask->pPrevious;
			free((uint32_t *)pCurrentTask);
		}
		pCurrentTask = pCurrentTask->pNext;
	}
}

void fnLoopThroughLinkedList() {
	STask *pCurrent = LinkedListOfTasks->pHead;
	while (pCurrent != NULL) {
		printf(pCurrent->szName);
		printf("\n");
		pCurrent = pCurrent->pNext;
	}
}

void fnExit() {
	pOldTask->szStatus = "STOP";
	asm volatile ("int $0x20");
}