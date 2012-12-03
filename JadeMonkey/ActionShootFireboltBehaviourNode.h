#pragma once
#include "BehaviourTreeNode.h"

class FireboltSkillComponent;
class BehaviourComponent;
class GameEntity;

class ActionShootFireboltBehaviourNode : BehaviourTreeNode
{
public:
	ActionShootFireboltBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* player, FireboltSkillComponent* fireboltComponent);
	bool Update(void);

protected:
	GameEntity* _player;
	FireboltSkillComponent* _fireboltComponent;
};