//
//  Man.h
//  niweishenmezhemediao
//
//  Created by mac on 14-9-10.
//
//

#ifndef __niweishenmezhemediao__Man__
#define __niweishenmezhemediao__Man__

#include <iostream>
#include "Config.h"
#include "cocos2d.h"
using namespace cocos2d;

class Man:public CCSprite
{
public:
    Man();
    ~Man();
    
    int m_i_direction; //1 left 2 right
    bool  m_b_is_cuting; //ture cuting
    bool  m_b_is_live;
    
    CREATE_FUNC(Man);
    void initWithManFile(const char* fileName);
    
    CCSprite* m_pMan_sprite;
    void changeManDirection(int nDir);
    void PlayAnimation(const char* fileName);
    void PlayAnimationWithState(const int state);
    void CreateAnimation();
    CCAnimation* CreateAnimationWithFileName(const char* fileName);
    CCAnimation* m_pStandAnimation;
    CCAnimation* m_pCuntAnimation;
    CCAnimation* m_pDeadAnimation;
};

#endif /* defined(__niweishenmezhemediao__Man__) */
