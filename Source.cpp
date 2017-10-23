#include "Header.h"

using namespace Program;

bool	isCollide(Entity *a, Entity *b)
{
	return (b->x - a->x)*(b->x - a->x) +
		(b->y - a->y)*(b->y - a->y)<
		(a->R + b->R)*(a->R + b->R);
}

bool	title(RenderWindow *app, Event *event)
{
	Texture	title;
	title.loadFromFile("images/title.png");
	Sprite	s_title(title);
	app->clear();
	Font font_text;
	font_text.loadFromFile("images/8bit.ttf");
	Text text1("", font_text, 200), text2("", font_text, 200);
	text1.setString("BEGIN");
	text1.setPosition(460, 200);
	text2.setString("END");
	text2.setPosition(554, 340);
	POINT *CurPos = new POINT;
	while (true)
	{
		app->pollEvent(*event);
		GetCursorPos(CurPos);
		text1.setFillColor(Color(255, 255, 255, 255));
		text2.setFillColor(Color(255, 255, 255, 255));
		app->draw(s_title);
		if (CurPos->x > 458 && CurPos->x < 913
			&& CurPos->y > 321 && CurPos->y < 400)
			text1.setFillColor(Color(0, 0, 0, 255));
		if (CurPos->x > 552 && CurPos->x < 819
			&& CurPos->y > 461 && CurPos->y < 540)
			text2.setFillColor(Color(0, 0, 0, 255));
		if (event->type == Event::MouseButtonReleased)
			if (event->key.code == Mouse::Left)
				if (CurPos->x > 458 && CurPos->x < 913
					&& CurPos->y > 321 && CurPos->y < 400)
					return (1);
		if (event->type == Event::MouseButtonReleased)
			if (event->mouseButton.button == Mouse::Left)
				if (event->mouseWheel.x > 552 && event->mouseWheel.x < 819
					&& event->mouseWheel.y > 461 && event->mouseWheel.y < 540)
					return (0);
	
		app->draw(text1);
		app->draw(text2);
		app->display();
	}
	delete CurPos;
}

int main()
{
	int		destination = 0;
	int		p_life = 3;
	int		p_rocket = 3;
	int		is_shield = 0;
	int		gameOver = -1;
	int		f = 1;
	int		score = 0;
	String	str_life = "3";
	String	str_rocket = "3";

	RenderWindow app(VideoMode(W, H), "Coursework!", Style::None);
	app.setFramerateLimit(60);
	
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;
	t1.loadFromFile("images/spaceship.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/explosions/type_C.png");
	t4.loadFromFile("images/ships/1.png");
	t5.loadFromFile("images/fire_blue.png");
	t6.loadFromFile("images/ships/2.png");
	t7.loadFromFile("images/explosions/type_B.png");
	t8.loadFromFile("images/ships/3.png");
	t9.loadFromFile("images/ships/4.png");
	t10.loadFromFile("images/fire_red.png");
	t11.loadFromFile("images/heart.png");
	t12.loadFromFile("images/explosions/type_A.png");
	t13.loadFromFile("images/shield.png");
	t14.loadFromFile("images/game_over.png");

	t1.setSmooth(true);
	t2.setSmooth(true);

	Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5f);
	Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8f);
	Animation rBullet(t10, 0, 0, 32, 64, 16, 0.8f);
	Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
	Animation sPlayer_go(t1, 40, 38, 40, 44	, 1, 0);
	Animation sPlayer_left(t1, 0, 0, 38, 40, 1, 0);
	Animation sPlayer_right	(t1, 78, 0, 38, 40, 1, 0);
	Animation sPlayer_left_go(t1, 0, 38, 38, 44, 1, 0);
	Animation sPlayer_right_go(t1, 78, 38, 38, 44, 1, 0);
	Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5f);
	Animation sExplosion_bullet(t12, 0, 0, 50, 50, 20, 0.5f);
	Animation enemyShip1(t4, 0, 0, 100, 100, 1, 0);
	Animation enemyShip2(t6, 0, 0, 100, 100, 1, 0);
	Animation enemyShip3(t8, 0, 0, 100, 100, 1, 0);
	Animation enemyShip4(t9, 0, 0, 100, 100, 1, 0);
	Animation rockets(t1, 56, 130, 4, 14, 2, 0.2f);
	list<Entity*> entities;
	srand(time(NULL));
	POINT *CurPos = new POINT;
	Sprite	shield(t13);
	Sprite	end(t14);
	Font font;
	end.setPosition(481, 362);
	shield.setOrigin(70, 70);
	font.loadFromFile("images/8bit.ttf");
	Text text1("", font, 35), text2("", font, 35), text3("", font, 70);
	text1.setPosition(1310, 720);
	text2.setPosition(1310, 690);

	Sprite	background(t2);
	Sprite	heart(t11);
	Sprite	rock(t1);
	rock.setPosition(1270, 725);
	rock.setTextureRect(IntRect(56, 130, 4, 8));
	rock.setScale(Vector2f(3.7f, 3.7f));
	rock.setRotation(-90);
	heart.setPosition(1270, 730);
		
	for (int i = 0; i < 1; i++)
	{
		int		l = rand() % 4;
		Enemy *a = new Enemy();
		if (l == 0)
			a->settings(enemyShip1, rand() % W, -50, (float)(rand() % 360), 50);
		else if (l == 1)
			a->settings(enemyShip2, rand() % W, -50, (float)(rand() % 360), 50);
		else if (l == 2)
			a->settings(enemyShip3, rand() % W, -50, (float)(rand() % 360), 50);
		else if (l == 3)
			a->settings(enemyShip4, rand() % W, -50, (float)(rand() % 360), 50);
		entities.push_back(a);
	}

	Player *p = new Player();
	p->settings(sPlayer, W / 2 - 80, H - 170, 0, 20);
	entities.push_back(p);
	p->anim.sprite.setScale(Vector2f(2, 2));
	ShowCursor(FALSE);
	while (app.isOpen())
	{
		Event event;

		GetCursorPos(CurPos);
		if (Keyboard::isKeyPressed(Keyboard::Escape) || f)
		{
			ShowCursor(TRUE);
			if (!title(&app, &event))
			{
				for (auto e : entities)
					delete e;
				return (0);
			}
			ShowCursor(FALSE);
			f = 0;
		}
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left && !(gameOver > 0))
				{
					Bullet *b = new Bullet();
					b->settings(sBullet, p->x, p->y, 0, 0);
					entities.push_back(b);
				}
				else if
					(event.key.code == Mouse::Right && p_rocket > 0 && !(gameOver > 0))
				{
					Rocket *b = new Rocket();
					b->name = "rocket";
					b->settings(rockets, p->x, p->y, 0.0, 0);
					entities.push_back(b);
					p_rocket--;
					if (p_rocket == 2)
						str_rocket = "2";
					else if (p_rocket == 1)
						str_rocket = "1";
					else
						str_rocket = "0";
				}
		}
		p->anim = sPlayer;
		if (CurPos->x >= 783)
		{
			p->anim = sPlayer_right;
			destination = 1;
			p->dx += 0.2f;
		}
		else if (CurPos->x < 583)
		{
			p->anim = sPlayer_left;
			destination = 2;
			p->dx -= 0.2f;
		}
		if (CurPos->y < 334)
		{
			p->dy -= 0.2f;
			p->anim = sPlayer_go;
			if (destination == 2)
				p->anim = sPlayer_left_go;
			if (destination == 1)
				p->anim = sPlayer_right_go;
		}
		else if (CurPos->y >= 434)
			p->dy += 0.2f;
		else
			p->thrust = 0;

		for (auto c : entities)
			if (c->name == "enemy" && rand() % 100 == 0)
				for (int kq = 0; kq < 3; kq++)
				{
					EnemyBullet *b = new EnemyBullet();
					b->settings(rBullet, c->x, c->y, (float)(70 + 20 * kq), 20);
					entities.push_back(b);
				}
		destination = 0;
		for (auto a : entities)
			for (auto b : entities)
			{
				if ((a->name == "enemy" && b->name == "bullet")
					|| (a->name == "enemy_bullet" && b->name == "bullet")
					|| (a->name == "enemy_bullet" && b->name == "rocket"))
					if (isCollide(a, b))
					{
						a->life = false;
						b->life = false;

						Entity *e = new Entity();
						if (a->name == "enemy_bullet" && b->name == "bullet")
						{
							e->settings(sExplosion_bullet, a->x, a->y, 0, 0);
							score += 5;
						}
						else
						{
							e->settings(sExplosion, a->x, a->y, 0, 0);
							score += 10;
						}
						e->name = "explosion";
						entities.push_back(e);
					}

				if (((a->name == "player" && b->name == "enemy")
					|| (a->name == "player" && b->name == "enemy_bullet"))
					&& !is_shield)
					if (isCollide(a, b))
					{
						p_life--;
						if (p_life == 2)
							str_life = "2";
						else if (p_life == 1)
							str_life = "1";
						else
							str_life = "0";
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion_ship, a->x, a->y, 0, 0);
						e->name = "explosion";
						entities.push_back(e);

						p->settings(sPlayer, W / 2 - 80, H - 170, 0, 20);
						p->dx = 0;
						p->dy = 0;
						is_shield = 200;
					}
				if (a->name == "rocket" && b->name == "enemy")
					if (isCollide(a, b))
					{
						a->life = false;
						b->life = false;

						for (auto n : entities)
							if (n->name == "enemy")
							{
								n->life = false;
								Entity *e = new Entity();
								e->settings(sExplosion, n->x, n->y, 0, 0);
								e->name = "explosion";
								entities.push_back(e);
								score += 10;
							}
					}
			}
	
		text3.setPosition(20, -17);
		text3.setString("Score: " + to_string(score));
		text2.setString("X " + str_rocket);
		text1.setString("X " + str_life);
		shield.setPosition(p->x, p->y);

		for (auto e : entities)
			if (e->name == "explosion")
				if (e->anim.isEnd()) e->life = 0;

	if (rand() % 80 == 0)
		{
			int		i = rand() % 4;
			Enemy *a = new Enemy();
			if (i == 0)
				a->settings(enemyShip1, rand() % W, -50, (float)(rand() % 360), 50);
			else if (i == 1)
				a->settings(enemyShip2, rand() % W, -50, (float)(rand() % 360), 50);
			else if (i == 2)
				a->settings(enemyShip3, rand() % W, -50, (float)(rand() % 360), 50);
			else if (i == 3)
				a->settings(enemyShip4, rand() % W, -50, (float)(rand() % 360), 50);
			entities.push_back(a);
		}
		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();
			if (e->life == false)
			{
				i = entities.erase(i);
				delete e;
			}
			else
				i++;
		}
		if (is_shield)
			is_shield--;
		if (p_life == 0 && gameOver == -1)
			gameOver = 150;
		if (gameOver > 0)
			gameOver--;
		if (gameOver == 0)
		{
			for (auto e : entities)
				delete e;
			return (0);
		}		
		//////draw//////
		app.draw(background);
		for (auto i : entities)
		{
			if (!(i->name == "player" && gameOver > 0))
				i->draw(app);
		}
		app.draw(text1);
		app.draw(text2);
		app.draw(text3);
		app.draw(heart);
		app.draw(rock);
		if (is_shield % 14 > 7 && gameOver == -1)
			app.draw(shield);
		if (gameOver > 0)
			app.draw(end);
		app.display();
	}

	return 0;
}
