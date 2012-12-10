#include "CondAllyHealthLowBehaviourNode.h"
#include "GameEntity.h"
#include "BehaviourComponent.h"

CondAllyHealthLowBehaviourNode::CondAllyHealthLowBehaviourNode(BehaviourComponent* behaviourComponent, int healthThreshold)
	: BehaviourTreeNode(behaviourComponent, Condition)
{
	this->_healthThreshold = healthThreshold;
}

bool CondAllyHealthLowBehaviourNode::Update(void)
{
	GameEntity* lowestAlly = nullptr;
	vector<GameEntity*> allies = this->_behaviourComponent->GetAllies();

	for(vector<GameEntity*>::iterator it = allies.begin();
		it < allies.end();
		it++)
	{
		if((*it)->getLife() < 100)
		{
			if(!lowestAlly)
				lowestAlly = (*it);
			else if(lowestAlly->getLife() > (*it)->getLife())
			{
				lowestAlly = (*it);
			}
		}
	}

	if(lowestAlly)
	{
		this->_behaviourComponent->SetTarget(lowestAlly);
		return true;
	}

	return false;
}

