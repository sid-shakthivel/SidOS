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

void fnParseTar(uint32_t address)
{
	int i = 0;
	while (true)
	{
		rgfFileSystem[i] = (STarHeader *)address;
		STarHeader *pHeader = rgfFileSystem[i];
		pHeader->u32Address = address;

		if (pHeader->szFilename[0] == '\0')
			break;

		uint32_t u32Size = fnCalculateSize(pHeader->szSize);

		printf("FILENAME COULD BE %s\n", rgfFileSystem[i]->szFilename);

		if (u32Size == 0)
			pHeader->szIsFile = 1 - '0';

		address += ((u32Size / 512) + 1) * 512;

		if (u32Size % 512)
			address += 512;

		i++;
	}
}

uint32_t fnCalculateTarFileSize(uint32_t u32Address)
{
	uint32_t u32PreservedAddress = u32Address;
	while (true)
	{
		STarHeader *pHeader = (STarHeader *)u32Address;
		pHeader->u32Address = u32Address;

		if (pHeader->szFilename[0] == '\0')
			break;

		uint32_t u32Size = fnCalculateSize(pHeader->szSize);

		if (u32Size == 0)
			pHeader->szIsFile = 1 - '0';

		u32Address += ((u32Size / 512) + 1) * 512;

		if (u32Size % 512)
			u32Address += 512;
	}
	printf("ADDRESS IS %d\n", u32Address);
	return u32Address;
}

void fnPrintFileContents(STarHeader *pHeader)
{
	char *pcFileContent = "";
	uint32_t u32Size = fnCalculateSize(pHeader->szSize);
	strcpy((char *)pHeader->u32Address + 512, pcFileContent, u32Size);
	printf("FOUND FILE: %s\n CONTENTS: %s\n", pHeader->szFilename, pcFileContent);
}

void fnInitialiseFilesystem()
{
	// Remove the backslashes at the end of folders
	int i = 0;
	while (rgfFileSystem[i] != NULL)
	{
		STarHeader *pCurrentHeader = rgfFileSystem[i];
		printf("FILENAME IS %s\n", pCurrentHeader->szFilename);
		i++;
	}
}