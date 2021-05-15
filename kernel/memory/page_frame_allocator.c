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

size_t *pCurrentMemoryLocation;
size_t *pEndMemoryLocation;

linked_list *linked_list_t;
size_t *pLengthOfLinkedList;

void push(page *pTest);
size_t *pop();

void initialize_page_frame_allocator(size_t start_memory_location, size_t final_memory_location)
{
	// Stores pointer to current memory location at end of kernel code
	pCurrentMemoryLocation = (size_t *)start_memory_location;

	pEndMemoryLocation = (size_t *)((size_t)pCurrentMemoryLocation + 4);

	pLengthOfLinkedList = (size_t *)((size_t)pCurrentMemoryLocation + 8);

	linked_list_t = (linked_list *)((size_t)pCurrentMemoryLocation + 12);

	*pCurrentMemoryLocation = ((size_t)pCurrentMemoryLocation + 20);

	*pEndMemoryLocation = final_memory_location;

	*pLengthOfLinkedList = 0;
}

size_t *allocate_page(void)
{
	if ((*pCurrentMemoryLocation + 4096) > *pEndMemoryLocation)
		return (size_t *)-1;

	if (*pLengthOfLinkedList == 0)
	{
		// Move pointer by 4KiB
		*pCurrentMemoryLocation = *pCurrentMemoryLocation + 4096;

		// Return pointer to previous memory location
		return (size_t *)(*pCurrentMemoryLocation - 4096);
	}

	// Pop off linked list, and return the pointer
	return pop();
}

void free_page(size_t *memory_location_pointer)
{
	// Make new struct
	page newPage;

	// Set next node to NULL
	newPage.next = NULL;

	// We need a pointer that is AT the memory location
	page *pTest;

	// Set pointer to memory location
	pTest = (page *)memory_location_pointer;

	// Set the value in that memory location to the struct
	*pTest = newPage;

	// Push to linked list
	push(pTest);
}

void push(page *pTest)
{
	if (*pLengthOfLinkedList == 0)
	{
		linked_list_t->head = pTest;
		linked_list_t->tail = pTest;
	}
	else
	{
		linked_list_t->tail->next = pTest;
	}

	(*pLengthOfLinkedList) = (*pLengthOfLinkedList) + 1;
}

size_t *pop()
{
	page *new_head = linked_list_t->head->next;
	size_t *current_head = (size_t *)linked_list_t->head;
	linked_list_t->head = new_head;
	return current_head;
}

