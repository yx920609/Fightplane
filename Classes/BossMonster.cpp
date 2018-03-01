//
//  BossMonster.cpp
//  Fightplane-mobile
//
//  Created by yxmac on 2017/11/15.
//

#include "BossMonster.hpp"
#include "GameLayer.hpp"
#include "EnermyData.hpp"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

bool BossMonster::init() {

    if (!this->Sprite::create()) {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bossEnermy.plist", "bossEnermy.png");

    this->setSpriteFrame("img_plane_boss_0.png");
    
//    schedule(schedule_selector(BossMonster::openFlyBullet), 1.5, 10, 0);
    
    schedule(schedule_selector(BossMonster::openFlyBullet), 2);
    
    schedule(schedule_selector(BossMonster::laserBoom), 3);
    
    scheduleUpdate();
    
    this->setRotation(180);
    
    return true;
}

void BossMonster::laserBoom(float dt) {
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("LASER.plist", "LASER.png");
    
    __Dictionary* dic = __Dictionary::createWithContentsOfFile("LASER.plist");
    
    __Dictionary* dic2 = dynamic_cast<__Dictionary*>(dic->objectForKey("frames"));
    
    Sprite* sp = createWithSpriteFrameName("img_bullet_laser_0.png");
    
    
    sp->setFlippedX(true);
    
    sp->setAnchorPoint(Vec2(0.5, 1));
    
    sp->setPosition(Vec2(this->getPosition().x, Director::getInstance()->getWinSize().height-this->getContentSize().height));
    
    sp->setScale(1, (Director::getInstance()->getWinSize().height-this->getContentSize().height+10)/sp->getContentSize().height);
       
    this->getParent()->addChild(sp);
    
    Vector<SpriteFrame*> allFrame;
    
    for (int i = 0; i < dic2->count(); i++) {
        SpriteFrame* sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("img_bullet_laser_%d.png",i));
//        sf->setAnchorPoint(Vec2(0.5, 1));
//        sf->getTexture()->getContentSize();
       Size size1 =  sf->getTexture()->getContentSize();
        Size size = sf->getOriginalSize();
        allFrame.pushBack(sf);
    }
    
    this->lazer = sp;

    sp->setTag(1999);
    
    Animation* animtaion = Animation::createWithSpriteFrames(allFrame, 0.1);
    
    Animate* animte = Animate::create(animtaion);
    
    animte->setTag(100);
    
//    Sequence* seq = Sequence::create(animte, CC_CALLBACK_1(BossMonster::removeLazer, this), NULL);
    
    Sequence* seq = Sequence::create(animte, RemoveSelf::create(true), NULL);

    sp->runAction(seq);
}

void BossMonster::removeLazer(Ref *sender) {
    
    this->lazer = NULL;
    
//    this->lazer ->release();
    
    
    
}

void BossMonster::openFlyBullet(float dt) {
    
    if (this->flyBulletArray.size()>=4) {
        return;
    }
    
    Sprite *leftBullet = Sprite::create("feidan.png");
    
    Sprite *rightBullet = Sprite::create("feidan.png");
    
    rightBullet->setRotation(180);

    leftBullet->setRotation(180);

    Vec2 orign = this->getPosition();
    
    leftBullet->setPosition(Vec2(orign.x-20, orign.y-20));
    
    rightBullet->setPosition(Vec2(orign.x+20, orign.y-20));
    
    this->getParent()->addChild(leftBullet);
    
    this->getParent()->addChild(rightBullet);
    
    this->flyBulletArray.pushBack(rightBullet);
    
    this->flyBulletArray.pushBack(leftBullet);

    schedule(schedule_selector(BossMonster::bulletMove), 0.1, 20, 0);
}

void BossMonster::bulletMove(float dt) {
    
    for (Sprite * bullet : this->flyBulletArray) {
    
    
    float x = EnermyData::sharedAnermy()->hero->getPosition().x;
    float y = EnermyData::sharedAnermy()->hero->getPosition().y;
    float a = this->getPosition().x - x;
    float b = this->getPosition().y- y;
    
    float angle = atanf(a / b);
    
//    if (angle>=0) {
        bullet->stopAllActions();
        float mDegree = CC_RADIANS_TO_DEGREES(angle);
        
        
        
        float endX = this->getPosition().x-(a / b)*this->getPosition().y;
        float endY = 0;
       bullet->setRotation(180+mDegree);
       
        if (((a/b<0)&&(b<0))||((a/b>0)&&(b<0))) {
             endX = this->getPosition().x-(a / b)*(this->getPosition().y-Director::getInstance()->getVisibleSize().height);
             endY = Director::getInstance()->getVisibleSize().height;
            bullet->setRotation(mDegree);
        }
    
        float flyVelocity = 200;//运行速度，可以自己控制，每秒所走的像素
        float flyLen = sqrt((this->getPosition().x - endX)*(this->getPosition().x - endX)+(this->getPosition().y - endY)*(this->getPosition().y - endY));
        float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间
        //子弹运行的距离和时间，从飞机处开始运行到目标
        auto actionMove = MoveTo::create(realFlyDuration, Point(endX, endY));
        //子弹执行完动作后进行函数回调，调用移除子弹函数
        
        
        auto callback = [&](Ref *sender) {
            
            Sprite *bullet = (Sprite *)sender;
            
            bullet->removeFromParentAndCleanup(true);
            
            this->flyBulletArray.eraseObject(bullet);
            
            log("删除追踪导弹");
        };
        
        CallFuncN* callfun=CallFuncN::create(callback);
 
//        CallFuncN* callfun=[](Ref *sender)

        
        //连续动作
        Sequence* sequence = Sequence::create(actionMove, callfun, NULL);
        //飞机开始跑动
        bullet->runAction(sequence);
    }
        
//    }
}

void BossMonster::update(float dt) {
    
    auto array = EnermyData::sharedAnermy()->enermyArray;
    auto selfArray = this->flyBulletArray;
    if (this->getParent()->getChildByTag(1999)) {
        if (this->lazer->boundingBox().intersectsRect(EnermyData::sharedAnermy()->hero->boundingBox())) {
            
            this->lazer->removeAllChildrenWithCleanup(true);
            
            this->removeFromParentAndCleanup(true);
            
            this->stopAction(1);
            
            return;
        }
    }
  
    
    for( Node *bullet : array) {

        if (this->boundingBox().intersectsRect(bullet->boundingBox())&&this->totalShooted>0) {
            
            EnermyData::sharedAnermy()->curruntScore +=50;

            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boom.plist", "boom.png");
            
            __Dictionary* dic = __Dictionary::createWithContentsOfFile("boom.plist");
            
            __Dictionary* dic2 = dynamic_cast<__Dictionary*>(dic->objectForKey("frames"));
            
            Sprite* sp = Sprite::createWithSpriteFrameName("anmition_1.png");
            
            sp->setFlippedX(true);
            
            sp->setPosition(bullet->getPosition());
            
            this->getParent()->addChild(sp);
            
            array.eraseObject(bullet);
            
            Vector<SpriteFrame*> allFrame;
            
            for (int i = 1; i <= dic2->count(); i++) {
                SpriteFrame* sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("anmition_%d.png",i));
                allFrame.pushBack(sf);
            }
            
            Animation* animtaion = Animation::createWithSpriteFrames(allFrame, 0.1);
            
            Animate* animte = Animate::create(animtaion);
            
            animte->setTag(100);
            
            Sequence* seq = Sequence::create(animte, RemoveSelf::create(true), NULL);
            
            sp->runAction(seq);
            
            this->totalShooted--;
            
            this->getParent()->removeChild(bullet);
            
            EnermyData::sharedAnermy()->enermyArray.eraseObject(bullet);
            
            NotificationCenter::getInstance()->postNotification("notice");

            break;

        }
        
        if (this->boundingBox().intersectsRect(bullet->boundingBox())&&this->totalShooted<=0) {
            EnermyData::sharedAnermy()->curruntScore +=1000;

            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boom.plist", "boom.png");
            
            __Dictionary* dic = __Dictionary::createWithContentsOfFile("boom.plist");
            
            __Dictionary* dic2 = dynamic_cast<__Dictionary*>(dic->objectForKey("frames"));
            
            Sprite* sp = Sprite::createWithSpriteFrameName("anmition_1.png");
//            sp->setFlippedX(true);
            
            
            
            sp->setPosition(this->getPosition());
            this->getParent()->addChild(sp);
         
            array.eraseObject(bullet);
            Vector<SpriteFrame*> allFrame;
            for (int i = 1; i <= dic2->count(); i++) {
                SpriteFrame* sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("anmition_%d.png",i));
                allFrame.pushBack(sf);
            }
            
            Animation* animtaion = Animation::createWithSpriteFrames(allFrame, 0.1);
            
            
            Animate* animte = Animate::create(animtaion);
            
            animte->setTag(100);
            
            Sequence* seq = Sequence::create(animte, RemoveSelf::create(true), NULL);
            
            sp->runAction(seq);
            
            if (bullet->getTag() == 8888) {
                
                EnermyData::sharedAnermy()->enermyArray.eraseObject(bullet);
                
                this->removeFromParentAndCleanup(true);
                
                this->stopAction(1);
                
                return;
            }
            
            EnermyData::sharedAnermy()->enermyArray.eraseObject(bullet);
            
            NotificationCenter::getInstance()->postNotification("notice");
            
            
            if (bullet->getTag() != 8888) {
                
                bullet->stopAllActions();
                
                bullet->removeFromParentAndCleanup(true);
             
                this->removeFromParentAndCleanup(true);
                
                
                
                return;

            }
            
            

        }
        
        
    }
    
    for( Node *bullet : selfArray) {
        if (bullet->boundingBox().intersectsRect(EnermyData::sharedAnermy()->hero->boundingBox())) {
            this->stopAction(1);
        }
        
    }
    
}

bool BossMonster:: stopAction(float dt) {
    //    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    Scene *endScene = endLayer::createScene();
    
    auto array = EnermyData::sharedAnermy()->enermyArray;
    

    array.clear();
    
    this->flyBulletArray.clear();
    
    //    this->getParent()->removeAllChildren();
    
    Director::getInstance()->replaceScene(endScene);
    
    return true;
}

void BossMonster::removeFlyBullet(Ref *sender) {
    Sprite *bullet = (Sprite *)sender;
    
    bullet->removeFromParentAndCleanup(true);
    
    log("删除追踪导弹");

    this->flyBulletArray.eraseObject(bullet);
}

void BossMonster::fireJiguang(float dt) {
    
}
