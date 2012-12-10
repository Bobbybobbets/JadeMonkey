#include "CondHealthMonitorBehaviourNode.h"
#include "BehaviourComponent.h"

CondHealthMonitorBehaviourNode::CondHealthMonitorBehaviourNode(BehaviourComponent* behaviourComponent, int healthThreshold)
	: BehaviourTreeNode(behaviourComponent, Condition)
{
	this->_healthThreshold = healthThreshold;
}

bool CondHealthMonitorBehaviourNode::Update(void)
{
	if(this->_behaviourComponent->getEntity()->getLife() < this->_healthThreshold)
	{
		return true;
	}

	return false;
}