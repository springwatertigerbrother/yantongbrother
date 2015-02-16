//
//  tree.h
//  niweishenmezhemediao
//
//  Created by mac on 14-9-10.
//
//

#ifndef __niweishenmezhemediao__tree__
#define __niweishenmezhemediao__tree__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class Tree:public CCSprite
{
public:
    CCSprite* m_pTreeSprite;
    int m_type;// 1 left branch 2 empty 3 right
    
    void PlayAnimtion(int nType);
    
    void initWithTreeFile(const char* fileName);
    
    Tree();
    ~Tree();
    CREATE_FUNC(Tree);

};

#endif /* defined(__niweishenmezhemediao__tree__) */
