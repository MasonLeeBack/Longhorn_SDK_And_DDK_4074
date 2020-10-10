RELEASE NOTES FOR DPINST RTM
----------------------------

This document lists some known bugs/limitations of the Release version of DPINST. 

* An authenticode-signed, Plug and Play driver cannot be installed silently on Windows XP and Windows 2000. This is due to  the fact that both Windows XP and Windows 2000 do not recognize authenticode-signed drivers, as a result of which they will always attempt to display the unsigned driver dialog. But in silent mode, since they are not allowed to display any UI, the install will fail silently.

* Silent install of Plug and Play drivers may fail on Windows Server 2003 depending on the driver package and should be tested on a case by case basis.

* On Windows 2000, depending on how the package was signed, signature checking can be very slow. Signature checking can be speeded up by installing the hotfix for Windows 2000 described in the Knowledge Base article KB329433.

Undocumented Feature

* DPInst recognizes the a new key called DriverPackageDisplayName in the Version section of the INF. If present, the name defined by this key will shown in the Add/Remove Programs field and in DPInst, making it easier for users to identify the driver package in case they want or need to remove it. Example: 
[Version]
...
DriverPackageDisplayName=Graphics Card Foo 77
