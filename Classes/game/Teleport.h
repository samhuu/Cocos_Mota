#ifndef __TELEPORT_H__
#define __TELEPORT_H__

#include "MTGame.h"

USING_NS_CC;

class Teleport : public Ref
{
public:
	Teleport(const ValueMap &dict, int x, int y);

	~Teleport(void);

	//���͵�����λ��
	Point tileCoord;

	//���͵�Ŀ������ʿ��������
	Point heroTileCoord;

	//Ŀ���ͼ�Ĳ���
	int targetMap;

	//Ψһ��ID
	int index;

	//ͼƬ������ļ�·��
	std::string imagePath;

	Sprite *teleportSprite;
};
#endif