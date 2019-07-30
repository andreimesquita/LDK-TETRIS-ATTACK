SHELL=cmd
# paths
LDKSDK=..\..\ldk\include
OUTDIR=..\..\build
LIBDIR=..\..\ldk\lib

HOT_RELOAD_OPTIONS=/PDB:$(OUTDIR)\match3_%random%.pdb

#build targets
LDK_GAME=$(OUTDIR)\ldk_game.dll
LDK_ENGINE=$(OUTDIR)\ldk.dll $(OUTDIR)\ldk.lib
LDK_EDITOR=$(OUTDIR)\ldk_editor.exe

#DEBUG OPTIONS
LIBS=user32.lib gdi32.lib Opengl32.lib Msimg32.lib Ole32.lib
DEBUG_DEFINES=/D "_LDK_DEBUG_" 
DEBUG_COMPILE_OPTIONS=/nologo /EHsc /MT /I$(LDKSDK) $(DEBUG_DEFINES) /Zi
DEBUG_LINK_OPTIONS=/link /subsystem:console $(LIBS)

#RELEASE OPTIONS
RELEASE_DEFINES=
RELEASE_COMPILE_OPTIONS=/nologo /EHsc /MT /I$(LDKSDK) $(RELEASE_DEFINES)
RELEASE_LINK_OPTIONS=/link /subsystem:windows $(LIBS)

CFLAGS=$(DEBUG_COMPILE_OPTIONS)
LINKFLAGS=$(DEBUG_LINK_OPTIONS)

match3: match3.cpp
	IF NOT EXIST "$(OUTDIR)\" @mkdir $(OUTDIR)
	cl match3.cpp /Fo$(OUTDIR) /Fe$(LDK_GAME) /LD $(CFLAGS) /link /subsystem:windows $(HOT_RELOAD_OPTIONS) $(LIBDIR)/ldk.lib
	xcopy assets $(OUTDIR)\assets /Y /I /E /F > nul
	copy /Y $(LDK_EDITOR) $(OUTDIR)\tetrisatk.exe
	
run:
	$(OUTDIR)\tetrisatk.exe

clean:
	IF EXIST $(OUTDIR)\match3 rd /S /Q $(OUTDIR)\match3 > nul