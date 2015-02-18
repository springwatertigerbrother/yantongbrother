/*

 AdViewConfigStore.h

  Copyright 2010 www.adview.cn

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 */

#import <Foundation/Foundation.h>
#import "AdViewConfigStore.h"
#import "AdViewConfig.h"
#import "AWNetworkReachabilityDelegate.h"

@class AWNetworkReachabilityWrapper;
@class AdViewDBManager;

typedef enum tagConfigMethod {
	ConfigMethod_DataFile = 0,
	ConfigMethod_OfflineFile = 1,
}ConfigMethod;

// Singleton class to store AdView configs, keyed by appKey. Fetched config
// is cached unless it is force-fetched using fetchConfig. Checks network
// reachability using AWNetworkReachabilityWrapper before making connections to
// fetch configs, so that that means it will wait forever until the config host
// is reachable.
@interface AdViewConfigStore : NSObject <AWNetworkReachabilityDelegate> {
  NSMutableDictionary *configs_;
  AdViewConfig *fetchingConfig_;

  AWNetworkReachabilityWrapper *reachability_;
  NSURLConnection *connection_;
  NSMutableData *receivedData_;
	int		reachCheckNum;
    
    AdViewDBManager *dbManager;
}

// Returns the singleton AdViewConfigStore object.
+ (AdViewConfigStore *)sharedStore;

// Deletes all existing configs.
+ (void)resetStore;

// Returns config for appKey. If config does not exist for appKey, goes and
// fetches the config from the server, the URL of which is taken from
// [delegate adViewConfigURL].
// Returns nil if appKey is nil or empty, another fetch is in progress, or
// error setting up reachability check.
- (AdViewConfig *)getConfig:(NSString *)appKey
                    delegate:(id<AdViewConfigDelegate>)delegate;

// Fetches (or re-fetch) the config for the given appKey. Always go to the
// network. Call this to get a new version of the config from the server.
// Returns nil if appKey is nil or empty, another fetch is in progress, or
// error setting up reachability check.
- (AdViewConfig *)fetchConfig:(NSString *)appKey
					blockMode:(BOOL)block
                      delegate:(id <AdViewConfigDelegate>)delegate;

// Fetches (or re-fetch) file config
- (AdViewConfig *)fetchFileConfig:(NSString *)appKey
						blockMode:(BOOL)block
						   method:(ConfigMethod)cfgMethod
					 delegate:(id <AdViewConfigDelegate>)delegate;

// For testing -- set mocks here.
@property (nonatomic,retain) AWNetworkReachabilityWrapper *reachability;
@property (nonatomic,retain) NSURLConnection *connection;
@property (nonatomic,retain) AdViewConfig *fetchingConfig;

- (void)setNeedParseConfig;
- (AdViewConfig*)getBufferConfig:(NSString*)appKey;

@end
