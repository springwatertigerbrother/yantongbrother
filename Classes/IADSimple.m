//
//  IADSimple.m
//  niweishenmezhemediao
//
//  Created by huge on 27/1/15.
//
//

#import "IADSimple.h"

@implementation IADSimple

@synthesize bannerView;

static IADSimple*iadSimple = nil;

+(IADSimple*)IADSimple {
    
    if (iadSimple == nil)
    {
        iadSimple = [[self alloc]init];
    }
      
    return iadSimple;
    
}

@end
