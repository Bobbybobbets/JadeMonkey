//=============================================================================
// flight_sim.cpp
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

//=============================================================================//

#include "stdafx.h"
#include "JadeMonkey.h"
#include "JadeMonkeyGame.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR		 pCmdLine,
                   int		 nCmdShow)
{

	// create the game
	JadeMonkeyGame* jadeMonkeyGame = new JadeMonkeyGame(hInstance, "The Jade Monkey");

	// initialize the game
	// note that this is done via a virtual function.  Thus there is no need to update this function
	jadeMonkeyGame->Initialize();


	jadeMonkeyGame->gameLoop();



}



