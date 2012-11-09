//=============================================================================
// JadeMonkeyGame.cpp
//
//Author: Doron Nussbaum (C) 2011 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. demonstrates the usage of the gameIO and gameApp framework 
//
//
//
// Description:
//--------------
// A simple application that draws text on the screen.  
// The application draws a text on the screen.  The text shows the text location 
// and the current frame number.  The text scrolls on the screen.
// The text scrolling changes direction when:
// a. the text reaches a boundary of the window
//
// b. the user presses the left mouse button - the left mouse button changes x-direction
// and the right mouse button changes the y-direction
//
// c. The escape key leaves the application
//
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
#include "JadeMonkeyGame.h"
#include "meshSurface.h"
#include <stdio.h>

using namespace std;

JadeMonkeyGame::JadeMonkeyGame(HINSTANCE hInstance, char* gameName):
	Game(hInstance, gameName), 
	x(0), 
	fontCourier(NULL)
{
	ground = new meshSurface(100, 100, 20,20,this);
	ground->setScale(1.0,4.0,1.0);
}

JadeMonkeyGame::~JadeMonkeyGame(void)
{
	if (fontCourier != NULL) {
		fontCourier->Release();
		fontCourier = NULL;
	}
	
	Game::~Game();
}




int JadeMonkeyGame::Update(long time)
{
	int rc = 0;

	// add code to update the game state


	// poll the input
	mInput->poll();
	
	// check if escape key was pressed
	if (mInput->keyboardPressed(DIK_ESCAPE)) {
		rc = 1;
	} else {
		if (mInput->keyboardPressed(DIK_LEFT)) {
			// move left
			cam.yaw(-0.5);
			rc = 0;
		}
		if (mInput->keyboardPressed(DIK_RIGHT)) {
			// move right
			cam.yaw(0.5);
			rc = 0;
		}
		if (mInput->keyboardPressed(DIK_UP)) {
			// pull up
			cam.pitch(0.2);
			rc = 0;
		}
		if (mInput->keyboardPressed(DIK_DOWN)) {
			// dive
			cam.pitch(-0.2);
			rc = 0;
		}
		if (mInput->keyboardPressed(DIK_W)) {
			// speed up
			cam.updateSpeed( 0.02);
			rc = 0;
		}
		if (mInput->keyboardPressed(DIK_S)) {
			// slow down
			if( cam.getSpeed() >= -0.2 )
				cam.updateSpeed( -0.02);
			rc = 0;
		}
		if (mInput->keyboardPressed(DIK_A)) {
			//roll left
			cam.roll(0.2);  //CCW
			rc = 0;
		}
		if (mInput->keyboardPressed(DIK_D)) {
			// roll write
			cam.roll(-0.2);  //CW
			rc = 0;
		}
	}

		D3DXVECTOR3 delta = mInput->mouseDelta();
		if (delta.x != 0 && delta.y != 0) {
			this->cam.changeLookAt(delta);
			rc +=0;
		}

	// move the camera
//	cam.moveForward(cam.getSpeed());



	return(rc);
}
/**************************************************************************/



 // renders all objects
int JadeMonkeyGame::Draw(long time)
{

	int i = 0;
	int rc;
	static float step = 1;
	float rad = 0;
	D3DXMATRIX worldMat, viewMat, matTransform, matProjection, matScale, matTranslate,  matRotation;


	//// set up the camera location
	//D3DXMatrixLookAtLH(&viewMat, 
	//&D3DXVECTOR3(40.0f, 40.0f, 40.0f), // camera loc
	//&D3DXVECTOR3(150.0f, 0.0f, -150.0f),  // look-at target 
	//&D3DXVECTOR3(0.0f, 1.0f, 0.0f)); // up Veotor
	D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(50,1000,50), &D3DXVECTOR3(500,0,500), &D3DXVECTOR3(0,1,0));

	RECT textbox1;
		textbox1.bottom=20;
	textbox1.right=300;
	textbox1.left=0;
	textbox1.top=0;
	// set the camera matrix
	cam.getViewMatrix(&viewMat);  // nuss1
	// inform direct3d about the view transformation
	rc = md3dDev->SetTransform(D3DTS_VIEW,&viewMat);

	//// set up the projection transformation
	//D3DXMatrixPerspectiveFovLH(&matProjection,  
	//	D3DXToRadian(80),			// field of view
	//	400/300, 					// aspect ratio
	//	1.0f, 1500.0f); 			// near and far planes

	getProjMat(&matProjection);
	// inform direc3d about the proejctions tranfsormation
	md3dDev->SetTransform(D3DTS_PROJECTION, &matProjection); 



    // clear the window to a deep blue
	rc = md3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);
	if (rc != D3D_OK) {
		i++;
	}
	
	md3dDev->BeginScene();    // begins the 3D scene
	
	ground->Draw(time);

    md3dDev->EndScene();    // ends the 3D scene

    rc = md3dDev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
	if (rc != D3D_OK) {
		i++;
	}

	 return 0;
 }



int JadeMonkeyGame::Initialize(void)
{
	int rc = 0;
	rc = Game::Initialize();

	//cube v;

	// set the intial location of the camera
	cam.setCamera(D3DXVECTOR3(-40,70,-40), D3DXVECTOR3(50,0,50), D3DXVECTOR3(0,1,0));
	//cam.setCamera(D3DXVECTOR3(0,0,1), D3DXVECTOR3(0,0,-1), D3DXVECTOR3(0,1,0));

	// initialize the projection matrix
	setProj(1.0,5000.0,D3DXToRadian(80),((float) this->mWndWidth)/this->mWndHeight);


	// create a font

	rc = D3DXCreateFont(md3dDev,
						10, // height of font
						0,	// use the default width
						FW_MEDIUM+50,
						//FW_NORMAL,	// normal font weight
						1, // no Mipmap
						FALSE, // italic
						DEFAULT_CHARSET, // default character set
						OUT_DEFAULT_PRECIS, // default precision
						DEFAULT_QUALITY, // default quality
						DEFAULT_PITCH ||FF_DONTCARE, // more defaults...
						"Courier",	// typeface “Courier"
						&fontCourier); 


	if (rc != S_OK) {
		rc = 1;
	}

	x = this->getWndWidth() / 2;
	y = this->getWndHeight() / 2;
	dx = 1;
	dy = 1;


	// get the dimension of the window

	// initialize a cube


	return 0;

err:
	return(rc);
}

int JadeMonkeyGame::LoadContent(void)
{
	return 0;
}
