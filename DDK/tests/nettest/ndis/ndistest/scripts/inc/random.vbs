
Option Explicit

'============================================================================================='
'/**
' This class provides random data of several different kinds. Useful to
' generate random data for stress and other testing
'@author    Adeel Siddiqui
'@date      03/12/02
'@alias     adeels
'*/
Class CRandomGenerator

   Sub Class_Initialize
      ' Seed the random number generator with a random value
      ReSeed
   End Sub

   Sub Class_Terminate

   End Sub

   '================================================================================================='
   '/**
   ' This method will seed the random number generator with a new seed. Do this everytime you want
   ' to get some extra variance in the random numbers being generated. ReSeed is called in the class
   ' constructor so every object of this class guarantees a different stream of random data from the
   ' previous object instantiated. Hence, every test run will test with new random data
   ' @syntax     oRandomGet.ReSeed
   ' @example
   '     Set oRandomGen = new CRandomGenerator
   '     oRandomGen.ReSeed      ' Redundant as reseeding already done in constructor
   ' */    
   Sub ReSeed
      ' Put a random seed in the generator
      Randomize
   End Sub

   '================================================================================================='
   '/**
   ' This method will return a whole random number lying between low and high value 
   ' (both values inclusive and positive).
   ' @params
   ' !low        The low end of the number range
   ' !high       The high end of the number range
   ' @return     The random number generated
   ' @sa         CRandomGenerator::GetRandomAlphaString, CRandomGenerator::GetRandomAlphaNumericString,
   '             CRandomGenerator::GetRandomHexString, CRandomGenerator::GetRandomGUID,
   '             CRandomGenerator::GetRandomNumber, CRandomGenerator::GetRandomFloat
   ' @example
   '     ' Will generate a random number between 5 and 10 (including 5 or 10)
   '     nData = oRandomGen.GetRandomNumber (5, 10)
   ' */    
   Function GetRandomNumber(low, high)
      GetRandomNumber = CLng ((high - low) * Rnd + low)
   End Function

   '================================================================================================='
   '/**
   ' This method will return a floating point random number lying between low and
   ' high value  (both values inclusive).
   ' @params
   ' !low        The low end of the number range
   ' !high       The high end of the number range
   ' @return     The random number generated
   ' @sa         CRandomGenerator::GetRandomAlphaString, CRandomGenerator::GetRandomAlphaNumericString,
   '             CRandomGenerator::GetRandomHexString, CRandomGenerator::GetRandomGUID,
   '             CRandomGenerator::GetRandomNumber
   ' @example
   '     ' Will generate a random number between 5 and 10 (including 5 or 10)
   '     rData = oRandomGen.GetRandomFloat (5, 10)
   ' */    
   Function GetRandomFloat(low, high)
      GetRandomFloat = ((high - low) * Rnd + low)
   End Function

   '================================================================================================='
   '/**
   ' This method will returns a string of alphabets. They can be both lower or upper case letters
   ' @params
   ' !nStrLen    The number of characters the string returned should contain
   ' @return     The random string generated
   ' @sa         CRandomGenerator::GetRandomAlphaString, CRandomGenerator::GetRandomAlphaNumericString,
   '             CRandomGenerator::GetRandomHexString, CRandomGenerator::GetRandomGUID,
   '             CRandomGenerator::GetRandomNumber
   ' @example
   '     ' Will generate a 7 character string
   '     strData = oRandomGen.GetRandomAlphaString(7)
   ' */    
   Function GetRandomAlphaString (ByVal nStrLen)
      Dim strString, nTemp
      
      strString = ""

      While (nStrLen > 0)
         Do
            ' This will generate a random alphabet (A-Z or a-z)
            nTemp = CByte (GetRandomNumber (65, 122))
         Loop While (nTemp > 90 And nTemp < 97)    ' Some non-alpha chars in middle
         
         strString = strString & Chr (nTemp)
         nStrLen = nStrLen - 1
      WEnd
      
      GetRandomAlphaString = strString
   End Function


   '================================================================================================='
   '/**
   ' This method will returns a string containing letters and numbers only. Letters can be in either
   ' upper case or lower case
   ' @params
   ' !nStrLen    The number of characters the string returned should contain
   ' @return     The random string generated
   ' @sa         CRandomGenerator::GetRandomAlphaString, CRandomGenerator::GetRandomAlphaNumericString,
   '             CRandomGenerator::GetRandomHexString, CRandomGenerator::GetRandomGUID,
   '             CRandomGenerator::GetRandomNumber
   ' @example
   '     ' Will generate string conatining a total of 10 alphabets and numbers
   '     strData = oRandomGen.GetRandomAlphaNumericString(10)
   ' */    
   Function GetRandomAlphaNumericString (ByVal nStrLen)
      Dim strString, nTemp
      
      strString = ""

      While (nStrLen > 0)
         Do
            ' This will generate a random alphabet or number (0-9 or A-Z or a-z)
            nTemp = CByte (GetRandomNumber (48, 122))
         Loop While ( (nTemp > 57 And nTemp < 65) Or _
                      (nTemp > 90 And nTemp < 97) )
         
         strString = strString & Chr (nTemp)
         nStrLen = nStrLen - 1
      WEnd
      
      GetRandomAlphaNumericString = strString
   End Function
   

   '================================================================================================='
   '/**
   ' This method will returns a random hexadecimal string of specified size
   ' @params
   ' !nStrLen    The number of hexits the string returned should contain
   ' @return     The random string generated
   ' @sa         CRandomGenerator::GetRandomAlphaString, CRandomGenerator::GetRandomAlphaNumericString,
   '             CRandomGenerator::GetRandomHexString, CRandomGenerator::GetRandomGUID,
   '             CRandomGenerator::GetRandomNumber
   ' @example
   '     ' Will generate string conatining 5 hexits
   '     strHexData = oRandomGen.GetRandomHexString(5)
   ' */    
   Function GetRandomHexString (ByVal nStrLen)
      Dim strString, nTemp
      
      strString = ""

      While (nStrLen > 0)
         Do
            ' This will generate a random hexit (0-9 or A-F)
            nTemp = CByte (GetRandomNumber (48, 70))
         Loop While (nTemp > 57 And nTemp < 65)
         
         strString = strString & Chr (nTemp)
         nStrLen = nStrLen - 1
      WEnd
      
      GetRandomHexString = strString

   End Function
   

   '================================================================================================='
   '/**
   ' This method will returns a random GUID of the form {8A3CEF81-3445-4c11-85B4-4944AE029DFC}.
   ' This function does NOT use GenGuid or its algorithms. These GUIDS are not guaranteed to be
   ' globally unique. This method simply returns random data formatted as a GUID.
   ' @return     The random GUID generated
   ' @sa         CRandomGenerator::GetRandomAlphaString, CRandomGenerator::GetRandomAlphaNumericString,
   '             CRandomGenerator::GetRandomHexString, CRandomGenerator::GetRandomGUID,
   '             CRandomGenerator::GetRandomNumber
   ' @example
   '     ' Will generate a GUID
   '     strGUID = oRandomGen.GetRandomGUID
   ' */    
   Function GetRandomGUID ()
      Dim strString
      
      ' Generate the GUID format in parts
      strString = "{"                                             ' The opening curly brace
      strString = strString & GetRandomHexString(8) & "-"         ' Then 8 hexits followed by -
      strString = strString & GetRandomHexString(4) & "-"         ' Then 4 hexits followed by -
      strString = strString & GetRandomHexString(4) & "-"         ' Then 4 hexits followed by -
      strString = strString & GetRandomHexString(4) & "-"         ' Then 4 hexits followed by -
      strString = strString & GetRandomHexString(12) & "}"        ' Then 12 hexits followed by closing brace
      
      GetRandomGUID = strString
   End Function
   

End Class

'<!-- CRC = 0x364dfb3f --->