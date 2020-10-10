'
' THIS is a HiGhLy CaSe SeNsItIvE file.
'
' Database tag format:
' [DATABASE PHYSICALMEDIUM[!|=]={Unspecified}|{ALL};]
' Note that items withing a tag cannot contain spaces and are ofcourse case sensitive
'
' Database entry format:
' TestType, AddressType, PacketSize, MDLs, bps%, PktDrop%, ClocksPerByte at 10Mbps
' Items must be separated by a "," and 0 or 1 space (after the comma).
'

'
' PhysicalMedium
'
[DATABASE PHYSICALMEDIUM==ALL]
'SEND_ONLY, UNICAST_ADDRESS, 30, 1, 50, 5, 100
ALL, ALL, 6, ALL, 50, 3, 100
ALL, ALL, 30, ALL, 50, 3, 100
ALL, ALL, 60, ALL, 50, 3, 100
ALL, ALL, 100, ALL, 50, 3, 100
[/DATABASE]

'<!-- CRC = 0x46462885 --->