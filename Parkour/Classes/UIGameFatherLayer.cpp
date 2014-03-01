//
//  UIGameFatherLayer.cpp
//  Parkour
//
//  Created by sanren on 14-1-9.
//
//

#include "UIGameFatherLayer.h"




UIGameFatherLayer::UIGameFatherLayer()
{
    _pGoldBatchNode = CCSpriteBatchNode::create("images/goldball.png");
    CC_SAFE_RETAIN(_pGoldBatchNode);
    CC_SAFE_RETAIN(m_GameMap);
}

UIGameFatherLayer::~UIGameFatherLayer()
{
    CC_SAFE_RELEASE_NULL(_pGoldBatchNode);
    CC_SAFE_RELEASE_NULL(m_GameMap);
}

bool UIGameFatherLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    initUI();
    initMap();
    initRole();
    initComponets();
    
    this->setTouchEnabled(true);
    return true;
}

void UIGameFatherLayer::initUI()
{
    
}

void UIGameFatherLayer::initComponets()
{
    std::vector<Gold_Struct> goldVector;
    
    m_GameMap->addChild(_pGoldBatchNode,GoldBatchNode);
    
    CCTMXObjectGroup* itemsGroup = m_GameMap->objectGroupNamed("items");
    CCObject* obj = NULL;
    
    CCARRAY_FOREACH(itemsGroup->getObjects(),obj)
    {
        CCDictionary* dictionary = (CCDictionary*)obj;
        if (dictionary->valueForKey("name")->compare("gold") ==0) {
            UtDlog::showLog("found gold obj");
            
            float x = dictionary->valueForKey("x")->floatValue();
            float y = dictionary->valueForKey("y")->floatValue();
            
            CCSprite* _gold = CCSprite::create("images/goldball.png");
            
            _pGoldBatchNode->addChild(_gold);
            _gold->setPosition(ccp(x,y));
            
            Gold_Struct _gs;
            
            _gs.goldSprite = _gold;
            _gs.goldValue = 100;
            
            goldVector.push_back(_gs);
        }
    }
    
    m_Role->setGoldVector(goldVector);

}

void UIGameFatherLayer::initMap()
{
    m_GameMap = CCTMXTiledMap::create("mapGrass.tmx");
    this->addChild(m_GameMap,1);
}

void UIGameFatherLayer::initRole()
{
    m_Role = Role::createWithTMX(m_GameMap);
    
    this->addChild(m_Role, ROLE_ZORDER);
    
//    CCTMXObjectGroup* group = m_GameMap->objectGroupNamed("Role");
//    CCDictionary* dictionary = group->objectNamed("player");
//    
//    int x = dictionary->valueForKey("x")->intValue();
//    int y = dictionary->valueForKey("y")->intValue();
//    
//    CCSprite* sp = CCSprite::create("Icon.png");
//    sp->setPosition(ccp(x,y));
//    sp->setAnchorPoint(CCPointZero);
//    
//    m_GameMap->addChild(sp, ROLE_ZORDER);
}

bool UIGameFatherLayer::ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent)
{
    dispatchTouchRoleMove();
    return true;
}

void UIGameFatherLayer::dispatchTouchRoleMove()
{
    if (m_Role->getCurrentRoleState() == ROLE_RUN) {
        m_Role->setCurrentRoleState(ROLE_JUMP_UP);
        return;
    }
}

void UIGameFatherLayer::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void UIGameFatherLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

CCScene* UIGameFatherLayer::scene()
{
    CCScene* sc = CCScene::create();
    
    sc->addChild(UIGameFatherLayer::create());
    
    return sc;
}
