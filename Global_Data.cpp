#pragma once
#include "stdafx.h"
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//NOTES:
///if i add a racetrack (eg: gGameState 0-8, not arena), MAX_RECORDS_CHAPTERS in cGame_Ftp must be increased

//Track Model Scales
// Arena = 0.6
// Phantom = 0.75 - yRotate fragmotion 180
///*****************************************************************
//GLOBAL - BUILD SETTING/INFORMATION
///*****************************************************************
const bool							gReleaseBuild				= false;
const string						gBuildVersion				= "v0.72";
const string						gBuildDate					= "04/05/14";
///*****************************************************************
//GLOBAL - ONLINE RECORDS
///*****************************************************************
const bool							gClearOnlineRecords			= false; //CLEAR ONLINE RECORDS?
int									gCurrentRecordViewed		= 0;
///*****************************************************************
//GLOBAL - TimeStep
///*****************************************************************
const float							gET_dt = 1.0f / 62.0f; //eg: Street Fighter 2 Turbo lol
float								gET_currentTime			= 0.0f;
float								gET_accumulator			= 0.0f;
float								gET_DeltaTime			= 0.0f;
///*****************************************************************
//GLOBAL - PHYSX PAUSE
///*****************************************************************
bool								gPhysxPause = false;
///*****************************************************************
//GLOBAL - DEBUG - DEVMODE
///*****************************************************************
bool								gDevMode = false;
///*****************************************************************
//GLOBAL - LOAD/SAVE - FILEPATHS
///*****************************************************************
char* gFilePath_Settings_Settings = "trzero_res\\settings\\settings.bin";
char* gFilePath_Settings_Upgrades = "trzero_res\\settings\\upgrades.bin";
char* gFilePath_Settings_PlayerStats = "trzero_res\\settings\\playerstats.bin";
char* gFilePath_Settings_LapRecords = "trzero_res\\settings\\laprecords_v2.bin";
char* gFilePath_Settings_DevMode_Audio = "trzero_res\\settings\\devaudio.bin";
///*****************************************************************
//GLOBAL - DEFINES
///*****************************************************************
//FPS monitor
int									gFps							= 60;
const float							gTimeStep						= 1.0f / 60.0f;//* gET_DeltaTime
//NETWORK 
const int							MAX_NETWORK_CONNECTIONS			= 8;
//Ai Count
const int							MAX_BIKE_AI_COUNT				= 39;
int									gAi_Max_Count					= 39;
int									gAi_UserChange					= gAi_Max_Count;
const int							MAX_BIKES_NET					= 19;
//Max Weapon Stuff
const int							MAX_PRIMARY_PROJECTILES_PER_BIKE = 10;
const int							MAX_UTILITY_TYPES			= 4;
const int							MAX_SECONDARY_TYPES			= 4;
//Max UPGRADE SPRITES
const int							MAX_UPGRADE_SPRITES			= 6;
///*****************************************************************
//GLOBAL - HANDLES
///*****************************************************************
//camera
CAMERA*								gCamera							= NULL;
//font
FONT*								gFont							= NULL;
FONT*								gFont2							= NULL;
//Char Buffer
char								gCharBuffer[256]				= { '\0' };
///*****************************************************************
//GLOBAL - CLASS OBJECTS
///*****************************************************************
//System_Thread
System_Thread						cThread;
//FTP
Game_Ftp							cGame_Ftp;
//Game_LoadingScreen
Game_LoadingScreen					cGame_LoadingScreen;
//Global Timers
Game_Timer							cGame_Timer;
//Player Stats
Game_PlayerStats					cGame_PlayerStats;
//Game_Optimiser
Game_Optimiser						cGame_Optimiser;
//Upgrades
Game_Upgrades						cGame_Upgrades;
//Game_Network
Game_Network						cGame_Network;
//Game Controls
Game_Controls						cGame_Controls;
//xbox 360 controller
Game_Input_xbox360controller		cGame_Input_xbox360controller;
//camera
Game_Camera							cGame_Camera;
//font
Game_Font							cGame_Font;
//menu main
Game_Menu							cGame_Menu;
//Hud
Game_Hud							cGame_Hud;
//RaceTracker
Game_RaceTracker					cGame_RaceTracker;
//chapter manager
Game_Chapter_Manager				cGame_Chapter_Manager;
//settings
Game_Settings						cGame_Settings;
//physx materials
Game_Physx_Material					cGame_Physx_Material;
//physx collision masks
Game_Physx_Collision_Mask			cGame_Physx_Collision_Mask;
//audio
Game_Audio							cGame_Audio;
//texture 2D samplers
Game_Texture2D_Sampler				cGame_Texture2D_Sampler;
//global textures
Game_Asset_Global_Texture			cGame_Asset_Global_Texture;
//Mesh
Game_Mesh							cGame_Mesh;
//skydome
Game_SkyDome						cGame_SkyDome;
//environment - tracks
Game_Track							cGame_Track;
//PostProcessing
Game_PostProcessing					cGame_PostProcessing;
//Particle
Game_Particle						cGame_Particle;
//bike - Ai
Game_Bike							cGame_Bike[40];
//DevMode
Game_DevMode						cGame_DevMode;
//Spawn System
Game_Spawn							cGame_Spawn;
//Gamma + Fade
Game_Gamma_Fade						cGame_Gamma_Fade;
//global GameMode Controller
Game_Mode_Controller				cGame_Mode_Controller;
//global Text Descriptions
Game_Global_Text_Description		cGame_Global_Text_Description;
//Replay
Game_Replay							cGame_Replay;
///*****************************************************************
//GLOBAL - GAME CONTROL DATA
///*****************************************************************
//MAIN
bool								gPaused							= false;
bool								gResetLevel						= false;
//global Menu States
bool								gMenu_Active					= true;
int									gMenuId							= 2;
int									gMenuSubId						= 0;
//Gamestate (loading, track selection , etc)
bool								gLoad							= false;
bool								gDestroy						= false;
int									gGameState						= 0;
int									gGameStateChange				= gGameState;
//GameMode (timetrail/weapons/elimitation etc)
int									gGameMode						= 2;
int									gGameModeChange					= gGameMode;
//Global Race Countdown Timer
int									gRaceCountdown					= 1800;//30 seconds
bool								gRaceCountdown_Net_Use			= false;
//RaceState (Start Of Race, End Race etc)
int									gRaceState						= 0;//0=Not started - 1=running - 2=Finished.
//Laps Update
bool								gLapsUpdate						= false;
//Position Based on Kills?
bool								gKillBasedPositions				= false;
//Mission Status (Failed/Completed etc)
bool								gRaceWin						= false;//Apply scores etc
//Exit to Windows
bool								gExitWin						= false;
//Boot Loader
bool								gBootLoadCompleted				= false;
int									gBootLoadState					= 0;
bool								gBootLoadVideoSkip				= true;
//Respawn Settings
bool								gRespawnEnable					= false;
const int							gRespawnTimerMax				= 420;
///*****************************************************************
//GLOBAL - GAME MENU MAIN DATA
///*****************************************************************
//Text input Lockout
bool								gTextInputLock					= false;
//Hold
float								gMenu_Input_Init_Delay			= 25.0f;
float								gMenu_Input_Hold_Delay			= 3.5f;
//Screen Ratio for sprites
float								gScreenYScale					= 1.0f;
///*****************************************************************
//GLOBAL - GAME CAMERA
///*****************************************************************
int									gCam_PlayerPreset				= 0;
///*****************************************************************
//GLOBAL - INPUT - MOUSE
///*****************************************************************
bool								gMouseEnabled					= false;
bool								gMouseIsHidden					= false;
D3DXVECTOR2							gMousePosition_Current			= D3DXVECTOR2(0.5f,0.5f);
///*****************************************************************
//GLOBAL - INPUT - KEYBOARD
///*****************************************************************
//menu
int									gKeyboard_Menu_Up				= DIK_UP;
int									gKeyboard_Menu_Down				= DIK_DOWN;
int									gKeyboard_Menu_Left				= DIK_LEFT;
int									gKeyboard_Menu_Right			= DIK_RIGHT;
int									gKeyboard_Menu_Select			= DIK_RETURN;
//bike
int									gKeyboard_Bike_Accelerate		= DIK_A;
int									gKeyboard_Bike_Break			= DIK_Z;
int									gKeyboard_Bike_Boost			= DIK_S;
int									gKeyboard_Bike_PrimaryWeapon	= DIK_SPACE;
int									gKeyboard_Bike_SecondaryWeapon	= DIK_V;
int									gKeyboard_Bike_UtilityWeapon	= DIK_F;
float								gKeyboard_Smooth_Steer			= 0.0f;
int									gKeyboard_Bike_Steer_Left		= DIK_LEFT;
int									gKeyboard_Bike_Steer_Right		= DIK_RIGHT;
int									gKeyboard_Bike_Axis_Y_Up		= DIK_UP;
int									gKeyboard_Bike_Axis_Y_Down		= DIK_DOWN;
//camera
int									gKeyboard_Camera_Mode_Change	= DIK_C;
//action
int									gKeyboard_Action_Start_A		= DIK_RETURN;
int									gKeyboard_Action_Start_B		= DIK_SPACE;
int									gKeyboard_Action_Pause			= DIK_P;
int									gKeyboard_Action_DevMode		= DIK_TAB;//D
///*****************************************************************
//GLOBAL - INPUT - XBOX 360 CONTROLLER
///*****************************************************************
//triggers
int									gXBox360Controller_TriggerLeft		= 0;
int									gXBox360Controller_TriggerRight		= 0;
//thumbstick
int									gXBox360Controller_ThumbStickLeftX	= 0;
int									gXBox360Controller_ThumbStickLeftY	= 0;
int									gXBox360Controller_ThumbStickRightX = 0;
int									gXBox360Controller_ThumbStickRightY = 0;
//vibration
bool								gXbox360Controller_Vibrate			= true;
float								gXbox360Controller_MotorLeft		= 0.0f;
float								gXbox360Controller_MotorRight		= 0.0f;
///*****************************************************************
//GLOBAL - AUDIO
///*****************************************************************
///Master Volumes
float								gVolumeFx						= 0.95f;
float								gVolumeMusic					= 0.55f;//0.55
float								gVolumeHitsound					= 0.9f;
///Sound Barrier
bool								gSoundBarrier					= false;
const float							gSoundBarrierSpeedActivation	= 7.0f;
const float							gSoundBarrierVolumeMin			= 0.1f;
const float							gSoundBarrierTendTo_In			= 12.0f;
const float							gSoundBarrierTendTo_Out			= 45.0f;
///*****************************************************************
//GLOBAL - GFX & SHADER - DEFINITIONS
///*****************************************************************
//Global 2d Hide (hud etc)
bool								gDisable2D						= false;
//fog
bool								gFog							= false;
float								gFog_Min						= 650.0f;
float								gFog_Max						= 1800.0f;
D3DXVECTOR4							gFog_Colour						= D3DXVECTOR4(0.3f,0.3f,0.3f,1.0f);
//Vsync
bool								gVsync							= true;
//Lights
D3DXVECTOR4							gDirectLight1 = D3DXVECTOR4(1.58f, 1.58f, 1.58f, 0.0f);//bikes
D3DXVECTOR4							gDirectLight2 = D3DXVECTOR4(0.76f, 0.76f, 0.76f, 0.12f);//roads
D3DXVECTOR4							gDirectLight3 = D3DXVECTOR4(1.7f, 1.7f, 1.7f, 0.11f);//Worlds
D3DXVECTOR4							gDirectLight4 = D3DXVECTOR4(0.0f, 1.5f, 3.0f, 0.7f);
//D3DXVECTOR4							gDirectLight1 = D3DXVECTOR4(2.0f, 2.0f, 2.0f, 0.1f);//bikes
//D3DXVECTOR4							gDirectLight2 = D3DXVECTOR4(0.75f, 0.75f, 0.75f, 0.35f);//roads
//D3DXVECTOR4							gDirectLight3 = D3DXVECTOR4(0.85f, 0.85f, 0.85f, 0.2f);//Worlds
//D3DXVECTOR4							gDirectLight4 = D3DXVECTOR4(0.0f, 1.5f, 3.0f, 0.7f);


//OPTIMISER
bool								gFirstRun						= true;
int									gGfxOptimiserState				= 0;//0 = inactive, 1 = running, 2 = required
//FXAA
bool								gFxaaEnable						= false;
int									gFxaaQuality					= 2;
//Mesh Smoothing
const float							gMeshSmoothing					= 0.67f;
//Font Scaler
float								gFontScale						= 1.0f;
//Colour Correction
float								gGammaMulti						= 1.0f;
//D3DXVECTOR4							gColourCorrection = D3DXVECTOR4(1.0f, 1.9f, 3.3f, 0.0f);//D3DXVECTOR4(0.98f,1.7f,2.8f,0.0f);
D3DXVECTOR4							gColourCorrection = D3DXVECTOR4(0.8f, 2.6f, 2.5f, 0.0f);//D3DXVECTOR4(0.98f,1.7f,2.8f,0.0f);
float								gUserGamma = gColourCorrection.x;
//Glow
bool								gGlowEnable						= false;
const bool							gGlowMeshEnable					= true; //Mesh, Load Glow flag -- For dev testing etc
//D3DXVECTOR4							gGlowValues = D3DXVECTOR4(1.5f, 0.55f, 5.0f, 1.0f);
D3DXVECTOR4							gGlowValues = D3DXVECTOR4(1.0f, 0.16f, 10.0f, 1.0f);
//Lumiance
float								gBloomThreshold					= 0.5f;
float								gBloomRadius					= 5.0f;
int									gBloomBlurCount					= 2;
//DoF
bool								gDoFEnable						= false;
int									gDoFQuality						= 2;
//Cascade Shadows
bool								gShadowsEnable					= false;
int									gShadowsResolution				= 2; //512
D3DXVECTOR3							gShadowsOrientation				= D3DXVECTOR3(98.0f,0.0f,0.0f);
D3DXVECTOR3							gShadowsLocation				= D3DXVECTOR3(-150.0f,394.0f,-405.0f);
D3DXVECTOR2							gShadowsSize					= D3DXVECTOR2(1866.0f,1410.0f);
float								gShadowBlur						= 2.0f;
float								gShadowBias						= 0.0004f;
float								gShadowDensity					= 0.4f;
//Reflections
bool								gReflectEnable					= false;
int									gReflectRes						= 256; // 64=low 128=norm 256-512=max
bool								gReflectMipMap					= false;
float								gReflectAmmount					= 0.5f;//0.25f
float								gReflectMinRange				= 0.01f;
float								gReflectMaxRange				= 2500.0f;
//Motion Blur
bool								gBlurEnable						= false;
int									gBlurSamples					= 8;
float								gBlurCamera						= 24.0f;
float								gBlurObject						= 0.0f;
///*****************************************************************
//GLOBAL - MESH/TEXTURE
///*****************************************************************
//Global Texture Pan/rotate floats
float								gTexturePan_Slow				= 0.0f;
float								gTexturePan_Med 				= 0.0f;
float								gTexturePan_Fast 				= 0.0f;
float								gTexturePan_Vibrate				= 0.0f;
float								gTextureRot_Slow				= 0.0f;
float								gTextureRot_Med 				= 0.0f;
float								gTextureRot_Fast 				= 0.0f;
//Global Mesh vectors and quats (eg: Double damage fx)
float								gMesh_UpDown					= 0.0f;
D3DXQUATERNION						g_qMesh_XY_Spin				= D3DXQUATERNION(0.0f,0.0f,0.0f,0.0f);
D3DXQUATERNION						g_qMesh_XY_Spin_Inverse		= D3DXQUATERNION(0.0f,0.0f,0.0f,0.0f);
///*****************************************************************
//GLOBAL - CULLING SYSTEM
///*****************************************************************
//FrustumCulling
const float							gFrustCullScale					= 0.6f;
const float							gFrustCullRadius				= 1.7f;
//Culling Sets
const float							gCullRangeMax					= 900.0f;
int									gMax_Culling_Bikes_Shown		= 25;
int									gMax_Culling_Bikes_Low_Detail	= 14;
int									gMax_Culling_Bikes_High_Detail	= 7;
///*****************************************************************
//GLOBAL - PARTICLE SYSTEM
///*****************************************************************
const int						gParticle_Explosion_MaxCreate			= 500;//150
const float						gParticle_Explosion_AnimatorMaxEmit		= 70.0f;
const float						gParticle_Explosion_WeaponHitMaxEmit	= 40.0f;
///*****************************************************************
//GLOBAL - BIKE - COLOUR - DEFINITIONS
///*****************************************************************
int									gBikeModelType_Ai				= 1; //0=Carl , 1=Dave
int									gBikeModelType_Player			= 1; //0=Carl , 1=Dave
//Bike Scale
D3DXVECTOR3							gBikeScale						= D3DXVECTOR3(1.5f,1.5f,1.5f);
//D3DXVECTOR3							gBikeScale						= D3DXVECTOR3(1.75f,1.75f,1.75f);
//D3DXVECTOR3							gBikeScale						= D3DXVECTOR3(0.96f,1.0f,1.0f);
//Menu Colours
int									gMenuColour						= 0;
D3DXVECTOR4							gMenuFontColour		 			= D3DXVECTOR4(1.2f,0.5f,0.0f,1.0f);
D3DXVECTOR3							gMenuTrackColour 				= D3DXVECTOR3(1.76f,0.72f,0.48f);
D3DXVECTOR4							gFontBlack						= D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);	
D3DXVECTOR4							gFontWhite						= D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);	
D3DXVECTOR4							gFontGreyLight					= D3DXVECTOR4(0.9f,0.9f,0.9f,1.0f);	
D3DXVECTOR4							gFontGreyDark					= D3DXVECTOR4(0.7f,0.7f,0.7f,1.0f);	
//Colour Pool
float								gHsvMin							= 0.5f;
float								gHsvMax							= 1.5f;
float								gBikeColourUserHSV				= 1.0f;
D3DXVECTOR3							gBikeColourUser 				= D3DXVECTOR3(1.0f,0.58f,0.35f);
int									gBikeColourSelectAi				= 0;
const D3DXVECTOR3					gBikeColourGreen 				= D3DXVECTOR3(0.5f,1.0f,0.25f);
const D3DXVECTOR3					gBikeColourOrange 				= D3DXVECTOR3(1.0f,0.58f,0.35f);
const D3DXVECTOR3					gBikeColourBlue 				= D3DXVECTOR3(0.35f,0.48f,1.0f);
const D3DXVECTOR3					gBikeColourPink 				= D3DXVECTOR3(0.45f,0.35f,1.0f);
const D3DXVECTOR3					gBikeColourWhite 				= D3DXVECTOR3(0.6f,0.6f,0.6f);
//Bike Shell Colour Definitions
//D3DXVECTOR3							gBikeShellColour = D3DXVECTOR3(0.91f, 0.91f, 0.91f);
D3DXVECTOR3							gBikeShellColour = D3DXVECTOR3(0.7f, 0.7f, 0.7f);
//Engine Colour Definitions
const D3DXVECTOR3					gColourEngineBreak				= D3DXVECTOR3(2.0f,0.0f,0.0f);
const D3DXVECTOR3					gColourEngineIdle				= D3DXVECTOR3(0.1f,0.1f,0.1f);
const D3DXVECTOR3					gColourEngineAccel				= D3DXVECTOR3(0.5f,0.0f,2.0f);
const D3DXVECTOR3					gColourEngineBoost				= D3DXVECTOR3(0.5f,0.0f,2.0f);
///*****************************************************************
//GLOBAL - TRACK
///*****************************************************************
//Reverse
int									gTrackReverse					= 0;
//Max Laps
int									gLapMax							= 3;
///*****************************************************************
//GLOBAL - BIKE - TRAIL
///*****************************************************************
bool								gTrailEnable					= true;
///*****************************************************************
//GLOBAL - BIKE - MANAGER
///*****************************************************************
//Allow Bikes to Move
bool								gBikesGo						= false;
//Speed Class setting
int									gSpeedClass						= 0;
///*****************************************************************
//GLOBAL - BIKE - ENERGY
///*****************************************************************
//Energy settings
const float							gEnergyWarningLimit				= 75.0f;
const float							gEnergyLowLimit					= 100.0f;
float								gEnergyRegenRate				= 0.25f;
///*****************************************************************
//GLOBAL - BIKE - PLAYER
///*****************************************************************
//Steering Caps
float								gPlayer_Steering_Speed_Min		= 0.5f;
float								gPlayer_Steering_Speed_Max		= 7.5f;
float								gPlayer_Steering_Output_Min		= 0.625f;
float								gPlayer_Steering_Output_Max		= 2.4f;
///*****************************************************************
//GLOBAL - BIKE - AI
///*****************************************************************
int									gAiDifficuty					= 1;//(3) 0-4
float								gAiDifficutyMulti				= 0.9f;//(1)1.1f (2)1.15f (3)1.2f
//Steering Caps
float								gAi_Steering_Speed_Min			= 0.6f;
float								gAi_Steering_Speed_Max			= 7.5f;
float								gAi_Steering_Output_Min			= 1.8f;
float								gAi_Steering_Output_Max			= 5.0f;
///*****************************************************************
//GLOBAL - BIKE - WEAPONS
///*****************************************************************
//MultiKill Tracking System
const int						gMaxMultiKillTimer					= 300;
//Respawn Shield Time
const int						gRespawnShieldTimeMax				= 180;
//Primary Weapon
bool							gEnergyPickup_ZeroHeat				= true;
int								gPrimaryHeatMax						= 100;
const int						gPrimaryAliveTimeMax				= 90;
const float						gPrimaryRadius						= 7.5f;
///Ai - setup in bike.weapons
float							gAiWeaponsDamageMulti				= 0.5f;
int								gPrimaryAiFireTimeMax				= 50;
int								gPrimaryAiRandMax					= 20;
//Secondary Weapons 
///(Missile)
///(ShoxWave)
///(EM Burst)
///(Rail)
const float						gSecondaryRadiusRail				= 10.0f;
//Utility Weapons
///*****************************************************************
//GLOBAL - INFO - FLAGS
///*****************************************************************
string								gInfoTrack						= "";
string								gInfoTrackReverse				= "";
string								gInfoGameMode					= "";
string								gInfoSpeedClass					= "";
string								gInfoAiDifficulty				= "";
string								gInfoPlayerCam					= "";
///*****************************************************************
//GLOBAL - GAMEMODE - CONTROLLER
///*****************************************************************
//Pickup Radius
const float						gPickupRadius						= 9.0f;
//Pickup Reset Timer
const int						gPickupTimerReset					= 17;
//Weapons
bool							gWeaponsEnable						= false;
bool							gWeaponsTrackEnable					= false;
//Boost
bool							gBoostEnable						= false;
bool							gBoostTrackEnable					= false;
///*****************************************************************
//GAME - NETWORK
///*****************************************************************
//MASTER SERVER
string							gMasterServerMOTD					= "";
bool							gMasterServerOnline					= false;
bool							gManualNetworkGame					= false;
string							gMasterServerBuildVersion			= gBuildVersion;
///Game Region
int								gGameRegion							= 0;
const int						gGameRegionMAX						= 1;
string							gGameRegionInfo						= "";
///Packet Checks
int								gNetworkIntValue[2000];
D3DXVECTOR3						gNetworkVector3Value[100];
string							gNetworkStringValue[10];
///Network State
int								gNumberOfClients					= 0;
int								gServerState						= 0;
int								gClientState						= 0;
///Tick Rate
int								gNetworkTickRateMax					= 3;
int								gNetworkTickRate					= 0;
///Global Ports
char							gNetworkPort[1024]					= "6001";//6001
char							gClientPort[1024]					= "6002";
///Global Password
char							gNetworkPass[1024]					= "LETMEIN";
///Player Names
char							gPlayerName[128]					= "Player";
//string							gNetwork_PlayerNames[10];
///IpAdress LAN
char							gIpAddress[1024]					= "192.168.0.1";
///Network players ready?
int								gNetPlayerReady[10];
int								gNetMeReady							= 0;
//NET DEBUG - HOW MANY CHANGED VALUES?
int								gDEBUG_Net_ChangedValues			= 0;
///*****************************************************************
//GAME - PlayerLEVELXP
///*****************************************************************
const int						gLevelMax							= 30;
const int						gPointsPerLevel						= 4;
///*****************************************************************
//GLOBAL - FEEDBACK
///*****************************************************************
int								gFeedback_Overall				= 5;
int								gFeedback_Gameplay				= 5;
int								gFeedback_Performance			= 5;
int								gFeedback_Visuals				= 5;
int								gFeedback_Sound					= 5;
int								gFeedback_Music					= 5;
int								gFeedback_Difficulty			= 5;
bool							gFeedback_Sent					= false;