#include "FloorPointCollisionComponent.h"
#include "GraphicsComponent.h"
#include <string>

using namespace std;

FloorPointCollisionComponent::FloorPointCollisionComponent(Game* game, GameEntity* entity) 
	: PointCollisionComponent(game, entity)
{
	_position = entity->getPosition();
	Initialize();
}


FloorPointCollisionComponent::~FloorPointCollisionComponent()
{

}

void FloorPointCollisionComponent::Initialize(void)
{
	width = this->_entity->getGraphicsComponent()->getDx() * (this->_entity->getGraphicsComponent()->getNumCols() - 1);
	length = this->_entity->getGraphicsComponent()->getDz() * this->_entity->getGraphicsComponent()->getNumRows();
	height = 0;
}

D3DXVECTOR3 FloorPointCollisionComponent::checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end, GameEntity* entity)
{
	GameEntity* pc = entity;

	int x = entity->getHeight();
	if( end.x < _position.x + width && end.x > _position.x && end.z < _position.z + length && end.z > _position.z)
	{
		if(start.y >= _position.y + pc->getHeight())
		{
			if( end.y <= _position.y + pc->getHeight())
				return D3DXVECTOR3(-5000, _position.y +  pc->getHeight(), -5000);
		}
	}
	return end;
}

string FloorPointCollisionComponent::GetName()
{
	return "FloorPointCollisionComponent";
}