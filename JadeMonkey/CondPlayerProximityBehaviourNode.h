#pragma once
#include "BehaviourTreeNode.h"
#include "GameEntity.h"

class CondPlayerProximityBehaviourNode : public BehaviourTreeNode
{
public:
	CondPlayerProximityBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* player, float distance);
	bool Update(void);

protected:
	GameEntity* _player;
	float _distance;
};