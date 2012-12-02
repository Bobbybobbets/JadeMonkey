#include "PathfindingGraphNode.h"

PathfindingGraphNode::PathfindingGraphNode()
{
	this->_position = D3DXVECTOR3(0, 0, 0);
	this->_neighbours = vector<PathfindingGraphNode*>();
}

PathfindingGraphNode::PathfindingGraphNode(D3DXVECTOR3 position)
{
	this->_position = position;
	this->_neighbours = vector<PathfindingGraphNode*>();
}

PathfindingGraphNode::PathfindingGraphNode(D3DXVECTOR3 position, PathfindingGraphNode* neighbours[])
{
	this->_position = position;
	this->_neighbours = vector<PathfindingGraphNode*>(
		neighbours, 
		neighbours + sizeof(neighbours)/sizeof(neighbours[0]));
}

D3DXVECTOR3 PathfindingGraphNode::GetPosition(void)
{
	return this->_position;
}

vector<PathfindingGraphNode*> PathfindingGraphNode::GetNeighbours(void)
{
	return this->_neighbours;
}

void PathfindingGraphNode::AddNeighbour(PathfindingGraphNode* neighbour)
{
	this->_neighbours.push_back(neighbour);
}