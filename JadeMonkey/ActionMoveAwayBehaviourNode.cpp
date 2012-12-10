#include "ActionMoveAwayBehaviourNode.h"
#include "BehaviourComponent.h"

ActionMoveAwayBehaviourNode::ActionMoveAwayBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* entity, AStarPathfindingComponent* pathfinding)
	: BehaviourTreeNode(behaviourComponent, Action)
{
	this->_pathfinding = pathfinding;
	this->_entity = entity;
}

bool ActionMoveAwayBehaviourNode::Update(void)
{
	if(!(this->_behaviourComponent->GetState() == RunningAway) || this->_pathfinding->AtGoal())
	{
		D3DXVECTOR3 direction = this->_behaviourComponent->getEntity()->getPosition() - this->_entity->getPosition();
		D3DXVec3Normalize(&direction, &direction);

		this->_pathfinding->SetGoalPosition(this->_behaviourComponent->getEntity()->getPosition() + direction * 200);
		this->_behaviourComponent->SetState(RunningAway);
	}
	return true;
}