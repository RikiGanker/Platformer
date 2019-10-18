#pragma once
#include "Map.h"
class Player {

public:

	float dx, dy;                   //скорость
	FloatRect rect;                //вместо координат - все в одной переменной
	bool onGround;                           //мы на земле?
	Sprite sprite;              //сюда картинка загружаться будет
	float currentFrame;            //текущий кадр для анимации

	Player(Texture &image);
	~Player() = default; 

	void update(float time);
	void Collision(int dir);
};

Player::Player(Texture &image){
	sprite.setTexture(image);              //загружаем картинку
	rect = FloatRect(35, 35, 64, 90);       //первоначальные координаты

	dx = dy = 0;
	currentFrame = 0;
}

void Player::update(float time){
	rect.left += dx * time;                     //координата х перемещаем ее на dx*time
	Collision(0);
	if (!onGround) dy = dy + 0.0005*time;              //если не на земле то падаем с ускорением... 0.0005 ускорение
	rect.top += dy * time;                           //прибавляем это к скорости (рект топ это игрик)
	onGround = false;
	Collision(1);
	//if(rect.top > ground) { rect.top = ground; dy = 0; onGround = true;}
	//если по игрику на некотором расстоянии внизу то считаем что он на земле
	currentFrame += 0.005*time;
	if (currentFrame > 4) currentFrame -= 4;
	if (dx > 0)  sprite.setTextureRect(IntRect(64 * int(currentFrame), 0, 64, 90));               //анимация передвижения вправо
	if (dx < 0)  sprite.setTextureRect(IntRect(64 * int(currentFrame) + 64, 0, -64, 90));                //влево

	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);       //выводим спрайт в позицию икс игрик

	dx = 0;
}

void Player::Collision(int dir){
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
		{                                                                                        //столкновение 
			if (TileMap[i][j] == 'B')
			{
				if ((dx > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
				if ((dx < 0) && (dir == 0)) rect.left = j * 32 + 32;
				if ((dy > 0) && (dir == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
				if ((dy < 0) && (dir == 1)) { rect.top = i * 32 + 32;   dy = 0; }
			}
			if (TileMap[i][j] == '0')
			{
				TileMap[i][j] = ' ';
			}
		}
}