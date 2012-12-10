#pragma once
#include "BEntityComponent.h"

class AIControllerComponent;
class GameEntity;
class Game;

class LinearPathfindingComponent : public BEntityComponent
{
public:
	LinearPathfindingComponent(Game* game, GameEntity* entity, AIControllerComponent* aiController);
	~LinearPathfindingComponent(void);
	virtual void Update(GameEntity* entity, long time) override;
	void FollowEntity(GameEntity* entity);

protected:
	GameEntity* _entityToFollow;
	bool _followEntity;
	AIControllerComponent* _aiController;
};