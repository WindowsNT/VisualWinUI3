@echo off
cls


REM Manifest Touch
f:\tools\pack\pack64.exe /m %CD%\Package.appxmanifest /n CN=EDD191C1-439D-4D37-B608-9E521142451D

msbuild VisualWinUI3.sln /clp:ErrorsOnly /p:Configuration="Release" /p:Platform=x64 /t:restore /p:RestorePackagesConfig=true
msbuild VisualWinUI3.sln /clp:ErrorsOnly /p:Configuration="Release" /p:Platform=x64 
call clbcall
call sign x64\Release\VisualWinUI3\VisualWinUI3.exe

REM Portable
f:\tools\pack\pack64.exe /i %CD%\app.ico /c x64w,%CD%\x64\Release\VisualWinUI3,VisualWinUI3.exe /o %CD%\VisualWinUI3.exe /u 88887777-A932-7654-A2E5-DECB481E355D
call sign VisualWinUI3.exe

REM MSIX
del VisualWinUI3.msix
makeappx pack /d x64\Release\VisualWinUI3 /p %CD%\VisualWinUI3.msix > nul


call clbcall
del "Generated Files"\* /s /q 
del packages\* /s /q
del x64\* /s /q
del VisualWinUI3\x64\* /s /q
del .vs\VisualWinUI3\CopilotIndices\* /s /q

f:\tools\tu8\uploader\uploader SmallTools
msbuild VisualWinUI3.sln -target:Clean

git add *
git commit -m "Update"
git push

