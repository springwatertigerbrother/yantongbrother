/*
 adview openapi ad-InMobi.
 */

#import "AdViewViewImpl.h"
#import "AdViewConfig.h"
#import "AdViewAdNetworkConfig.h"
#import "AdViewDelegateProtocol.h"
#import "AdViewLog.h"
#import "AdViewAdNetworkAdapter+Helpers.h"
#import "AdViewAdNetworkRegistry.h"
#import "AdViewAdapterInMobi.h"
#import "AdViewExtraManager.h"

@interface AdViewAdapterInMobi ()
@end


@implementation AdViewAdapterInMobi

+ (AdViewAdNetworkType)networkType {
    return AdViewAdNetworkTypeInMobi;
}

+ (void)load {
	if(NSClassFromString(@"IMBanner") != nil) {
		[[AdViewAdNetworkRegistry sharedRegistry] registerClass:self];
	}
}

- (void)getAd {
	Class IMBannerClass = NSClassFromString (@"IMBanner");
	
	if (nil == IMBannerClass) {
		[adViewView adapter:self didFailAd:nil];
		AWLogInfo(@"no inmobi lib, can not create.");
		return;
	}
    
    Class InMobiClass = NSClassFromString(@"InMobi");
    [InMobiClass initialize:[self appId]];
//    [InMobiClass setLogLevel:IMLogLevelDebug];
    
	[self updateSizeParameter];
        
	IMBanner *inmobiBanner = [[IMBanner alloc] initWithFrame:self.rSizeAd appId:[self appId] adSize:(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)?IM_UNIT_728x90:IM_UNIT_320x50];
    
    inmobiBanner.additionaParameters = [NSDictionary dictionaryWithObject:@"c_adview" forKey:@"tp"];   //4.0.3 渠道方法
    
    [inmobiBanner setDelegate:self];
	if (nil == inmobiBanner) {
		[adViewView adapter:self didFailAd:nil];
		return;
	}
    
//    [inmobiBanner addAdNetworkExtras:extra];
//    [extra release];
    
    [inmobiBanner loadBanner];
    
    self.adNetworkView = inmobiBanner;
    [inmobiBanner release];
}

- (void)stopBeingDelegate {
    IMBanner *inmobiBanner = (IMBanner *)self.adNetworkView;
    if (inmobiBanner != nil) {
        [inmobiBanner stopLoading];
        [inmobiBanner setDelegate:nil];
        self.adNetworkView = nil;
    }
}

- (void)updateSizeParameter {
    /*
     * auto for iphone, auto for ipad,
     * 320x50, 300x250,
     * 480x60, 728x90
     */
    int flagArr[] = {IM_UNIT_320x50,IM_UNIT_728x90,
        IM_UNIT_320x50,IM_UNIT_300x250,
        IM_UNIT_468x60,IM_UNIT_728x90};
    CGSize sizeArr[] = {CGSizeMake(320, 50),CGSizeMake(728, 90),
        CGSizeMake(320, 50),CGSizeMake(300, 250),
        CGSizeMake(468, 60),CGSizeMake(728, 90)};
    
    [self setSizeParameter:flagArr size:sizeArr];
}

- (NSString *) appId {
	NSString *apID;
	if ([adViewDelegate respondsToSelector:@selector(inmobiApIDString)]) {
		apID = [adViewDelegate inmobiApIDString];
	}
	else {
		apID = networkConfig.pubId;
	}
	
	return apID;
	
#if 0
	return @"4f0acf110cf2f1e96d8eb7ea";		//4f0acf110cf2f1e96d8eb7ea
#endif
}

#pragma mark delegate 

- (void)bannerDidReceiveAd:(IMBanner *)banner {
    AWLogInfo(@"inmobi did receive ad");
     [adViewView adapter:self didReceiveAdView:banner];
}

- (void)banner:(IMBanner *)banner didFailToReceiveAdWithError:(IMError *)error {
    AWLogInfo(@"inmobi did fail to receive ad");
    AWLogDebug(@"%@",error.domain);
    [adViewView adapter:self didFailAd:error];
}

- (void)bannerDidDismissScreen:(IMBanner *)banner {
    [self helperNotifyDelegateOfFullScreenModalDismissal];
}

- (void)bannerWillDismissScreen:(IMBanner *)banner {
}

-(void)bannerWillPresentScreen:(IMBanner *)banner {
    [self helperNotifyDelegateOfFullScreenModal];
}

-(void)bannerWillLeaveApplication:(IMBanner *)banner {
}

@end
