#include "ActionMoveToTargetBehaviourNode.h"
#include "BehaviourComponent.h"
#include "AStarPathfindingComponent.h"

ActionMoveToTargetBehaviourNode::ActionMoveToTargetBehaviourNode(BehaviourComponent* behaviourComponent, AStarPathfindingComponent* pathfinding)
	: BehaviourTreeNode(behaviourComponent, Action)
{
	this->_pathfinding = pathfinding;
}

bool ActionMoveToTargetBehaviourNode::Update(void)
{
	if(this->_behaviourComponent->GetState() != ChaseTarget && this->_behaviourComponent->GetTarget())
	{
		this->_pathfinding->FollowEntity(this->_behaviourComponent->GetTarget());
		this->_behaviourComponent->SetState(ChaseTarget);
		return true;
	}

	return false;
}