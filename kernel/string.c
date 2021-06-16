#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "include/string.h"
#include "include/vga_text.h"

uint32_t strlen(char *szString)
{
	uint32_t i = 0;
	while (szString[i] != '\0')
	{
		i++;
	}
	return i;
}

bool strcmp(char *pcStringOne, char *pcStringTwo)
{
	uint32_t u32LengthOfStringOne = strlen(pcStringOne);
	uint32_t u32LengthOfStringTwo = strlen(pcStringTwo);

	if (u32LengthOfStringOne != u32LengthOfStringTwo)
	{
		return false;
	}

	for (uint32_t i = 0; i < u32LengthOfStringOne; i++)
	{
		if (pcStringOne[i] != pcStringTwo[i])
		{
			return false;
		}
	}

	return true;
}

// src, dest
void strcpy(char *pcSrc, char *pcDest, uint32_t u32Size)
{
	for (uint32_t i = 0; i < u32Size; i++)
		pcDest[i] = pcSrc[i];
}

void memcpy(void *pDest, void *pSrc, uint32_t u32Limit)
{
	char *prgcSrc = (char *)pSrc;
	char *prgcDest = (char *)pDest;

	for (uint32_t i = 0; i < u32Limit; i++)
		prgcDest[i] = prgcSrc[i];
}

void substr(char *pcDest, char *pcSrc, uint32_t u32Start, uint32_t u32End)
{
	uint32_t j = 0;
	uint32_t i = u32Start;
	while (i < u32End)
	{
		pcDest[j] = pcSrc[i];
		i++;
		j++;
	}
	pcDest[j++] = '\0';
}

//void substr(char *destination, const char *source, int beg, int n)
//{
//	while (n > 0)
//	{
//		*destination = *(source + beg);
//
//		destination++;
//		source++;
//		n--;
//	}
//
//	*destination = '\0';
//}