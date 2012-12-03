//=============================================================================
// myGame.h 
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

#pragma once
#include "Game.h"
#include "camera.h"
#include <vector>
#include "GameEntitiesContainer.h"
#include "EntityFactory.h"

using namespace std;

class JadeMonkeyGame : public Game
{
public:
	JadeMonkeyGame(HINSTANCE hInstance, char* gameName, EntityFactory* fact);
	~JadeMonkeyGame(void);
	virtual int Update(long time) override;
	virtual int Draw(long time) override;
	virtual int Initialize(void) override;
	virtual int LoadContent(void) override;
	virtual D3DXVECTOR3 checkFloorCollisions(D3DXVECTOR3 start, D3DXVECTOR3 end, GameEntity* entity) override;
	virtual D3DXVECTOR3 checkWallCollisions(D3DXVECTOR3 start, D3DXVECTOR3 end, GameEntity* entity) override;
	// variables used to position the text on the screen
	int x;	// x location of the string to be drawn
	int y;	// y location of the string to be drawn
	int dx;		// change in x at each frame
	int dy;		// change in y at each frame
	RECT textBox;	// rectangle for the text

	char s[1024]; // string to be drawn

	 
	LPD3DXFONT fontCourier; // font to be used 

	virtual void setMessage(string message) override;

private:
	GameEntitiesContainer _entitiesContainer;
	EntityFactory* _entityFactory;
	string message;
	DWORD lastMessage;
	bool displayMessage;

	RECT textbox;
};
