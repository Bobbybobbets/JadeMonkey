#include "AIControllerComponent.h"
#include "VectorUtil.h"

class GameEntity;

AIControllerComponent::AIControllerComponent(Game* game, GameEntity* entity)
	: BEntityComponent(game, entity)
{
	this->_moving = false;
}

void AIControllerComponent::Update(GameEntity* entity, long time)
{
	if(this->_moving)
	{
		D3DXVECTOR3 moveTo = D3DXVECTOR3(this->_moveToPosition.x, 0.0f, this->_moveToPosition.z);
		D3DXVECTOR3 curPos = D3DXVECTOR3(this->_entity->getPosition().x, 0.0f, this->_entity->getPosition().z);
		D3DXVECTOR3 step;
		D3DXVECTOR3 vToPosition = moveTo - curPos;
		this->_entity->setDirection(vToPosition);
		step = _entity->getDirection()*this->_entity->getSpeed();

		if(D3DXVec3Length(&vToPosition) < D3DXVec3Length(&step))
		{
			step = vToPosition;
		}
		
		this->_entity->setPosition(
			this->_entity->getPosition() + step
		);
		this->_moving = false;
	}
}

void AIControllerComponent::MoveTo(D3DXVECTOR3 position)
{
	this->_moveToPosition = position;
	this->_moving = true;
}