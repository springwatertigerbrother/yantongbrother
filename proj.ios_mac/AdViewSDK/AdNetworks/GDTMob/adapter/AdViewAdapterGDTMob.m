//
//  AdViewAdapterGDTMob.m
//  AdViewSDK
//
//  Created by 马明 on 14-1-28.
//
//

#import "AdViewAdapterGDTMob.h"
#import "AdViewViewImpl.h"
#import "AdViewConfig.h"
#import "AdViewAdNetworkConfig.h"
#import "AdViewDelegateProtocol.h"
#import "AdViewLog.h"
#import "AdViewAdNetworkAdapter+Helpers.h"
#import "AdViewAdNetworkRegistry.h"

@implementation AdViewAdapterGDTMob

+ (AdViewAdNetworkType)networkType {
    return AdViewAdNetworkTypeGDTMob;
}

+ (void)load {
    if (NSClassFromString(@"GDTMobBannerView") != nil) {
        [[AdViewAdNetworkRegistry sharedRegistry] registerClass:self];
    }
}

- (void)getAd {
    Class GDTBannerClass = NSClassFromString (@"GDTMobBannerView");
	
	if (nil == GDTBannerClass) {
		AWLogInfo(@"no GDTMob lib, can not create.");
		[adViewView adapter:self didFailAd:nil];
		return;
	}
	
	GDTMobBannerView* adView = (GDTMobBannerView*)[[self makeAdView] retain];
	if (nil == adView) {
		[adViewView adapter:self didFailAd:nil];
		return;
	}
	
	self.adNetworkView = adView;
    [adView loadAdAndShow]; // 开始加载广告
    
    [adView release];
//    [self setupDefaultDummyHackTimer];
}

//- (NSString *)appIdForAd {
//	NSString *apID;
//	if ([adViewDelegate respondsToSelector:@selector(DoMobApIDString)]) {
//		apID = [adViewDelegate DoMobApIDString];
//	}
//	else {
//		apID = networkConfig.pubId;
//	}
//	return apID;
//}

- (void)stopBeingDelegate {
    AWLogInfo(@"--GDTMob stopBeingDelegate--");
    GDTMobBannerView* gdtmobView = (GDTMobBannerView*)self.adNetworkView;
    
    gdtmobView.delegate = nil;
	gdtmobView.currentViewController = nil;
	self.adNetworkView = nil;
}

- (void)dealloc {
    [super dealloc];
}

- (UIView*)makeAdView {
    Class GDTBannerClass = NSClassFromString (@"GDTMobBannerView");
	
	if (nil == GDTBannerClass) {
		AWLogInfo(@"no GDTMob lib, can not create.");
		return nil;
	}
	
	if (nil == self) {
		AWLogInfo(@"have not set GDTMob adapter.");
		return nil;
	}
	
	AdViewAdapterGDTMob *adapter = (AdViewAdapterGDTMob*)self;
	
	[adapter updateSizeParameter];
	GDTMobBannerView* adView = [[GDTBannerClass alloc] initWithFrame:adapter.rSizeAd appkey:networkConfig.pubId placementId:networkConfig.pubId2];
    
	if (nil == adView) {
		AWLogInfo(@"did not alloc GDTMobView");
		return nil;
	}
	
    adView.frame = adapter.rSizeAd;
    adView.delegate = self; // 设置 Delegate
    adView.currentViewController = [self.adViewDelegate viewControllerForPresentingModalView];
    adView.interval = 0; // 设置刷新时间为0（不自动刷新）
    adView.isTestMode = [self isTestMode];
    adView.isGpsOn = [self helperUseGpsMode];
    
	return [adView autorelease];
}

#pragma mark -
#pragma mark GDTMob delegate
- (BOOL)shouldSendExMetric {
    return YES;
}

- (void)bannerViewMemoryWarning {}

- (void)bannerViewDidReceived {
    AWLogInfo(@"GDTMOb did receiveAd");
    [self.adViewView adapter:self didReceiveAdView:self.adNetworkView];
}

- (void)bannerViewFailToReceived:(int)errCode {
    AWLogInfo(@"GDTMob fail, code:%d",errCode);
    [self.adViewView adapter:self didFailAd:[NSError errorWithDomain:@"err code" code:errCode userInfo:nil]];
}

- (void)bannerViewDidPresentScreen {
    AWLogInfo(@"GDTMob did presentScreen");
}

- (void)bannerViewDidDismissScreen {
    AWLogInfo(@"GDTMob did dismissScreen");
}

- (void)bannerViewWillLeaveApplication {
    AWLogInfo(@"GDTMob click action");
//    [adViewView adapter:self shouldReport:self.adNetworkView DisplayOrClick:NO];
}

@end
