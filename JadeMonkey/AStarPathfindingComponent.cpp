#include "AStarPathfindingComponent.h"
#include <queue>
#include <vector>
#include "VectorUtil.h"
#include "PathFindingUtil.h"
#include <iostream>

using namespace std;

AStarPathfindingComponent::AStarPathfindingComponent(Game* game, GameEntity* entity, AIControllerComponent* aiController, long framesToWait)
	: BEntityComponent(game, entity)
{
	this->_aiController = aiController;
	this->_entityToFollow = nullptr;
	this->_followEntity = false;
	this->_frameThreshold = 50;
	this->_frameCount = 0;
	this->_frameWait = framesToWait;
}

void AStarPathfindingComponent::Initialize(void)
{
	this->_graph = PathfindingUtil::CreateAStarGraphFromFloors(70, 70, 20, 20, D3DXVECTOR3(-35, 0, -35));
	this->_path = stack<AStarNode*>();
	this->_doSearch = true;
}

void AStarPathfindingComponent::Update(GameEntity* entity, long time)
{
	if(!this->ensureGoalIntegrity(time))
	{
		AStarNode* entityNode = this->_graph->GetClosestNode(this->_entity->getPosition());
		AStarNode* goalNode;

		if(this->_followEntity)
		{
			this->_entityToFollowPosBuffer = this->_entityToFollow->getPosition();
			goalNode = this->_graph->GetClosestNode(this->_entityToFollowPosBuffer);
			
		}
		else
			goalNode = &this->_graph->Nodes[4600];


		this->findPosition(
			this->_graph, 
			entityNode, 
			goalNode, 
			&this->_path);

		this->_doSearch = false;
	}
	else
	{
		if(this->_path.size() > 0)
		{
			D3DXVECTOR3 moveToPosition = this->_path.top()->Position();
			if(this->_entity->getPosition().x == moveToPosition.x && this->_entity->getPosition().z == moveToPosition.z)
			{
				this->_path.pop();
			}

		
			this->_aiController->MoveTo(moveToPosition);
		}
	}
}

void AStarPathfindingComponent::FollowEntity(GameEntity* entity)
{
	this->_entityToFollow = entity;
	this->_followEntity = true;
	this->_doSearch = true;
}

void AStarPathfindingComponent::SetGoalPosition(D3DXVECTOR3 goal)
{
	this->_goalPosition = goal;
	this->_doSearch = true;
	this->_followEntity = false;
}

float AStarPathfindingComponent::getFScore(AStarNode* node, AStarNode* goal)
{
	//distance heuristic
	float distance = VectorUtil::Distance3f(node->Position(), goal->Position());
	return distance;
}

void AStarPathfindingComponent::findPosition(AStarPathfindingGraph* graph_in, AStarNode* currentNode_in, AStarNode* goalNode_in, stack<AStarNode*>* path_out)
{
	priority_queue<AStarNode*, vector<AStarNode*>, AStarNodeComparison> openset;
	vector<AStarNode*> closedset;
	AStarNode* currentNode = currentNode_in;
	AStarNode* goalNode = goalNode_in;
	AStarPathfindingGraph* graph = graph_in;
	int path_out_size = path_out->size();
	
	for(int i = 0; i < path_out_size; i++)
	{
		path_out->pop();
	}
	
	long startTick = GetTickCount();
	long endTick;

	//initialize all nodes
	for(int i = 0; i < graph->Size; i++)
	{
		graph->Nodes[i].Initialize();
	}

	openset.push(currentNode);

	while(openset.size() > 0)
	{
		AStarNode* current = openset.top();
		vector<AStarNode*> neighbours = current->Neighbours();

		if(current->Position() == goalNode->Position())
		{
			AStarNode* node = current;

			while(node->OptimalPathParent() != nullptr)
			{
				path_out->push(node);
				node = node->OptimalPathParent();
			}
		}

		openset.pop();
		current->Processed = true;

		vector<AStarNode*>::iterator it;
		for(it = neighbours.begin(); it < neighbours.end(); it++)
		{
			AStarNode* neighbour = (*it);

			if(!neighbour->Processed)
			{
				float tentative_g_score = current->GScore + VectorUtil::Distance3f(current->Position(), neighbour->Position());

				if(!neighbour->Visited || tentative_g_score <= neighbour->GScore)
				{
					neighbour->SetOptimalPathParent(current);
					neighbour->GScore = tentative_g_score;
					neighbour->FScore = neighbour->GScore + this->getFScore(neighbour, goalNode);

					if(!neighbour->Visited)
					{
						neighbour->Visited = true;
						openset.push(neighbour);
					}
					else
					{
						make_heap(
							const_cast<AStarNode**>(&openset.top()), 
							const_cast<AStarNode**>(&openset.top() + openset.size()),
							AStarNodeComparison());
					}
				}
			}
		}
	}

	endTick	 = GetTickCount();	
}

bool AStarPathfindingComponent::ensureGoalIntegrity(long time)
{
	if(this->_frameWait <= 0)
	{
		if(++this->_frameCount > this->_frameThreshold)
		{
			this->_frameCount = 0;
			if(this->_followEntity)
			{
				if(!this->_doSearch)
				{
					if(this->_entityToFollowPosBuffer != this->_entityToFollow->getPosition())
					{
						return false;
					}

					return true;
				}

				this->_doSearch = false;
				return true;
			}

			return !this->_doSearch;
		}
	}
	this->_frameWait--;
	return true;
}