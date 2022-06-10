#include "MTGame.h"
#include "SimpleAudioEngine.h"
#include "audio/include/AudioEngine.h" 
using namespace experimental;
using namespace CocosDenshion;

ControlLayer::ControlLayer(void)
{
	sGlobal->controlLayer = this;

}

ControlLayer::~ControlLayer(void)
{

}

bool ControlLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	EventListenerKeyboard * listenerKeyboard = cocos2d::EventListenerKeyboard::create();
	//���¼���ע��ص�����
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(ControlLayer::onKeyPressed, this);
	//ע�����������
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);





	//�����رհ�ť
	MenuItemImage *pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(ControlLayer::menuCloseCallback));
	pCloseItem->setPosition(Point(Director::getInstance()->getWinSize().width - 20, 20));
	
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);

	//��������ť
	MenuItem *down = MenuItemFont::create("v", this, menu_selector(ControlLayer::menuCallBackMove));
	MenuItem *left = MenuItemFont::create("<", this, menu_selector(ControlLayer::menuCallBackMove) );
	MenuItem *right = MenuItemFont::create(">", this, menu_selector(ControlLayer::menuCallBackMove) );
	MenuItem *up = MenuItemFont::create("A", this, menu_selector(ControlLayer::menuCallBackMove) );
	MenuItem* playBG = MenuItemFont::create("G", this, menu_selector(ControlLayer::playMusicCallback));
	MenuItem* pauseBG = MenuItemFont::create("P", this, menu_selector(ControlLayer::pauseMusicCallback));
	MenuItem* recoverBG = MenuItemFont::create("R", this, menu_selector(ControlLayer::recoverMusicCallback));
	MenuItem* stopBG = MenuItemFont::create("S", this, menu_selector(ControlLayer::stopMusicCallback));
	MenuItem* VolumeUp = MenuItemFont::create("U", this, menu_selector(ControlLayer::MusicVolumeUp));
	MenuItem* VolumeDown = MenuItemFont::create("D", this, menu_selector(ControlLayer::MusicVolumeDown));
	Menu* menu = Menu::create(playBG , pauseBG, recoverBG, stopBG, VolumeUp, VolumeDown,NULL);
	
	//Ϊ�˷�����ң���ÿ��menuItem����tag
	down->setTag(kDown);
	left->setTag(kLeft);
	right->setTag(kRight);
	up->setTag(kUp);

	Size visibleSize = Director::getInstance()->getWinSize();
	

	

	
	//�˵�����50ˮƽ����
	menu->alignItemsHorizontallyWithPadding(20);
	this->addChild(menu);
	return true;
}

void ControlLayer::menuCloseCallback(cocos2d::Ref* pSender)
{
    Director::sharedDirector()->end();
}
void ControlLayer::playMusicCallback(CCObject* pSender)
{
	
	 bgid= AudioEngine::play2d("02 - Outer Wilds.mp3", 1, 1);
	{
		//������Ч
		SimpleAudioEngine::sharedEngine()->playEffect("effect1.wav");
	}
}

void ControlLayer::pauseMusicCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	{
		//������Ч
		SimpleAudioEngine::sharedEngine()->playEffect("effect1.wav");
	}
}
void ControlLayer::recoverMusicCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	{
		//������Ч
		SimpleAudioEngine::sharedEngine()->playEffect("effect1.wav");
	}
}
void ControlLayer::stopMusicCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	{
		//������Ч
		SimpleAudioEngine::sharedEngine()->playEffect("effect1.wav");
	}
}

void ControlLayer::MusicVolumeUp(CCObject* pSender)
{
	float temp = AudioEngine::getVolume(bgid);
	{
		//�����Ӵ�
		AudioEngine::setVolume(bgid,temp+0.1);
	
	}
}
void ControlLayer::MusicVolumeDown(CCObject* pSender)
{
	float temp = AudioEngine::getVolume(bgid);

	{		
		//������С

		AudioEngine::setVolume(bgid, temp - 0.1);
	}
}



void ControlLayer::menuCallBackMove(cocos2d::Ref* pSender)
{
    Node *node = (Node *) pSender;

	//��ť��tag������Ҫ���ߵķ���
	int targetDirection = node->getTag();

	sGlobal->hero->move((HeroDirection) targetDirection);
}

void ControlLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Ref* pSende)
{

	//�ж� keyCode ö�������������µİ���
	switch (keyCode) {
		//��ɫ1���ĸ������ƶ�
	case EventKeyboard::KeyCode::KEY_W: {
		sGlobal->hero->move((HeroDirection)kUp);
		break;
	}
	case EventKeyboard::KeyCode::KEY_S: {

		sGlobal->hero->move((HeroDirection)kDown);
		break;
	}
	case EventKeyboard::KeyCode::KEY_D: {

		sGlobal->hero->move((HeroDirection)kRight);
		break;
	}
	case EventKeyboard::KeyCode::KEY_A: {

		sGlobal->hero->move((HeroDirection)kLeft);
		break;
	}
								
	}
}

