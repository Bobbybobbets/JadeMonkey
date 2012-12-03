#include "CameraComponent.h"
#include <iostream>

using namespace std;

CameraComponent::CameraComponent(Game* game, GameEntity* entity)
	: BEntityComponent(game, entity)
{
}

void CameraComponent::Initialize(void)
{
	this->_speed = 5.0f;
	this->_strafeSpeed = 5.0f;
}

void CameraComponent::Update(GameEntity* entity, long time)
{

}

D3DXVECTOR3 CameraComponent::UpVector(void)
{
	return this->_upVector;
}

D3DXVECTOR3 CameraComponent::LookAtVector(void)
{
	return this->_lookAtVector;
}

D3DXVECTOR3 CameraComponent::Position(void)
{
	return this->_entity->getPosition();
}

void CameraComponent::SetRollDelta(float angleDeg)
{
	float angleRad = D3DXToRadian(angleDeg);
	D3DXVECTOR3 rotVector(0.0,0.0,0.0);

	// get rotation axis
	rotVector = this->_lookAtVector;

	updateOrientation(rotVector, angleRad);
}

void CameraComponent::SetPitchDelta(float angleDeg)
{
	float angleRad = D3DXToRadian(angleDeg);
	D3DXVECTOR3 rotVector(0.0,0.0,0.0);

	D3DXVec3Cross( &rotVector, &this->_upVector, &this->_lookAtVector);

	updateOrientation(rotVector , angleDeg);
}

void CameraComponent::SetYawDelta(float angleDeg)
{
	float angleRad = D3DXToRadian(angleDeg);
	D3DXVECTOR3 rotVector(0.0,0.0,0.0);

	updateOrientation(this->_upVector, angleDeg);
}

void CameraComponent::SetPositionAbs(D3DXVECTOR3 pos)
{
	this->_entity->setPosition(pos);
}

void CameraComponent::SetPositionDelta(D3DXVECTOR3 delta)
{
	D3DXVECTOR3 pos = this->Position();
	pos.x += delta.x;
	pos.y += delta.y;
	pos.z += delta.z;

	this->_entity->setPosition(pos);
}

void CameraComponent::ChangeLookAt(D3DXVECTOR3 delta)
{
	D3DXMATRIX rotMat, rotMat1, rotMat2;	
	D3DXVECTOR3 xaxis;
	D3DXVECTOR3 yaxis;
	
	// Initialize the axis to their respective values
	yaxis.x = 0;
	yaxis.y = 1;
	yaxis.z = 0;

	// Scale the change in mouse (configurable setting?)
	delta.x /= MOUSE_SENSITIVITY_SCALE;
	delta.y /= MOUSE_SENSITIVITY_SCALE;

	//Declare the rotation axis based on the x and y axis 
	D3DXMatrixRotationAxis(&rotMat1, &yaxis,delta.x);
	D3DXVec3Cross(&xaxis, &_upVector, &_lookAtVector);
	D3DXMatrixRotationAxis(&rotMat2, &xaxis,delta.y);

	// Compound the two rotation matrices
	rotMat = rotMat2 *  rotMat1 ;
	
	// Transform the upvector and lookatvector based on the rotation matrix
	D3DXVec3TransformCoord(&this->_upVector, &this->_upVector, &rotMat);
	D3DXVec3TransformCoord(&this->_lookAtVector, &this->_lookAtVector, &rotMat);

	// Ensure that the magnitudes are less than 1
	D3DXVec3Normalize(&this->_upVector, &this->_upVector);
	D3DXVec3Normalize(&this->_lookAtVector, &this->_lookAtVector);

	this->_entity->setDirection(this->_lookAtVector);
}

D3DXMATRIX* CameraComponent::GetViewMatrix(D3DXMATRIX* viewMatrix)
{
	D3DXVECTOR3 lookAt;

	//lookAtVector = D3DXVECTOR3(.5,-.15,.5);
	D3DXVECTOR3 position = this->Position();
	lookAt = position + this->_lookAtVector;


	return(D3DXMatrixLookAtLH(viewMatrix, &this->Position(),&lookAt, &this->_upVector));
}


D3DXVECTOR3 CameraComponent::MoveForward(float numUnits)
{
	float magnitude;
	magnitude = numUnits;
	D3DXVECTOR3 temp;
	D3DXVECTOR3 xzDirection;
	xzDirection = D3DXVECTOR3(this->_lookAtVector.x, 0, this->_lookAtVector.z);
	D3DXVec3Normalize(&xzDirection, &xzDirection);

	temp.x = Position().x + xzDirection.x * magnitude;
	temp.z = Position().z + xzDirection.z * magnitude;
	temp.y = Position().y;
	D3DXVECTOR3 lookAt = this->_lookAtVector;

	
	temp = 	_game->checkWallCollisions(Position() , temp, this->_entity);
	this->SetPositionAbs(temp);

	return (this->Position());
}

D3DXVECTOR3 CameraComponent::Strafe(float numUnits)
{
	D3DXVECTOR3 strafeVec;
	D3DXVECTOR3 lookDirection;
	D3DXVECTOR3 yaxis(0,1,0);
	D3DXVECTOR3 newPos;
	lookDirection.x = this->_lookAtVector.x;
	lookDirection.y = 0;
	lookDirection.z = this->_lookAtVector.z;
	


	//The strafe vector will be the cross between the forward direction and the y axis
	if(numUnits > 0)
	{
		D3DXVec3Cross(&strafeVec, &lookDirection , &yaxis);
	}
	else
	{
		D3DXVec3Cross(&strafeVec, &yaxis, &lookDirection);
	}

	D3DXVec3Normalize(&strafeVec, &strafeVec);
	strafeVec *= numUnits;

	if (numUnits > 0)
	{
		newPos = _game->checkWallCollisions(Position() , Position() + strafeVec, this->_entity);
		this->SetPositionAbs(newPos);
	}
	else
	{	
		newPos = _game->checkWallCollisions(Position() , Position() - strafeVec, this->_entity);
		this->SetPositionAbs(newPos);
	}


	D3DXVec3Normalize(&this->_lookAtVector, &this->_lookAtVector);
	//position.x = position.x + lookAtVector.x * magnitude;
	//position.y = position.y + lookAtVector.y * magnitude;
	//position.z = position.z + lookAtVector.z * magnitude;

	return (this->Position());
}


void CameraComponent::SetCamera(D3DXVECTOR3 position, D3DXVECTOR3 lookAtPoint, D3DXVECTOR3 upVector)
{
	this->SetPositionAbs(position);
	this->_lookAtVector = lookAtPoint - position;
	this->_upVector = upVector;
	D3DXVec3Normalize(&this->_upVector, &this->_upVector);
	D3DXVec3Normalize(&this->_lookAtVector, &this->_lookAtVector);
}

float CameraComponent::GetSpeed(void)
{
	return(this->_speed);
}

float CameraComponent::GetStrafeSpeed(void)
{
	return this->_strafeSpeed;
}

int CameraComponent::UpdateSpeed(float speed)
{
	if( this->_speed > 1 || speed > 0)
		this->_speed += speed;	

	return 0;
}

void CameraComponent::updateOrientation(D3DXVECTOR3 rotVector, float angleRad)
{
	D3DXVECTOR3 xaxis(0.0,0.0,0.0);
	float rc = 0.0;

	// create rotation matrix
	D3DXMatrixRotationAxis(&this->_rotMat, &rotVector,angleRad);

	rc = D3DXVec3Dot(&this->_upVector,&this->_lookAtVector);


	// rotate the camera (up vector and/or looAtVector)
	D3DXVec3TransformCoord(&this->_upVector, &this->_upVector, &this->_rotMat);
	D3DXVec3TransformCoord(&this->_lookAtVector, &this->_lookAtVector, &this->_rotMat);

	rc = D3DXVec3Dot(&this->_upVector,&this->_lookAtVector);

	// update the upVector
	D3DXVec3Cross(&xaxis, &this->_upVector, &this->_lookAtVector);
		
	rc = D3DXVec3Dot(&xaxis,&this->_upVector);
	rc = D3DXVec3Dot(&xaxis,&this->_lookAtVector);
	rc = D3DXVec3Dot(&this->_upVector,&this->_lookAtVector);

	D3DXVec3Cross(&this->_upVector,  &this->_lookAtVector, &xaxis);
		
	rc = D3DXVec3Dot(&xaxis,&this->_upVector);
	rc = D3DXVec3Dot(&xaxis,&this->_lookAtVector);
	rc = D3DXVec3Dot(&this->_upVector,&this->_lookAtVector);

	D3DXVec3Normalize(&this->_upVector, &this->_upVector);
	D3DXVec3Normalize(&this->_lookAtVector, &this->_lookAtVector);
		
	rc = D3DXVec3Dot(&this->_upVector,&this->_lookAtVector);

	D3DXVECTOR3 entityDirection = D3DXVECTOR3(this->_lookAtVector.x, 0, this->_lookAtVector.z);
	
}

float CameraComponent::getHeightOfPlayer()
{
	return heightOfPlayer;
}