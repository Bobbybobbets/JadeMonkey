#pragma once
#include "BEntityComponent.h"
#include "PathfindingGraphNode.h"
#include <vector>

class PathfindingGraphComponent : BEntityComponent
{
public:
	PathfindingGraphComponent(Game* game, GameEntity* entity, PathfindingGraphNode* nodes[]);
	vector<PathfindingGraphNode*> GetGraphNodes(void);

private:
	vector<PathfindingGraphNode*> _nodes;
};
