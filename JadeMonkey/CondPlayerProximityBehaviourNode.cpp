#include "CondPlayerProximityBehaviourNode.h"
#include "VectorUtil.h"
#include "BehaviourComponent.h"

CondPlayerProximityBehaviourNode::CondPlayerProximityBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* player, float distance, string name)
	: BehaviourTreeNode(behaviourComponent, name, Condition)
{
	this->_player = player;
	this->_distance = distance;
}

bool CondPlayerProximityBehaviourNode::Update(void)
{
	float distance = VectorUtil::Distance3f(
			this->_behaviourComponent->getEntity()->getPosition(), 
			this->_player->getPosition());
	if( distance <= this->_distance)
	{
		return true;
	}
	else
	{
		return false;
	}
}