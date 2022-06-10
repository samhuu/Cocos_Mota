#include "GameMap.h"

GameMap::GameMap(void)
{
	sGlobal->gameMap = this;
}

GameMap::~GameMap(void)
{
	this->unscheduleAllSelectors();
}

//��̬��������������GameMapʵ��
GameMap* GameMap::gameMapWithTMXFile(const char *tmxFile)
{
	//newһ������
	GameMap *pRet = new GameMap();

	//����init����
	if (pRet->initWithTMXFile(tmxFile))
	{
		//���ö����init����
		pRet->extraInit();

		//��ʵ������autorelease�أ�ͳһ��������ƶ������������
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

//TliedMap����ĳ�ʼ������
void GameMap::extraInit()
{
	//��������ͼ����������
	enableAnitiAliasForEachLayer();

	//��ʼ���������
	floorLayer = this->getLayer("floor");
	wallLayer = this->getLayer("wall");
	itemLayer = this->getLayer("item");
	doorLayer = this->getLayer("door");

	initEnemy();
	initObject();
}

void GameMap::initEnemy()
{
	//��ȡ�����
	enemyLayer = this->getLayer("enemy");

	Size s = enemyLayer->getLayerSize();

	//����enemy�㣬�����ڵĹ��ﱣ�浽������
	for (int x = 0; x < s.width; x++) 
	{
		for (int y = 0; y < s.height; y++) 
		{
			int gid = enemyLayer->getTileGIDAt(Point(x, y));
			if (gid != 0) 
			{
				Enemy* enemy = new Enemy();

				//�����������
				enemy->position = Point(x, y);

				//���������ʼ��ͼ��ID
				enemy->startGID = gid;

				//��ӹ����������
				enemyArray.pushBack(enemy);
			}
		}
	}

	//���ڸ��µ��˶���
	schedule(schedule_selector(GameMap::updateEnemyAnimation), 0.2f);
}

//���¹����ͼ��
void GameMap::updateEnemyAnimation(float time)
{	
	Vector<Enemy*>::iterator  iter;
	Enemy *enemy, *needRemove = NULL;

	//�����������й�����������
	for (iter = enemyArray.begin(); iter != enemyArray.end(); ++iter) 
	{
		enemy = *iter;
		if (enemy != NULL) 
		{
			//��ȡ���ﵱǰ��ͼ��ID
			int gid = enemyLayer->getTileGIDAt(enemy->position);

			//������ﱻɾ���ˣ���Ҫ������enemyArray��Ҳɾ��
			if (gid == 0)
			{
				needRemove = enemy;
				continue;
			}
			gid++;

			//�����һ��ͼ��ID ��ʼͼ��ID
			if (gid - enemy->startGID > 3) 
			{
				gid = enemy->startGID;
			}

			//�����������µ�ͼ��
			enemyLayer->setTileGID(gid, enemy->position);
		}
	}

	//ɾ��������Ĺ���
	if (needRemove != NULL)
	{
		enemyArray.eraseObject(needRemove);
	}
}

//��ʼ�������
void GameMap::initObject()
{
	//��ȡ�����
	TMXObjectGroup* group = this->objectGroupNamed("object");

	//��ȡ������ڵ����ж���
	const ValueVector &objects = group->getObjects();

	//�������ж���
	for(ValueVector::const_iterator it = objects.begin(); 
		it != objects.end(); it++) 
	{
		const ValueMap &dict = (*it).asValueMap();

		std::string key = "x";

		//��ȡx����
		int x = dict.at(key).asInt();
		key = "y";

		//��ȡy����
		int y = dict.at(key).asInt();
		Point tileCoord = tileCoordForPosition(Point(x, y));

		//����ΨһID
		int index = tileCoord.x + tileCoord.y * this->getMapSize().width;
		key = "type";

		//��ȡ�������
		std::string type = dict.at(key).asString();

		//��������Ǵ�����
		if (type == "teleport")
		{
			Teleport *teleport = new Teleport(dict, x, y);
			teleportDict.insert(index, teleport);
		}
		//���������NPC����
		else if (type == "npc")
		{
			NPC *npc = new NPC(dict, x, y);
			npcDict.insert(index, npc);
		}
	}
}

void GameMap::enableAnitiAliasForEachLayer()
{
	const Vector<Node *>&  childrenArray = this->getChildren();

	//����Tilemap������ͼ��
	for (size_t i = 0, count = childrenArray.size(); i < count; i++)
	{
		SpriteBatchNode* child = (SpriteBatchNode*)childrenArray.at(i);

		if (!child)
		{
			break;
		}

		//��ͼ��������������
		child->getTexture()->setAntiAliasTexParameters();
	}
}

//��cocos2d-x����ת��ΪTilemap����
Point GameMap::tileCoordForPosition(Point position)
{
	int x = position.x / this->getTileSize().width;
	int y = (((this->getMapSize().height - 1) * this->getTileSize().height) - position.y) / this->getTileSize().height;
	return Point(x, y);
}

//��Tilemap����ת��Ϊcocos2d-x����
Point GameMap::positionForTileCoord(Point tileCoord)
{
	Point pos = Point((tileCoord.x * this->getTileSize().width), ((this->getMapSize().height - tileCoord.y - 1) * this->getTileSize().height));
	return pos;
}

//���¹���ս��ʱ����ɫ״̬
void GameMap::updateEnemyHitEffect(float time)
{
	//���´�����һ
	fightCount++;

	if (fightCount % 2 == 1)
	{
		//���ù���sprite��ɫΪ��ɫ
		fightingEnemy->setColor(Color3B::WHITE);
	}
	else
	{
		//���ù���sprite��ɫΪ��ɫ
		fightingEnemy->setColor(Color3B::RED);
	}

	//�л�5�κ�ȡ����ʱ��
	if (fightCount == 5)
	{
		unschedule(schedule_selector(GameMap::updateEnemyHitEffect));
	}
}

//��ʾ����������
void GameMap::showEnemyHitEffect(Point tileCoord)
{
	//���´���
	fightCount = 0;

	//��ȡ�����Ӧ��CCSprite����
	fightingEnemy = enemyLayer->tileAt(tileCoord);

	if (fightingEnemy == NULL)
	{
		return;
	}

	//���ù���sprite��ɫΪ��ɫ
	fightingEnemy->setColor(Color3B::RED);

	//������ʱ�����´��״̬
	this->schedule(schedule_selector(GameMap::updateEnemyHitEffect), 0.18f);
}
