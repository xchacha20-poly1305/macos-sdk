//
//  VTLSession.hpp
//
//
//  Created by alexanderprutkov on 11/08/2022.
//

#pragma once

#include <IOKit/IOLib.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/IOService.h>

#include "VTLInterfaceTypes.hpp"
#include "VTLRequest.hpp"
#include "VTLQueue.hpp"
#include "VTLTransportInterface.hpp"

class VTLSessionService;

class VTLSession : public OSObject {
    
    OSDeclareAbstractStructors(VTLSession);
    
    using super = OSObject;
    
public:

    using ActivateCallback = void (*)(void* target, IOReturn activationStatus);
    
    enum class State
    {
        IDLE,
        WAIT_FOR_REMOTE,
        WAIT_FOR_LOCAL,
        ACTIVE,
        DEACTIVATING, // Teardown in progress - a caller is inside deactivateGated()
        DEACTIVATED,  // Terminal - session fully torn down; no transitions out
        INVALID
    };
    static const char* stringState(State state);

    enum class Event
    {
        REMOTE_ACTIVATED,
        LOCAL_ACTIVATED,
        LOCAL_DEACTIVATED,
        DEACTIVATION_COMPLETE  // Fired by deactivateGated() when cleanup finishes; drives DEACTIVATING→DEACTIVATED
    };
    static const char* stringEvent(Event e);
    
    IOReturn signalSMEvent(Event e);
    
    void setRemoteId(VTLSessionID remote);
    VTLSessionID getId() const;
    VTLSessionID getRemoteId() const;
    State getState() const;

    void setSessionService(VTLSessionService *svc);
    VTLSessionService *getSessionService() const;
    OSSharedPtr<VTLSessionService> copySessionService() const;

    void setSessionName(const char* name); // copies into name_[]; calls updateSessionStr()
    const char* str() const;               // returns pre-formatted "session [N]name" string

    virtual bool init(OSSharedPtr<VTLTransportInterface> transport, VTLSessionID id);
    virtual void free() APPLE_KEXT_OVERRIDE;
    
    /*!
     @function setTarget
     Set the target pointer to be used during Tx/Rx/Activate callbacks. Currently a single target is used for all callbacks
     @param target a pointer to a target. Can be anything
     */
    virtual void setTarget(void* target);
    
    /*!
     @function registerActivationCallback
     Register an ActivateCallback to be used when a session is activated. The callback will run from VTL thread context, and it *shall not* issue any lengthy or blocking operations.
      Ideally, the callback should signal client that session is ready for read/write operations
     @param callback a callback to invoke. Callback parameters are:
            1. target - pointer that was set during setTarget() call
            2. activationStatus - status of session activation.

     @return registration status.
     */
    virtual IOReturn registerActivationCallback(ActivateCallback callback);
    
    // For future iovec support...
    //virtual OSSharedPtr<VTLRequest> createRequest(VTLRequest::VTLRequestDirection direction, OSSharedPtr<OSArray> descriptors) = 0;
    virtual OSSharedPtr<VTLRequest> createRequest(VTLRequest::VTLRequestDirection direction, OSSharedPtr<IOMemoryDescriptor> descriptor) = 0;
    virtual OSSharedPtr<VTLRequest> createRequest(VTLRequest::VTLRequestDirection direction, size_t size) { panic("unsupported"); return OSMakeShared<VTLRequest>(); }
    virtual OSSharedPtr<VTLRequest> createRequest(VTLRequest::VTLRequestDirection direction, UInt32 rangeCount, IOAddressRange ranges[] ) { panic("unsupported"); return OSMakeShared<VTLRequest>(); }
    
    /*!
     @function submitRequest
     Submit a VTLRequest.
     @param request - a request to submit.
     @param ranges - array of buffers to submit (pointer and size)
     @param rangeCount - length of ranges array
     @return operation status.
     */
    virtual IOReturn submitRequest(OSSharedPtr<VTLRequest> request, IOAddressRange ranges[], UInt32 rangeCount);

    /*!
     @function submitRequest
     Submit a VTLRequest.
     @param request - a request to submit.
     @return operation status.
     */
    virtual IOReturn submitRequest(OSSharedPtr<VTLRequest> request) = 0;
        
    /*!
     @function clearRxRequests
     Clears out all pending RX requests

     @return operation status.
     */
    virtual IOReturn clearRxRequests() = 0;

    virtual IOReturn abortRequest(VTLRequest *request);

    void trackInflightRequest();
    void untrackInflightRequest();
    // Sleeps the calling thread (plain IOLock) until inflightCount_ reaches 0 or the
    // timeout expires. Returns the remaining inflight count (0 = fully drained).
    // NOTE: USB3StreamingSession does NOT call this — it uses commandSleep inside
    // deactivateGated() so the workloop can continue processing completions while waiting.
    // This method is the fallback for non-workloop callers (e.g. future transports).
    uint32_t waitForInflightRequests(uint32_t timeoutMs);
    void abortInflightRequests();
    
    virtual IOReturn destroyRequest(VTLRequestID requestID);
    virtual OSSharedPtr<VTLRequest> copyRequestForID(VTLRequestID requestID);
    virtual void debugPrintRequests();

    /*!
    @function usesDMACommands
    returns whether the session or underlying transport makes use of DMA commands
    */
    virtual inline bool usesDMACommands() { return false; }

    /*!
     @function activate
     Activate this session asyncronously. Should be called when client installed Tx/Rx/Activate callbacks and the target is set. Upon activation, installed ActivateCallback is called
     
     @return operation status.
     */
    virtual IOReturn activate() = 0;

    /*!
     @function deactivate
     Deactivate this session asyncronously. Should be called when client disconnects from the session. Remote side will be signalled deactivation

     @return operation status.
     */
    virtual IOReturn deactivate();

protected:
    VTLSessionID id_;
    VTLSessionID remoteId_;
    ActivateCallback activateCallback_ = nullptr;
    void* target_;

    IOSimpleLock *SMLock_ = nullptr;
    State SMState_;

    volatile uint32_t inflightCount_;
    IOLock* inflightWaitLock_;

    IOReturn trackRequest(OSSharedPtr<VTLRequest> request);

    OSSharedPtr<VTLTransportInterface> transport_;

    State advanceSM(Event e);

    /*!
     @function notifyInflightDrained
     Called (from any context) when inflightCount_ transitions to 0. Subclasses override
     this to wake any thread sleeping in a command-gate wait for inflight drain.
     */
    virtual void notifyInflightDrained() {}

    virtual bool okToRead() const;
    virtual bool okToWrite() const;

private:
    OSSharedPtr<OSArray> requests_;
    IOLock*              requestsLock_ = nullptr;

    char name_[64]       = {}; // set by setSessionName()
    char sessionStr_[96] = {}; // pre-formatted, rebuilt by updateSessionStr()
    void updateSessionStr();

    VTLSessionService *sessionService_ = nullptr; // unretained; guarded by requestsLock_; cleared in VTLSessionService::stop()

};

class VTLSessionService : public IOService {
    
    OSDeclareDefaultStructors(VTLSessionService);
    using super = IOService;
    
public:
    enum class Role
    {
        LOCAL,
        REMOTE,
    };
    
    virtual bool start(IOService *provider) APPLE_KEXT_OVERRIDE;
    virtual bool terminate(IOOptionBits options = 0) APPLE_KEXT_OVERRIDE;
    virtual bool willTerminate(IOService *provider, IOOptionBits options) APPLE_KEXT_OVERRIDE;
    virtual bool didTerminate(IOService *provider, IOOptionBits options, bool *defer) APPLE_KEXT_OVERRIDE;
    virtual void stop(IOService *provider) APPLE_KEXT_OVERRIDE;
    virtual bool matchPropertyTable( OSDictionary * table, SInt32 *score ) override;

    static OSSharedPtr<VTLSessionService> withParams(OSSharedPtr<VTLSession> session,  VTLSessionService::Role role, OSSharedPtr<OSDictionary> sessionProperties);
    
    OSSharedPtr<VTLSession> getSession();
    
private:
    OSSharedPtr<VTLSession> session_;

};
