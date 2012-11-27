#include "AStarPathfindingComponent.h"
#include <queue>
#include <vector>
#include "VectorUtil.h"

using namespace std;

AStarPathfindingComponent::AStarPathfindingComponent(Game* game, GameEntity* entity, PathNode* currentNode)
	: BEntityComponent(game, entity)
{
	this->_currentNode = currentNode;
}

void AStarPathfindingComponent::Initialize(void)
{
}

void AStarPathfindingComponent::Update(GameEntity* entity, long time)
{
	priority_queue<PathNode*, vector<PathNode*>, greater<PathNode*>> openset;
	vector<PathNode*> closedset;

	this->_currentNode->GScore = 0;
	this->_currentNode->SetOptimalPathParent(nullptr);
	openset.push(this->_currentNode);

	while(openset.size() > 0)
	{
		PathNode* current = openset.top();
		vector<PathNode*> neighbours = current->Neighbours();

		if(current == this->_currentGoal)
		{
			
		}

		openset.pop();
		current->Visited = true;

		vector<PathNode*>::iterator it;
		for(it = neighbours.begin(); it < neighbours.end(); it++)
		{
			PathNode* neighbour = (*it);

			if(!neighbour->Visited)
			{
				neighbour->GScore = current->GScore + VectorUtil::Distance3f(current->Position(), neighbour->Position());
				neighbour->FScore = this->getFScore(neighbour);
				openset.push(neighbour);
			}
		}
	}

}

void AStarPathfindingComponent::SetGoal(PathNode* goal)
{
	this->_currentGoal = goal;
}

float AStarPathfindingComponent::getFScore(PathNode* node)
{
	//distance heuristic
	float distance = VectorUtil::Distance3f(node->Position(), this->_currentGoal->Position());
	return distance;
}