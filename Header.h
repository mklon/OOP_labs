#pragma	once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <time.h>
#include <list>
#include <stdlib.h>

using namespace	sf;
using namespace	std;
const int		W = 1366;
const int	H = 768;

namespace Program
{
	const float	DEGTORAD = 0.017453f;
	class	Animation
	{
	public:
		float			Frame, speed;
		Sprite			sprite;
		vector<IntRect> frames;
		
		Animation() {}
		Animation(Texture &t, int x, int y, int w, int h, int count, float Speed);
		void	update();
		bool	isEnd();

	};

	class	Entity : public Animation
	{
	public:
		float		x, y, dx, dy, angle, R;
		bool		life;
		string		name;
		Animation	anim;
		
		Entity();
		void			settings(Animation &a, int X, int Y, float Angle, int radius);
		virtual void	update() {};
		void			draw(RenderWindow &app);
		virtual			~Entity() {};
	};

	class	Enemy : public Entity
	{
	public:
		Enemy();
		void	update();

	};

	class	Bullet : public Entity
	{
	public:
		Bullet();
		void	update();
	};

	class	Rocket : public Entity
	{
	public:
		Rocket();
		void	update();
	};

	class	EnemyBullet : public Entity
	{
	public:
		EnemyBullet();
		void	update();
	};

	class	Player : public Entity
	{
	public:
		bool	thrust;

		Player();
		void	update();
	};
}
