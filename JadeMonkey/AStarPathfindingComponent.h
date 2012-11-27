#pragma once
#include "BEntityComponent.h"
#include "GameEntity.h"
#include "PathNode.h"

class AStarPathfindingComponent : BEntityComponent
{
public:
	AStarPathfindingComponent(Game* game, GameEntity* entity, PathNode* currentNode);
	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;
	void SetGoal(PathNode* goal);

protected:
	PathNode* _currentNode;
	PathNode* _currentGoal;
	
	float getFScore(PathNode* node);

};
