#include "WallPointXCollisionComponent.h"
#include "GraphicsComponent.h"
#include "PlayerComponent.h"

#include <string>

using namespace std;

WallPointXCollisionComponent::WallPointXCollisionComponent(Game* game, GameEntity* entity, PlayerComponent *pc) : PointCollisionComponent(game, entity, pc)
{
	Initialize();
	_position = entity->getPosition();
}


WallPointXCollisionComponent::~WallPointXCollisionComponent()
{

}

void WallPointXCollisionComponent::Initialize(void)
{
	width = this->_entity->getGraphicsComponent()->getDx() * this->_entity->getGraphicsComponent()->getNumCols();
	length = 0;
	height = this->_entity->getGraphicsComponent()->getDy() * this->_entity->getGraphicsComponent()->getNumRows();
}

D3DXVECTOR3 WallPointXCollisionComponent::checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end)
{

	
	if( start.z > _position.z && start.x < _position.z + width && start.y < _position.y + height && start.y > _position.y)
	{
		if( start.x < _position.x)
			if( end.x > _position.x)
			{
				if( height < 100000)
					return D3DXVECTOR3(end.x, end.y + height, end.z);
				else
					return start;
			}
		
		if( start.x > _position.x)
			if(end.x < _position.x)
			{
				if( height < 100000)
					return D3DXVECTOR3(end.x, end.y + height, end.z);
				else
					return start;
			}
	}	
	return end;
}

string WallPointXCollisionComponent::GetName()
{
	return "WallPointXCollisionComponent";
}