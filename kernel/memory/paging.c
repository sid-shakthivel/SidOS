#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/multiboot.h"
#include "../include/paging.h"
#include "../include/vga_text.h"

typedef struct multiboot_segment
{
    unsigned int size;
    unsigned long long int addr;
    unsigned long long int length;
    unsigned int type;
} multiboot_segment_t;

unsigned int calculate_max_memory(multiboot_info_t *mbd)
{
    multiboot_segment_t *entry = (multiboot_segment_t *)(mbd->mmap_addr);

    uint32_t max_memory = 0;

    while ((multiboot_uint32_t)entry < mbd->mmap_addr + mbd->mmap_length)
    {
        if (entry->addr == 0x100000)
        {
            max_memory = (uint32_t)entry->addr + (uint32_t)entry->length;
            break;
        }
        entry = (multiboot_segment_t *)((unsigned int)entry + entry->size + sizeof(entry->size));
    }

    return max_memory;
}

int *pCurrentMemoryLocation;
int *end_memory_location;

struct page
{
    struct page *next;
};

struct linked_list
{
    struct page *head;
    struct page *tail;
};

struct linked_list *linked_list_t;
int length_of_linked_list;

void push(struct page *pTest)
{
    if (length_of_linked_list == 0)
    {
        linked_list_t->head = pTest;
        linked_list_t->tail = pTest;
    }
    else
    {
        linked_list_t->tail->next = pTest;
    }

    length_of_linked_list++;
}

int *pop()
{
    struct page *new_head = linked_list_t->head->next;
    int *current_head = (int *)linked_list_t->head;
    linked_list_t->head = new_head;
    return current_head;
}

void initialize_paging(int start_memory_location, int final_memory_location)
{
    length_of_linked_list = 0;

    pCurrentMemoryLocation = (int *)start_memory_location;

    *end_memory_location = final_memory_location;
}

int *allocate_page()
{
    if (length_of_linked_list == 0 && (*pCurrentMemoryLocation + 1024) < *end_memory_location)
    {
        // Move pointer by 4KiB
        pCurrentMemoryLocation = pCurrentMemoryLocation + 1024;

        // Return pointer to previous memory location
        return (int *)(pCurrentMemoryLocation - 1024);
    }

    // Pop off linked list, and return the pointer
    return pop();
}

void free_page(int *memory_location_pointer)
{
    // Make new struct
    struct page newPage;

    // Set next node to NULL
    newPage.next = NULL;

    // We need a pointer that is AT the memory location
    struct page *pTest;

    // Set pointer to memory location
    pTest = (struct page *)memory_location_pointer;

    // Set the value in that memory location to the struct
    *pTest = newPage;

    push(pTest);
}