#pragma once

#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"
#include "SpriteComponent.hpp"
#include <string>

using namespace std;


class ProjectileComponent : public Component

{
public:
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel) {};
	~ProjectileComponent()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}
   



	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			cout << "Out of Range" << endl;
			entity->destroy();
		}
		else if (transform->position.x > 1300 ||
                 transform->position.x < -100 );
		{
			cout << "Out of bounds!" << endl;
			entity->destroy();
		}
	}

private:

	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;


};