echo off

set RegistryRoot=Software\Microsoft\DbgW64\7.0

:startreg
echo Registering the files...

regtlib dte.olb
regit coloader.dll
regtlib coloader.tlb
regit vspkgs\mso.dll
regtlib vspkgs\mso.dll
regit /root:%RegistryRoot% /v vspkgs\msenv.dll
regit /root:%RegistryRoot% /v vspkgs\cmddef.dll
regit /root:%RegistryRoot% /v vspkgs\dircontrol.dll
regit /root:%RegistryRoot% /v DbgW64Pkgs\DbgW64mnu.dll
regit /root:%RegistryRoot% /v vspkgs\vssln.dll
regit /root:%RegistryRoot% /v vspkgs\vsdebug.dll
regit /root:%RegistryRoot% /v sdm2.dll
regit msdbg2.dll
regit /root:%RegistryRoot% /v natdbgde.dll

echo Registering debugger services
vs7jit -regserver 
mdm -service

DbgW64.exe /setup /selfreg /rt %RegistryRoot%

:end
