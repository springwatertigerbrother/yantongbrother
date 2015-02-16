#ifndef __GameCenter_SCENE_H__
#define __GameCenter_SCENE_H__

#include "cocos2d.h"
#include "Man.h"
#include "tree.h"

using namespace cocos2d;

struct TreesInfo
{
    CCPoint pos;
    int type;
};
class GameOverLayer;

class GameCenter : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    void update(float dt);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameCenter);
    
    std::vector<Tree*> m_tree_vec;
    std::vector<TreesInfo> m_trees_info_vec;
    int m_i_man_direction;
    int m_i_tree_type;
    int m_i_direction_clicked;

    bool m_b_isVisibel_tap;
    
    int m_i_score ;
    int m_i_current_level;
    bool m_b_crazy;
    Man* m_pMan;
    std::vector<CCPoint>m_man_vec;
    void StartGame();
    void InitTrees();
    void UpdateTreesWithInfo();
    void InitMan();
    void UpdateMan();
    bool IsBranchMeetMan();
    void ChangeTrees();
    void PlayCutTreeAnimationWithType();
    void RemoveAllTrees();
    void MoveTrees();
    void GameOver();
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ChangeSpeed();

    void RemoveSelfAfterAction(CCNode* pSender);
    //score content
    CCLabelTTF* m_pScorelbl;
    CCLabelBMFont* m_pLevellbl;
    CCSprite* m_pRootSprite;
    GameOverLayer* pGameOverLayer;
    
    // 如何疯狂砍 ： 1，任务先四角飞一圈然后回位，2，变大，人物靠边移动，让其别碰到站台；3，全屏震动一下，4，开始砍，用两帧做个动画，5，砍完后重新初始化树和位置，速度，人物变回去
    
    void CrazyCut();
    void StopMoveTrees();
    void StartMoveTrees();
    void BeforeCrazyAnimation();
    void BackToNormal();
    
};

#endif // __GameCenter_SCENE_H__
