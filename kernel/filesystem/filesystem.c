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

uint32_t fnCalculateEndOfTarball(uint32_t address)
{
	int i = 0;
	while (true)
	{
		STarHeader *pHeader = (STarHeader *)address;

		if (pHeader->szFilename[0] == '\0')
			break;

		pHeader->u32Address = address;

		uint32_t u32Size = fnCalculateSize(pHeader->szSize);

		if (u32Size == 0)
			pHeader->szIsFile = 1 - '0';

		address += ((u32Size / 512) + 1) * 512;

		rgfFileSystem[i] = pHeader;

		if (u32Size % 512)
			address += 512;

		i++;
	}
	return address;
}

void fnInitialiseFilesystem()
{
	uint32_t i = 0;
	STarHeader *pCurrentHeader;
	uint32_t u32SizeOfString;
	uint32_t u32LastSlash = 0;
	while (rgfFileSystem[i] != NULL)
	{
		pCurrentHeader = rgfFileSystem[i];
		u32SizeOfString = strlen(pCurrentHeader->szFilename);
		if (pCurrentHeader->szFilename[u32SizeOfString - 1] == '/')
			--u32SizeOfString;

		u32LastSlash = 0;
		for (uint32_t i = 0; i < u32SizeOfString; i++) {
			if (pCurrentHeader->szFilename[i] == '/')
				u32LastSlash = i;
		}

		char *filename = "";
		substr(filename, pCurrentHeader->szFilename, i == 0 ? u32LastSlash : u32LastSlash+1, u32SizeOfString);
		printf("FILENAME IS %s\n", filename);

		i++;
	}
}