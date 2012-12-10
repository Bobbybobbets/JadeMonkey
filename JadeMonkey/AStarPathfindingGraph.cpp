#include "AStarPathfindingGraph.h"


AStarPathfindingGraph::AStarPathfindingGraph(D3DXVECTOR3 position, AStarNode** nodes, int size, int rows, int cols, int dx, int dz)
{
	this->_position = position;
	this->Nodes = nodes;
	this->Size = size;
	this->_rows = rows;
	this->_cols = cols;
	this->_dx = dx;
	this->_dz = dz;

	this->_nodeArray2D = this->buildArray(nodes, size);
}

AStarNode* AStarPathfindingGraph::GetClosestNode(D3DXVECTOR3 position)
{
	POINT p = this->getArrayPosition(position);

	return this->_nodeArray2D[p.x][p.y];
}

POINT AStarPathfindingGraph::getArrayPosition(D3DXVECTOR3 position)
{
	D3DXVECTOR3 graphPosition = this->_position;
	int rows = this->_rows;
	int cols = this->_cols;
	int dx = this->_dx;
	int dz = this->_dz;
	int x;
	int y;
	POINT p;

	p.x = (int)((position.x - graphPosition.x) / dx);
	p.y = (int)((position.z - graphPosition.z) / dz);

	if(p.x >= rows)
	{
		p.x = rows-1;
	}
	if(p.x < 0)
	{
		p.x = 0;
	}
	if(p.y >= cols)
	{
		p.y = cols-1;
	}
	if(p.y < 0)
	{
		p.y = 0;
	}

	return p;
}

vector<vector<AStarNode*>> AStarPathfindingGraph::buildArray(
	AStarNode** nodes_in, 
	int size)
{
	vector<vector<AStarNode*>> array2D;
	int rows = this->_rows;
	int cols = this->_cols;
	int dx = this->_dx;
	int dz = this->_dz;
	AStarNode** nodes = nodes_in;


	//height
	array2D.resize(rows);
	for(int i = 0; i < rows; i++)
	{
		//width
		array2D[i].resize(cols);	
	}

	for(int i = 0; i < size; i++)
	{

		POINT p = this->getArrayPosition(nodes[i]->Position());
		array2D[p.x][p.y] =  nodes[i];
	}

	return array2D;
}