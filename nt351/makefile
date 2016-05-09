CL_OPTS = -I. -Ox -GD -GF -Zl -MD -LD

all: kernel3_.dll ntdl_.dll msvcr_.dll user3_.dll ole3_.dll gdi3_.dll advapi3_.dll comctl3_.dll

clean:
	del /Q *.obj *.dll *.exp *.lib

advapi32-wrapper.dll: ../advapi32.c ../common.c
	cl $(CL_OPTS) /Fe$@ $** kernel32.lib user32.lib

comctl32-wrapper.dll: ../comctl32.c ../common.c
	cl $(CL_OPTS) /Fe$@ $** comctl32.lib user32.lib kernel32.lib

gdi32-wrapper.dll: ../gdi32.c ../common.c
	cl $(CL_OPTS) /Fe$@ $** gdi32.lib user32.lib kernel32.lib msvcrt.lib

ole32-wrapper.dll: ../ole32.c ../common.c
	cl $(CL_OPTS) /Fe$@ $** ole32.lib user32.lib kernel32.lib msvcrt.lib

user32-wrapper.dll: ../user32.c ../common.c
	cl $(CL_OPTS) /Fe$@ $** user32.lib kernel32.lib msvcrt.lib

msvcrt-wrapper.dll: ../msvcrt.c ../common.c
	cl $(CL_OPTS) /Fe$@ $** user32.lib kernel32.lib msvcrt.lib

ntdll-wrapper.dll: ../ntdll.c ../common.c
	cl $(CL_OPTS) /Fe$@ $** user32.lib kernel32.lib msvcrt.lib

kernel32-wrapper.dll: ../kernel32.c ../common.c
	cl $(CL_OPTS) /Fe$@ $** user32.lib kernel32.lib msvcrt.lib

comctl3_.dll: comctl32-wrapper.dll
	copy $** $@

advapi3_.dll: advapi32-wrapper.dll
	copy $** $@

ole3_.dll: ole32-wrapper.dll
	copy $** $@

gdi3_.dll: gdi32-wrapper.dll
	copy $** $@

user3_.dll: user32-wrapper.dll
	copy $** $@

msvcr_.dll: msvcrt-wrapper.dll
	copy $** $@

kernel3_.dll: kernel32-wrapper.dll
	copy $** $@

ntdl_.dll: ntdll-wrapper.dll
	copy $** $@

