@echo off
rem chdir into the source directory
pushd ..
rem set environment variable to find dll files
set PATH=.;..\framework\lib;%PATH%
rem call the cgv viewer
call "../framework/bin/cgv_viewer_12.exe" plugin:"../framework/lib/cg_fltk_12.dll" plugin:"solution/exercise1_solution.dll"
popd