#pragma once
#include "Enemy.h"

class Game {
public:
	void RunGame();
};

void Game::RunGame(){
	RenderWindow window(VideoMode(1280, 720), "Glad's Adventure!");

	Texture z;
	z.loadFromFile("BULIZNIK.png");
	Sprite ti(z);

	Texture t;
	t.loadFromFile("Glad.png");         //Загрузка картинки в тектуру

	Texture q1;
	q1.loadFromFile("stay.png");

	Texture en;
	en.loadFromFile("enemy.png");

	float currentFrame = 0;  //номер текущего кадра

	Player p(t);

	Enemy enemy;
	enemy.set(en, 22 * 32, 22 * 32);          //нач координаты 

	Texture menu_texture1, menu_texture2, menu_texture3, about_texture;
	menu_texture1.loadFromFile("111.png");
	menu_texture2.loadFromFile("222.png");
	menu_texture3.loadFromFile("333.png");
	about_texture.loadFromFile("about.png");
	Sprite menu1(menu_texture1), menu2(menu_texture2), menu3(menu_texture3), about(about_texture);
	bool Menu = 1;
	int MenuNum = 0;
	menu1.setPosition(540, 285);
	menu2.setPosition(540, 345);
	menu3.setPosition(540, 405);

	while (Menu)
	{
		menu1.setColor(Color::Red);
		menu2.setColor(Color::Red);
		menu3.setColor(Color::Red);
		MenuNum = 0;
		window.clear(Color::Green);

		if (IntRect(540, 285, 169, 39).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Yellow); MenuNum = 1; }
		if (IntRect(540, 345, 210, 34).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Yellow); MenuNum = 2; }
		if (IntRect(540, 405, 110, 41).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Yellow); MenuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (MenuNum == 1) Menu = false;
			if (MenuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (MenuNum == 3) { window.close(); Menu = false; }

		}

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}


	SoundBuffer buffer;
	buffer.loadFromFile("Jump.ogg");
	Sound sound(buffer);


	Music music;
	music.openFromFile("theme.ogg");
	music.play();

	
	p.dx = 0.1;
	/*Sprite s;
	s.setTexture(t);         //Загрузка теккстуры в спрайт и расположение его
	s.setTextureRect(IntRect(0,0,64,90));
	s.setPosition(50,100);*/

	Clock clock;

	RectangleShape rectangle(Vector2f(32, 32));

	while (window.isOpen())

	{
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return; }//если эскейп, то выходим из игры
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;                    //скорость анимации
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{	//s.move(-0.1*time,0);
			{p.dx = -0.1; }
			/*	currentFrame += 0.005*time;
		  if (currentFrame > 4) currentFrame -=4 ;                                                               //смена кадров
		  s.setTextureRect(IntRect(64*int(currentFrame)+64,0,-64,90));*/
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))                                                              //Движение картинки
		{	//s.move(0.1*time,0);	
			{p.dx = 0.1; }
			/*currentFrame += 0.005*time;
	  if (currentFrame > 4) currentFrame -=4 ;
	  s.setTextureRect(IntRect(64*int(currentFrame),0,64,90));*/

		}


		if (Keyboard::isKeyPressed(Keyboard::Up))
		{	//s.move(0,0.1);	
			if (p.onGround) { p.dy = -0.4; p.onGround = false; sound.play(); }             //при прижке даем ускорение
		}

		p.update(time);
		enemy.update(time);

		if (p.rect.intersects(enemy.rect))
		{
			if (enemy.life) {
				if (p.dy > 0) { enemy.dx = 0; p.dy = -0.2; enemy.life = false; }
				else /*window.close();*/p.sprite.setColor(Color::Red);
			}
		}

		window.clear(Color::White);

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				//  if (TileMap[i][j]=='B') rectangle.setFillColor(Color::Black);
				if (TileMap[i][j] == 'B') ti.setTextureRect(IntRect(0, 0, 32, 32));
				//if (TileMap[i][j]=='0')  rectangle.setFillColor(Color::Green);                          //каждому элементу в матрице карты задается элемент

				if (TileMap[i][j] == ' ') continue;

				if (p.rect.left > 640)   offsetX = p.rect.left - 640; //чтоб перс был в середине экрана отнимаем половину ширины и высоты экрана

				if (p.rect.left > 1600) offsetX = 960;
				if (p.rect.top > 360)  offsetY = p.rect.top - 360;

				if (p.rect.top > 392) offsetY = 32;

				rectangle.setPosition(j * 32, i * 32);

				ti.setPosition(j * 32 - offsetX, i * 32 - offsetY);
				//window.draw(rectangle);
				window.draw(ti);

			}

		window.draw(p.sprite);
		window.draw(enemy.sprite);
		window.display();
	}
}

