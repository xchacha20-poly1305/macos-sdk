//
//  
//
// Copyright (C) 2022 Apple Inc. All rights reserved.
//
// This document is the property of Apple Inc.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Apple Inc.
	
//
//  VTLTransportInterface.hpp
//  VTLInterface
//
//  Created by alexanderprutkov on 07/11/2022.
//

#pragma once

#include <IOKit/IOService.h>
#include "VTLInterfaceTypes.hpp"
//#include "VTLSession.hpp"

class VTLSession;

class VTLTransportInterface : public IOService {
    
    // Abstract structors for base class
    OSDeclareAbstractStructors(VTLTransportInterface);
    using super = IOService;

private:
    static constexpr char VTL_MAIN_TRANSPORT_BOOT_ARG[] = "vtl-main-transport";
    static constexpr size_t VTL_MAIN_TRANSPORT_BOOT_ARG_SIZE = 256;

    static constexpr char VTL_DEFAULT_TRANSPORT[] = "usb2";

public:
    virtual IOService* probe(IOService *provider, int32_t *score) APPLE_KEXT_OVERRIDE;
    virtual bool start(IOService *provider) APPLE_KEXT_OVERRIDE;
    virtual void stop(IOService *provider) APPLE_KEXT_OVERRIDE;

    virtual OSSharedPtr<VTLSession> getControlSession() = 0;
    virtual OSSharedPtr<VTLSession> getSession(VTLSessionID idx) = 0;
    
    virtual IOByteCount64 getAvailableBandwidth() = 0;


protected:
    virtual const char* getTransportBootArgName() const = 0;
};

