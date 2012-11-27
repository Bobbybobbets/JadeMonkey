#pragma once
#include "Game.h"
#include <vector>

using namespace std;

class PathNode
{
public:
	float GScore;
	float FScore;
	bool Visited;
	PathNode(D3DXVECTOR3 position);
	PathNode(D3DXVECTOR3 position, PathNode* neighbours[]);
	D3DXVECTOR3 Position(void);
	vector<PathNode*> Neighbours();
	PathNode* OptimalPathParent();
	void SetOptimalPathParent(PathNode* node);
	void AddNeighbour(PathNode* node);

	friend bool operator <(
		const PathNode& x, const PathNode& y)
	{
		if(x.FScore < y.FScore)
			return true;

		return false;
	}

protected:
	D3DXVECTOR3 _position;
	vector<PathNode*> _neighbours;
	PathNode* _optimalPathParent;
};