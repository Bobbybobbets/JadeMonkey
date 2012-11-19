#pragma once

#include "BEntityComponent.h"
#include "Game.h"
#include "GameEntity.h"
#include "gameIO.h"
#include "CameraComponent.h"
#include "PhysicsComponent.h"

class PlayerFPInputComponent : public BEntityComponent
{
public:
	PlayerFPInputComponent(Game* game, GameEntity* entity, CameraComponent* camera, PhysicsComponent* physics);
	void Initialize(void);
	void Update(GameEntity* entity, long time);

private:
	gameIO* _io;
	CameraComponent* _camera;
	PhysicsComponent* _physics;
};