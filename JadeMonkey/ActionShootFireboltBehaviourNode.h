#pragma once
#include "BehaviourTreeNode.h"

class FireboltSkillComponent;
class BehaviourComponent;
class GameEntity;

class ActionShootFireboltBehaviourNode : public BehaviourTreeNode
{
public:
	ActionShootFireboltBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* player, FireboltSkillComponent* fireboltComponent, string name);
	bool Update(void);

protected:
	GameEntity* _player;
	FireboltSkillComponent* _fireboltComponent;
};