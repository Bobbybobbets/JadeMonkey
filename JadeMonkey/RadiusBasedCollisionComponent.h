#pragma once
#include "CollisionComponent.h"
#include <vector>
#include "Enums.h"
#include "PlayerComponent.h"

using namespace std;

class RadiusBasedCollisionComponent : public CollisionComponent
{
public:
	RadiusBasedCollisionComponent(Game* game, GameEntity* entity, float radius, CollisionGroup group, CollisionConsequence consequence);
	~RadiusBasedCollisionComponent(void);
	void Initialize(void){}
	void Update(GameEntity* entity, long time);
	CollisionGroup GetGroup(void);
	float GetRadius(void);
	void SetTarget(GameEntity* target);
	bool Collided(void);
	string GetName(void){ return "RadiusBasedCollisionComponent";}

private:
	float _radius;
	CollisionGroup _group;
	static vector<RadiusBasedCollisionComponent*> _colliders;
	CollisionComponent* _lastCollision;
	bool _collision;
	CollisionConsequence _consequence;
	GameEntity* _target;
};
