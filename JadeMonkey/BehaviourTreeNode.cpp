#include "BehaviourTreeNode.h"


BehaviourTreeNode::BehaviourTreeNode(BehaviourComponent* behaviourComponent, BehaviourTreeNodeType type)
{
	this->_type = type;
	this->_runningNode = nullptr;
	this->_behaviourComponent = behaviourComponent;
	this->_state = Ready;
}

void BehaviourTreeNode::AddChild(BehaviourTreeNode* node)
{
	this->_children.push_back(node);
}

BehaviourTreeNodeState BehaviourTreeNode::GetState(void)
{
	return this->_state;
}

void BehaviourTreeNode::SetState(BehaviourTreeNodeState state)
{
	this->_state = state;
}

BehaviourTreeNodeType BehaviourTreeNode::GetType(void)
{
	return this->_type;
}

vector<BehaviourTreeNode*> BehaviourTreeNode::GetChildren(void)
{
	return this->_children;
}
