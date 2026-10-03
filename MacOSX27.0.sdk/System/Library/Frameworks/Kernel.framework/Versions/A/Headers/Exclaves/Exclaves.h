/*
 * Copyright (c) 1998-2023 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_EXCLAVES_H
#define _IOKIT_EXCLAVES_H



#if CONFIG_EXCLAVES

#include <kern/thread_call.h>
#include <libkern/OSTypes.h>
#include <stdbool.h>
#include <stdint.h>

#include <IOKit/IOReturn.h>

#ifdef __cplusplus

#include <libkern/c++/OSDictionary.h>
#include <libkern/c++/OSSymbol.h>


extern OSDictionary     *gExclaveProxyStates;
extern IORecursiveLock  *gExclaveProxyStateLock;
extern const OSSymbol * gDARTMapperFunctionSetActive;

extern "C" {
#endif /* __cplusplus */




enum IOExclaveInterruptUpcallType {
	kIOExclaveInterruptUpcallTypeRegister,
	kIOExclaveInterruptUpcallTypeRemove,
	kIOExclaveInterruptUpcallTypeEnable
};

struct IOExclaveInterruptUpcallArgs {
	int index;                                /* interrupt source slot */
	enum IOExclaveInterruptUpcallType type;   /* operation selector */
	union {
		struct {
			// Register an IOIES with no provider for testing purposes
			bool test_irq;
		} register_args;
		struct {
			bool enable;                  /* true = enable, false = disable */
		} enable_args;
	} data;
};


enum IOExclaveTimerUpcallType {
	kIOExclaveTimerUpcallTypeRegister,
	kIOExclaveTimerUpcallTypeRemove,
	kIOExclaveTimerUpcallTypeEnable,
	kIOExclaveTimerUpcallTypeSetTimeout,
	kIOExclaveTimerUpcallTypeCancelTimeout
};

struct IOExclaveTimerUpcallArgs {
	uint32_t timer_id;                        /* per-proxy timer slot id */
	enum IOExclaveTimerUpcallType type;       /* operation selector */
	union {
		struct {
			bool enable;                  /* true = enable, false = disable */
		} enable_args;
		struct {
			bool clock_continuous;        /* true = continuous clock, false = absolute */
			AbsoluteTime duration;        /* timeout value in the chosen clock */
			kern_return_t kr;             /* out: kernel return from arming the timer */
		} set_timeout_args;
	} data;
};


enum IOExclaveAsyncNotificationUpcallType {
	AsyncNotificationUpcallTypeSignal,
};

struct IOExclaveAsyncNotificationUpcallArgs {
	enum IOExclaveAsyncNotificationUpcallType type;  /* operation selector */
	uint32_t notificationID;                         /* notification source id */
};


enum IOExclaveMapperOperationUpcallType {
	MapperActivate,
	MapperDeactivate,
};

struct IOExclaveMapperOperationUpcallArgs {
	enum IOExclaveMapperOperationUpcallType type;    /* operation selector */
	uint32_t mapperIndex;                            /* index of the mapper to act on */
};


enum IOExclaveANEUpcallType {
	kIOExclaveANEUpcallTypeSetPowerState,
	kIOExclaveANEUpcallTypeWorkSubmit,
	kIOExclaveANEUpcallTypeWorkBegin,
	kIOExclaveANEUpcallTypeWorkEnd,
	kIOExclaveANEUpcallTypeUpdateXnuContent,
};

struct IOExclaveANEUpcallArgs {
	enum IOExclaveANEUpcallType type;     /* operation selector */
	union {
		struct {
			uint32_t desired_state;       /* target power state */
		} setpowerstate_args;
		
		struct {
			uint64_t arg0;                /* opaque ANE driver arg 0 */
			uint64_t arg1;                /* opaque ANE driver arg 1 */
			uint64_t arg2;                /* opaque ANE driver arg 2 */
			uint64_t arg3;                /* opaque ANE driver arg 3 */
		} work_args;
	};
};


enum IOExclaveLPWUpcallType {
	kIOExclaveLPWUpcallTypeCreateAssertion,
	kIOExclaveLPWUpcallTypeReleaseAssertion,
	kIOExclaveLPWUpcallTypeRequestRunMode,
};

struct IOExclaveLPWUpcallArgs {
	enum IOExclaveLPWUpcallType type;     /* operation selector */
	union {
		/*
		 * createassertion: fields are forwarded to the LPW
		 * subsystem unchanged. owner / data / types describe
		 * the requested assertion (their semantics are owned
		 * by the LPW IDL, not by this header); id_out
		 * receives the kernel-assigned assertion id on
		 * success.
		 */
		struct {
			uint64_t id_out;              /* out: new assertion id */
			uint64_t owner;               /* opaque assertion owner token */
			uint64_t data;                /* opaque assertion payload */
			uint64_t types;               /* opaque assertion type bitmap */
		} createassertion;
		struct {
			uint64_t id;                  /* assertion id to release */
		} releaseassertion;
		struct {
			uint64_t runmode_mask;        /* requested run-mode bits */
		} requestrunmode;
	} data;
};


bool IOExclaveInterruptUpcallHandler(uint64_t id, struct IOExclaveInterruptUpcallArgs *args);
bool IOExclaveTimerUpcallHandler(uint64_t id, struct IOExclaveTimerUpcallArgs *args);
bool IOExclaveLockWorkloop(uint64_t id, bool lock);
bool IOExclaveAsyncNotificationUpcallHandler(uint64_t id, struct IOExclaveAsyncNotificationUpcallArgs *args);
bool IOExclaveMapperOperationUpcallHandler(uint64_t id, struct IOExclaveMapperOperationUpcallArgs *args);
bool IOExclaveANEUpcallHandler(uint64_t id, struct IOExclaveANEUpcallArgs *args, bool *result);
IOReturn IOExclaveLPWUpcallHandler(struct IOExclaveLPWUpcallArgs *args);

IOReturn IOExclaveLPWCreateAssertion(uint64_t *id_out, const char *desc);
IOReturn IOExclaveLPWReleaseAssertion(uint64_t id);


void IOExclavesFullWake(const char * reason);

/* Test support */

struct IOExclaveTestSignalInterruptParam {
	uint64_t id;
	uint64_t index;
};
void IOExclaveTestSignalInterrupt(thread_call_param_t, thread_call_param_t);

void exclaves_wait_for_cpu_init(void);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif 

#endif 
