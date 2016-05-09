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
#pragma comment(linker,"/entry:DllMain@12")

#include "common.h"
#include "msvcrt-forwards.h"

#pragma LINKER__CDECL_REEXPORT(_wcserror)
#pragma LINKER__CDECL_REEXPORT(_fstat64)

int __cdecl
My_fstat64( 
	   _In_ int fd,
	   _Out_ void *stat
	    )
{
  PopupMessage(_T("_fstat64"));
  return -1;
}
  
wchar_t * __cdecl
My_wcserror(int errnum)
{
  PopupMessage(_T("_wcserror"));
  return L"<dummy error";
}

BOOL WINAPI
DllMain(
	_In_ HINSTANCE self,
	_In_ DWORD reason,
	_In_ LPVOID junk
	)
{
  switch (reason) {
  case DLL_PROCESS_ATTACH:
    ProcessImports();
    break;
      
  case DLL_PROCESS_DETACH:
    return FALSE;
    break;
  }

  return TRUE;
}
