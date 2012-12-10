#pragma once
#include "BehaviourTreeNode.h"
#include "GameEntity.h"

class CondEntityProximityBehaviourNode : public BehaviourTreeNode
{
public:
	CondEntityProximityBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* entity, float distance, string name);
	bool Update(void);

protected:
	GameEntity* _entity;
	float _distance;
};