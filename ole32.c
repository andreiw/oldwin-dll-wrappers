#pragma comment(linker,"/entry:DllMain@12")

#include "common.h"
#include "ole32-forwards.h"

#pragma LINKER_CDECL_REEXPORT(CoInitializeEx)

HRESULT
MyCoInitializeEx(
		 _In_opt_ LPVOID pvReserved,
		 _In_     DWORD  dwCoInit
		 )
{
  return CoInitialize(NULL);
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
