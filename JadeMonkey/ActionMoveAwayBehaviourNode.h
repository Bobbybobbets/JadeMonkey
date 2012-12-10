#pragma once
#include "BehaviourTreeNode.h"

class BehaviourComponent;
class AStarPathfindingComponent;
class GameEntity;

class ActionMoveAwayBehaviourNode : public BehaviourTreeNode
{
public:
	ActionMoveAwayBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* entity, AStarPathfindingComponent* pathfinding);
	bool Update(void);

protected:
	AStarPathfindingComponent* _pathfinding;
	GameEntity* _entity;
};