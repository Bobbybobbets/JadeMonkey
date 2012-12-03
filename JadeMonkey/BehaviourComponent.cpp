#include "BehaviourComponent.h"
#include <vector>
#include "AIEntitiesInteractionContainer.h"


using namespace std;

BehaviourComponent::BehaviourComponent(Game* game, GameEntity* entity, enum Behaviour behaviour, AIEntitiesInteractionContainer entitiesContainer, AStarPathfindingComponent* pathfinding)
	: BEntityComponent(game, entity)
{
	this->_currentState = Idle;

	switch(behaviour)
	{
	case BasicEnemy:
		this->_rootNode = BehaviourBuilder::BuildBasicEnemy(this, entitiesContainer.Player, pathfinding);
		break;
	}
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
