#pragma once
//-----------------------------------------------------------------
// About: 
//
// name: "Global_Params.h"
// 
// included in: "stdafx.h" after "dllOddityEngine2.h"
// 
// usage: here we make our globals truely global so they can be accessed anywhere.
//		  this way we don't have to add "e.g. extern int bob;" to every cpp
//		  we want to use a global in. every cpp has top have stdafx.h in it so why
//		  not use that to our advantage for our globals and save any uneccessary clutter.
//
//-----------------------------------------------------------------
///*****************************************************************
//GLOBAL - CLASS HEADER FILES - our global classes that we will use globaly
///*****************************************************************
#include "Global_Class_Headers.h"
///*****************************************************************
//GLOBAL - BUILD SETTING/INFORMATION
///*****************************************************************
extern const bool						gReleaseBuild;
extern const string						gBuildVersion;
extern const string						gBuildDate;
///*****************************************************************
//GLOBAL - ONLINE RECORDS
///*****************************************************************
extern const bool						gClearOnlineRecords;
extern int								gCurrentRecordViewed;
///*****************************************************************
//GLOBAL - TimeStep
///*****************************************************************
extern const float						gET_dt;
extern float							gET_currentTime;
extern float							gET_accumulator;
extern float							gET_DeltaTime;
///*****************************************************************
//GLOBAL - PHYSX PAUSE
///*****************************************************************
extern bool								gPhysxPause;
///*****************************************************************
//GLOBAL - DEBUG - DEVMODE
///*****************************************************************
extern bool								gDevMode;
///*****************************************************************
//GLOBAL - LOAD/SAVE - FILEPATHS
///*****************************************************************
extern char* gFilePath_Settings_Settings;
extern char* gFilePath_Settings_Upgrades;
extern char* gFilePath_Settings_PlayerStats;
extern char* gFilePath_Settings_LapRecords;
extern char* gFilePath_Settings_DevMode_Audio;
///*****************************************************************
//GLOBAL - DEFINES
///*****************************************************************
//FPS monitor
extern int								gFps;
extern const float						gTimeStep;
//NETWORK 
extern const int						MAX_NETWORK_CONNECTIONS;
//Ai Count
extern const int						MAX_BIKE_AI_COUNT;
extern int								gAi_Max_Count;
extern int								gAi_UserChange;
extern const int						MAX_BIKES_NET;
//Max Weapon Stuff
extern const int						MAX_PRIMARY_PROJECTILES_PER_BIKE;
extern const int						MAX_UTILITY_TYPES;
extern const int						MAX_SECONDARY_TYPES;
//Max UPGRADE SPRITES
extern const int						MAX_UPGRADE_SPRITES;
///*****************************************************************
//GLOBAL - HANDLES
///*****************************************************************
//camera
extern CAMERA*							gCamera;
//font
extern FONT*							gFont;
extern FONT*							gFont2;
//Char Buffer
extern char								gCharBuffer[256];
///*****************************************************************
//GLOBAL - CLASS OBJECTS
///*****************************************************************
//System_Thread
extern System_Thread					cThread;
//FTP
extern Game_Ftp							cGame_Ftp;
//Game_LoadingScreen
extern Game_LoadingScreen				cGame_LoadingScreen;
//Global Timers
extern Game_Timer						cGame_Timer;
//Player Stats
extern Game_PlayerStats					cGame_PlayerStats;
//Game_Optimiser
extern Game_Optimiser					cGame_Optimiser;
//Upgrades
extern Game_Upgrades					cGame_Upgrades;
//Game_Network
extern Game_Network						cGame_Network;
//Game Controls
extern Game_Controls					cGame_Controls;
//xbox 360 controller
extern Game_Input_xbox360controller		cGame_Input_xbox360controller;
//camera
extern Game_Camera						cGame_Camera;
//font
extern Game_Font						cGame_Font;
//menu main
extern Game_Menu						cGame_Menu;
//Hud
extern Game_Hud							cGame_Hud;
//RaceTracker
extern Game_RaceTracker					cGame_RaceTracker;
//chapter manager
extern Game_Chapter_Manager				cGame_Chapter_Manager;
//settings
extern Game_Settings					cGame_Settings;
//physx materials
extern Game_Physx_Material				cGame_Physx_Material;
//physx collision masks
extern Game_Physx_Collision_Mask		cGame_Physx_Collision_Mask;
//audio
extern Game_Audio						cGame_Audio;
//texture 2D samplers
extern Game_Texture2D_Sampler			cGame_Texture2D_Sampler;
//global textures
extern Game_Asset_Global_Texture		cGame_Asset_Global_Texture;
//global meshes
extern Game_Mesh						cGame_Mesh;
//skydome
extern Game_SkyDome						cGame_SkyDome;
//environment - tracks
extern Game_Track						cGame_Track;
//PostProcessing
extern Game_PostProcessing				cGame_PostProcessing;
//Particle
extern Game_Particle					cGame_Particle;
//bike - Ai
extern Game_Bike						cGame_Bike[40];
//DevMode
extern Game_DevMode						cGame_DevMode;
//Spawn System
extern Game_Spawn						cGame_Spawn;
//Gamma + Fade
extern Game_Gamma_Fade					cGame_Gamma_Fade;
//global GameMode Controller
extern Game_Mode_Controller				cGame_Mode_Controller;
//global Text Descriptions
extern Game_Global_Text_Description		cGame_Global_Text_Description;
//Replay
extern Game_Replay						cGame_Replay;
///*****************************************************************
//GLOBAL - GAME CONTROL DATA
///*****************************************************************
//MAIN
extern bool								gPaused;
extern bool								gResetLevel;
//global control settings
extern bool								gMenu_Active;
extern int								gMenuId;
extern int								gMenuSubId;
//Gamestate (loading, track selection , etc)
extern bool								gLoad;
extern bool								gDestroy;
extern int								gGameState;
extern int								gGameStateChange;
//GameMode (timetrail/weapons/elimitation etc)
extern int								gGameMode;
extern int								gGameModeChange;
//Global Race Countdown Timer
extern int								gRaceCountdown;
extern bool								gRaceCountdown_Net_Use;
//RaceState (Start Of Race, End Race etc)
extern int								gRaceState;
//Laps Update
extern bool								gLapsUpdate;
//Position Based on Kills?
extern bool								gKillBasedPositions;
//Mission Status (Failed/Completed etc)
extern bool								gRaceWin;
//Exit to Windows
extern bool								gExitWin;
//Boot Loader
extern bool								gBootLoadCompleted;
extern int								gBootLoadState;
extern bool								gBootLoadVideoSkip;
//Respawn Settings
extern bool								gRespawnEnable;
extern const int						gRespawnTimerMax;
///*****************************************************************
//GLOBAL - GAME MENU MAIN DATA
///*****************************************************************
//Text input Lockout
extern bool								gTextInputLock;
//Hold
extern float							gMenu_Input_Init_Delay;
extern float							gMenu_Input_Hold_Delay;
//Screen Ratio for sprites
extern float							gScreenYScale;
///*****************************************************************
//GLOBAL - GAME CAMERA
///*****************************************************************
extern int								gCam_PlayerPreset;
///*****************************************************************
//GLOBAL - INPUT - MOUSE
///*****************************************************************
extern bool								gMouseEnabled;
extern bool								gMouseIsHidden;
extern D3DXVECTOR2						gMousePosition_Current;
///*****************************************************************
//GLOBAL - INPUT - KEYBOARD
///*****************************************************************
//menu
extern int								gKeyboard_Menu_Up;
extern int								gKeyboard_Menu_Down;
extern int								gKeyboard_Menu_Left;
extern int								gKeyboard_Menu_Right;
extern int								gKeyboard_Menu_Select;
//bike
extern int								gKeyboard_Bike_Accelerate;
extern int								gKeyboard_Bike_Break;
extern int								gKeyboard_Bike_Boost;
extern int								gKeyboard_Bike_PrimaryWeapon;
extern int								gKeyboard_Bike_SecondaryWeapon;
extern int								gKeyboard_Bike_UtilityWeapon;
extern float							gKeyboard_Smooth_Steer;
extern int								gKeyboard_Bike_Steer_Left;
extern int								gKeyboard_Bike_Steer_Right;
extern int								gKeyboard_Bike_Axis_Y_Up;
extern int								gKeyboard_Bike_Axis_Y_Down;
//camera
extern int								gKeyboard_Camera_Mode_Change;
//action
extern int								gKeyboard_Action_Start_A;
extern int								gKeyboard_Action_Start_B;
extern int								gKeyboard_Action_Pause;
extern int								gKeyboard_Action_DevMode;
///*****************************************************************
//GLOBAL - INPUT - XBOX 360 CONTROLLER
///*****************************************************************
//triggers
extern int								gXBox360Controller_TriggerLeft;
extern int								gXBox360Controller_TriggerRight;
//thumbstick
extern int								gXBox360Controller_ThumbStickLeftX;
extern int								gXBox360Controller_ThumbStickLeftY;
extern int								gXBox360Controller_ThumbStickRightX;
extern int								gXBox360Controller_ThumbStickRightY;
//vibration
extern bool								gXbox360Controller_Vibrate;
extern float							gXbox360Controller_MotorLeft;
extern float							gXbox360Controller_MotorRight;
///*****************************************************************
//GLOBAL - AUDIO
///*****************************************************************
///Master Volumes
extern float							gVolumeFx;
extern float							gVolumeMusic;
extern float							gVolumeHitsound;
///Sound Barrier
extern bool								gSoundBarrier;
extern const float						gSoundBarrierSpeedActivation;
extern const float						gSoundBarrierVolumeMin;
extern const float						gSoundBarrierTendTo_In;
extern const float						gSoundBarrierTendTo_Out;
///*****************************************************************
//GLOBAL - GFX & SHADER - DEFINITIONS
///*****************************************************************
//Global 2d Hide (hud etc)
extern bool								gDisable2D;
//fog
extern bool								gFog;
extern float							gFog_Min;
extern float							gFog_Max;
extern D3DXVECTOR4						gFog_Colour;
//Vsync
extern bool								gVsync;
//Lights
extern D3DXVECTOR4						gDirectLight1;
extern D3DXVECTOR4						gDirectLight2;
extern D3DXVECTOR4						gDirectLight3;
extern D3DXVECTOR4						gDirectLight4;
//OPTIMISER
extern bool								gFirstRun;
extern int								gGfxOptimiserState;
//FXAA
extern bool								gFxaaEnable;
extern int								gFxaaQuality;
//Mesh Smoothing
extern const float						gMeshSmoothing;
//Font Scaler
extern float							gFontScale;
//Colour Correction (fake gamma etc)
extern float							gGammaMulti;
extern D3DXVECTOR4						gColourCorrection;
extern float							gUserGamma;
//Glow
extern bool								gGlowEnable;
extern const bool						gGlowMeshEnable; //Mesh, Load Glow flag -- For dev testing etc
extern D3DXVECTOR4						gGlowValues;
//Lumiance
extern float							gBloomThreshold;
extern float							gBloomRadius;
extern int								gBloomBlurCount;
//Dof
extern bool								gDoFEnable;
extern int								gDoFQuality;
//Cascade Shadows
extern bool								gShadowsEnable;
extern int								gShadowsResolution;
extern D3DXVECTOR3						gShadowsOrientation;
extern D3DXVECTOR3						gShadowsLocation;
extern D3DXVECTOR2						gShadowsSize;
extern float							gShadowBlur;
extern float							gShadowBias;
extern float							gShadowDensity;
//Reflections
extern bool								gReflectEnable;
extern int								gReflectRes;
extern bool								gReflectMipMap;
extern float							gReflectAmmount;
extern float							gReflectMinRange;
extern float							gReflectMaxRange;
//Motion Blur
extern bool								gBlurEnable;
extern int								gBlurSamples;
extern float							gBlurCamera;
extern float							gBlurObject;
///*****************************************************************
//GLOBAL - MESH/TEXTURE
///*****************************************************************
//Global Texture Pan/rotate floats
extern float							gTexturePan_Slow;
extern float							gTexturePan_Med;
extern float							gTexturePan_Fast;
extern float							gTexturePan_Vibrate;
extern float							gTextureRot_Slow;
extern float							gTextureRot_Med;
extern float							gTextureRot_Fast;
//Global Mesh vectors and quats (eg: Double damage fx)
extern float							gMesh_UpDown;
extern D3DXQUATERNION					g_qMesh_XY_Spin;
extern D3DXQUATERNION					g_qMesh_XY_Spin_Inverse;
///*****************************************************************
//GLOBAL - CULLING SYSTEM
///*****************************************************************
//FrustumCulling
extern const float						gFrustCullScale;
extern const float						gFrustCullRadius;
//Culling Sets
extern const float						gCullRangeMax;
extern int								gMax_Culling_Bikes_Shown;
extern int								gMax_Culling_Bikes_Low_Detail;
extern int								gMax_Culling_Bikes_High_Detail;
///*****************************************************************
//GLOBAL - PARTICLE SYSTEM
///*****************************************************************
extern const int						gParticle_Explosion_MaxCreate;
extern const float						gParticle_Explosion_AnimatorMaxEmit;
extern const float						gParticle_Explosion_WeaponHitMaxEmit;
///*****************************************************************
//GLOBAL - BIKE - COLOURS - DEFINITIONS
///*****************************************************************
extern int								gBikeModelType_Ai;
extern int								gBikeModelType_Player;
//Bike Scale
extern D3DXVECTOR3						gBikeScale;
//Menu Colour
extern int								gMenuColour;
extern D3DXVECTOR4						gMenuFontColour;
extern D3DXVECTOR3						gMenuTrackColour;
extern D3DXVECTOR4						gFontBlack;	
extern D3DXVECTOR4						gFontWhite;	
extern D3DXVECTOR4						gFontGreyLight;	
extern D3DXVECTOR4						gFontGreyDark;	
//Colour Pool
extern float							gHsvMin;
extern float							gHsvMax;
extern float							gBikeColourUserHSV;
extern D3DXVECTOR3						gBikeColourUser;
extern int								gBikeColourSelectAi;
extern const D3DXVECTOR3				gBikeColourGreen;
extern const D3DXVECTOR3				gBikeColourOrange;
extern const D3DXVECTOR3				gBikeColourBlue;
extern const D3DXVECTOR3				gBikeColourPink;
extern const D3DXVECTOR3				gBikeColourWhite;
//Bike Shell Colour Definitions
extern D3DXVECTOR3						gBikeShellColour;
//Engine Colour Definitions
extern const D3DXVECTOR3				gColourEngineBreak;
extern const D3DXVECTOR3				gColourEngineIdle;
extern const D3DXVECTOR3				gColourEngineAccel;
extern const D3DXVECTOR3				gColourEngineBoost;
///*****************************************************************
//GLOBAL - TRACK
///*****************************************************************
//Reverse
extern int								gTrackReverse;
//Max Laps
extern int								gLapMax;
///*****************************************************************
//GLOBAL - BIKE - TRAIL
///*****************************************************************
extern bool								gTrailEnable;
///*****************************************************************
//GLOBAL - BIKE - MANAGER
///*****************************************************************
//Allow Bikes to Move Flag (gPause and gGameReady etc)
extern bool								gBikesGo;
//Speed Class setting
extern int								gSpeedClass;
//Boost Multiplier (fAccel_Max * this)
///*****************************************************************
//GLOBAL - BIKE - ENERGY
///*****************************************************************
//Energy settings
extern const float						gEnergyWarningLimit;
extern const float						gEnergyLowLimit;
extern float							gEnergyRegenRate;
///*****************************************************************
//GLOBAL - BIKE - PLAYER
///*****************************************************************
//Steering Caps
extern float							gPlayer_Steering_Speed_Min;
extern float							gPlayer_Steering_Speed_Max;
extern float							gPlayer_Steering_Output_Min;
extern float							gPlayer_Steering_Output_Max;
///*****************************************************************
//GLOBAL - BIKE - AI
///*****************************************************************
extern int								gAiDifficuty;
extern float							gAiDifficutyMulti;
//Steering Caps
extern float							gAi_Steering_Speed_Min;
extern float							gAi_Steering_Speed_Max;
extern float							gAi_Steering_Output_Min;
extern float							gAi_Steering_Output_Max;
///*****************************************************************
//GLOBAL - BIKE - WEAPONS
///*****************************************************************
//MultiKill Tracking System
extern const int						gMaxMultiKillTimer;
//Respawn Shield Time
extern const int						gRespawnShieldTimeMax;
//Primary Weapon
extern bool								gEnergyPickup_ZeroHeat;
extern int								gPrimaryHeatMax;
extern const int						gPrimaryAliveTimeMax;
extern const float						gPrimaryRadius;
///Ai - setup in bike.weapons
extern float							gAiWeaponsDamageMulti;
extern int								gPrimaryAiFireTimeMax;
extern int								gPrimaryAiRandMax;
//Secondary Weapons 
///(Missile)
///(ShoxWave)
///(EM Burst)
///(Rail)
extern const float						gSecondaryRadiusRail;
//Utility Weapons
///*****************************************************************
//GLOBAL - INFO - FLAGS
///*****************************************************************
extern string							gInfoTrack;
extern string							gInfoTrackReverse;
extern string							gInfoGameMode;
extern string							gInfoSpeedClass;
extern string							gInfoAiDifficulty;
extern string							gInfoPlayerCam;
///*****************************************************************
//GLOBAL - GAMEMODE - CONTROLLER
///*****************************************************************
//Pickup Radius
extern const float					gPickupRadius;
//Pickup Reset Timer
extern const int					gPickupTimerReset;
//Weapons
extern bool							gWeaponsEnable;
extern bool							gWeaponsTrackEnable;
//Boost
extern bool							gBoostEnable;
extern bool							gBoostTrackEnable;
///*****************************************************************
//GAME - NETWORK
///*****************************************************************
//MASTER SERVER
extern string						gMasterServerMOTD;
extern bool							gMasterServerOnline;
extern bool							gManualNetworkGame;
extern string						gMasterServerBuildVersion;
///game region
extern int							gGameRegion;
extern const int					gGameRegionMAX;
extern string						gGameRegionInfo;
///Packet Checks
extern int							gNetworkIntValue[2000];
extern D3DXVECTOR3					gNetworkVector3Value[100];
extern string						gNetworkStringValue[10];
///Network State
extern int							gNumberOfClients;
extern int							gServerState;
extern int							gClientState;
///Tick Rate
extern int							gNetworkTickRateMax;
extern int							gNetworkTickRate;
///Global Ports
extern char							gNetworkPort[1024];
extern char							gClientPort[1024];
///Global Password
extern char							gNetworkPass[1024];
///Player Names
extern char							gPlayerName[128];
//extern string						gNetwork_PlayerNames[10];
///IpAdress LAN
extern char							gIpAddress[1024];
///Network players ready?
extern int							gNetPlayerReady[10];
extern int							gNetMeReady;
//NET DEBUG - HOW MANY CHANGED VALUES?
extern int							gDEBUG_Net_ChangedValues;
///*****************************************************************
//GAME - PlayerLEVELXP
///*****************************************************************
extern const int						gLevelMax;
extern const int						gPointsPerLevel;
///*****************************************************************
//GLOBAL - FEEDBACK
///*****************************************************************
extern int							gFeedback_Overall;
extern int							gFeedback_Gameplay;
extern int							gFeedback_Performance;
extern int							gFeedback_Visuals;
extern int							gFeedback_Sound;
extern int							gFeedback_Music;
extern int							gFeedback_Difficulty;
extern bool							gFeedback_Sent;
///*****************************************************************
//GLOBAL - FUNCTIONS - FORWARD DECLARATIONS - our custom functions that we can use anywhere.
///*****************************************************************
#include "Global_Functions_ForwardDec_Mouse.h"
#include "Global_Functions_ForwardDec_Math.h"