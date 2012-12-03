#pragma once
#include "BehaviourTreeNode.h"

class PrioritySelectorBehaviourNode : public BehaviourTreeNode
{
public :
	PrioritySelectorBehaviourNode(BehaviourComponent* behaviourComponent);
	bool Update(void);
};