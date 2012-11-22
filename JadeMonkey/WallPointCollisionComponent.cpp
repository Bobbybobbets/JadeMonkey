#include "WallPointCollisionComponent.h"
#include "GraphicsComponent.h"
#include <string>

using namespace std;

WallPointCollisionComponent::WallPointCollisionComponent(Game* game, GameEntity* entity, PlayerComponent* pc) : PointCollisionComponent(game, entity, pc)
{
	Initialize();
	_position = entity->getPosition();
}


WallPointCollisionComponent::~WallPointCollisionComponent()
{

}

void WallPointCollisionComponent::Initialize(void)
{
	width = this->_entity->getGraphicsComponent()->getDx() * this->_entity->getGraphicsComponent()->getNumCols();
	length = 0;
	height = this->_entity->getGraphicsComponent()->getDy() * this->_entity->getGraphicsComponent()->getNumRows();
}

D3DXVECTOR3 WallPointCollisionComponent::checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
//	return false;
	// Check the x
	if( start.x > _position.x && start.x < _position.x + width && start.y < _position.y + height && start.y > _position.y)
	{
		if( start.z < _position.z)
			if( end.z > _position.z)
			{
				if( height < 100000)
					return D3DXVECTOR3(end.x, end.y + height, end.z);
				else
					return start;
			}
		if( start.z > _position.z)
			if(end.z < _position.z)
			{
				if( height < 100000)
					return D3DXVECTOR3(end.x, end.y + height, end.z);
				else
					return start;
			}
	}	
	return end;
}

string WallPointCollisionComponent::GetName()
{
	return "WallPointCollisionComponent";
}