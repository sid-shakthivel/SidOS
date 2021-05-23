#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/paging.h"
#include "../include/vga_text.h"
#include "../include/multiboot.h"

extern uint32_t __kernel_end;

extern void enablePaging();
extern void loadPageDirectory(uint32_t *pd);

typedef struct multiboot_segment
{
	unsigned int size;
	unsigned long long int addr;
	unsigned long long int length;
	unsigned int type;
} multiboot_segment_t;

uint32_t *page_directory;
uint32_t *page_tables;

uint32_t number_of_directory_entries = 1024;
uint32_t number_of_table_entries = 1024;

void set_entry(uint32_t *location, uint32_t memory_location, uint8_t is_kernel, uint8_t is_writeable) {
	*location = memory_location & 0xFFFFF000;

	//	Setting Cache Disable Bit To 1
	*location |= 1 << 4;

	*location |= is_kernel << 2;
	*location |= is_writeable << 1;

	//	Setting Present Bit To 1
	*location |= 1 << 0;
}

void identity_map()
{
	//	Set Up Page Directory With Page Table Entries

	uint32_t current_page_table = (uint32_t)page_tables;

	for (uint32_t *current_page_directory_entry = page_directory; current_page_directory_entry < page_tables; ++current_page_directory_entry)
	{
		set_entry(current_page_directory_entry, current_page_table, 1, 1);
		current_page_table += 4096;
	}

	// Setup Page Tables - Map All Physical Addresses To Virtual Ones

	for (uint32_t current_memory_address = 0; current_memory_address < 0x00000000021acfff; ++current_memory_address)
	{
		uint32_t *index = (uint32_t *)page_tables + (current_memory_address / 4096);
		set_entry(index, current_memory_address, 1, 1);
	}
}

uint32_t initialize_paging()
{
	page_directory = (uint32_t *)&__kernel_end;
	page_tables = page_directory + number_of_directory_entries;

	identity_map();

	loadPageDirectory(page_directory);
	enablePaging();

	return (uint32_t) &__kernel_end + (1024 * 4) + (1024 * 4 * 1024);
}

size_t calculate_max_memory(multiboot_info_t *mbd)
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
		entry = (multiboot_segment_t *)((size_t)entry + entry->size + sizeof(entry->size));
	}

	return max_memory;
}