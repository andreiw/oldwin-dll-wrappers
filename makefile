CL_OPTS = -Ox -GA

all: patcher.exe .phony
	cd nt40 && nmake
	cd nt351 && nmake

.phony:

clean:
	del /Q *.obj *.exe
	cd nt40 && nmake clean
	cd nt351 && nmake clean

patcher.exe: patcher.cpp
	cl $(CL_OPTS) /Fe$@ $** imagehlp.lib
