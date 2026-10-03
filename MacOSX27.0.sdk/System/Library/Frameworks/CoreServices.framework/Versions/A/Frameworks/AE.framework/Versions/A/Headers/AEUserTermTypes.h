/*
 *  AEUserTermTypes.h — Apple Events AEUT resource format interfaces.
 *  Copyright © 1999-2026 Apple Inc. All rights reserved.
 */
#ifndef __AEUSERTERMTYPES__
#define __AEUSERTERMTYPES__

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif


#include <os/availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#pragma pack(push, 2)

CF_ENUM(OSType) {
  kAEUserTerminology            = 'aeut', ///< 0x61657574
  kAETerminologyExtension       = 'aete', ///< 0x61657465
  kAEScriptingSizeResource      = 'scsz', ///< 0x7363737a
  kAEOSAXSizeResource           = 'osiz' ///< Resource type of a scripting addition's (osax) size resource; see the `kOSIZ...` flag bits below.
};

enum {
  kAEUTHasReturningParam        = 31, ///< if event has a keyASReturning param
  kAEUTOptional                 = 15, ///< if something is optional
  kAEUTlistOfItems              = 14, ///< if property or reply is a list.
  kAEUTEnumerated               = 13, ///< if property or reply is of an enumerated type.
  kAEUTReadWrite                = 12, ///< if property is writable.
  kAEUTChangesState             = 12, ///< if an event changes state.
  kAEUTTightBindingFunction     = 12, ///< if this is a tight-binding precedence function.
                                        /* AppleScript 1.3: new bits for reply, direct parameter, parameter, and property flags */
  kAEUTEnumsAreTypes            = 11, ///< if the enumeration is a list of types, not constants
  kAEUTEnumListIsExclusive      = 10, ///< if the list of enumerations is a proper set
  kAEUTReplyIsReference         = 9, ///< if the reply is a reference, not a value
  kAEUTDirectParamIsReference   = 9, ///< if the direct parameter is a reference, not a value
  kAEUTParamIsReference         = 9, ///< if the parameter is a reference, not a value
  kAEUTPropertyIsReference      = 9, ///< if the property is a reference, not a value
  kAEUTNotDirectParamIsTarget   = 8, ///< if the direct parameter is not the target of the event
  kAEUTParamIsTarget            = 8, ///< if the parameter is the target of the event
  kAEUTApostrophe               = 3, ///< if a term contains an apostrophe.
  kAEUTFeminine                 = 2, ///< if a term is feminine gender.
  kAEUTMasculine                = 1, ///< if a term is masculine gender.
  kAEUTPlural                   = 0 ///< if a term is plural.
};

/// The layout of an application's `'scsz'` (Scripting Size) resource, read by the Apple Event
/// Manager/OSA to learn how much memory a scriptable application needs and how it wants to be
/// dispatched to. `scriptingSizeFlags` holds the `kLaunchToGetTerminology`/
/// `kDontFindAppBySignature`/`kAlwaysSendSubject` bits below; the remaining fields give the
/// minimum, preferred, and maximum stack and heap sizes the application should be launched
/// with.
struct TScriptingSizeResource {
  SInt16              scriptingSizeFlags;
  UInt32              minStackSize;
  UInt32              preferredStackSize;
  UInt32              maxStackSize;
  UInt32              minHeapSize;
  UInt32              preferredHeapSize;
  UInt32              maxHeapSize;
};
typedef struct TScriptingSizeResource   TScriptingSizeResource;
enum {
  kLaunchToGetTerminology       = (1 << 15), ///< If kLaunchToGetTerminology is 0, 'aete' is read directly from res file.  If set to 1, then launch and use 'gdut' to get terminology.
  kDontFindAppBySignature       = (1 << 14), ///< If kDontFindAppBySignature is 0, then find app with signature if lost.  If 1, then don't
  kAlwaysSendSubject            = (1 << 13) ///< If kAlwaysSendSubject 0, then send subject when appropriate. If 1, then every event has Subject Attribute
};

/// The pre-AppleScript-1.3 name for `kLaunchToGetTerminology` (same bit, `1 << 15`, in
/// `scriptingSizeFlags`), kept for source compatibility with older code.
/* old names for above bits. */
enum {
  kReadExtensionTermsMask       = (1 << 15)
};

enum {
                                        /* AppleScript 1.3: Bit positions for osiz resource */
                                        /* AppleScript 1.3: Bit masks for osiz resources */
  kOSIZDontOpenResourceFile     = 15, ///< If set, resource file is not opened when osax is loaded
  kOSIZdontAcceptRemoteEvents   = 14, ///< If set, handler will not be called with events from remote machines
  kOSIZOpenWithReadPermission   = 13, ///< If set, file will be opened with read permission only
  kOSIZCodeInSharedLibraries    = 11 ///< If set, loader will look for handler in shared library, not osax resources
};


#pragma pack(pop)


#endif /* __AEUSERTERMTYPES__ */

