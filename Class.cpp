#include "Header.h"

namespace Program
{
	//_____________Class Animation_____________
	Animation::Animation(Texture &t, int x, int y, int w, int h, int count, float Speed)
	{
		Frame = 0;
		speed = Speed;

		for (int i = 0; i < count; i++)
			frames.push_back(IntRect(x + i*w, y, w, h));
		sprite.setTexture(t);
		sprite.setOrigin((float)(w / 2), (float)(h / 2));
		sprite.setTextureRect(frames[0]);
	}

	void	Animation::update()
	{
		Frame += speed;
		int n = frames.size();
		if (Frame >= n) Frame -= n;
		if (n>0) sprite.setTextureRect(frames[int(Frame)]);
	}

	bool	Animation::isEnd()
	{
		return Frame + speed >= frames.size();
	}

	//_____________Class Entity_____________
	Entity::Entity()
	{
		life = 1;
	}
	void	Entity::settings(Animation &a, int X, int Y, float Angle, int radius)
	{
		anim = a;
		x = (float)X;
		y = (float)Y;
		R = (float)radius;
		angle = Angle;
	}
	void	Entity::draw(RenderWindow &app)
	{
		anim.sprite.setPosition(x, y);
		app.draw(anim.sprite);

		CircleShape circle(R);
		circle.setFillColor(Color(255, 0, 0, 170));
		circle.setPosition(x, y);
		circle.setOrigin(R, R);
		//app.draw(circle);
	}

	//_____________Class Enemy_____________
	Enemy::Enemy()
	{
		dy = (float)(rand() % 3 + 2);
		name = "enemy";
	}
	void	Enemy::update()
	{
		y += dy;


		if (y > H + 50)
			life = 0;
	}

	//_____________Class Bullet_____________
	Bullet::Bullet()
	{
		name = "bullet";
		dx = 0;
	}
	void  Bullet::update()
	{
		dy = -cos(DEGTORAD) * 8.0f;
		y += dy;
		x += dx;
		if (x>W || x<0 || y>H || y<0)
			life = 0;
	}

	//_____________Class Rocket_____________
	Rocket::Rocket()
	{
		name = "rocket";
		dx = 0;
	}
	void	Rocket::update()
	{
		anim.sprite.setScale(Vector2f(2.5, 2.5));
		dy = -cos(DEGTORAD) * 8.0f;
		y += dy;
		x += dx;
		if (x>W || x<0 || y>H || y<0)
			life = 0;
	}

	//_____________Class EnemyBullet_____________
	EnemyBullet::EnemyBullet()
	{
		dx = 0;
		angle = 90;
		name = "enemy_bullet";
	}
	void	EnemyBullet::update()
	{
		dx = -cos(angle * DEGTORAD) * 6.0f;
		dy = sin(angle * DEGTORAD) * 6.0f;
		y += dy;
		x += dx;
		anim.sprite.setRotation(270 - angle);
		if (x>W || x<0 || y>H || y<0)
			life = 0;
	}

	//_____________Class Player_____________
	Player::Player()
	{
		name = "player";
	}
	void	Player::update()
	{
		anim.sprite.setScale(Vector2f(1.5, 1.5));
		if (thrust)
		{
			dx += cos(DEGTORAD)*0.2f;
			dy += sin(DEGTORAD)*0.2f;
		}
		else
		{
			dx *= 0.97f;
			dy *= 0.97f;
		}
		int		maxSpeed = 15;
		float	speed = sqrt(dx*dx + dy*dy);
		if (speed > maxSpeed)
		{
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
		}
		if (x > W + 20)
			x = 0 - 20;
		if (x < 0 - 20)
			x = W + 20;
		if (y < 20)
		{
			dy = 0;
			y = 20;
		}
		if (y > H - 20)
		{
			dy = 0;
			y = H - 20;
		}
		x += dx;
		y += dy;

	}
}
