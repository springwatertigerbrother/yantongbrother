/*

 AdNetwork.m

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

#import "AdViewAdNetworkConfig.h"
#import "AdViewConfig.h"
#import "AdViewAdNetworkRegistry.h"
#import "AdViewLog.h"
#import "AdViewError.h"
#import "AdViewClassWrapper.h"

#define kAdViewPubIdKey @"pubid"
#define kAdViewPubId2Key @"pubid2"
#define kAdViewPubId3Key @"pubid3"

@implementation AdViewAdNetworkConfig

@synthesize networkType;
@synthesize nid;
@synthesize networkName;
@synthesize trafficPercentage;
@synthesize priority;
@synthesize credentials;
@synthesize credentials2;
@synthesize credentials3;
@synthesize adapterClass;

- (id)initWithDictionary:(NSDictionary *)adNetConfigDict
       adNetworkRegistry:(AdViewAdNetworkRegistry *)registry
                   error:(AdViewError **)error {
  self = [super init];

  if (self != nil) {
    NSInteger temp;
    id ntype = [adNetConfigDict objectForKey:AWAdNetworkConfigKeyType];
    id netId = [adNetConfigDict objectForKey:AWAdNetworkConfigKeyNID];
    id netName = [adNetConfigDict objectForKey:AWAdNetworkConfigKeyName];
    id weight = [adNetConfigDict objectForKey:AWAdNetworkConfigKeyWeight];
    id pri = [adNetConfigDict objectForKey:AWAdNetworkConfigKeyPriority];

    if (ntype == nil || netId == nil || netName == nil || pri == nil) {
      NSString *errorMsg =
        @"Ad network config has no network type, network id, network name, or priority";
      if (error != nil) {
        *error = [AdViewError errorWithCode:AdViewConfigDataError
                                 description:errorMsg];
      }
      else {
        AWLogWarn(errorMsg);
      }

      [self release];
      return nil;
    }

    if (advIntVal(&temp, ntype)) {
      networkType = temp;
    }
    if ([netId isKindOfClass:[NSString class]]) {
      nid = [[NSString alloc] initWithString:netId];
    }
    if ([netName isKindOfClass:[NSString class]]) {
      networkName = [[NSString alloc] initWithString:netName];
    }

    double tempDouble;
    if (weight == nil) {
      trafficPercentage = 0.0;
    }
    else if (advDoubleVal(&tempDouble, weight)) {
      trafficPercentage = tempDouble;
    }

    if (advIntVal(&temp, pri)) {
      priority = temp;
    }

	  //trafficPercentage add by laizhiwen 110415
    if (networkType == 0 /*|| nid == nil*/ || networkName == nil || priority == 0 || trafficPercentage < 1.0) {
      NSString *errorMsg =
        @"Ad network config has invalid network type, network id, network name or priority or weight";
      if (error != nil) {
        *error = [AdViewError errorWithCode:AdViewConfigDataError
                                 description:errorMsg];
      }
      else {
        AWLogWarn(errorMsg);
      }

      [self release];
      return nil;
    }

    id cred = [adNetConfigDict objectForKey:AWAdNetworkConfigKeyCred];
    if (cred == nil) {
      credentials = nil;
    }
    else {
      if ([cred isKindOfClass:[NSDictionary class]]) {
        credentials = [[NSDictionary alloc] initWithDictionary:cred copyItems:YES];
      }
      else if ([cred isKindOfClass:[NSString class]]) {
		  cred = [cred stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        credentials = [[NSDictionary alloc] initWithObjectsAndKeys:
                       [NSString stringWithString:cred], kAdViewPubIdKey,
                       nil];
      }
    }
	  
	  id cred2 = [adNetConfigDict objectForKey:AWAdNetworkConfigKey2Cred];
	  if (cred2 == nil) {
		  credentials2 = nil;
	  }
	  else {
		  if ([cred2 isKindOfClass:[NSDictionary class]]) {
			  credentials2 = [[NSDictionary alloc] initWithDictionary:cred2 copyItems:YES];
		  }
		  else if ([cred2 isKindOfClass:[NSString class]]) {
			  cred2 = [cred2 stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
			  credentials2 = [[NSDictionary alloc] initWithObjectsAndKeys:
							 [NSString stringWithString:cred2], kAdViewPubId2Key,
							 nil];
		  }
	  }
	  
	  id cred3 = [adNetConfigDict objectForKey:AWAdNetworkConfigKey3Cred];
	  if (cred3 == nil) {
		  credentials3 = nil;
	  }
	  else {
		  if ([cred3 isKindOfClass:[NSDictionary class]]) {
			  credentials3 = [[NSDictionary alloc] initWithDictionary:cred3 copyItems:YES];
		  }
		  else if ([cred3 isKindOfClass:[NSString class]]) {
			  cred3 = [cred3 stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
			  credentials3 = [[NSDictionary alloc] initWithObjectsAndKeys:
							  [NSString stringWithString:cred3], kAdViewPubId3Key,
							  nil];
		  }
	  }	  

    adapterClass = [registry adapterClassFor:networkType].theClass;
    if (adapterClass == nil) {
      NSString *errorMsg =
      [NSString stringWithFormat:@"Ad network type %d not supported, no adapter found",
       networkType];
      if (error != nil) {
        *error = [AdViewError errorWithCode:AdViewConfigDataError
                                 description:errorMsg];
      }
      else {
        AWLogWarn(errorMsg);
      }

      [self release];
      return nil;
    }
  }

  return self;
}

- (NSString *)pubId {
  if (credentials == nil) return nil;
  return [credentials objectForKey:kAdViewPubIdKey];
}

- (NSString *)pubId2 {
	if (credentials2 == nil) return nil;
	return [credentials2 objectForKey:kAdViewPubId2Key];
}

- (NSString *)pubId3 {
	if (credentials3 == nil) return nil;
	return [credentials3 objectForKey:kAdViewPubId3Key];
}

- (NSString *)description {
  NSString *creds = [self pubId];
  if (creds == nil) {
    creds = @"{";
    for (NSString *k in [credentials keyEnumerator]) {
      creds = [creds stringByAppendingFormat:@"%@:%@ ",
               k, [credentials objectForKey:k]];
    }
    creds = [creds stringByAppendingString:@"}"];
  }
	
	NSString *creds2 = [self pubId2];
	if (creds2 == nil) {
		creds2 = @"{";
		for (NSString *k in [credentials2 keyEnumerator]) {
			creds = [creds2 stringByAppendingFormat:@"%@:%@ ",
					 k, [credentials2 objectForKey:k]];
		}
		creds2 = [creds2 stringByAppendingString:@"}"];
	}	
  return [NSString stringWithFormat:
          @"name:%@ type:%d nid:%@ weight:%lf priority:%d creds:%@ creds2:%@",
          networkName, networkType, nid, trafficPercentage, priority, creds, creds2];
}

- (void)dealloc {
  [nid release], nid = nil;
  [networkName release], networkName = nil;
  [credentials release], credentials = nil;
  [credentials2 release], credentials2 = nil;

  [super dealloc];
}

@end
