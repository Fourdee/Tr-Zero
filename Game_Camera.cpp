//-----------------------------------------------------------------
// About:
//
// name: "Game_Camera.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
//
// device input: none.
//
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Camera.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - CAMERA - CONSTRUCTORS
///*****************************************************************
Game_Camera::Game_Camera(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Camera::~Game_Camera(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - ZERODATA
///*****************************************************************
void Game_Camera::ZeroData(void)
{
	//-------------------------------------------------------------
	//Player Camera Settings
	///Tr-Zero
	//vPlayerCam[0]								= D3DXVECTOR4(5.05f,-17.5f,-1.0f,60.0f);
	//vPlayerCam[0]								= D3DXVECTOR4(5.65f,-15.70f,4.0f,60.0f);
	vPlayerCam[0]								= D3DXVECTOR4(4.95f,-13.0f,4.0f,70.0f);
	///Tr-Zero High
	//vPlayerCam[1]								= D3DXVECTOR4(5.65f,-15.70f,4.0f,60.0f);
	//vPlayerCam[1]								= D3DXVECTOR4(7.25f,-18.70f,4.0f,60.0f);
	vPlayerCam[1]								= D3DXVECTOR4(6.55f,-15.9f,4.0f,70.0f);
	///vintage
	//vPlayerCam[2]								= D3DXVECTOR4(4.95f,-19.2f,2.0f,44.0f);
	vPlayerCam[2]								= D3DXVECTOR4(5.35f,-18.0f,4.0f,40.0f);
	///internal
	//vPlayerCam[3]								= D3DXVECTOR4(2.4f,1.44f,-3.0f,60.0f);
	vPlayerCam[3]								= D3DXVECTOR4(2.6f,1.44f,2.0f,58.0f);
															  //Y	  Z	   Rot   fov
	//Others
	fFov										= 60.0f;
	fFovBoostExtra								= 0.0f;
	ClipDistance_Min							= 0.525f;
	ClipDistance_Max							= 8000.0f;
	vCamOutput									= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vCamOffset									= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vCamLookAt									= D3DXVECTOR3(0.0f,0.0f,0.0f);
	qCamOutput									= D3DXQUATERNION(-90.0f,0.0f,0.0f,1.0f);
	Mode_InGame									= gCam_PlayerPreset;
	Mode_Menu									= 0;
	Mode_Paused									= 0;
	TendToCam									= 100.0f;
	TendToFov									= 40.0f;
	fRotation_px								= 0.0f;
	fRotation_py								= 0.0f;
	fRotation_pz								= 0.0f;
	//Timer
	Timer_Selected								= 0;
	Timer_Mode									= 0;
	//Target Data
	vTarget 									= D3DXVECTOR3(0.0f,0.0f,0.0f);
	qTarget										= D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	TargetSpeed									= 0.0f;
	SpeedClassMax								= 0.0f;
	TargetLean									= 0.0f;
	TargetSteering								= 0.0f;
	SpeedState									= 0;
	SpectateId									= gAi_Max_Count;
	bSpectate									= false;
	TargetRespawning							= false;
	//Orbit Data
	fOrbitAngle									= 0.0f;
	fOrbitDistance 								= 13.0f;
	//Current Camera Info
	CamInfo_TimerMax							= 180;
	CamInfo_Timer								= CamInfo_TimerMax;
	CamInfo_Text								= "";
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - CAMERA - CREATE
///*****************************************************************
void Game_Camera::Create(void)
{
	//-------------------------------------------------------------
	gCamera = iCameraCreate(0.0f,0.0f,1.0f,1.0f);
	//-------------------------------------------------------------
	//Zero Data
	ZeroData();
	//-------------------------------------------------------------
	iCameraLocationSet(gCamera,&D3DXVECTOR3(0.0f,4.0f,-10.0f));
	iCameraClipDistanceSet(gCamera,ClipDistance_Min,ClipDistance_Max);
	iCameraFOVSet(gCamera,fFov);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - CAMERA - UPDATE
///*****************************************************************
void Game_Camera::Update(void)
{
	//-------------------------------------------------------------
	//Camera Active Target Data
	Spectate_Selector();
	//Update Mode Selector
	Mode_Selector();
	//update camera data
	iCameraFOVSet(gCamera,fFov);
	iCameraLocationSet(gCamera,&vCamOutput);
	iCameraOrientationSet(gCamera,&qCamOutput);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - MODE SELECTOR
///*****************************************************************
void Game_Camera::Mode_Selector(void)
{
	//-------------------------------------------------------------
	//selection
	if(gGameState==0)
	{
		if(Mode_Menu==0){Camera_Menu_Intro();}
		else if(Mode_Menu==1){User_Orbit();}
		else if(Mode_Menu==2){Upgrade_View();}
		else if(Mode_Menu==3){User_FreeView();}
		else if(Mode_Menu==4){Network_Lobby();}
		else if(Mode_Menu==5){Camera_InGame();}///Camera prefrence menu
	}
	else if(gMenu_Active)
	{
		if(Mode_Menu==0){Camera_MenuPause();}
		else if(Mode_Menu==1){User_Orbit();}
		else if(Mode_Menu==2){Upgrade_View();}
		else if(Mode_Menu==3){User_FreeView();}
		else if(Mode_Menu==5){Camera_InGame();}///Camera prefrence menu
	}
	else if(gRaceState==0)//Intro
	{
		if(cGame_Mode_Controller.Intro.bBeginTimer)
		{
			//Intro (3 second countdown)
			Intro_Countdown();
		}
		else
		{
			//Track intro
			if(gGameState==1){Intro_Volex(false);}
			else if(gGameState==2){User_FreeView();}
			else if(gGameState==3){User_FreeView();}
			else if(gGameState==10){User_FreeView();}
		}
	}
	else if(gRaceState==1)//Ingame
	{
		if(TargetRespawning)
		{
			User_Orbit();
			//Lookat player - slow follow
		}
		else
		{
			Camera_InGame();
		}
	}
	else if(gRaceState==2)//End Race
	{
		Camera_InGame();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - SPECTATE SELECTOR
///*****************************************************************
void Game_Camera::Spectate_Selector(void)
{
	//-------------------------------------------------------------
	//toggle
	if(gRaceState>=1 && 
		gAi_Max_Count > 0)
	{
		int MaxAllowed = gAi_Max_Count;
		//if(iNetworkIsActive())
		//{
		//	MaxAllowed = gNumberOfClients;
		//}

		if(iKeyClick(VK_OEM_6))
		{
			//Active - 1st player
			if(!bSpectate)
			{
				bSpectate = true;
				SpectateId = 0;
			}
			else//Cycle through
			{
				///Enable/cycle through
				SpectateId++;
				if(SpectateId>=MaxAllowed)
				{
					SpectateId = gAi_Max_Count;
					bSpectate = false;
				}
			}
		}
		//Turn off
		if(iKeyClick(VK_OEM_4))
		{
			bSpectate = false;
			SpectateId = gAi_Max_Count;
		}
	}
	else
	{
		//Disable
		bSpectate = false;
		SpectateId = gAi_Max_Count;
	}
	//-------------------------------------------------------------
	//Update
	vTarget = cGame_Bike[SpectateId].Manager.vBikeOutput;
	qTarget = cGame_Bike[SpectateId].Manager.qBikeOutput;
	TargetSpeed	= cGame_Bike[SpectateId].Manager.fAcceleration_Speed;
	TargetLean = cGame_Bike[SpectateId].Manager.fLean;
	TargetSteering = cGame_Bike[SpectateId].fSteering;
	SpeedClassMax = cGame_Bike[SpectateId].Manager.fAcceleration_Max * 2.0f;
	SpeedState = cGame_Bike[SpectateId].InputSpeedState;
	TargetRespawning = cGame_Bike[SpectateId].bRespawning;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - INTRO VOLEX
///*****************************************************************
void Game_Camera::Intro_Volex(bool bCreate)
{
	//-------------------------------------------------------------
	//Cam Speed
	TendToCam = 200.0f;
	if(bCreate)
	{
		TendToCam = 12.0f;
	}
	//-------------------------------------------------------------
	//Camera Transition timer
	if(!bCreate)
	{
		Timer_Selected++;
		if(Timer_Selected==360)
		{
			Timer_Mode++;
			Timer_Selected = 0;
		}
	}
	//-------------------------------------------------------------
	//Intro Cam positions
	//-------------------------------------------------------------
	if(Timer_Mode==0)
	{///Setup
		vCamOffset = D3DXVECTOR3(-452.0f,-347.0f,-899.0f);
		vCamLookAt = D3DXVECTOR3(-438.0f,-99.0f,-245.0f);		
		vCamOutput = vCamOffset;
		///Fov offsets
		fFov = 30.0f;
		Timer_Mode = 1;
		iQuaternionLookAt(&qCamOutput,&vCamOutput,&vCamLookAt,&D3DXVECTOR3(0.0f,1.0f,0.0f));
	}
	else if(Timer_Mode==1)
	{
		if(bCreate)
		{
			static bool bSwitch = false;
			if(iKeyClick(DIK_M)){bSwitch = !bSwitch;}
			if(!bSwitch)
			{	///Cam origin
				vCamOffset.x += cGame_Controls.Input_Bike_Steering();
				vCamOffset.y += cGame_Controls.Input_Bike_Axis_Y();
				vCamOffset.z += cGame_Controls.Input_Camera_Axis_Y() * 2.0f;
			}
			else
			{	///Cam Lookat
				vCamLookAt.x += cGame_Controls.Input_Bike_Steering();
				vCamLookAt.y += cGame_Controls.Input_Bike_Axis_Y();
				vCamLookAt.z += cGame_Controls.Input_Camera_Axis_Y() * 2.0f;
			}
		}
		else
		{
			vCamOffset = D3DXVECTOR3(-468.0f,-300.0f,-530.0f);
			vCamLookAt = D3DXVECTOR3(-261.0f,-324.0f,-254.0f);
		}
	}
	else if(Timer_Mode==2)
	{
		vCamOffset = D3DXVECTOR3(-175.0f,-355.0f,-260.0f);
		vCamLookAt = D3DXVECTOR3(-106.0f,-284.0f,-258.0f);
	}
	else if(Timer_Mode==3)
	{
		vCamOffset = D3DXVECTOR3(280.0f,-331.0f,-248.0f);
		vCamLookAt = D3DXVECTOR3(383.0f,629.0f,-631.0f);	
	}
	else if(Timer_Mode==4)
	{
		vCamOffset = D3DXVECTOR3(142.0f,160.0f,-490.0f);
		vCamLookAt = D3DXVECTOR3(-86.0f,-9.0f,-344.0f);
	}
	else if(Timer_Mode==5)
	{
		vCamOffset = D3DXVECTOR3(173.0f,100.0f,-31.0f);
		vCamLookAt = D3DXVECTOR3(-254.0f,-50.0f,25.0f);
	}
	else if(Timer_Mode==6)
	{
		vCamOffset = D3DXVECTOR3(-214.0f,262.0f,266.0f);
		vCamLookAt = D3DXVECTOR3(-569.0f,-20.0f,-136.0f);
	}
	else if(Timer_Mode==7)
	{
		vCamOffset = D3DXVECTOR3(-475.0f,-75.0f,0.0f);
		vCamLookAt = D3DXVECTOR3(-569.0f,-80.0f,-500.0f);
	}
	else
	{
		Timer_Mode = 0;
	}
	//-------------------------------------------------------------
	//Output
	iFloatTendTo2(vCamOutput.x,vCamOffset.x,TendToCam);
	iFloatTendTo2(vCamOutput.y,vCamOffset.y,TendToCam);
	iFloatTendTo2(vCamOutput.z,vCamOffset.z,TendToCam);
	iFloatTendTo2(fFov,45.0f,TendToFov);

	D3DXVECTOR3 up; 
	up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	iVectorRotate(&up,&up,&qTarget);
	D3DXQUATERNION qLookAt = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	iQuaternionLookAt(&qLookAt,&vCamOutput,&vCamLookAt,&up);
	if(bCreate)
	{
		iQuaternionInterpolate(&qCamOutput,&qCamOutput,&qLookAt,0.1f);
	}
	else
	{
		iQuaternionInterpolate(&qCamOutput,&qCamOutput,&qLookAt,0.01f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - Replay_Camera
///*****************************************************************
void Game_Camera::Replay_Camera(void)
{
	//-------------------------------------------------------------
	//Cam Speed
	TendToCam = 100.0f;
	//-------------------------------------------------------------
	///World Cam
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXQUATERNION qLookAt = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	iQuaternionLookAt(&qLookAt,&vCamOutput,&vTarget,&up);
	iQuaternionInterpolate(&qCamOutput,&qCamOutput,&qLookAt,0.5f);

	float FovTarget = iFloatInterpolate(iVectorLength(&(vTarget - vCamOutput)),5.0f,800.0f,70.0f,5.0f);
	iFloatTendTo2(fFov,FovTarget,15.0f);

	vCamOffset.x = cGame_Controls.Input_Bike_Steering();
	vCamOffset.y = cGame_Controls.Input_Bike_Axis_Y();
	vCamOffset.z = (cGame_Controls.Input_Camera_Axis_Y() * 2.0f);

	iVectorRotate(&vCamOffset,&vCamOffset,&qCamOutput);
	vCamOutput = vCamOutput + vCamOffset;

	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - INTRO COUNTDOWN
///*****************************************************************
void Game_Camera::Intro_Countdown(void)
{
	//-------------------------------------------------------------
	//Cam Speed
	TendToCam = 15.0f;
	//-------------------------------------------------------------
	int TimeLeft = cGame_Mode_Controller.Intro.IntroTimerMax - cGame_Mode_Controller.Intro.IntroTimer;
	if(cGame_Mode_Controller.Intro.IntroTimer<=1)
	{///Setup
		vCamOffset.x = 5.0f;
		vCamOffset.y = 5.0f;
		vCamOffset.z = 50.0f;
		vCamOutput = vCamOffset;
		///Fov offsets
		fFov = 30.0f;
	}
	else if(TimeLeft==180)
	{///3
		vCamOffset.x = -6.0f;
		vCamOffset.y = 2.0f;
		vCamOffset.z = 16.0f;
	}
	else if(TimeLeft==120)
	{///2
		vCamOffset.x = 14.0f;
		vCamOffset.y = 0.0f;
		vCamOffset.z = -2.0f;
	}
	else if(TimeLeft==60)
	{///1
		vCamOffset.x = 0.0f;
		vCamOffset.y = 2.5f;
		vCamOffset.z = -12.0f;
	}
	//-------------------------------------------------------------
	//Output
	D3DXVECTOR3 vCamTarget = iVectorLocationOffset(&vTarget,&qTarget,&vCamOffset);
	iFloatTendTo2(vCamOutput.x,vCamTarget.x,TendToCam);
	iFloatTendTo2(vCamOutput.y,vCamTarget.y,TendToCam);
	iFloatTendTo2(vCamOutput.z,vCamTarget.z,TendToCam);
	iFloatTendTo2(fFov,45.0f,TendToFov);

	D3DXVECTOR3 up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	iVectorRotate(&up,&up,&qTarget);
	iQuaternionLookAt(&qCamOutput,&vCamOutput,&vTarget,&up);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - USER FREEVIEW
///*****************************************************************
void Game_Camera::User_FreeView(void)
{
	//-------------------------------------------------------------
	fRotation_px = 0.0f;
	fRotation_py += cGame_Controls.Input_Camera_Axis_X();
	fRotation_pz = 0.0f;
	
	if(cGame_Controls.Input_Bike_Acceleration())
	{
		fFov += 0.5f;
	}
	else if(cGame_Controls.Input_Bike_Break())
	{
		fFov -= 0.5f;
	}

	iQuaternionFromEulerAngles(&qCamOutput,fRotation_px,fRotation_py,fRotation_pz);

	vCamOffset.x = cGame_Controls.Input_Bike_Steering();
	vCamOffset.y = cGame_Controls.Input_Bike_Axis_Y();
	vCamOffset.z = (cGame_Controls.Input_Camera_Axis_Y() * 2.0f);

	iVectorRotate(&vCamOffset,&vCamOffset,&qCamOutput);
	vCamOutput = vCamOutput + vCamOffset;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - USER ORBIT
///*****************************************************************
void Game_Camera::User_Orbit(void)
{
	//-------------------------------------------------------------
	//Orbit Controller
	if(abs(fOrbitAngle) >= 360.0f)
	{
		vCamOffset.x = fOrbitDistance * cos(0.0f);
		vCamOffset.z = fOrbitDistance * sin(0.0f);
		fOrbitAngle = 0.0f;
	}
	else
	{
		if(abs(cGame_Controls.Input_Camera_Axis_X()) > 0.1f)
		{
			fOrbitAngle += (cGame_Controls.Input_Camera_Axis_X() / 50.0f);
		}
		else
		{
			fOrbitAngle += 0.001f;
		}
	}

	//Smooth Process		
	iFloatTendTo2(vCamOffset.x, fOrbitDistance * cos(fOrbitAngle),10.0f);
	iFloatTendTo2(vCamOffset.y, 3.0f + (cGame_Controls.Input_Camera_Axis_Y() * 4.0f),35.0f);
	iFloatTendTo2(vCamOffset.z, fOrbitDistance * sin(fOrbitAngle),10.0f);
	///Gfx optimizer adjust
	if(gGfxOptimiserState==1)
	{
		vCamOffset.x = 0.2f;
		vCamOffset.y = 3.0f;
		vCamOffset.z = -12.0f;
	}

	D3DXVECTOR3 location = iVectorLocationOffset(&vTarget,&qTarget,&vCamOffset);

	//Lookat
	D3DXVECTOR3 up; 
	up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	iVectorRotate(&up,&up,&qTarget);
	iQuaternionLookAt(&qCamOutput,&location,&vTarget,&up);
	//-------------------------------------------------------------
	//Fov
	iFloatTendTo2(fFov,65.0f,TendToFov);
	//Output
	if(gMenu_Active)
	{
		vCamOutput = iVectorLocationOffset(&location,&qCamOutput,&D3DXVECTOR3(-4.0f,0.0f,0.0f));
	}
	else
	{
		vCamOutput = location;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - UPGRADE VIEW
///*****************************************************************
void Game_Camera::Upgrade_View(void)
{
	//-------------------------------------------------------------
	//Orbit Controller
	if(abs(fOrbitAngle) >= 360.0f)
	{
		vCamOffset.x = fOrbitDistance * cos(0.0f);
		vCamOffset.z = fOrbitDistance * sin(0.0f);
		fOrbitAngle = 0.0f;
	}
	else
	{
		if(abs(cGame_Controls.Input_Camera_Axis_X()) > 0.1f)
		{
			fOrbitAngle += cGame_Controls.Input_Camera_Axis_X() / 50.0f;
		}
		else
		{
			fOrbitAngle += 0.001f;
		}
	}

	//Smooth Process		
	iFloatTendTo2(vCamOffset.x, fOrbitDistance * cos(fOrbitAngle),10.0f);
	iFloatTendTo2(vCamOffset.y, 3.0f + (cGame_Controls.Input_Camera_Axis_Y() * 4.0f),35.0f);
	iFloatTendTo2(vCamOffset.z, fOrbitDistance * sin(fOrbitAngle),10.0f);

	D3DXVECTOR3 location = iVectorLocationOffset(&vTarget,&qTarget,&vCamOffset);

	//Lookat
	D3DXVECTOR3 up; 
	up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	iVectorRotate(&up,&up,&qTarget);
	iQuaternionLookAt(&qCamOutput,&location,&vTarget,&up);
	//-------------------------------------------------------------
	//Fov
	iFloatTendTo2(fFov,65.0f,TendToFov);
	//Output
	vCamOutput = iVectorLocationOffset(&location,&qCamOutput,&D3DXVECTOR3(-6.0f,0.0f,0.0f));
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - Network_Lobby
///*****************************************************************
void Game_Camera::Network_Lobby(void)
{
	//-------------------------------------------------------------
	//Fov
	iFloatTendTo2(fFov,75.0f,TendToFov);
	float NetOrbitDistance = 60.0f;
	//Orbit Controller
	if(abs(fOrbitAngle) >= 360.0f)
	{
		vCamOffset.x = NetOrbitDistance * cos(0.0f);
		vCamOffset.z = NetOrbitDistance * sin(0.0f);
		fOrbitAngle = 0.0f;
	}
	else
	{
		if(abs(cGame_Controls.Input_Camera_Axis_X()) > 0.1f)
		{
			fOrbitAngle += cGame_Controls.Input_Camera_Axis_X() / 50.0f;
		}
		else
		{
			fOrbitAngle += 0.001f;
		}
	}
	//Smooth Process		
	iFloatTendTo2(vCamOffset.x, NetOrbitDistance * cos(fOrbitAngle),10.0f);
	iFloatTendTo2(vCamOffset.y, 15.0f + (cGame_Controls.Input_Camera_Axis_Y() * 10.0f),35.0f);
	iFloatTendTo2(vCamOffset.z, NetOrbitDistance * sin(fOrbitAngle),10.0f);
	D3DXVECTOR3 location = iVectorLocationOffset(&cGame_Spawn.vSpawnLocation[4],&qTarget,&vCamOffset);
	//Lookat
	D3DXVECTOR3 up; 
	up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	iVectorRotate(&up,&up,&qTarget);
	iQuaternionLookAt(&qCamOutput,&location,&cGame_Spawn.vSpawnLocation[4],&up);
	//-------------------------------------------------------------
	//Output
	vCamOutput = iVectorLocationOffset(&location,&qCamOutput,&D3DXVECTOR3(-20.0f,0.0f,0.0f));
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - MENU INTRO
///*****************************************************************
void Game_Camera::Camera_Menu_Intro(void)
{
	//-------------------------------------------------------------
	//Menu Cam Intro
	//-------------------------------------------------------------
	if(Timer_Mode==0)
	{///SETUP
		TendToCam = 35.0f;
		vCamOffset.x = 100.0f;
		vCamOffset.y = 300.0f;
		vCamOffset.z = 0.0f;
		///Fov offsets
		fFov = 55.0f;
		Timer_Mode = 1;
	}
	else if(Timer_Mode==1)
	{///backside
		TendToCam = 70.0f;
		iFloatTendTo2(vCamOffset.x, -4.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y, 3.0f,TendToCam);
		iFloatTendTo2(vCamOffset.z, -6.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,75.0f,TendToFov);
		Timer_Selected++;
	}
	else if(Timer_Mode==2)
	{///front
		//gBikesGo = true;
		TendToCam = 250.0f;
		iFloatTendTo2(vCamOffset.x, -6.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y, 2.0f,TendToCam);
		iFloatTendTo2(vCamOffset.z, 11.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,65.0f,TendToFov);
		Timer_Selected++;
	}
	else if(Timer_Mode==3)
	{///backlong
		TendToCam = 250.0f;
		iFloatTendTo2(vCamOffset.x, -15.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y, 6.0f,TendToCam);
		iFloatTendTo2(vCamOffset.z, -31.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,50.0f,TendToFov);
		Timer_Selected++;
	}
	else
	{
		Timer_Mode = 1;
	}
	//Menu Camera Transition timer
	if(Timer_Selected==420)
	{
		Timer_Mode++;
		Timer_Selected = 0;
	}
	//-------------------------------------------------------------
	//Output
	D3DXVECTOR3 location = iVectorLocationOffset(&vTarget,&qTarget,&vCamOffset);

	D3DXVECTOR3 up; 
	up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	iVectorRotate(&up,&up,&qTarget);
	iQuaternionLookAt(&qCamOutput,&location,&vTarget,&up);

	///Offset the cam to compensate for menu on left.
	vCamOutput = iVectorLocationOffset(&location,&qCamOutput,&D3DXVECTOR3(-4.0f,0.0f,0.0f));
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - MENU PAUSED
///*****************************************************************
void Game_Camera::Camera_MenuPause(void)
{
	//-------------------------------------------------------------
	//Camera Transition timer
	if(Timer_Selected==480)
	{
		Mode_Paused++;
		Timer_Selected = 0;
	}
	else
	{
		Timer_Selected++;
	}
	//Cam Speed
	TendToCam = 250.0f;
	//-------------------------------------------------------------
	//Paused Cam positions
	//-------------------------------------------------------------
	if(Mode_Paused==0)
	{///front
		iFloatTendTo2(vCamOffset.x, -10.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y, 5.0f,TendToCam);
		iFloatTendTo2(vCamOffset.z, 16.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,35.0f,TendToFov);
	}
	else if(Mode_Paused==1)
	{///front
		iFloatTendTo2(vCamOffset.x, -8.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y, 0.0f,TendToCam);
		iFloatTendTo2(vCamOffset.z, -1.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,60.0f,TendToFov);
	}
	else if(Mode_Paused==2)
	{///Back
		iFloatTendTo2(vCamOffset.x, -4.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y, -1.0f,TendToCam);
		iFloatTendTo2(vCamOffset.z, -6.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,60.0f,TendToFov);
	}
	else if(Mode_Paused==3)
	{///Back
		iFloatTendTo2(vCamOffset.x, -1.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y, 0.0f,TendToCam);
		iFloatTendTo2(vCamOffset.z, -11.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,60.0f,TendToFov);
	}
	else if(Mode_Paused==4)
	{///Back
		iFloatTendTo2(vCamOffset.x, 3.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y, 2.0f,TendToCam);
		iFloatTendTo2(vCamOffset.z, -10.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,50.0f,TendToFov);
	}
	else
	{
		Mode_Paused = 0;
	}
	//-------------------------------------------------------------
	//Output
	D3DXVECTOR3 preoutput = iVectorLocationOffset(&vTarget,&qTarget,&vCamOffset);

	D3DXVECTOR3 up; 
	up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	iVectorRotate(&up,&up,&qTarget);
	iQuaternionLookAt(&qCamOutput,&preoutput,&vTarget,&up);
	/// use preoutput, add a little extra offset to the left of bike.
	/// Accommodates the menu being on the left
	vCamOutput = iVectorLocationOffset(&preoutput,&qCamOutput,&D3DXVECTOR3(-4.0f,0.0f,0.0f));
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CAMERA - IN GAME
///*****************************************************************
void Game_Camera::Camera_InGame(void)
{
	//-------------------------------------------------------------
	//Smooth Cam
	D3DXQUATERNION qPrevious = qCamOutput;
	//Cam Speed
	TendToCam = 6.0f;
	///Input
	if(cGame_Controls.Input_Camera_Mode_Change())
	{
		Mode_InGame++;
		///Current Camera Info
		CamInfo_Timer = 0;
	}
	//Fov Scale + Limiter
	float Limiter = iFloatInterpolate(abs(TargetSpeed),0.0f,SpeedClassMax,0.0f,15.0f);
	float fFovSpeedBarrier = 0.0f;
	if(gSoundBarrier)
	{
		fFovSpeedBarrier = 10.0f;
	}

	if(SpeedState==2)
	{
		iFloatTendTo2(fFovBoostExtra,5.0f + fFovSpeedBarrier,12.0f);
	}
	else
	{
		iFloatTendTo2(fFovBoostExtra,0.0f + fFovSpeedBarrier,12.0f);
	}
	//-------------------------------------------------------------
	if(Mode_InGame==0)
	{//Tr-Zero 1
		///Current Camera Info
		CamInfo_Text = "Tr-Zero";
		///Vector offsets
		iFloatTendTo2(vCamOffset.x,TargetLean / 5.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y,vPlayerCam[Mode_InGame].x,TendToCam);
		iFloatTendTo2(vCamOffset.z,vPlayerCam[Mode_InGame].y,TendToCam);
		///Quat offsets
		iFloatTendTo2(fRotation_px,vPlayerCam[Mode_InGame].z,TendToCam);
		iFloatTendTo2(fRotation_py,TargetSteering,TendToCam);
		iFloatTendTo2(fRotation_pz,0.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,vPlayerCam[Mode_InGame].w + fFovBoostExtra,TendToFov);
	}
	else if(Mode_InGame==1)
	{//Tr-Zero 2
		///Current Camera Info
		CamInfo_Text = "Tr-Zero High";
		///Vector offsets
		iFloatTendTo2(vCamOffset.x,TargetLean / 5.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y,vPlayerCam[Mode_InGame].x,TendToCam);
		iFloatTendTo2(vCamOffset.z,vPlayerCam[Mode_InGame].y,TendToCam);
		///Quat offsets
		iFloatTendTo2(fRotation_px,vPlayerCam[Mode_InGame].z,TendToCam);
		iFloatTendTo2(fRotation_py,TargetSteering,TendToCam);
		iFloatTendTo2(fRotation_pz,0.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,vPlayerCam[Mode_InGame].w + fFovBoostExtra,TendToFov);
	}
	else if(Mode_InGame==2)
	{//Vintage
		CamInfo_Text = "Vintage";
		float fVintage_Adjust_Z = iFloatInterpolate(TargetSpeed,0.0f,gSoundBarrierSpeedActivation,0.0f,4.0f);
		if(gSoundBarrier)
		{
			fVintage_Adjust_Z += fFovSpeedBarrier / 3.0f;
		}

		float fVintage_Adjust_Fov = iFloatInterpolate(TargetSpeed,0.0f,gSoundBarrierSpeedActivation,0.0f,25.0f);

		///Vector offsets
		iFloatTendTo2(vCamOffset.x,TargetLean / 6.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y,vPlayerCam[Mode_InGame].x,TendToCam);
		iFloatTendTo2(vCamOffset.z,vPlayerCam[Mode_InGame].y + fVintage_Adjust_Z,TendToCam);
		///Quat offsets
		iFloatTendTo2(fRotation_px,vPlayerCam[Mode_InGame].z,TendToCam);
		iFloatTendTo2(fRotation_py,TargetSteering * 2.0f,TendToCam);
		iFloatTendTo2(fRotation_pz,0.0f,TendToCam);
		///Fov offsets
		iFloatTendTo2(fFov,vPlayerCam[Mode_InGame].w + fFovBoostExtra + fVintage_Adjust_Fov,TendToFov);
	}
	else if(Mode_InGame==3)
	{//Internal
		CamInfo_Text = "Internal";
		///Vector offsets
		iFloatTendTo2(vCamOffset.x,TargetLean / 15.0f,TendToCam);
		iFloatTendTo2(vCamOffset.y,vPlayerCam[Mode_InGame].x,TendToCam);

		float fZ_SoundBarrier_Extra = 0.0f;
		if(gSoundBarrier)
		{
			fZ_SoundBarrier_Extra = 1.0f;
		}
		iFloatTendTo2(vCamOffset.z,vPlayerCam[Mode_InGame].y + fZ_SoundBarrier_Extra,TendToCam);
		///Quat offsets
		iFloatTendTo2(fRotation_px,vPlayerCam[Mode_InGame].z,TendToCam);
		iFloatTendTo2(fRotation_py,TargetSteering,TendToCam);
		iFloatTendTo2(fRotation_pz,TargetLean / 4.0f,TendToCam);
		///Fov offsets
		float fFov_SoundBarrier_Extra = 0.0f;
		if(gSoundBarrier)
		{
			fFov_SoundBarrier_Extra = 15.0f;
		}
		iFloatTendTo2(fFov,vPlayerCam[Mode_InGame].w + Limiter + fFovBoostExtra + fFov_SoundBarrier_Extra,TendToFov);
	}
	//-------------------------------------------------------------
	else if(Mode_InGame==4)
	{// na
		Mode_InGame = 5;
	}
	//-------------------------------------------------------------
	else if(Mode_InGame==5)
	{// UserOrbit + Replay Cam
		//if(gRaceState==1)
		//{
			CamInfo_Text = "Orbit";
			User_Orbit();
		//}
		//else
		//{
			//CamInfo_Text = "Replay - TV";
			//if(gGameState==1){Replay_Camera();}
			//else if(gGameState==2){Replay_Camera();}
			//else if(gGameState==3){Replay_Camera();}
			//else if(gGameState==10){Replay_Camera();}
			//else
			//{
			//	Mode_InGame = 0;
			//}
		//}
	}
	else if(Mode_InGame==6)
	{// Freeview
		if(!gReleaseBuild)
		{
			CamInfo_Text = "FreeView";
			iFloatTendTo2(fFov,50.0f,TendToFov);
			User_FreeView();
		}
		else
		{
			Mode_InGame = 0;
		}
	}
	else
	{// Reset
		Mode_InGame = 0;
	}
	//-------------------------------------------------------------
	//Output
	if(Mode_InGame < 5)
	{
		//Smooth Cam
		D3DXQUATERNION qPrevious = qCamOutput;
		vCamOutput = iVectorLocationOffset(&vTarget,&qTarget,&vCamOffset);
		iQuaternionFromEulerAngles(&qCamOutput,fRotation_px,fRotation_py,fRotation_pz);
		///Look Back
		if(cGame_Controls.Input_Camera_LookBack())
		{
			vCamOffset = D3DXVECTOR3(0.0f,5.0f,12.0f);
			vCamOutput = iVectorLocationOffset(&vTarget,&qTarget,&vCamOffset);
			iQuaternionFromEulerAngles(&qCamOutput,3.0f,fRotation_py - 180.0f,0.0f);
			fFov = 90.0f;
		}
		iQuaternionMultiply(&qCamOutput,&qCamOutput,&qTarget);
		iQuaternionInterpolate(&qCamOutput,&qPrevious,&qCamOutput,0.5f);
	}
	//-------------------------------------------------------------
	//Current Camera Info
	if(CamInfo_Timer<CamInfo_TimerMax)
	{
		D3DXVECTOR2 vInfo = D3DXVECTOR2(12.0f,-8.0f);
		D3DXVECTOR4 vColour = gMenuFontColour;
		vInfo.x = iFloatInterpolate((float)CamInfo_Timer,0.0f,15.0f,25.0f,12.0f);
		vColour.w = iFloatInterpolate((float)CamInfo_Timer,(float)CamInfo_TimerMax / 2.0f,(float)CamInfo_TimerMax,1.0f,0.0f);
		iPrint((char*)CamInfo_Text.c_str(),cGame_Font.f20pt,&vInfo,&vColour,gFont2,true);
		CamInfo_Timer++;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - CAMERA - DESTROY
///*****************************************************************
void Game_Camera::Destroy(void)
{
	//-------------------------------------------------------------
	ZeroData();
	iCameraDestroy(gCamera);
	//-------------------------------------------------------------
}