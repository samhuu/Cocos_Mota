#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "MTGame.h"

USING_NS_CC;

class NPC;
class Teleport;

//�̳���CCTMXTIledMap
class GameMap : public TMXTiledMap
{
	//ֻ����������ȡ��ͼ��CC_PROPERTY_READONLY
	CC_SYNTHESIZE(TMXLayer*, floorLayer, FloorLayer);
	CC_SYNTHESIZE(TMXLayer*, wallLayer, WallLayer);
	CC_SYNTHESIZE(TMXLayer*, enemyLayer, EnemyLayer);
	CC_SYNTHESIZE(TMXLayer*, itemLayer, ItemLayer);
	CC_SYNTHESIZE(TMXLayer*, doorLayer, DoorLayer);

public:
	GameMap(void);
	~GameMap(void);

	//��̬��������������GameMapʵ��
	static GameMap* gameMapWithTMXFile(const char *tmxFile);

	//TiledMap��cocos2d-x����ϵ�໥ת���ķ���
	Point tileCoordForPosition(Point position);
	Point positionForTileCoord(Point tileCoord);
	void showEnemyHitEffect(Point tileCoord);

	//��ŵ�ͼ�Ϲ���������Լ�npc 
	Vector<Enemy*> enemyArray;
	Map<int, Teleport*> teleportDict;
	Map<int, NPC*> npcDict;

protected:
	//TiledMap����ĳ�ʼ������
	void extraInit();

	//��ʼ����������
	void initEnemy();

	//��ʼ������
	void initObject();

	//������ͼ����������
	void enableAnitiAliasForEachLayer();

	//���¹��ﶯ��
	void updateEnemyAnimation(float time);

	//��ʱ����ս��ʱ�Ĺ���
	Sprite* fightingEnemy;

	//��ʱ����������
	int fightCount;

	//���¹���ս��ʱ����ɫ״̬
	void updateEnemyHitEffect(float time);
};

#endif