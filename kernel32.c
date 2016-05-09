#pragma comment(linker,"/entry:DllMain@12")

#include "common.h"
#include "kernel32-forwards.h"

#pragma LINKER_REEXPORT(AttachConsole, 4)
#pragma LINKER_REEXPORT(CancelIo, 4)
#pragma LINKER_REEXPORT(FindFirstVolumeW, 8)
#pragma LINKER_REEXPORT(FindNextVolumeW, 12)
#pragma LINKER_REEXPORT(FindVolumeClose, 4)
#pragma LINKER_REEXPORT(GetComputerNameExA, 12)
#pragma LINKER_REEXPORT(GetConsoleWindow, 0)
#pragma LINKER_REEXPORT(GetFileSizeEx, 8)
#pragma LINKER_REEXPORT(QueueUserAPC, 12)
#pragma LINKER_REEXPORT(GetModuleHandleExW, 12)
#pragma LINKER_REEXPORT(GetSystemWindowsDirectoryW, 8)
#pragma LINKER_REEXPORT(GetSystemWindowsDirectoryA, 8)
#pragma LINKER_REEXPORT(GetSystemWow64DirectoryW, 8)
#pragma LINKER_REEXPORT(GetVolumeNameForVolumeMountPointW, 12)
#pragma LINKER_REEXPORT(GetVolumePathNamesForVolumeNameW, 16)
#pragma LINKER_REEXPORT(GlobalMemoryStatusEx, 4)
#pragma LINKER_REEXPORT(IsProcessInJob, 12)
#pragma LINKER_REEXPORT(OpenThread, 12)
#pragma LINKER_REEXPORT(SwitchToThread, 0)
#pragma LINKER_REEXPORT(RtlCaptureContext, 4)
#pragma LINKER_REEXPORT(QueryInformationJobObject, 20)
#pragma LINKER_REEXPORT(SetComputerNameExW, 8)
#pragma LINKER_REEXPORT(SetFilePointerEx, 20)
#pragma LINKER_REEXPORT(GetSystemDefaultUILanguage, 0)
#pragma LINKER_REEXPORT(GetUserDefaultUILanguage, 0)
#pragma LINKER_REEXPORT(GetCPInfoExW, 12)
#pragma LINKER_REEXPORT(SetProcessAffinityMask, 8)
#pragma LINKER_REEXPORT(GetDiskFreeSpaceExW, 16)
#pragma LINKER_REEXPORT(GetFileAttributesExW, 12)
#pragma LINKER_REEXPORT(TryEnterCriticalSection, 4)

VOID
PopupMessage(
	     _In_ LPCTSTR lpszText
	     );

BOOL WINAPI
MyTryEnterCriticalSection(
			  _Inout_ LPCRITICAL_SECTION lpCriticalSection
			  )
{
  PopupMessage(_T("TryEnterCriticalSection"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

BOOL WINAPI
MyGetFileAttributesExW(
		       _In_  LPCWSTR                lpFileName,
		       _In_  GET_FILEEX_INFO_LEVELS fInfoLevelId,
		       _Out_ LPVOID                 lpFileInformation
		       )
{
  PopupMessage(_T("GetFileAttributesExW"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

BOOL WINAPI
MyGetDiskFreeSpaceExW(
		      _In_opt_  LPCWSTR         lpDirectoryName,
		      _Out_opt_ PULARGE_INTEGER lpFreeBytesAvailable,
		      _Out_opt_ PULARGE_INTEGER lpTotalNumberOfBytes,
		      _Out_opt_ PULARGE_INTEGER lpTotalNumberOfFreeBytes
		      )
{
  PopupMessage(_T("GetDiskFreeSpaceExW"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

typedef struct CPINFOWEX {
  UINT  MaxCharSize;
  BYTE  DefaultChar[MAX_DEFAULTCHAR];
  BYTE  LeadByte[MAX_LEADBYTES];
  WCHAR UnicodeDefaultChar;
  UINT  CodePage;
  TCHAR CodePageName[MAX_PATH];
} CPINFOWEX, *LPCPINFOWEX;

LANGID WINAPI
MyGetSystemDefaultUILanguage(
			     VOID
			     )
{
  return GetSystemDefaultLangID();
}

LANGID WINAPI
MyGetUserDefaultUILanguage(
			   VOID
			   )
{
  return GetSystemDefaultLangID();
}

BOOL WINAPI
MyGetCPInfoExW(
	       _In_  UINT        CodePage,
	       _In_  DWORD       dwFlags,
	       _Out_ LPCPINFOWEX lpCPInfoEx
	       )
{
  BOOL ret;
  CPINFO info;

  ret = GetCPInfo(CodePage, &info);
  if (!ret) {
    return ret;
  }

  lpCPInfoEx->MaxCharSize = info.MaxCharSize;
  CopyMemory(lpCPInfoEx->DefaultChar, info.DefaultChar, MAX_DEFAULTCHAR);
  CopyMemory(lpCPInfoEx->LeadByte, info.LeadByte, MAX_LEADBYTES);
  lpCPInfoEx->UnicodeDefaultChar = L'?';
  lpCPInfoEx->CodePage = CodePage;
  lpCPInfoEx->CodePageName[0] = L'?';
  lpCPInfoEx->CodePageName[1] = L'\0';
  return ret;
}

#define INVALID_SET_FILE_POINTER ((DWORD)-1)
BOOL WINAPI
MySetFilePointerEx(
		   _In_      HANDLE         hFile,
		   _In_      LARGE_INTEGER  liDistanceToMove,
		   _Out_opt_ PLARGE_INTEGER lpNewFilePointer,
		   _In_      DWORD          dwMoveMethod
		   )
{
  LONG low = liDistanceToMove.LowPart;
  LONG high = liDistanceToMove.HighPart;

  low = SetFilePointer(hFile, low, &high, dwMoveMethod);
  if (low == INVALID_SET_FILE_POINTER) {
    return FALSE;
  }

  if (lpNewFilePointer != NULL) {
    lpNewFilePointer->LowPart = low;
    lpNewFilePointer->HighPart = high;
  }

  return TRUE;
}

typedef enum  COMPUTER_NAME_FORMAT {
  COMPUTER_NAME_FORMAT_MEH
} COMPUTER_NAME_FORMAT;

BOOL WINAPI
MySetComputerNameExW(
		   _In_ COMPUTER_NAME_FORMAT NameType,
		   _In_ LPCWSTR              lpBuffer
		   )
{
  return SetComputerNameW(lpBuffer);
}

typedef enum JOBOBJECTINFOCLASS {
  JOBOBJECTINFOCLASS_MEH
} JOBOBJECTINFOCLASS;
BOOL WINAPI
MyQueryInformationJobObject(
			    _In_opt_  HANDLE             hJob,
			    _In_      JOBOBJECTINFOCLASS JobObjectInfoClass,
			    _Out_     LPVOID             lpJobObjectInfo,
			    _In_      DWORD              cbJobObjectInfoLength,
			    _Out_opt_ LPDWORD            lpReturnLength
			    )
{
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

VOID WINAPI
MyRtlCaptureContext(
		    _Out_ PCONTEXT Context
		    )
{
  ZeroMemory(Context, sizeof(CONTEXT));
  Context->ContextFlags = CONTEXT_CONTROL;

__asm {
  Label:
    mov [Context.Ebp], ebp
    mov [Context.Esp], esp
    mov eax, [Label]
    mov [Context.Eip], eax
  }
}

BOOL WINAPI 
MySwitchToThread(void)
{
  Sleep(0);
  return TRUE;
}

HANDLE WINAPI
MyOpenThread(
	     _In_ DWORD dwDesiredAccess,
	     _In_ BOOL  bInheritHandle,
	     _In_ DWORD dwThreadId
	     )
{
  OBJECT_ATTRIBUTES   ObjectAttributes;
  CLIENT_ID           ClientId;
  HANDLE              hThread;
  NTSTATUS            Status;

  InitializeObjectAttributes(&ObjectAttributes, NULL, 0, NULL, NULL);

  if (bInheritHandle) {
    ObjectAttributes.Attributes = OBJ_INHERIT;
  }

  ClientId.UniqueProcess = NULL;
  ClientId.UniqueThread = (HANDLE)dwThreadId;

  Status = NtOpenThread(&hThread,             // Thread handle
			dwDesiredAccess,      // Access to thread object
			&ObjectAttributes,    // Object attributes
			&ClientId);           // Client Id

  if (!NT_SUCCESS(Status)) {
    SetLastError(RtlNtStatusToDosError(Status));
    return NULL;
  }

  return hThread;
}

BOOL WINAPI
MyIsProcessInJob(
		 _In_     HANDLE ProcessHandle,
		 _In_opt_ HANDLE JobHandle,
		 _Out_    PBOOL  Result
		 )
{
  PopupMessage(_T("ProcessInJob"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

typedef PVOID LPMEMORYSTATUSEX;
BOOL WINAPI
MyGlobalMemoryStatusEx(
		       _Inout_ LPMEMORYSTATUSEX lpBuffer
		       )
{
  PopupMessage(_T("GlobalMemoryStatusEx"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

BOOL WINAPI
MyGetVolumePathNamesForVolumeNameW(
				   _In_  LPCWSTR lpszVolumeName,
				   _Out_ LPWSTR  lpszVolumePathNames,
				   _In_  DWORD   cchBufferLength,
				   _Out_ PDWORD  lpcchReturnLength
				   )
{
  PopupMessage(_T("GetVolumePathNamesForVolumeNameW"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

BOOL WINAPI
MyGetVolumeNameForVolumeMountPointW(
				    _In_  LPCWSTR lpszVolumeMountPoint,
				    _Out_ LPWSTR  lpszVolumeName,
				    _In_  DWORD   cchBufferLength
				    )
{
  PopupMessage(_T("MyGetVolumeNameForVolumeMountPointW"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

UINT WINAPI
MyGetSystemWow64DirectoryW(
			   _Out_ LPWSTR lpBuffer,
			   _In_  UINT   uSize
			   )
{
  PopupMessage(_T("GetSystemWow64DirectoryW"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return 0;
}

UINT WINAPI
MyGetSystemWindowsDirectoryW(
			     _Out_ LPWSTR lpBuffer,
			     _In_  UINT   uSize
			     )
{
  wchar_t szWindowsDir[MAX_PATH];
  wchar_t *pBackslash;
  UINT len;

  GetSystemDirectoryW(szWindowsDir, MAX_PATH);    
  pBackslash = wcsrchr(szWindowsDir,  L'\\');
  *pBackslash = L'\0';

  len = wcslen(szWindowsDir);
  if (len > uSize) {
    return uSize;
  }

  wcscpy(lpBuffer, szWindowsDir);
  return len;
}

UINT WINAPI
MyGetSystemWindowsDirectoryA(
			     _Out_ LPSTR lpBuffer,
			     _In_  UINT   uSize
			     )
{
  char szWindowsDir[MAX_PATH];
  char *pBackslash;
  UINT len;

  GetSystemDirectoryA(szWindowsDir, MAX_PATH);    
  pBackslash = strrchr(szWindowsDir,  '\\');
  *pBackslash = '\0';

  len = strlen(szWindowsDir);
  if (len > uSize) {
    return uSize;
  }

  strcpy(lpBuffer, szWindowsDir);
  return len;
}

BOOL WINAPI
MyGetModuleHandleExW(
		     _In_     DWORD   dwFlags,
		     _In_opt_ LPCWSTR lpModuleName,
		     _Out_    HMODULE *phModule
		     )
{
  PopupMessage(_T("GetModuleHandleExW"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

typedef VOID *PAPCFUNC;
typedef PDWORD ULONG_PTR;

DWORD WINAPI
MyQueueUserAPC(
	       _In_ PAPCFUNC  pfnAPC,
	       _In_ HANDLE    hThread,
	       _In_ ULONG_PTR dwData
	       )
{
  PopupMessage(_T("QueueUserAPC"));
  return 0;
}

BOOL WINAPI
MyGetFileSizeEx(
		_In_  HANDLE         hFile,
		_Out_ PLARGE_INTEGER lpFileSize
		)
{
  DWORD low;
  DWORD high;

  low = GetFileSize(hFile, &high);
  if (low == INVALID_FILE_SIZE) {
    return FALSE;
  }

  lpFileSize->LowPart = low;
  lpFileSize->HighPart = high;

  return TRUE;
}

HWND WINAPI
MyGetConsoleWindow(
		   void
		   )
{
#define MY_BUFSIZE 1024
  HWND hwndFound;
  TCHAR pszNewWindowTitle[MY_BUFSIZE];
  TCHAR pszOldWindowTitle[MY_BUFSIZE]; 

  GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
  wsprintf(pszNewWindowTitle,TEXT("%d/%d"),
	   GetTickCount(),
	   GetCurrentProcessId());

  SetConsoleTitle(pszNewWindowTitle);
  Sleep(40);

  hwndFound = FindWindow(NULL, pszNewWindowTitle);
  SetConsoleTitle(pszOldWindowTitle);

  return hwndFound;
}


BOOL WINAPI
MyGetComputerNameExA(
		     _In_    COMPUTER_NAME_FORMAT NameType,
		     _Out_   LPSTR                lpBuffer,
		     _Inout_ LPDWORD              lpnSize
		     )
{
  return GetComputerNameA(lpBuffer, lpnSize);
}

BOOL WINAPI
MyFindVolumeClose(
		  _In_ HANDLE hFindVolume
		  )
{
  PopupMessage(_T("FindVolumeClose"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

BOOL WINAPI
MyFindNextVolumeW(
		  _In_  HANDLE hFindVolume,
		  _Out_ LPWSTR lpszVolumeName,
		  _In_  DWORD  cchBufferLength
		  )
{
  PopupMessage(_T("FindNextVolumeW"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return FALSE;
}

HANDLE WINAPI
MyFindFirstVolumeW(
		   _Out_ LPWSTR lpszVolumeName,
		   _In_  DWORD  cchBufferLength
		   )
{
  PopupMessage(_T("FindFirstVolumeW"));
  SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
  return INVALID_HANDLE_VALUE;
}

BOOL WINAPI
MySetProcessAffinityMask(
			 _In_ HANDLE    hProcess,
			 _In_ DWORD     dwProcessAffinityMask
			 )
{
  return TRUE;
}

BOOL WINAPI
MyAttachConsole(
		_In_ DWORD dwProcessId
		)
{
  return TRUE;
}

BOOL WINAPI
MyCancelIo(
	   _In_ HANDLE hFile
	   )
{
  PopupMessage(_T("CancelIo"));
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
