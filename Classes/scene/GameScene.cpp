#include "GameScene.h"

GameScene::GameScene(void)
{
	sGlobal->gameScene = this;
}

GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	//�½�һ��GameLayerʵ��
	GameLayer *gamelayer = GameLayer::create();

	//��GameLayerʵ����ӵ�������
	this->addChild(gamelayer, kGameLayer, kGameLayer);

	//�½�һ��ControlLayerʵ��
	ControlLayer *controlLayer = ControlLayer::create();

	//��ControlLayerʵ����ӵ�������
	this->addChild(controlLayer, kControlLayer, kControlLayer);

	

    


	return true;
}

//�л���Ϸ��ͼ֮ǰ
void GameScene::switchMap()
{
	//����һ�����ֲ㣬���ڵ�ͼ�л�ʱ����ʾ���뵭��Ч��
	LayerColor* fadeLayer = LayerColor::create(Color4B(0, 0, 0, 0));

	fadeLayer->setAnchorPoint(Point::ZERO);
	fadeLayer->setPosition(Point::ZERO);
	addChild(fadeLayer, kFadeLayer, kFadeLayer);

	//ִ�е��붯�������������resetGameLayer����
	Action* action = Sequence::create(
		FadeIn::create(0.5f), 
		CallFunc::create(CC_CALLBACK_0(GameScene::resetGameLayer, this)), 
		NULL);

	fadeLayer->runAction(action);
}

//�л���Ϸ��ͼ
void GameScene::resetGameLayer()
{
	//ɾ���ϵ�GameLayer
	this->removeChildByTag(kGameLayer, true);

	//�����µ�GameLayer
	GameLayer *gamelayer = GameLayer::create();
	this->addChild(gamelayer, kGameLayer, kGameLayer);

	//���ֲ�ִ�е���Ч���������󣬵���removeFadeLayer����ɾ�����ֲ�
	Action* action = Sequence::create(
		FadeOut::create(0.5f), 
		CallFunc::create(CC_CALLBACK_0(GameScene::removeFadeLayer, this)),	
		NULL);

	this->getChildByTag(kFadeLayer)->runAction(action);
}

void GameScene::removeFadeLayer()
{
	this->removeChildByTag(kFadeLayer, true);
}