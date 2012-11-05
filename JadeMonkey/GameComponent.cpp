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


#include "StdAfx.h"
#include "GameComponent.h"

GameComponent::GameComponent(Game* game):mIndBuf(NULL), mVtxBuf(NULL)
{
	this->_game = game;
}

GameComponent::~GameComponent(void)
{
}

int GameComponent::Initialize(void)
{
	return 0;
}

int GameComponent::Update(long time)
{
	return 0;
}

