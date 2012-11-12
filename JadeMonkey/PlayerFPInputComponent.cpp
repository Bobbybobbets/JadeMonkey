#include "PlayerFPInputComponent.h"


PlayerFPInputComponent::PlayerFPInputComponent(Game* game, GameEntity* entity, CameraComponent* camera)
	: EntityComponent(game, entity)
{
	this->_io = game->getIOInterface();
	this->_camera = camera;
}

void PlayerFPInputComponent::Initialize()
{
}

void PlayerFPInputComponent::Update(GameEntity* entity, long time)
{
	int wndWidth = _game->getWndWidth();
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
		//roll left
		cam->Strafe(cam->GetStrafeSpeed());  //CCW
	}
	if (this->_io->keyboardPressed(DIK_D)) {
		// roll write
		cam->Strafe(-cam->GetStrafeSpeed());
	}

}
