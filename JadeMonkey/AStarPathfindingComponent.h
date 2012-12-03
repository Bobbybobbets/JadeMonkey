#pragma once
#include "BEntityComponent.h"
#include "GameEntity.h"
#include "AStarNode.h"
#include "AStarPathfindingGraph.h"
#include <stack>
#include "AIControllerComponent.h"

class AStarPathfindingComponent : public BEntityComponent
{
public:
	AStarPathfindingComponent(Game* game, GameEntity* entity, AIControllerComponent* aiController, long framesToWait);
	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;
	void FollowEntity(GameEntity* entity);
	void SetGoalPosition(D3DXVECTOR3 goal);

protected:
	D3DXVECTOR3 _goalPosition;
	AStarPathfindingGraph* _graph;
	stack<AStarNode*> _path;
	bool _doSearch;
	AIControllerComponent* _aiController;
	GameEntity* _entityToFollow;
	D3DXVECTOR3 _entityToFollowPosBuffer;
	bool _followEntity;
	long _frameThreshold;
	long _frameCount;
	long _frameWait;

	float getFScore(AStarNode* node, AStarNode* goal);
	void findPosition(
		AStarPathfindingGraph* graph, AStarNode* currentNode, AStarNode* goalNode, stack<AStarNode*>* path_out);
	bool ensureGoalIntegrity(long time);
};
