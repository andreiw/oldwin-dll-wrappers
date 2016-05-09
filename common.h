#ifndef COMMON_H
#define COMMON_H

#ifndef _DLL
#error "_DLL is not defined."
#endif

#define _In_opt_
#define _Inout_
#define _Out_
#define _Out_opt_
#define _In_

#define UNICODE
#define _UNICODE

#if defined(WIN32) && !defined(_WIN32)
#define _WIN32
#endif

#define _S(x) #x
#define S(x) _S(x)
#define REEXPORT(x, args) "/export:"S(x)"=_My"S(x)"@"S(args)
#define _CDECL_REEXPORT(x) "/export:_"S(x)"=_My"S(x)
#define CDECL_REEXPORT(x) "/export:"S(x)"=_My"S(x)
#define LINKER_REEXPORT(x, args) comment(linker, REEXPORT(x, args))
#define LINKER__CDECL_REEXPORT(x) comment(linker, _CDECL_REEXPORT(x))
#define LINKER_CDECL_REEXPORT(x) comment(linker, CDECL_REEXPORT(x))

#include <windows.h>
#include <winbase.h>
#include <winnt.h>
#include <tchar.h>
#include "ntdefs.h"

VOID
PopupMessage(
	     _In_ LPCTSTR lpszText
	     );

VOID
ProcessImports(
	       VOID
	       );

extern NtOpenThreadProc NtOpenThread;
extern RtlNtStatusToDosErrorProc RtlNtStatusToDosError;

#endif /* COMMON_H */
