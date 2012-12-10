#pragma once
#include "BehaviourTreeNode.h"

class BehaviourComponent;
class AStarPathfindingComponent;

class ActionStopMovingBehaviourNode : public BehaviourTreeNode
{
public:
	ActionStopMovingBehaviourNode(BehaviourComponent* behaviourComponent, AStarPathfindingComponent* pathfinding);
	bool Update(void);

protected:
	AStarPathfindingComponent* _pathfinding;

};