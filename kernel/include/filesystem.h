#ifndef TESOS_FILESYSTEM_H
#define TESOS_FILESYSTEM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

typedef struct STarHeader
{
	char szFilename[100];
	char szFileMode[8];
	char szUID[8];
	char szGID[8];
	char szSize[12];
	char szLastMod[12];
	char szChecksum[8];
	char szLinkIndicator[1];
	uint8_t u8IsFile; // 0 for file and 1 for directory
	struct STarHeader **pNextHeader;
	struct STarHeader *pPreviousHeader;
	char szFormattedFilename[100];
	uint32_t u32Index;
} STarHeader;

extern STarHeader *rgfFileSystem[32];
void fnPrintFileContents(STarHeader *pHeader);
uint32_t fnCalculateEndOfTarball(uint32_t address);
void fnInitialiseFilesystem();
uint32_t fnGetIndex(char *name);

#endif //TESOS_FILESYSTEM_H