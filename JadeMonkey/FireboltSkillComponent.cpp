#include "FireboltSkillComponent.h"
#include <d3dx9.h>
#include "GameEntity.h"
#include "ScaledBoxGraphicsComponent.h"
#include "PhysicsComponent.h"
#include "JadeMonkeyGame.h"

FireboltSkillComponent::FireboltSkillComponent(Game* game, GameEntity* entity, int cooldown)
	: SkillComponent(game, entity, cooldown)
{
}

void FireboltSkillComponent::fireSkill(void)
{
	GameEntity* firebolt = new GameEntity(this->_game, D3DXVECTOR3(5, 5, 5));
	firebolt->setPosition(this->_entity->getPosition());
	firebolt->setDirection(D3DXVECTOR3(this->_entity->getDirection().x, 0, this->_entity->getDirection().z));
	firebolt->setVelocity(1);
	ScaledBoxGraphicsComponent* graphics = new ScaledBoxGraphicsComponent(this->_game, firebolt, D3DCOLOR_RGBA(255,100,0,150));

	firebolt->AddGraphicsComponent(graphics);
	
	firebolt->Initialize();
	this->_children.push_back(firebolt);
	((JadeMonkeyGame*)this->_game)->GetEntitiesContainer()->EntitiesToAdd.push_back(firebolt);
}