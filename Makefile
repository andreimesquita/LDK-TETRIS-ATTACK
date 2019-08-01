SHELL=cmd
# paths
LDKSDK=ldk\include
OUTDIR=build
LIBDIR=ldk\lib
ENTRY_POINT_CPP=game\game.cpp
FINAL_EXE_NAME=tetrisatk.exe
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

.PHONY: clean compile

compile: $(ENTRY_POINT_CPP)
	@echo Compiling...
	cl $(ENTRY_POINT_CPP) /Fo$(OUTDIR) /Fe$(LDK_GAME) /LD $(CFLAGS) /link /subsystem:windows $(LIBDIR)/ldk.lib
	
	@echo Moving assets into build folder...
	xcopy game\assets $(OUTDIR)\assets /Y /I /E /F > nul
	xcopy assets $(OUTDIR)\assets /Y /I /E /F > nul
	copy /Y $(LDK_EDITOR) $(OUTDIR)\$(FINAL_EXE_NAME)
	
run:
	$(OUTDIR)\tetrisatk.exe

clean:
	@echo Cleaning up build folder...
	IF EXIST "$(OUTDIR)\assets" rd /S /Q $(OUTDIR)\assets > nul
	IF EXIST "$(OUTDIR)\ldk_game.dll" del /Q /F $(OUTDIR)\ldk_game.dll > nul
	IF EXIST "$(OUTDIR)\tetrisatk.exe" del /Q /F $(OUTDIR)\tetrisatk.exe > nul
	IF EXIST "$(OUTDIR)\ldk_game.exp" del /Q /F $(OUTDIR)\ldk_game.exp > nul
	IF EXIST "$(OUTDIR)\ldk_game.ilk" del /Q /F $(OUTDIR)\ldk_game.ilk > nul
	IF EXIST "$(OUTDIR)\game.obj" del /Q /F $(OUTDIR)\game.obj > nul
	IF EXIST "$(OUTDIR)\ldk_game.lib" del /Q /F $(OUTDIR)\ldk_game.lib > nul
	IF EXIST "$(OUTDIR)\ldk_game.pdb" del /Q /F $(OUTDIR)\ldk_game.pdb > nul
