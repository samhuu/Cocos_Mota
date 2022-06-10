#include "NPC.h"

NPC::NPC(const ValueMap &dict, int x, int y)
{
	//��ȡ����
	std::string key = "name";
	npcId = dict.at(key).asInt();

	//��ȡ����
	key = "type";
	type = dict.at(key).asString();

	//��ȡimage��
	key = "image";
	imagePath = dict.at(key).asString();

	//��ȡrectX��rectY
	key = "rectX";
	int x1 = dict.at(key).asInt();

	key = "rectY";
	int y1 = dict.at(key).asInt();

	rect = Rect(x1, y1, 32, 32);

	//positionΪcocos2d-x���꣬tileCoordΪTileMap����
	Point position = Point(x, y);
	tileCoord = sGlobal->gameMap->tileCoordForPosition(position);

	//����������ʾnpc�ľ���
	npcSprite = Sprite::create(imagePath, rect);
	npcSprite->setAnchorPoint(Point::ZERO);
	npcSprite->setPosition(position);

	sGlobal->gameLayer->addChild(npcSprite, kZNPC);

	//�Ӷ����������и���npcId��ȡ��������ʼ���ò���
	Animate* animation = sAnimationMgr->createAnimate(npcId);
	if (animation != NULL)
	{
		ActionInterval* action = RepeatForever::create(animation);
		npcSprite->runAction(action);
	}
}

NPC::~NPC(void)
{
}
