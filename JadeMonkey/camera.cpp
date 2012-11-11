
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


/******************************************************************/
/*
Purpose: camera constructor


Descripton: 

Return:


*/

#define MOUSE_SENSITIVITY_SCALE 1000

camera::camera(void): position(0.0,0.0,(float)-50.0), lookAtVector(0.0,0.0,1.0), upVector(0.0,1.0,0.0)
, speed((float)1.1)
, strafeSpeed(0.001)
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
	D3DXVECTOR3 rotVector(0.0,0.0,0.0);

	D3DXVec3Cross( &rotVector, &upVector, &lookAtVector);

	updateOrientation(rotVector , angleDeg);
	
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
	D3DXVECTOR3 rotVector(0.0,0.0,0.0);

	updateOrientation(upVector, angleDeg);

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
	//position.y = position.y + lookAtVector.y * magnitude;
	position.z = position.z + lookAtVector.z * magnitude;

	return (position);
}

D3DXVECTOR3 camera::strafe(float numUnits)
{
	D3DXVECTOR3 strafeVec;
	D3DXVECTOR3 lookDirection;
	D3DXVECTOR3 yaxis(0,1,0);
	lookDirection.x = lookAtVector.x;
	lookDirection.y = 0;
	lookDirection.z = lookAtVector.z;


	//The strafe vector will be the cross between the forward direction and the y axis
	D3DXVec3Cross(&strafeVec, &lookDirection , &yaxis);

	strafeVec.x += numUnits;
	strafeVec.z += numUnits;

	if (numUnits > 0)
		position += strafeVec;
	else
		position -= strafeVec;
//	lookAtVector.x = strafeVec.x;
//	lookAtVector.z = strafeVec.z;
	
	D3DXVec3Normalize(&lookAtVector, &lookAtVector);
	//position.x = position.x + lookAtVector.x * magnitude;
	//position.y = position.y + lookAtVector.y * magnitude;
	//position.z = position.z + lookAtVector.z * magnitude;

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
	float rc = 0.0;

	// create rotation matrix
	D3DXMatrixRotationAxis(&rotMat, &rotVector,angleRad);

	rc = D3DXVec3Dot(&upVector,&lookAtVector);


	// rotate the camera (up vector and/or looAtVector)
	D3DXVec3TransformCoord(&upVector, &upVector, &rotMat);
	D3DXVec3TransformCoord(&lookAtVector, &lookAtVector, &rotMat);

	rc = D3DXVec3Dot(&upVector,&lookAtVector);

	// update the upVector
	D3DXVec3Cross(&xaxis, &upVector, &lookAtVector);
		
	rc = D3DXVec3Dot(&xaxis,&upVector);
	rc = D3DXVec3Dot(&xaxis,&lookAtVector);
	rc = D3DXVec3Dot(&upVector,&lookAtVector);

	D3DXVec3Cross(&upVector,  &lookAtVector, &xaxis);
		
	rc = D3DXVec3Dot(&xaxis,&upVector);
	rc = D3DXVec3Dot(&xaxis,&lookAtVector);
	rc = D3DXVec3Dot(&upVector,&lookAtVector);

	D3DXVec3Normalize(&upVector, &upVector);
	D3DXVec3Normalize(&lookAtVector, &lookAtVector);
		
	rc = D3DXVec3Dot(&upVector,&lookAtVector);


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

	//lookAtVector = D3DXVECTOR3(.5,-.15,.5);
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
	D3DXVec3Normalize(&this->upVector, &this->upVector);
	D3DXVec3Normalize(&this->lookAtVector, &this->lookAtVector);

}
// change the speed of the camera motion
int camera::updateSpeed(float speed)
{
	if( this->speed > 1 || speed > 0)
		this->speed += speed;	

	return 0;
}

void camera::changeLookAt(D3DXVECTOR3 delta) {
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
	D3DXVec3Cross(&xaxis, &upVector, &lookAtVector);
	D3DXMatrixRotationAxis(&rotMat2, &xaxis,delta.y);

	// Compound the two rotation matrices
	rotMat = rotMat2 *  rotMat1 ;
	
	// Transform the upvector and lookatvector based on the rotation matrix
	D3DXVec3TransformCoord(&upVector, &upVector, &rotMat);
	D3DXVec3TransformCoord(&lookAtVector, &lookAtVector, &rotMat);

	// Ensure that the magnitudes are less than 1
	D3DXVec3Normalize(&this->upVector, &this->upVector);
	D3DXVec3Normalize(&this->lookAtVector, &this->lookAtVector);

}

float camera::getSpeed(void)
{
	return(speed);
}

float camera::getStrafeSpeed(void)
{
	return strafeSpeed;
}