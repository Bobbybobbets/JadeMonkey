#pragma once
#include <vector>
#include <d3dx9.h>
#include <math.h>
#include "AStarNode.h"

using namespace std;



class AStarPathfindingGraph
{
public:
	AStarPathfindingGraph(D3DXVECTOR3 position, AStarNode** nodes, int size, int rows, int cols, int dx, int dz);
	AStarNode** Nodes;
	unsigned int Size;

	AStarNode* GetClosestNode(D3DXVECTOR3 position);

protected:
	vector<vector<AStarNode*>> _nodeArray2D;
	D3DXVECTOR3 _position;
	int _rows;
	int _cols;
	int _dx;
	int _dz;

	POINT getArrayPosition(D3DXVECTOR3 position);
	vector<vector<AStarNode*>> buildArray(AStarNode** nodes_in, int size);
};