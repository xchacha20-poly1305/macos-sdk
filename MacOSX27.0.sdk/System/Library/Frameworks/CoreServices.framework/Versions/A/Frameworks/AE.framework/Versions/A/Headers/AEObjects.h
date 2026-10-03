/*
 *  AEObjects.h — Object Support Library interfaces.
 *  Copyright © 1999-2026 Apple Inc. All rights reserved.
 */
#ifndef __AEOBJECTS__
#define __AEOBJECTS__

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif

#ifndef __APPLEEVENTS__
#include <AE/AppleEvents.h>
#endif

#include <os/availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

enum {
                                        /**** LOGICAL OPERATOR CONSTANTS  ****/
  kAEAND                        = 'AND ', ///< 0x414e4420
  kAEOR                         = 'OR  ', ///< 0x4f522020
  kAENOT                        = 'NOT ', ///< 0x4e4f5420
                                        /**** ABSOLUTE ORDINAL CONSTANTS  ****/
  kAEFirst                      = 'firs', ///< 0x66697273
  kAELast                       = 'last', ///< 0x6c617374
  kAEMiddle                     = 'midd', ///< 0x6d696464
  kAEAny                        = 'any ', ///< 0x616e7920
  kAEAll                        = 'all ', ///< 0x616c6c20
                                        /**** RELATIVE ORDINAL CONSTANTS  ****/
  kAENext                       = 'next', ///< 0x6e657874
  kAEPrevious                   = 'prev', ///< 0x70726576
                                        /**** KEYWORD CONSTANT    ****/
  keyAECompOperator             = 'relo', ///< 0x72656c6f
  keyAELogicalTerms             = 'term', ///< 0x7465726d
  keyAELogicalOperator          = 'logc', ///< 0x6c6f6763
  keyAEObject1                  = 'obj1', ///< 0x6f626a31
  keyAEObject2                  = 'obj2', ///< 0x6f626a32
                                        /*    ... for Keywords for getting fields out of object specifier records. */
  keyAEDesiredClass             = 'want', ///< 0x77616e74
  keyAEContainer                = 'from', ///< 0x66726f6d
  keyAEKeyForm                  = 'form', ///< 0x666f726d
  keyAEKeyData                  = 'seld' ///< 0x73656c64
};

CF_ENUM(AEKeyword) {
                                        /*    ... for Keywords for getting fields out of Range specifier records. */
  keyAERangeStart               = 'star', ///< 0x73746172
  keyAERangeStop                = 'stop', ///< 0x73746f70
                                        /*    ... special handler selectors for OSL Callbacks. */
  keyDisposeTokenProc           = 'xtok', ///< 0x78746f6b
  keyAECompareProc              = 'cmpr', ///< 0x636d7072
  keyAECountProc                = 'cont', ///< 0x636f6e74
  keyAEMarkTokenProc            = 'mkid', ///< 0x6d6b6964
  keyAEMarkProc                 = 'mark', ///< 0x6d61726b
  keyAEAdjustMarksProc          = 'adjm', ///< 0x61646a6d
  keyAEGetErrDescProc           = 'indc' ///< 0x696e6463
};

/****   VALUE and TYPE CONSTANTS    ****/
enum {
                                        /*    ... possible values for the keyAEKeyForm field of an object specifier. */
  formAbsolutePosition          = 'indx', ///< 0x696e6478
  formRelativePosition          = 'rele', ///< 0x72656c65
  formTest                      = 'test', ///< 0x74657374
  formRange                     = 'rang', ///< 0x72616e67
  formPropertyID                = 'prop', ///< 0x70726f70
  formName                      = 'name', ///< 0x6e616d65
  formUniqueID                  = 'ID  ', ///< 0x49442020
}
	;
CF_ENUM(DescType) {
                                        /*    ... relevant types (some of these are often pared with forms above). */
  typeObjectSpecifier           = 'obj ', ///< 0x6f626a20
  typeObjectBeingExamined       = 'exmn', ///< 0x65786d6e
  typeCurrentContainer          = 'ccnt', ///< 0x63636e74
  typeToken                     = 'toke', ///< 0x746f6b65
  typeRelativeDescriptor        = 'rel ', ///< 0x72656c20
  typeAbsoluteOrdinal           = 'abso', ///< 0x6162736f
  typeIndexDescriptor           = 'inde', ///< 0x696e6465
  typeRangeDescriptor           = 'rang', ///< 0x72616e67
  typeLogicalDescriptor         = 'logi', ///< 0x6c6f6769
  typeCompDescriptor            = 'cmpd', ///< 0x636d7064
  typeOSLTokenList              = 'ostl' ///< 0x6F73746C
};

/// Flags that control the behaviour of ``AEResolve``.  Combine additively.
enum {
  kAEIDoMinimum                 = 0x0000, ///< Resolve with no optional callbacks.
  kAEIDoWhose                   = 0x0001, ///< Engage whose-clause resolution.
  kAEIDoMarking                 = 0x0004, ///< Call the mark and adjust-marks callbacks during resolution.
  kAEPassSubDescs               = 0x0008, ///< Pass sub-specifiers down to accessor procs rather than pre-resolving them.
  kAEResolveNestedLists         = 0x0010, ///< Resolve each element of a list specifier individually.
  kAEHandleSimpleRanges         = 0x0020, ///< Let OSL handle simple `formRange` specifiers internally.
  kAEUseRelativeIterators       = 0x0040  ///< Use relative (prev/next) iteration when resolving relative-position specifiers.
};

/**** SPECIAL CONSTANTS FOR CUSTOM WHOSE-CLAUSE RESOLUTION */
enum {
  typeWhoseDescriptor           = 'whos', ///< 0x77686f73
  formWhose                     = 'whos', ///< 0x77686f73
  typeWhoseRange                = 'wrng', ///< 0x77726e67
  keyAEWhoseRangeStart          = 'wstr', ///< 0x77737472
  keyAEWhoseRangeStop           = 'wstp', ///< 0x77737470
  keyAEIndex                    = 'kidx', ///< 0x6b696478
  keyAETest                     = 'ktst' ///< 0x6b747374
};

/// A replacement token record used when manually resolving `formRange` key data.
///
/// When an accessor proc receives key data whose descriptor type is
/// `typeCurrentContainer` (`'ccnt'`), OSL has substituted the container token in
/// place of the original container descriptor.  Applications that resolve range
/// specifiers by calling ``AEResolve`` recursively can ignore this type; those that
/// walk the key data themselves will find one of these records when the range
/// boundary was expressed as a `typeCurrentContainer`.
struct ccntTokenRecord {
  DescType            tokenClass; ///< The descriptor type of the token.
  AEDesc              token;      ///< The token descriptor itself.
};
typedef struct ccntTokenRecord          ccntTokenRecord;
typedef ccntTokenRecord *               ccntTokenRecPtr;
typedef ccntTokenRecPtr *               ccntTokenRecHandle;
/// Legacy names for `AEDesc *` and `AEDesc **`, retained only for source compatibility with
/// pre-Carbon code that used the old naming convention (`OLDROUTINENAMES`). New code should
/// use `AEDesc *` directly.
#if OLDROUTINENAMES
typedef AEDesc *                        DescPtr;
typedef DescPtr *                       DescHandle;
#endif  /* OLDROUTINENAMES */

// MARK: - OSL callback signatures

/// Locates objects of a given class within a container and returns a token for them.
///
/// This is the central callback of the Object Support Library.  OSL calls it once per
/// resolution step when walking an object specifier chain.  The accessor must handle
/// every `(desiredClass, containerClass, form)` combination it registers, and return
/// `errAEEventNotHandled` for combinations it does not handle.
///
/// - Parameters:
///   - desiredClass: The four-character class code of the objects to find.
///   - container: The token (or null descriptor) identifying the container to search.
///   - containerClass: The class code of the container described by `container`.
///   - form: The key form (`formAbsolutePosition`, `formName`, etc.) describing how
///     `selectionData` identifies the target object(s).
///   - selectionData: A descriptor whose type and content depend on `form`.
///   - value: On successful return, a token descriptor (type `typeToken` or any
///     application-defined type) identifying the located object(s).  The caller owns
///     this descriptor; it will be disposed via the ``OSLDisposeTokenProcPtr`` callback.
///   - accessorRefcon: The refcon supplied when the accessor was installed.
/// - Returns: `noErr` on success, `errAENoSuchObject` if the object does not exist,
///   or `errAEEventNotHandled` if this accessor does not handle the given combination.
typedef CALLBACK_API( OSErr , OSLAccessorProcPtr )(DescType desiredClass, const AEDesc *container, DescType containerClass, DescType form, const AEDesc *selectionData, AEDesc *value, SRefCon accessorRefcon);

/// Tests a relational operator between two object tokens and returns the Boolean result.
///
/// OSL calls this when resolving a `formTest` specifier that contains a comparison
/// descriptor.  The two operands will already have been resolved to tokens by the time
/// this callback is invoked.
///
/// - Parameters:
///   - oper: The comparison operator, such as `kAEEquals` or `kAELessThan`.
///   - obj1: The first operand token.
///   - obj2: The second operand token.
///   - result: On return, `true` if the comparison holds; `false` otherwise.
/// - Returns: `noErr` on success, or an appropriate error code.
typedef CALLBACK_API( OSErr , OSLCompareProcPtr )(DescType oper, const AEDesc *obj1, const AEDesc *obj2, Boolean *result);

/// Returns the number of objects of a given class within a container.
///
/// OSL calls this when it needs to resolve an ordinal such as `kAELast`, `kAEMiddle`,
/// or `kAEAll`, and when it needs to validate an absolute index.
///
/// - Parameters:
///   - desiredType: The class code of the objects to count.
///   - containerClass: The class code of the container.
///   - container: A token identifying the container.
///   - result: On return, the number of objects of `desiredType` within `container`.
/// - Returns: `noErr` on success, or an appropriate error code.
typedef CALLBACK_API( OSErr , OSLCountProcPtr )(DescType desiredType, DescType containerClass, const AEDesc *container, long *result);

/// Disposes of a token that is no longer needed.
///
/// OSL calls this whenever it is finished with a token returned by an accessor.
/// Applications that store external references inside tokens (such as object IDs or
/// locked memory) should release those resources here.  The descriptor itself is
/// disposed by OSL after this callback returns; the callback must not call
/// ``AEDisposeDesc`` on `unneededToken`.
///
/// - Parameters:
///   - unneededToken: The token descriptor to clean up.
/// - Returns: `noErr` on success.
typedef CALLBACK_API( OSErr , OSLDisposeTokenProcPtr )(AEDesc * unneededToken);

/// Creates and returns a mark token for the given container.
///
/// OSL calls this at the start of a marking pass (when `kAEIDoMarking` is set in
/// ``AEResolve``'s flags).  The returned mark token is an opaque value that subsequent
/// ``OSLMarkProcPtr`` calls will use to record which elements are selected.
///
/// - Parameters:
///   - dContainerToken: A token identifying the container whose elements will be marked.
///   - containerClass: The class code of the container.
///   - result: On return, a newly created mark token.  OSL owns this descriptor and
///     will dispose it; the callback must not dispose it.
/// - Returns: `noErr` on success, or an appropriate error code.
typedef CALLBACK_API( OSErr , OSLGetMarkTokenProcPtr )(const AEDesc *dContainerToken, DescType containerClass, AEDesc *result);

/// Returns a pointer to the application's current error descriptor.
///
/// If an accessor or other OSL callback needs to return detailed error information
/// beyond a simple `OSErr`, it can store an error descriptor in the location that this
/// callback returns.  OSL will include that descriptor in the Apple Event reply if
/// resolution fails.
///
/// - Parameters:
///   - appDescPtr: On return, a pointer to the location where the application stores
///     its error descriptor.  The pointer itself must remain valid for the lifetime
///     of the Apple Event being processed.
/// - Returns: `noErr` on success.
typedef CALLBACK_API( OSErr , OSLGetErrDescProcPtr )(AEDesc ** appDescPtr);

/// Marks a single token as selected during a marking pass.
///
/// OSL calls this once for each object that satisfies a `formTest` specifier when
/// `kAEIDoMarking` is set.  The application records the selection by associating
/// `index` with `dToken` using the mark token supplied by ``OSLGetMarkTokenProcPtr``.
///
/// - Parameters:
///   - dToken: The token to mark.
///   - markToken: The mark token returned by the `OSLGetMarkTokenProcPtr` callback.
///   - index: A one-based sequential index assigned to this token within the current
///     marking pass.
/// - Returns: `noErr` on success.
typedef CALLBACK_API( OSErr , OSLMarkProcPtr )(const AEDesc *dToken, const AEDesc *markToken, long index);

/// Adjusts stored mark indices after OSL has narrowed a range.
///
/// After a `formRange` resolution, OSL may call this callback to renumber the marks
/// that fall within `newStart`…`newStop` so they form a contiguous 1-based sequence.
/// Marks outside that range should be removed.
///
/// - Parameters:
///   - newStart: The first (one-based) mark index in the surviving range.
///   - newStop: The last (one-based) mark index in the surviving range.
///   - markToken: The mark token that was used during the marking pass.
/// - Returns: `noErr` on success.
typedef CALLBACK_API( OSErr , OSLAdjustMarksProcPtr )(long newStart, long newStop, const AEDesc *markToken);
/// The UPP (Universal Procedure Pointer) type for each `OSL...ProcPtr` callback declared
/// above, for use with the `New`/`Dispose`/`Invoke` wrappers below and with the OSL install
/// calls (such as `AEInstallObjectAccessor`, `AESetObjectCallbacks`) that take one.
typedef STACK_UPP_TYPE(OSLAccessorProcPtr)                      OSLAccessorUPP;
typedef STACK_UPP_TYPE(OSLCompareProcPtr)                       OSLCompareUPP;
typedef STACK_UPP_TYPE(OSLCountProcPtr)                         OSLCountUPP;
typedef STACK_UPP_TYPE(OSLDisposeTokenProcPtr)                  OSLDisposeTokenUPP;
typedef STACK_UPP_TYPE(OSLGetMarkTokenProcPtr)                  OSLGetMarkTokenUPP;
typedef STACK_UPP_TYPE(OSLGetErrDescProcPtr)                    OSLGetErrDescUPP;
typedef STACK_UPP_TYPE(OSLMarkProcPtr)                          OSLMarkUPP;
typedef STACK_UPP_TYPE(OSLAdjustMarksProcPtr)                   OSLAdjustMarksUPP;

/// Creates an `OSLAccessorUPP` from `userRoutine`, for passing to `AEInstallObjectAccessor`.
extern OSLAccessorUPP
NewOSLAccessorUPP(OSLAccessorProcPtr userRoutine)             API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Creates an `OSLCompareUPP` from `userRoutine`, for passing to `AESetObjectCallbacks`.
extern OSLCompareUPP
NewOSLCompareUPP(OSLCompareProcPtr userRoutine)               API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Creates an `OSLCountUPP` from `userRoutine`, for passing to `AESetObjectCallbacks`.
extern OSLCountUPP
NewOSLCountUPP(OSLCountProcPtr userRoutine)                   API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Creates an `OSLDisposeTokenUPP` from `userRoutine`, for passing to `AESetObjectCallbacks`.
extern OSLDisposeTokenUPP
NewOSLDisposeTokenUPP(OSLDisposeTokenProcPtr userRoutine)     API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Creates an `OSLGetMarkTokenUPP` from `userRoutine`, for passing to `AESetObjectCallbacks`.
extern OSLGetMarkTokenUPP
NewOSLGetMarkTokenUPP(OSLGetMarkTokenProcPtr userRoutine)     API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Creates an `OSLGetErrDescUPP` from `userRoutine`, for passing to `AESetObjectCallbacks`.
extern OSLGetErrDescUPP
NewOSLGetErrDescUPP(OSLGetErrDescProcPtr userRoutine)         API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Creates an `OSLMarkUPP` from `userRoutine`, for passing to `AESetObjectCallbacks`.
extern OSLMarkUPP
NewOSLMarkUPP(OSLMarkProcPtr userRoutine)                     API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Creates an `OSLAdjustMarksUPP` from `userRoutine`, for passing to `AESetObjectCallbacks`.
extern OSLAdjustMarksUPP
NewOSLAdjustMarksUPP(OSLAdjustMarksProcPtr userRoutine)       API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Disposes of an `OSLAccessorUPP` created with `NewOSLAccessorUPP`.
extern void
DisposeOSLAccessorUPP(OSLAccessorUPP userUPP)                 API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Disposes of an `OSLCompareUPP` created with `NewOSLCompareUPP`.
extern void
DisposeOSLCompareUPP(OSLCompareUPP userUPP)                   API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Disposes of an `OSLCountUPP` created with `NewOSLCountUPP`.
extern void
DisposeOSLCountUPP(OSLCountUPP userUPP)                       API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Disposes of an `OSLDisposeTokenUPP` created with `NewOSLDisposeTokenUPP`.
extern void
DisposeOSLDisposeTokenUPP(OSLDisposeTokenUPP userUPP)         API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Disposes of an `OSLGetMarkTokenUPP` created with `NewOSLGetMarkTokenUPP`.
extern void
DisposeOSLGetMarkTokenUPP(OSLGetMarkTokenUPP userUPP)         API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Disposes of an `OSLGetErrDescUPP` created with `NewOSLGetErrDescUPP`.
extern void
DisposeOSLGetErrDescUPP(OSLGetErrDescUPP userUPP)             API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Disposes of an `OSLMarkUPP` created with `NewOSLMarkUPP`.
extern void
DisposeOSLMarkUPP(OSLMarkUPP userUPP)                         API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Disposes of an `OSLAdjustMarksUPP` created with `NewOSLAdjustMarksUPP`.
extern void
DisposeOSLAdjustMarksUPP(OSLAdjustMarksUPP userUPP)           API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Calls the `OSLAccessorProcPtr` callback referenced by `userUPP`, forwarding the given
/// arguments to it.
extern OSErr
InvokeOSLAccessorUPP(
  DescType        desiredClass,
  const AEDesc *  container,
  DescType        containerClass,
  DescType        form,
  const AEDesc *  selectionData,
  AEDesc *        value,
  SRefCon         accessorRefcon,
  OSLAccessorUPP  userUPP)                                    API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Calls the `OSLCompareProcPtr` callback referenced by `userUPP`, forwarding the given
/// arguments to it.
extern OSErr
InvokeOSLCompareUPP(
  DescType        oper,
  const AEDesc *  obj1,
  const AEDesc *  obj2,
  Boolean *       result,
  OSLCompareUPP   userUPP)                                    API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Calls the `OSLCountProcPtr` callback referenced by `userUPP`, forwarding the given
/// arguments to it.
extern OSErr
InvokeOSLCountUPP(
  DescType        desiredType,
  DescType        containerClass,
  const AEDesc *  container,
  long *          result,
  OSLCountUPP     userUPP)                                    API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Calls the `OSLDisposeTokenProcPtr` callback referenced by `userUPP`, forwarding the given
/// arguments to it.
extern OSErr
InvokeOSLDisposeTokenUPP(
  AEDesc *            unneededToken,
  OSLDisposeTokenUPP  userUPP)                                API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Calls the `OSLGetMarkTokenProcPtr` callback referenced by `userUPP`, forwarding the given
/// arguments to it.
extern OSErr
InvokeOSLGetMarkTokenUPP(
  const AEDesc *      dContainerToken,
  DescType            containerClass,
  AEDesc *            result,
  OSLGetMarkTokenUPP  userUPP)                                API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Calls the `OSLGetErrDescProcPtr` callback referenced by `userUPP`, forwarding the given
/// arguments to it.
extern OSErr
InvokeOSLGetErrDescUPP(
  AEDesc **         appDescPtr,
  OSLGetErrDescUPP  userUPP)                                  API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Calls the `OSLMarkProcPtr` callback referenced by `userUPP`, forwarding the given
/// arguments to it.
extern OSErr
InvokeOSLMarkUPP(
  const AEDesc *  dToken,
  const AEDesc *  markToken,
  long            index,
  OSLMarkUPP      userUPP)                                    API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Calls the `OSLAdjustMarksProcPtr` callback referenced by `userUPP`, forwarding the given
/// arguments to it.
extern OSErr
InvokeOSLAdjustMarksUPP(
  long               newStart,
  long               newStop,
  const AEDesc *     markToken,
  OSLAdjustMarksUPP  userUPP)                                 API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

#if __MACH__
  #ifdef __cplusplus
    inline OSLAccessorUPP                                       NewOSLAccessorUPP(OSLAccessorProcPtr userRoutine) { return userRoutine; }
    inline OSLCompareUPP                                        NewOSLCompareUPP(OSLCompareProcPtr userRoutine) { return userRoutine; }
    inline OSLCountUPP                                          NewOSLCountUPP(OSLCountProcPtr userRoutine) { return userRoutine; }
    inline OSLDisposeTokenUPP                                   NewOSLDisposeTokenUPP(OSLDisposeTokenProcPtr userRoutine) { return userRoutine; }
    inline OSLGetMarkTokenUPP                                   NewOSLGetMarkTokenUPP(OSLGetMarkTokenProcPtr userRoutine) { return userRoutine; }
    inline OSLGetErrDescUPP                                     NewOSLGetErrDescUPP(OSLGetErrDescProcPtr userRoutine) { return userRoutine; }
    inline OSLMarkUPP                                           NewOSLMarkUPP(OSLMarkProcPtr userRoutine) { return userRoutine; }
    inline OSLAdjustMarksUPP                                    NewOSLAdjustMarksUPP(OSLAdjustMarksProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeOSLAccessorUPP(OSLAccessorUPP) { }
    inline void                                                 DisposeOSLCompareUPP(OSLCompareUPP) { }
    inline void                                                 DisposeOSLCountUPP(OSLCountUPP) { }
    inline void                                                 DisposeOSLDisposeTokenUPP(OSLDisposeTokenUPP) { }
    inline void                                                 DisposeOSLGetMarkTokenUPP(OSLGetMarkTokenUPP) { }
    inline void                                                 DisposeOSLGetErrDescUPP(OSLGetErrDescUPP) { }
    inline void                                                 DisposeOSLMarkUPP(OSLMarkUPP) { }
    inline void                                                 DisposeOSLAdjustMarksUPP(OSLAdjustMarksUPP) { }
    inline OSErr                                                InvokeOSLAccessorUPP(DescType desiredClass, const AEDesc * container, DescType containerClass, DescType form, const AEDesc * selectionData, AEDesc * value, SRefCon accessorRefcon, OSLAccessorUPP userUPP) { return (*userUPP)(desiredClass, container, containerClass, form, selectionData, value, accessorRefcon); }
    inline OSErr                                                InvokeOSLCompareUPP(DescType oper, const AEDesc * obj1, const AEDesc * obj2, Boolean * result, OSLCompareUPP userUPP) { return (*userUPP)(oper, obj1, obj2, result); }
    inline OSErr                                                InvokeOSLCountUPP(DescType desiredType, DescType containerClass, const AEDesc * container, long * result, OSLCountUPP userUPP) { return (*userUPP)(desiredType, containerClass, container, result); }
    inline OSErr                                                InvokeOSLDisposeTokenUPP(AEDesc * unneededToken, OSLDisposeTokenUPP userUPP) { return (*userUPP)(unneededToken); }
    inline OSErr                                                InvokeOSLGetMarkTokenUPP(const AEDesc * dContainerToken, DescType containerClass, AEDesc * result, OSLGetMarkTokenUPP userUPP) { return (*userUPP)(dContainerToken, containerClass, result); }
    inline OSErr                                                InvokeOSLGetErrDescUPP(AEDesc ** appDescPtr, OSLGetErrDescUPP userUPP) { return (*userUPP)(appDescPtr); }
    inline OSErr                                                InvokeOSLMarkUPP(const AEDesc * dToken, const AEDesc * markToken, long index, OSLMarkUPP userUPP) { return (*userUPP)(dToken, markToken, index); }
    inline OSErr                                                InvokeOSLAdjustMarksUPP(long newStart, long newStop, const AEDesc * markToken, OSLAdjustMarksUPP userUPP) { return (*userUPP)(newStart, newStop, markToken); }
  #else
    #define NewOSLAccessorUPP(userRoutine)                      ((OSLAccessorUPP)userRoutine)
    #define NewOSLCompareUPP(userRoutine)                       ((OSLCompareUPP)userRoutine)
    #define NewOSLCountUPP(userRoutine)                         ((OSLCountUPP)userRoutine)
    #define NewOSLDisposeTokenUPP(userRoutine)                  ((OSLDisposeTokenUPP)userRoutine)
    #define NewOSLGetMarkTokenUPP(userRoutine)                  ((OSLGetMarkTokenUPP)userRoutine)
    #define NewOSLGetErrDescUPP(userRoutine)                    ((OSLGetErrDescUPP)userRoutine)
    #define NewOSLMarkUPP(userRoutine)                          ((OSLMarkUPP)userRoutine)
    #define NewOSLAdjustMarksUPP(userRoutine)                   ((OSLAdjustMarksUPP)userRoutine)
    #define DisposeOSLAccessorUPP(userUPP)
    #define DisposeOSLCompareUPP(userUPP)
    #define DisposeOSLCountUPP(userUPP)
    #define DisposeOSLDisposeTokenUPP(userUPP)
    #define DisposeOSLGetMarkTokenUPP(userUPP)
    #define DisposeOSLGetErrDescUPP(userUPP)
    #define DisposeOSLMarkUPP(userUPP)
    #define DisposeOSLAdjustMarksUPP(userUPP)
    #define InvokeOSLAccessorUPP(desiredClass, container, containerClass, form, selectionData, value, accessorRefcon, userUPP) (*userUPP)(desiredClass, container, containerClass, form, selectionData, value, accessorRefcon)
    #define InvokeOSLCompareUPP(oper, obj1, obj2, result, userUPP) (*userUPP)(oper, obj1, obj2, result)
    #define InvokeOSLCountUPP(desiredType, containerClass, container, result, userUPP) (*userUPP)(desiredType, containerClass, container, result)
    #define InvokeOSLDisposeTokenUPP(unneededToken, userUPP)    (*userUPP)(unneededToken)
    #define InvokeOSLGetMarkTokenUPP(dContainerToken, containerClass, result, userUPP) (*userUPP)(dContainerToken, containerClass, result)
    #define InvokeOSLGetErrDescUPP(appDescPtr, userUPP)         (*userUPP)(appDescPtr)
    #define InvokeOSLMarkUPP(dToken, markToken, index, userUPP) (*userUPP)(dToken, markToken, index)
    #define InvokeOSLAdjustMarksUPP(newStart, newStop, markToken, userUPP) (*userUPP)(newStart, newStop, markToken)
  #endif
#endif

// MARK: - OSL lifecycle

/// Initialises the Object Support Library.
///
/// Call this once before calling any other OSL function.  On macOS the OSL is part
/// of the Apple Event framework and is always available, so this call is essentially
/// a no-op, but it must still be made for source compatibility.
///
/// - Returns: `noErr` on success.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
AEObjectInit(void)                                            API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

// MARK: - Global OSL callbacks

/// Registers the application's OSL callback procedures with the Object Support Library.
///
/// The OSL calls these procedures while resolving object specifiers via ``AEResolve``.
/// All parameters are optional; pass `NULL` for any callback the application does not
/// need to supply.  Registering a new set of callbacks replaces any previously
/// registered set entirely.
///
/// Applications that implement scriptability typically call this once at startup,
/// immediately after ``AEObjectInit``, before installing their object accessors with
/// ``AEInstallObjectAccessor``.
///
/// - Parameters:
///   - myCompareProc: Compares two tokens with a relational operator.  Required for
///     `formTest` resolution.  See ``OSLCompareProcPtr``.
///   - myCountProc: Returns the number of elements of a given class in a container.
///     Required for ordinal resolution (`kAEAll`, `kAELast`, etc.).  See
///     ``OSLCountProcPtr``.
///   - myDisposeTokenProc: Disposes of tokens when OSL is finished with them.  Pass
///     `NULL` only if your tokens carry no external resources.  See
///     ``OSLDisposeTokenProcPtr``.
///   - myGetMarkTokenProc: Creates a mark token at the start of a marking pass.
///     Required only when `kAEIDoMarking` is passed to ``AEResolve``.  See
///     ``OSLGetMarkTokenProcPtr``.
///   - myMarkProc: Marks a token as selected during a marking pass.  Required only
///     when `kAEIDoMarking` is passed to ``AEResolve``.  See ``OSLMarkProcPtr``.
///   - myAdjustMarksProc: Renumbers marks after range narrowing.  Required only when
///     `kAEIDoMarking` is passed to ``AEResolve``.  See ``OSLAdjustMarksProcPtr``.
///   - myGetErrDescProcPtr: Returns a pointer to the application's error descriptor
///     storage.  See ``OSLGetErrDescProcPtr``.
/// - Returns: `noErr` on success.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
AESetObjectCallbacks(
  OSLCompareUPP        myCompareProc,
  OSLCountUPP          myCountProc,
  OSLDisposeTokenUPP   myDisposeTokenProc,
  OSLGetMarkTokenUPP   myGetMarkTokenProc,
  OSLMarkUPP           myMarkProc,
  OSLAdjustMarksUPP    myAdjustMarksProc,
  OSLGetErrDescUPP     myGetErrDescProcPtr)                   API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

// MARK: - Object specifier resolution

/// Resolves an object specifier into a token by recursively calling the installed accessor functions.
///
/// `AEResolve` walks the containment chain of `objectSpecifier` from outermost
/// container inward, calling the appropriate ``OSLAccessorProcPtr`` at each step.
/// The final result — a token descriptor identifying the target object(s) — is
/// returned in `theToken`.
///
/// The caller owns the returned token and must dispose of it by calling
/// ``AEDisposeToken`` (not ``AEDisposeDesc``) when finished, so that any
/// application-level resources held by the token are released via the
/// ``OSLDisposeTokenProcPtr`` callback.
///
/// The `callbackFlags` parameter is a bitwise OR of values from the `kAEI*` family:
///
/// | Flag                    | Effect                                                     |
/// |-------------------------|------------------------------------------------------------|
/// | `kAEIDoMinimum`         | No optional callbacks; accessor only.                      |
/// | `kAEIDoWhose`           | Resolve whose-clause (`formWhose`) specifiers.             |
/// | `kAEIDoMarking`         | Invoke mark / adjust-marks callbacks for `formTest`.       |
/// | `kAEPassSubDescs`       | Pass unresolved sub-specifiers to accessors.               |
/// | `kAEResolveNestedLists` | Resolve list specifiers element-by-element.                |
/// | `kAEHandleSimpleRanges` | Let OSL handle `formRange` without a custom accessor.      |
/// | `kAEUseRelativeIterators` | Use prev/next iteration for `formRelativePosition`.      |
///
/// - Parameters:
///   - objectSpecifier: The object specifier descriptor to resolve.
///   - callbackFlags: Flags controlling which optional OSL callbacks are engaged.
///   - theToken: On successful return, a token identifying the resolved object(s).
///     Dispose with ``AEDisposeToken`` when finished.
/// - Returns: `noErr` on success, `errAENoSuchObject` if the specifier names an
///   object that does not exist, or another Apple Event error if resolution fails.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
AEResolve(
  const AEDesc *  objectSpecifier,
  short           callbackFlags,
  AEDesc *        theToken)                                   API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

// MARK: - Object accessor dispatch table

/// Registers an object accessor function for a given class and container-type pair.
///
/// The OSL maintains a dispatch table that maps `(desiredClass, containerType)` pairs
/// to accessor functions.  When ``AEResolve`` needs to locate an object of
/// `desiredClass` inside a container of `containerType`, it looks up and calls the
/// matching accessor.
///
/// Pass `typeWildCard` for either `desiredClass` or `containerType` (or both) to
/// install a catch-all accessor that handles any class or any container type,
/// respectively.  A specific entry always takes precedence over a wildcard entry.
///
/// If an entry for the same `(desiredClass, containerType)` pair already exists in
/// the specified table, it is replaced.
///
/// - Parameters:
///   - desiredClass: The class of objects this accessor can locate, or `typeWildCard`.
///   - containerType: The descriptor type of containers this accessor searches, or
///     `typeWildCard`.
///   - theAccessor: The accessor function to install.  See ``OSLAccessorProcPtr``.
///   - accessorRefcon: An arbitrary value passed through to the accessor each time it
///     is called.  Pass `0` if not needed.
///   - isSysHandler: Pass `true` to install in the system accessor table, `false` for
///     the application table.  Use of the system table is not recommended.
/// - Returns: `noErr` on success, or a Memory Manager error if the table entry could
///   not be allocated.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
AEInstallObjectAccessor(
  DescType         desiredClass,
  DescType         containerType,
  OSLAccessorUPP   theAccessor,
  SRefCon          accessorRefcon,
  Boolean          isSysHandler)                              API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Removes a previously installed object accessor from the dispatch table.
///
/// - Parameters:
///   - desiredClass: The class code the accessor was registered for.
///   - containerType: The container type the accessor was registered for.
///   - theAccessor: The accessor function pointer.  Must match the value passed to
///     ``AEInstallObjectAccessor`` exactly.
///   - isSysHandler: Pass `true` to search the system accessor table; `false` for
///     the application table.
/// - Returns: `noErr` on success, or `errAEHandlerNotFound` if no matching entry
///   exists.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
AERemoveObjectAccessor(
  DescType         desiredClass,
  DescType         containerType,
  OSLAccessorUPP   theAccessor,
  Boolean          isSysHandler)                              API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

/// Retrieves the accessor function and refcon registered for a given class and container-type pair.
///
/// - Parameters:
///   - desiredClass: The class code to look up.
///   - containerType: The container type to look up.
///   - accessor: On return, the installed accessor function, or a wildcard accessor
///     if no exact match was found.
///   - accessorRefcon: On return, the refcon associated with the returned accessor.
///   - isSysHandler: Pass `true` to search the system accessor table; `false` for
///     the application table.
/// - Returns: `noErr` on success, or `errAEHandlerNotFound` if no matching entry
///   (including wildcards) exists.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
AEGetObjectAccessor(
  DescType          desiredClass,
  DescType          containerType,
  OSLAccessorUPP *  accessor,
  SRefCon *         accessorRefcon,
  Boolean           isSysHandler)                             API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

// MARK: - Token disposal

/// Disposes of a token returned by ``AEResolve`` or ``AECallObjectAccessor``.
///
/// Unlike ``AEDisposeDesc``, this function first invokes the application's
/// ``OSLDisposeTokenProcPtr`` callback (if one is installed) so that any
/// application-level resources held inside the token can be released before the
/// descriptor itself is freed.  Always use `AEDisposeToken` rather than
/// `AEDisposeDesc` when disposing of tokens.
///
/// Passing a null descriptor (type `typeNull`) is safe and returns `noErr`.
///
/// - Parameters:
///   - theToken: The token descriptor to dispose.  On return, a null descriptor.
/// - Returns: `noErr` on success.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
AEDisposeToken(AEDesc * theToken)                             API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

// MARK: - Direct accessor invocation

/// Looks up and directly calls the registered accessor for the given class and container.
///
/// This is the low-level mechanism that ``AEResolve`` uses internally.  Applications
/// can call it directly when they need to drive object resolution step-by-step — for
/// example, inside a custom accessor that needs to delegate part of the resolution
/// to another accessor, or in an event handler that constructs tokens without going
/// through the full resolver.
///
/// The function searches the application accessor table first, then the system table.
/// Wildcard entries (`typeWildCard`) are matched if no specific entry is found.
///
/// The returned token must be disposed of with ``AEDisposeToken``.
///
/// - Parameters:
///   - desiredClass: The class of object to locate.
///   - containerToken: A token identifying the container to search.  For the
///     top-level container, pass a null descriptor.
///   - containerClass: The class code of the container described by `containerToken`.
///   - keyForm: The form of the key data (`formAbsolutePosition`, `formName`, etc.).
///   - keyData: A descriptor providing the selection criterion corresponding to
///     `keyForm`.
///   - token: On successful return, a token identifying the located object(s).
///     Dispose with ``AEDisposeToken`` when finished.
/// - Returns: `noErr` on success, `errAENoSuchObject` if the object does not exist,
///   or `errAEHandlerNotFound` if no accessor is registered for the combination.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
AECallObjectAccessor(
  DescType        desiredClass,
  const AEDesc *  containerToken,
  DescType        containerClass,
  DescType        keyForm,
  const AEDesc *  keyData,
  AEDesc *        token)                                      API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __AEOBJECTS__ */

