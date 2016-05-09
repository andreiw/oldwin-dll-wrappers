#pragma comment(linker,"/entry:DllMain@12")

#include "common.h"
#include "advapi32-forwards.h"

#pragma LINKER_REEXPORT(CheckTokenMembership, 12)

BOOL WINAPI
MyCheckTokenMembership(
		     _In_opt_ HANDLE TokenHandle,
		     _In_     PSID   SidToCheck,
		     _Out_    PBOOL  IsMember
		     )
{
  PopupMessage(_T("CheckTokenMembership"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
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
