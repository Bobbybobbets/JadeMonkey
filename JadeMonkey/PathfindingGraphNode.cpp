#include "PathfindingGraphNode.h"

PathfindingGraphNode::PathfindingGraphNode(D3DXVECTOR3 position)
{
	this->_position = position;
	this->_children = vector<PathfindingGraphNode*>();
}

PathfindingGraphNode::PathfindingGraphNode(D3DXVECTOR3 position, PathfindingGraphNode* children[])
{
	this->_position = position;
	this->_children = vector<PathfindingGraphNode*>(
		children, 
		children + sizeof(children)/sizeof(children[0]));
}

D3DXVECTOR3 PathfindingGraphNode::GetPosition(void)
{
	return this->_position;
}

vector<PathfindingGraphNode*> PathfindingGraphNode::GetChildren(void)
{
	return this->_children;
}

void PathfindingGraphNode::AddChild(PathfindingGraphNode* child)
{
	this->_children.push_back(child);
}