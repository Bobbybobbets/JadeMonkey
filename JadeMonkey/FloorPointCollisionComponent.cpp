#include "FloorPointCollisionComponent.h"
#include "GraphicsComponent.h"
#include <string>

using namespace std;

FloorPointCollisionComponent::FloorPointCollisionComponent(Game* game, GameEntity* entity) : PointCollisionComponent(game, entity)
{
	_position = entity->getPosition();
	Initialize();
}


FloorPointCollisionComponent::~FloorPointCollisionComponent()
{

}

void FloorPointCollisionComponent::Initialize(void)
{
	width = this->_entity->getGraphicsComponent()->getDx() * this->_entity->getGraphicsComponent()->getNumCols();
	length = this->_entity->getGraphicsComponent()->getDz() * this->_entity->getGraphicsComponent()->getNumRows();
	height = 0;
}

bool FloorPointCollisionComponent::checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end)
{

	if( end.x < _position.x + width && end.x > _position.x && end.z < _position.z + length && end.z > _position.z)
	{
		if(start.y > _position.y )
		{
			if( end.y <= _position.y )
				return true;
		}
	}
		return false;
}

string FloorPointCollisionComponent::GetName()
{
	return "FloorPointCollisionComponent";
}