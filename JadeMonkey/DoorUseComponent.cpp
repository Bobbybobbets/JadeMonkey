#include "DoorUseComponent.h"
#include "GraphicsComponent.h"

DoorUseComponent::DoorUseComponent() : BEntityComponent(NULL,NULL)
{

}

DoorUseComponent::DoorUseComponent(Game *game, GameEntity *entity, CameraComponent *camera, PlayerComponent *player, DoorComponent *door, bool xDoor) : BEntityComponent(game, entity)
{
	this->xDoor = xDoor;
	this->player = player;
	this->door = door;
	this->camera = camera;
	Initialize();
}

bool DoorUseComponent::checkAttemptedOpenDoor()
{
	// equation for the line is p = dl + lo  , l is camera look at vector and lo is the players location + eight in the y value
	// and d = (po - lo) . n / l . n
	// po is the position of the entity, n is the normal of the plane
	// if the DoorComponent xDoor is true, then the normal is (0,0,1) , if xDoor is false the normal is (1,0,0)
	// after finding d sub into the original value and solve for the new line
	// Then check to see if it's in the bounds of the door

	D3DXVECTOR3 lookAt = camera->LookAtVector();
	D3DXVECTOR3 normal;
	D3DXVECTOR3 numerator = this->_entity->getPosition() - player->getEntity()->getPosition();

	if(this->xDoor)
		normal = D3DXVECTOR3(1,0,0);
	else
		normal = D3DXVECTOR3(0,0,1);


	int d = D3DXVec3Dot(&numerator , &normal) / D3DXVec3Dot(&lookAt, &normal);

	D3DXVECTOR3 intersection = d * lookAt + player->getEntity()->getPosition();

	if( xDoor )
		return checkXDoor( intersection);
	else
		return checkZDoor(intersection);
}

bool DoorUseComponent::checkXDoor(D3DXVECTOR3 intersection)
{
	D3DXVECTOR3 entPos = this->_entity->getPosition();
		if( intersection.z >  entPos.z && intersection.z <  entPos.z + width 
			&& intersection.y < entPos.y + height + player->getHeight() && intersection.y >  entPos.y)
			return true;
	return false;

}

bool DoorUseComponent::checkZDoor(D3DXVECTOR3 intersection)
{
	D3DXVECTOR3 entPos = this->_entity->getPosition();
	if( intersection.x > entPos.x && intersection.x < entPos.x + width 
		&& intersection.y < entPos.y + height + player->getHeight() && intersection.y > entPos.y)
		return true;

	return false;
}


void DoorUseComponent::Initialize(void)
{
	width = this->_entity->getGraphicsComponent()->getDx() * (this->_entity->getGraphicsComponent()->getNumCols() - 1);
	height = this->_entity->getGraphicsComponent()->getDy() * (this->_entity->getGraphicsComponent()->getNumRows() - 1);
}

int DoorUseComponent::getNumKeys()
{
	return this->door->getNumKeys();
}