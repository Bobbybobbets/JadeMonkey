#pragma once
#include "CollisionComponent.h"
#include <vector>
#include "Enums.h"
#include "PlayerComponent.h"

using namespace std;

class GridBasedCollisionComponent : public CollisionComponent
{
public:
	GridBasedCollisionComponent(Game* game, GameEntity* entity, float radius, CollisionGroup group, CollisionConsequence consequence, PlayerComponent *player);
	void Initialize(void){}
	void Update(GameEntity* entity, long time);
	CollisionGroup GetGroup(void);
	float GetRadius(void);
	bool Collided(void);
	string GetName(void){ return "GridBasedCollisionComponent";}

private:
	float _radius;
	CollisionGroup _group;
	static vector<GridBasedCollisionComponent*> _colliders;
	CollisionComponent* _lastCollision;
	bool _collision;
	CollisionConsequence _consequence;
	PlayerComponent *_player;
};
