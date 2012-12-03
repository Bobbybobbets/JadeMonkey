#pragma once
#include "Game.h"
#include <vector>
#include "Enums.h"

using namespace std;

class AStarNode
{
public:
	float GScore;
	float FScore;
	bool Visited;
	bool Processed;
	AStarNode();
	AStarNode(D3DXVECTOR3 position);
	AStarNode(D3DXVECTOR3 position, AStarNode* neighbours[]);
	void Initialize();
	D3DXVECTOR3 Position(void);
	vector<AStarNode*> Neighbours();
	AStarNode* GetNeighbour(AStarNeighbourDirection direction);
	AStarNode* OptimalPathParent();
	void SetOptimalPathParent(AStarNode* node);
	void AddNeighbour(AStarNode* node, AStarNeighbourDirection direction);

protected:
	D3DXVECTOR3 _position;
	vector<AStarNode*> _neighbours;
	AStarNode* _top;
	AStarNode* _topRight;
	AStarNode* _right;
	AStarNode* _downRight;
	AStarNode* _down;
	AStarNode* _downLeft;
	AStarNode* _left;
	AStarNode* _topLeft;
	AStarNode* _optimalPathParent;
};

struct AStarNodeComparison
{
public:
	bool AStarNodeComparison::operator()(AStarNode* lhs, AStarNode* rhs)
	{
		return (lhs->FScore > rhs->FScore);
	};
};