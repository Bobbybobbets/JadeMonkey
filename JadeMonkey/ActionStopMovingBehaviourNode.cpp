#include "ActionStopMovingBehaviourNode.h"
#include "BehaviourComponent.h"
#include "AStarPathfindingComponent.h"

ActionStopMovingBehaviourNode::ActionStopMovingBehaviourNode(BehaviourComponent* behaviourComponent, AStarPathfindingComponent* pathfinding)
	: BehaviourTreeNode(behaviourComponent, Action)
{
	this->_pathfinding = pathfinding;
}

bool ActionStopMovingBehaviourNode::Update(void)
{
	this->_behaviourComponent->SetState(Idle);
	this->_pathfinding->Stop();
	return true;
}