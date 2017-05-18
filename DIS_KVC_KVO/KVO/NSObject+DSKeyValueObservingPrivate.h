//
//  NSObject+DSKeyValueObservingPrivate.h
//  DIS_KVC_KVO
//
//  Created by renjinkui on 2017/2/18.
//  Copyright © 2017年 JK. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DSKeyValueObservance;
@class DSKeyValueProperty;
@class DSKeyValueObservationInfo;

typedef struct {
    id object;//8
    DSKeyValueObservance *observance;//c
}ImplicitObservanceAdditionInfo;

typedef struct {
    id relationshipObject;//10
    id observer;//14
    NSString *keyPathFromRelatedObject;//18
    id object;//1c
    void *context;//20
    BOOL flag;//24
}ImplicitObservanceRemovalInfo;

typedef struct ObservationInfoWatcher{
    id object;
    DSKeyValueObservationInfo *observationInfo;
    struct ObservationInfoWatcher *next;
}ObservationInfoWatcher;

typedef struct {
    CFMutableArrayRef pendingArray;//0
    ObservationInfoWatcher *firstWatcher;//4
    ImplicitObservanceAdditionInfo  implicitObservanceAdditionInfo;
    ImplicitObservanceRemovalInfo implicitObservanceRemovalInfo;
}DSKeyValueObservingTSD;

#define NSKeyValueObservingTSDKey 0x15
#define NSKeyValueObservingKeyPathTSDKey 0x20
#define NSKeyValueObservingObjectTSDKey 0x1F

#define DSKeyValueObservingTSDKey (NSKeyValueObservingTSDKey +1)
#define DSKeyValueObservingKeyPathTSDKey (NSKeyValueObservingKeyPathTSDKey +1)
#define DSKeyValueObservingObjectTSDKey (NSKeyValueObservingObjectTSDKey +1)

void DSKeyValueObservingTSDDestroy(void *data);
ImplicitObservanceAdditionInfo *DSKeyValueGetImplicitObservanceAdditionInfo();
ImplicitObservanceRemovalInfo *DSKeyValueGetImplicitObservanceRemovalInfo();

extern const CFArrayCallBacks DSKVOPendingNotificationArrayCallbacks;

const void *DSKVOPendingNotificationRetain(CFAllocatorRef allocator, const void *value);
void DSKVOPendingNotificationRelease(CFAllocatorRef allocator, const void *value);


extern dispatch_once_t isVMWare_onceToken;
extern BOOL isVMWare_doWorkarounds;

@interface NSObject (DSKeyValueObservingPrivate)

- (void)_d_changeValueForKey:(NSString *)key usingBlock:(void (^)())block;
- (void)_d_changeValueForKey:(NSString *)key1 key:(NSString *)key2 key:(NSString *)key3 usingBlock:(void (^)(void))block;
- (void)_d_changeValueForKeys:(NSString * *)keys count:(NSUInteger)count maybeOldValuesDict:(id)oldValuesDict usingBlock:(void (^)(void))block;
- (id)_d_implicitObservationInfo;
- (CFMutableArrayRef)_d_pendingChangeNotificationsArrayForKey:(NSString *)key create:(BOOL)create;
- (void)_d_notifyObserversOfChangeFromValuesForKeys:(NSDictionary *)fromValueForKeys toValuesForKeys:(NSDictionary *)toValueForKeys;
- (void)_d_didChangeValuesForKeys:(id)keys;
- (void)_d_willChangeValuesForKeys:(id)keys;
+ (BOOL)_d_shouldAddObservationForwardersForKey:(NSString *)key;

@end
