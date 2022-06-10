#include "AnimationManager.h"

DECLARE_SINGLETON_MEMBER(AnimationManager);

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
	//Director���Լ����AnimationCache
	//AnimationCache::purgeSharedAnimationCache();
}

bool AnimationManager::initAnimationMap()
{
	char temp[20];
	
	//������ʿ�����ߵĶ���
	sprintf(temp, "%d", aDown);
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(kDown), temp);
	
	//������ʿ�����ߵĶ���
	sprintf(temp, "%d", aRight);
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(kRight), temp);
	
	//������ʿ�����ߵĶ���
	sprintf(temp, "%d", aLeft);
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(kLeft), temp);

	//������ʿ�����ߵĶ���
	sprintf(temp, "%d", aUp);
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(kUp), temp);
	
	//����ս������
	sprintf(temp, "%d", aFight);
	AnimationCache::getInstance()->addAnimation(createFightAnimation(), temp);
	
	//����NPC����
	AnimationCache::getInstance()->addAnimation(createNPCAnimation(), "npc0");

	return true;
}

Animation* AnimationManager::createHeroMovingAnimationByDirection(HeroDirection direction)
{
	Texture2D *heroTexture = TextureCache::getInstance()->addImage("hero.png");
	
	//�ڶ���������ʾ��ʾ�����x, y, width, height������direction��ȷ����ʾ��y����
	SpriteFrame *frame0 = SpriteFrame::createWithTexture(heroTexture, Rect(32*0, 32*direction, 32, 32));
	SpriteFrame *frame1 = SpriteFrame::createWithTexture(heroTexture, Rect(32*1, 32*direction, 32, 32));
	SpriteFrame *frame2 = SpriteFrame::createWithTexture(heroTexture, Rect(32*2, 32*direction, 32, 32));
	SpriteFrame *frame3 = SpriteFrame::createWithTexture(heroTexture, Rect(32*3, 32*direction, 32, 32));
	
	Vector<SpriteFrame*> animFrames;

	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);
	animFrames.pushBack(frame2);
	animFrames.pushBack(frame3);

	//0.05f��ʾÿ֡������ļ��
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);

	return animation;
}

//����ս������ģ��
Animation* AnimationManager::createFightAnimation()
{
	Texture2D *texture = TextureCache::getInstance()->addImage("sword.png");

	//����ÿ֡�����
	int fightAnim[] = 
	{
		4,6,8,10,13,15,17,19,20,0
	};
	
	Vector<SpriteFrame*> animFrames;
	
	int x, y;
	for (int i = 0; i < 10; i++) 
	{
		//����ÿ֡�����������е�ƫ����
		x = fightAnim[i] % 5 - 1;
		y = fightAnim[i] / 5;
		
		SpriteFrame *frame = SpriteFrame::createWithTexture(texture, Rect(192*x, 192*y, 192, 192));
		
		//��17��19֡��y��������-8��ƫ��
		if (fightAnim[i] == 17 || fightAnim[i] == 19)
		{
			frame->setOffsetInPixels(Point(0, -8));
		}
		
		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	return animation;
}

Animation* AnimationManager::createNPCAnimation()
{
	Texture2D *heroTexture = TextureCache::getInstance()->addImage("npc.png");
	
	//�ڶ���������ʾ��ʾ�����x, y, width, height������direction��ȷ����ʾ��y����
	SpriteFrame *frame0 = SpriteFrame::createWithTexture(heroTexture, Rect(32*0, 0, 32, 32));
	SpriteFrame *frame1 = SpriteFrame::createWithTexture(heroTexture, Rect(32*1, 0, 32, 32));
	SpriteFrame *frame2 = SpriteFrame::createWithTexture(heroTexture, Rect(32*2, 0, 32, 32));
	SpriteFrame *frame3 = SpriteFrame::createWithTexture(heroTexture, Rect(32*3, 0, 32, 32));
	
	Vector<SpriteFrame*> animFrames;

	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);
	animFrames.pushBack(frame2);
	animFrames.pushBack(frame3);
	
	//0.05f��ʾÿ֡������ļ��
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);

	return animation;
}

//��ȡָ������ģ��
Animation* AnimationManager::getAnimation(int key)
{
	char temp[20];
	sprintf(temp, "%d", key);
	return AnimationCache::getInstance()->animationByName(temp);
}

//��ȡһ��ָ������ģ���ʵ��
Animate* AnimationManager::createAnimate(int key)
{
	//��ȡָ������ģ��
	Animation* anim = getAnimation(key);

	if (anim == NULL)
	{
		return NULL;
	}

	//���ݶ���ģ������һ������ʵ��
	return Animate::create(anim);
}

//��ȡһ��ָ������ģ���ʵ��
Animate* AnimationManager::createAnimate(const char* key)
{
	//��ȡָ������ģ��
	Animation* anim = AnimationCache::getInstance()->animationByName(key);

	if (anim == NULL)
	{
		return NULL;
	}

	//���ݶ���ģ������һ������ʵ��
	return Animate::create(anim);
}
