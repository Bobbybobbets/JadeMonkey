#include "MainCharacter.h"

MainCharacter::MainCharacter(Game* game, InputComponent* input, CameraComponent* camera)
	: GameEntity(game)
{
	this->_input = input;
	this->_camera = camera;
}

int MainCharacter::Initialize(void)
{
	return 0;
}

int MainCharacter::Update(long time)
{
	this->_input->Update(this, time);
	this->_camera->Update(this, time);
}