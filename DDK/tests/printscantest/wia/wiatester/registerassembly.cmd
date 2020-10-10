@echo off
::
:: Try first if some framework is in the path
::
RegAsm.exe %*
if errorlevel 2 ( 

    echo.
    echo It is not in the path, trying v2.0 ...

    %windir%\Microsoft.NET\Framework\v2.0.31113\RegAsm.exe %*

    if errorlevel 2 ( 
 
        echo.
        echo Trying v1.1 ...

        %windir%\Microsoft.NET\Framework\v1.1.4322\RegAsm.exe %*

        if errorlevel 2 ( 

           echo.
           echo Please install .NET Framework

        )
    )
)
