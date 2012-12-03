#include "SequenceSelectorBehaviourNode.h"
#include "Enums.h"

SequenceSelectorBehaviourNode::SequenceSelectorBehaviourNode(BehaviourComponent* behaviourComponent, string name)
	:BehaviourTreeNode(behaviourComponent, name, SequenceSelector)
{
}

bool SequenceSelectorBehaviourNode::Update(void)
{
	vector<BehaviourTreeNode*>::iterator it;

	for(it = this->_children.begin(); it < this->_children.end(); it++)
	{
		if(!(*it)->Update())
		{
			return false;
		}
	}

	return true;
}