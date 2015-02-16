//
//  Config.h
//  niweishenmezhemediao
//
//  Created by mac on 14-9-10.
//
//

#ifndef niweishenmezhemediao_Config_h
#define niweishenmezhemediao_Config_h
#include "cocos2d.h"
#include <iostream>

using namespace std;


enum ManDirectionEnum
{
    left_man = 1,
    right_man = 3
};
enum TreeTypeEnum
{
    left_branch = 1,
    empty_branch = 2,
    right_branch = 3
};
enum ClickDirection
{
    left_click = 0,
    right_click,
};
#define TOP 10
#define TREES_NUM 8
#define TREES_MOVE_TIME 0.3
#define CRAZY_TIME 0.9
#define CRAZY_SPEED 0.3f
#define START_SPEED 0.25f
#define LEVEL1_NUM  50
#define LEVEL2_NUM  300
#define LEVEL3_NUM  500
enum LayerEnum
{
    score_layer =100,
    GameStartLayer_enum,
    GameOverLayer_enum,
    
};


#endif
