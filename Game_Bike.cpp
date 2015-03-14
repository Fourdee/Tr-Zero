//-----------------------------------------------------------------
// About:
//
// name: "Game_Bike.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
// usage: 
//
// device input: Input functions...
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Bike.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - BIKE - CONSTRUCTORS
///*****************************************************************
Game_Bike::Game_Bike(void)
{
	//-------------------------------------------------------------
	ResetData();
	//-------------------------------------------------------------
}

Game_Bike::~Game_Bike(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - CREATE
///*****************************************************************
void Game_Bike::Create(int ImposterIndex)
{
	//-------------------------------------------------------------
	//Null Data
	ResetData();
	//-------------------------------------------------------------
	//Asign global ID
	PlayerID = ImposterIndex;
	//-------------------------------------------------------------
	//Assign Spawn Location ID
	int SpawnLoc_Id = PlayerID;
	///server adjust - move ai's up the field.
	if(cGame_Network.Server.State==2 && ///is server
		PlayerID>=gNumberOfClients &&	///is Ai
		PlayerID<gAi_Max_Count)			///is not player
	{
		SpawnLoc_Id = PlayerID - gNumberOfClients;
	}

	///Client adjust
	if(cGame_Network.Client.State==2 && ///is client
		PlayerID==gAi_Max_Count)		///is Player
	{
		SpawnLoc_Id = gAi_Max_Count - (cGame_Network.Client.Client_ID + 1);
	}
	//-------------------------------------------------------------
	//manager
	if(PlayerID<gNumberOfClients || ///create networked player AI
		PlayerID==gAi_Max_Count)	///create Player Bike
	{
		Manager.Player_Create(&cGame_Spawn.vSpawnLocation[SpawnLoc_Id],&cGame_Spawn.qSpawnLocation,PlayerID);
	}
	else							///create AI Bike
	{
		Manager.Ai_Create(&cGame_Spawn.vSpawnLocation[SpawnLoc_Id],&cGame_Spawn.qSpawnLocation,PlayerID);
	}
	//Colour
	Colour.Create(PlayerID);
	//Energy
	Energy.Create(PlayerID);
	//-------------------------------------------------------------
	//Create Bike Weapons
	Weapons.Create(PlayerID);
	//-------------------------------------------------------------
	//Global Steering Caps for AI/Player
	Apply_Ai_Steering_Limits_Per_Track();
	Apply_Player_Steering_Limits_Per_Track();
	//-------------------------------------------------------------
	//Apply Player Names
	sprintf_s(gCharBuffer,"Ai#%d",PlayerID);
	Name = (string)gCharBuffer;
	if(PlayerID==gAi_Max_Count)
	{
		Name = (string)gPlayerName;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - UPDATE
///*****************************************************************
void Game_Bike::Update(void)
{
	//-------------------------------------------------------------
	//Replay Bike
	if(cGame_Replay.State==2)
	{
		Update_Replay();
	}
	//-------------------------------------------------------------
	//Player
	else if(PlayerID==gAi_Max_Count)
	{
		Update_Player();
	}
	//-------------------------------------------------------------
	//Normal AI
	else if(Networked_Ai_Type==0)
	{
		Update_Ai_Offline();
	}
	//-------------------------------------------------------------
	//Network controlled by host
	else 
	{
		//Networked_Ai_Type 1 = player
		//Networked_Ai_Type -1 = ai
		Update_Ai_Networked();
	}

	//-------------------------------------------------------------
	//Globals 
	///update Culling Distance
	fDistanceToCam = iVectorLength(&(Manager.vTargetMesh - cGame_Camera.vCamOutput));
	///setup tire & engine spin
	if(gBikesGo)
	{
		float spintarget = iFloatInterpolate(abs(Manager.fAcceleration_Speed),0.0f,9.0f,0.0f,180.0f / (1.0f + abs(Manager.fAcceleration_Speed * 2.0f)));
		///Forward or Backwards rotation?
		if(Manager.fAcceleration_Speed <= -0.0f)
		{
			spintarget = -spintarget;
		}
		fTireSpin += spintarget;
		///Cap Rotation to 360
		if(fTireSpin >= 360.0f)
		{
			fTireSpin -= 360.0f;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - Update_Ai_Offline
///*****************************************************************
void Game_Bike::Update_Ai_Offline(void)
{
	//-------------------------------------------------------------
	//Respawn ?
	if(!Energy.bAlive && 
		gRespawnEnable &&
		gBikesGo)
	{
		if(RespawnTimer<gRespawnTimerMax)
		{
			bRespawning = true;
			RespawnTimer++;
		}
		else
		{
			Manager.Ai_Create(&cGame_RaceTracker.vSpawn[PlayerID],&cGame_RaceTracker.qSpawn[PlayerID],PlayerID);
			Energy.ResetData(PlayerID);
			Weapons.fInDamage = 0.0f;
			//Activate shield for respawn
			Weapons.ShieldRespawnActivator();
			///change Lap to last WP
			if(cGame_RaceTracker.Waypoint_Current[PlayerID]==0 && 
				cGame_RaceTracker.Lap_Current[PlayerID] > 0)
			{
				cGame_RaceTracker.Lap_Current[PlayerID]--;
			}
			//Reset Mesh Animator
			cGame_Mesh.Animator.Mode[PlayerID] = 0;
			//Finish
			bRespawning = false;
			RespawnTimer = 0;
		}
	}
	//-------------------------------------------------------------
	//update controls - acceleration, steering (From Scanner input)
	if(gBikesGo)
	{
		Update_AI_InputSpeedState();
		Update_Ai_SteeringControl();
	}
	//-------------------------------------------------------------
	//update manager
	Manager.Update(&InputSpeedState,
					fSteering,
					false,
					Energy.bAlive);
	//-------------------------------------------------------------
	//update Energy System
	Energy.UpdateAi(&Manager.fCollision_px,
					&Manager.fCollision_pz,
					&Manager.vRotations.x,
					&InputSpeedState,
					&Manager.bHardCollision,
					&Networked_Ai_Type);
	//-------------------------------------------------------------
	//Update Bike Weapons
	Weapons.Crosshair();
	if(gWeaponsEnable &&
		gBikesGo)
	{
		Weapons.Update_Ai(&Manager.vBikeOutput,
							&Manager.qBikeOutput,
							&Manager.fAcceleration_Speed,
							&Networked_Ai_Type);
	}
	//-------------------------------------------------------------
	//Update Bike Colour
	Colour.UpdateAi(&InputSpeedState,
					&Manager.fCollision_px,
					&Energy.fEnergy,
					&Energy.bEnergyRegenActive,
					&Manager.bHardCollision,
					&Networked_Ai_Type);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - Update_Ai_Networked
///*****************************************************************
void Game_Bike::Update_Ai_Networked(void)
{
	//-------------------------------------------------------------
	bool bUseCollision = false;
	bDrift = false;
	//-------------------------------------------------------------
	//Respawn ?
	if(!Energy.bAlive && 
		gRespawnEnable &&
		gBikesGo)
	{
		if(RespawnTimer<gRespawnTimerMax)
		{
			bRespawning = true;
			RespawnTimer++;
		}
		else
		{
			//Manager.Ai_Create(&cGame_RaceTracker.vSpawn[PlayerID],&cGame_RaceTracker.qSpawn[PlayerID],PlayerID);
			//Energy.ResetData(PlayerID);
			Weapons.fInDamage = 0.0f;
			//Activate shield for respawn
			Weapons.ShieldRespawnActivator();
			///change Lap to last WP
			if(cGame_RaceTracker.Waypoint_Current[PlayerID]==0 && 
				cGame_RaceTracker.Lap_Current[PlayerID] > 0)
			{
				cGame_RaceTracker.Lap_Current[PlayerID]--;
			}
			//Reset Mesh Animator
			cGame_Mesh.Animator.Mode[PlayerID] = 0;
			////Finish
			//bRespawning = false;
			//RespawnTimer = 0;
		}
	}
	else
	{
		bRespawning = false;
		RespawnTimer = 0;
	}
	//-------------------------------------------------------------
	//Networked Player Setup
	if(Networked_Ai_Type==1)
	{
		if(NetDrift==1)
		{
			bDrift = true;
		}
	}
	//Networked AI Setup
	else if(Networked_Ai_Type==-1)
	{
		Colour.vBikeColourTarget = gBikeColourWhite;

		bUseCollision = Energy.bAlive;
		///update controls - acceleration, steering (From Scanner input)
		if(gBikesGo)
		{
			Update_Ai_SteeringControl();
		}
	}
	//-------------------------------------------------------------
	//Net - Packet Recieved (Actual Location Server Data)
	if(cGame_Network.Client.bPacketRecieved || 
		cGame_Network.Server.bPacketRecieved[PlayerID])
	{
		//Manager.vBikeOrigin = vNetwork_Recieve;
		//Manager.qBikeOrigin = qNetwork_Recieve;
		iVectorInterpolate(&Manager.vBikeOrigin,&vNetwork_Recieve,&Manager.vBikeOrigin,0.1f);
		iQuaternionInterpolate(&Manager.qBikeOrigin,&qNetwork_Recieve,&Manager.qBikeOrigin,0.1f);
	}
	//Net - Predict Locations
	Manager.Update(&InputSpeedState,
					fSteering,
					bDrift,
					bUseCollision);
	//-------------------------------------------------------------
	//update Energy System
	Energy.UpdateAi(&Manager.fCollision_px,
					&Manager.fCollision_pz,
					&Manager.vRotations.x,
					&InputSpeedState,
					&Manager.bHardCollision,
					&Networked_Ai_Type);
	//-------------------------------------------------------------
	//Network Crosshair
	Weapons.Crosshair();
	if(gWeaponsEnable &&
		gBikesGo)
	{
		Weapons.Update_Ai(&Manager.vBikeOutput,
							&Manager.qBikeOutput,
							&Manager.fAcceleration_Speed,
							&Networked_Ai_Type);
	}
	//-------------------------------------------------------------
	//Update Bike Colour
	Colour.UpdateAi(&InputSpeedState,
					&Manager.fCollision_px,
					&Energy.fEnergy,
					&Energy.bEnergyRegenActive,
					&Manager.bHardCollision,
					&Networked_Ai_Type);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - CONTROLS - Update_AI_InputSpeedState
///*****************************************************************
void Game_Bike::Update_AI_InputSpeedState(void)
{
	//-------------------------------------------------------------
	float fWallCheck = Manager.fScanLengthWall / 2.0f;
	//Dead
	if(!Energy.bAlive)
	{
		InputSpeedState = 0;
	}
	//Walls too close, break
	else if(Manager.fScanLeft_DistanceCp < fWallCheck || Manager.fScanRight_DistanceCp < fWallCheck)
	{
		InputSpeedState = -1;
	}
	//Boost
	else if(gBoostEnable &&
			Energy.fEnergy > 175.0f && 
			!Energy.bEnergyRegenActive &&
			cGame_RaceTracker.bBikeRacing[PlayerID])
	{
			InputSpeedState = 2;//2
	}
	//Go
	else
	{
		InputSpeedState = 1;
		Manager.fAcceleration_TendTo_Forward = 140.0f;
		//AI Catchup System Offline
		if(!iNetworkIsActive() &&
			cGame_RaceTracker.Position_Current[PlayerID] > cGame_RaceTracker.Position_Current[gAi_Max_Count] &&
			Manager.fAcceleration_Speed < Manager.fAcceleration_Max)
		{
			Manager.fAcceleration_TendTo_Forward = 60.0f;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - CONTROLS - Update_Ai_SteeringControl
///*****************************************************************
void Game_Bike::Update_Ai_SteeringControl(void)
{
	//-------------------------------------------------------------
	if(Energy.bAlive)
	{
		Manager.fTendToWalls = 25.0f;
		//Adjust Scanner length depending on track wall size
		if(Manager.fScanLeft_DistanceCp < Manager.fScanLengthWall && 
			Manager.fScanRight_DistanceCp < Manager.fScanLengthWall)
		{
			iFloatTendTo2(Manager.fScanLengthWall,9.0f,20.0f);
		}
		else
		{
			iFloatTendTo2(Manager.fScanLengthWall,100.0f,5.0f);
		}
		//Work out the steering from wall scanners
		float fSteeringMax = iFloatInterpolateSmooth(abs(Manager.fAcceleration_Speed),gAi_Steering_Speed_Min,gAi_Steering_Speed_Max,gAi_Steering_Output_Min,gAi_Steering_Output_Max);
		///New Method 2
		float fWallSample = Manager.fScanLengthWall / 1.3f;///1.5f
		fSteering_Target = iFloatInterpolateSmooth(Manager.fAiSteering,-fWallSample,fWallSample,-fSteeringMax,fSteeringMax);


		//Keep left or Right
		float fKeepLeftOrRight = 0.0f;
		if(Manager.fAiSteering >= 0.0f &&
			Manager.fScanLeft_DistanceCp >= 50.0f)///closer to left wall
		{
			fKeepLeftOrRight = iFloatInterpolate(Manager.fScanLeft_DistanceCp,50.0f,100.0f,0.0f,-fSteeringMax);
			fSteering_Target += (fKeepLeftOrRight / 2.0f);
		}
		else if(Manager.fAiSteering < 0.0f && 
			Manager.fScanRight_DistanceCp >= 50.0f)
		{
			fKeepLeftOrRight = iFloatInterpolate(Manager.fScanRight_DistanceCp,50.0f,100.0f,0.0f,fSteeringMax);
			fSteering_Target += (fKeepLeftOrRight / 2.0f);
		}
		//Output
		iFloatTendTo2(fSteering,fSteering_Target,1.5f);
	}
	else
	{
		Manager.fScanLengthWall = 9.0f;
		Manager.fTendToWalls = 1.5f;
		//Manager.fScanLeft_DistanceCp = 9.0f;
		//Manager.fScanRight_DistanceCp = 9.0f;
		//Output
		iFloatTendTo2(fSteering,0.0f,90.0f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - Update_Player
///*****************************************************************
void Game_Bike::Update_Player(void)
{
	//-------------------------------------------------------------
	//Respawn ?
	if(!Energy.bAlive && 
		gRespawnEnable &&
		gBikesGo)
	{
		if(RespawnTimer<gRespawnTimerMax)
		{
			bRespawning = true;
			RespawnTimer++;
		}
		else
		{
			Manager.Player_Create(&cGame_RaceTracker.vSpawn[PlayerID],&cGame_RaceTracker.qSpawn[PlayerID],PlayerID);
			//Manager.Player_Create(&vSpawnPosition,&vSpawnOrientation,PlayerID);
			Energy.ResetData(PlayerID);
			Weapons.fInDamage = 0.0f;
			//Activate shield for respawn
			Weapons.ShieldRespawnActivator();
			///change Lap to last WP
			if(cGame_RaceTracker.Waypoint_Current[PlayerID]==0 && 
				cGame_RaceTracker.Lap_Current[PlayerID] > 0)
			{
				cGame_RaceTracker.Lap_Current[PlayerID]--;
			}
			//Reset Mesh Animator
			cGame_Mesh.Animator.Mode[PlayerID] = 0;
			//Finish
			bRespawning = false;
			RespawnTimer = 0;
		}
	}
	//-------------------------------------------------------------
	//update controls - acceleration, steering
	if(gBikesGo)
	{
		if(gGameState==0 || 
			!cGame_RaceTracker.bBikeRacing[gAi_Max_Count] ||
			(Weapons.UtilityType==1 && Weapons.bUtilityInUse))
		{
			//AI TAKEOVER
			Update_Player_AiTakeOver();
		}
		else
		{
			//acceleration, steering (From user input)
			Update_Player_InputSpeedState();
			Update_Player_SteeringControl();
			Update_Player_DriftControl();
		}
	}
	//-------------------------------------------------------------
	//update manager
	Manager.Update(&InputSpeedState,
				   fSteering,
				   bDrift,
				   false);
	//-------------------------------------------------------------
	//update Energy System
	Energy.UpdatePlayer(&Manager.fCollision_px,
						&Manager.fCollision_pz,
						&Manager.vRotations.x,
						cGame_Controls.Input_Bike_Axis_Y(),
						&InputSpeedState,
						&Manager.bHardCollision,
						&Networked_Ai_Type);
	//-------------------------------------------------------------
	//Update Bike Weapons
	Weapons.Crosshair();
	if(gWeaponsEnable &&
		gBikesGo)
	{
		Weapons.Update_Player(&Manager.vBikeOutput,
								&Manager.qBikeOutput,
								&Manager.fAcceleration_Speed);
	}
	//-------------------------------------------------------------
	//Update Bike Colour Class
	Colour.UpdatePlayer(&InputSpeedState,
						&Manager.fCollision_px,
						&Energy.fEnergy,
						&Energy.bEnergyRegenActive,
						&Manager.bHardCollision);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - CONTROLS - Update_Player_InputSpeedState
///*****************************************************************
void Game_Bike::Update_Player_InputSpeedState(void)
{
	//-------------------------------------------------------------
	//Dead
	if(!Energy.bAlive)
	{
		InputSpeedState = 0;
	}
	//Boost...
	else if(cGame_Controls.Input_Bike_Boost())
	{
		if(gBoostEnable &&
			Energy.fEnergy > gEnergyLowLimit)
		{
			InputSpeedState = 2;
		}
		else
		{
			InputSpeedState = 1;
		}
	}
	//acceleration...
	else if(cGame_Controls.Input_Bike_Acceleration())
	{
		InputSpeedState = 1;
	}
	//breaks...
	else if(cGame_Controls.Input_Bike_Break())
	{
		InputSpeedState = -1;
	}
	//Idle
	else
	{
		InputSpeedState = 0;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - CONTROLS - Update_Player_SteeringControl
///*****************************************************************
void Game_Bike::Update_Player_SteeringControl(void)
{
	//-------------------------------------------------------------
	//Player takeover setup switch
	if(bAiTakeover)
	{
		Manager.fScanLengthWall = 9.0f;
		Manager.fScanLeft_DistanceCp = 9.0f;
		Manager.fScanRight_DistanceCp = 9.0f;
		Manager.fTendToWalls = 1.5f;

		bAiTakeover = false;
	}
	//-------------------------------------------------------------
	//Work out the steering from inputs, against speed
	float fSteering_Multi = iFloatInterpolateSmooth(abs(Manager.fAcceleration_Speed),gPlayer_Steering_Speed_Min,gPlayer_Steering_Speed_Max,gPlayer_Steering_Output_Min,gPlayer_Steering_Output_Max);
	fSteering_Target = cGame_Controls.Input_Bike_Steering() * fSteering_Multi;
	//Dead - Respawn null value
	if(!Energy.bAlive)
	{
		fSteering_Target = 0.0f;
	}
	///Take a little off steering target to prevent bounce.
	fSteering_Target -= (Manager.fSteeringAdjust / 4.0f);

	//TendToSpeed to match targeting steering(smooth as silk)
	float SteeringTendTo = 1.0f;

	if(bDrift)//new style of drift
	{
		SteeringTendTo = iFloatInterpolateSmooth(abs(fSteering_Target),0.0f,fSteering_Multi,32.0f,24.0f);
	}
	else
	{
		SteeringTendTo = iFloatInterpolateSmooth(abs(fSteering_Target),0.0f,0.1f + abs(fSteering_Target),13.0f,26.0f);
	}
	iFloatTendTo2(fSteering,fSteering_Target,SteeringTendTo);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - CONTROLS - Update_Player_DriftControl
///*****************************************************************
void Game_Bike::Update_Player_DriftControl(void)
{
	//-------------------------------------------------------------
	//Kill
	if(InputSpeedState==2 || //Boost
		abs(Manager.fCollision_px) > 0.25f)//collision
	{
		DriftTimer = 0;
		bDrift = false;
	}
	//Activate
	else if(InputSpeedState==1)//acceleration
	{
		if(DriftTimer < 25 &&
			DriftTimer > 0 &&
			abs(fSteering) > 0.1f)
		{
			bDrift = true;
		}
		DriftTimer = 0;
	}
	//Reset - start activation timer
	else if(InputSpeedState==-1)//breaks
	{
		DriftTimer++;
		bDrift = false;
	}
	else//Idle
	{
		DriftTimer--;
		if(DriftTimer<0)
		{
			DriftTimer = 0;
		}
		bDrift = false;
	}

	//-------------------------------------------------------------
	//Kill
	if(bDrift)
	{
		if(abs(fSteering_Target) <= 0.1f)
		{
			DriftTimerDisable++;
			if(DriftTimerDisable >= 20)
			{
				bDrift = false;
			}
		}
		else if(DriftTimerDisable > 1)
		{
			DriftTimerDisable--;
		}
	}
	else
	{
		DriftTimerDisable = 0;
	}
	//-------------------------------------------------------------
	//Net Drift
	NetDrift = 0;
	if(bDrift)
	{
		NetDrift = 1;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - CONTROLS - Update_Player_AiTakeOver
///*****************************************************************
void Game_Bike::Update_Player_AiTakeOver(void)
{
	//-------------------------------------------------------------
	//AI takeover setup switch
	if(bAiTakeover)
	{
		Manager.fScanLengthWall = 80.0f;
		Manager.fScanLeft_DistanceCp = 80.0f;
		Manager.fScanRight_DistanceCp = 80.0f;
		Manager.fTendToWalls = 25.0f;

		bDrift = false;
		bAiTakeover = false;
	}
	//-------------------------------------------------------------
	//Speed Control
	//-------------------------------------------------------------
	float fWallCheck = Manager.fScanLengthWall / 2.0f;
	//Dead
	if(!Energy.bAlive)
	{
		InputSpeedState = 0;
	}
	//Walls too close, break
	else if(Manager.fScanLeft_DistanceCp < fWallCheck || Manager.fScanRight_DistanceCp < fWallCheck)
	{
		InputSpeedState = -1;
	}
	//Utility Autopilot
	else if(Weapons.UtilityType==1 && Weapons.bUtilityInUse)
	{
		InputSpeedState = 2;
		Energy.fEnergy = cGame_Upgrades.fEnergyMax[PlayerID];
	}
	else
	{
		InputSpeedState = 1;
	}
	//-------------------------------------------------------------
	//Steering control
	//-------------------------------------------------------------
	if(Manager.fScanLeft_DistanceCp < Manager.fScanLengthWall && Manager.fScanRight_DistanceCp < Manager.fScanLengthWall)
	{
		iFloatTendTo2(Manager.fScanLengthWall,9.0f,20.0f);
	}
	else
	{
		iFloatTendTo2(Manager.fScanLengthWall,100.0f,5.0f);
	}
	//Work out the steering from wall scanners
	float fSteeringMax = iFloatInterpolateSmooth(abs(Manager.fAcceleration_Speed),gAi_Steering_Speed_Min,gAi_Steering_Speed_Max,gAi_Steering_Output_Min,gAi_Steering_Output_Max);
	///New Method 2
	float fWallSample = Manager.fScanLengthWall / 1.3f;///1.5f
	fSteering_Target = iFloatInterpolateSmooth(Manager.fAiSteering,-fWallSample,fWallSample,-fSteeringMax,fSteeringMax);
	//-------------------------------------------------------------
	if(Energy.bAlive)
	{
		iFloatTendTo2(fSteering,fSteering_Target,1.5f);
	}
	else
	{
		iFloatTendTo2(fSteering,0.0f,90.0f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - Update_Replay
///*****************************************************************
void Game_Bike::Update_Replay(void)
{
	//-------------------------------------------------------------
	//Replay Bike
	//-------------------------------------------------------------
	//update Energy System
	if(Energy.fEnergy >= 0.0f)
	{
		Energy.bAlive = true;
	}
	else
	{
		//Whoops
		Energy.fEnergy = -1.0f;
		Energy.bAlive = false;
	}
	//-------------------------------------------------------------
	//Respawn ?
	if(!Energy.bAlive && 
		gRespawnEnable &&
		gBikesGo)
	{
		if(RespawnTimer<gRespawnTimerMax)
		{
			bRespawning = true;
			RespawnTimer++;
		}
		else
		{
			Energy.ResetData(PlayerID);
			Weapons.fInDamage = 0.0f;
			//Activate shield for respawn
			Weapons.ShieldRespawnActivator();
			//Reset Mesh Animator
			cGame_Mesh.Animator.Mode[PlayerID] = 0;
			//Finish
			bRespawning = false;
			RespawnTimer = 0;
		}
	}
	//-------------------------------------------------------------
	//update manager
	Manager.Update_Replay(&InputSpeedState,
							fSteering,
							bDrift);
	//-------------------------------------------------------------
	//Update Bike Weapons
	Weapons.Crosshair();
	if(gBikesGo)
	{
		Weapons.Update_Replay(&Manager.vBikeOutput,
								&Manager.qBikeOutput,
								&Manager.fAcceleration_Speed);
	}
	//-------------------------------------------------------------
	//Update Bike Colour Class
	Colour.Update_Replay(&InputSpeedState,
						&Manager.fCollision_px,
						&Energy.fEnergy,
						&Energy.bEnergyRegenActive,
						&Manager.bHardCollision);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - CONTROLS - Apply_Player_Steering_Limits_Per_Track
///*****************************************************************
void Game_Bike::Apply_Player_Steering_Limits_Per_Track(void)
{
	//-------------------------------------------------------------
	if(PlayerID==gAi_Max_Count)
	{
		//Default - all tracks unless specifed below.
		//gPlayer_Steering_Speed_Min		= 0.5f;
		//gPlayer_Steering_Speed_Max		= 7.5f;
		//gPlayer_Steering_Output_Min		= 0.625f;
		//gPlayer_Steering_Output_Max		= 2.4f;

		gPlayer_Steering_Speed_Min		= 0.0f;
		gPlayer_Steering_Speed_Max		= 10.0f;
		gPlayer_Steering_Output_Min		= 0.7f;
		gPlayer_Steering_Output_Max		= 3.1f;
		//-------------------------------------------------------------
		//Custom Steering Limits, Per track basis
		if(gGameState==2)//Silence
		{
			gPlayer_Steering_Output_Max		= 1.6f;
		}
		else if(gGameState==3)//Phantom
		{
			gPlayer_Steering_Output_Max		= 2.6f;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - BIKE - CONTROLS - Apply_Ai_Steering_Limits_Per_Track
///*****************************************************************
void Game_Bike::Apply_Ai_Steering_Limits_Per_Track(void)
{
	//-------------------------------------------------------------
	if(PlayerID==0)
	{
		///new
		gAi_Steering_Speed_Min			= 0.0f;
		gAi_Steering_Speed_Max			= 10.0f;
		gAi_Steering_Output_Min			= 1.8f;
		gAi_Steering_Output_Max			= 5.0f;

		if(gGameState==2)///Silence
		{
			gAi_Steering_Speed_Min			= 0.0f;
			gAi_Steering_Speed_Max			= 10.0f;
			gAi_Steering_Output_Min			= 0.9f;
			gAi_Steering_Output_Max			= 1.3f;
		}
		//else if(gGameState==3)///Phantom
		//{
		//	gAi_Steering_Speed_Min			= 0.6f;
		//	gAi_Steering_Speed_Max			= 7.5f;
		//	gAi_Steering_Output_Min			= 1.8f;
		//	gAi_Steering_Output_Max			= 5.0f;
		//}
		//else if(gGameState==10)///Arena Rez
		//{
		//	gAi_Steering_Speed_Min			= 0.6f;
		//	gAi_Steering_Speed_Max			= 7.5f;
		//	gAi_Steering_Output_Min			= 1.8f;
		//	gAi_Steering_Output_Max			= 5.0f;
		//}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - DESTROY
///*****************************************************************
void Game_Bike::Destroy(void)
{
	//-------------------------------------------------------------
	//Destroy Bike Weapons
	Weapons.Destroy();
	//-------------------------------------------------------------
	//Energy System
	Energy.Destroy();
	//Bike Colours
	Colour.Destroy();
	//manager
	Manager.Destroy();
	//reset data
	ResetData();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - BIKE - ZERO DATA
///*****************************************************************
void Game_Bike::ResetData(void)
{
	//-------------------------------------------------------------
	Name									= "";
	PlayerID								= 0;
	Networked_Ai_Type						= 0;
	vNetwork_Recieve						= D3DXVECTOR3(0.0f,0.0f,0.0f);
	qNetwork_Recieve						= D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	// Speed States - sent to bikemanager
	InputSpeedState							= 0;
	//Accel - Steering - Updates
	fSteering								= 0.0f;
	fSteering_Target						= 0.0f;
	//mesh
	fTireSpin								= 0.0f;
	//Culling Distance
	fDistanceToCam							= 500.0f;
	//Drift (RidgeRacer Style)
	bDrift									= false;
	NetDrift								= 0;
	DriftTimer								= 0;
	DriftTimerDisable						= 0;
	//Respawn
	RespawnTimer							= 0;
	bRespawning								= false;
	//PLAYER
	bAiTakeover								= false;
	//---------------------------------------------------------
}