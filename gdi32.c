#pragma comment(linker,"/entry:DllMain@12")

#include "common.h"
#include "gdi32-forwards.h"

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
