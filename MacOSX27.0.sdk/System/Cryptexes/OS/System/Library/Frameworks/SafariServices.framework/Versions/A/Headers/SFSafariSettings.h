// Copyright © 2026 Apple Inc. All rights reserved.


#import <Foundation/Foundation.h>
#import <SafariServices/SFFoundation.h>

NS_ASSUME_NONNULL_BEGIN

SF_ENUM_AVAILABLE_MAC_SAFARI(27_0)
typedef NS_ENUM(NSInteger, SFSafariSettingsError) {
    /// The process does not have the permission to call this API.
    SFSafariSettingsErrorNotAllowed,
    /// The system was unable to perform the requested operation.
    SFSafariSettingsErrorFailed,
};

SF_EXTERN NSString * const SFSafariSettingsErrorDomain SF_AVAILABLE_MAC_SAFARI(27_0);

NS_SWIFT_SENDABLE
SF_CLASS_AVAILABLE_MAC_SAFARI(27_0)
@interface SFSafariSettings : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Query the value of the Safari settings toggle for AutoFill > User names and passwords
/// - Parameters:
///   - completionHandler: The block the system calls after the operation complets, with a boolean parameter representing the toggle value.
///     - term isEnabled: A boolean value representing the current value of the toggle.
///     - term error: An SFSafariSettingsError if any occurred. If non-nil, the value of `isEnabled`
+ (void)checkAutoFillUserNamesAndPasswordsEnabledWithCompletionHandler:(void (^)(BOOL isEnabled, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:isAutoFillUserNamesAndPasswordsEnabled());

@end

NS_ASSUME_NONNULL_END

