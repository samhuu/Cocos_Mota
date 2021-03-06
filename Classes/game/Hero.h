#ifndef __HERO_H__
#define __HERO_H__

#include "MTGame.h"
#include "Enemy.h"

USING_NS_CC;

class Teleport;

//勇士类继承自CCNode
class Hero : public Node
{
public:
	Hero(void);
	~Hero(void);

	//初始化方法
	bool init();

	CREATE_FUNC(Hero);

	//让勇士向指定方向移动一格
	void move(HeroDirection direction);

	//设置勇士朝向
	void setFaceDirection(HeroDirection direction);

	//开始战斗逻辑
	void fight();

	//标识勇士是否在移动状态
	bool isHeroMoving;

	//标识勇士是否在战斗状态
	bool isHeroFighting;

	//标识勇士是否在开门状态
	bool isDoorOpening;

	//拾取物品
	void pickUpItem();

	//开门
	void openDoor(int targetDoorGID);

	//对NPC交互
	void actWithNPC();

	//传送
	void doTeleport(Teleport *teleport);

	//怪物编号
	int getenemyID(int targetEnemyGID);
	//血量
	int getenemyHp(int targetEnemyGID);
	//攻击
	int getenemyAttack(int targetEnemyGID);
	//防御
	int getenemyDefense(int targetEnemyGID);

	int getitemHp(int targetEnemyGID);
	int getitemAtk(int targetEnemyGID);
	int getitemDef(int targetEnemyGID);



	


protected:

	

	

	//用于显示勇士形象的精灵
	Sprite *heroSprite;
	
	//临时保存目标的Tilemap坐标
	Point targetTileCoord;
	
	//临时保存目标的cocos2d-x坐标
	Point targetPosition;
	
	//临时保存门起始的图块ID
	int targetDoorGID;
	
	//显示战斗动画的精灵
	Sprite *fightSprite;
	
	//战斗完成后的回调函数
	void onFightDone(Node* pTarget);
	
	//碰撞检测方法
	CollisionType checkCollision(Point heroPosition);
	
	//移动完成后的回调函数
	void onMoveDone(Node* pTarget, void* data);
	
	//更新开门动画
	void updateOpenDoorAnimation(float time);
};

#endif