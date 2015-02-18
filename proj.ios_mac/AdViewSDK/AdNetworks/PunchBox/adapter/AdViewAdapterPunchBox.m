//
//  AdViewAdapterPunchBox.m
//  AdViewSDK
//
//  Created by Ma ming on 13-6-28.
//
//

#import "AdViewAdapterPunchBox.h"
#import "AdViewViewImpl.h"
#import "AdViewConfig.h"
#import "AdViewAdNetworkConfig.h"
#import "AdViewDelegateProtocol.h"
#import "AdViewLog.h"
#import "AdViewAdNetworkAdapter+Helpers.h"
#import "AdViewAdNetworkRegistry.h"

#import "CSADRequest.h"
#import "ChanceAd.h"

@implementation AdViewAdapterPunchBox

+ (AdViewAdNetworkType)networkType {
    return AdViewAdNetworkTypePunchBox;
}

+ (void)load {
    if(NSClassFromString(@"ChanceAd") != nil) {
		[[AdViewAdNetworkRegistry sharedRegistry] registerClass:self];
	}

}

- (void)getAd {
    Class PunchBoxAdClass = NSClassFromString(@"ChanceAd");
    Class PBBannerClass = NSClassFromString(@"CSBannerView");
    if (nil == PunchBoxAdClass || nil == PBBannerClass) {
        AWLogInfo(@"no Chance lib, can not create.");
		[adViewView adapter:self didFailAd:nil];
        return;
    }

    NSString *appID = self.networkConfig.pubId;

    CSADRequest *adRequest = [CSADRequest requestWithRequestInterval:40 andDisplayTime:40];
    adRequest.placementID = self.networkConfig.pubId2;
    
    [PunchBoxAdClass startSession:appID];
    [self updateSizeParameter];
    CSBannerView *bannerView = [[PBBannerClass alloc] initWithFrame:self.rSizeAd];
    bannerView.delegate = self;
    self.adNetworkView = bannerView;
    [bannerView loadRequest:adRequest];
    [bannerView release];
    //设置是否是测试模式
//    [PunchBoxAdClass requestEventAd:@"adview" withPosition:CGPointMake(0, 0)];

}

- (BOOL)canMultiBeingDelegate {
    return NO;
}

- (void)updateSizeParameter {
    /*
     * auto for iphone, auto for ipad,
     * 320x50, 300x250,
     * 480x60, 728x90
     */

    CGSize sizeArr[] = {CGSizeMake(320,50),CGSizeMake(720,90),
        CGSizeMake(320,50),CGSizeMake(320,50),
        CGSizeMake(320,50),CGSizeMake(720,90)};
    
    [self setSizeParameter:nil size:sizeArr];
}


#pragma mark -
#pragma mark delegate

// 收到Banner广告
- (void)csBannerViewDidReceiveAd:(CSBannerView *)csBannerView
{
    if (csBannerView)
        [self.adViewView adapter:self didReceiveAdView:csBannerView];
}

// Banner广告数据错误
- (void)csBannerView:(CSBannerView*)csBannerView receiveAdError:(CSRequestError *)requestError
{
    [self.adViewView adapter:self didFailAd:nil];
}

// 将要展示Banner广告
- (void)csBannerViewWillPresentScreen:(CSBannerView *)csBannerView
{
    AWLogInfo(@"PunchBox will presentScreen");
}

// 移除Banner广告
- (void)csBannerViewDidDismissScreen:(CSBannerView *)csBannerView
{
    AWLogInfo(@"PunchBox will dismiss");
//    [self helperNotifyDelegateOfFullScreenModalDismissal];
}

- (void)stopBeingDelegate {
    AWLogInfo(@"PunchBox stop Being delegate");
    CSBannerView *banner = (CSBannerView*)self.adNetworkView;
    banner.delegate = nil;
    [banner removeFromSuperview];
}

@end
