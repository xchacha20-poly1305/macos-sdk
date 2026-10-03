/*
 *  AEMach.h — Apple Events over Mach message interfaces.
 *  Copyright © 1999-2026 Apple Inc. All rights reserved.
 */
#ifndef __AEMACH__
#define __AEMACH__

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif

#ifndef __AEDATAMODEL__
#include <AE/AEDataModel.h>
#endif


#if TARGET_RT_MAC_MACHO
#ifndef _MACH_MESSAGE_H_
#include <mach/message.h>
#endif
#endif

#include <os/availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

// MARK: - AE Mach API
//
// Apple Events on macOS are implemented in terms of Mach messages.
// To facilitate writing server processes that can send and receive
// Apple Events, the following APIs are provided.
//
// Apple Events are directed to a well-known port uniquely tied to a
// process. The AE framework discovers this port based on the
// keyAddressAttr of the event (as specified in AECreateAppleEvent by
// the target parameter). If a port cannot be found,
// procNotFound (-600) is returned on AESend.
//
// The keyReplyPortAttr attribute specifies the mach_port_t to which
// an Apple Event reply should be directed. By default, replies go to
// the process's registered port. A client may specify its own port
// to receive queued replies.
//
// When AESendMessage is called with kAEWaitReply, an anonymous port
// blocks until the reply is received.
//
// In general the Apple Event APIs are thread safe, but the delivery
// mechanism (AEProcessAppleEvent, AEResumeTheCurrentEvent) is not.
// Thread-safe servers should avoid Apple Event routines that do not
// explicitly state their thread safety.

CF_ENUM(AEKeyword) {
  keyReplyPortAttr              = 'repp'	///< The `mach_port_t` to which an Apple Event reply should be directed. By default, replies go to the process's registered port. A client may specify its own port to receive queued replies.
};

CF_ENUM(DescType) {
  typeReplyPortAttr             = keyReplyPortAttr	///<	`typeReplyPortAttr` was misnamed and is deprecated; use `keyReplyPortAttr` instead.
};

/// Returns the Mach port registered by the Apple Event framework for this process.
///
/// This port is considered public and will be used by other applications to target
/// your process. You may add this port to a port set only if you are not also using
/// routines from HIToolbox — in that case HIToolbox retains control of this port and
/// Apple Events are dispatched through the main event loop.
///
extern mach_port_t
AEGetRegisteredMachPort(void)                                 API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Decodes a Mach message into an Apple Event and its related reply.
///
/// The reply is set up from fields of the event. You can call this routine if you
/// wish to dispatch or handle the event yourself. To return a reply to the sender:
///
/// ```c
/// AESendMessage(reply, NULL, kAENoReply, kAENormalPriority, kAEDefaultTimeout);
/// ```
///
/// If this message is a reply, `reply` will be initialized to `{ typeNull, 0 }` and
/// `event` will be the Apple Event reply with event class `typeAppleEvent`, class
/// `typeAppleEventReply`. The contents of the header are invalid after this call.
///
/// - Parameters:
///   - header: The incoming Mach message to decode.
///   - event: The Apple Event to decode the message into.
///   - reply: The Apple Event reply decoded from the message.
extern OSStatus
AEDecodeMessage(
  mach_msg_header_t *  header,
  AppleEvent *         event,
  AppleEvent *         reply)        /* can be NULL */        API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Decodes and dispatches an event to an event handler, then packages and returns the reply to the sender.
///
/// The contents of the header are invalid after this call ( and the entire \c mach_msg ) may have been changed by the process of extracting the contents into an AppleEvent and dispatching it to the application.
///
/// - Parameters:
///   - header: The incoming Mach message to dispatch.
/// - Note: Not thread safe.
extern OSStatus
AEProcessMessage(mach_msg_header_t * header)                  API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Sends an Apple Event to a target process.
///
/// If the target is the current process (specified by `typeProcessSerialNumber` of `{ 0, kCurrentProcess }`), the event is dispatched directly to the appropriate event handler without serialization.
///
/// - Parameters:
///   - event: The event to send.
///   - reply: The reply for the event; may be `NULL`.
///   - sendMode: The mode flags controlling how the event is sent.
///   - timeOutInTicks: The timeout in ticks; pass `0` for no timeout.
extern OSStatus
AESendMessage(
  const AppleEvent *  event,
  AppleEvent *        reply,                /* can be NULL */
  AESendMode          sendMode,
  long                timeOutInTicks)                         API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );




#ifdef __cplusplus
}
#endif

#endif /* __AEMACH__ */
