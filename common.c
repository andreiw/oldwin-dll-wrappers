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
