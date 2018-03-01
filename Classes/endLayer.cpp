//
//  endLayer.cpp
//  Fightplane-mobile
//
//  Created by yxmac on 2017/11/14.
//

#include "endLayer.hpp"
#include "ui/CocosGUI.h"
#include "GameLayer.hpp"
#include "EnermyData.hpp"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace ui;
USING_NS_CC;

Scene * endLayer::createScene() {
    
    auto scene = Scene::create();
    
    auto layer = endLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool endLayer::init() {
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/tiankong.mp3");
    
    auto btn = Button::create();
    
    btn->setTitleText("Game over !\nStart");
    
    btn->setTitleFontName("fonts/Marker Felt.ttf");
    
    btn->setTitleAlignment(TextHAlignment::CENTER);
    
    btn->setTitleFontSize(20);
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Size size = Director::getInstance()->getWinSize();
    
    btn->setAnchorPoint(Vec2(0.5, 0.5));
    
    btn->setPosition(Vec2(size.width/2, size.height/2));
    
//    btn->addTouchEventListener(CC_CALLBACK_2(endLayer::restart, this));
    
    Sprite *temp = Sprite::create("feidan.png");
    
    temp->setPosition(Vec2(0, 0));
    
    temp->setContentSize(Size(100, 50));
    
    this->addChild(temp);
    
    btn->addTouchEventListener(
                               [temp](Ref *sender,Widget::TouchEventType event){
        
                                   if (event == Widget::TouchEventType::ENDED) {
                                       Size size = temp->getContentSize();
                                       EnermyData::sharedAnermy()->curruntScore = 0;
                                       
                                       EnermyData::sharedAnermy()->timeAdd = 20;
                                       
                                       EnermyData::sharedAnermy()->enermyArray.clear();
                                       
                                       Scene *mainScene = GameLayer::createScene();
                                       
                                       Director::getInstance()->replaceScene(mainScene);
                                   }
    }
                               );

    
    
    addChild(btn);
    
    return true;
}

void endLayer:: restart(cocos2d::Ref* pSender,cocos2d::ui::Widget::TouchEventType event) {
    
    if (event == Widget::TouchEventType::ENDED) {
        
        EnermyData::sharedAnermy()->curruntScore = 0;
        
        EnermyData::sharedAnermy()->timeAdd = 20;
        
        EnermyData::sharedAnermy()->enermyArray.clear();
        
        Scene *mainScene = GameLayer::createScene();
        
        Director::getInstance()->replaceScene(mainScene);
    }
}

