/*
 * ColorSync - ColorSyncDevice.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNCDEVICE__
#define __COLORSYNCDEVICE__

#ifdef __cplusplus
extern "C" {
#endif

#include <ColorSync/ColorSyncProfile.h>

#if !defined(__swift__)

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

#endif

/// A key whose value is the `CFUUIDRef` identifying the device.
CSEXTERN CFStringRef kColorSyncDeviceID CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;                /* CFUUIDRef */
/// A key whose value is one of the device-class constants below.
CSEXTERN CFStringRef kColorSyncDeviceClass CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;             /* one of the below : */
    /// The device class for a camera device.
    ///
    /// The string that represents a camera device is `cmra`.
    CSEXTERN CFStringRef kColorSyncCameraDeviceClass CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;   /* cmra */
    /// The device class for a display device.
    ///
    /// The string that represents a display device is `mntr`.
    CSEXTERN CFStringRef kColorSyncDisplayDeviceClass CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;  /* mntr */
    /// The device class for a printer device.
    ///
    /// The string that represents a printer device is `prtr`.
    CSEXTERN CFStringRef kColorSyncPrinterDeviceClass CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;  /* prtr */
    /// The device class for a scanner device.
    ///
    /// The string that represents a scanner device is `scnr`.
    CSEXTERN CFStringRef kColorSyncScannerDeviceClass CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;  /* scnr */

/// A key whose value is the `CFURLRef` of a device profile.
CSEXTERN CFStringRef kColorSyncDeviceProfileURL CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;

/// A key whose value is the device's localized name in the current locale.
CSEXTERN CFStringRef kColorSyncDeviceDescription CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;       /* CFString with a name in current locale */
/// A key whose value is a `CFDictionary` of the device's localized names.
CSEXTERN CFStringRef kColorSyncDeviceDescriptions CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;      /* CFDictionary with localized names */

/// A key whose value is a `CFDictionary` describing the device's factory profiles.
CSEXTERN CFStringRef kColorSyncFactoryProfiles CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;         /* CFDictionary containing factory profile info */
/// A key whose value is a `CFDictionary` describing the device's custom profiles.
CSEXTERN CFStringRef kColorSyncCustomProfiles CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;          /* CFDictionary containing custom profile info */

/// A key whose value is the device mode's localized name in the current locale.
CSEXTERN CFStringRef kColorSyncDeviceModeDescription CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;   /* CFString, e.g. Glossy, Best Quality */
/// A key whose value is a `CFDictionary` of the device mode's localized names.
CSEXTERN CFStringRef kColorSyncDeviceModeDescriptions CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;  /* CFDictionary with localized mode names */
/// A key whose value is the ProfileID of the device's default profile.
CSEXTERN CFStringRef kColorSyncDeviceDefaultProfileID CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;  /* see below */
/// A key specifying the host preference scope of a device; currently only `kCFPreferencesCurrentHost` is supported.
CSEXTERN CFStringRef kColorSyncDeviceHostScope CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;         /* currently only kCFPreferencesCurrentHost is supported */
/// A key specifying the user preference scope of a device; one of `kCFPreferencesCurrentUser` or `kCFPreferencesAnyUser`.
CSEXTERN CFStringRef kColorSyncDeviceUserScope CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;         /* kCFPreferences{Current,Any}User */
/// A key specifying the host preference scope of a profile; currently only `kCFPreferencesCurrentHost` is supported.
CSEXTERN CFStringRef kColorSyncProfileHostScope CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;        /* currently only kCFPreferencesCurrentHost is supported */
/// A key specifying the user preference scope of a profile; one of `kCFPreferencesCurrentUser` or `kCFPreferencesAnyUser`.
CSEXTERN CFStringRef kColorSyncProfileUserScope CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;        /* kCFPreferences{Current,Any}User */

/// A key in the device-profile-info dictionary whose value indicates whether the profile is a factory profile.
CSEXTERN CFStringRef kColorSyncDeviceProfileIsFactory CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;  /* Present in ColorSyncDeviceProfileInfo dictionary.*/
                                                        /* See ColorSyncDeviceProfileIterateCallback below. */
/// A key in the device-profile-info dictionary whose value indicates whether the profile is the default profile.
CSEXTERN CFStringRef kColorSyncDeviceProfileIsDefault CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;  /* ditto */
/// A key in the device-profile-info dictionary whose value indicates whether the profile is the current profile.
CSEXTERN CFStringRef kColorSyncDeviceProfileIsCurrent CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;  /* ditto */
/// A key in the device-profile-info dictionary whose value is the profile's ProfileID.
CSEXTERN CFStringRef kColorSyncDeviceProfileID CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;         /* ditto */

/// A notification that ColorSync posts when a device is registered.
CSEXTERN CFStringRef kColorSyncDeviceRegisteredNotification CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;          /* com.apple.ColorSync.DeviceRegisteredNotification */
/// A notification that ColorSync posts when a device is unregistered.
CSEXTERN CFStringRef kColorSyncDeviceUnregisteredNotification CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;        /* com.apple.ColorSync.DeviceUnregisteredNotification */
/// A notification that ColorSync posts when a device's profiles change.
CSEXTERN CFStringRef kColorSyncDeviceProfilesNotification CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;            /* com.apple.ColorSync.DeviceProfilesNotification */
/// A notification that ColorSync posts when a display device's profiles change.
CSEXTERN CFStringRef kColorSyncDisplayDeviceProfilesNotification CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;     /* com.apple.ColorSync.DisplayProfileNotification */
/// A notification that ColorSync posts when the profile repository changes.
CSEXTERN CFStringRef kColorSyncProfileRepositoryChangeNotification CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;   /* com.apple.ColorSync.ProfileRepositoryChangeNotification */
/// A notification concerning the window server's device registration.
CSEXTERN CFStringRef kColorSyncRegistrationUpdateWindowServer CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;        /* com.apple.ColorSync.kColorSyncRegistrationUpdateWindowServer */
    
/// Registers a device of the given class with ColorSync.
///
/// The `deviceInfo` dictionary requires the following keys:
///
/// - ``kColorSyncDeviceDescriptions``: A `CFDictionary` with localized names of the device.
///   Localization keys must be five-character strings containing a language code and region code
///   in the `lc_RG` format, and must contain (at least) the `en_US` locale.
/// - ``kColorSyncFactoryProfiles``: A `CFDictionary` of factory profile info dictionaries. The keys
///   are the profile IDs and the values are the profile info dictionaries.
///
/// It may also include the following optional keys:
///
/// - ``kColorSyncDeviceHostScope``: The host scope of the device; one of `kCFPreferencesCurrentHost`
///   or `kCFPreferencesAnyHost`. If you don't specify it, the framework assumes `kCFPreferencesCurrentHost`.
/// - ``kColorSyncDeviceUserScope``: The user scope of the device; one of `kCFPreferencesCurrentUser`
///   or `kCFPreferencesAnyUser`. If you don't specify it, the framework assumes `kCFPreferencesCurrentUser`.
///
/// The factory profiles dictionary (the value for the key ``kColorSyncFactoryProfiles`` in
/// `deviceInfo`) requires the following keys and values. A ProfileID (of `CFStringRef` type)
/// identifies each profile and serves as the key. The value associated with the key
/// is a profile info dictionary that describes an individual device profile.
///
/// - ``kColorSyncDeviceDefaultProfileID``: The associated value must be one of the ProfileIDs
///   present in the dictionary. Presence of this key is not required if there is only one factory
///   profile.
///
/// Each profile info `CFDictionary` requires the following keys:
///
/// - ``kColorSyncDeviceProfileURL``: The `CFURLRef` of the profile to register.
/// - ``kColorSyncDeviceModeDescriptions``: A `CFDictionary` with localized device mode names for the
///   profile. Localization keys must be five-character strings containing a language code and
///   region code in the `lc_RG` format, and must contain (at least) the `en_US` locale.
///   For example, `en_US` "Glossy Paper with best quality".
///
/// Example of a `deviceInfo` dictionary:
///
///     <<
///         kColorSyncDeviceDescriptions   <<
///                                             en_US  My Little Printer
///                                             de_DE  Mein Kleiner Drucker
///                                             fr_FR  Mon petit immprimeur
///                                             ...
///                                         >>
///         kColorSyncFactoryProfiles       <<
///                                             CFSTR("Profile 1")  <<
///                                                                     kColorSyncDeviceProfileURL    {CFURLRef}
///
///                                                                     kColorSyncDeviceModeDescriptions    <<
///                                                                                                             en_US Glossy Paper
///                                                                                                             de_DE Glanzpapier
///                                                                                                             fr_FR Papier glace
///                                                                                                             ...
///                                                                                                         >>
///                                             ...
///
///                                             kColorSyncDeviceDefaultProfileID  CFSTR("Profile 1")
///                                         >>
///         kColorSyncDeviceUserScope   kCFPreferencesAnyUser
///
///         kColorSyncDeviceHostScope   kCFPreferencesCurrentHost
///     <<
///
/// - Note: Scope for factory profiles is exactly the same as the device scope.
/// - Note: Pass `kCFNull` in lieu of the profile URL, or no URL key/value pair at all, if a
///   factory profile is not available. This enables setting a custom profile.
/// - Note: For compatibility with the legacy API, create the profile
///   keys as `CFString`s from `uint32_t` numbers as follows:
///   `CFStringRef key = CFStringCreateWithFormat(NULL, NULL, CFSTR("%u"), (uint32_t) i);`
///
/// - Parameters:
///   - deviceClass: The class of the device to register.
///   - deviceID: The identifier of the device to register.
///   - deviceInfo: A dictionary containing the information needed to register a device.
/// - Returns: `true` on success and `false` in case of failure.
CSEXTERN bool ColorSyncRegisterDevice (CFStringRef deviceClass, CFUUIDRef deviceID, CFDictionaryRef deviceInfo) CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;

/// Unregisters a device of the given class and identifier.
///
/// - Parameters:
///   - deviceClass: The class of the device to unregister.
///   - deviceID: The identifier of the device to unregister.
/// - Returns: `true` on success and `false` in case of failure.
CSEXTERN bool ColorSyncUnregisterDevice (CFStringRef deviceClass, CFUUIDRef deviceID) CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;

/// Sets custom profiles for a device in lieu of its factory profiles.
///
/// The `profileInfo` dictionary requires the following keys:
///
/// - ProfileIDs, which must be a subset of the ProfileIDs you registered the device with, or
///   ``kColorSyncDeviceDefaultProfileID`` for setting a custom default profile.
///
/// It requires the following values:
///
/// - The `CFURLRef` of the profile to set as a custom profile.
///
/// It may also include the following optional keys:
///
/// - ``kColorSyncProfileHostScope``: The host scope of the profile; one of `kCFPreferencesCurrentHost`
///   or `kCFPreferencesAnyHost`. If you don't specify it, the framework assumes `kCFPreferencesCurrentHost`.
/// - ``kColorSyncProfileUserScope``: The user scope of the profile; one of `kCFPreferencesCurrentUser`
///   or `kCFPreferencesAnyUser`. If you don't specify it, the framework assumes `kCFPreferencesCurrentUser`.
///
/// - Note: Profile scope for custom profiles cannot exceed the scope of the factory profiles.
/// - Note: There is only one host scope and user scope per dictionary (that is, per call).
/// - Note: Pass `kCFNull` in lieu of the profile URL to unset the custom profile and reset the
///   current profile to the factory profile.
///
/// - Parameters:
///   - deviceClass: The class of the device.
///   - deviceID: The identifier of the device.
///   - profileInfo: A `CFDictionary` containing the information about custom profiles to set in
///     lieu of factory profiles.
/// - Returns: `true` on success and `false` in case of failure.
CSEXTERN bool ColorSyncDeviceSetCustomProfiles (CFStringRef deviceClass, CFUUIDRef deviceID, CFDictionaryRef profileInfo) CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;

/// Copies information about a device, resolved for the current host and current user.
///
/// Returns a dictionary with the following keys and values resolved for the current host and
/// current user:
///
///     <<
///         kColorSyncDeviceClass                   {camera, display, printer, scanner}
///         kColorSyncDeviceID                      {CFUUIDRef registered with ColorSync}
///         kColorSyncDeviceDescription             {localized device description}
///         kColorSyncFactoryProfiles  (dictionary) <<
///                                                     {ProfileID}    (dictionary) <<
///                                                                                     kColorSyncDeviceProfileURL      {CFURLRef or kCFNull}
///                                                                                     kColorSyncDeviceModeDescription {localized mode description}
///                                                                                 >>
///                                                      ...
///                                                     kColorSyncDeviceDefaultProfileID {ProfileID}
///                                                 >>
///         kColorSyncCustomProfiles  (dictionary) <<
///                                                     {ProfileID}    {CFURLRef or kCFNull}
///                                                     ...
///                                                <<
///         kColorSyncDeviceUserScope              {kCFPreferencesAnyUser or kCFPreferencesCurrentUser}
///         kColorSyncDeviceHostScope              {kCFPreferencesAnyHost or kCFPreferencesCurrentHost}
///     >>
///
/// - Parameters:
///   - deviceClass: The class of the device.
///   - devID: The identifier of the device.
/// - Returns: A dictionary describing the device, or `NULL` if no matching device is registered.
CSEXTERN CFDictionaryRef __nullable ColorSyncDeviceCopyDeviceInfo (CFStringRef deviceClass, CFUUIDRef devID) CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;
    
/// A callback that ColorSync invokes for each device profile during iteration.
///
/// The `colorSyncDeviceProfileInfo` dictionary contains the following keys:
///
///     kColorSyncDeviceClass              {camera, display, printer, scanner}
///     kColorSyncDeviceID                 {CFUUIDRef registered with ColorSync}
///     kColorSyncDeviceDescription        {localized device description}
///     kColorSyncDeviceModeDescription    {localized device mode description}
///     kColorSyncDeviceProfileID          {ProfileID registered with ColorSync}
///     kColorSyncDeviceProfileURL         {CFURLRef registered with ColorSync}
///     kColorSyncDeviceProfileIsFactory   {kCFBooleanTrue or kCFBooleanFalse}
///     kColorSyncDeviceProfileIsDefault   {kCFBooleanTrue or kCFBooleanFalse}
///     kColorSyncDeviceProfileIsCurrent   {kCFBooleanTrue or kCFBooleanFalse}
///
/// - Parameters:
///   - colorSyncDeviceProfileInfo: A dictionary describing the device profile.
///   - userInfo: The user info passed to the iteration function. Optional.
typedef bool (*ColorSyncDeviceProfileIterateCallback) (CFDictionaryRef colorSyncDeviceProfileInfo,
                                                       void* __nullable userInfo) CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;
                                                       
/// Iterates over the profiles registered for all devices, invoking a callback for each.
///
/// - Parameters:
///   - callBack: The callback to invoke for each registered device profile.
///   - userInfo: Caller-supplied context passed through to the callback. Optional.
CSEXTERN void ColorSyncIterateDeviceProfiles(ColorSyncDeviceProfileIterateCallback callBack,
                                            void* __nullable userInfo) CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;
    
CSEXTERN CFUUIDRef CGDisplayCreateUUIDFromDisplayID (uint32_t displayID) CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;
/*
 * A utility function converting displayID to CFUUIDRef
 */

CSEXTERN uint32_t CGDisplayGetDisplayIDFromUUID (CFUUIDRef uuid) CS_AVAILABLE_STARTING(10.4) CS_UNAVAILABLE_EMBEDDED;
/*
 * A utility function converting first 32 bits of CFUUIDRef to displayID
 */
    
#if !defined(__swift__)

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif

#ifdef __cplusplus
}
#endif

#endif /* __COLORSYNCDEVICE__ */
