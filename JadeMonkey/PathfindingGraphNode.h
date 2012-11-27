#pragma once
#include <d3dx9.h>
#include <vector>

using namespace std;

class PathfindingGraphNode
{
public:
	PathfindingGraphNode(D3DXVECTOR3 position);
	PathfindingGraphNode(D3DXVECTOR3 position, PathfindingGraphNode* children[]);
	D3DXVECTOR3 GetPosition(void);
	vector<PathfindingGraphNode*> GetChildren(void);
	void AddChild(PathfindingGraphNode* child);

private:
	D3DXVECTOR3 _position;
	vector<PathfindingGraphNode*> _children;
};
