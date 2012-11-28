#include "TrapDoorCollisionComponent.h"
#include "GraphicsComponent.h"
#include <string>

using namespace std;

TrapDoorCollisionComponent::TrapDoorCollisionComponent(Game* game, GameEntity* entity, PlayerComponent *pc, TrapDoorComponent *trapDoor) : PointCollisionComponent(game, entity, pc)
{
	_position = entity->getPosition();
	_trapDoor = trapDoor;
	Initialize();
}


TrapDoorCollisionComponent::~TrapDoorCollisionComponent()
{

}

void TrapDoorCollisionComponent::Initialize(void)
{
	width = this->_entity->getGraphicsComponent()->getDx() * (this->_entity->getGraphicsComponent()->getNumCols() - 1);
	length = this->_entity->getGraphicsComponent()->getDz() * this->_entity->getGraphicsComponent()->getNumRows();
	height = 0;
}

D3DXVECTOR3 TrapDoorCollisionComponent::checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end)
{

	if( !_trapDoor->getTriggered())
	{
		int x = pc->getHeight();
		if( end.x < _position.x + width && end.x > _position.x && end.z < _position.z + length && end.z > _position.z)
		{
			if(start.y >= _position.y + pc->getHeight())
			{
				if( end.y <= _position.y + pc->getHeight())
				{
					_trapDoor->setTriggered(true);
					return D3DXVECTOR3(-5000, _position.y +  pc->getHeight(), -5000);
				}
			}
		}
	}
	return end;
}

string TrapDoorCollisionComponent::GetName()
{
	return "TrapDoorCollisionComponent";
}