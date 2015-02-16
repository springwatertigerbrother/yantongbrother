#include "config.h"
#include "GameCenterScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverLayer.h"
#include "GameStartLayer.h"
#include "DataHome.h"

using namespace cocos2d;
using namespace CocosDenshion;
//
//enum ManDirectionEnum
//{
//    left_man = 1,
//    right_man = 3
//};
//enum TreeTypeEnum
//{
//    left_branch = 1,
//    empty_branch = 2,
//    right_branch = 3
//};
//enum ClickDirection
//{
//    left_click = 0,
//    right_click,
//};
//#define TOP 10
//#define TREES_NUM 8
//#define TREES_MOVE_TIME 0.3
//enum LayerEnum
//{
//    score_layer =100,
//    GameStartLayer_enum,
//    GameOverLayer_enum,
//    
//};

int increment = 1;
bool bPlaying = false;
int levelStep = 50;
float fTreeSpeed = 0.4f;
int crayCount = 30;
float crazyTime = 3;

#define  BGSPRITETAG 1000

CCScene* GameCenter::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameCenter *layer = GameCenter::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameCenter::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSprite* pBgSprite = CCSprite::create("images/bg2.png");
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    pBgSprite->setPosition(ccp(s.width/2, s.height/2));
    pBgSprite->setTag(BGSPRITETAG);
    addChild(pBgSprite);
    
    m_i_score = 0;
    m_i_current_level = 0;
    m_b_crazy = false;
    m_b_isVisibel_tap = true;
    
    GameStartLayer* pStarLayer = GameStartLayer::create();
    pStarLayer->setPosition(CCPointZero);
    addChild(pStarLayer,GameStartLayer_enum);
    StartGame();
    return true;
}

void GameCenter::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, false);
}

bool GameCenter::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    
    CCPoint touchLocation = pTouch->getLocation();
    //         touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
//    CCPoint local =  convertToNodeSpace(touchLocation);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
//    if (s.width/2 >= touchLocation.x) {
//        m_i_direction_clicked = left_click;
//        m_i_man_direction = left_man;
//    }else
//    {
//        m_i_direction_clicked = right_click;
//        m_i_man_direction = right_man;
//    }

    if (m_i_man_direction == left_man) {
        m_i_direction_clicked = right_click;
        m_i_man_direction = right_man;
    }else
    {
        m_i_direction_clicked = left_click;
        m_i_man_direction = left_man;
    }
//    BackToNormal();
//    PlayCutTreeAnimationWithType();
//    ChangeTrees();
    UpdateMan();
    
    if (bPlaying == false)
    {
//        StartGame();
        bPlaying = true;
        schedule(schedule_selector(GameCenter::MoveTrees), fTreeSpeed);

    }

    return true;
}

void GameCenter::InitTrees()
{
    RemoveAllTrees();
    m_trees_info_vec.clear();
    
    //init trees postion
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCPointMake(s.width/2, s.height/TREES_NUM);
    if (!m_pRootSprite)
    {
        m_pRootSprite = CCSprite::create("images/gg2.png");
        m_pRootSprite->setPosition(CCPointMake(s.width/2, -45));
        addChild(m_pRootSprite, 10);
    }
    
    for (int i = 0; i<8; i++)
    {
//        treesPosVec.push_back(CCPointMake(origin.x,origin.y*i));
        
        TreesInfo temInfo;
        temInfo.pos = CCPointMake(origin.x,origin.y*i + s.height/TREES_NUM);
        if (i<3)
        {
            temInfo.type = empty_branch;
        }
        else if(m_trees_info_vec[i-1].type == empty_branch)
        {
            temInfo.type = rand()%3 + 1;
        }
        else
        {
            temInfo.type = empty_branch;
        }
        
        m_trees_info_vec.push_back(temInfo);

    }
    UpdateTreesWithInfo();
}

void GameCenter::UpdateTreesWithInfo()
{
    
    for (int i = 0; i<m_trees_info_vec.size(); i++)
    {
        Tree* pTree = Tree::create();
        int nType = m_trees_info_vec[i].type;
        CCString* typeStr = CCString::createWithFormat("images/gg%d.png",nType);
        pTree->initWithTreeFile(typeStr->getCString());
        pTree->setPosition(m_trees_info_vec[i].pos);
        pTree->setTag(i);
        addChild(pTree);
        m_tree_vec.push_back(pTree);
    }
    m_i_tree_type = m_trees_info_vec[0].type;
}
bool GameCenter::IsBranchMeetMan()
{
    if (m_i_man_direction == m_i_tree_type)
    {
        return true;
    }
    return false;
}
void GameCenter::InitMan()
{
    if (m_pMan)
    {
        m_pMan->removeFromParentAndCleanup(true);
    }
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin1 = CCPointMake(s.width/2 - 100, s.height/TREES_NUM - 30);
    CCPoint origin2 = CCPointMake(s.width/2 + 100, s.height/TREES_NUM - 30);

    m_man_vec.push_back(origin1);
    m_man_vec.push_back(origin2);
    
    int Index = 1;
    m_i_man_direction = Index;
    
    m_pMan = Man::create();
    m_pMan->initWithManFile("Icon-72.png");
//    if (Index == 1)
//    {
//        m_i_man_direction = right_man;
//    }
    m_pMan->m_i_direction = m_i_man_direction;
    m_pMan->changeManDirection(m_i_man_direction);
    m_pMan->setPosition(m_man_vec.at(left_click));
    addChild(m_pMan,50);
    
//    m_i_tree_type = Index;
}
void GameCenter::UpdateMan()
{
    
    if (m_pMan)
    {
        m_pMan->setPosition(m_man_vec[m_i_direction_clicked]);
        m_pMan->changeManDirection(m_i_man_direction);
    }
}
void GameCenter::ChangeTrees()
{
    RemoveAllTrees();

    for (int i = 0; i<TREES_NUM-1; i++)
    {
        m_trees_info_vec[i].type = m_trees_info_vec[i+1].type;
    }
    
    TreesInfo tempInfo;
    tempInfo.pos = m_trees_info_vec.at(TREES_NUM-1).pos;
    
    if(m_trees_info_vec[TREES_NUM-1].type == empty_branch)
    {
        tempInfo.type = rand()%3 + 1;
    }
    else
    {
        tempInfo.type = empty_branch;
    }

//    int nType = rand()%3 + 1;
//    tempInfo.type = nType;
    m_trees_info_vec[TREES_NUM-1] = tempInfo;
    
    UpdateTreesWithInfo();
    
    m_i_score+=increment;
    
    CCMoveBy* pMoveby = CCMoveBy::create(0.1, ccp(0, -5));
    m_pRootSprite->runAction(CCSequence::create(pMoveby,pMoveby->reverse(),NULL));
}
void GameCenter::RemoveAllTrees()
{
    for (int i = 0; i<m_tree_vec.size(); i++)
    {
        m_tree_vec[i]->removeFromParentAndCleanup(true);
    }
    m_tree_vec.clear();
}
void GameCenter::GameOver()
{
    DataHome::getInstance()->wScore = m_i_score;
    
    setTouchEnabled(false);
    bPlaying = false;
    unscheduleUpdate();
    unschedule(schedule_selector(GameCenter::MoveTrees));
    m_pMan->PlayAnimationWithState(3);
    pGameOverLayer = GameOverLayer::create();
    pGameOverLayer->setAnchorPoint(CCPointZero);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    pGameOverLayer->setAnchorPoint(CCPointZero);
    pGameOverLayer->setPosition(ccp(0,s.height));
    pGameOverLayer->runAction(CCMoveTo::create(0.5,CCPointZero));
    addChild(pGameOverLayer,GameOverLayer_enum);
    CCLog("gameover");
}
void GameCenter::update(float dt)
{
    char tempStr[50] = {0};
    std::sprintf(tempStr, "%d",m_i_score);

//    std::string tempStr = (std::to_string(m_i_score));
//    tempStr = "score:"+ tempStr;
    m_pScorelbl->setString(tempStr);
    
    if (m_b_crazy)
    {
        return;
    }
    if (m_i_current_level<m_i_score/levelStep)
    {
  
//        BeforeCrazyAnimation();

        m_i_current_level ++;
        char strArray[100] = {0};
        sprintf(strArray, "%d",m_i_current_level);
        
        string tempStr = "level";
        tempStr+= strArray;
    }
    if (m_i_score == LEVEL1_NUM) {
        fTreeSpeed =0.18f;
        m_i_score+=increment;
        ChangeSpeed();

    }else     if (m_i_score == LEVEL2_NUM) {

        fTreeSpeed =0.15f;
        m_i_score+=increment;
        ChangeSpeed();
    }else     if (m_i_score == LEVEL3_NUM) {
        
        fTreeSpeed =0.12f;
        m_i_score+=increment;
        ChangeSpeed();
    }

    
    if (IsBranchMeetMan())
    {
        GameOver();
    }
}
void GameCenter::StopMoveTrees()
{
    m_b_crazy = false;
    unschedule(schedule_selector(GameCenter::MoveTrees));
}
void GameCenter::StartMoveTrees()
{
    schedule(schedule_selector(GameCenter::MoveTrees), CRAZY_SPEED);
}
void GameCenter::BeforeCrazyAnimation()
{
    StopMoveTrees();
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCSprite* sprite = dynamic_cast<CCSprite*>(this->getChildByTag(BGSPRITETAG));
    
    sprite->runAction(
                      CCRepeat::create(
                                            CCSequence::create(
                                                             CCMoveBy::create(0.05f, ccp(10,10)),
                                                             CCMoveBy::create(0.05f, ccp(-10,-10)),
                                                             NULL),2));
//    m_pMan->runAction(CCMoveTo::create(0.5, ccp(s.width-m_pMan->m_pMan_sprite->getContentSize().width/1.6, m_pMan->getPositionY())));
    m_pMan->PlayAnimationWithState(4);
    
    CCCallFunc* pCall1 = CCCallFunc::create(this, callfunc_selector(GameCenter::CrazyCut));
    CCCallFunc* pCall2 = CCCallFunc::create(this, callfunc_selector(GameCenter::StartMoveTrees));
    CCCallFunc* pCallStop = CCCallFunc::create(this, callfunc_selector(GameCenter::StopMoveTrees));
    CCCallFunc* pCallStartGame = CCCallFunc::create(this, callfunc_selector(GameCenter::StartGame));
    this->runAction(CCSequence::create(CCDelayTime::create(0.8),pCall1,CCDelayTime::create(CRAZY_TIME),pCallStop,pCallStartGame, NULL));
    
}
void GameCenter::BackToNormal()
{
    StartMoveTrees();
    
}
void GameCenter::PlayCutTreeAnimationWithType()
{
    m_pMan->stopAllActions();
    m_pMan->PlayAnimationWithState(2);
    int nRotateDir = -1;
    if (m_i_man_direction == left_man)
    {
        nRotateDir = 1;
    }
    int nType = m_i_tree_type;
   
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCSprite* pSpriteTree = NULL;
    CCString* typeStr = CCString::createWithFormat("images/gg%d.png",nType);
    pSpriteTree = CCSprite::create(typeStr->getCString());
    pSpriteTree->setPosition(m_trees_info_vec[0].pos);
    addChild(pSpriteTree,score_layer);
    auto action1 = CCRotateBy::create(TREES_MOVE_TIME, 180*nRotateDir);
    float fTargetX ;
    if (nRotateDir == 1)
    {
       fTargetX = nRotateDir*s.width;
    }else if (nRotateDir == -1)
    {
        fTargetX = 0;
    }
    auto actionMoveToSide = CCMoveTo::create(TREES_MOVE_TIME, ccp(fTargetX,s.height/TREES_NUM*2));
    auto action2 = CCCallFuncN::create(this, callfuncN_selector(GameCenter::RemoveSelfAfterAction));
//    pSpriteTree->runAction(CCSequence::create(CCSpawn::create(action1,actionMoveToSide), action2, NULL));
    pSpriteTree->runAction(CCSequence::create(action1, action2, NULL));
    pSpriteTree->runAction(actionMoveToSide);
}
void GameCenter::RemoveSelfAfterAction(CCNode* pSender)
{
    if (pSender)
    {
       pSender->removeFromParentAndCleanup(true);
    }
}
void GameCenter::MoveTrees()
{
//    if (m_b_crazy)
//    {
//        crayCount++;
//        if (crayCount > CRAZY_TIME)
//        {
//            m_b_crazy = false;
//            crayCount = 0;
//        }
//    }
    PlayCutTreeAnimationWithType();
    ChangeTrees();
}
void GameCenter::StartGame()
{
    m_i_score = 0;
    m_i_man_direction = -1;
    m_i_tree_type = -1;
    m_i_current_level = 0;
    fTreeSpeed = START_SPEED;

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    if (!m_pScorelbl)
    {
        m_pScorelbl = CCLabelTTF::create();
        m_pScorelbl->setPosition(ccp(s.width/2, s.height/2));
        m_pScorelbl->setFontSize(60);
        m_pScorelbl->enableStroke(ccBLACK, 5,true);
        m_pScorelbl->enableShadow(CCSizeMake(5, 5), 100, 10);
        addChild(m_pScorelbl, score_layer);
    }
    if (!m_pLevellbl)
    {
        
        m_pLevellbl = CCLabelBMFont::create("level 0", "fonts/boundsTestFont.fnt");
        addChild(m_pLevellbl,score_layer);
        m_pLevellbl->setScale(1.5);
        m_pLevellbl->setPosition(ccp(s.width/2, s.height/2 + 80));
    }else
    {
        m_pLevellbl->setString("0");
    }
    
    InitTrees();
    InitMan();
    setTouchEnabled(true);
    unscheduleUpdate();
    scheduleUpdate();

}
void GameCenter::CrazyCut()
{
    m_b_crazy = true;
    unschedule(schedule_selector(GameCenter::MoveTrees));
    schedule(schedule_selector(GameCenter::MoveTrees), 0.1f);
    return;
}
void GameCenter::ChangeSpeed()
{
    unschedule(schedule_selector(GameCenter::MoveTrees));
    schedule(schedule_selector(GameCenter::MoveTrees), fTreeSpeed);

}
void GameCenter::menuCloseCallback(CCObject* pSender)
{
    schedule(schedule_selector(GameCenter::MoveTrees), 1);

//    CCDirector::sharedDirector()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}
