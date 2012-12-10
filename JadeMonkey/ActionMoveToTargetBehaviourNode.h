#pragma once
#include "BehaviourTreeNode.h"

class BehaviourComponent;
class AStarPathfindingComponent;

class ActionMoveToTargetBehaviourNode : public BehaviourTreeNode
{
public:
	ActionMoveToTargetBehaviourNode(BehaviourComponent* behaviourComponent, AStarPathfindingComponent* pathfinding);
	bool Update(void);

protected:
	AStarPathfindingComponent* _pathfinding;
};