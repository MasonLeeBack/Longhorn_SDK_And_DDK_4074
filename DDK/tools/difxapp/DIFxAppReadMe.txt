RELEASE NOTES FOR DIFXAPP Version 1.0 
-------------------------------------

This document lists some known bugs/limitations of DIFxApp Version 1.0 

* An authenticode-signed, Plug and Play driver cannot be installed silently on Windows XP and Windows 2000. This is due to  the fact that both Windows XP and Windows 2000 do not recognize authenticode-signed drivers, as a result of which they will always attempt to display the unsigned driver dialog. But in silent mode, since they are not allowed to display any UI, the install will fail silently.

* Silent install of authenticode-signed Plug and Play drivers will fail on Windows Server 2003 if the driver package includes a co-installer.

* Repair of Plug and Play drivers does not work.