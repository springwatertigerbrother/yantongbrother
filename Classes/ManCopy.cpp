//
//  ManCopy.c
//  niweishenmezhemediao
//
//  Created by huge on 14/9/14.
//
//

#include "Man.h"

Man::Man()
{
    
}
Man::~Man()
{
    
}

void Man::initWithManFile(const char* fileName)
{
    m_pMan_sprite = CCSprite::create(fileName);
    addChild(m_pMan_sprite);
    CreateAnimation();
    PlayAnimationWithState(1);
//    PlayAnimation("10056_attack");
}

void Man::PlayAnimation(const char* fileName)
{
    std::string tempStr = fileName;
    auto ache = CCSpriteFrameCache::sharedSpriteFrameCache();
    ache->addSpriteFramesWithFile((tempStr+".plist").c_str(),(tempStr+".png").c_str());
    
    std::vector<CCSpriteFrame*> animFramesvec;
    char str[100] = {0};
    for(int i = 1; i < 12; i++)
    {
        sprintf(str, "%s_10%02d.png",fileName,i);
        auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        animFramesvec.push_back(frame);
    }
    Vector<SpriteFrame*> animFrames;
    for (int i = 0; i<animFramesvec.size(); i++)
    {
        animFrames.pushBack(animFramesvec.at(i));
    }
    auto animation = CCAnimation::createWithSpriteFrames(animFrames, 0.01f);
    m_pMan_sprite->runAction(CCRepeatForever::create( CCAnimate::create(animation) ) );
}

void Man::changeManDirection(int nDir)
{
    if (nDir == left_man) {
        m_pMan_sprite->setFlipX(true);
    }else
    {
        m_pMan_sprite->setFlipX(false);
    }
}
CCAnimation* Man::CreateAnimationWithFileName(const char* fileName)
{
    std::string tempStr = fileName;
    auto ache = CCSpriteFrameCache::sharedSpriteFrameCache();
    ache->addSpriteFramesWithFile((tempStr+".plist").c_str(),(tempStr+".png").c_str());
    
    CCDictionary* dict =
    CCDictionary::createWithContentsOfFileThreadSafe((tempStr+".plist").c_str());
    CCDictionary* frames = (CCDictionary *) dict->objectForKey(std::string("frames"));
    int nCount = frames->count();
    std::vector<CCSpriteFrame*> animFramesvec;
    char str[100] = {0};
    for(int i = 1; i < nCount; i++)
    {
        sprintf(str, "%s_10%02d.png",fileName,i);
        auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        animFramesvec.push_back(frame);
    }
    Vector<SpriteFrame*> animFrames;
    for (int i = 0; i<animFramesvec.size(); i++)
    {
        animFrames.pushBack(animFramesvec.at(i));
    }
    auto animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);

    return animation;
}
void Man::CreateAnimation()
{
    m_pStandAnimation = CreateAnimationWithFileName("10056_stand");
    m_pStandAnimation->retain();
    m_pCuntAnimation = CreateAnimationWithFileName("10056_attack");
    m_pCuntAnimation->retain();
    m_pDeadAnimation = CreateAnimationWithFileName("10056_hurt");
    m_pDeadAnimation->retain();
}
void Man::PlayAnimationWithState(const int state)//1stand 2cut 3 dead
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    switch (state)
    {
        case 1:
            m_pMan_sprite->stopAllActions();
            m_pMan_sprite->runAction(CCRepeatForever::create( CCAnimate::create(m_pStandAnimation) )) ;
            break;
        case 2:
            m_pMan_sprite->stopAllActions();
            m_pMan_sprite->runAction(CCRepeatForever::create( CCAnimate::create(m_pCuntAnimation) )) ;
            break;
        case 3:
            m_pMan_sprite->stopAllActions();
            m_pMan_sprite->runAction(CCSequence::create(CCRepeatForever::create( CCAnimate::create(m_pDeadAnimation) ),CCScaleTo::create(0.25, 1.0,0.5),NULL));
            break;
        case 4:
            m_pMan_sprite->stopAllActions();
            m_pMan_sprite->runAction(CCSequence::create(CCRepeatForever::create( CCAnimate::create(m_pStandAnimation) ),CCScaleTo::create(0.5, 2,2),CCScaleTo::create(0.5, 2,2), NULL));
            break;
        default:
            break;
    }
}

