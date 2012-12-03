#include "GridBasedCollisionComponent.h"
#include "GameEntity.h"
#include "VectorUtil.h"
#include "Enums.h"

vector<GridBasedCollisionComponent*> GridBasedCollisionComponent::_colliders;

GridBasedCollisionComponent::GridBasedCollisionComponent(Game* game, GameEntity* entity, float radius, CollisionGroup group, CollisionConsequence consequence, PlayerComponent *player)
	: CollisionComponent(game, entity)
{
	this->_radius = radius;
	this->_group = group;
	this->_colliders.push_back(this);
	this->_consequence = consequence;
	this->_player = player;
}

CollisionGroup GridBasedCollisionComponent::GetGroup(void)
{
	return this->_group;
}

float GridBasedCollisionComponent::GetRadius(void)
{
	return this->_radius;
}

void GridBasedCollisionComponent::Update(GameEntity* entity, long time)
{
	this->_collision = false;

	for(int i = 0; i < this->_colliders.size(); i++)
	{
		if(this->_colliders[i]->GetGroup() != this->_group)
		{
			GameEntity* otherEntity = this->_colliders[i]->getEntity();
			D3DXVECTOR3 positionOther = this->_colliders[i]->getEntity()->getPosition();
			D3DXVECTOR3 positionThis = this->_entity->getPosition();
			float distance = VectorUtil::Distance3f(D3DXVECTOR3(positionOther.x, positionOther.y, positionOther.z), D3DXVECTOR3(positionThis.x, positionThis.y, positionThis.z));

			if(distance < this->_radius + this->_colliders[i]->GetRadius())
			{
				this->_collision = true;
				this->_lastCollision = this->_colliders[i];

				switch(this->_consequence)
				{
				case MinusSize:
					otherEntity->setSize(otherEntity->getSize() - D3DXVECTOR3(0, 5, 0));
					break;
				case MinusLife:
					otherEntity->reduceLife(25);
					break;
				case Kill:
					if(otherEntity->GetType() == HumanPlayer)
					{
						otherEntity->setPosition(D3DXVECTOR3(30, 70, 30));
						_player->LoseLife();
					}
					else if(otherEntity->GetType() == Enemy)
					{
						otherEntity->SetStatus(false);
					}
					break;
				case Nothing:
					break;
				}
			}
		}
	}
}

bool GridBasedCollisionComponent::Collided(void)
{
	return this->_collision;
}

