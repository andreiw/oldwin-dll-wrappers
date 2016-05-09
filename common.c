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
#include "common.h"

NtOpenThreadProc NtOpenThread;
RtlNtStatusToDosErrorProc RtlNtStatusToDosError;

VOID
ProcessImports(
	       VOID
	       )
{
  NtOpenThread = (NtOpenThreadProc) GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtOpenThread");
  RtlNtStatusToDosError = (RtlNtStatusToDosErrorProc) GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "RtlNtStatusToDosError");
}

VOID
PopupMessage(
	     _In_ LPCTSTR lpszText
	     )
{
  MSGBOXPARAMS          m;

  m.cbSize             = sizeof(m);
  m.hwndOwner          = NULL;
  m.lpszCaption        = _T("wrapper");
  m.dwStyle            = MB_OK;
  m.hInstance          = NULL;
  m.lpszIcon           = IDI_ERROR;
  m.dwContextHelpId    = 0;
  m.lpfnMsgBoxCallback = NULL;
  m.dwLanguageId       = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);

  m.lpszText = lpszText;
  MessageBoxIndirect(&m);
}
