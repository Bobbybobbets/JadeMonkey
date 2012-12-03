#include "ActionShootFireboltBehaviourNode.h"
#include "BehaviourComponent.h"
#include "FireboltSkillComponent.h"
#include "GameEntity.h"
#include "Enums.h"

ActionShootFireboltBehaviourNode::ActionShootFireboltBehaviourNode(BehaviourComponent* behaviourComponent, GameEntity* player, FireboltSkillComponent* fireboltComponent, string name)
	: BehaviourTreeNode(behaviourComponent, name, Action)
{
	this->_player = player;
	this->_fireboltComponent = fireboltComponent;
}

bool ActionShootFireboltBehaviourNode::Update(void)
{
	GameEntity* thisEntity = this->_behaviourComponent->getEntity();
	thisEntity->setDirection(this->_player->getPosition() - thisEntity->getPosition());
	this->_fireboltComponent->Activate();

	return true;
}