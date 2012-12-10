#include "CondEntityProximityBehaviourNode.h"
#include "VectorUtil.h"
#include "BehaviourComponent.h"

CondEntityProximityBehaviourNode::CondEntityProximityBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* entity, float distance, string name)
	: BehaviourTreeNode(behaviourComponent, name, Condition)
{
	this->_entity = entity;
	this->_distance = distance;
}

bool CondEntityProximityBehaviourNode::Update(void)
{
	float distance = VectorUtil::Distance3f(
			this->_behaviourComponent->getEntity()->getPosition(), 
			this->_entity->getPosition());
	if( distance <= this->_distance)
	{
		return true;
	}
	else
	{
		return false;
	}
}