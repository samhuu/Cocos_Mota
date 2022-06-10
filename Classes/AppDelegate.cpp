#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "MTGame.h"

using namespace cocos2d;

AppDelegate::AppDelegate()
{
	
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
	//释放动画管理器
	sAnimationMgr->release();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Brave C++ version");
		director->setOpenGLView(glview);
	}

	glview->setDesignResolutionSize(480, 320, ResolutionPolicy::SHOW_ALL); 

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);
	
	//初始化动画管理器
	sAnimationMgr->initAnimationMap();
   
	//创建游戏主界面
    Scene *pScene = GameScene::create();
	
	//让director运行场景
    director->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->pause();

    //SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->resume();

    //SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
