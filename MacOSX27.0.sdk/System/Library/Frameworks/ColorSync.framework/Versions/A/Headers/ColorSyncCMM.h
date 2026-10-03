/*
 * ColorSync - ColorSyncCMM.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNCCMM__
#define __COLORSYNCCMM__

#ifdef __cplusplus
extern "C" {
#endif

#include <ColorSync/ColorSyncProfile.h>
#include <ColorSync/ColorSyncTransform.h>

/*
 * Notes:
 *  - Color conversions are performed by a Color Management Module (CMM) which is a plugin to ColorSync.
 *  - ColorSync contains Apple CMM, which is not replaceable, but third parties can install their own CMMs
 *  - ColorSync provides access to installed CMMs as well as those that can be part of the application bundle.
 *  - CMM can be selected and specified as a preferred CMM per color transform created by the application 
 *  - if the third party CMM fails to perform a task, Apple CMM will take it over
 *  - ColorSyncCMMRef is a light weight wrapper of CFBundleRef
 *  - See /Developer/Examples/ColorSync/DemoCMM
 */

/// A reference to a Color Management Module (CMM).
///
/// This type is a lightweight wrapper around a Core Foundation bundle.
typedef struct CF_BRIDGED_TYPE(id) ColorSyncCMM* ColorSyncCMMRef;

#if !defined(__swift__)

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

#endif

/// Returns the `CFTypeID` for `ColorSyncCMM`s.
CSEXTERN_DESKTOP CFTypeID ColorSyncCMMGetTypeID(void) CS_AVAILABLE_STARTING(10.4, 16.0);

/// Creates a CMM object from a CMM bundle.
///
/// - Parameter cmmBundle: The bundle containing the CMM.
/// - Returns: A new ``ColorSyncCMMRef``, or `NULL` in case of failure.
CSEXTERN_DESKTOP ColorSyncCMMRef __nullable ColorSyncCMMCreate(CFBundleRef cmmBundle) CS_AVAILABLE_DESKTOP(10.4);

/// Returns the bundle associated with a CMM.
///
/// - Returns: The `CFBundleRef` for the CMM, or `NULL` for the built-in Apple CMM.
CSEXTERN_DESKTOP CFBundleRef __nullable ColorSyncCMMGetBundle(ColorSyncCMMRef) CS_AVAILABLE_DESKTOP(10.4);

/// Copies the localized name of a CMM.
///
/// Use this function to get the name of the built-in CMM.
///
/// - Returns: The localized name of the CMM.
CSEXTERN_DESKTOP CFStringRef __nullable ColorSyncCMMCopyLocalizedName(ColorSyncCMMRef) CS_AVAILABLE_DESKTOP(10.4);

/// Copies the identifier of a CMM.
///
/// Use this function to get the identifier of the built-in CMM.
///
/// - Returns: The identifier of the CMM.
CSEXTERN_DESKTOP CFStringRef __nullable ColorSyncCMMCopyCMMIdentifier(ColorSyncCMMRef) CS_AVAILABLE_DESKTOP(10.4);

/// A callback that the framework invokes for each installed CMM during iteration.
///
/// Return `false` to stop the iteration.
///
/// - Parameters:
///   - cmm: The CMM for this iteration step.
///   - userInfo: The user info passed to the iteration function.
typedef bool (*ColorSyncCMMIterateCallback)(ColorSyncCMMRef cmm, void* userInfo) CS_AVAILABLE_DESKTOP(10.4);

/// Iterates over the installed CMMs, invoking a callback for each one.
///
/// - Parameters:
///   - callBack: A pointer to a client-provided function.
///   - userInfo: A pointer to the user info that the framework passes to the callback. Optional.
CSEXTERN_DESKTOP void ColorSyncIterateInstalledCMMs (ColorSyncCMMIterateCallback callBack, void* __nullable userInfo) CS_AVAILABLE_DESKTOP(10.4);


/*
* ==========================================================================================
* This part defines the interface for developers of third party CMMs for ColorSync.
* ==========================================================================================
*/

/// A function a CMM provider implements to initialize a device-link profile.
typedef bool (*CMMInitializeLinkProfileProc) (ColorSyncMutableProfileRef, CFArrayRef profileInfo, CFDictionaryRef __nullable options);

/// A function a CMM provider implements to initialize a color transform.
typedef bool (*CMMInitializeTransformProc) (ColorSyncTransformRef, CFArrayRef profileInfo, CFDictionaryRef __nullable options);

/// A function a CMM provider implements to apply a color transform to image data.
typedef bool (*CMMApplyTransformProc)(ColorSyncTransformRef transform, size_t width, size_t height,
                                      size_t dstPlanes, void* __nonnull  * __nonnull  dst, ColorSyncDataDepth dstDepth,
                                      ColorSyncDataLayout dstFormat, size_t dstBytesPerRow,
                                      size_t srcPlanes, const void* __nonnull* __nonnull src, ColorSyncDataDepth srcDepth,
                                      ColorSyncDataLayout srcFormat, size_t srcBytesPerRow,
                                      CFDictionaryRef __nullable options);

/// A function a CMM provider implements to create a transform property for a given key.
typedef CFTypeRef __nullable (*CMMCreateTransformPropertyProc)(ColorSyncTransformRef __nullable transform, CFTypeRef key, CFDictionaryRef __nullable options);

/// The CMM bundle info-dictionary key whose value is the name of the function that initializes a device-link profile.
CSEXTERN_DESKTOP CFStringRef kCMMInitializeLinkProfileProcName CS_AVAILABLE_DESKTOP(10.4);     /* CMMInitializeLinkProfileProcName   */
/// The CMM bundle info-dictionary key whose value is the name of the function that initializes a color transform.
CSEXTERN_DESKTOP CFStringRef kCMMInitializeTransformProcName CS_AVAILABLE_DESKTOP(10.4);       /* CMMInitializeTransformProcName     */
/// The CMM bundle info-dictionary key whose value is the name of the function that applies a color transform.
CSEXTERN_DESKTOP CFStringRef kCMMApplyTransformProcName CS_AVAILABLE_DESKTOP(10.4);            /* CMMApplyTransformProcName          */
/// The CMM bundle info-dictionary key whose value is the name of the function that creates a transform property.
CSEXTERN_DESKTOP CFStringRef kCMMCreateTransformPropertyProcName CS_AVAILABLE_DESKTOP(10.4);   /* CMMCreateTransformPropertyProcName */

/*
* Following keys are expected to be present in the CMM bundle info dictionary:
*
* Standard Mac OS X bundle keys:
*              kCFBundleExecutableKey
*              kCFBundleIdentifierKey
*              kCFBundleVersionKey
*              kCFBundleNameKey
*
* CMM specific keys:
*              kCMMInitializeLinkProfileProcName  -  CFStringRef of the name of a CMMInitializeLinkProfile
*                                                    function implemented in the CMM bundle executable.
*
*              kCMMInitializeTransformProcName    -  CFStringRef of the name of a CMMInitializeTransform
*                                                    function implemented in the CMM bundle executable.
*
*              kCMMApplyTransformProcName         -  CFStringRef of the name of a CMMApplyTransform function
*                                                    implemented in the CMM bundle executable.
*
*              kCMMCreateTransformPropertyProcName - CFStringRef of the name of a CMMCreateTransformProperty
*                                                    function implemented in the CMM bundle executable.
*                                                    Optional.
*/

#ifdef __cplusplus
}
#endif

#if !defined(__swift__)

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif

#endif /* __COLORSYNCCMM__ */
