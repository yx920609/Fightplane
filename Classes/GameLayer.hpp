//
//  GameLayer.hpp
//  Fightplane
//
//  Created by yxmac on 2017/5/22.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SmallPlain.hpp"
#include "EnermyData.hpp"
#include "ui/CocosGUI.h"
#include "endLayer.hpp"
#include "RandomPlane.hpp"
USING_NS_CC;
class JoyStick;

class GameLayer:public cocos2d::Layer {
    
    public:
    
    static cocos2d::Scene *createScene();
    
    virtual bool init();
    
    ~GameLayer() {
        NotificationCenter::getInstance()->removeObserver(this, "notice");
        }
    
    CREATE_FUNC(GameLayer);

    void fire(cocos2d::Ref* pSender,cocos2d::ui::Widget::TouchEventType event);

    void addEnemyPlane(float tmp);
    
    
    void moveTop(cocos2d::Ref* pSender,cocos2d::ui::Widget::TouchEventType event);
    
    void moveDown(cocos2d::Ref* pSender,cocos2d::ui::Widget::TouchEventType event);

    void moveLeft(cocos2d::Ref* pSender,cocos2d::ui::Widget::TouchEventType event);

    void moveRight(cocos2d::Ref* pSender,cocos2d::ui::Widget::TouchEventType event);

    
    void timerMoveTop();
    
    void timerMoveDown();

    void timerMoveRight();

    void timerMoveLeft();
    
    Label *scoreLable;

    Label *bestLable;

    Sprite *m_Plane;

private:
    
    EnermyData *myData;
    
    int curruntBtnTag;
    
    void  remove(Node *sender);
    
    void  stopAction(Node *sender);
    
    JoyStick* rocker;
    
    void schedulePos(float dt);
    
    void moveBackground(float dt);

    float xScroll;
    
    int timeAdd;
    
    Sprite *sprite1;
    

    void timerAdd (float dt);
    
    void setScore(Ref *sender);
    
    void addBossEnermy (float dt);
};

#endif /* GameLayer_hpp */
