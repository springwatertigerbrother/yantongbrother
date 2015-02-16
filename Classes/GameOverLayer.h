//
//  GameOverLayer.h
//  niweishenmezhemediao
//
//  Created by huge on 13/9/14.
//
//

#ifndef __niweishenmezhemediao__GameOverLayer__
#define __niweishenmezhemediao__GameOverLayer__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;


class GameOverLayer: public cocos2d::CCLayerColor
{
public:
//    GameOverLayer();
//    ~GameOverLayer();
    
    virtual bool init();
    CREATE_FUNC(GameOverLayer);
//    
//    virtual void registerWithTouchDispatcher();
//    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ReStartGame();
    void ExitGame();
};

#endif /* defined(__niweishenmezhemediao__GameOverLayer__) */
