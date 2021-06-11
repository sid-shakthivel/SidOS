#ifndef TESOS_FILESYSTEM_H
#define TESOS_FILESYSTEM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

typedef struct STarHeader {
	char szFilename[100];
	char szFileMode[8];
	char szUID[8];
	char szGID[8];
	char szSize[12];
	char szLastMod[12];
	char szChecksum[8];
	char szLinkIndicator[1];
	uint32_t u32Address;
} STarHeader;

extern STarHeader *rgfFileSystem[16];

void fnParseTar(uint32_t address);

void fnPrintFileContents(STarHeader *pHeader);

#endif //TESOS_FILESYSTEM_H