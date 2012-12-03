#include "ActionMoveToPlayerBehaviourNode.h"
#include "BehaviourComponent.h"


ActionMoveToPlayerBehaviourNode::ActionMoveToPlayerBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* player, AStarPathfindingComponent* pathfinding)
	: BehaviourTreeNode(behaviourComponent, Action)
{
	this->_player = player;
	this->_pathfinding = pathfinding;
}

bool ActionMoveToPlayerBehaviourNode::Update(void)
{
	this->_pathfinding->FollowEntity(this->_player);
	this->_behaviourComponent->SetState(ChasePlayer);
	return true;
}