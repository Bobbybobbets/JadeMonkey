#pragma once
#include "BehaviourTreeNode.h"
#include "AStarPathfindingComponent.h"
//#include "BehaviourComponent.h"
#include "Enums.h"

class GameEntity;
class BehaviourComponent;

class ActionMoveToPlayerBehaviourNode : public BehaviourTreeNode
{
public:
	ActionMoveToPlayerBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* player, AStarPathfindingComponent* pathfinding, string name);
	bool Update(void);
protected:
	GameEntity* _player;
	AStarPathfindingComponent* _pathfinding;
};
