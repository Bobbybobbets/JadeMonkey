#include "ActionMoveToPlayerBehaviourNode.h"
#include "BehaviourComponent.h"


ActionMoveToPlayerBehaviourNode::ActionMoveToPlayerBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* player, AStarPathfindingComponent* pathfinding, string name)
	: BehaviourTreeNode(behaviourComponent, name, Action)
{
	this->_player = player;
	this->_pathfinding = pathfinding;
}

bool ActionMoveToPlayerBehaviourNode::Update(void)
{
	if(this->_behaviourComponent->GetState() != ChasePlayer)
	{
		this->_pathfinding->FollowEntity(this->_player);
		this->_behaviourComponent->SetState(ChasePlayer);
		return true;
	}

	return false;
}