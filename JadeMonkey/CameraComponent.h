#pragma once
#include "GameEntity.h"
#include "BEntityComponent.h"

#define MOUSE_SENSITIVITY_SCALE 1000;

class CameraComponent : public BEntityComponent
{
public:
	CameraComponent(Game* game, GameEntity* entity);
	D3DXVECTOR3 UpVector(void);
	D3DXVECTOR3 LookAtVector(void);
	D3DXVECTOR3 Position(void);
	virtual void SetRollDelta(float angleDeg);
	virtual void SetPitchDelta(float angleDeg);
	virtual void SetYawDelta(float angleDeg);
	virtual void SetPositionAbs(D3DXVECTOR3 pos);
	virtual void SetPositionDelta(D3DXVECTOR3 delta);
	virtual void Update(GameEntity* entity, long time) override;
	virtual void Initialize(void) override;
	D3DXVECTOR3 MoveForward(float numUnits);  // moves the camera forward by the numUnits units along the lookAtVector
	D3DXVECTOR3 Strafe(float numUnits);  // moves the camera forward by the numUnits units along the lookAtVector
	void ChangeLookAt(D3DXVECTOR3 delta);
	D3DXMATRIX * GetViewMatrix(D3DXMATRIX * viewMatrix);
	void SetCamera(D3DXVECTOR3 position, D3DXVECTOR3 lookAtPoint, D3DXVECTOR3 upVector);
	float GetStrafeSpeed(void);
	float GetSpeed(void);
	int UpdateSpeed(float speed);
	float getHeightOfPlayer();


private:

	D3DXVECTOR3 _lookAtVector;
	D3DXVECTOR3 _upVector;
	D3DXMATRIX _rotMat;
	void updateOrientation(D3DXVECTOR3 rotVector, float angleRad);
	float _speed;
	float _strafeSpeed;
	float heightOfPlayer; // how tall the player is
};