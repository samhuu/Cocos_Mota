#include "Hero.h"

Hero::Hero()
{
	sGlobal->hero = this;
	
}

Hero::~Hero()
{

}

bool Hero::init()
{
	if (!Node::init())
	{
		return false;
	}

	//根据向下行走动画的第一帧创建精灵spriteWithSpriteFrame
	heroSprite = Sprite::createWithSpriteFrame(sAnimationMgr->getAnimation(kDown)->getFrames().at(0)->getSpriteFrame());

	//设置锚点
	heroSprite->setAnchorPoint(Point::ZERO);

	//将用于显示的heroSprite加到自己的节点下
	this->addChild(heroSprite);

	

	//创建空的战斗动画精灵
	fightSprite = Sprite::create();

	this->addChild(fightSprite);

	//一开始不处于move状态。
	isHeroMoving = false;
	isHeroFighting = false;
	isDoorOpening = false;
	return true;
	
	

}



int Hero::getenemyID(int Gid)
{
	int res = (Gid + 4) / 4;
	return res;
}

int Hero::getenemyHp(int id)
{
	switch (id)
	{
	case 1:
		return 1000;
		break;
	case 2:
		return 2000;
		break;
	case 3:
		return 2000;
		break;
	case 4:
		return 2000;
		break;
	case 5:
		return 1000;
		break;
	case 6:
		return 1000;
		break;
	case 7:
		return 1000;
		break;
	case 8:
		return 3000;
		break;
	case 9:
		return 2000;
		break;
	case 10:
		return 2000;
		break;
	case 11:
		return 2000;
		break;
	case 12:
		return 5000;
		break;
	case 13:
		return 2000;
		break;
	case 14:
		return 5000;
		break;
	case 15:
		return 5000;
		break;
	case 16:
		return 5000;
		break;
	case 17:
		return 5000;
		break;
	case 18:
		return 5000;
		break;
	case 19:
		return 5000;
		break;
	case 20:
		return 5000;
		break;
	case 21:
		return 5000;
		break;
	case 22:
		return 5000;
		break;
	case 25:
		return 5000;
		break;
	}
}

int Hero::getenemyAttack(int id)
{
	switch (id)
	{
	case 1:
		return 100;
		break;
	case 2:
		return 200;
		break;
	case 3:
		return 200;
		break;
	case 4:
		return 200;
		break;
	case 5:
		return 100;
		break;
	case 6:
		return 100;
		break;
	case 7:
		return 100;
		break;
	case 8:
		return 300;
		break;
	case 9:
		return 200;
		break;
	case 10:
		return 200;
		break;
	case 11:
		return 200;
		break;
	case 12:
		return 500;
		break;
	case 13:
		return 200;
		break;
	case 14:
		return 500;
		break;
	case 15:
		return 500;
		break;
	case 16:
		return 500;
		break;
	case 17:
		return 500;
		break;
	case 18:
		return 500;
		break;
	case 19:
		return 500;
		break;
	case 20:
		return 500;
		break;
	case 21:
		return 500;
		break;
	case 22:
		return 500;
		break;
	case 25:
		return 500+sGlobal->def;
		break;
	}
}

int Hero::getenemyDefense(int id)
{
	switch (id)
	{
	case 1:
		return 0;
		break;
	case 2:
		return 0;
		break;
	case 3:
		return 0;
		break;
	case 4:
		return 0;
		break;
	case 5:
		return 0;
		break;
	case 6:
		return 0;
		break;
	case 7:
		return 0;
		break;
	case 8:
		return 0;
		break;
	case 9:
		return 0;
		break;
	case 10:
		return 0;
		break;
	case 11:
		return 0;
		break;
	case 12:
		return 100;
		break;
	case 13:
		return 100;
		break;
	case 14:
		return 100;
		break;
	case 15:
		return 100;
		break;
	case 16:
		return 100;
		break;
	case 17:
		return 100;
		break;
	case 18:
		return 100;
		break;
	case 19:
		return 100;
		break;
	case 20:
		return 100;
		break;
	case 21:
		return 100;
		break;
	case 22:
		return 100;
		break;
	case 25:
		return 100;
		break;
	}
}

int Hero::getitemHp(int id)
{
	switch (id)
	{
	case 0:
		return 500;
		break;
	case 1:
		return 0;
		break;
	case 4:
		return 1000;
		break;
	case 5:
		return 0;
		break;
	case 6:
		return 0;
		break;
	case 16:
		return 0;
		break;
	case 17:
		return 0;
		break;
	case 28:
		return 0;
		break;

	}

}


int Hero::getitemAtk(int id)
{
	switch (id)
	{
	case 0:
		return 500;
		break;
	case 1:
		return 0;
		break;
	case 4:
		return 500;
		break;
	case 5:
		return 0;
		break;
	case 6:
		return 0;
		break;
	case 16:
		return 0;
		break;
	case 17:
		return 0;
		break;
	case 28:
		return 500;
		break;

	}

}

int Hero::getitemDef(int id)
{
	switch (id)
	{
	case 0:
		return 0;
		break;
	case 1:
		return 50;
		break;
	case 4:
		return 0;
		break;
	case 5:
		return 0;
		break;
	case 6:
		return 0;
		break;
	case 16:
		return 0;
		break;
	case 17:
		return 0;
		break;
	case 28:
		return 20;
		break;
	
	}

}

void Hero::move(HeroDirection direction) 
{
	if (isHeroMoving)
	{
		return;

	}

	//移动的距离
	Point moveByPosition;

	//根据方向计算移动的距离
	switch (direction)
	{
	case kDown:
		moveByPosition = Point(0, -32);
		break;
	case kLeft:
		moveByPosition = Point(-32, 0);
		break;
	case kRight:
		moveByPosition = Point(32, 0);
		break;
	case kUp:
		moveByPosition = Point(0, 32);
		break;
	}

	//计算目标坐标，用当前勇士坐标加上移动距离
	targetPosition = this->getPosition() + moveByPosition;

	//调用checkCollision检测碰撞类型，如果是墙壁、怪物、门，则只需要设置勇士的朝向
	CollisionType collisionType = checkCollision(targetPosition);

	if (collisionType == kWall 
		|| collisionType == kEnemy
		|| collisionType == kDoor 
		|| collisionType == kNPC)
	{
		setFaceDirection((HeroDirection)direction);
		return;
	}

	//heroSprite仅播放行走动画
	heroSprite->runAction(sAnimationMgr->createAnimate(direction));
	

	//主体进行位移，结束时调用onMoveDone方法 把方向信息传递给onMoveDone方法
	Action *action = Sequence::create(
		MoveBy::create(0.20f, moveByPosition), 
		CallFuncN::create(CC_CALLBACK_1(Hero::onMoveDone, this, (void*)direction)), 
		NULL);

	this->runAction(action);
	char stats[60] = { 0 };
	sprintf(stats, "hp:%d  atk:%d  def:%d lv1:%d lv2:%d ", sGlobal->hp, sGlobal->atk, sGlobal->def, sGlobal->lv1key, sGlobal->lv2key);
	sGlobal->gameLayer->showStats(stats, getPosition());

	isHeroMoving = true;
}

void Hero::onMoveDone(Node* pTarget, void* data)
{
	//将void*先转换为int，再从int转换到枚举类型
	int direction = (int) data;
	setFaceDirection((HeroDirection)direction);
	isHeroMoving = false;
	sGlobal->gameLayer->setSceneScrollPosition(this->getPosition());

}

void Hero::setFaceDirection(HeroDirection direction)
{
	heroSprite->setTextureRect(Rect(0, 32*direction, 32, 32));
}

//判断碰撞类型
CollisionType Hero::checkCollision(Point heroPosition) 
{
	//cocos2d-x坐标转换为Tilemap坐标
	targetTileCoord = sGlobal->gameMap->tileCoordForPosition(heroPosition);

	//如果勇士坐标超过地图边界，返回kWall类型，阻止其移动
	if (heroPosition.x < 0
		|| targetTileCoord.x > sGlobal->gameMap->getMapSize().width - 1
		|| targetTileCoord.y < 0
		|| targetTileCoord.y > sGlobal->gameMap->getMapSize().height - 1)
	{
		return kWall;
	}

	//获取墙壁层对应坐标的图块ID
	int targetTileGID = sGlobal->gameMap->getWallLayer()->getTileGIDAt(targetTileCoord);

	//如果图块ID不为0，表示有墙
	if (targetTileGID) 
	{
		return kWall;
	}

	//获取怪物层对应坐标的图块ID
	targetTileGID = sGlobal->gameMap->getEnemyLayer()->getTileGIDAt(targetTileCoord);
	int gid = targetTileGID;
	//如果图块ID不为0，表示有怪物
	if (gid) 
	{
	
		
		//开始战斗
		fight();
	
		return kEnemy;
	}

	//获取物品层对应坐标的图块ID
	targetTileGID = sGlobal->gameMap->getItemLayer()->getTileGIDAt(targetTileCoord);

	//如果图块ID不为0，表示有物品
	if (targetTileGID)
	{
	
		//拾取物品
		pickUpItem();
		return kItem;
	}

	//获取门层对应坐标的图块ID
	targetTileGID = sGlobal->gameMap->getDoorLayer()->getTileGIDAt(targetTileCoord);

	//如果图块ID不为0，表示有门
	if (targetTileGID)
	{
		//打开门
		openDoor(targetTileGID);
		return kDoor;
	}

	int index = targetTileCoord.x + targetTileCoord.y * sGlobal->gameMap->getMapSize().width;

	//从npc字典中查询
	NPC *npc = sGlobal->gameMap->npcDict.at(index);
	if (npc != NULL)
	{
		actWithNPC();
		return kNPC;
	}

	//从Teleport字典中查询
	Teleport *teleport = sGlobal->gameMap->teleportDict.at(index);
	if (teleport != NULL)
	{
		doTeleport(teleport);
		return kTeleport;
	}

	//可以通行
	return kNone;
}

//开始战斗
void Hero::fight()
{
	//已经在战斗中，避免重复战斗
	if (isHeroFighting)
	{
		return;
	}
	isHeroFighting = true;

	int enemyGID = sGlobal->gameMap->getEnemyLayer()->getTileGIDAt(targetTileCoord);
	int id = getenemyID(enemyGID);
	int e_hp=   getenemyHp(id);
	int e_atk = getenemyAttack(id);
	int e_def = getenemyDefense(id);



	int hploss = (e_hp / (sGlobal->atk - e_def)*(e_atk - sGlobal->def));

	if (hploss >= sGlobal->hp)
	{
		sGlobal->gameLayer->showStats("you died", this->getPosition());
		Hero hero;
		}





	//显示怪物受到打击的效果
	sGlobal->gameMap->showEnemyHitEffect(targetTileCoord);

	//显示损失的生命值
	char temp[30] = { 0 };
	
	sGlobal->hp = sGlobal->hp - hploss;
	sprintf(temp, "lost hp: -%d ",hploss );

	Point temp2 = getPosition();

	sGlobal->gameLayer->showTip(temp, temp2);
	

	char stats[60] = { 0 };
	sprintf(stats, "hp:%d  atk:%d  def:%d lv1:%d lv2:%d ", sGlobal->hp , sGlobal->atk,sGlobal->def, sGlobal->lv1key, sGlobal->lv2key);
	sGlobal->gameLayer->showStats(stats, temp2);


	//将用于显示战斗动画的精灵设置为可见
	fightSprite->setVisible(true);

	//计算显示战斗动画的位置为勇士和怪物的中间点
	Point pos = Point((targetPosition.x - getPosition().x) / 2 + 16, (targetPosition.y - getPosition().y) / 2 + 16);
	fightSprite->setPosition(pos);

	//创建战斗动画
	Action* action = Sequence::create(
		sAnimationMgr->createAnimate(aFight),
		
		CallFuncN::create(CC_CALLBACK_1(Hero::onFightDone, this)),
		NULL);

	fightSprite->runAction(action);
}

//战斗结束的回调
void Hero::onFightDone(Node* pSender)
{
	//删除怪物对应的图块，表示已经被消灭
	sGlobal->gameMap->getEnemyLayer()->removeTileAt(targetTileCoord);
	isHeroFighting = false;
}

//拾取物品
void Hero::pickUpItem()
{
	int id = sGlobal->gameMap->getItemLayer()->getTileGIDAt(targetTileCoord)-275;
	

	sGlobal->hp = sGlobal->hp + getitemHp(id);
	sGlobal->atk = sGlobal->atk + getitemAtk(id);
	sGlobal->def = sGlobal->def + getitemDef(id);
	if (id == 16)
	{
		sGlobal->lv1key++;
	};
	if (id == 17)
	{
		sGlobal->lv2key++;
	}



	//将物品从地图上移除
	sGlobal->gameMap->getItemLayer()->removeTileAt(targetTileCoord);
}

//打开门
void Hero::openDoor(int gid)
{
	//如果门正在被开启，则返回
	if (isDoorOpening)
	{
		return;
	}

	//保存正在被开启的门的初始GID
	targetDoorGID = gid;

	isDoorOpening = true;
	if(gid==259 && sGlobal->lv1key >0)
	{ 
		sGlobal->lv1key--;
	//定时器更新门动画
	schedule(schedule_selector(Hero::updateOpenDoorAnimation), 0.1f);
	//数据显示更新
	Point temp2 = getPosition();
	char stats[60] = { 0 };
	sprintf(stats, "hp:%d  atk:%d  def:%d lv1:%d lv2:%d ", sGlobal->hp, sGlobal->atk, sGlobal->def, sGlobal->lv1key, sGlobal->lv2key);
	sGlobal->gameLayer->showStats(stats, temp2);

	}
	if (gid == 260 && sGlobal->lv2key > 0)
	{
		sGlobal->lv2key--;
		//定时器更新门动画
		schedule(schedule_selector(Hero::updateOpenDoorAnimation), 0.1f);
		//数据显示更新
		Point temp2 = getPosition();
		char stats[60] = { 0 };
		sprintf(stats, "hp:%d  atk:%d  def:%d lv1:%d lv2:%d ", sGlobal->hp, sGlobal->atk, sGlobal->def, sGlobal->lv1key, sGlobal->lv2key);
		sGlobal->gameLayer->showStats(stats, temp2);

	}


	
}

//更新开门动画
void Hero::updateOpenDoorAnimation(float time)
{
	//计算动画下一帧的图块ID，TileMap的图块编号方式是横向递增1，所以每列相同的位置的图块ID相差了每行图块的个数
	int nextGID = sGlobal->gameMap->getDoorLayer()->getTileGIDAt(targetTileCoord) + 4;

	//如果超过了第四帧动画，就将当前位置的图块删除，并取消定时器
	if (nextGID - targetDoorGID > 4 * 3) 
	{
		sGlobal->gameMap->getDoorLayer()->removeTileAt(targetTileCoord);
		unschedule(schedule_selector(Hero::updateOpenDoorAnimation));
		isDoorOpening = false;
	}
	else
	{
		//更新动画至下一帧
		sGlobal->gameMap->getDoorLayer()->setTileGID(nextGID, targetTileCoord);
	}
}

//与NPC交互
void Hero::actWithNPC()
{
	sGlobal->gameLayer->showTip("talking with npc", getPosition());
}

//传送点逻辑
void Hero::doTeleport(Teleport *teleport)
{
	//从传送点的属性中后去目标地图的层数
	sGlobal->currentLevel = teleport->targetMap;

	//获取勇士在新地图中的起始位置
	sGlobal->heroSpawnTileCoord = teleport->heroTileCoord;

	//开始切换游戏地图
	sGlobal->gameScene->switchMap();
}
