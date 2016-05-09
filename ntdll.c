#pragma comment(linker,"/entry:DllMain@12")

#include "common.h"
#include "ntdll-forwards.h"

#pragma LINKER_CDECL_REEXPORT(NtQueryQuotaInformationFile)
#pragma LINKER_CDECL_REEXPORT(NtSetQuotaInformationFile)
#pragma LINKER_CDECL_REEXPORT(RtlAddAccessAllowedAceEx)
#pragma LINKER_CDECL_REEXPORT(RtlAddAccessDeniedAceEx)
#ifndef NT40
#pragma LINKER_CDECL_REEXPORT(RtlDowncaseUnicodeString)
#endif /* NT40 */
#pragma LINKER_CDECL_REEXPORT(RtlGetVersion)
#pragma LINKER_CDECL_REEXPORT(RtlSetControlSecurityDescriptor)

#pragma comment(linker, "/export:__stricmp=msvcrt._stricmp")
#pragma comment(linker, "/export:__strnicmp=msvcrt._strnicmp")
#pragma comment(linker, "/export:strtoul=msvcrt.strtoul")
#pragma comment(linker, "/export:iscntrl=msvcrt.iscntrl")
#pragma comment(linker, "/export:isdigit=msvcrt.isdigit")
#pragma comment(linker, "/export:isalnum=msvcrt.isalnum")
#pragma comment(linker, "/export:isgraph=msvcrt.isgraph")
#pragma comment(linker, "/export:ispunct=msvcrt.ispunct")

NTSTATUS
MyRtlSetControlSecurityDescriptor(
				  _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
				  _In_ SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest,
				  _In_ SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet 
				  )
{
  PopupMessage(_T("RtlSetControlSecurityDescriptor"));
  return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
MyRtlGetVersion(
		_Inout_ PRTL_OSVERSIONINFOW lpVersionInformation
		)
{
  BOOL status = GetVersionExW(lpVersionInformation);
  if (status) {
    return STATUS_SUCCESS;
  }

  return STATUS_UNSUCCESSFUL;
}

#ifndef NT40
NTSTATUS
MyRtlDowncaseUnicodeString(
			   _Inout_ PUNICODE_STRING UniDest,
			   _In_ PCUNICODE_STRING UniSource,
			   _In_ BOOLEAN AllocateDestinationString 
			   )
{
  ULONG i;

  if (AllocateDestinationString) {
    UniDest->MaximumLength = UniSource->Length;
    UniDest->Buffer = malloc(UniSource->Length * sizeof(WCHAR));
    if (UniDest->Buffer == NULL) {
      return STATUS_NO_MEMORY;
    }
  }
  else if (UniSource->Length > UniDest->MaximumLength) {
    return STATUS_BUFFER_OVERFLOW;
  }

  UniDest->Length = UniSource->Length;
  for (i = 0; i < UniSource->Length / sizeof(WCHAR); i++) {
    if (UniSource->Buffer[i] < L'A') {
      UniDest->Buffer[i] = UniSource->Buffer[i];
    } else if (UniSource->Buffer[i] <= L'Z') {
      UniDest->Buffer[i] = (UniSource->Buffer[i] + (L'a' - L'A'));
    } else {
      PopupMessage(_T("RtlDowncaseUnicodeString"));
      return STATUS_NOT_IMPLEMENTED;
    }
  }

  return STATUS_SUCCESS;
}
#endif /* NT40 */

NTSTATUS
MyRtlAddAccessDeniedAceEx(
			  _Inout_ PACL Acl,
			  _In_ ULONG Revision,
			  _In_ ULONG Flags,
			  _In_ ACCESS_MASK AccessMask,
			  _In_ PSID Sid 
			  )
{
  PopupMessage(_T("RtlAddAccessDeniedAceEx"));
  return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
MyRtlAddAccessAllowedAceEx(
			   _Inout_ PACL        Acl,
			   _In_    ULONG       AceRevision,
			   _In_    ULONG       AceFlags,
			   _In_    ACCESS_MASK AccessMask,
			   _In_    PSID        Sid
			   )
{
  PopupMessage(_T("RtlAddAccessAllowedAceEx"));
  return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
MyNtSetQuotaInformationFile(
			    _In_  HANDLE           FileHandle,
			    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
			    _In_  PVOID            Buffer,
			    _In_  ULONG            Length
			    )
{
  return STATUS_INVALID_DEVICE_REQUEST;
}

NTSTATUS
MyNtQueryQuotaInformationFile(
			    _In_     HANDLE           FileHandle,
			    _Out_    PIO_STATUS_BLOCK IoStatusBlock,
			    _Out_    PVOID            Buffer,
			    _In_     ULONG            Length,
			    _In_     BOOLEAN          ReturnSingleEntry,
			    _In_opt_ PVOID            SidList,
			    _In_     ULONG            SidListLength,
			    _In_opt_ PSID             StartSid,
			    _In_     BOOLEAN          RestartScan
			    )
{
  return STATUS_INVALID_DEVICE_REQUEST;
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
