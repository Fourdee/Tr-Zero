//-----------------------------------------------------------------
// About:
//
// name: "Game_Input_xbox360controller.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
// usage: create the xbox 360 controller
//		  update it's basic params - thunbsticks and triggers
//
// device input: xbox 360 controller
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Input_xbox360controller.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - INTPUT - XBOX 360 CONTROLLER - CONSTRUCTORS
///*****************************************************************
Game_Input_xbox360controller::Game_Input_xbox360controller(void)
{
	//-------------------------------------------------------------
	GamepadsConnected = 0;
	//---------------------------------------------------------
	//triggers
	gXBox360Controller_TriggerLeft = 0;
	gXBox360Controller_TriggerRight = 0;
	//---------------------------------------------------------
	//thumbsticks
	gXBox360Controller_ThumbStickLeftX = 0;
	gXBox360Controller_ThumbStickLeftY = 0;
	gXBox360Controller_ThumbStickRightX = 0;
	gXBox360Controller_ThumbStickRightY = 0;
	//---------------------------------------------------------
	//Buttons
	bAcell = false;
	bBreak = false;
	bBoost = false;
	bCamera = false;
	bColour = false;
	bStart = false;
	bSelect = false;
	bPrimary = false;
	bSecondary = false;
	bUtility = false;
	//-------------------------------------------------------------
}

Game_Input_xbox360controller::~Game_Input_xbox360controller(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - INTPUT - XBOX 360 CONTROLLER - CREATE
///*****************************************************************
void Game_Input_xbox360controller::Create(void)
{
	//-------------------------------------------------------------
	//create xbox 360 controller
	Gamepad = iGamepadXbox360Create();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - INTPUT - XBOX 360 CONTROLLER - UPDATE
///*****************************************************************
void Game_Input_xbox360controller::Update(void)
{
	//-------------------------------------------------------------
	GamepadsConnected = iGamepadXbox360ConnectedCount();
	//-------------------------------------------------------------
	if(GamepadsConnected > 0)
	{
		//-----------------------------------------------------
		//triggers - return value from 0-255
		gXBox360Controller_TriggerLeft = iGamepadXbox360TriggerLeft(Gamepad);
		gXBox360Controller_TriggerRight = iGamepadXbox360TriggerRight(Gamepad);
		//-----------------------------------------------------
		//thumbsticks - returns values between - (min -32768, max 32768)
		gXBox360Controller_ThumbStickLeftX = iGamepadXbox360ThumbStickLeftX(Gamepad);
		gXBox360Controller_ThumbStickLeftY = iGamepadXbox360ThumbStickLeftY(Gamepad);
		gXBox360Controller_ThumbStickRightX = iGamepadXbox360ThumbStickRightX(Gamepad);
		gXBox360Controller_ThumbStickRightY = iGamepadXbox360ThumbStickRightY(Gamepad);
		//-----------------------------------------------------
		//Buttons
		bAcell = iGamepadXbox360ButtonDown(Gamepad,GP_BUTTON_A);
		bBreak = iGamepadXbox360ButtonDown(Gamepad,GP_BUTTON_B);
		bBoost = iGamepadXbox360ButtonDown(Gamepad,GP_BUTTON_X);
		bCamera = iGamepadXbox360ButtonClick(Gamepad,GP_BUTTON_Y);
		//bColour = iGamepadXbox360ButtonClick(Gamepad,GP_BUTTON_SHOULDER_RIGHT);
		bColour = iGamepadXbox360ButtonDown(Gamepad,GP_BUTTON_SHOULDER_RIGHT);
		bStart = iGamepadXbox360ButtonClick(Gamepad,GP_BUTTON_START);
		bSelect = iGamepadXbox360ButtonClick(Gamepad,GP_BUTTON_BACK);

		bPrimary = false;
		if(iGamepadXbox360TriggerRight(Gamepad) > 50)
		{
			bPrimary = true;
		}

		bSecondary = false;
		if(iGamepadXbox360TriggerLeft(Gamepad) > 50)
		{
			bSecondary = true;
		}

		bUtility = iGamepadXbox360ButtonDown(Gamepad,GP_BUTTON_SHOULDER_LEFT);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - INTPUT - XBOX 360 CONTROLLER - DESTROY
///*****************************************************************
void Game_Input_xbox360controller::Destroy(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}