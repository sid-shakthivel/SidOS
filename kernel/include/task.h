#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef struct STask
{
	char *szName;
	uint32_t *pu32ESP;
	struct STask *pNext;
	struct STask *pPrevious;
} STask;

typedef struct SLinkedList {
	STask *pHead;
	STask *pTail;
	uint32_t u32Length;
} SLinkedList;

STask *fnCreateNewTask(char *szName, int(*fnFunc)());

extern SLinkedList *LinkedListOfTasks;

void fnInitialiseTasks();

STask *fnReturnNewTask();

void fnLoopThroughLinkedList();

#endif