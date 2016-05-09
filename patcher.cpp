/*
 * Copyright (C) 2016 Andrei Warkentin <andrey.warkentin@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <stdio.h>
#include "windows.h"
#include "ImageHlp.h"
#include "tchar.h"

static int
strcasecmp(const char *s1,
	   const char *s2)
{
  const u_char *us1 = (const u_char *) s1;
  const u_char *us2 = (const u_char *) s2;

  while (tolower(*us1) == tolower(*us2++)) {
    if (*us1++ == '\0') {
      return 0;
    }
  }

  return (tolower(*us1) - tolower(*--us2));
}

template <class T> PIMAGE_SECTION_HEADER
GetEnclosingSectionHeader(DWORD rva,
			  T* pNTHeader)
{
  unsigned i;
  PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(pNTHeader);

  for (i = 0; i < pNTHeader->FileHeader.NumberOfSections; i++, section++) {
    DWORD size = section->Misc.VirtualSize;
    if ( 0 == size ) {
      size = section->SizeOfRawData;
    }
  
    if ( (rva >= section->VirtualAddress) && 
	 (rva < (section->VirtualAddress + size))) {
      return section;
    }
  }
  
  return 0;
}

template <class T> LPVOID
GetPtrFromRVA(DWORD rva, T* pNTHeader,
	      PBYTE imageBase)
{
  int delta;
  PIMAGE_SECTION_HEADER pSectionHdr;

  pSectionHdr = GetEnclosingSectionHeader(rva, pNTHeader);
  if (!pSectionHdr) {
    return 0;
  }

  delta = (int) (pSectionHdr->VirtualAddress - pSectionHdr->PointerToRawData);
  return (PVOID) (imageBase + rva - delta);
}

static BOOL
PatchImports(char* name)
{
  LOADED_IMAGE image;

  if (!MapAndLoad(name, NULL, &image, FALSE, FALSE)) {
	  fprintf(stderr, "couldn't MapAndLoad '%s'\n", name);
	  return FALSE;
  }

  if (image.FileHeader->OptionalHeader.NumberOfRvaAndSizes >= 2) {
    PIMAGE_IMPORT_DESCRIPTOR importDesc =
      (PIMAGE_IMPORT_DESCRIPTOR) GetPtrFromRVA(
        image.FileHeader->OptionalHeader.DataDirectory[1].VirtualAddress,
	image.FileHeader,
	image.MappedAddress);
    while(1) {
      char *s;
      int len;

      // We've reached an empty IMAGE_IMPORT_DESCRIPTOR?
      if ((importDesc->TimeDateStamp == 0) && (importDesc->Name==0)) {
	break;
      }

      s = (char *) GetPtrFromRVA(importDesc->Name,
				 image.FileHeader,
				 image.MappedAddress);

      len = strlen(s);
      if (!strcasecmp(s, "kernel32.dll") ||
	  !strcasecmp(s, "msvcrt.dll") ||
	  !strcasecmp(s, "user32.dll") ||
	  !strcasecmp(s, "gdi32.dll") ||
	  !strcasecmp(s, "ole32.dll") ||
	  !strcasecmp(s, "advapi32.dll") ||
	  !strcasecmp(s, "comctl32.dll") ||
	  !strcasecmp(s, "ntdll.dll")) {
	printf("...patching %s ->", s);
	s[len - 5] = '_';
	printf(" %s\n", s);
      }
	  
      importDesc++;
    }
  }

  UnMapAndLoad(&image);
  return TRUE;
}

int
main(int argc,
     char **argv) 
{
  char *prog;

  if (argc < 2) {
    fprintf(stderr, "usage: %s exe-to-patch\n", argv[0]);
    return -1;
  } else {
	prog = argv[1];
  }

  if (!PatchImports(prog)) {
	fprintf(stderr, "patching failed\n");
    return -1;
  }

  printf("done\n");
  return 0;
}
