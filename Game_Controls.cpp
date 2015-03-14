//-----------------------------------------------------------------
// About:
//
// name: "Game_Controls.cpp:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Controls.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - CONTROLS - CONSTRUCTORS
///*****************************************************************
Game_Controls::Game_Controls(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}

Game_Controls::~Game_Controls(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - CONTROLS - UPDATE
///*****************************************************************
void Game_Controls::Update(void)
{
	//-------------------------------------------------------------
	//update xbox 360 controller
	cGame_Input_xbox360controller.Update();
	//-------------------------------------------------------------
	//Update Pause State
	if(gRaceState==1)
	{
		Input_Action_Pause();
	}
	//-------------------------------------------------------------
	//Screenshot
	if(iKeyClick(DIK_F12))
	{
		//Check for existing files
		int current = 0;
		char Checker[1024];
		sprintf_s(Checker,"trzero_res\\#screenshots\\SS_%d.jpg",current);
		while(iFileExists(Checker))
		{
			current++;
			sprintf_s(Checker,"trzero_res\\#screenshots\\SS_%d.jpg",current);
		}
		//Save screenshot
		iScreenShotSave("trzero_res\\#screenshots\\SS.jpg",
						true,
						current,
						false,
						32,
						"jpg",
						false);	
	}
	//-------------------------------------------------------------
	//AUTO SCREENSHOT
	//static bool bTakeScreenShots = false;
	//static int time = 0;
	//static int current = 0;
	//if(iKeyClick(DIK_K))
	//{
	//	bTakeScreenShots ^=1;
	//}

	//if(bTakeScreenShots)
	//{
	//	time++;
	//	if(time==120)
	//	{
	//		iScreenShotSave("trzero_res\\#screenshots\\shot_.bmp",
	//						true ,
	//						current ,
	//						false ,
	//						32 ,
	//						"bmp" ,
	//						false );	
	//		time = 0;
	//		current++;
	//	}
	//}
	//-------------------------------------------------------------
	//Toggle 2D
	if(iKeyClick(DIK_F11))
	{
		gDisable2D = !gDisable2D;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - CONTROLS - Update_Feedback
///*****************************************************************
void Game_Controls::Update_Feedback(void)
{
	//-------------------------------------------------------------
	//Runs after Bikes have been processed
	//-------------------------------------------------------------
	//Xbox Motor Test
	if(cGame_Input_xbox360controller.GamepadsConnected>0)
	{
		iFloatTendTo2(gXbox360Controller_MotorLeft,0.0f,6.5f);
		iFloatTendTo2(gXbox360Controller_MotorRight,0.0f,6.5f);
		if(gXbox360Controller_Vibrate &&
			gBikesGo &&
			gRaceState==1)
		{
			//Motors inuse
			///Front Collision
			if(abs(cGame_Bike[gAi_Max_Count].Manager.fCollision_pz) > 0.01f)
			{
				gXbox360Controller_MotorLeft = iFloatInterpolate(abs(cGame_Bike[gAi_Max_Count].Manager.fCollision_pz),10.0f,400.0f,15000.0f,35000.0f);
			}
			else if(abs(cGame_Bike[gAi_Max_Count].Manager.fCollision_px) > 0.01f)
			{
				gXbox360Controller_MotorLeft = iFloatInterpolate(abs(cGame_Bike[gAi_Max_Count].Manager.fCollision_px),0.1f,0.7f,0.0f,15000.0f);
			}
			else if(cGame_Bike[gAi_Max_Count].Weapons.bBeingHit)
			{
				gXbox360Controller_MotorLeft = 7500.0f;
			}
			///Charge
			//gXbox360Controller_MotorRight = iFloatInterpolate(abs(cGame_Bike[gAi_Max_Count].fSteering),1.0f,gPlayer_Steering_Output_Max,0.0f,12000.0f);		
			if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryProjectileAliveTime==1)
			{
				gXbox360Controller_MotorRight = 41000.0f;
			}
			else if(cGame_Bike[gAi_Max_Count].Weapons.bSecondaryWeaponCharging)
			{
				gXbox360Controller_MotorRight = iFloatInterpolate((float)cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponChargeTime,0.0f,(float)cGame_Bike[gAi_Max_Count].Weapons.SecondaryWeaponChargeTimeMax,0.0f,13000.0f);
			}
			
			iFloatCap(gXbox360Controller_MotorLeft,0.0f,65535.0f);
			iFloatCap(gXbox360Controller_MotorRight,0.0f,65535.0f);
			iGamepadXbox360RumbleLeftMotorSet(cGame_Input_xbox360controller.Gamepad,(int)gXbox360Controller_MotorLeft);
			iGamepadXbox360RumbleRightMotorSet(cGame_Input_xbox360controller.Gamepad,(int)gXbox360Controller_MotorRight);
		}
		else
		{
			//Reset
			gXbox360Controller_MotorLeft = 0.0f;
			gXbox360Controller_MotorRight = 0.0f;
			iGamepadXbox360RumbleLeftMotorSet(cGame_Input_xbox360controller.Gamepad,0);
			iGamepadXbox360RumbleRightMotorSet(cGame_Input_xbox360controller.Gamepad,0);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - BIKE - ACCELLERATION
///*****************************************************************
bool Game_Controls::Input_Bike_Acceleration(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	if(iKeyDown(gKeyboard_Bike_Accelerate) || 
		cGame_Input_xbox360controller.bAcell)
	{
		bState = true;
	}

	if(gTextInputLock)
	{
		bState = false;
	}
	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - BIKE - BREAK
///*****************************************************************
bool Game_Controls::Input_Bike_Break(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	if(iKeyDown(gKeyboard_Bike_Break) || 
		cGame_Input_xbox360controller.bBreak)
	{
		bState = true;
	}

	if(gTextInputLock)
	{
		bState = false;
	}

	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - BIKE - BOOST
///*****************************************************************
bool Game_Controls::Input_Bike_Boost(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	if(iKeyDown(gKeyboard_Bike_Boost) || 
		cGame_Input_xbox360controller.bBoost)
	{
		bState = true;
	}

	if(gTextInputLock)
	{
		bState = false;
	}

	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - BIKE - PRIMARY WEAPON
///*****************************************************************
bool Game_Controls::Input_Bike_PrimaryWeapon(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//-------------------------------------------------------------
	if(iKeyDown(gKeyboard_Bike_PrimaryWeapon) || 
		cGame_Input_xbox360controller.bPrimary ||
		iMouseButtonDown(DIK_LMB))
	{
		bState = true;
	}

	if(gTextInputLock)
	{
		bState = false;
	}

	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - BIKE - SECONDARY WEAPON
///*****************************************************************
bool Game_Controls::Input_Bike_SecondaryWeapon(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//-------------------------------------------------------------
	if(iKeyDown(gKeyboard_Bike_SecondaryWeapon) || 
		cGame_Input_xbox360controller.bSecondary ||
		iMouseButtonDown(DIK_RMB))
	{
		bState = true;
	}

	if(gTextInputLock)
	{
		bState = false;
	}

	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - BIKE - UTILITY WEAPON
///*****************************************************************
bool Game_Controls::Input_Bike_UtilityWeapon(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//-------------------------------------------------------------
	if(iKeyDown(gKeyboard_Bike_UtilityWeapon) || 
		iMouseButtonDown(DIK_MMB) ||
		cGame_Input_xbox360controller.bUtility)
	{
		bState = true;
	}

	if(gTextInputLock)
	{
		bState = false;
	}

	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - BIKE - STEERING
///*****************************************************************
float Game_Controls::Input_Bike_Steering(void)
{
	//-------------------------------------------------------------
	float fValue = 0.0f;
	//fValue = iFloatInterpolate((float)iMouseX(),0.0f,1.0f,-1.0f,1.0f);
	if(iKeyDown(gKeyboard_Bike_Steer_Left))
	{
		iFloatTendTo2(gKeyboard_Smooth_Steer,-1.0f,3.0f);
		fValue = gKeyboard_Smooth_Steer;
	}
	else if(iKeyDown(gKeyboard_Bike_Steer_Right))
	{
		iFloatTendTo2(gKeyboard_Smooth_Steer,1.0f,3.0f);
		fValue = gKeyboard_Smooth_Steer;
	}
	else if(iGamepadXbox360ConnectedCount() > 0)//enable xbox steering
	{
		//fValue = iFloatInterpolate((float)gXBox360Controller_ThumbStickLeftX,-32768.0f,32768.0f,-1.0f,1.0f);
		if(abs(gXBox360Controller_ThumbStickLeftX) >= 5000)
		{
			fValue = iFloatInterpolate((float)abs(gXBox360Controller_ThumbStickLeftX),5000.0f,32768.0f,0.0f,1.0f);
			if(gXBox360Controller_ThumbStickLeftX <=-0)
			{
				fValue = -fValue;
			}
		}
	}
	return fValue;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - BIKE - AXIS Y
///*****************************************************************
float Game_Controls::Input_Bike_Axis_Y(void)
{
	//-------------------------------------------------------------
	float fValue = 0.0f;

	if(iKeyDown(gKeyboard_Bike_Axis_Y_Up))
	{
		fValue = 1.0f;
	}
	else if(iKeyDown(gKeyboard_Bike_Axis_Y_Down))
	{
		fValue = -1.0f;
	}
	else if(iGamepadXbox360ConnectedCount() > 0)//xbox 360 controller
	{
		fValue = iFloatInterpolateSmooth((float)gXBox360Controller_ThumbStickLeftY,-32768.0f,32768.0f,-1.0f,1.0f);
	}
	return fValue;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - CAMERA - AXIS X
///*****************************************************************
float Game_Controls::Input_Camera_Axis_X(void)
{
	//-------------------------------------------------------------
	float fValue = 0.0f;

	//if(iKeyDown(gKeyboard_Bike_Axis_Y_Up))
	//{
	//	fValue = -1.0f;
	//}
	//else if(iKeyDown(gKeyboard_Bike_Axis_Y_Down))
	//{
	//	fValue = 1.0f;
	//}
	if(iGamepadXbox360ConnectedCount() > 0)//xbox 360 controller
	{
		fValue = iFloatInterpolateSmooth((float)gXBox360Controller_ThumbStickRightX,-32768.0f,32768.0f,-1.0f,1.0f);
	}
	return fValue;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - CAMERA - AXIS Y
///*****************************************************************
float Game_Controls::Input_Camera_Axis_Y(void)
{
	//-------------------------------------------------------------
	float fValue = 0.0f;

	//if(iKeyDown(gKeyboard_Bike_Axis_Y_Up))
	//{
	//	fValue = -1.0f;
	//}
	//else if(iKeyDown(gKeyboard_Bike_Axis_Y_Down))
	//{
	//	fValue = 1.0f;
	//}
	if(iGamepadXbox360ConnectedCount() > 0)//xbox 360 controller
	{
		fValue = iFloatInterpolateSmooth((float)gXBox360Controller_ThumbStickRightY,-32768.0f,32768.0f,-1.0f,1.0f);
	}
	return fValue;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - CAMERA - MODE SELECT
///*****************************************************************
bool Game_Controls::Input_Camera_Mode_Change(void)
{ 
	//-------------------------------------------------------------
	bool bState = false;
	if(iKeyClick(gKeyboard_Camera_Mode_Change) || 
		cGame_Input_xbox360controller.bCamera)
	{
		bState = true;
	}

	if(gTextInputLock)
	{
		bState = false;
	}
	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - CAMERA - LOOK BACK
///*****************************************************************
bool Game_Controls::Input_Camera_LookBack(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//-------------------------------------------------------------
	//keyboard
	if(iKeyDown(DIK_D))
	{
		bState = true;
	}
	//xbox 360 controller
	else if(iGamepadXbox360ConnectedCount() > 0)
	{
		if(cGame_Input_xbox360controller.bColour)
		{
			bState = true;
		}
	}
	if(gTextInputLock)
	{
		bState = false;
	}
	//-------------------------------------------------------------
	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - ACTION - PAUSE
///*****************************************************************
void Game_Controls::Input_Action_Pause(void)
{ 
	//-------------------------------------------------------------
	if(!gTextInputLock)
	{
		if(iKeyClick(gKeyboard_Action_Pause) || 
			cGame_Input_xbox360controller.bStart)
		{
			gPaused = true;
			gMenu_Active = true;

			//reset spectate
			cGame_Camera.bSpectate = false;
			cGame_Camera.SpectateId = gAi_Max_Count;

			if(!iNetworkIsActive())
			{
				gBikesGo = false;
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - ACTION - START
///*****************************************************************
bool Game_Controls::Input_Action_Start(void)
{ 
	//-------------------------------------------------------------
	bool bState = false;

	if(iKeyClick(gKeyboard_Action_Start_A) ||
		iKeyClick(gKeyboard_Action_Start_B) ||
		cGame_Input_xbox360controller.bStart)
	{
		bState = true;
	}

	if(gTextInputLock)
	{
		bState = false;
	}
	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - ACTION - DEV MODE SELECT
///*****************************************************************
bool Game_Controls::Input_Action_DevMode(void)
{
	//-------------------------------------------------------------
	if(iKeyClick(gKeyboard_Action_DevMode) || 
	   iGamepadXbox360ButtonClick(cGame_Input_xbox360controller.Gamepad,GP_BUTTON_DPAD_UP))
	{
		gDevMode ^= 1;
	}
	return gDevMode;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - ACTION - CHANGE COLOUR
///*****************************************************************
bool Game_Controls::Input_Action_Colour(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//keyboard
	if(iKeyClick(DIK_X))
	{
		bState = true;
	}
	//xbox 360 controller
	//else if(iGamepadXbox360ConnectedCount() > 0)
	//{
	//	if(cGame_Input_xbox360controller.bColour)
	//	{
	//		bState = true;
	//	}
	//}
	if(gTextInputLock)
	{
		bState = false;
	}

	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - ACTION - SCOREBOARD
///*****************************************************************
bool Game_Controls::Input_Action_ScoreBoard(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//-------------------------------------------------------------
	if(!gDevMode)
	{
		//keyboard
		if(iKeyClick(DIK_F1))
		{
			bState = true;
		}
		//xbox 360 controller
		else if(iGamepadXbox360ConnectedCount() > 0)
		{
			if(cGame_Input_xbox360controller.bSelect)
			{
				bState = true;
			}
		}
	}

	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - MENU - UP
///*****************************************************************
bool Game_Controls::Input_Menu_Action_Up(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//keyboard
	if(iKeyDown(gKeyboard_Menu_Up))
	{
		if(iKeyClickAutoRepeat(gKeyboard_Menu_Up,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay))
		{
			bState = true;
		}
	}
	//xbox 360 controller
	else if(iGamepadXbox360ConnectedCount() > 0)
	{
		if(iGamepadXbox360ThumbStickLeftYAutoRepeat(cGame_Input_xbox360controller.Gamepad,22768,true,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay) ||
		   iGamepadXbox360ButtonClickAutoRepeat(cGame_Input_xbox360controller.Gamepad,GP_BUTTON_DPAD_UP,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay))
		{
			bState = true;
		}
	}
	
	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - MENU - DOWN
///*****************************************************************
bool Game_Controls::Input_Menu_Action_Down(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//keyboard
	if(iKeyDown(gKeyboard_Menu_Down))
	{
		if(iKeyClickAutoRepeat(gKeyboard_Menu_Down,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay))
		{
			bState = true;
		}
	}
	//xbox 360 controller
	else if(iGamepadXbox360ConnectedCount() > 0)
	{
		if(iGamepadXbox360ThumbStickLeftYAutoRepeat(cGame_Input_xbox360controller.Gamepad,-22768,false,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay) ||
		   iGamepadXbox360ButtonClickAutoRepeat(cGame_Input_xbox360controller.Gamepad,GP_BUTTON_DPAD_DOWN,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay))
		{
			bState = true;
		}
	}
	
	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - MENU - LEFT
///*****************************************************************
bool Game_Controls::Input_Menu_Action_Left(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//keyboard
	if(iKeyDown(gKeyboard_Menu_Left))
	{
		if(iKeyClickAutoRepeat(gKeyboard_Menu_Left,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay))
		{
			bState = true;
		}
	}
	//xbox 360 controller
	else if(iGamepadXbox360ConnectedCount() > 0)
	{
		if(iGamepadXbox360ThumbStickLeftXAutoRepeat(cGame_Input_xbox360controller.Gamepad,-22768,false,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay) ||
		   iGamepadXbox360ButtonClickAutoRepeat(cGame_Input_xbox360controller.Gamepad,GP_BUTTON_DPAD_LEFT,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay))
		{
			bState = true;
		}
	}
	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - MENU - RIGHT
///*****************************************************************
bool Game_Controls::Input_Menu_Action_Right(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//keyboard
	if(iKeyDown(gKeyboard_Menu_Right))
	{
		if(iKeyClickAutoRepeat(gKeyboard_Menu_Right,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay))
		{
			bState = true;
		}
	}
	//xbox 360 controller
	else if(iGamepadXbox360ConnectedCount() > 0)
	{
		if(iGamepadXbox360ThumbStickLeftXAutoRepeat(cGame_Input_xbox360controller.Gamepad,22768,true,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay) ||
		   iGamepadXbox360ButtonClickAutoRepeat(cGame_Input_xbox360controller.Gamepad,GP_BUTTON_DPAD_RIGHT,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay))
		{
			bState = true;
		}
	}
	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - MENU - SELECT
///*****************************************************************
bool Game_Controls::Input_Menu_Action_Select(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	//Only allow selection when Menu Text is ready.
	if(cGame_Menu.bTextReady)
	{
		//keyboard
		if(iKeyClick(gKeyboard_Menu_Select))
		{
			bState = true;
		}
		//Mouse
		else if(iMouseButtonClick(VK_LBUTTON) && gMousePosition_Current.x < -6.5f)
		{
			bState = true;
		}
		//xbox 360 controller
		else if(iGamepadXbox360ConnectedCount() > 0)
		{
			if(cGame_Input_xbox360controller.bAcell || 
				cGame_Input_xbox360controller.bStart)
			{
				bState = true;
			}
		}

		if(gTextInputLock)
		{
			bState = false;
		}
		//Play sound
		if(bState)
		{
			if(cGame_Menu.Text_Main[gMenuSubId]=="Back" || cGame_Menu.Text_Main[gMenuSubId]=="Apply")
			{
				cGame_Audio.Menu.MenuFx(1);
			}
			else
			{
				cGame_Audio.Menu.MenuFx(2);
			}
		}
	}
	return bState;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - INPUT - MENU - BACK
///*****************************************************************
bool Game_Controls::Input_Menu_Action_Back(void)
{
	//-------------------------------------------------------------
	bool bState = false;
	if(iKeyClick(DIK_ESCAPE))
	{
		bState = true;
	}
	//xbox 360 controller
	else if(iGamepadXbox360ConnectedCount() > 0)
	{
		if(cGame_Input_xbox360controller.bBreak)
		{
			bState = true;
		}
	}

	if(gTextInputLock)
	{
		bState = false;
	}
	else if(bState)
	{
		cGame_Audio.Menu.MenuFx(1);
	}

	return bState;
	//-------------------------------------------------------------
}