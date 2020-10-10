'--------------------------------------------------------------------------
'Contains all the constants specific to LAN scripts.

'--------------------------------------------------------------------------
Dim GoodFunctAddr
GoodFunctAddr = FunctAddr(&H01&, &H02&, &H03&, &H04&)

Dim BadFunctAddr
BadFunctAddr  = FunctAddr(&H10&, &H20&, &H30&, &H40&)

Dim NullFunctAddr
NullFunctAddr = FunctAddr(&H00&, &H00&, &H00&, &H00&)
'--------------------------------------------------------------------------
Dim GoodGroupAddr
GoodGroupAddr = GrpAddr(&H81&, &H02&, &H03&, &H04&)

Dim BadGroupAddr
BadGroupAddr  = GrpAddr(&H90&, &H20&, &H30&, &H40&)

Dim NullGroupAddr
NullGroupAddr = GrpAddr(&H00&, &H00&, &H00&, &H00&)

'--------------------------------------------------------------------------
Dim GoodMulticastAddr
GoodMulticastAddr = NetAddr(&H01&, &H02&, &H03&, &H04&, &H05&, &H06&)

Dim BadMulticastAddr
BadMulticastAddr  = NetAddr(&H01&, &H02&, &H03&, &H04&, &H05&, &H00&)

'--------------------------------------------------------------------------
Dim RandomAddr               
RandomAddr = NetAddr(&H00&, &H02&, &H04&, &H06&, &H08&, &H0a&)
'--------------------------------------------------------------------------

'<!-- CRC = 0xdb9d4003 --->