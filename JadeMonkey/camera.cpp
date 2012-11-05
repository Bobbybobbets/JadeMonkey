
//=============================================================================
// camera.cpp 
//
//Author: Doron Nussbaum (C) 2011 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. demonstarte the usage of a camera
//
//
// Description:
//--------------
// A simple application that demonstrates how to crete and use a camera 
//
//
// License
//--------------
//
// Code can be used for instructional and educational purposes and for assignments in the gaming courses at 
// the School of Compuer Science at Carleton University.
// Usage of code for other purposes is not allowed without a given permission by the author.
//
//
// Disclaimer
//--------------
//
// The code is provided as is without any warranty

//=============================================================================


#include "StdAfx.h"
#include "camera.h"
#include <math.h>

/******************************************************************/
/*
Purpose: camera constructor


Descripton: 

Return:


*/

camera::camera(void): position(0.0,0.0,-50.0), lookAtVector(0.0,0.0,1.0), upVector(0.0,1.0,0.0)
, speed(0.2)
{

}

/******************************************************************/
/*
Purpose: camera destructor


Descripton: 

Return:


*/
camera::~camera(void)
{
}


/******************************************************************/
/*
Purpose: change the orientation of the camera (roll transformation)


Descripton: 

Return:
1 - if failed
0 - if successful

*/


int camera::roll(float angleDeg)
{
	float angleRad = D3DXToRadian(angleDeg);
	D3DXVECTOR3 rotVector(0.0,0.0,0.0);


	// get rotation axis
	rotVector = lookAtVector;

	updateOrientation(rotVector, angleRad);


	return 0;
}


/******************************************************************/
/*
Purpose: change the orientation of the camera (pitch transformation)


Descripton: 

Return:
1 - if failed
0 - if successful

*/

int camera::pitch(float angleDeg)
{
	float angleRad = D3DXToRadian(angleDeg);
	D3DXVECTOR3 pitchVector(0.0,0.0,0.0);

	D3DXVec3Cross( &pitchVector , &upVector, &lookAtVector);

	updateOrientation( pitchVector , angleRad);

	return 0;
}

/******************************************************************/
/*
Purpose: change the orientation of the camera (yaw transformation)


Descripton: 

Return:
1 - if failed
0 - if successful

*/



int camera::yaw(float angleDeg)
{
	float angleRad = D3DXToRadian(angleDeg);
	D3DXVECTOR3 yawVector(0.0,0.0,0.0);

	// get rotation axis
	yawVector = upVector;

	updateYawOrientation(yawVector, angleRad);


	return 0;
}

/******************************************************************/
/*
Purpose: obtains the current position of the camera


Descripton: 

Return:
D3DXVECTOR3 - camera position

*/

D3DXVECTOR3 camera::getPosition(void)
{
	return (position);
}


/******************************************************************/
/*
Purpose: obtains the lookAt point of the camera


Descripton: 

Return:
D3DXVECTOR3 - camera lookAt point

*/


D3DXVECTOR3 camera::getLookAtPoint(void)
{
	return (position + lookAtVector);
}

/******************************************************************/
/*
Purpose: obtains the camera's up vector


Descripton: 

Return:
D3DXVECTOR3 - camera upVector

*/



D3DXVECTOR3 camera::getUpVector(void)
{
	return (upVector);
}


/******************************************************************/
/*
Purpose: changes the camera's position relative to its current position


Descripton: 

Return:
0 - success

*/


int camera::changePoitionDelta(float dx, float dy, float dz)
{
	position.x += dx;
	position.y += dy;
	position.z += dz;

	return 0;
}


/******************************************************************/
/*
Purpose: changes the camera's position relative to its current position


Descripton: 

Return:
0 - success

*/


int camera::changePositionDelta(D3DXVECTOR3 *dv)
{
	position += *dv;
	return 0;
}

/******************************************************************/
/*
Purpose: changes the camera's position to a new position


Descripton: 

Return:
0 - success

*/


int camera::changeAbsPoition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	return 0;
}

/******************************************************************/
/*
Purpose: changes the camera's position to a new position


Descripton: 

Return:
0 - success

*/

int camera::changeAbsPosition(D3DXVECTOR3 *v)
{
	position = *v;
	return 0;
}

/******************************************************************/
/*
Purpose: changes the camera's position along the LootAt vector


Descripton: move the camera forward by the numUnits along the looAtVector

Return:
the new position

*/


D3DXVECTOR3 camera::moveForward(float numUnits)
{
	float magnitude;
	magnitude = numUnits;

	position.x = position.x + lookAtVector.x * magnitude;
	position.y = position.y + lookAtVector.y * magnitude;
	position.z = position.z + lookAtVector.z * magnitude;

	return (position);
}

/******************************************************************/
/*
Purpose: 


Descripton: 

Return:


*/


int camera::updateOrientation(D3DXVECTOR3 rotVector, float angleRad)
{

	D3DXVECTOR3 xaxis(0.0,0.0,0.0);

	// create rotation matrix
	D3DXMatrixRotationAxis(&rotMat, &rotVector,angleRad);

	// rotate the camera (up vector and/or looAtVector)
	D3DXVec3TransformCoord(&upVector, &upVector, &rotMat);
	D3DXVec3TransformCoord(&lookAtVector, &lookAtVector, &rotMat);

	// update the upVector
	D3DXVec3Cross(&xaxis, &upVector, &lookAtVector);
	D3DXVec3Cross(&upVector,  &lookAtVector, &xaxis);
	D3DXVec3Normalize(&upVector, &upVector);
	D3DXVec3Normalize(&lookAtVector, &lookAtVector);

	return 0;
}


int camera::updateYawOrientation(D3DXVECTOR3 rotVector, float angleRad)
{

	D3DXVECTOR3 xaxis(0.0,0.0,0.0);

	// create rotation matrix
	D3DXMatrixRotationAxis(&rotMat, &rotVector,angleRad);

	// rotate the camera (up vector and/or looAtVector)
	D3DXVec3TransformCoord(&upVector, &upVector, &rotMat);
	D3DXVec3TransformCoord(&lookAtVector, &lookAtVector, &rotMat);

	// update the upVector
//	D3DXVec3Cross(&xaxis, &upVector, &lookAtVector);
//	D3DXVec3Cross(&lookAtVector,  &upVector, &xaxis);
	D3DXVec3Normalize(&upVector, &upVector);
	D3DXVec3Normalize(&lookAtVector, &lookAtVector);

	return 0;
}

/******************************************************************/
/*
Purpose: obtains the view transformation matrix


Descripton: 

Return:
the transformation matrix

*/



D3DMATRIX * camera::getViewMatrix(D3DXMATRIX * viewMatrix)
{
	D3DXVECTOR3 lookAt;
	
	lookAt = position+lookAtVector;

	return(D3DXMatrixLookAtLH(viewMatrix, &position,&lookAt, &upVector));
}

/******************************************************************/
/*
Purpose: set the camera parameters


Descripton: 

Return:


*/


void camera::setCamera(D3DXVECTOR3 position, D3DXVECTOR3 lookAtPoint, D3DXVECTOR3 upVector)
{
	this->position = position;
	this->lookAtVector = lookAtPoint - position;
	this->upVector = upVector;
	lookAtVector.x = 0.0;
	lookAtVector.y = 0.0;
	lookAtVector.z = 1.0;
	D3DXVec3Normalize(&this->upVector, &this->upVector);
	D3DXVec3Normalize(&this->lookAtVector, &this->lookAtVector);
}
// change the speed of the camera motion
int camera::updateSpeed(float speed)
{
	this->speed += speed;
	return 0;
}

float camera::getSpeed(void)
{
	return(speed);
}


