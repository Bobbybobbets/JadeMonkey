#include "RadiusBasedCollisionComponent.h"
#include "GameEntity.h"
#include "VectorUtil.h"
#include "Enums.h"
#include "JadeMonkeyGame.h"
#include  <algorithm>

vector<RadiusBasedCollisionComponent*> RadiusBasedCollisionComponent::_colliders;

RadiusBasedCollisionComponent::RadiusBasedCollisionComponent(Game* game, GameEntity* entity, float radius, CollisionGroup group, CollisionConsequence consequence)
	: CollisionComponent(game, entity)
{
	this->_radius = radius;
	this->_group = group;
	this->_colliders.push_back(this);
	this->_consequence = consequence;
	this->_collision = false;
	this->_target = nullptr;
}

RadiusBasedCollisionComponent::~RadiusBasedCollisionComponent(void)
{
	RadiusBasedCollisionComponent::_colliders.erase(
		std::remove(
			RadiusBasedCollisionComponent::_colliders.begin(), 
			RadiusBasedCollisionComponent::_colliders.end(), 
			this), 
		RadiusBasedCollisionComponent::_colliders.end());
}

CollisionGroup RadiusBasedCollisionComponent::GetGroup(void)
{
	return this->_group;
}

float RadiusBasedCollisionComponent::GetRadius(void)
{
	return this->_radius;
}

void RadiusBasedCollisionComponent::Update(GameEntity* entity, long time)
{
	bool collision = false;

	for(int i = 0; i < this->_colliders.size(); i++)
	{
		if(!this->_target || (this->_target && this->_target == this->_colliders[i]->getEntity()))
		{
			if(this->_colliders[i]->GetGroup() != this->_group)
			{
				GameEntity* otherEntity = this->_colliders[i]->getEntity();
				D3DXVECTOR3 positionOther = this->_colliders[i]->getEntity()->getPosition();
				D3DXVECTOR3 positionThis = this->_entity->getPosition();
				float distance = VectorUtil::Distance3f(D3DXVECTOR3(positionOther.x, positionOther.y, positionOther.z), D3DXVECTOR3(positionThis.x, positionThis.y, positionThis.z));

				if(distance < this->_radius + this->_colliders[i]->GetRadius())
				{
					collision = true;
					this->_lastCollision = this->_colliders[i];

					if(!this->_collision && otherEntity->GetType() != Projectile)
					{
						this->_collision = true;
						switch(this->_consequence)
						{
						case MinusSize:
							otherEntity->setSize(otherEntity->getSize() - D3DXVECTOR3(0, 5, 0));
							break;
						case MinusLife:
							if(otherEntity == ((JadeMonkeyGame*)this->_game)->GetPlayer()->getEntity())
							{
								if(!((JadeMonkeyGame*)this->_game)->GetPlayer()->getEntity()->IsInvincible())
								{
									((JadeMonkeyGame*)this->_game)->GetPlayer()->LoseLife();
								}
							}
							else{
								otherEntity->reduceLife(50);
							}
							break;
						case Kill:
							if(otherEntity->GetType() == HumanPlayer)
							{
								otherEntity->setPosition(D3DXVECTOR3(30, 70, 30));
								((JadeMonkeyGame*)this->_game)->GetPlayer()->LoseLife();
							}
							else if(otherEntity->GetType() == Enemy)
							{
								otherEntity->SetStatus(false);
							}
							break;
						case Heal:
							otherEntity->augmentLife(25);
							this->_entity->Disable();
							break;
						case Nothing:
							break;
						}
					}
				}
			}
		}
	}

	if(!collision && this->_collision)
	{
		this->_collision = false;
	}
}

void RadiusBasedCollisionComponent::SetTarget(GameEntity* target)
{
	this->_target = target;
}

bool RadiusBasedCollisionComponent::Collided(void)
{
	return this->_collision;
}

