#pragma once
#include <d3dx9.h>
#include <vector>

using namespace std;

class PathfindingGraphNode
{
public:
	PathfindingGraphNode();
	PathfindingGraphNode(D3DXVECTOR3 position);
	PathfindingGraphNode(D3DXVECTOR3 position, PathfindingGraphNode* children[]);
	D3DXVECTOR3 GetPosition(void);
	vector<PathfindingGraphNode*> GetNeighbours(void);
	void AddNeighbour(PathfindingGraphNode* neighbour);

private:
	D3DXVECTOR3 _position;
	vector<PathfindingGraphNode*> _neighbours;
};
