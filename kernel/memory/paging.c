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

uint32_t bitExtracted(int number, int k, int p)
{
	return (((1 << k) - 1) & (number >> (p - 1)));
}

uint32_t get_len_of_hex(uint32_t hex)
{
	int i = 0;
	while (hex != 0)
	{
		i++;
		hex = hex / 16;
	}
	return i;
}

void set_page_directory_entry(uint32_t *location, uint32_t page_table_location, uint8_t is_kernel, uint8_t is_writeable)
{
	//	Page Align Our Page Table Location
	switch (get_len_of_hex(page_table_location))
	{
		case 6:
			page_table_location = page_table_location << 8 & 0xFFFFF000;
			break;
		case 7:
			page_table_location = page_table_location << 4 & 0xFFFFF000;
			break;
		default:
			break;
	}

	//	Make Sure Entry Is 0xFFFFFFFF
	*location = 0xFFFFF000;

	//	Setting Page Table Address
	*location = (*location & page_table_location);

	//	Setting Cache Disable Bit To 1
	*location |= 1 << 4;

	*location |= is_kernel << 2;
	*location |= is_writeable << 1;

	//	Setting Present Bit To 1
	*location |= 1 << 0;
}

void set_page_table_entry(uint32_t *location, uint32_t physical_memory_location, uint8_t is_kernel, uint8_t is_writeable)
{
	//	Page Align Physical Memory Location

	switch (get_len_of_hex(physical_memory_location))
	{
		case 6:
			physical_memory_location = (physical_memory_location << 8) & 0xFFFFF000;
			break;
		case 7:
			physical_memory_location = (physical_memory_location << 4) & 0xFFFFF000;
			break;
		default:
			break;
	}

	//	Make Sure Entry Is 0xFFFFFFFF
	*location = 0xFFFFF000;

	//	Setting Page Table Address
	*location = (*location & (uint32_t)physical_memory_location);

	//	Setting Cache Disable Bit To 1
	*location |= 1 << 4;

	*location |= is_kernel << 2;
	*location |= is_writeable << 1;

	//	Setting Present Bit To 1
	*location |= 1 << 0;
}

void identity_map(uint32_t maximum_memory)
{
//	uint32_t *start_of_usable_memory = page_tables + (number_of_table_entries * number_of_table_entries);

	//	Set Up Page Directory With Page Table Entries

	uint32_t current_page_table_address = (uint32_t)page_tables;

	for (uint32_t *current_memory_address = page_directory; current_memory_address < page_tables; ++current_memory_address)
	{
		set_page_directory_entry(current_memory_address, current_page_table_address, 1, 1);
		current_page_table_address += 4096;
	}

	// Setup Page Tables - Map All Physical Addresses To Virtual Ones

	for (uint32_t *current_memory_address = 0; (uint32_t) current_memory_address < maximum_memory; current_memory_address++)
	{
		uint32_t* index = page_tables + ((uint32_t) current_memory_address / 4096);
		set_page_table_entry(index, (uint32_t)current_memory_address, 1, 1);
	}
}

uint32_t initialize_paging(uint32_t maximum_memory)
{
	//	Initialise Page Directory and Page Table to Their Respective Locations
	page_directory = (uint32_t *)&__kernel_end;
	page_tables = page_directory + number_of_directory_entries;

	identity_map(maximum_memory);

	loadPageDirectory(page_directory);
//	enablePaging();

	return 1;
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