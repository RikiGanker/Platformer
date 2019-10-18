#pragma once
#include "Map.h"
class Player {

public:

	float dx, dy;                   //��������
	FloatRect rect;                //������ ��������� - ��� � ����� ����������
	bool onGround;                           //�� �� �����?
	Sprite sprite;              //���� �������� ����������� �����
	float currentFrame;            //������� ���� ��� ��������

	Player(Texture &image);
	~Player() = default; 

	void update(float time);
	void Collision(int dir);
};

Player::Player(Texture &image){
	sprite.setTexture(image);              //��������� ��������
	rect = FloatRect(35, 35, 64, 90);       //�������������� ����������

	dx = dy = 0;
	currentFrame = 0;
}

void Player::update(float time){
	rect.left += dx * time;                     //���������� � ���������� �� �� dx*time
	Collision(0);
	if (!onGround) dy = dy + 0.0005*time;              //���� �� �� ����� �� ������ � ����������... 0.0005 ���������
	rect.top += dy * time;                           //���������� ��� � �������� (���� ��� ��� �����)
	onGround = false;
	Collision(1);
	//if(rect.top > ground) { rect.top = ground; dy = 0; onGround = true;}
	//���� �� ������ �� ��������� ���������� ����� �� ������� ��� �� �� �����
	currentFrame += 0.005*time;
	if (currentFrame > 4) currentFrame -= 4;
	if (dx > 0)  sprite.setTextureRect(IntRect(64 * int(currentFrame), 0, 64, 90));               //�������� ������������ ������
	if (dx < 0)  sprite.setTextureRect(IntRect(64 * int(currentFrame) + 64, 0, -64, 90));                //�����

	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);       //������� ������ � ������� ��� �����

	dx = 0;
}

void Player::Collision(int dir){
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
		{                                                                                        //������������ 
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