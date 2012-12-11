#include "FireboltSkillComponent.h"
#include <d3dx9.h>
#include "GameEntity.h"
#include "ScaledBoxGraphicsComponent.h"
#include "PhysicsComponent.h"
#include "JadeMonkeyGame.h"
#include "Enums.h"
#include "RadiusBasedCollisionComponent.h"
#include "PointLightComponent.h"

FireboltSkillComponent::FireboltSkillComponent(Game* game, GameEntity* entity, int cooldown, CollisionGroup group, PlayerComponent *player)
	: SkillComponent(game, entity, cooldown)
{
	this->_indexBuffer = 0;
	this->_group = group;
	this->_player = player;
}

void FireboltSkillComponent::fireSkill(void)
{
	if(this->_children.size() < 4)
	{
		GameEntity* firebolt = new GameEntity(this->_game, D3DXVECTOR3(5, 5, 5));
		firebolt->SetType(Projectile);
		firebolt->setPosition(this->_entity->getPosition());
		firebolt->setDirection(D3DXVECTOR3(this->_entity->getDirection().x, 0, this->_entity->getDirection().z));
		firebolt->setVelocity(5);
		ScaledBoxGraphicsComponent* graphics = new ScaledBoxGraphicsComponent(this->_game, firebolt, D3DCOLOR_RGBA(255,100,0,150));
		RadiusBasedCollisionComponent* collision = new RadiusBasedCollisionComponent(this->_game, firebolt, 10, this->_group, MinusLife);
		PointLightComponent* light = new PointLightComponent(this->_game, firebolt, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), 50);

		firebolt->AddComponent(collision);
		firebolt->AddComponent(light);
		firebolt->AddGraphicsComponent(graphics);
		firebolt->Initialize();
		this->_children.push_back(firebolt);
	}
	else
	{
		this->_children[this->_indexBuffer%this->_children.size()]->setPosition(this->_entity->getPosition());
		this->_children[this->_indexBuffer%this->_children.size()]->setDirection(D3DXVECTOR3(this->_entity->getDirection().x, 0, this->_entity->getDirection().z));
		this->_children[this->_indexBuffer%this->_children.size()]->Enable();
		this->_indexBuffer++;
	}
	
}