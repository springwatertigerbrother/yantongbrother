/*

 AdViewAdapterGeneric.m

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

#import "AdViewAdapterGeneric.h"
#import "AdViewViewImpl.h"
#import "AdViewLog.h"
#import "AdViewAdNetworkAdapter+Helpers.h"
#import "AdViewAdNetworkRegistry.h"

@implementation AdViewAdapterGeneric

+ (AdViewAdNetworkType)networkType {
  return AdViewAdNetworkTypeGeneric;
}

+ (void)load {
  [[AdViewAdNetworkRegistry sharedRegistry] registerClass:self];
}

- (void)getAd {
  if ([adViewDelegate respondsToSelector:@selector(adViewReceivedGenericRequest:)]) {
    [adViewDelegate adViewReceivedGenericRequest:adViewView];
    [adViewView adapterDidFinishAdRequest:self];
  }
  else {
    AWLogWarn(@"Delegate does not implement adViewReceivedGenericRequest");
    [adViewView adapter:self didFailAd:nil];
  }
}

- (void)stopBeingDelegate {
  // nothing to do
}

- (void)dealloc {
  [super dealloc];
}

@end
