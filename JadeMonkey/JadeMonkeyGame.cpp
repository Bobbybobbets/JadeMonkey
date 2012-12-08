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
#include <stdio.h>
#include "GameEntity.h"
#include "EntityFactory.h"
#include "MainEntityFactory.h"
#include "CollisionComponent.h"
#include "WallPointCollisionComponent.h"
#include <sstream>

using namespace std;

JadeMonkeyGame::JadeMonkeyGame(HINSTANCE hInstance, char* gameName, EntityFactory* fact):
	Game(hInstance, gameName), 
	x(0), 
	fontCourier(NULL)
{
	this->_entityFactory = fact;
	displayMessage = false;
	this->Restart = false;


	int x=0;
	int horizStep = 30;
	for( x = 0 ; x < 3 ; x++) 
	{
		hearts[x] = new Heart(this, D3DXVECTOR3(75 + horizStep * x, getWndHeight() - 100, 0));
	}
}

JadeMonkeyGame::~JadeMonkeyGame(void)
{
	if (fontCourier != NULL) {
		fontCourier->Release();
		fontCourier = NULL;
	}
	
	Game::~Game();
}

PlayerComponent* JadeMonkeyGame::GetPlayer(void)
{
	return this->_entitiesContainer.MainCharacter;
}

int JadeMonkeyGame::Update(long time)
{
	int rc = 0;

	if(this->Restart)
	{
		this->Initialize();	
	}

	// add code to update the game state

	// poll the input
	mInput->poll();
	

	// check if escape key was pressed
	if (mInput->keyboardPressed(DIK_ESCAPE)) {
		rc = 1;
	} 

		for(vector<GameEntity*>::iterator it = this->_entitiesContainer.Entities.begin(); 
			it < this->_entitiesContainer.Entities.end(); 
			it++)
		{
			if((*it)->IsActive())
			{
				(*it)->Update(time);
			}
		}

		for(vector<GameEntity*>::iterator it = this->_entitiesContainer.EntitiesToRemove.begin();
			it < this->_entitiesContainer.EntitiesToRemove.end();
			it++)
		{
			delete((*it));
			this->_entitiesContainer.Entities.erase(it);
		}

		for(vector<GameEntity*>::iterator it = this->_entitiesContainer.EntitiesToAdd.begin();
			it < this->_entitiesContainer.EntitiesToAdd.end();
			it++)
		{
			this->_entitiesContainer.Entities.push_back((*it));
		}

		this->_entitiesContainer.EntitiesToAdd.clear();
		this->_entitiesContainer.EntitiesToRemove.clear();
	

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
	//D3DXMatrixLookAtLH(&viewMat,&D3DXVECTOR3(50,1000,50), &D3DXVECTOR3(500,0,500), &D3DXVECTOR3(0,1,0));

	RECT textbox1;
	textbox1.bottom=20;
	textbox1.right=300;
	textbox1.left=0;
	textbox1.top=0;
	// set the camera matrix
	//cam.getViewMatrix(&viewMat);  // nuss1
	this->_entitiesContainer.Cameras[0]->GetViewMatrix(&viewMat);
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

	//clear z buffer
	md3dDev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
	md3dDev->BeginScene();    // begins the 3D scene	

	switch (state ) 
	{
	case 4:
			for(vector<GameEntity*>::iterator it = this->_entitiesContainer.Entities.begin(); 
				it < this->_entitiesContainer.Entities.end(); 
				it++)
			{
				if((*it)->IsActive())
				{
					(*it)->Draw(time);
				}
			}
	
			if(displayMessage && GetTickCount() - lastMessage < 5000)
			{
				textbox1.left = getWndWidth()/3;
				textbox1.top = getWndHeight()/3;
				textbox1.bottom = getWndHeight()/2 + 100;
				textbox1.right = getWndWidth()/3 + 400;

				LPCTSTR str2 = message.c_str();
				fontCourier->DrawText(NULL, str2, -1, &textbox1, DT_LEFT | DT_VCENTER, D3DCOLOR_ARGB(255, 255, 0, 0));
			}
			else
				displayMessage = false;
			break;
	// Died
	case 1:
		RenderDeadScreen();
		break;
	// Won
	case 2:
		RenderWonScreen();
		break;
	// Lost
	case 3:
		RenderLostScreen();
		break;
	// start
	case 0:
		RenderStartScreen();
		break;
	}

	RenderUI();

	for( int x = 0 ; x < GetPlayer()->getLives() ; x++)
	{
		hearts[x]->Draw(time);
	}

    md3dDev->EndScene();    // ends the 3D scene

    rc = md3dDev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
	if (rc != D3D_OK) {
		i++;
	}

	 return 0;
 }

 void JadeMonkeyGame::RenderStartScreen()
 {
	RECT textbox1;

	textbox1.left = 0;
	textbox1.bottom = getWndHeight()/2;
	textbox1.top = getWndHeight()/2 - 150;
	textbox1.right = getWndWidth();

	stringstream ss2;//create a stringstream
	LPCTSTR str2 = screenMessage.c_str();
	uiFont->DrawText(NULL, str2, -1, &textbox1, DT_LEFT | DT_VCENTER, D3DCOLOR_ARGB(255, 255, 255, 0));

 }

void JadeMonkeyGame::RenderDeadScreen()
 {
	RECT textbox1;
	textbox1.left = getWndWidth()/2 - 250;
	textbox1.bottom = getWndHeight()/2;
	textbox1.top = getWndHeight()/2 - 150;
	textbox1.right = textbox1.left + 500;

	stringstream ss2;//create a stringstream
	LPCTSTR str2 = screenMessage.c_str();
	uiFont->DrawText(NULL, str2, -1, &textbox1, DT_LEFT | DT_VCENTER, D3DCOLOR_ARGB(255, 255, 255, 0));
 }
void JadeMonkeyGame::RenderWonScreen()
 {
	RECT textbox1;
	textbox1.left =0;
	textbox1.bottom = getWndHeight()/2;
	textbox1.top = getWndHeight()/2 - 150;
	textbox1.right = getWndWidth();

	stringstream ss2;//create a stringstream
	LPCTSTR str2 = screenMessage.c_str();
	uiFont->DrawText(NULL, str2, -1, &textbox1, DT_LEFT | DT_VCENTER, D3DCOLOR_ARGB(255, 255, 255, 0));
 }
void JadeMonkeyGame::RenderLostScreen()
 {
	RECT textbox1;
	textbox1.left = getWndWidth()/2 - 300;
	textbox1.bottom = getWndHeight()/2;
	textbox1.top = getWndHeight()/2 - 150;
	textbox1.right = textbox1.left + 650;

	stringstream ss2;//create a stringstream
	LPCTSTR str2 = screenMessage.c_str();
	uiFont->DrawText(NULL, str2, -1, &textbox1, DT_LEFT | DT_VCENTER, D3DCOLOR_ARGB(255, 255, 255, 0));
 }
void JadeMonkeyGame::RenderUI()
{
	RECT textbox1;
	RECT textbox2;

	textbox1.left = 0;
	textbox1.bottom = getWndHeight() - 50;
	textbox1.top = getWndHeight() - 100;
	textbox1.right = 250;

	textbox2.left = getWndWidth() - 220;
	textbox2.bottom = getWndHeight() - 50;
	textbox2.right = getWndWidth() - 10;
	textbox2.top = getWndHeight() - 100;


	string numberLives = "Lives:";	
	LPCTSTR str2 = numberLives.c_str();
	uiFont->DrawText(NULL, str2, -1, &textbox1, DT_LEFT | DT_VCENTER, D3DCOLOR_ARGB(255, 255, 255, 0));

	stringstream ss3;//create a stringstream
	ss3 << "Keys Collected: " << numKeys;
	string numberKeys;
	numberKeys = ss3.str();//return a string with the contents of the stream
	LPCTSTR str3 = numberKeys.c_str();
	uiFont->DrawText(NULL, str3, -1, &textbox2, DT_LEFT | DT_VCENTER, D3DCOLOR_ARGB(255, 255, 255, 0));

}

GameEntitiesContainer* JadeMonkeyGame::GetEntitiesContainer(void)
{
	return &(this->_entitiesContainer);
}

int JadeMonkeyGame::Initialize(void)
{
	int rc = 0;
	rc = Game::Initialize();

	//cube v;

	// set the intial location of the camera
	//cam.setCamera(D3DXVECTOR3(0,70,0), D3DXVECTOR3(50,70,50), D3DXVECTOR3(0,1,0));
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


	//create game entities
	this->_entitiesContainer = this->_entityFactory->GetContainer(this);

	//intialize game entities
	for(vector<GameEntity*>::iterator it = this->_entitiesContainer.Entities.begin(); 
		it < this->_entitiesContainer.Entities.end(); 
		it++)
	{
		(*it)->Initialize();
	}

	return 0;

err:
	return(rc);
}

int JadeMonkeyGame::LoadContent(void)
{
	return 0;
}

D3DXVECTOR3 JadeMonkeyGame::checkFloorCollisions(D3DXVECTOR3 start, D3DXVECTOR3 end, GameEntity* entity)
{
	D3DXVECTOR3 toReturn;
	for(vector<GameEntity*>::iterator it = this->_entitiesContainer.Floors.begin(); 
		it < this->_entitiesContainer.Floors.end(); 
		it++)
	{
		if( (*it)->getCollisionComponents().size() != 0)
		{
			toReturn = (*it)->getCollisionComponents().at(0)->checkCollision(start,end, entity);

			if(toReturn != end)
				return toReturn;
		}
	}
	return end;
}

D3DXVECTOR3 JadeMonkeyGame::checkWallCollisions(D3DXVECTOR3 start, D3DXVECTOR3 end, GameEntity* entity)
{
	D3DXVECTOR3 toReturn;

	for(vector<GameEntity*>::iterator it = this->_entitiesContainer.Walls.begin(); 
		it < this->_entitiesContainer.Walls.end(); 
		it++)
	{
		if( (*it)->getCollisionComponents().size() != 0)
		{
			toReturn = (*it)->getCollisionComponents().at(0)->checkCollision(start,end, entity);

			// Check to see if the vector returned doesn't equal the end coordinates (would only happen when colliding with something)
			if(toReturn != end)
				return toReturn;
			
		}
	}
	return end;
}

void JadeMonkeyGame::setMessage(string message) 
{
	this->message = message;
	lastMessage = GetTickCount();
	displayMessage = true;
}
