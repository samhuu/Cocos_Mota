#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

//��������ͷ�ļ�
#include "MTGame.h"

//ʹ��cocos2d�����ռ�
using namespace cocos2d;

//GameScene�̳�CCScene
class GameScene : public Scene
{
public:
	GameScene(void);
	~GameScene(void);

	//��ʼ������
	virtual bool init();

	CREATE_FUNC(GameScene);

	void switchMap();
	void resetGameLayer();
	void removeFadeLayer();
};

#endif