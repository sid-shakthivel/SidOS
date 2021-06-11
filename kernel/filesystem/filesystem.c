#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/filesystem.h"
#include "../include/vga_text.h"
#include "../include/string.h"

STarHeader *rgfFileSystem[16];

uint32_t fnCalculateSize(char *pSize) {
	uint32_t u32Size = 0;
	int count = 1;
	for (int j = 11; j > 0; j--, count *= 8)
		u32Size += ((pSize[j - 1] - '0') * count);
	return u32Size;
}

void fnParseTar(uint32_t address) {
	uint32_t i = 0;

	while (true) {
		STarHeader *pHeader = (STarHeader *) address;
		pHeader->u32Address = address;

		if (pHeader->szFilename[0] == '\0')
			break;

		uint32_t u32Size = fnCalculateSize(pHeader->szSize);

		printf("%s ", pHeader->szFilename);

		if (u32Size == 0) {
			printf("ITS A FOLDER\n");
		} else {
			printf("ITS A FILE\n");
		};

		address += ((u32Size / 512) + 1) * 512;

		if (u32Size % 512)
			address += 512;

		i++;
	}
}

void fnPrintFileContents(STarHeader *pHeader) {
	char *pcFileContent = "";
	uint32_t u32Size = fnCalculateSize(pHeader->szSize);
	strcpy((char *) pHeader->u32Address + 512, pcFileContent, u32Size);
	printf("FOUND FILE: %s\n CONTENTS: %s\n", pHeader->szFilename, pcFileContent);
}