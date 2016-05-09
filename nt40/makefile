CL_OPTS = -DNT40 -I. -Ox -GD -GF -Zl -MD -LD

all: ntdl_.dll

clean:
	del /Q *.obj *.dll *.exp *.lib

ntdll-wrapper.dll: ../ntdll.c ../common.c
	cl $(CL_OPTS) /Fe$@ $** user32.lib kernel32.lib msvcrt.lib

ntdl_.dll: ntdll-wrapper.dll
	copy $** $@

