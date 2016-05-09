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
