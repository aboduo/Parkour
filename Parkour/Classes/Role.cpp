//
//  Role.cpp
//  Parkour
//
//  Created by sanren on 14-1-12.
//
//

#include "Role.h"


Role::Role():xSpeed(5),ySpeed(15),constXSpeed(xSpeed),constYSpeed(ySpeed)
{}

Role::~Role()
{}

bool Role::init()
{
    return true;
}

void Role::extraInit()
{
    
    CCTMXObjectGroup* group = getGameMap()->objectGroupNamed("Role");
    CCDictionary* dictionary = group->objectNamed("player");
    
    float x = dictionary->valueForKey("x")->floatValue();
    float y = dictionary->valueForKey("y")->floatValue();
    
    mSprite = CCSprite::create("Icon.png");
    mSprite->setAnchorPoint(CCPointZero);
    mSprite->setPosition(ccp(x,y));
    
    getGameMap()->addChild(mSprite,ROLE_ZORDER);
    
    setCurrentRoleState(ROLE_RUN);
    
    //setMapPointByRole();
    
    this->schedule(schedule_selector(Role::role_Update),0.016f);
    
    this->schedule(schedule_selector(Role::camera_Update),0.016f);
}

void Role::setCurrentRolePoint(CCPoint point)
{
    mSprite->setPosition(point);
    
}

CCPoint Role::getCurrentRolePoint()
{
    return mSprite->getPosition();
}

void Role::role_Update(float dt)
{
    role_Logic();
}

void Role::role_Logic()
{
    switch (getCurrentRoleState())
    {
        case ROLE_STAND_BY:
            UtDlog::showLog("Stand by");
            break;
        case ROLE_INVAILD_STATE:
            break;
        case ROLE_RUN:
            runLogic();
            break;
        case ROLE_JUMP_UP:
            jumpUpLogic();
            break;
        case ROLE_JUMP_DOWN:
            jumpDownLogic();
            break;
        
        default:
            break;
    }
}

void Role::runLogic()
{
    /*
     1,获取人物的位置点
     2,结合速度修改位置点
     3,传给新的人物位置
     */
    
    CCPoint preRolePoint = getCurrentRolePoint();
    CCPoint targetRolePoint = ccp(preRolePoint.x + xSpeed,preRolePoint.y);
    this->setCurrentRolePoint(targetRolePoint);
    
}
void Role::jumpUpLogic()
{
}
void Role::jumpDownLogic()
{
}

Role* Role::createWithTMX(CCTMXTiledMap* _map)
{
    Role* role = new Role();
    
    if (role&&role->init())
    {
        role->setGameMap(_map);
        
        role->extraInit();
        
        role->autorelease();
        
        return  role;
        
    }
    
    CC_SAFE_DELETE(role);
    
    return NULL;
}

void Role::camera_Update(float dt)
{
    setMapPointByRole();
}

void Role::setMapPointByRole()
{
    CCSize visableSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCSize mapTiledNum = getGameMap()->getMapSize();
    
    CCSize tiledSize = getGameMap()->getTileSize();
    
    CCSize mapSize = CCSizeMake(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);
    
    CCPoint rolePoint = mSprite->getPosition();
    
    float x = rolePoint.x > visableSize.width/4?rolePoint.x:visableSize.width/4;
    x = x < mapSize.width - visableSize.width*0.8?x:mapSize.width - visableSize.width*0.8;
    
    float y = rolePoint.y > visableSize.height/3?rolePoint.y:visableSize.height/3;
    y = y < mapSize.height/2?y:mapSize.height/2;
    
    CCPoint desPoint = ccp(x,y);
    CCPoint centerPoint = ccp(visableSize.width/2, visableSize.height/2);
    
    CCPoint rltPoint = ccpSub(centerPoint, desPoint);
    
    getGameMap()->setPosition(rltPoint);
}