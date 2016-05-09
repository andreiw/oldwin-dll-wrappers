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
#ifndef NTDEFS_H
#define NTDEFS_H

#define OBJ_INHERIT 0x00000002

typedef struct _CLIENT_ID {
  HANDLE UniqueProcess;
  HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _LSA_UNICODE_STRING {
  USHORT Length;
  USHORT MaximumLength;
  PWSTR  Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING, UNICODE_STRING, *PUNICODE_STRING;
typedef CONST PUNICODE_STRING PCUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
  ULONG           Length;
  HANDLE          RootDirectory;
  PUNICODE_STRING ObjectName;
  ULONG           Attributes;
  PVOID           SecurityDescriptor;
  PVOID           SecurityQualityOfService;
}  OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef PVOID PSECURITY_DESCRIPTOR;
typedef WORD SECURITY_DESCRIPTOR_CONTROL;
typedef LPOSVERSIONINFOW PRTL_OSVERSIONINFOW;
typedef PVOID PIO_STATUS_BLOCK;
typedef PVOID PSID;

#define InitializeObjectAttributes( p, n, a, r, s ) { \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );	      \
    (p)->RootDirectory = r;			      \
    (p)->Attributes = a;			      \
    (p)->ObjectName = n;			      \
    (p)->SecurityDescriptor = s;		      \
    (p)->SecurityQualityOfService = NULL;	      \
  }

typedef LONG NTSTATUS;
#define STATUS_UNSUCCESSFUL    ((NTSTATUS) 0xC0000001)
#define STATUS_SUCCESS         ((NTSTATUS) 0x00000000L)
#define STATUS_NOT_IMPLEMENTED ((NTSTATUS) 0xC0000002L)
#define STATUS_BUFFER_OVERFLOW ((NTSTATUS) 0x80000005)
#define STATUS_INVALID_DEVICE_REQUEST ((NTSTATUS) 0xC0000010L)
#define NT_SUCCESS(Status)     (((NTSTATUS)(Status)) >= 0)

typedef NTSTATUS
(NTAPI *NtOpenThreadProc)(
		_Out_ PHANDLE             ThreadHandle,
		_In_  ACCESS_MASK          AccessMask,
		_In_  POBJECT_ATTRIBUTES   ObjectAttributes,
		_In_  PCLIENT_ID           ClientId
		);

typedef ULONG
(NTAPI *RtlNtStatusToDosErrorProc)(
			 _In_ NTSTATUS Status
			 );

#endif /* NTDEFS_H */
