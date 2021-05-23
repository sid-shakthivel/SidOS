#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/multiboot.h"
#include "../include/page_frame_allocator.h"
#include "../include/vga_text.h"

typedef struct Page
{
	struct Page *next;
} page;

typedef struct Linked_List
{
	page *head;
	page *tail;
} linked_list;

uint32_t *pCurrentMemoryLocation;
uint32_t *pEndMemoryLocation;

linked_list *linked_list_t;
uint32_t *pLengthOfLinkedList;

void push(page *pTest);
uint32_t *pop();

void initialize_page_frame_allocator(uint32_t start_memory_location, uint32_t final_memory_location)
{
	pCurrentMemoryLocation = (uint32_t *) start_memory_location;
	*pCurrentMemoryLocation = (uint32_t) (((uint32_t *) start_memory_location) + 5);

	pEndMemoryLocation = ((uint32_t *) start_memory_location) + 1;
	*pEndMemoryLocation = final_memory_location;

	pLengthOfLinkedList = ((uint32_t *) start_memory_location) + 2;
	*pLengthOfLinkedList = 0;

	linked_list_t = (linked_list *) (((uint32_t *) start_memory_location) + 3);
}

uint32_t *allocate_page(void)
{
	if ((*pCurrentMemoryLocation + 4096) > *pEndMemoryLocation)
		return (uint32_t *)-1;

	if (*pLengthOfLinkedList == 0)
	{
		*pCurrentMemoryLocation = *pCurrentMemoryLocation + 4096;

		return (uint32_t *)(*pCurrentMemoryLocation - 4096);
	}

	return pop();
}

void free_page(size_t *memory_location_pointer)
{
	page newPage, *pPage;

	newPage.next = NULL;

	pPage = (page *)memory_location_pointer;

	*pPage = newPage;

	push(pPage);
}

void push(page *pPage)
{
	if (*pLengthOfLinkedList == 0)
	{
		linked_list_t->head = pPage;
		linked_list_t->tail = pPage;
	}
	else
	{
		linked_list_t->tail->next = pPage;
	}

	(*pLengthOfLinkedList) = (*pLengthOfLinkedList) + 1;
}

uint32_t *pop()
{
	page *new_head = linked_list_t->head->next;
	uint32_t *current_head = (uint32_t *)linked_list_t->head;
	linked_list_t->head = new_head;
	return current_head;
}

