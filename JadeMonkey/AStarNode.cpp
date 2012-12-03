#include "AStarNode.h"

AStarNode::AStarNode()
{
	this->_position = D3DXVECTOR3(0, 0, 0);
	this->_neighbours = vector<AStarNode*>();
	this->_optimalPathParent = nullptr;
	this->Visited = false;
	this->Processed = false;
}

AStarNode::AStarNode(D3DXVECTOR3 position)
{
	this->_position = position;
	this->_neighbours = vector<AStarNode*>();
	this->_optimalPathParent = nullptr;
	this->Visited = false;
	this->Processed = false;
}

AStarNode::AStarNode(D3DXVECTOR3 position, AStarNode* neighbours[])
{
	this->_position = position;
	this->_neighbours = vector<AStarNode*>(neighbours, neighbours + sizeof(neighbours)/sizeof(neighbours[0]));
	this->_optimalPathParent = nullptr;
	this->Visited = false;
	this->Processed = false;
}

void AStarNode::Initialize(void)
{
	this->FScore = 0;
	this->GScore = 0;
	this->Visited = false;
	this->Processed = false;
	this->_optimalPathParent = nullptr;
}

D3DXVECTOR3 AStarNode::Position(void)
{
	return this->_position;
}

vector<AStarNode*> AStarNode::Neighbours(void)
{
	return this->_neighbours;
}

AStarNode* AStarNode::GetNeighbour(AStarNeighbourDirection direction)
{
	switch(direction)
	{
	case Top:
		return this->_top;
		break;
	case TopRight:
		return this->_topRight;
		break;
	case Right:
		return this->_right;
		break;
	case DownRight:
		return this->_downRight;
		break;
	case Down:
		return this->_down;
		break;
	case DownLeft:
		return this->_downLeft;
		break;
	case Left:
		return this->_left;
		break;
	case TopLeft:
		return this->_topLeft;
		break;
	}
}

AStarNode* AStarNode::OptimalPathParent(void)
{
	return this->_optimalPathParent;
}

void AStarNode::SetOptimalPathParent(AStarNode* node)
{
	this->_optimalPathParent = node;
}

void AStarNode::AddNeighbour(AStarNode* node, AStarNeighbourDirection direction)
{
	this->_neighbours.push_back(node);

	switch(direction)
	{
	case Top:
		this->_top = node;
		break;
	case TopRight:
		this->_topRight = node;
		break;
	case Right:
		this->_right = node;
		break;
	case DownRight:
		this->_downRight = node;
		break;
	case Down:
		this->_down = node;
		break;
	case DownLeft:
		this->_downLeft = node;
		break;
	case Left:
		this->_left = node;
		break;
	case TopLeft:
		this->_topLeft = node;
		break;
	}
}