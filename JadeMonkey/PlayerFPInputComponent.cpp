#include "PlayerFPInputComponent.h"


PlayerFPInputComponent::PlayerFPInputComponent(Game* game, GameEntity* entity, CameraComponent* camera, PhysicsComponent* physics, FireboltSkillComponent* fireboltSkill)
	: BEntityComponent(game, entity)
{
	this->_io = game->getIOInterface();
	this->_camera = camera;
	this->_physics = physics;
	this->_firebolt = fireboltSkill;
}

void PlayerFPInputComponent::Initialize()
{
}

void PlayerFPInputComponent::Update(GameEntity* entity, long time)
{
	int wndWidth = this->_game->getWndWidth();
	int wndHeight = _game->getWndHeight();
	CameraComponent* cam = this->_camera;

	D3DXVECTOR3 delta = this->_io->mouseDelta();
	if (delta.x != 0.0f && delta.y != 0.0f) {
		this->_camera->ChangeLookAt(delta);

		// Make sure that the cursor is in the middle of the screen
		SetCursorPos(wndWidth/2 , wndHeight/2);
	}

	if (this->_io->keyboardPressed(DIK_W)) {
		cam->MoveForward(cam->GetSpeed());
	}
	if (this->_io->keyboardPressed(DIK_S)) {
		cam->MoveForward(-cam->GetSpeed());
	}
	if (this->_io->keyboardPressed(DIK_A)) {
		cam->Strafe(cam->GetStrafeSpeed());  //CCW
	}
	if (this->_io->keyboardPressed(DIK_D)) {
		cam->Strafe(-cam->GetStrafeSpeed());
	}

	if (this->_io->keyboardPressed(DIK_SPACE) && _physics->getOnGround()) {
		_physics->setAccelerationVector(D3DXVECTOR3(0.0f,5.0f,0.0f));
	}

	if(this->_io->mouseButtonPressed(0))
	{
		this->_firebolt->Activate();
	}
}
