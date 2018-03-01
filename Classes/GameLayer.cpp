//
//  GameLayer.cpp
//  Fightplane
//
//  Created by yxmac on 2017/5/22.
//
//

#include "GameLayer.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "JoyStick.hpp"
#include "BossMonster.hpp"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;
using namespace ui;

Scene* GameLayer::createScene() {
    
     auto scene = Scene::create();

     auto layer = GameLayer::create();

     scene->addChild(layer);

     return scene;
}

bool GameLayer::init(){
    
    if (!Layer::init()) {
        return false;
    }
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/background.mp3");
    
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    auto winsize = Director::getInstance()->getWinSize();
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto originSize = Director::getInstance()->getVisibleSize();
    
    auto sprite = Sprite::create("bg3_0.jpg");
//    sprite->setScale(winsize.width/visibleSize.width, winsize.height/visibleSize.height);
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
//    sprite->setPosition(Vec2(visibleSize.width/2+origin.x,origin.y+ visibleSize.height/2));
    sprite->setPosition(Vec2(winsize.width/2, winsize.height/2));
    Size size_back = sprite->getContentSize();
    sprite->setScale(winsize.width/size_back.width, winsize.height/size_back.height);
    
 
    myData = EnermyData::sharedAnermy();
//    this->addChild(sprite);
    
    xScroll = 0;
    
    sprite1 = Sprite::create("xingyun2.jpg");//只需要创建一个背景精灵
    
    sprite1->setAnchorPoint(Vec2(0., 0));
//    sprite1->setPosition(Vec2(winsize.width/2, winsize.height/2));
    sprite1->setPosition(Vec2(0, 0));

    Size size = sprite1->getContentSize();
    
    sprite1->setScale(winsize.width/size.width, winsize.width/size.width);

    addChild(sprite1);
    Texture2D::TexParams texRepeat = { GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_REPEAT };//这些openGL的参数不是对所有的图片类型都适合
    sprite1->getTexture()->setTexParameters(texRepeat);//设置精灵渲染时获得纹理的方式为:重复渲染
    
    
    
    schedule(schedule_selector(GameLayer::moveBackground), 0.01f);
    
    auto plane = Sprite::create("a4-5.png");
    
    this->m_Plane = plane;
    
    plane->setTag(8888);
    
    myData->enermyArray.pushBack(plane);
//    auto fireButton = MenuItemImage::create(
//                                            "smsBtn0.png",
//                                            "smsBtn1.png",
//                                            CC_CALLBACK_1(GameLayer::fire, this));
//    fireButton->setPosition(Vec2(winsize.width-fireButton->getContentSize().width/2,origin.y+fireButton->getContentSize().height/2));
    
    auto fireBtn = Button::create("smsBtn0.png",
                                 "smsBtn1.png","smsBtn0.png");
    
    fireBtn->addTouchEventListener(CC_CALLBACK_2(GameLayer::fire, this));

    
    fireBtn->setPosition(Vec2(winsize.width-fireBtn->getContentSize().width/2,origin.y+fireBtn->getContentSize().height/2));

    this->addChild(fireBtn);
//    fireBtn->addTouchEventListener(<#const ccWidgetTouchCallback &callback#>)
    
    auto topBtn = Button::create("top@2x.png",
                                 "top@2x.png","top@2x.png");
    topBtn->addTouchEventListener(CC_CALLBACK_2(GameLayer::moveTop, this));
        topBtn->setPosition(Vec2(origin.x+50,origin.y+50));

//    topBtn->setScale9Enabled(true);
    
    topBtn->setContentSize(Size(40, 40));

    Size mize = topBtn->getContentSize();
    
//    this->addChild(topBtn);
    
    topBtn->setPressedActionEnabled(true);
    
    topBtn->setTag(1000);
    
    auto leftBtn = Button::create("left@2x.png",
                                 "left@2x.png","left@2x.png");

    leftBtn->addTouchEventListener(CC_CALLBACK_2(GameLayer::moveLeft, this));
    
//    leftBtn->ignoreContentAdaptWithSize(true);
//    //    leftBtn->setScale(1.5);
//    leftBtn->setScale9Enabled(true);
//    
//    leftBtn->setContentSize(Size(50, 50));
    
    leftBtn->setTag(1001);
    
    leftBtn->setPosition(Vec2(origin.x+30,origin.y+30));
    
//    this->addChild(leftBtn);
    
    leftBtn->setPressedActionEnabled(true);
    
    
    auto rightBtn = Button::create("right@2x.png",
                                  "right@2x.png","right@2x.png");
    
    rightBtn->addTouchEventListener(CC_CALLBACK_2(GameLayer::moveRight, this));
    
    Size sizeBtn = rightBtn->getContentSize();
    
    rightBtn->setTag(1002);
    
    rightBtn->setPosition(Vec2(origin.x+70,origin.y+30));

//    this->addChild(rightBtn);
    
    rightBtn->setPressedActionEnabled(true);
  
    auto bottomBtn = Button::create("bottom@2x.png",
                                   "bottom@2x.png","bottom@2x.png");
    
    bottomBtn->addTouchEventListener(CC_CALLBACK_2(GameLayer::moveDown, this));
    
    bottomBtn->setTag(1003);
    
    bottomBtn->setPosition(Vec2(origin.x+50,origin.y+10));
    
    bottomBtn->setSize(Size(20, 10));

//    this->addChild(bottomBtn);
    bottomBtn->setPressedActionEnabled(true);
    
    rocker = JoyStick::create();
    rocker->setPosition(Vec2(10, 10));
//    rocker->setContentSize(Size(70, 70));
    this->addChild(rocker);
    
    Size btnSize = leftBtn->getContentSize();
  
    plane->setAnchorPoint(Vec2(0.5, 0.5));
    // position the sprite on the center of the screen
    plane->setPosition(Vec2(winsize.width/2,plane->getContentSize().height+origin.y));
    Size size_plane = plane->getContentSize();
    
    EnermyData::sharedAnermy()->hero = plane;
    plane->setScale(winsize.width*0.10/size_plane.width, winsize.height*0.10/size_plane.height);
    this->addChild(plane);
    
//    auto sprite = Sprite::create("HelloWorld.png");
//    
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
//    this->schedule(schedule_selector(GameLayer::fire), 0.5);
    this->schedule(schedule_selector(GameLayer::addEnemyPlane), 1);
    
    schedule(schedule_selector(GameLayer::schedulePos), 0.01);

    schedule(schedule_selector(GameLayer::timerAdd),1);
    
    schedule(schedule_selector(GameLayer::addBossEnermy), 1, 0, 1);
    
    
    
    EnermyData::sharedAnermy()->timeAdd = 20;
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::setScore), "notice", nullptr);
    
     scoreLable = Label::createWithTTF(StringUtils::format("Currunt point:%d",EnermyData::sharedAnermy()->curruntScore), "fonts/Marker Felt.ttf", 16);

    scoreLable->setPosition(Vec2(origin.x + originSize.width/10,
                            origin.y + visibleSize.height - scoreLable->getContentSize().height));
    
    // add the label as a child to this layer
    
    scoreLable->setAlignment(TextHAlignment::LEFT);
    this->addChild(scoreLable);
    
    
    
    bestLable = Label::createWithTTF(StringUtils::format("Best point:%d",UserDefault::getInstance()->getIntegerForKey("bestScore")?UserDefault::getInstance()->getIntegerForKey("bestScore"):0), "fonts/Marker Felt.ttf", 24);
    
    bestLable->setPosition(Vec2(origin.x + originSize.width/2,
                                 origin.y + visibleSize.height - scoreLable->getContentSize().height));
    
    // add the label as a child to this layer
    
    bestLable->setAlignment(TextHAlignment::LEFT);
    this->addChild(bestLable);
    
    return true;
    
    
}

void GameLayer::schedulePos(float dt)
{
    /*获取摇杆到圆点的位置*/
    auto dis = rocker->getRocker()->getPosition().distance(rocker->getRockerBg()->getPosition());
    dis /= 20.0;
    //    log("%f", dis);
    auto hero = getChildByTag(8888);
    float angle = rocker->getAngle();
    
    switch (rocker->getDir()) {
        case RDIRECTION::UP:
            
            if (hero->getPositionY()>=Director::getInstance()->getVisibleSize().height) {
                return;
            }
            
            hero->setPositionY(hero->getPositionY()+dis);
            break;
        case RDIRECTION::DOWN:
            if (hero->getPositionY()<=Director::getInstance()->getVisibleOrigin().y) {
                return;
            }
            hero->setPositionY(hero->getPositionY()-dis);
            break;
        case RDIRECTION::LEFT:
            if (hero->getPositionX()<=Director::getInstance()->getVisibleOrigin().x) {
                return;
            }
            hero->setPositionX(hero->getPositionX()-dis);
            break;
        case RDIRECTION::RIGHT:
            if (hero->getPositionX()>=Director::getInstance()->getVisibleSize().width) {
                return;
            }
            hero->setPositionX(hero->getPositionX()+dis);
            break;
        case RDIRECTION::L_UP:
            if (hero->getPositionX()<=Director::getInstance()->getVisibleOrigin().x||hero->getPositionY()>=Director::getInstance()->getVisibleSize().height) {
                return;
            }
            hero->setPosition(hero->getPosition()+Vec2(dis*cos(angle),dis*sin(angle)));
            break;
        case RDIRECTION::R_UP:
            if (hero->getPositionX()>=Director::getInstance()->getVisibleSize().width||hero->getPositionY()>=Director::getInstance()->getVisibleSize().height) {
                return;
            }
            hero->setPosition(hero->getPosition()+Vec2(dis*cos(angle),dis*sin(angle)));
            break;
        case RDIRECTION::L_DOWN:
            if (hero->getPositionY()<=Director::getInstance()->getVisibleOrigin().y||hero->getPositionX()<=Director::getInstance()->getVisibleOrigin().x) {
                return;
            }
            hero->setPosition(hero->getPosition()+Vec2(dis*cos(angle),-dis*sin(angle)));
            break;
        case RDIRECTION::R_DOWN:
            if (hero->getPositionY()>=Director::getInstance()->getVisibleSize().width||hero->getPositionY()<=Director::getInstance()->getVisibleOrigin().y) {
                return;
            }
            hero->setPosition(hero->getPosition()+Vec2(dis*cos(angle),-dis*sin(angle)));
            break;
            
        default:
            break;
    }
}

void GameLayer::moveBackground(float dt)
{
    sprite1->setTextureRect(Rect(0, (xScroll-=0.5), Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height+5));  //y轴的坐标每帧都递减(向下卷动),如果是递增,则地图向上卷动,如果是x轴坐标变化,则地图左右移动
}

void GameLayer::timerAdd(float dt)
{
    EnermyData::sharedAnermy()->timeAdd = EnermyData::sharedAnermy()->timeAdd+2;
    
    
   
}

void GameLayer::addBossEnermy(float dt) {
    
    BossMonster *boss = BossMonster::create();
    boss->setAnchorPoint(Vec2(0.5, 0.5));

//    boss->setScale(0.5, 0.5);

    boss->setContentSize(Size(80, 50));
    
    boss->setPosition(Vec2(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getVisibleSize().height));
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/bossbeijing.mp3");

    
    this->addChild(boss);

    
    Vec2 start = Vec2(0, -25);

    
    
    float s= start.length();
    
    float time =s/100;
    
    FiniteTimeAction *seq = MoveBy::create(time, start);
    
    Sequence *allseq = Sequence::create(seq,NULL, NULL);
    
    boss->runAction(seq);
    
    
}

void GameLayer::moveTop(cocos2d::Ref* pSender,Widget::TouchEventType event)
{
    Sprite *plane = (Sprite *)Node::getChildByTag(8888);
    
    Vec2 start = plane->getPosition();
    start.subtract(Vec2(plane->getPositionX(), -(Director::getInstance()->getVisibleSize().height-plane->getPositionY()*2-plane->getContentSize().height/2)));
    
    float s= start.length();
    
    float time =s/100;
    
    CallFuncN* callfun=CallFuncN::create(CC_CALLBACK_1(GameLayer::stopAction, this));
    
    FiniteTimeAction *seq = MoveBy::create(time, start);
    
    Sequence *allseq = Sequence::create(seq,callfun, NULL);
    
    
    
    allseq ->setTag(1);
    
    if (event == Widget::TouchEventType::BEGAN)
    {
        CCLOG("touch begin");
        
        plane->runAction(allseq);

    }
    
    if (event == Widget::TouchEventType::ENDED)
    {
        CCLOG("touch ended");
        
        
        plane->stopAction(plane->getActionByTag(1));

    }
    if (event == Widget::TouchEventType::CANCELED)
        
    {
        
        CCLOG("touch cancel");
        
        plane->stopAction(plane->getActionByTag(1));
        
    }
    
}


void GameLayer::moveDown(cocos2d::Ref* pSender,Widget::TouchEventType event)
{
    Sprite *plane = (Sprite *)Node::getChildByTag(8888);
    
    Vec2 start = plane->getPosition();
    Vec2 orign = Director::getInstance()->getVisibleOrigin();
    
    start.subtract(Vec2(plane->getPositionX(), plane->getPositionY()*2-plane->getContentSize().height/2));
    
    float s= start.length();
    
    float time =s/60;
    
    FiniteTimeAction *seq = MoveBy::create(time, start);
    
    Sequence *allseq = Sequence::create(seq, NULL);
    
    allseq ->setTag(2);
    
    if (event == Widget::TouchEventType::BEGAN)
    {
        CCLOG("touch begin");
        
        plane->runAction(allseq);
        
    }
    
    if (event == Widget::TouchEventType::ENDED)
    {
        CCLOG("touch ended");
        
        
        plane->stopAction(plane->getActionByTag(2));
        
    }
    if (event == Widget::TouchEventType::CANCELED)
    {
        CCLOG("touch cancel");
        
        
        plane->stopAction(plane->getActionByTag(2));
        
    }
    
    
   
}

void GameLayer::moveLeft(cocos2d::Ref* pSender,Widget::TouchEventType event)
{
    Sprite *plane = (Sprite *)Node::getChildByTag(8888);
    
    Vec2 start = plane->getPosition();
    start.subtract(Vec2(+ plane->getPositionX()*2-plane->getContentSize().width/2, plane->getPositionY()));
    
    float s= start.length();
    
    float time =s/60;
    
    FiniteTimeAction *seq = MoveBy::create(time, start);
    
    Sequence *allseq = Sequence::create(seq, NULL);
    
    allseq ->setTag(3);
    
    if (event == Widget::TouchEventType::BEGAN)
    {
        CCLOG("touch begin");
        
        plane->runAction(allseq);
        
    }
    
    if (event == Widget::TouchEventType::ENDED)
    {
        CCLOG("touch ended");
        
        
        plane->stopAction(plane->getActionByTag(3));
        
    }
    if (event == Widget::TouchEventType::CANCELED)
    {
        CCLOG("touch cancel");
        
        
        plane->stopAction(plane->getActionByTag(3));
        
    }
}

void GameLayer::moveRight(cocos2d::Ref* pSender,Widget::TouchEventType event)
{
    Sprite *plane = (Sprite *)Node::getChildByTag(8888);
    
    Vec2 start = plane->getPosition();
    start.subtract(Vec2(-(Director::getInstance()->getVisibleSize().width-plane->getPositionX()*2-plane->getContentSize().width/2), plane->getPositionY()));
    
    float s= start.length();
    
    float time =s/60;
    
    FiniteTimeAction *seq = MoveBy::create(time, start);
    
    Sequence *allseq = Sequence::create(seq, NULL);
    
    allseq ->setTag(4);
    
    if (event == Widget::TouchEventType::BEGAN)
    {
        CCLOG("touch begin");
        
//        CallFunc *func =
        
        plane->runAction(allseq);
        
    }
    
    if (event == Widget::TouchEventType::ENDED)
    {
        CCLOG("touch ended");
        
        
        plane->stopAction(plane->getActionByTag(4));
        
    }
    if (event == Widget::TouchEventType::CANCELED)
    {
        CCLOG("touch cancel");
        
        
        plane->stopAction(plane->getActionByTag(4));
        
    }

}

void GameLayer::addEnemyPlane(float tmp) {
//    SmallPlain *enermy = SmallPlain::create();
//    enermy->setPosition(CCRANDOM_0_1()*Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
    
    
    
    RandomPlane *enermy = RandomPlane::create();
    enermy->planeType = rand()%7;
    enermy->setPosition(CCRANDOM_0_1()*Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
    enermy->move(10);
    this->addChild(enermy);
}


void GameLayer::fire(cocos2d::Ref* pSender,Widget::TouchEventType event ) {
    
    if (event == Widget::TouchEventType::BEGAN) {
    
        SimpleAudioEngine::getInstance()->playEffect("sounds/fire.mp3");

        
    Sprite *plane = (Sprite *)Node::getChildByTag(8888);
    
    Sprite *bullet = Sprite::create("zidan1.png");
    bullet ->setScale(0.5, 0.5);
    bullet->setPosition(Vec2(plane->getPositionX(),plane->getPositionY()+0.5*plane->getContentSize().height));
    Size size_bullet = bullet->getContentSize();
    
    auto winsize = Director::getInstance()->getWinSize();

    bullet->setScale(winsize.width*0.015/size_bullet.width, winsize.height*0.04/size_bullet.height);
    Vec2 start = bullet->getPosition();
    start.subtract(Vec2(bullet->getPositionX(), -Director::getInstance()->getWinSize().height));
    
    myData->enermyArray.pushBack(bullet);

    float s= start.length();
    
    float time =s/60;
    
    CallFuncN* callfun=CallFuncN::create(CC_CALLBACK_1(GameLayer::remove, this));
    
    
    FiniteTimeAction *seq = MoveBy::create(time, start);
  
    
    Sequence *allseq = Sequence::create(seq,callfun, NULL);
    
    bullet->runAction(allseq);
    
    this->addChild(bullet);
    }
}

void GameLayer::setScore(Ref *sender) {
    
    
    
    scoreLable->setString(StringUtils::format("Currunt point:%d",EnermyData::sharedAnermy()->curruntScore));
    
    if (EnermyData::sharedAnermy()->curruntScore >=UserDefault::getInstance()->getIntegerForKey("bestScore")) {
        bestLable->setString(StringUtils::format("Best point:%d",EnermyData::sharedAnermy()->curruntScore));
        
        UserDefault::getInstance()->setIntegerForKey("bestScore", EnermyData::sharedAnermy()->curruntScore);
    }
    
}

void GameLayer::stopAction(Node *sender){
    
    log("结束action");
  
    sender->stopAllActions();
    
    
    
}

void GameLayer::remove(Node *sender){
    
    sender->removeFromParentAndCleanup(true);
//    data->bulletArr->removeObject(sender);//从数组中异移除
    myData->enermyArray.eraseObject(sender);
}
