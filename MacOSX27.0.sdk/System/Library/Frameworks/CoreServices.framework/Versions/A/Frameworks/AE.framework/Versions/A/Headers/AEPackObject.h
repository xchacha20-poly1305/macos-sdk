/*
 *  AEPackObject.h — Apple Events object packing interfaces.
 *  Copyright © 1999-2026 Apple Inc. All rights reserved.
 */
#ifndef __AEPACKOBJECT__
#define __AEPACKOBJECT__

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

// MARK: - Object packing

/// Creates a descriptor that identifies an element by its one-based integer position.
///
/// Use this as the `keyData` argument to ``CreateObjSpecifier`` when building a
/// `formAbsolutePosition` object specifier.  The resulting descriptor has type
/// `typeLongInteger`.
///
/// - Parameters:
///   - theOffset: The one-based position of the element.
///   - theDescriptor: On successful return, the newly created descriptor.  The caller
///     must dispose of it with ``AEDisposeDesc`` when finished.
/// - Returns: `noErr` on success, or a Memory Manager error if allocation fails.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
CreateOffsetDescriptor(
  long      theOffset,
  AEDesc *  theDescriptor)                                    API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Creates a comparison descriptor that tests a relationship between two object specifiers.
///
/// A comparison descriptor (type `typeCompDescriptor`) encodes a binary relational test
/// such as "word 3 equals 'hello'" and is typically used as a term inside a logical
/// descriptor or as key data for a `formTest` object specifier.
///
/// If `disposeInputs` is `true`, the Apple Event Manager disposes of both `operand1`
/// and `operand2` after they have been incorporated into the new descriptor, whether or
/// not the call succeeds.  Pass `false` when you need to keep or reuse the input
/// descriptors yourself.
///
/// - Parameters:
///   - comparisonOperator: The four-character-code comparison operator, such as
///     `kAEEquals`, `kAELessThan`, `kAEBeginsWith`, or `kAEContains`.
///   - operand1: A pointer to the first operand descriptor — typically an object
///     specifier identifying the property or element to test.
///   - operand2: A pointer to the second operand descriptor — the value to compare
///     against.
///   - disposeInputs: Pass `true` to have the function dispose of `operand1` and
///     `operand2`; pass `false` to retain them.
///   - theDescriptor: On successful return, the newly created comparison descriptor.
///     The caller must dispose of it with ``AEDisposeDesc`` when finished.
/// - Returns: `noErr` on success, or `errAECoercionFail` if the operands cannot be
///   combined.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
CreateCompDescriptor(
  DescType   comparisonOperator,
  AEDesc *   operand1,
  AEDesc *   operand2,
  Boolean    disposeInputs,
  AEDesc *   theDescriptor)                                   API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Creates a logical descriptor that combines one or more comparison terms with AND, OR, or NOT.
///
/// A logical descriptor (type `typeLogicalDescriptor`) applies a Boolean operator to a
/// list of comparison or nested logical descriptors.  It is used as the key data for a
/// `formTest` object specifier, or directly as an Apple Event parameter where a
/// Boolean expression is expected.
///
/// `theLogicalTerms` must be a descriptor list (`typeAEList`) containing one or more
/// descriptors of type `typeCompDescriptor` or `typeLogicalDescriptor`.  For `kAENOT`
/// the list must contain exactly one term.
///
/// If `disposeInputs` is `true`, the function disposes of `theLogicalTerms` after it
/// has been incorporated, whether or not the call succeeds.
///
/// - Parameters:
///   - theLogicalTerms: A descriptor list of the terms to combine.
///   - theLogicOperator: The Boolean operator: `kAEAND`, `kAEOR`, or `kAENOT`.
///   - disposeInputs: Pass `true` to have the function dispose of `theLogicalTerms`;
///     pass `false` to retain it.
///   - theDescriptor: On successful return, the newly created logical descriptor.
///     The caller must dispose of it with ``AEDisposeDesc`` when finished.
/// - Returns: `noErr` on success, or a Memory Manager error if allocation fails.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
CreateLogicalDescriptor(
  AEDescList *  theLogicalTerms,
  DescType      theLogicOperator,
  Boolean       disposeInputs,
  AEDesc *      theDescriptor)                                API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Creates an object specifier descriptor that identifies one or more application objects.
///
/// An object specifier (type `typeObjectSpecifier`) is a hierarchical record that
/// identifies an element or property within a containment hierarchy.  It encodes four
/// pieces of information: what class of object is wanted (`desiredClass`), where to
/// look for it (`theContainer`), how the key data identifies it (`keyForm`), and the
/// key data itself (`keyData`).
///
/// Common `keyForm` values and the expected `keyData` type:
///
/// | `keyForm`              | `keyData` descriptor type                        |
/// |------------------------|--------------------------------------------------|
/// | `formAbsolutePosition` | `typeLongInteger` (from ``CreateOffsetDescriptor``) |
/// | `formPropertyID`       | `typeType` (a four-char property code)           |
/// | `formName`             | `typeUTF8Text` or `typeChar`                     |
/// | `formRange`            | `typeRangeDescriptor` (from ``CreateRangeDescriptor``) |
/// | `formTest`             | `typeLogicalDescriptor` or `typeCompDescriptor`  |
///
/// Passing `typeNull` for `theContainer` creates an absolute specifier rooted at the
/// application; pass an enclosing object specifier to create a relative one.
///
/// If `disposeInputs` is `true`, both `theContainer` and `keyData` are disposed of
/// after they have been incorporated, whether or not the call succeeds.
///
/// - Parameters:
///   - desiredClass: The four-character class code of the object to identify, such as
///     `cWord`, `cParagraph`, or `cDocument`.
///   - theContainer: A pointer to a descriptor identifying the container in which to
///     search.  Pass a null descriptor (`typeNull`) to specify the application itself.
///   - keyForm: The form of the key data — one of `formAbsolutePosition`,
///     `formRelativePosition`, `formPropertyID`, `formName`, `formRange`, or
///     `formTest`.
///   - keyData: A pointer to the descriptor that selects the specific object within
///     the container according to `keyForm`.
///   - disposeInputs: Pass `true` to have the function dispose of `theContainer` and
///     `keyData`; pass `false` to retain them.
///   - objSpecifier: On successful return, the newly created object specifier.
///     The caller must dispose of it with ``AEDisposeDesc`` when finished.
/// - Returns: `noErr` on success, or a Memory Manager error if allocation fails.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
CreateObjSpecifier(
  DescType   desiredClass,
  AEDesc *   theContainer,
  DescType   keyForm,
  AEDesc *   keyData,
  Boolean    disposeInputs,
  AEDesc *   objSpecifier)                                    API_AVAILABLE( macos(10.0) ) API_UNAVAILABLE( ios, tvos, watchos );


/// Creates a range descriptor that identifies a contiguous span of elements.
///
/// A range descriptor (type `typeRangeDescriptor`) is used as the key data for a
/// `formRange` object specifier.  It records the start and stop boundaries of the
/// range, each expressed as an object specifier or an absolute-position descriptor.
///
/// Example: to build an object specifier for "words 2 through 5" you would first
/// create two offset descriptors (via ``CreateOffsetDescriptor``), pass them here to
/// get a range descriptor, then pass that range descriptor to ``CreateObjSpecifier``
/// with `keyForm` = `formRange` and `desiredClass` = `cWord`.
///
/// If `disposeInputs` is `true`, both `rangeStart` and `rangeStop` are disposed of
/// after they have been incorporated, whether or not the call succeeds.
///
/// - Parameters:
///   - rangeStart: A pointer to a descriptor identifying the first element of the
///     range.
///   - rangeStop: A pointer to a descriptor identifying the last element of the
///     range.
///   - disposeInputs: Pass `true` to have the function dispose of `rangeStart` and
///     `rangeStop`; pass `false` to retain them.
///   - theDescriptor: On successful return, the newly created range descriptor.
///     The caller must dispose of it with ``AEDisposeDesc`` when finished.
/// - Returns: `noErr` on success, or a Memory Manager error if allocation fails.
/// - Note: Thread safe since macOS 10.2.
extern OSErr
CreateRangeDescriptor(
  AEDesc *  rangeStart,
  AEDesc *  rangeStop,
  Boolean   disposeInputs,
  AEDesc *  theDescriptor)                                    __API_AVAILABLE(macos(10.0));



#ifdef __cplusplus
}
#endif

#endif /* __AEPACKOBJECT__ */
