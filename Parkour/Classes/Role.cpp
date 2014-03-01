//
//  Role.cpp
//  Parkour
//
//  Created by sanren on 14-1-12.
//
//

#include "Role.h"


Role::Role():xSpeed(5),ySpeed(15),constXSpeed(xSpeed),constYSpeed(ySpeed),acceslate(0.9)
{
    m_particleBatchNode = CCParticleBatchNode::create("images/goldEffect.png");
    CC_SAFE_RETAIN(m_particleBatchNode);
}

Role::~Role()
{
    CC_SAFE_RELEASE_NULL(m_particleBatchNode);
}

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
    
    getGameMap()->addChild(m_particleBatchNode,Gold_Particle_Tag);
    
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

//修复碰撞
void Role::fixColl(COLL_STATE _collState,CCRect box)
{
    //算出相交的矩形
    //根据方向将人物拉回到应有的位置
    
    CCRect roleBox = mSprite->boundingBox();
    float maxX = roleBox.getMaxX()<box.getMaxX()?roleBox.getMaxX():box.getMaxX();
    float minX = roleBox.getMinX()>box.getMinX()?roleBox.getMinX():box.getMinX();
    
    float maxY = roleBox.getMaxY()<box.getMaxY()?roleBox.getMaxY():box.getMaxY();
    float minY = roleBox.getMinY()>box.getMinY()?roleBox.getMinY():box.getMinY();
    
    float width = maxX - minX;
    float height = maxY - minY;
    
    switch (_collState) {
        case COLL_BUTTOM:
            mSprite->setPositionY(mSprite->getPositionY()+height);
            break;
        case COLL_TOP:
            mSprite->setPositionY(mSprite->getPositionY()-height);
            break;
        case COLL_RIGHT:
            mSprite->setPositionX(mSprite->getPositionX()-width);
            break;
        case COLL_LEFT:
            mSprite->setPositionX(mSprite->getPositionX()+width);
            break;
        default:
            break;
    }
    
}

void Role::runLogic()
{
    
    
    if (isCollWithCollArea(COLL_RIGHT)) {
        this->setCurrentRoleState(ROLE_STAND_BY);
        return;
    }
    
    if (!isCollWithCollArea(COLL_BUTTOM)) {
        this->setCurrentRoleState(ROLE_JUMP_DOWN);
        return;
    }
    
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
    CCPoint preRolePoint = getCurrentRolePoint();
    
    
    ySpeed -= acceslate;
    
    if (ySpeed <= 0)
    {
        ySpeed = 0;
        //ROLE_JUMP_DOWN
        this->setCurrentRoleState(ROLE_JUMP_DOWN);
    }
    
    CCPoint targetRolePoint = ccp(preRolePoint.x+xSpeed, preRolePoint.y+ySpeed);
    
    this->setCurrentRolePoint(targetRolePoint);
    
}
void Role::jumpDownLogic()
{
    if (isCollWithCollArea(COLL_BUTTOM))
    {
        ySpeed = constYSpeed;
        this->setCurrentRoleState(ROLE_RUN);
        return;
    }
    
    CCPoint preRolePoint = getCurrentRolePoint();
    
    
    ySpeed += acceslate;
    
    if (ySpeed >= 15)
    {
        ySpeed = 15;
    }
    
    CCPoint targetRolePoint = ccp(preRolePoint.x+xSpeed, preRolePoint.y-ySpeed);
    
    this->setCurrentRolePoint(targetRolePoint);
    
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

bool Role::isCollWithCollArea(COLL_STATE _collState)
{
    bool bFlag=false;
    
    CCTMXObjectGroup* collGroup = getGameMap()->objectGroupNamed("coll");
    CCObject* obj = NULL;
    
    CCARRAY_FOREACH(collGroup->getObjects(), obj)
    {
        CCDictionary* dictionary = (CCDictionary*)obj;
        
        float x = dictionary->valueForKey("x")->floatValue();
        float y = dictionary->valueForKey("y")->floatValue();
        
        float width = dictionary->valueForKey("width")->floatValue();
        float height = dictionary->valueForKey("height")->floatValue();
        
        CCRect box = CCRectMake(x, y, width, height);
        
        switch (_collState) {
            case COLL_BUTTOM:
                bFlag = isCollWithBottom(box);
                break;
            case COLL_LEFT:
                bFlag = isCollWithLeft(box);
                break;
            case COLL_RIGHT:
                bFlag = isCollWithRight(box);
                break;
            case COLL_TOP:
                bFlag = isCollWithTop(box);
                break;
            default:
                break;
        }
        
        if (bFlag)
        {
            fixColl(_collState, box);
        }
    
    }
    return bFlag;
}

bool Role::isCollWithLeft(CCRect box)
{
    CCRect roleBox = mSprite->boundingBox();
    CCPoint rolePoint = ccp(roleBox.getMinX(), roleBox.getMidY());
    
    return box.containsPoint(rolePoint);
}

bool Role::isCollWithRight(CCRect box)
{
    CCRect roleBox = mSprite->boundingBox();
    CCPoint rolePoint = ccp(roleBox.getMaxX(), roleBox.getMidY());
    
    return box.containsPoint(rolePoint);
}

bool Role::isCollWithTop(CCRect box)
{
    CCRect roleBox = mSprite->boundingBox();
    CCPoint rolePoint = ccp(roleBox.getMidX(), roleBox.getMaxY());
    
    return box.containsPoint(rolePoint);
}

bool Role::isCollWithBottom(CCRect box)
{
    CCRect roleBox = mSprite->boundingBox();
    CCPoint rolePoint = ccp(roleBox.getMidX(), roleBox.getMinY());
    
    return box.containsPoint(rolePoint);
}

void Role::camera_Update(float dt){
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

void Role::collWithGold(float dt)
{
    for (unsigned int i=0; i<goldVector.size(); i++)
    {
        Gold_Struct gs = goldVector[i];
        
        if (gs.goldSprite&&mSprite->boundingBox().intersectsRect(gs.goldSprite->boundingBox()))
        {
            UtDlog::showLog("与金币碰撞了");
            
            CCPoint point = gs.goldSprite->getPosition();
            
            CCParticleSystemQuad* mParticle = CCParticleSystemQuad::create("images/goldEffect.plist");
            
            mParticle->setPosition(point);
            mParticle->setAutoRemoveOnFinish(true);//注意内存
            
            m_particleBatchNode->addChild(mParticle);

            gs.goldSprite->removeFromParentAndCleanup(true);
            goldVector.erase(goldVector.begin()+i);

            
        }
    }
}

void Role::onEnter()
{
    CCNode::onEnter();
    
    this->schedule(schedule_selector(Role::collWithGold), 0.016f);
    
}