#include "CondTargetProximityBehaviourNode.h"
#include "VectorUtil.h"
#include "BehaviourComponent.h"

CondTargetProximityBehaviourNode::CondTargetProximityBehaviourNode(BehaviourComponent* behaviourComponent, float distance)
	: BehaviourTreeNode(behaviourComponent, Condition)
{
	this->_distance = distance;
}

bool CondTargetProximityBehaviourNode::Update(void)
{
	if(this->_behaviourComponent->GetTarget())
	{
		float distance = VectorUtil::Distance3f(
			this->_behaviourComponent->GetTarget()->getPosition(),
			this->_behaviourComponent->getEntity()->getPosition());

		if(distance <= this->_distance)
		{
			return true;
		}

		return false;
	}
}