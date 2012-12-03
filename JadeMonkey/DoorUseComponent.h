#pragma once

#include "PointCollisionComponent.h"
#include "DoorComponent.h"
#include "CameraComponent.h"

class DoorUseComponent : BEntityComponent
{
private:
	PlayerComponent *player;
	DoorComponent *door;
	CameraComponent *camera;
	bool xDoor;
	int width;
	int height;

	bool checkXDoor(D3DXVECTOR3);
	bool checkZDoor(D3DXVECTOR3);
public:
	DoorUseComponent();
	DoorUseComponent(Game* game, GameEntity *entity, CameraComponent *camera, PlayerComponent *player, DoorComponent *door, bool xDoor);
	~DoorUseComponent();

	bool checkAttemptedOpenDoor();

	virtual void Initialize(void) override;

	int getNumKeys();
	void setNumKeys(int numKeys);
};