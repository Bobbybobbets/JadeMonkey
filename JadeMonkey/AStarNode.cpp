#include "PathNode.h"

PathNode::PathNode(D3DXVECTOR3 position)
{
	this->_position = position;
	this->_neighbours = vector<PathNode*>();
	this->_optimalPathParent = nullptr;
	this->Visited = false;
}

PathNode::PathNode(D3DXVECTOR3 position, PathNode* neighbours[])
{
	this->_position = position;
	this->_neighbours = vector<PathNode*>(neighbours, neighbours + sizeof(neighbours)/sizeof(neighbours[0]));
	this->_optimalPathParent = nullptr;
	this->Visited = false;
}

D3DXVECTOR3 PathNode::Position(void)
{
	return this->_position;
}

vector<PathNode*> PathNode::Neighbours(void)
{
	return this->_neighbours;
}

PathNode* PathNode::OptimalPathParent(void)
{
	return this->_optimalPathParent;
}

void PathNode::SetOptimalPathParent(PathNode* node)
{
	this->_optimalPathParent = node;
}

void PathNode::AddNeighbour(PathNode* node)
{
	this->_neighbours.push_back(node);
}