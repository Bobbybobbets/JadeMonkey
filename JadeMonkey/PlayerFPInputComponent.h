#pragma once

#include "BEntityComponent.h"
#include "Game.h"
#include "GameEntity.h"
#include "gameIO.h"
#include "CameraComponent.h"
#include "DoorUseComponent.h"
#include "PhysicsComponent.h"
#include "FireboltSkillComponent.h"
#include "PlayerComponent.h"


class PlayerFPInputComponent : public BEntityComponent
{
public:
	PlayerFPInputComponent(Game* game, GameEntity* entity, CameraComponent* camera, PhysicsComponent* physics, FireboltSkillComponent* fireboltSkill, DoorUseComponent *door, PlayerComponent *player);
	void Initialize(void);
	void Update(GameEntity* entity, long time);

private:
	gameIO* _io;
	CameraComponent* _camera;
	PhysicsComponent* _physics;
	FireboltSkillComponent* _firebolt;
	DoorUseComponent* _door;
	PlayerComponent *_player;

};