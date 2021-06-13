#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/filesystem.h"
#include "../include/vga_text.h"
#include "../include/string.h"
#include "../include/memory.h"

STarHeader *rgfFileSystem[32];

uint32_t fnCalculateSize(char *pSize)
{
	uint32_t u32Size = 0;
	int count = 1;
	for (int j = 11; j > 0; j--, count *= 8)
		u32Size += ((pSize[j - 1] - '0') * count);
	return u32Size;
}

uint32_t fnEndOfTarBall(uint32_t address)
{
	while (true)
	{
		char *test = (char *)address;
		STarHeader *pHeader = (STarHeader *)address;

		if (pHeader->szFilename[0] == '\0')
		{
			printf("ISSUE\n");
			break;
		}

		printf("FILENAME IS %s\n", pHeader->szFilename);

		pHeader->u32Address = address;

		uint32_t u32Size = fnCalculateSize(pHeader->szSize);

		if (u32Size == 0)
			pHeader->szIsFile = 1 - '0';

		address += ((u32Size / 512) + 1) * 512;

		if (u32Size % 512)
			address += 512;
	}
	return address;
}

void fnInitialiseFilesystem()
{
	// Remove the backslashes at the end of folders
}