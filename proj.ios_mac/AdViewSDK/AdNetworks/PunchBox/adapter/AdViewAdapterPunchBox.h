//
//  AdViewAdapterPunchBox.h
//  AdViewSDK
//
//  Created by Ma ming on 13-6-28.
//
//

#import "AdViewAdNetworkAdapter.h"
#import "CSBannerView.h"

@interface AdViewAdapterPunchBox : AdViewAdNetworkAdapter <CSBannerViewDelegate> {

}

+ (AdViewAdNetworkType)networkType;

@end
