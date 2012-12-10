#include "BehaviourComponent.h"
#include <vector>
#include "AIEntitiesInteractionContainer.h"
#include "FireboltSkillComponent.h"
#include "JadeMonkeyGame.h"


using namespace std;

vector<GameEntity*> BehaviourComponent::_allies;

BehaviourComponent::BehaviourComponent(Game* game, GameEntity* entity, enum Behaviour behaviour, AIEntitiesInteractionContainer entitiesContainer, AStarPathfindingComponent* pathfinding, PlayerComponent *player)
	: BEntityComponent(game, entity)
{
	this->_currentState = Idle;
	this->_player = player;
	this->_target = nullptr;
	this->_allies.push_back(entity);
	FireboltSkillComponent* firebolt;
	HealSkillComponent* healSkill;

	switch(behaviour)
	{
	case BasicEnemy:
		this->_rootNode = BehaviourBuilder::BuildBasicEnemy(this, entitiesContainer.Player, pathfinding);
		break;
	case RangedEnemy:
		firebolt = new FireboltSkillComponent(this->_game, this->getEntity(), 50, entitiesContainer.Group, _player);
		this->_entity->AddSkillComponent(firebolt);
		this->_rootNode = BehaviourBuilder::BuildRangedEnemy(this, entitiesContainer.Player, pathfinding, firebolt);
		break;
	case HealerEnemy:
		healSkill = new HealSkillComponent(this->_game, this->getEntity(), 50, 100, Player);
		this->_entity->AddSkillComponent(healSkill);
		this->_rootNode = BehaviourBuilder::BuildHealerEnemy(this, entitiesContainer.Player, pathfinding, healSkill);
		break;
	}
}

void BehaviourComponent::SetTarget(GameEntity* target)
{
	this->_target = target;
}

GameEntity* BehaviourComponent::GetTarget(void)
{
	return this->_target;
}

void BehaviourComponent::Update(GameEntity* entity, long time)
{
	this->_rootNode->Update();
}

void BehaviourComponent::SetState(BehaviourState state)
{
	this->_currentState = state;
}

BehaviourState BehaviourComponent::GetState(void)
{
	return this->_currentState;
}

vector<GameEntity*> BehaviourComponent::GetAllies(void)
{
	return this->_allies;
}