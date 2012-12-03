#pragma once
#include "BehaviourTreeNode.h"

class SequenceSelectorBehaviourNode : public BehaviourTreeNode
{
public:
	SequenceSelectorBehaviourNode(BehaviourComponent* behaviourComponent, string name);
	bool Update(void);
};