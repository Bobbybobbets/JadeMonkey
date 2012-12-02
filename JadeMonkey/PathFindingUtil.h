#pragma once
#include "GraphicsComponent.h"
#include "AStarPathfindingGraph.h"
#include "AStarNode.h"

class PathfindingUtil
{
public:
	static AStarPathfindingGraph* CreateAStarGraphFromFloors(unsigned int rows, unsigned int cols, float dx, float dz, D3DXVECTOR3 position);
};