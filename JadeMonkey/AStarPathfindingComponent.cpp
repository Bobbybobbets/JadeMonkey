#include "AStarPathfindingComponent.h"
#include <queue>
#include <vector>
#include "VectorUtil.h"
#include "PathFindingUtil.h"
#include <iostream>

using namespace std;

AStarPathfindingComponent::AStarPathfindingComponent(Game* game, GameEntity* entity, AIControllerComponent* aiController, long framesToWait, AStarPathfindingGraph* graph)
	: BDrawableEntityComponent(game, entity)
{
	this->_graph = graph;
	this->_aiController = aiController;
	this->_entityToFollow = nullptr;
	this->_followEntity = false;
	this->_switchedEntity = false;
	this->_frameThreshold = 30;
	this->_frameCount = 0;
	this->_frameWait = framesToWait;
	this->_atGoal = false;

	this->_graphicEntity = new GameEntity(this->_game, D3DXVECTOR3(1, 1, 1));
	//ScaledBoxGraphicsComponent* nodeGraphic = new ScaledBoxGraphicsComponent(this->_game, this->_graphicEntity, D3DCOLOR_RGBA(255,0,0,255));
	//this->_graphicEntity->AddGraphicsComponent(nodeGraphic);
}

AStarPathfindingComponent::~AStarPathfindingComponent(void)
{
	delete this->_aiController;
	delete this->_graphicEntity;
}

void AStarPathfindingComponent::Initialize(void)
{
	//this->_graph = PathfindingUtil::CreateAStarGraphFromFloors(70, 70, 20, 20, D3DXVECTOR3(-35, 0, -35));
	this->_path = stack<AStarNode*>();
	this->_doSearch = false;
	this->_debug = true;
	this->_graphicEntity->Initialize();
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
			goalNode = this->_graph->GetClosestNode(this->_goalPosition);


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

			if(this->_path.size() == 0)
				this->_atGoal = true;
		}
	}
}

void AStarPathfindingComponent::Draw(long time)
{
	for(int i = 0; i < this->_graph->Size; i++)
	{
		this->_graphicEntity->setPosition(this->_graph->Nodes[i]->Position());
		this->_graphicEntity->Draw(time);
	}
}

bool AStarPathfindingComponent::AtGoal(void)
{
	return this->_atGoal;
}

void AStarPathfindingComponent::Stop(void)
{
	this->clearPath();
	this->_doSearch = false;
	this->_followEntity = false;
}

void AStarPathfindingComponent::FollowEntity(GameEntity* entity)
{
	this->clearPath();
	this->_entityToFollow = entity;
	this->_followEntity = true;
	this->_switchedEntity = true;
	this->_doSearch = true;
	this->_atGoal = false;
}

void AStarPathfindingComponent::SetGoalPosition(D3DXVECTOR3 goal)
{
	this->_goalPosition = goal;
	this->_doSearch = true;
	this->_followEntity = false;
	this->_atGoal = false;
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
	queue<AStarNode*> bestCandidates;
	list<AStarNode*> toSort;
	AStarNode* currentNode = currentNode_in;
	AStarNode* goalNode = goalNode_in;
	AStarPathfindingGraph* graph = graph_in;
	int path_out_size = path_out->size();
	
	this->clearPath();
	
	long startTick = GetTickCount();
	long endTick;

	//initialize all nodes
	for(int i = 0; i < graph->Size; i++)
	{
		graph->Nodes[i]->Initialize();
	}

	openset.push(currentNode);
	currentNode->FScore = this->getFScore(currentNode, goalNode);

	while(openset.size() > 0 || bestCandidates.size() > 0 || toSort.size() > 0)
	{
		AStarNode* current;

		if(bestCandidates.size() > 0)
		{
			current = bestCandidates.front();
			bestCandidates.pop();
		}
		else
		{
			for(int i = 0; i < toSort.size(); i++)
			{
				openset.push(toSort.front());
				toSort.pop_front();
			}

			current = openset.top();
			openset.pop();
		}
		
		vector<AStarNode*> neighbours = current->Neighbours();

		if(current->Position() == goalNode->Position())
		{
			AStarNode* node = current;

			while(node->OptimalPathParent() != nullptr)
			{
				path_out->push(node);
				node = node->OptimalPathParent();
			}

			break;
		}

		current->Processed = true;

		vector<AStarNode*>::iterator it;
		for(int i = 0; i < neighbours.size(); i++)
		{
			AStarNode* neighbour = neighbours[i];

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
						/*
						neighbour->Visited = true;
						if(neighbour->FScore < current->FScore)
						{
							bestCandidates.push(neighbour);
						}
						else
						{
							toSort.push_back(neighbour);
						}*/

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
					if(this->_entityToFollowPosBuffer != this->_entityToFollow->getPosition() || this->_switchedEntity)
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

void AStarPathfindingComponent::clearPath(void)
{
	for(int i = 0; i < this->_path.size(); i++)
	{
		this->_path.pop();
	}
}