@ECHO OFF
SetLocal EnableDelayedExpansion

SET cFilenames=
FOR /R %%f in (*.c) do (SET cFilenames=!cFilenames! %%f)

SET assembly=testbed
SET compilerFlags=-g 
SET includeFlags=-Isrc -I../engine/src/
SET linkerFlags=-L../bin/ -lHammer3D.lib
SET defines=-DDEBUG -DHIMPORT

ECHO "Building %assembly%%..."
clang %cFilenames% %compilerFlags% -o ../bin/%assembly%.exe %defines% %includeFlags% %linkerFlags%