#pragma comment(linker,"/entry:DllMain@12")

#include "common.h"
#include "comctl32-forwards.h"

#pragma LINKER_CDECL_REEXPORT(InitCommonControlsEx)

typedef VOID (*InitCommonControlsProc)(VOID);
InitCommonControlsProc MyInitCommonControls;

typedef PVOID LPINITCOMMONCONTROLSEX;
BOOL
MyInitCommonControlsEx(
		       _In_ const LPINITCOMMONCONTROLSEX lpInitCtrls
		       )
{
  MyInitCommonControls();
  return TRUE;
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
    MyInitCommonControls = (InitCommonControlsProc) GetProcAddress(GetModuleHandle(TEXT("comctl32.dll")), "InitCommonControls");
    break;
      
  case DLL_PROCESS_DETACH:
    return FALSE;
    break;
  }

  return TRUE;
}
