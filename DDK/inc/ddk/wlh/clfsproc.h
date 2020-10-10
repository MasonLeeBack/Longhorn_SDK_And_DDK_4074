/*=============================================================================

    Copyright (c) 1999-2000  Microsoft Corporation

    Module Name:

        clfsproc.h

    Abstract:

        Declares Common Log export API Kernel library..

    Author:

        Dexter Bradshaw [DexterB] 15-Feb-2000

    Environment:

        Kernel Mode

    Revision History:


=============================================================================*/
#ifndef __CLFSPROC_H__
#define __CLFSPROC_H__

#ifndef KERNEL_MODE
#   define KERNEL_MODE 1
#endif  KERNEL_MODE

#include <clfsmsg.h>
#include <clfs.h>

//
//	This is a hack.  --jacobl
//

#ifdef IAMCLFS
#include <clfsintf.h>
#endif


//------------------------------------------------------------------------------
// TYPE DEFINITIONS
//------------------------------------------------------------------------------

//
// CLFS_THREAD_CONTEXT
//
// Definition of the CLFS thread top-level context.
//

typedef struct _CLFS_THREAD_CONTEXT
{
    USHORT usReserved;              // Initial two bytes are reserved.
    ULONG ulClfs;                   // CLFS constant.
    PIRP pirpSavedContext;          // Stack of the saved top-level context.

} CLFS_THREAD_CONTEXT, *PCLFS_THREAD_CONTEXT, *PPCLFS_THREAD_CONTEXT;

#ifdef __cplusplus
extern "C"
{
#endif __cplusplus


//-----------------------------------------------------------------------------
// ClfsLsnEqual
//
// Check for the equivalence of LSNs.
//
//-----------------------------------------------------------------------------

BOOLEAN ClfsLsnEqual (
                    IN const CLFS_LSN* plsn1,
                    IN const CLFS_LSN* plsn2
                    );

//-----------------------------------------------------------------------------
// ClfsLsnLess
//
// Check if LSN1 is less than LSN2.
//
//-----------------------------------------------------------------------------

BOOLEAN ClfsLsnLess (
                    IN const CLFS_LSN* plsn1,
                    IN const CLFS_LSN* plsn2
                    );


//-----------------------------------------------------------------------------
// ClfsLsnGreater
//
// Check if LSN1 is  greater than LSN2.
//
//-----------------------------------------------------------------------------

BOOLEAN ClfsLsnGreater (
                    IN const CLFS_LSN* plsn1,
                    IN const CLFS_LSN* plsn2
                    );

//-----------------------------------------------------------------------------
// ClfsLsnNull
//
// Check whether or not an LSN is CLFS_LSN_NULL.
//
//-----------------------------------------------------------------------------

BOOLEAN ClfsLsnNull (IN const CLFS_LSN* plsn); 

//------------------------------------------------------------------------------
// ClfsLsnCreate
// 
// Create an LSN given a log identifier, a container identifier, a block
// offset and a bucket identifier.  Caller must test for invalid LSN after
// making this call.
//------------------------------------------------------------------------------

CLFS_LSN ClfsLsnCreate (
                    IN CLFS_CONTAINER_ID cidContainer,
                    IN ULONG offBlock,
                    IN ULONG cRecord
                    );

//-----------------------------------------------------------------------------
// ClfsLsnContainer
//
// Entry point to extract the container identifier from the LSN.
//-----------------------------------------------------------------------------

CLFS_CONTAINER_ID ClfsLsnContainer (IN const CLFS_LSN* plsn);


//-----------------------------------------------------------------------------
// ClfsLsnBlockOffset
//
// Entry point to extract the block offset from the LSN.
//-----------------------------------------------------------------------------

ULONG ClfsLsnBlockOffset (IN const CLFS_LSN* plsn);


//-----------------------------------------------------------------------------
// ClfsLsnRecordSequence 
//
// Entry point to extract the bucket identifier from the LSN.
//-----------------------------------------------------------------------------

ULONG ClfsLsnRecordSequence (IN const CLFS_LSN* plsn);


//------------------------------------------------------------------------------
// ClfsCreateLogFile
//
// Entry point to create a physical log file consisting of uniformly sized
// containers lying in a given directory path.
//------------------------------------------------------------------------------

NTSTATUS ClfsCreateLogFile (
                    OUT PPLOG_FILE_OBJECT pplfoLog,
                    IN PUNICODE_STRING puszLogFileName,
                    IN ACCESS_MASK fDesiredAccess,
                    IN DWORD dwShareMode,
                    IN PSECURITY_DESCRIPTOR psdLogFile,
                    IN ULONG fCreateDisposition,
                    IN ULONG fCreateOptions,
                    IN ULONG fFlags
                    );


//------------------------------------------------------------------------------
// ClfsDeleteLogByPointer
//
// Entry point to delete a physical log file and its underlying container
// storage referencing a log file object.
//------------------------------------------------------------------------------

NTSTATUS ClfsDeleteLogByPointer (IN PLOG_FILE_OBJECT plfoLog);


//------------------------------------------------------------------------------
// ClfsDeleteLogFile
//
// Entry point to delete a physical log file and its underlying container
// storage by name.
//------------------------------------------------------------------------------

NTSTATUS ClfsDeleteLogFile (
                    IN PUNICODE_STRING puszLogFileName,
                    IN PSECURITY_DESCRIPTOR psdLogFile
                    );

//------------------------------------------------------------------------------
// ClfsAddLogContainer
//
// Adds a log container to a given physical file identified by the log
// file object pointer.
//------------------------------------------------------------------------------

NTSTATUS ClfsAddLogContainer (
                    IN PLOG_FILE_OBJECT plfoLog,
                    IN PULONGLONG pcbContainer,
                    IN PUNICODE_STRING puszContainerPath
                    );

//------------------------------------------------------------------------------
// ClfsAddLogContainerSet
//
// Adds a set of log containers to a given physical file identified by the log
// file object pointer.
//------------------------------------------------------------------------------

NTSTATUS ClfsAddLogContainerSet (
                    IN PLOG_FILE_OBJECT plfoLog,
                    IN USHORT cContainers,
                    IN PULONGLONG pcbContainer OPTIONAL,
                    IN PUNICODE_STRING rguszContainerPath
                    );

//------------------------------------------------------------------------------
// ClfsRemoveLogContainer
//
// Removes a log container from a physical log file identified by
// the log file object pointer.
//------------------------------------------------------------------------------

NTSTATUS ClfsRemoveLogContainer (
                    IN PLOG_FILE_OBJECT plfoLog,
                    IN PUNICODE_STRING puszContainerPath,
                    IN BOOLEAN fForce
                    );

//------------------------------------------------------------------------------
// ClfsRemoveLogContainerSet
//
// Removes a set of log containers from a physical log file identified by
// the log file object pointer.
//------------------------------------------------------------------------------

NTSTATUS ClfsRemoveLogContainerSet (
                    IN PLOG_FILE_OBJECT plfoLog,
                    IN USHORT cContainers,
                    IN PUNICODE_STRING rgwszContainerPath,
                    IN BOOLEAN fForce
                    );

//------------------------------------------------------------------------------
// ClfsSetArchiveTail
//
// Sets the archive tail for either a client or physical log file
// depending on the type of the log handle.
//------------------------------------------------------------------------------

NTSTATUS ClfsSetArchiveTail (
                    IN PLOG_FILE_OBJECT plfoLog,
                    IN PCLFS_LSN plsnArchiveTail
                    );

//------------------------------------------------------------------------------
// ClfsSetEndOfLog
//
// Sets the end of log for either a client or physical log file
// depending on the type of the log handle.
//------------------------------------------------------------------------------

NTSTATUS ClfsSetEndOfLog (
                    IN PLOG_FILE_OBJECT plfoLog,
                    IN PCLFS_LSN plsnEnd
                    );


//------------------------------------------------------------------------------
// ClfsCreateScanContext
//
// Create a scan context to enumerate scan descriptors for storage containers 
// that back the physical log file object.
//------------------------------------------------------------------------------

NTSTATUS ClfsCreateScanContext (
                    IN PLOG_FILE_OBJECT plfoLog,
                    IN ULONG cFromContainer,
                    IN ULONG cContainers,
                    IN CLFS_SCAN_MODE eScanMode,
                    IN OUT PCLFS_SCAN_CONTEXT pcxScan
                    );


//------------------------------------------------------------------------------
// ClfsScanLogContainers
//
// Scan descriptors for storage containers backing the physical
// log file stream.
//------------------------------------------------------------------------------

NTSTATUS ClfsScanLogContainers (
                    IN OUT PCLFS_SCAN_CONTEXT pcxScan,
                    IN CLFS_SCAN_MODE eScanMode
                    );


//------------------------------------------------------------------------------
// ClfsGetContainerName
//
// ClfsGetContainerName gets the full path name of a container given its logical
// container identifier.
//
//------------------------------------------------------------------------------

NTSTATUS ClfsGetContainerName (
                    IN PLOG_FILE_OBJECT plfoLog,
                    IN CLFS_CONTAINER_ID cidLogicalContainer,
                    IN OUT PUNICODE_STRING puszContainerName,
                    OUT PULONG pcActualLenContainerName OPTIONAL
                    );


//------------------------------------------------------------------------------
// ClfsGetLogFileInformation
//
// Get log file information for a physical log and client stream
// specific to the log file object pointer.
//
// Deprecated.  Use ClfsQueryLogFileInformation instead (it is equivalent
// to this call if ClfsLogBasicInformation is used as information class).
//
//------------------------------------------------------------------------------

NTSTATUS ClfsGetLogFileInformation (
                    IN PLOG_FILE_OBJECT plfoLog,
                    OUT PCLFS_INFORMATION pinfoBuffer,
                    IN OUT PULONG pcbBuffer
                    );

//------------------------------------------------------------------------------
// ClfsQueryLogFileInformation
//
// Get log file information for a physical log and client stream
// specific to the log file object pointer.
//------------------------------------------------------------------------------

NTSTATUS ClfsQueryLogFileInformation (
					IN PLOG_FILE_OBJECT plfoLog,
                    IN CLFS_LOG_INFORMATION_CLASS eInformationClass,
					OUT PVOID pinfoBuffer,
					IN OUT PULONG pcbBuffer
					);

//------------------------------------------------------------------------------
// ClfsReadRestartArea
//
// Read the last restart area successfully written to a physical or 
// client log stream given a marshalling context.
//------------------------------------------------------------------------------

NTSTATUS ClfsReadRestartArea (
                    IN OUT PVOID pvMarshalContext,
                    OUT PVOID *ppvRestartBuffer,
                    OUT PULONG pcbRestartBuffer,
                    OUT PCLFS_LSN plsn,
                    OUT PVOID *ppvReadContext
                    );

//------------------------------------------------------------------------------
// ClfsCopyRestartArea
//
// Read and copy the last restart area successfully written to a physical or 
// client log stream given a marshalling context.
//------------------------------------------------------------------------------

NTSTATUS ClfsCopyRestartArea (
                    IN OUT PVOID pvMarshalContext,
                    OUT PVOID pvRestartBuffer,
                    IN ULONG cbRestartBuffer,
                    OUT PULONG pcbBytesRead,
                    OUT PCLFS_LSN plsn,
                    OUT PVOID *ppvReadContext
                    );


//------------------------------------------------------------------------------
// ClfsReadPreviousRestartArea
//
// Read the previous restart area successfully written to a physical or 
// client log stream given the read context created by the a call to
// ClfsReadRestartArea.
//------------------------------------------------------------------------------

NTSTATUS ClfsReadPreviousRestartArea (
                    IN PVOID pvReadContext,
                    OUT PVOID *ppvRestartBuffer,
                    OUT PULONG pcbRestartBuffer,
                    OUT PCLFS_LSN plsnRestart
                    );

//------------------------------------------------------------------------------
// ClfsCopyPreviousRestartArea
//
// Read and copy the last restart area successfully written to a physical or 
// client log stream given the read context created by the a call to
// ClfsReadRestartArea.
//------------------------------------------------------------------------------

NTSTATUS ClfsCopyPreviousRestartArea (
                    IN PVOID pvReadContext,
                    OUT PVOID pvRestartBuffer,
                    IN ULONG cbRestartBuffer,
                    OUT PULONG pcbBytesRead,
                    OUT PCLFS_LSN plsnRestart
                    );


//------------------------------------------------------------------------------
// ClfsWriteRestartArea
//
// Write a new restart area to a physical or client log stream given a
// a marshalling context.
//------------------------------------------------------------------------------

NTSTATUS ClfsWriteRestartArea (
                    IN OUT PVOID pvMarshalContext,
                    IN PVOID pvRestartBuffer,
                    IN ULONG cbRestartBuffer,
                    IN PCLFS_LSN plsnBase,
                    IN ULONG fFlags,
                    OUT PULONG pcbWritten OPTIONAL,
                    OUT PCLFS_LSN plsnNext OPTIONAL
                    );


//------------------------------------------------------------------------------
// ClfsCloseAndResetLogFile
//
// Orderly shutdown of a physical or client log file stream given the log file
// object pointer.
//------------------------------------------------------------------------------

NTSTATUS ClfsCloseAndResetLogFile (IN PLOG_FILE_OBJECT plfoLog);


//------------------------------------------------------------------------------
// ClfsCloseLogFileObject
//
// Close a log file object without the orderly shutdown of the log.
//------------------------------------------------------------------------------

NTSTATUS  ClfsCloseLogFileObject (IN PLOG_FILE_OBJECT plfoLog);


//------------------------------------------------------------------------------
// NtCreateMarshallingArea
//
// Initalize a marshalling area for a physical or client log
// file stream given log file object pointer.
//------------------------------------------------------------------------------

NTSTATUS ClfsCreateMarshallingArea (
                    IN PLOG_FILE_OBJECT plfoLog,
                    IN POOL_TYPE ePoolType,
                    IN PALLOCATE_FUNCTION pfnAllocBuffer OPTIONAL,
                    IN PFREE_FUNCTION pfnFreeBuffer OPTIONAL,
                    IN ULONG cbMarshallingBuffer,
                    IN ULONG cMaxBuffers,
                    OUT PVOID *ppvMarshalContext
                    );

//------------------------------------------------------------------------------
// ClfsDeleteMarshallingArea
//
// Delete a marshalling area for a physical or client log
// file stream.
//------------------------------------------------------------------------------

NTSTATUS ClfsDeleteMarshallingArea (IN PVOID pvMarshalContext);


//------------------------------------------------------------------------------
// ClfsReserveAndAppendLog
//
// Reserve space and append log buffers to a physical or client
// log stream.
//------------------------------------------------------------------------------

NTSTATUS ClfsReserveAndAppendLog (
                    IN PVOID pvMarshalContext,
                    IN PCLFS_WRITE_ENTRY rgWriteEntries OPTIONAL,
                    IN ULONG cWriteEntries,
                    IN PCLFS_LSN plsnUndoNext OPTIONAL,
                    IN PCLFS_LSN plsnPrevious OPTIONAL,
                    IN ULONG cReserveRecords,
                    IN OUT PLONGLONG rgcbReservation OPTIONAL,
                    IN ULONG fFlags,
                    OUT PCLFS_LSN plsn OPTIONAL
                    );

//------------------------------------------------------------------------------
// ClfsReserveAndAppendLogAligned
//
// Reserve space and append log buffers to a physical or client
// log stream, aligning each of the write entries according to
// the alignment specified.
//------------------------------------------------------------------------------

NTSTATUS ClfsReserveAndAppendLogAligned (
                    IN PVOID pvMarshalContext,
                    IN PCLFS_WRITE_ENTRY rgWriteEntries OPTIONAL,
                    IN ULONG cWriteEntries,
                    IN ULONG cbEntryAlignment,
                    IN PCLFS_LSN plsnUndoNext OPTIONAL,
                    IN PCLFS_LSN plsnPrevious OPTIONAL,
                    IN ULONG cReserveRecords,
                    IN OUT PLONGLONG rgcbReservation OPTIONAL,
                    IN ULONG fFlags,
                    OUT PCLFS_LSN plsn OPTIONAL
                    );

//------------------------------------------------------------------------------
// ClfsAlignReservedLog
//
// Given a valid marshalling context, allocate an aggregate number of reserved
// records and bytes.
//------------------------------------------------------------------------------

NTSTATUS ClfsAlignReservedLog (
                    IN PVOID pvMarshalContext,
                    IN ULONG cRecords,
                    IN LONGLONG rgcbReservation [],
                    OUT PLONGLONG pcbAlignReservation
                    );


//------------------------------------------------------------------------------
// ClfsAllocReservedLog
//
// Given a valid marshalling context, allocate an aggregate number of reserved
// records and bytes.
//------------------------------------------------------------------------------

NTSTATUS ClfsAllocReservedLog (
                    IN PVOID pvMarshalContext,
                    IN ULONG cRecords,
                    IN PLONGLONG pcbAdjustment
                    );


//------------------------------------------------------------------------------
// ClfsFreeReservedLog
//
// Set the reserved log space to a new size or specify a delta
// for the reserved space given log file.
//------------------------------------------------------------------------------

NTSTATUS ClfsFreeReservedLog (
                    IN PVOID pvMarshalContext,
                    IN ULONG cRecords,
                    IN PLONGLONG pcbAdjustment
                    );

//------------------------------------------------------------------------------
// ClfsFlushBuffers
// 
// Append all buffers in the marshalling area up to the flush queue and flush
// all buffers up to the disk.
//------------------------------------------------------------------------------

NTSTATUS ClfsFlushBuffers (IN PVOID pvMarshalContext);



//------------------------------------------------------------------------------
// ClfsFlushToLsn
// 
// Flush all buffers in the marshalling area up to a target LSN to the flush
// queue and flush all buffers up to the target LSN to the disk.
//------------------------------------------------------------------------------

NTSTATUS ClfsFlushToLsn (
                    IN PVOID pvMarshalContext,
                    IN PCLFS_LSN plsnFlush,
                    OUT PCLFS_LSN plsnLastFlushed OPTIONAL
                    );

//------------------------------------------------------------------------------
// ClfsReadLogRecord
//
// Read a log record from a physical or client log stream given
// a starting LSN.
//------------------------------------------------------------------------------

NTSTATUS ClfsReadLogRecord (
                    IN PVOID pvMarshalContext,
                    IN OUT PCLFS_LSN plsnFirst,
                    IN CLFS_CONTEXT_MODE peContextMode,
                    OUT PVOID *ppvReadBuffer,
                    OUT PULONG pcbReadBuffer,
                    OUT PCLFS_RECORD_TYPE peRecordType,
                    OUT PCLFS_LSN plsnUndoNext,
                    OUT PCLFS_LSN plsnPrevious,
                    OUT PVOID* ppvReadContext
                    );

//------------------------------------------------------------------------------
// ClfsReadNextLogRecord
//
// Read the next log record from a given marshalling context.
//------------------------------------------------------------------------------

NTSTATUS ClfsReadNextLogRecord (
                    IN OUT PVOID pvReadContext,
                    OUT PVOID *ppvBuffer,
                    OUT PULONG pcbBuffer,
                    IN OUT PCLFS_RECORD_TYPE peRecordType,
                    IN PCLFS_LSN plsnUser OPTIONAL,
                    OUT PCLFS_LSN plsnUndoNext,
                    OUT PCLFS_LSN plsnPrevious,
                    OUT PCLFS_LSN plsnRecord
                    );

//------------------------------------------------------------------------------
// ClfsCopyLogRecord
//
// Read and copy a log record from a physical or client log stream given
// a starting LSN.
//------------------------------------------------------------------------------

NTSTATUS ClfsCopyLogRecord (
                    IN PVOID pvMarshalContext,
                    IN OUT PCLFS_LSN plsnFirst,
                    IN CLFS_CONTEXT_MODE peContextMode,
                    IN OUT PVOID pvReadBuffer,
                    IN ULONG cbReadBuffer,
                    OUT PCLFS_RECORD_TYPE peRecordType,
                    OUT PCLFS_LSN plsnUndoNext,
                    OUT PCLFS_LSN plsnPrevious,
                    OUT PULONG pcbRecordLength,
                    OUT PVOID* ppvReadContext
                    );


//------------------------------------------------------------------------------
// ClfsCopyNextLogRecord
//
// Read and copy the next log record from a given marshalling context.
//------------------------------------------------------------------------------

NTSTATUS ClfsCopyNextLogRecord (
                    IN OUT PVOID pvReadContext,
                    IN OUT PVOID pvBuffer,
                    IN ULONG cbBuffer,
                    IN OUT PCLFS_RECORD_TYPE peRecordType,
                    IN PCLFS_LSN plsnUser OPTIONAL,
                    OUT PCLFS_LSN plsnUndoNext,
                    OUT PCLFS_LSN plsnPrevious,
                    OUT PCLFS_LSN plsnRecord,
                    OUT PULONG pcbRecordLength
                    );



//------------------------------------------------------------------------------
// ClfsTerminateReadLog
//
// Terminate the read context.
//------------------------------------------------------------------------------

NTSTATUS ClfsTerminateReadLog (IN PVOID pvCursorContext);


//------------------------------------------------------------------------------
// ClfsGetLastLsn
//
// Get the last used LSN.
//------------------------------------------------------------------------------

NTSTATUS ClfsGetLastLsn (
                    IN PLOG_FILE_OBJECT plfoLog,
                    OUT PCLFS_LSN plsnLast
                    );


//------------------------------------------------------------------------------
// ClfsGetIoStatistics
//
// Get I/O statistics on the CLFS log file.
//------------------------------------------------------------------------------

NTSTATUS ClfsGetIoStatistics (
                    IN PLOG_FILE_OBJECT plfoLog,
                    IN OUT PVOID pvStatsBuffer,
                    IN ULONG cbStatsBuffer,
                    IN CLFS_IOSTATS_CLASS eStatsClass,
                    OUT PULONG pcbStatsWritten OPTIONAL
                    );



//-----------------------------------------------------------------------------
// ClfsLaterLsn
//
//      Method Description:
//
//          Increment an LSN by 1
//
//      Arguments:
//
//          plsn -- LSN to be incremented.
//          
//
//      Return Value:
//
//          A valid LSN next in sequence to the input LSN, if successful.
//          Otherwise, this function returns CLFS_LSN_INVALID.
//
//-----------------------------------------------------------------------------

CLFS_LSN
ClfsLaterLsn (IN PCLFS_LSN plsn);


//-----------------------------------------------------------------------------
// ClfsEarlierLsn
//
//      Method Description:
//
//          Decrement an LSN by 1
//
//      Arguments:
//
//          plsn -- LSN to be decremented.
//          
//
//      Return Value:
//
//          A valid LSN next in sequence to the input LSN, if successful.
//          Otherwise, this function returns CLFS_LSN_INVALID.
//
//-----------------------------------------------------------------------------

CLFS_LSN
ClfsEarlierLsn (IN PCLFS_LSN plsn);

//----------------------------------------------------------------------------
// ClfsLsnDifference
//
//      Method Description:
//
//          Find the approximate number of bytes between two LSNs.
//
//      Arguments:
//
//          plsnStart       -- LSN start of the log file range
//          plsnFinish      -- LSN finish of the log file range
//          cbContainer     -- size of a container
//          cbMaxBlock      -- maximum size of an I/O block
//          pcbDifference   -- approximate number of bytes between two LSNs.
//          
//          
//
//      Return Value:
//
//          STATUS_SUCCESS if difference is succeeds and an error status
//          otherwise.
//
//-----------------------------------------------------------------------------

NTSTATUS
ClfsLsnDifference (
    IN PCLFS_LSN    plsnStart,
    IN PCLFS_LSN    plsnFinish,
    IN ULONG        cbContainer,
    IN ULONG        cbMaxBlock,
    OUT PLONGLONG   pcbDifference
    );

//----------------------------------------------------------------------------
// ClfsValidTopLevelContext
//
//      Method Description:
//
//          Check that the current top level context is a common log (CLFS)
//          context.
//
//      Arguments:
//
//          pirp            -- reference to top of top-level context stack      
//          
//      Return Value:
//
//          TRUE if this is a valid CLFS top-level context and FALSE otherwise.
//
//-----------------------------------------------------------------------------

BOOLEAN
ClfsValidTopLevelContext (IN PIRP pirpTopLevelContext);

//
//	This is a hack.  --jacobl
//

#ifdef IAMCLFS

NTSTATUS
ClfsGetManagementSupportInterface(
    IN  PLOG_FILE_OBJECT            LogFileObject,
    OUT PPILOG_MANAGEMENT_SUPPORT   ManagementInterface
    );

NTSTATUS
ClfsGetObservableInterface(
    IN  PLOG_FILE_OBJECT LogFileObject,
    OUT PPIOBSERVABLE    ObservableInterface
    );

#endif

#ifdef __cplusplus
}
#endif __cplusplus

#endif  __CLFSPROC_H__

//-----------------------------------------------------------------------------
//                              END OF FILE
//-----------------------------------------------------------------------------

