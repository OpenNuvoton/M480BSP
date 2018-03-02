@echo off
for /f "tokens=*" %%i in ('dir /b /ad /s *') do (
	if exist "%%i\.metadata" (
		RD %%i\.metadata\.mylyn /S /Q
		del %%i\.metadata\*.lock /Q
		del %%i\.metadata\*.log /Q
		del %%i\.metadata\version.ini /Q
        )
	if exist "%%i\..\GCC\RemoteSystemsTempFiles" (
		RD %%i\..\GCC\RemoteSystemsTempFiles /Q /S
	)
	if exist "%%i\GCC\RemoteSystemsTempFiles" (
		RD %%i\GCC\RemoteSystemsTempFiles /Q /S
	)
	if exist "%%i\Packages" (
		RD %%i\Packages /Q /S
	)
	if exist "%%i\..\Packages" (
		RD %%i\..\Packages /Q /S
	)
	if exist "%%i\.settings" (
		RD %%i\.settings /Q /S
	)
	if exist "%%i\Release" (
		RD %%i\Release /Q /S
	)
	if exist "%%i\.plugins" (
		for /f "tokens=*" %%j in ('dir /b %%i\.plugins') do (
			if not %%j == org.eclipse.core.resources (
				if not %%j == org.eclipse.e4.workbench (
					if not %%j == org.eclipse.debug.core (
						RD %%i\.plugins\%%j  /S /Q
					)
				)
			)			
			if %%j == org.eclipse.core.resources (
					rmdir %%i\.plugins\%%j\.history /s/q
					mkdir %%i\.plugins\%%j\.history

					for /f "tokens=*" %%k in ('dir /b /s .markers') do (
						del %%k /Q
					)
			)
		)
	)
	del %%i\*.o
	del %%i\*.d
)