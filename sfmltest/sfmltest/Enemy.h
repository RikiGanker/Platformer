#pragma once
#include "Player.h"
class Enemy {

public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	bool life;
	void set(Texture &image, int x, int y);
	void update(float time);
	void Collision();
};

void Enemy::set(Texture &image, int x, int y)
{
	sprite.setTexture(image);
	rect = FloatRect(x, y, 32, 32);
	dx = 0.05;
	currentFrame = 0;
	life = true;
}

void Enemy::update(float time)
{
	rect.left += dx * time;
	Collision();
	currentFrame += time * 0.005;
	if (currentFrame > 2) currentFrame -= 2;
	sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, 32, 32));
	if (!life) sprite.setTextureRect(IntRect(0, 32, 32, 32));
	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
}

void Enemy::Collision(){
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
			if (TileMap[i][j] == 'B')
			{
				if (dx > 0)
				{
					rect.left = j * 32 - rect.width; dx *= -1;
				}
				else if (dx < 0)
				{
					rect.left = j * 32 + 32;  dx *= -1;
				}

			}
}