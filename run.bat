:: Uso: [set EXEC="caminho\do\executavel.exe"]&&[set TEST_FOLDER=caminho\dos\casetests]&&[set ARGS=ic]&&[set SOLUTIONS_FILE=arquivo\de\solucoes.txt]&&run.bat [> arq\de\saida.txt]
@ECHO off
setlocal enabledelayedexpansion

if not defined EXEC (
	set EXEC="build\sabp.exe"
)

if not defined TEST_FOLDER (
	set TEST_FOLDER=test\reduced
)

rem I need to fix this later, dear God...
set ARGS=-ic

if defined SOLUTIONS_FILE (
	for /f "tokens=1,2 skip=1" %%a in (%SOLUTIONS_FILE%) do (
		set solutions[%%a]=%%b
	)
)

for %%g in (%TEST_FOLDER%\*) do (
	for %%h in (%%g) do set testname=%%~nxh
	for /f "delims=" %%h in ("!testname!") do set optimal=!solutions[%%h]!

	echo Arquivo de teste: %%g

	set start_t=!TIME!
	for /f "tokens=4" %%h in ('!EXEC! !ARGS! ^< %%g') do set res=%%h
	set end_t=!TIME!
	call :difftime !start_t! !end_t! difference

	echo Resultado do programa: !res!
	if defined optimal (
		echo Resultado ótimo:       !optimal!
		if !res! EQU !optimal! (
			echo Resultado ótimo^^!
		) else (
			set /a diff= !res!-!optimal!
			echo Diferença de !diff!
		)
	)
	echo Tempo de execução: !difference! segundos
)

endlocal
set EXEC=
set TEST_FOLDER=
set SOLUTIONS_FILE=
set ARGS=
goto :eof

rem Function that gets the difference between two %TIME% variables, expects args= start(VAL), end(VAL), ret(VARNAME)
rem This function assumes that the difference in time is LESS THAN 24 HOURS; If the difference is larger, return is incorrect
:difftime
setlocal
	
	for /f "tokens=1-3 delims=:" %%a in ("%~1") do (
		set /a start_h= ^(1%%a-100^) * 3600
		set /a start_m= ^(1%%b-100^) * 60
		set /a start_s= ^(1%%c-100^)
	)

	for /f "tokens=1-3 delims=:" %%a in ("%~3") do (
		set /a end_h= ^(1%%a-100^) * 3600
		set /a end_m= ^(1%%b-100^) * 60
		set /a end_s= ^(1%%c-100^)
	)

	set /a start_i= %start_h% + %start_m% + %start_s%
	set /a end_i= %end_h% + %end_m% + %end_s%
	set /a diff_t= %end_i% - %start_i%

	if diff_t LSS 0 set /a diff_t= %diff_t%+86400
	
endlocal & set %~5=%diff_t%
goto :eof