/*
 * Copyright (C) 2022 Apple Inc. All rights reserved.
 *
 * This document is the property of Apple Inc.
 * It is considered confidential and proprietary.
 *
 * This document may not be reproduced or transmitted in any form,
 * in whole or in part, without the express written permission of
 * Apple Inc.
 */

#pragma once

#include <IOKit/IOService.h>
#include <IOKit/IOCommandGate.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOKernelReporters.h>

#include "VTLInterfaceTypes.hpp"
#include "VTLSession.hpp"
#include "VTLQueue.hpp"

#define kVTLTrafficBufferSize "VTLTrafficBufferSize"
#define kVTLTrafficBurstSize  "VTLTrafficBurstSize"
#define kVTLTrafficFrequency  "VTLTrafficFrequency"

class VTLTransportInterface;

class VTLAdapter : public IOService {
    
    OSDeclareDefaultStructors(VTLAdapter);
    using super = IOService;

public:
    
    using CreateSessionResult = struct {
        OSSharedPtr<VTLSession> session;
        IOReturn creationStatus;
    };

    virtual bool start(IOService *provider) APPLE_KEXT_OVERRIDE;
    virtual void free(void) APPLE_KEXT_OVERRIDE;
    virtual IOService *probe(IOService *provider, int32_t *score) APPLE_KEXT_OVERRIDE;

    virtual IOReturn newUserClient( task_t owningTask, void * securityID,
        UInt32 type, OSDictionary * properties,
        LIBKERN_RETURNS_RETAINED IOUserClient ** handler ) override;

    /*!
     @function createSession
     Create an VTL session with remote counterpart
     @param trafficProperties a dictionary of traffic properties that will be used for admission. Worst case scenario must be provided. Session bandwidth requirements will be derived from this parameters.
     Must include OSNumber values for the following keys:
     kVTLTrafficBufferSize - maximum buffer size that will be transferred (in bytes)
     kVTLTrafficBurstSize - maximum number of buffers that can be sent at once (in bytes)
     kVTLTrafficFrequency - max frequency (in msec) in which bursts of traffic can be sent. For example: kVTLTrafficFrequency = 5 -> burst of data can be sent every 5 msec
     @param sessionProperties a dictionary of user-specified properties that will be passed to remote side. Upon successfull session creation, remote VTLSessionService object will have those properties.
     @param options optional flags for session creation.
     @return a tuple with new session pointer and a creationStatus. If creationStatus is not kIOReturnSuccess - session object is undefined and should not be referenced.
     
     */
        
    VTLAdapter::CreateSessionResult createSession(OSSharedPtr<OSDictionary> trafficProperties, OSSharedPtr<OSDictionary> sessionProperties, IOOptionBits options = 0);

    IOReturn sendCloseSessionMessage(OSSharedPtr<OSDictionary> properties);
    IOReturn closeSession(OSSharedPtr<OSDictionary> properties);
    // IOReturn signalSessionActivated(VTLSessionID sessionID);
    //TODO: willTerminate/didTerminate
    

    VTLCommandTag getCommandTag(VTLCommandType type);

private:

    OSSharedPtr<VTLTransportInterface> transport_;
    OSSharedPtr<IOWorkLoop> controlWorkloop_;
    OSSharedPtr<IOCommandGate> controlCmdGate_;
    OSSharedPtr<IOInterruptEventSource> controlMessagesHandler_;
    OSSharedPtr<VTLQueue> controlRequestsQueue_;
    
    IOReturn createSessionEvent_;
    
    //VTLAdapterCommand VTLAdapterCommand_;
    OSSharedPtr<IOMemoryDescriptor> VTLAdapterCommandMemDesc_;
    OSSharedPtr<VTLRequest> VTLAdapterCommand_;
    
    // Available bandwidth in bytes per second
    IOByteCount64 availableBandwidth_;
    
    VTLSessionID clientID_;
    
    // Support single user client for now
    OSSharedPtr<IOService> activeUserClient_;

    volatile VTLCommandTag commandTags_[VTLCommandType::NUM_COMMANDS];
    
    void controlMessageCallback(OSSharedPtr<VTLRequest> request, IOReturn status, IOByteCount bytesTransferred);
    void controlMessageHandler(IOInterruptEventSource *source, int count);
    void messageSentCallback(OSSharedPtr<IOMemoryDescriptor> descriptor, IOReturn status, IOByteCount bytesTransferred);
    void controlSessionActivateCallback(IOReturn activationStatus);
    
    IOReturn admitSession(VTLSessionID sid, OSSharedPtr<OSDictionary> txProperties);

};


OSSharedPtr<const OSSymbol> createUserClientPlugInPathString( void );
