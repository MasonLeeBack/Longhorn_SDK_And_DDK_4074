/**********************************************************************/
/**                       Microsoft Windows NT                       **/
/**                Copyright(c) Microsoft Corp., 1993-1999           **/
/**********************************************************************/

/*
    mdmsg.h

    This file is generated by the MC tool from the MDMSG.MC message
    file.


    FILE HISTORY:
        michth      26-Jun-1996 Created.

*/


#ifndef _MDMSG_H_
#define _MDMSG_H_

//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-------------------------------+
//  |S|R|C|N|r|    Facility         |               Code            |
//  +-+-+-+-+-+---------------------+-------------------------------+
//
//  where
//
//      S - Severity - indicates success/fail
//
//          0 - Success
//          1 - Fail (COERROR)
//
//      R - reserved portion of the facility code, corresponds to NT's
//              second severity bit.
//
//      C - reserved portion of the facility code, corresponds to NT's
//              C field.
//
//      N - reserved portion of the facility code. Used to indicate a
//              mapped NT status value.
//
//      r - reserved portion of the facility code. Reserved for internal
//              use. Used to indicate HRESULT values that are not status
//              values, but are instead message ids for display strings.
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: MD_ERROR_NOT_INITIALIZED
//
// MessageText:
//
//  MetaData has not been initialized.
//
#define MD_ERROR_NOT_INITIALIZED         0x800CC800L

//
// MessageId: MD_ERROR_DATA_NOT_FOUND
//
// MessageText:
//
//  The specified metadata was not found.
//
#define MD_ERROR_DATA_NOT_FOUND          0x800CC801L

//
// MessageId: MD_ERROR_INVALID_VERSION
//
// MessageText:
//
//  The version specified in metadata storage was not recognized.
//
#define MD_ERROR_INVALID_VERSION         0x800CC802L

//
// MessageId: MD_WARNING_PATH_NOT_FOUND
//
// MessageText:
//
//  A specified metaobject path was not found. The metaobject and associated metadata was ignored.
//
#define MD_WARNING_PATH_NOT_FOUND        0x000CC803L

//
// MessageId: MD_WARNING_DUP_NAME
//
// MessageText:
//
//  A metaobject or metadata was specified more than once. The duplicate ignored.
//
#define MD_WARNING_DUP_NAME              0x000CC804L

//
// MessageId: MD_WARNING_INVALID_DATA
//
// MessageText:
//
//  Invalid metadata was specified. The invalid metadata was ignored.
//
#define MD_WARNING_INVALID_DATA          0x000CC805L

//
// MessageId: MD_ERROR_SECURE_CHANNEL_FAILURE
//
// MessageText:
//
//  A secure communications channel could not be established with the target server.
//
#define MD_ERROR_SECURE_CHANNEL_FAILURE  0x800CC806L

//
// MessageId: MD_WARNING_PATH_NOT_INSERTED
//
// MessageText:
//
//  The path was not inserted into the string as requested. The probable cause is that the data is at an object at a higher level than the handle.
//
#define MD_WARNING_PATH_NOT_INSERTED     0x000CC807L

//
// MessageId: MD_ERROR_CANNOT_REMOVE_SECURE_ATTRIBUTE
//
// MessageText:
//
//  The METADATA_SECURE attribute cannot be removed from a data item via the GetData method. Use the DeleteData method to remove the secure data.
//
#define MD_ERROR_CANNOT_REMOVE_SECURE_ATTRIBUTE 0x800CC808L

//
// MessageId: MD_WARNING_SAVE_FAILED
//
// MessageText:
//
//  The metadata save prior to backup failed. The previous version of the data was backed up.
//
#define MD_WARNING_SAVE_FAILED           0x000CC809L

//
// MessageId: MD_ERROR_IISAO_INVALID_SCHEMA
//
// MessageText:
//
//  The schema information could not be loaded. A required key or property is missing from the metabase.
//
#define MD_ERROR_IISAO_INVALID_SCHEMA    0x800CC810L

//
// MessageId: MD_ERROR_READ_METABASE_FILE
//
// MessageText:
//
//  Unable to read the metabase file.  Look at eventlog for further details.
//
#define MD_ERROR_READ_METABASE_FILE      0x800CC819L

//
// MessageId: MD_ERROR_NO_SESSION_KEY
//
// MessageText:
//
//  Could not find session key in IIS_Global section of XML file.
//
#define MD_ERROR_NO_SESSION_KEY          0x800CC81DL


#endif  // _MDMSG_H_

