//
//  GameStartLayer.cpp
//  niweishenmezhemediao
//
//  Created by huge on 13/9/14.
//
//

#include "GameStartLayer.h"

bool GameStartLayer::init()
{
    if ( !CCLayerColor::initWithColor(ccc4(200, 100, 100, 200)))
    {
        return false;
    }
    setTouchEnabled(true);
    //    setTouchEnabled(true);
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    ccLanguageType currentLanguage = CCApplication::sharedApplication()->getCurrentLanguage();

//    CCMenuItemFont* pItem1 = CCMenuItemFont::create("remove ADS", this, menu_selector(GameStartLayer::ReMoveAdvertisement));
//    
//    CCMenu* pMenu = CCMenu::create(pItem1,NULL);
//    pMenu->alignItemsVerticallyWithPadding(20);
//    pItem1->setFontSize(80);
//    
//    pMenu->setPosition(ccp(s.width/2, s.height/2));
//    addChild(pMenu);
    CCSprite* pBg = CCSprite::create("images/startBG1.png");
    pBg->setPosition(CCPointMake(s.width/2, s.height/1.5));
    pBg->setOpacity(200);
    addChild(pBg);
    CCLabelBMFont* pGameoverLblBM;
//    if (currentLanguage == kLanguageChinese) {
//     pGameoverLblBM = CCLabelBMFont::create("干掉 烟筒", "fonts/boundsTestFont.fnt");
//    }else
    {
     pGameoverLblBM = CCLabelBMFont::create("kill\n chimney", "fonts/boundsTestFont.fnt");

    }

//    CCLabelTTF* pGameoverLbl = CCLabelTTF::create("destroy the pipestem", "ArialRoundedMTBold", 40,CCSizeMake(300, 200),kCCTextAlignmentCenter);
    CCSize contentSize = pBg->getContentSize();
    pGameoverLblBM->setPosition(ccp(contentSize.width/2,contentSize.height*0.75));
    pGameoverLblBM->setScale(1.5);
    pGameoverLblBM->setAlignment(kCCTextAlignmentCenter);
    
    CCLabelTTF* plblDiscription = CCLabelTTF::create();
    std::string disStr ;
    if (currentLanguage == kLanguageChinese)
    {
        disStr = "我知道你们都有很好的环保意识，\n为了你们的健康请\n干掉烟筒！";
    }else
    {
        disStr = "you have a good awaess of environmental protection.\n for your health\n kill the chimney!!!";
    };
    plblDiscription->setFontSize(28);
    plblDiscription->setHorizontalAlignment(kCCTextAlignmentCenter);
    plblDiscription->setString(disStr.c_str());
    plblDiscription->setPosition(ccp(contentSize.width/2,contentSize.height*0.3));
    plblDiscription->setDimensions(ccp(contentSize.width*0.8, 100));
    plblDiscription->setColor(ccRED);
    pBg->addChild(plblDiscription);
//    pGameoverLblBM->setHorizontalAlignment(kCCTextAlignmentCenter);
    pBg->addChild(pGameoverLblBM);
    
//    CCMenuItemFont* pItem2 = CCMenuItemFont::create("start",this,menu_selector(GameStartLayer::StartGame));
    CCMenuItemImage* pItem2 = CCMenuItemImage::create("images/start2normal.png", "images/start2press.png", this, menu_selector(GameStartLayer::StartGame)) ;
//    pItem2->setFontSize(180);
    CCMenu* pMenu2 = CCMenu::create(pItem2,NULL);
    pItem2->setPosition(ccp(s.width/2, s.height/5));
    pMenu2->setPosition(CCPointZero);
    addChild(pMenu2);
    

    return true;
}

void GameStartLayer::ReMoveAdvertisement()
{
    
}
void GameStartLayer::StartGame()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    this->runAction(CCMoveTo::create(0.2, ccp(0,s.height)));
}
void GameStartLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool GameStartLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLog("gamestartlayer");
    setTouchEnabled(false);
    return true;
}