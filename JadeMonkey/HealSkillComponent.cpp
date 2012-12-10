#include "HealSkillComponent.h"
#include "GameEntity.h";
#include "ScaledBoxGraphicsComponent.h"
#include "GridBasedCollisionComponent.h"
#include "LinearPathfindingComponent.h"
#include "AIControllerComponent.h"

HealSkillComponent::HealSkillComponent(Game* game, GameEntity* entity,  int cooldown, float range, CollisionGroup group)
	: TargetedSkillComponent(game, entity, cooldown, range)
{
	this->_group = group;
}

void HealSkillComponent::fireSkill(void)
{
	if(this->_target != nullptr)
	{
		GameEntity* healingbolt = new GameEntity(this->_game, D3DXVECTOR3(5, 5, 5));
		healingbolt->SetType(Projectile);
		healingbolt->setPosition(this->_entity->getPosition());
		healingbolt->setDirection(D3DXVECTOR3(this->_entity->getDirection().x, 0, this->_entity->getDirection().z));
		healingbolt->setVelocity(5);
		ScaledBoxGraphicsComponent* graphics = new ScaledBoxGraphicsComponent(this->_game, healingbolt, D3DCOLOR_RGBA(0,255,0,150));
		GridBasedCollisionComponent* collision = new GridBasedCollisionComponent(this->_game, healingbolt, 10, this->_group, Heal);
		AIControllerComponent* aiController = new AIControllerComponent(this->_game, healingbolt);
		LinearPathfindingComponent* pathfinding = new LinearPathfindingComponent(this->_game, healingbolt, aiController);

		pathfinding->FollowEntity(this->_target);
		collision->SetTarget(this->_target);

		healingbolt->AddComponent(aiController);
		healingbolt->AddComponent(pathfinding);
		healingbolt->AddComponent(collision);
		healingbolt->AddGraphicsComponent(graphics);

		healingbolt->Initialize();
		this->_children.push_back(healingbolt);
	}
}