#include "WallPointXCollisionComponent.h"
#include "GraphicsComponent.h"
#include "PlayerComponent.h"

#include <string>

using namespace std;

WallPointXCollisionComponent::WallPointXCollisionComponent(Game* game, GameEntity* entity) : PointCollisionComponent(game, entity)
{
	Initialize();
	_position = entity->getPosition();
}


WallPointXCollisionComponent::~WallPointXCollisionComponent()
{

}

void WallPointXCollisionComponent::Initialize(void)
{
	width = this->_entity->getGraphicsComponent()->getDx() * (this->_entity->getGraphicsComponent()->getNumCols() - 1);
	length = 0;
	height = this->_entity->getGraphicsComponent()->getDy() * (this->_entity->getGraphicsComponent()->getNumRows() - 1);
}

D3DXVECTOR3 WallPointXCollisionComponent::checkCollision(D3DXVECTOR3 start, D3DXVECTOR3 end, GameEntity* entity)
{
	GameEntity* pc = entity;
	
	if( start.z > _position.z && start.z < _position.z + width && start.y < _position.y + height + pc->getHeight() && start.y > _position.y)
	{
		if( start.x < _position.x)
			if( end.x > _position.x)
			{
				if( height <= pc->getStepHeight())
					return D3DXVECTOR3(end.x, end.y + height, end.z);
				else
					return start;
			}
		
		if( start.x > _position.x)
			if(end.x < _position.x)
			{
				if( height <= pc->getStepHeight())
					return D3DXVECTOR3(end.x, end.y + height , end.z);
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