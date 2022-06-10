#ifndef __CONTROLLAYER_H__
#define __CONTROLLAYER_H__

#include "MTGame.h"

USING_NS_CC;

class ControlLayer : public Layer
{
public:
	ControlLayer(void);
	~ControlLayer(void);

	//node方法会调用此函数
	virtual bool init();

	CREATE_FUNC(ControlLayer);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Ref* pSender);

	//方向按钮点击事件的回调
	void menuCallBackMove(cocos2d::Ref* pSender);

	//关闭按钮点击事件的回调
	void menuCloseCallback(cocos2d::Ref* pSender);

	void playMusicCallback(CCObject* pSender);		//播放背景音乐
	void pauseMusicCallback(CCObject* pSender);		//暂停背景音乐
	void recoverMusicCallback(CCObject* pSender);	//恢复背景音乐
	void stopMusicCallback(CCObject* pSender);		//停止背景音乐
	void MusicVolumeUp(CCObject* pSender);	
	void MusicVolumeDown(CCObject* pSender);

	int bgid;

};

#endif
