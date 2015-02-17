//
//  GameStartLayer.h
//  niweishenmezhemediao
//
//  Created by huge on 13/9/14.
//
//

#ifndef __niweishenmezhemediao__GameStartLayer__
#define __niweishenmezhemediao__GameStartLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class GameStartLayer:public CCLayerColor
{
    virtual bool init();
public:
    CREATE_FUNC(GameStartLayer);
    void StartGame();
    void ReMoveAdvertisement();
    void EnterGameCenter();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    
    EventListenerTouchOneByOne *listener ;

//    virtual void onEnter() override;

//    virtual void registerWithTouchDispatcher();
};

#endif /* defined(__niweishenmezhemediao__GameStartLayer__) */
