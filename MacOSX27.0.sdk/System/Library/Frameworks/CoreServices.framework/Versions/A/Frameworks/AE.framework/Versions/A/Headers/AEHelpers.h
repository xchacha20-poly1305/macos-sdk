/*
 *  AEHelpers.h — AEBuild, AEPrint, and AEStream interfaces.
 *  Copyright © 1999-2026 Apple Inc. All rights reserved.
 */
/*
 * Originally from AEGIzmos by Jens Alfke, circa 1992.
 */
#ifndef __AEHELPERS__
#define __AEHELPERS__

#include <stdarg.h>
#ifndef __APPLEEVENTS__
#include <AE/AppleEvents.h>
#endif

#ifndef __AEDATAMODEL__
#include <AE/AEDataModel.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif



#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

/*
 * AEBuild:
 *
 * AEBuild provides a very high level abstraction for building
 * complete AppleEvents and complex ObjectSpeciers.  Using AEBuild it
 * is easy to produce a textual representation of an AEDesc.  The
 * format is similar to the stdio printf call, where meta data is
 * extracted from a format string and used to build the final
 * representation.
 * 
 * For more information on AEBuild and other APIs in AEHelpers, see:
 *     <http://developer.apple.com/technotes/tn/tn2045.html>
 */
/// Syntax Error Codes
typedef UInt32 AEBuildErrorCode;
enum {
  aeBuildSyntaxNoErr            = 0, ///< (No error)
  aeBuildSyntaxBadToken         = 1, ///< Illegal character
  aeBuildSyntaxBadEOF           = 2, ///< Unexpected end of format string
  aeBuildSyntaxNoEOF            = 3, ///< Unexpected extra stuff past end
  aeBuildSyntaxBadNegative      = 4, ///< "-" not followed by digits
  aeBuildSyntaxMissingQuote     = 5, ///< Missing close "'"
  aeBuildSyntaxBadHex           = 6, ///< Non-digit in hex string
  aeBuildSyntaxOddHex           = 7, ///< Odd # of hex digits
  aeBuildSyntaxNoCloseHex       = 8, ///< Missing hex quote close "�"
  aeBuildSyntaxUncoercedHex     = 9, ///< Hex string must be coerced to a type
  aeBuildSyntaxNoCloseString    = 10, ///< Missing close quote
  aeBuildSyntaxBadDesc          = 11, ///< Illegal descriptor
  aeBuildSyntaxBadData          = 12, ///< Bad data value inside (� �)
  aeBuildSyntaxNoCloseParen     = 13, ///< Missing ")" after data value
  aeBuildSyntaxNoCloseBracket   = 14, ///< Expected "," or "]"
  aeBuildSyntaxNoCloseBrace     = 15, ///< Expected "," or "}"
  aeBuildSyntaxNoKey            = 16, ///< Missing keyword in record
  aeBuildSyntaxNoColon          = 17, ///< Missing ":" after keyword in record
  aeBuildSyntaxCoercedList      = 18, ///< Cannot coerce a list
  aeBuildSyntaxUncoercedDoubleAt = 19 ///< "@@" substitution must be coerced
};

/// A structure containing error state.
struct AEBuildError {
  AEBuildErrorCode    fError;
  UInt32              fErrorPos;
};
typedef struct AEBuildError             AEBuildError;
/// Builds a new `AEDesc` (which may be a plain value, a list, or a record) by parsing a
/// textual format string, similar in spirit to how \c vprintf builds a string. The format
/// string can express nested lists (`[...]`), records (`{...}`), keyword-tagged values, and
/// literal data (integers, hex byte strings, quoted text), and an `@` placeholder consumes one
/// variadic argument in order, optionally coerced to the type named by a preceding sigil
/// (e.g. `usng(@)` or `TEXT(@)`). See TN2045 ("Using AEBuild and Friends") for the complete
/// grammar.
/// - Parameters:
///   - dst: On success, receives the newly created descriptor; the caller must dispose of it
///     with `AEDisposeDesc` when done.
///   - error: On a syntax error, receives the error code and the byte offset within `src`
///     where parsing failed. Can be NULL if this detail isn't needed.
///   - src: The AEBuild format string.
///   - ...: One argument for each `@` placeholder appearing in `src`, in order.
extern OSStatus
AEBuildDesc(
  AEDesc *        dst,
  AEBuildError *  error,       /* can be NULL */
  const char *    src,
  ...)                                                        API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// The `va_list` counterpart of `AEBuildDesc`, for callers that have already collected their
/// `@`-placeholder arguments into a `va_list` (typically because they themselves are a
/// variadic wrapper function).
extern OSStatus
vAEBuildDesc(
  AEDesc *        dst,
  AEBuildError *  error,       /* can be NULL */
  const char *    src,
  va_list         args)                                       API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );



/// Parses an AEBuild format string, the same syntax used by `AEBuildDesc`, and merges the
/// resulting keyword-tagged values directly into `event`'s existing parameter record. Unlike
/// `AEBuildDesc`, `format` must describe one or more keyword-value pairs (e.g.
/// `"'----':@, 'kfrm':@"`) rather than a bare value, since the parsed result is appended as
/// parameters rather than returned as a standalone descriptor.
/// - Parameters:
///   - event: The AppleEvent to add parameters to. Modified in place.
///   - error: On a syntax error, receives the error code and byte offset within `format`.
///     Can be NULL if this detail isn't needed.
///   - format: The AEBuild format string, consisting of one or more keyword-value pairs.
///   - ...: One argument for each `@` placeholder appearing in `format`, in order.
extern OSStatus
AEBuildParameters(
  AppleEvent *    event,
  AEBuildError *  error,        /* can be NULL */
  const char *    format,
  ...)                                                        API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// The `va_list` counterpart of `AEBuildParameters`, for callers that have already collected
/// their `@`-placeholder arguments into a `va_list`.
/// - Parameters:
///   - event: the AppleEvent to add parameters to.  Modifies in place.
///   - error: On a syntax error, receives the error code and byte offset within `format`.
///     Can be NULL if this detail isn't needed.
///   - format: The AEBuild format string, consisting of one or more keyword-value pairs.
///   - args: the complete va\_args list of arguments
extern OSStatus
vAEBuildParameters(
  AppleEvent *    event,
  AEBuildError *  error,        /* can be NULL */
  const char *    format,
  va_list         args)                                       API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Creates a brand-new `AppleEvent` and populates its parameters in a single call, combining
/// what would otherwise be a call to `AECreateAppleEvent` followed by `AEBuildParameters`.
/// `theClass`, `theID`, and the `addressType`/`addressData`/`addressLength`/`returnID`/
/// `transactionID` arguments are passed through to create the event exactly as
/// `AECreateAppleEvent` would; `paramsFmt` and the variadic arguments that follow are then
/// parsed using the AEBuild format string syntax and appended as parameters, exactly as
/// `AEBuildParameters` would do.
/// - Parameters:
///   - result: On success, receives the newly created AppleEvent; the caller must dispose of
///     it with `AEDisposeDesc` when done.
///   - error: On a syntax error in `paramsFmt`, receives the error code and byte offset.
///     Can be NULL if this detail isn't needed.
///   - paramsFmt: The AEBuild format string describing the event's parameters, consisting of
///     one or more keyword-value pairs. Can be NULL (or empty) if the event has no parameters.
extern OSStatus
AEBuildAppleEvent(
  AEEventClass    theClass,
  AEEventID       theID,
  DescType        addressType,
  const void *    addressData,
  Size            addressLength,
  SInt16          returnID,
  SInt32          transactionID,
  AppleEvent *    result,
  AEBuildError *  error,               /* can be NULL */
  const char *    paramsFmt,
  ...)                                                        API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// The `va_list` counterpart of `AEBuildAppleEvent`, for callers that have already collected
/// their `@`-placeholder arguments into a `va_list`.
extern OSStatus
vAEBuildAppleEvent(
  AEEventClass    theClass,
  AEEventID       theID,
  DescType        addressType,
  const void *    addressData,
  Size            addressLength,
  SInt16          returnID,
  SInt32          transactionID,
  AppleEvent *    resultEvt,
  AEBuildError *  error,               /* can be NULL */
  const char *    paramsFmt,
  va_list         args)                                       API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// AEPrintDescToHandle provides a way to turn an AEDesc into a textual
/// representation.  This is most useful for debugging calls to
/// AEBuildDesc and friends.  The Handle returned should be disposed by
/// the caller.  The size of the handle is the actual number of
/// characters in the string.
extern OSStatus
AEPrintDescToHandle(
  const AEDesc *  desc,
  Handle *        result)                                     API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// The AEStream interface allows you to build AppleEvents by appending
/// to an opaque structure (an `AEStreamRef`) and then turning this
/// structure into an AppleEvent.  The basic idea is to open the
/// stream, write data, and then close it - closing it produces an
/// `AEDesc`, which may be partially complete, or may be a complete
/// AppleEvent.
typedef struct OpaqueAEStreamRef*       AEStreamRef;

/// Creates a new, empty `AEStreamRef` with nothing yet written to it. This is the AEStream
/// counterpart to starting an AEBuild format string: the stream is a good choice over
/// AEBuild when the shape of the descriptor being built (how many list elements, how many
/// keyed parameters) isn't known until run time, since it lets you write to it in a loop
/// rather than assembling one large format string and argument list up front.
/// - Returns: NULL on memory allocation failure
extern AEStreamRef
AEStreamOpen(void)                                            API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Closes and disposes of an `AEStreamRef`, producing the finished result in `desc`. What
/// `desc` receives depends on how the stream was opened: a plain descriptor if the stream was
/// built with `AEStreamOpenDesc`/`AEStreamOpenList`/`AEStreamOpenRecord`, or a complete
/// `AppleEvent` if it was built with `AEStreamCreateEvent` or `AEStreamOpenEvent`.
/// You must dispose of `desc` yourself once you're done with it.
/// If you just want to dispose of the `AEStreamRef` without keeping its contents (for example,
/// on an error path), you can pass NULL for `desc`.
extern OSStatus
AEStreamClose(
  AEStreamRef   ref,
  AEDesc *      desc)                                         API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Prepares `ref` to accumulate the raw bytes of a newly created descriptor of type
/// `newType`. Follow this with one or more calls to `AEStreamWriteData` to supply the
/// descriptor's contents, then `AEStreamCloseDesc` to finish it.
extern OSStatus
AEStreamOpenDesc(
  AEStreamRef   ref,
  DescType      newType)                                      API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Appends raw bytes to the descriptor most recently opened with `AEStreamOpenDesc` or
/// `AEStreamOpenKeyDesc`. Can be called more than once to append data incrementally.
extern OSStatus
AEStreamWriteData(
  AEStreamRef   ref,
  const void *  data,
  Size          length)                                       API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Finishes the descriptor most recently opened with `AEStreamOpenDesc` or
/// `AEStreamOpenKeyDesc`. After this, you can close the stream to retrieve the finished
/// descriptor, or, if you're assembling a list or record, continue adding further descs.
extern OSStatus
AEStreamCloseDesc(AEStreamRef ref)                            API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// A convenience that combines `AEStreamOpenDesc`, `AEStreamWriteData`, and
/// `AEStreamCloseDesc` into a single call, for the common case where the entire descriptor's
/// data is already available in one buffer.
extern OSStatus
AEStreamWriteDesc(
  AEStreamRef   ref,
  DescType      newType,
  const void *  data,
  Size          length)                                       API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Writes an entire, already-built `AEDesc` (which may itself be a list or record) to the
/// stream in one step, equivalent to opening a desc of the same type, writing its data, and
/// closing it. Useful for splicing a descriptor obtained elsewhere into a stream you're
/// assembling.
extern OSStatus
AEStreamWriteAEDesc(
  AEStreamRef     ref,
  const AEDesc *  desc)                                       API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Begins a list at the current position in the stream. Append elements to the list with
/// `AEStreamOpenDesc`/`AEStreamWriteData`/`AEStreamCloseDesc`, `AEStreamWriteDesc`, or
/// `AEStreamWriteAEDesc`, in the order they should appear in the list. Finish the list with
/// `AEStreamCloseList`. Lists can be nested by opening another list (or record) as one of the
/// elements.
extern OSStatus
AEStreamOpenList(AEStreamRef ref)                             API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Finishes the list most recently opened with `AEStreamOpenList`.
extern OSStatus
AEStreamCloseList(AEStreamRef ref)                            API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Begins a record at the current position in the stream, with descriptor type `newType`. A
/// record usually has type `typeAERecord` (`'reco'`), but application-defined "user-defined
/// record" types are common too. Add keyed entries with `AEStreamWriteKeyDesc`,
/// `AEStreamOpenKeyDesc`, or `AEStreamWriteKey` followed by a desc, and finish the record with
/// `AEStreamCloseRecord`.
extern OSStatus
AEStreamOpenRecord(
  AEStreamRef   ref,
  DescType      newType)                                      API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Changes the descriptor type of the record most recently opened with `AEStreamOpenRecord`,
/// without needing to reopen it. Useful when the record's final type isn't known until after
/// some of its keyed entries have already been written.
extern OSStatus
AEStreamSetRecordType(
  AEStreamRef   ref,
  DescType      newType)                                      API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Finishes the record most recently opened with `AEStreamOpenRecord`.
extern OSStatus
AEStreamCloseRecord(AEStreamRef ref)                          API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Adds a keyed descriptor to the record most recently opened with `AEStreamOpenRecord`,
/// in a single call. This is the stream analog of `AEPutParamDesc`/`AEPutKeyPtr`, and can
/// only be used while writing to a record (not a bare desc or list).
extern OSStatus
AEStreamWriteKeyDesc(
  AEStreamRef   ref,
  AEKeyword     key,
  DescType      newType,
  const void *  data,
  Size          length)                                       API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Begins a keyed entry in the record most recently opened with `AEStreamOpenRecord`, for
/// cases where the entry's data isn't all available at once. Follow this with one or more
/// calls to `AEStreamWriteData` to supply the entry's contents, then `AEStreamCloseDesc` to
/// finish it — or open a nested list/record as the entry's value instead.
extern OSStatus
AEStreamOpenKeyDesc(
  AEStreamRef   ref,
  AEKeyword     key,
  DescType      newType)                                      API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Writes just the keyword for the next entry in the record most recently opened with
/// `AEStreamOpenRecord`, without its value. Follow this with `AEStreamWriteDesc` or
/// `AEStreamWriteAEDesc` to supply the entry's value.
extern OSStatus
AEStreamWriteKey(
  AEStreamRef   ref,
  AEKeyword     key)                                          API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Creates a new `AppleEvent` and returns a stream open on it, combining what would otherwise
/// be a call to `AECreateAppleEvent` followed by `AEStreamOpenEvent`. `clazz`, `id`, and the
/// `targetType`/`targetData`/`targetLength`/`returnID`/`transactionID` arguments populate the
/// event's meta fields exactly as `AECreateAppleEvent` would. After this call, add the event's
/// parameters using the other AEStream calls (`AEStreamWriteKeyDesc`, `AEStreamOpenList`,
/// etc.), then retrieve the finished `AppleEvent` with `AEStreamClose`.
extern AEStreamRef
AEStreamCreateEvent(
  AEEventClass   clazz,
  AEEventID      id,
  DescType       targetType,
  const void *   targetData,
  Size           targetLength,
  SInt16         returnID,
  SInt32         transactionID)                               API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Opens a stream on an existing `AppleEvent`, for adding further parameters using the
/// AEStream calls. This is useful, for example, when constructing the reply record inside an
/// AppleEvent handler. Note that `AEStreamOpenEvent` consumes `event` — you can't access it
/// again until the stream is closed. When you're done adding parameters,
/// `AEStreamClose` reconstitutes the (now augmented) event.
extern AEStreamRef
AEStreamOpenEvent(AppleEvent * event)                         API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Marks `key` as an optional parameter keyword, by adding it to the event's
/// `keyOptionalKeywordAttr` attribute list. A handler that doesn't recognize an optional
/// parameter can ignore it instead of returning `errAEParamMissed`.
extern OSStatus
AEStreamOptionalParam(
  AEStreamRef   ref,
  AEKeyword     key)                                          API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );



#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __AEHELPERS__ */

