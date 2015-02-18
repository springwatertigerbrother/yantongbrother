/*
 
 Copyright 2010 www.adview.cn. All rights reserved.
 
 */

#import "AdViewViewImpl.h"
#import "AdViewConfig.h"
#import "AdViewAdNetworkConfig.h"
#import "AdViewDelegateProtocol.h"
#import "AdViewLog.h"
#import "AdViewAdNetworkAdapter+Helpers.h"
#import "AdViewAdNetworkRegistry.h"
#import "AdViewAdapterMobiSage.h"
#import "AdviewObjCollector.h"

#define TestUserSpot @"all"

@implementation AdViewAdapterMobiSage
@synthesize adViewInternal;
@synthesize mobiSageAdView;

+ (AdViewAdNetworkType)networkType {
  return AdViewAdNetworkTypeAdSage;
}

+ (void)load {
	if(NSClassFromString(@"MobiSageBanner") != nil) {
        //AWLogInfo(@"AdView: Find MobiSage AdNetork");
		[[AdViewAdNetworkRegistry sharedRegistry] registerClass:self];
	}
}

- (void)actGetAd {
    NSString *apID = @"";
    NSTimeInterval tmStart = [[NSDate date] timeIntervalSince1970];
    
	Class mobiSageAdBannerClass = NSClassFromString (@"MobiSageBanner");
	if (nil == mobiSageAdBannerClass) {
		[adViewView adapter:self didFailAd:nil];
		AWLogInfo(@"no mobisage lib, can not create.");
		return;
	}
    
	if ([adViewDelegate respondsToSelector:@selector(mobiSageApIDString)]) {
		apID = [adViewDelegate mobiSageApIDString];
	}
	else {
		apID = networkConfig.pubId2;
	}
	
	[self updateSizeParameter];
	
#if 1	//根据厂商建议，不调用此。
    Class mobiSageAdViewManagerClass = NSClassFromString (@"MobiSageManager");
	if (nil != mobiSageAdViewManagerClass)
		[[mobiSageAdViewManagerClass getInstance] setPublisherID:apID];
#endif
	
    NSString *slotToken = networkConfig.pubId3;
    if (nil == slotToken) {
        slotToken = @"";
    }
    
    MobiSageBanner* adView = [[mobiSageAdBannerClass alloc] initWithDelegate:self   adSize:Default_size slotToken:slotToken intervalTime:Ad_NO_Refresh switchAnimeType:Random];
	
	if (nil == adView) {
		[adViewView adapter:self didFailAd:nil];
		return;
	}
    adView.frame = self.rSizeAd;
//    adView.delegate = self;
    self.adNetworkView = adView;
    [adView release];
    
    NSTimeInterval tmEnd = [[NSDate date] timeIntervalSince1970];
    
    AWLogInfo(@"mobisage getad time:%f", tmEnd - tmStart);
}

//For first load mobisage will use 5-9 second, use background mode.
- (void)getAd {
    //[self performSelectorInBackground:@selector(actGetAd) withObject:nil];
    [self setupDefaultDummyHackTimer];
#if 0       //如果异步处理，未完成就释放，可能出错，因此屏蔽。
    if ([NSThread isMultiThreaded]) {
        adThread_ = [[NSThread alloc] initWithTarget:self selector:@selector(actGetAd) object:nil];
        [adThread_ setName:@"mobisage_getad"];
        [adThread_ setThreadPriority:0.1f];
        [adThread_ start];
    } else
#endif
    {
        [self performSelector:@selector(actGetAd)];
    }
}

- (void)stopBeingDelegate {
    AWLogInfo(@"--MobiSage stopBeingDelegate");
	
    MobiSageBanner *banner = (MobiSageBanner*)self.adNetworkView;
    banner.delegate = nil;
    self.adNetworkView = nil;
    
	[self cleanupDummyHackTimer];
}

- (void)cleanupDummyRetain {
	[super cleanupDummyRetain];
    
    if ([adThread_ isExecuting]) {
        self.adViewView = nil;
        self.adViewDelegate = nil;
        [[AdviewObjCollector sharedCollector] addObj:self];
    }
}

- (void)updateSizeParameter {
    /*
     * auto for iphone, auto for ipad,
     * 320x50, 300x250,
     * 480x60, 728x90
     */
//    int flagArr[] = {Ad_320X50,Ad_728X90,
//        Ad_320X50,Ad_300X250,
//        Ad_468X60,Ad_728X90};
    CGSize sizeArr[] = {CGSizeMake(320, 50), CGSizeMake(728, 90),
        CGSizeMake(320, 50), CGSizeMake(300, 250),
        CGSizeMake(468, 60), CGSizeMake(728, 90)};
    
    [self setSizeParameter:nil size:sizeArr];
}

- (void)mobiSageBannerSuccessToShowAd:(MobiSageBanner *)adBanner
{
    AWLogInfo(@"mobiSageStartShowAd");
    [self cleanupDummyHackTimer];
    
//    [self.adViewInternal addSubview:self.mobiSageAdView];
    [self.adViewView adapter:self didReceiveAdView:adBanner];
}

- (void)mobiSageBannerPopADWindow:(MobiSageBanner*)adBanner {
    AWLogInfo(@"mobiSageWillPopAd");
    [self helperNotifyDelegateOfFullScreenModal];
}

- (void)mobiSageBannerHideADWindow:(MobiSageBanner*)adBanner {
    AWLogInfo(@"mobiSageHidePopAd");
    [self helperNotifyDelegateOfFullScreenModalDismissal];
}

- (void)mobiSageBannerFaildToShowAd:(MobiSageBanner*)adBanner withError:(NSError *)error {
	AWLogInfo(@"mobiSageActionError:%@",error.domain);
}

- (void)dealloc {
	[super dealloc];
}

#pragma mark delegate methods.

- (UIViewController *)viewControllerToPresent {
    if ([self.adViewDelegate respondsToSelector:@selector(viewControllerForPresentingModalView)])
        return [self.adViewDelegate viewControllerForPresentingModalView];
	return nil;
}

@end
