#pragma once
#include "BEntityComponent.h"
#include "GameEntity.h"
#include "AStarNode.h"
#include "AStarPathfindingGraph.h"
#include <stack>
#include "AIControllerComponent.h"
#include "ScaledBoxGraphicsComponent.h"

class AStarPathfindingComponent : public BDrawableEntityComponent
{
public:
	AStarPathfindingComponent(Game* game, GameEntity* entity, AIControllerComponent* aiController, long framesToWait, AStarPathfindingGraph* graph);
	~AStarPathfindingComponent(void);
	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;
	virtual void Draw(long time) override;
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
	bool _switchedEntity;
	long _frameThreshold;
	long _frameCount;
	long _frameWait;
	bool _debug;
	GameEntity* _graphicEntity;

	float getFScore(AStarNode* node, AStarNode* goal);
	void findPosition(
		AStarPathfindingGraph* graph, AStarNode* currentNode, AStarNode* goalNode, stack<AStarNode*>* path_out);
	bool ensureGoalIntegrity(long time);
};
