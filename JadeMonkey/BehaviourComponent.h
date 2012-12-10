#pragma once
#include "BEntityComponent.h"
#include "BehaviourTreeNode.h"
#include "AStarPathfindingComponent.h"
#include "BehaviourBuilder.h"
#include "AIEntitiesInteractionContainer.h"
#include "Enums.h"

class PlayerComponent;
class GameEntity;

class BehaviourComponent : public BEntityComponent
{
public:
	BehaviourComponent(Game* game, GameEntity* entity, enum Behaviour behaviour, AIEntitiesInteractionContainer entitiesContainer, AStarPathfindingComponent* pathfinding, PlayerComponent *player);
	void Update(GameEntity* entity, long time) override;
	BehaviourState GetState(void);
	void SetState(BehaviourState state);
	void SetTarget(GameEntity* target);
	GameEntity* GetTarget(void);
	vector<GameEntity*> GetAllies(void);


protected:
	BehaviourState _currentState;
	BehaviourTreeNode* _rootNode;
	PlayerComponent *_player;
	GameEntity* _target;
	static vector<GameEntity*> _allies;
};