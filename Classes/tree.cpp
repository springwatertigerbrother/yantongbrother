//
//  tree.cpp
//  niweishenmezhemediao
//
//  Created by mac on 14-9-10.
//
//

#include "tree.h"

Tree::Tree()
{
}
Tree::~Tree()
{

}

void Tree:: initWithTreeFile(const char* fileName)
{
    m_pTreeSprite =  CCSprite::create(fileName);
    if (m_pTreeSprite)
    {
        addChild(m_pTreeSprite);
    }
}
