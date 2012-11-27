#include "PathfindingGraphComponent.h"

PathfindingGraphComponent::PathfindingGraphComponent(
	Game* game, 
	GameEntity* entity, 
	PathfindingGraphNode* nodes[]
) : BEntityComponent(game, entity)
{
	this->_nodes = vector<PathfindingGraphNode*>(nodes, nodes + sizeof(nodes)/sizeof(nodes[0]));
}

vector<PathfindingGraphNode*> PathfindingGraphComponent::GetGraphNodes(void)
{
	return this->_nodes;
}

vector<PathfindingGraphNode*> PathfindingGraphComponent::GetActiveGraph(void)
{
	return *PathfindingGraphComponent::_activeGraph;
}