@echo off
REM gen-ntp_keyword.bat
REM helper to invoke keyword-gen and possibly update ntp_keyword.h
REM Usage:
REM   gen-ntp_keyword dir_containing_keyword-gen.exe
REM

set HDR_FILE=..\..\..\..\ntpd\ntp_keyword.h
set UTD_FILE=..\..\..\..\ntpd\keyword-gen-utd
set TMP_TAG=%RANDOM%_%RANDOM%
set NEW_HDR_FILE=new_keyword_%TMP_TAG%.h
set NEW_CMP_FILE=new_keyword_cmp_%TMP_TAG%.h
set CUR_CMP_FILE=ntp_keyword_cmp_%TMP_TAG%.h

if "{%1}" == "{}" goto Usage
if not exist "%1\keyword-gen.exe" goto ExeNotFound
"%1\keyword-gen.exe" ..\..\..\..\ntpd\ntp_parser.h > "%NEW_HDR_FILE%"

REM check if we must create both files from scratch
if not exist "%HDR_FILE%" goto missingFiles
if not exist "%UTD_FILE%" goto missingFiles

:compareFiles
findstr /v diff_ignore_line "%NEW_HDR_FILE%" > "%NEW_CMP_FILE%"
findstr /v diff_ignore_line "%HDR_FILE%"  > "%CUR_CMP_FILE%"
set meat_changed=0
fc /L "%CUR_CMP_FILE%" "%NEW_CMP_FILE%" > NUL
if errorlevel 1 set meat_changed=1
del "%CUR_CMP_FILE%" "%NEW_CMP_FILE%"
if "0"=="%meat_changed%" goto SkipUpdate

:missingFiles
REM The files may have been deleted by the IDE in a Clean or Rebuild.
REM Check if we're in a BitKeeper repo and if so retrieve the most
REM recent version of the files.
bk root ../../../.. 2>NUL >NUL
if errorlevel 1 goto createFiles

bk checkout %HDR_FILE% %UTD_FILE%
if errorlevel 1 goto createFiles
goto compareFiles

:createFiles
copy /y /v "%NEW_HDR_FILE%" "%HDR_FILE%"  > NUL
findstr diff_ignore_line "%NEW_HDR_FILE%" > "%UTD_FILE%"
echo updated keyword-gen-utd and ntp_keyword.h
goto SkipSkipMsg

:skipUpdate
echo ntp_keyword.h is unchanged
REM 'touch' the files by replacing them with a concatenation of itself and NUL:
copy /b "%HDR_FILE%" + NUL "%HDR_FILE%" > NUL
copy /b "%UTD_FILE%" + NUL "%UTD_FILE%" > NUL

:SkipSkipMsg
set meat_changed=
del "%NEW_HDR_FILE%"
goto Exit

:Usage
echo Usage:
echo   gen-ntp_keyword dir_containing_keyword-gen.exe
goto Exit

:ExeNotFound
echo keyword-gen.exe not found at %1\keyword-gen.exe
goto Exit

:Exit
