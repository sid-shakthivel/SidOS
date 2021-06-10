#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/filesystem.h"
#include "../include/vga_text.h"
#include "../include/string.h"

STarHeader *rgfFileSystem[16];

uint32_t fnCalculateSize(char *pSize) {
	uint32_t u32Total = 0;
	for (int i = 0; i < 11; i++) {
		u32Total += *(pSize + i);
	}
	return u32Total;
}

void fnParseTar(uint32_t address) {
	uint32_t i = 0;

	while (true) {
		STarHeader *pHeader = (STarHeader *) address;
		pHeader->u32Address = address;

		if (pHeader->szFilename[0] == '\0')
			break;

		rgfFileSystem[i] = pHeader;

		uint32_t u32Size = fnCalculateSize(pHeader->szSize);

		address += ((u32Size / 512) + 1) * 512;

		i++;
	}
}

void fnPrintFileContents(STarHeader *pHeader) {
	char *pcFileContent = "";
	uint32_t u32Size = fnCalculateSize(pHeader->szSize);
	strcpy((char *) pHeader->u32Address + 512, pcFileContent, u32Size);
	printf("FOUND FILE: %s\n CONTENTS: %s\n", pHeader->szFilename, pcFileContent);
}