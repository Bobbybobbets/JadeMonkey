#include "PrioritySelectorBehaviourNode.h"
#include "Enums.h"

PrioritySelectorBehaviourNode::PrioritySelectorBehaviourNode(BehaviourComponent* behaviourComponent)
	: BehaviourTreeNode(behaviourComponent, PrioritySelector)
{
}

bool PrioritySelectorBehaviourNode::Update(void)
{
	vector<BehaviourTreeNode*>::iterator it;

	for(it = this->_children.begin(); it < this->_children.end(); it++)
	{
		if((*it)->Update())
		{
			return true;
		}
	}

	return false;
}