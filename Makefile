# source paths
LDKSDK=include

#build targets

#DEBUG OPTIONS
LIBS=user32.lib gdi32.lib Opengl32.lib Msimg32.lib Ole32.lib
DEBUG_DEFINES=/D "_LDK_DEBUG_" 
DEBUG_COMPILE_OPTIONS=/nologo /EHsc /MT /I$(LDKSDK) $(DEBUG_DEFINES) /Zi
DEBUG_LINK_OPTIONS=/link /subsystem:console $(LIBS)

#DEBUG build
CFLAGS=$(DEBUG_COMPILE_OPTIONS)
LINKFLAGS=$(DEBUG_LINK_OPTIONS)

.PHONY: clean game assets

game: game\match3\match3.cpp
	@echo Building game dll...
	cl game\match3\match3.cpp /Fobuild\ /Febuild\ldk_game.dll /LD $(CFLAGS) /link /subsystem:windows lib/ldk.lib
	@copy /Y build\ldk_game.dll .

assets:
	@echo copying assets ...
	@xcopy game\assets build\assets /Y /I /E /F > NUL
	@xcopy assets build\assets /Y /I /E /F > NUL
	@copy /Y ldk.cfg build > NUL

clean:
	@IF EXIST "_game_copy.dll" del \S \Q "_game_copy.dll" > NUL
	@IF EXIST "build" del /S /Q .\build\* > NUL
	@IF EXIST "build\assets" rd /S /Q .\build\assets > NUL
