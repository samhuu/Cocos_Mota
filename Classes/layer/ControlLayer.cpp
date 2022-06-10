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
	//绑定事件，注册回调函数
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(ControlLayer::onKeyPressed, this);
	//注册这个监听器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);





	//创建关闭按钮
	MenuItemImage *pCloseItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(ControlLayer::menuCloseCallback));
	pCloseItem->setPosition(Point(Director::getInstance()->getWinSize().width - 20, 20));
	
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);

	//创建方向按钮
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
	
	//为了方便查找，给每个menuItem设置tag
	down->setTag(kDown);
	left->setTag(kLeft);
	right->setTag(kRight);
	up->setTag(kUp);

	Size visibleSize = Director::getInstance()->getWinSize();
	

	

	
	//菜单项按间距50水平排列
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
		//播放音效
		SimpleAudioEngine::sharedEngine()->playEffect("effect1.wav");
	}
}

void ControlLayer::pauseMusicCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	{
		//播放音效
		SimpleAudioEngine::sharedEngine()->playEffect("effect1.wav");
	}
}
void ControlLayer::recoverMusicCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	{
		//播放音效
		SimpleAudioEngine::sharedEngine()->playEffect("effect1.wav");
	}
}
void ControlLayer::stopMusicCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	{
		//播放音效
		SimpleAudioEngine::sharedEngine()->playEffect("effect1.wav");
	}
}

void ControlLayer::MusicVolumeUp(CCObject* pSender)
{
	float temp = AudioEngine::getVolume(bgid);
	{
		//音量加大
		AudioEngine::setVolume(bgid,temp+0.1);
	
	}
}
void ControlLayer::MusicVolumeDown(CCObject* pSender)
{
	float temp = AudioEngine::getVolume(bgid);

	{		
		//音量减小

		AudioEngine::setVolume(bgid, temp - 0.1);
	}
}



void ControlLayer::menuCallBackMove(cocos2d::Ref* pSender)
{
    Node *node = (Node *) pSender;

	//按钮的tag就是需要行走的方向
	int targetDirection = node->getTag();

	sGlobal->hero->move((HeroDirection) targetDirection);
}

void ControlLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Ref* pSende)
{

	//判断 keyCode 枚举来区分所按下的按键
	switch (keyCode) {
		//角色1的四个方向移动
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

