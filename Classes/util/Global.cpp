#include "Global.h"

DECLARE_SINGLETON_MEMBER(Global);

Global::Global(void)
{
	gameScene = NULL;

	gameLayer = NULL;

	controlLayer = NULL;

	gameMap = NULL;

	hero = NULL;



	hp = 5000;
	atk = 500;
	def = 0; 
	lv1key=1;

	lv2key=1;

	//����Ϸ����ǰ��ͼ����Ϊ0
	currentLevel = 0;

	//��ʿ����λ��
	heroSpawnTileCoord = Point(1, 11);

	
}

Global::~Global(void)
{

}