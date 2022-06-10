#ifndef __CONTROLLAYER_H__
#define __CONTROLLAYER_H__

#include "MTGame.h"

USING_NS_CC;

class ControlLayer : public Layer
{
public:
	ControlLayer(void);
	~ControlLayer(void);

	//node��������ô˺���
	virtual bool init();

	CREATE_FUNC(ControlLayer);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Ref* pSender);

	//����ť����¼��Ļص�
	void menuCallBackMove(cocos2d::Ref* pSender);

	//�رհ�ť����¼��Ļص�
	void menuCloseCallback(cocos2d::Ref* pSender);

	void playMusicCallback(CCObject* pSender);		//���ű�������
	void pauseMusicCallback(CCObject* pSender);		//��ͣ��������
	void recoverMusicCallback(CCObject* pSender);	//�ָ���������
	void stopMusicCallback(CCObject* pSender);		//ֹͣ��������
	void MusicVolumeUp(CCObject* pSender);	
	void MusicVolumeDown(CCObject* pSender);

	int bgid;

};

#endif
