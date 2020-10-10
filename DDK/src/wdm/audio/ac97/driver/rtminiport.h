/********************************************************************************
**    Copyright (c) 1998-2000 Microsoft Corporation. All Rights Reserved.
**
**       Portions Copyright (c) 1998-1999 Intel Corporation
**
********************************************************************************/

#ifndef _RTMINIPORT_H_
#define _RTMINIPORT_H_

#include "shared.h"

/*****************************************************************************
 * Constants
 *****************************************************************************
 */
const int WAVE_SAMPLERATES_TESTED = 7;
const int MIC_SAMPLERATES_TESTED = 4;

const DWORD dwWaveSampleRates[WAVE_SAMPLERATES_TESTED] =
    {48000, 44100, 32000, 22050, 16000, 11025, 8000};
const DWORD dwMicSampleRates[MIC_SAMPLERATES_TESTED] =
    {48000, 32000, 16000, 8000};

const int PIN_WAVEOUT_OFFSET = (PIN_WAVEOUT / 2);
const int PIN_WAVEIN_OFFSET  = (PIN_WAVEIN / 2);
const int PIN_MICIN_OFFSET   = (PIN_MICIN / 2);

/*****************************************************************************
 * Forward References
 *****************************************************************************
 */
class CRTStream;

extern NTSTATUS CreateRTStream
(
    OUT     CRTStream **   pRTStream
);

/*****************************************************************************
 * Classes
 *****************************************************************************
 */

/*****************************************************************************
 * CRTMiniport
 *****************************************************************************
 * ICH wave PCI miniport.  This object is associated with the device and is
 * created when the device is started.  The class inherits IRTMiniport
 * so it can expose this interface, CUnknown so it automatically gets
 * reference counting and aggregation support, and IPowerNotify for ACPI 
 * power management notification.
 */
class CRTMiniport : public IRTMiniport,
                        public IPowerNotify,
                        public CUnknown
{
private:
    // The stream class accesses a lot of private member variables.
    // A better way would be to abstract the access through member
    // functions which on the other hand would produce more overhead
    // both in CPU time and programming time.
    friend class CRTStream;

    //
    // CRTMiniport private variables
    //
    CRTStream           *Streams[PIN_MICIN_OFFSET + 1];
    PRTPORT             Port;           // Port driver object.
    PADAPTERCOMMON      AdapterCommon;  // Adapter common object.
    PINTERRUPTSYNC      InterruptSync;  // Interrupt Sync.
    DEVICE_POWER_STATE  m_PowerState;   // advanced power control.
    DWORD               m_dwChannelMask; // Channel config for speaker positions.
    WORD                m_wChannels;      // Number of channels.

    /*************************************************************************
     * CRTMiniport methods
     *************************************************************************
     * These are private member functions used internally by the object.  See
     * MINWAVE.CPP for specific descriptions.
     */

    //
    // Checks and connects the miniport to the resources.
    //
    NTSTATUS ProcessResources
    (
        IN   PRESOURCELIST     ResourceList
    );

    //
    // Tests the data format but not the sample rate.
    //
    NTSTATUS TestDataFormat
    (
        IN PKSDATAFORMAT Format,
        IN WavePins      Pin
    );

    // Test for standard sample rate support and fill the data range information
    // in the structures below.
    NTSTATUS BuildDataRangeInformation (void);

public:
    /*************************************************************************
     * The following two macros are from STDUNK.H.  DECLARE_STD_UNKNOWN()
     * defines inline IUnknown implementations that use CUnknown's aggregation
     * support.  NonDelegatingQueryInterface() is declared, but it cannot be
     * implemented generically.  Its definition appears in MINWAVE.CPP.
     * DEFINE_STD_CONSTRUCTOR() defines inline a constructor which accepts
     * only the outer unknown, which is used for aggregation.  The standard
     * create macro (in MINWAVE.CPP) uses this constructor.
     */
    DECLARE_STD_UNKNOWN ();
    DEFINE_STD_CONSTRUCTOR (CRTMiniport);
    ~CRTMiniport ();

    //
    // Include IRTMiniport (public/exported) methods
    //
    IMP_IRTMiniport;

    //
    // IPowerNotify methods
    //
    IMP_IPowerNotify;

    //
    // This static functions is the interrupt service routine which is
    // not stream related, but services all streams at once.
    //
    static NTSTATUS InterruptServiceRoutine
    (
        IN      PINTERRUPTSYNC  InterruptSync,
        IN      PVOID           StaticContext
    );

    //
    // This is the property handler for KSPROPERTY_AUDIO_CHANNEL_CONFIG of the
    // DAC node.
    //
    static NTSTATUS PropertyChannelConfig
    (
        IN      PPCPROPERTY_REQUEST PropertyRequest
    );
};

#endif          // _MINWAVE_H_


