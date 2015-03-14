//-----------------------------------------------------------------
// About:
// All references to Oddity Engine 2 removed
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
///*****************************************************************
//PRE-INITIALIZATION
///*****************************************************************
void PreInit(void)
{
	//-------------------------------------------------------------

	//-------------------------------------------------------------
}
///*****************************************************************
//INITIALIZATION
///*****************************************************************
void Init(void)
{
	//-------------------------------------------------------------
	//Keep system alive (disables Power saving)
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);
	//HANDLE CPU1 = GetCurrentProcess();
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);//ABOVE_NORMAL_PRIORITY_CLASS HIGH_PRIORITY_CLASS
	//-------------------------------------------------------------
	//disable escape key exiting...
	iEscEnable(false);
	//-------------------------------------------------------------
	//Disable Physx system?
	///iPhysxPause(gPhysxPause); - Dave: not pausing physx in the Init section on startup as it needs it’s first timestep applied before pausing
	iPhysxGlobalDirectionalLightEnableSet(false,false,false,false);
	//-------------------------------------------------------------
	//background color
	iBackgroundColorSet(&D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f));
	//-------------------------------------------------------------
	//Mouse
	iWindowsMouseHide(true);
	gMouseIsHidden = true;
	iMouseReset(&gMousePosition_Current);
	//-------------------------------------------------------------
}
///*****************************************************************
//RUN LOOP
///*****************************************************************
void Run(void)
{
	//-------------------------------------------------------------
	//Update the chapter manager (destroy/load/run chapters)
	cGame_Chapter_Manager.Update();
	//-------------------------------------------------------------
}
///*****************************************************************
//EXIT
///*****************************************************************
void Exit(void)
{
	//---------------------------------------------------------
	//Restore system power profile
	SetThreadExecutionState(ES_CONTINUOUS);
	//---------------------------------------------------------
	//Enable Physx (Prevent Exit Crash)
	iPhysxPause(false);
	//---------------------------------------------------------
    //output memory leaks...
    //_CrtDumpMemoryLeaks();
	//-------------------------------------------------------------
	//global textures
	cGame_Asset_Global_Texture.Destroy();
	//-------------------------------------------------------------
	//physx collision masks
	cGame_Physx_Collision_Mask.Destroy();
	//-------------------------------------------------------------
	//physx materials
	cGame_Physx_Material.Destroy();
	//-------------------------------------------------------------
	//settings
	cGame_Settings.Destroy();
	//-------------------------------------------------------------
	//font
	cGame_Font.Destroy();
	//-------------------------------------------------------------
	//camera
	cGame_Camera.Destroy();
	//-------------------------------------------------------------
	//Network
	cGame_Network.Destroy();
	//-------------------------------------------------------------
}