//=============================================================================
// gameObtjec.h 
//
//Author: Doron Nussbaum (C) 2011 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. handles the common properties and functios of a game object 

//
// Description:
//--------------

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

#include "d3dx9.h"
#include "d3dx9math.h"
#include "IUpdateable.h"
#include "Game.h"



class GameComponent : public IUpdateable
{
	// functions
public:
	~GameComponent(void);
	GameComponent(Game* game);
	virtual int Initialize();
	virtual int Update(long time);

	//members
private:
	IDirect3DIndexBuffer9 *mIndBuf;
	IDirect3DVertexBuffer9 *mVtxBuf;
	Game* _game;

};
