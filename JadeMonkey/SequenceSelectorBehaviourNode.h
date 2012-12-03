#pragma once
#include "BehaviourTreeNode.h"

class SequenceSelectorBehaviourNode : public BehaviourTreeNode
{
public:
	SequenceSelectorBehaviourNode(BehaviourComponent* behaviourComponent);
	bool Update(void);
};