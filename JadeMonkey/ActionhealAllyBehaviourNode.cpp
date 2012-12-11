#include "ActionHealAllyBehaviourNode.h"
#include "HealSkillComponent.h"
#include "BehaviourComponent.h"

ActionHealAllyBehaviourNode::ActionHealAllyBehaviourNode(BehaviourComponent* behaviourComponent, HealSkillComponent* healSkill, string name)
	: BehaviourTreeNode(behaviourComponent, name, Action)
{
	this->_healSkillComponent = healSkill;
}

bool ActionHealAllyBehaviourNode::Update(void)
{
	GameEntity* target = this->_behaviourComponent->GetTarget();

	if(target)
	{
		if(this->_healSkillComponent->InRange(target))
		{
				this->_healSkillComponent->SetTarget(target);
				this->_healSkillComponent->Activate();
				this->_behaviourComponent->SetTarget(nullptr);
				return true;
		}
	}
	return false;
}