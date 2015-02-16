//
//  GameOverLayer.cpp
//  niweishenmezhemediao
//
//  Created by huge on 13/9/14.
//
//

#include "GameOverLayer.h"
#include "GameCenterScene.h"
#include "DataHome.h"
#include "AdScenesDemo.h"
#include "AdViewToolX.h"
#include "IADSimple.h"

//GameOverLayer::GameOverLayer()
//{
//
//}
//GameOverLayer::~GameOverLayer()
//{
//
//}

static int m_i_HistoryHighestScore;


bool GameOverLayer::init()
{
    if ( !CCLayerColor::initWithColor(ccc4(200, 100, 100, 100)))
    {
        return false;
    }
//    setTouchEnabled(true);
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSprite* pBg = CCSprite::create("images/gameoverBG2.jpg");
    pBg->setPosition(CCPointMake(s.width/2, s.height/2));
    pBg->setScale(0.6);
    pBg->setOpacity(200);
    addChild(pBg);
    
    CCMenuItemImage* pItem1 = CCMenuItemImage::create("images/restartn.png", "images/restartp.png", this, menu_selector(GameOverLayer::ReStartGame)) ;
    CCMenuItemImage* pItem2 = CCMenuItemImage::create("images/start2normal.png", "images/start2press.png", this, menu_selector(GameOverLayer::ExitGame)) ;
    //    pItem2->setFontSize(180);
//    CCMenu* pMenu2 = CCMenu::create(pItem2,NULL);
//    pItem2->setPosition(ccp(s.width/2, s.height/5));
//    pMenu2->setPosition(CCPointZero);
//    addChild(pMenu2);
    
//    CCMenuItemFont* pItem1 = CCMenuItemFont::create("restart", this, menu_selector(GameOverLayer::ReStartGame));
//    CCMenuItemFont* pItem2 = CCMenuItemFont::create("share",this,menu_selector(GameOverLayer::ExitGame));

    CCMenu* pMenu = CCMenu::create(pItem1,NULL);
    pMenu->alignItemsVerticallyWithPadding(20);
//    pItem1->setFontSize(30);
//    pItem2->setFontSize(30);
    
    pMenu->setPosition(ccp(s.width/2, s.height/3.5));
    addChild(pMenu);

    CCLabelBMFont* pGameoverLblBM = CCLabelBMFont::create("Game Over", "fonts/bitmapFontTest2.fnt");
    pGameoverLblBM->setString("Game Over");
    pGameoverLblBM->setScale(1.1);
    pGameoverLblBM->setPosition(ccp(s.width/2,s.height*0.7));
    addChild(pGameoverLblBM);

//    CCLabelTTF* pGameoverLbl = CCLabelTTF::create("Game Over", "ArialRoundedMTBold", 100);
//    pGameoverLbl->setColor(ccRED);
//    pGameoverLbl->setPosition(ccp(s.width/2,s.height*0.7));
//    addChild(pGameoverLbl);
    
    int nScore = DataHome::getInstance()->wScore;
    char tempStr[50] = {0};
    std::sprintf(tempStr, "%d",nScore);
    CCLabelBMFont* pScoreTitle = CCLabelBMFont::create("score", "fonts/bitmapFontTest.fnt", 1, kCCTextAlignmentCenter, CCPointZero);
    pScoreTitle->setPosition(ccp(s.width/2,s.height*0.6));
    addChild(pScoreTitle);
    
    CCLabelBMFont* pScoreValue = CCLabelBMFont::create(tempStr, "fonts/boundsTestFont.fnt", 1.8, kCCTextAlignmentCenter, CCPointZero);
    pScoreValue->setPosition(ccp(s.width/2,s.height*0.53));
    addChild(pScoreValue);
    
    
//    tempStr = "score:"+tempStr;
//    CCLabelTTF* pCurrentScoreLbl = CCLabelTTF::create(tempStr.c_str(), "ArialRoundedMTBold", 100);
//    pCurrentScoreLbl->setPosition(ccp(s.width/2,s.height*0.6));
//    addChild(pCurrentScoreLbl);
    
    if (nScore>m_i_HistoryHighestScore)
    {
        m_i_HistoryHighestScore = nScore;
    }
    char tempStr2[50] = {0};
    std::sprintf(tempStr2, "%d",m_i_HistoryHighestScore);

//    tempStr = std::to_string(m_i_HistoryHighestScore);
    CCLabelBMFont* pBestTitle = CCLabelBMFont::create("best",  "fonts/bitmapFontTest.fnt", 1, kCCTextAlignmentCenter, CCPointZero);
    pBestTitle->setPosition(ccp(s.width/2,s.height*0.48));
    addChild(pBestTitle);
    
    CCLabelBMFont* pBestValue = CCLabelBMFont::create(tempStr2, "fonts/boundsTestFont.fnt", 1.8, kCCTextAlignmentCenter, CCPointZero);
    pBestValue->setPosition(ccp(s.width/2,s.height*0.40));
    addChild(pBestValue);
//    
//    tempStr = "best:"+tempStr;
//    CCLabelTTF* pHightestLbl = CCLabelTTF::create(tempStr.c_str(), "ArialRoundedMTBold", 100);
//    pHightestLbl->setPosition(ccp(s.width/2,s.height*0.5));
//    addChild(pHightestLbl);

    AdViewToolX::setAdHidden(false);
    AdViewToolX::setAdPosition(AdViewToolX::AD_POS_CENTER, AdViewToolX::AD_POS_BOTTOM);
    
    IADSimple* simple = [IADSimple IADSimple];
    [simple.bannerView setHidden:false];

//    CCDirector::sharedDirector()->pushScene(AdBottomDemo::scene(AdSceneDemo::DemoAdBottom));

    
      return true;
}

void GameOverLayer::ReStartGame()
{
    AdViewToolX::setAdHidden(true);
    IADSimple* simple = [IADSimple IADSimple];
    [simple.bannerView setHidden:false];
    
    if (this->getParent())
    {
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        this->runAction(CCMoveTo::create(0.2, ccp(0,s.height)));

        ((GameCenter*)(this->getParent()))->StartGame();
//        ((HelloWorld*)(this->getParent()))->setTouchEnabled(true);
    }

//    this->removeFromParentAndCleanup(true);

}

void GameOverLayer::ExitGame()
{
    CCDirector::sharedDirector()->end();
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif

}

//
//void GameOverLayer::registerWithTouchDispatcher()
//{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
//}
//
//bool GameOverLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
//{
//    
//    CCPoint touchLocation = pTouch->getLocation();
//
//    return true;
//}
