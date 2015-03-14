//-----------------------------------------------------------------
// Bike Energy class
//
// Sets up: all required energy pools for all current bikes
// Updates: Energy pools
//
// Updates applied in Game_Bike_Player/AI UPDATE
// 
// TODO:
// 
// - ...
// - 
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Bike_Energy.h"
//-----------------------------------------------------------------
Game_Bike_Energy::Game_Bike_Energy(void)
{
	//-------------------------------------------------------------
	ResetData(0);
	//-------------------------------------------------------------
}

Game_Bike_Energy::~Game_Bike_Energy(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - ENERGY - CREATE
///*****************************************************************
void Game_Bike_Energy::Create(int PlayerID)
{
	//-------------------------------------------------------------
	ResetData(PlayerID);
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - ENERGY - UPDATE
///*****************************************************************
void Game_Bike_Energy::Update(float* fCollision_px_in, 
								float* fCollision_pz_in,
								int* InputSpeedState,
								bool* HardCollision_In,
								int* NetAiType)
{
	//-------------------------------------------------------------
	//Alive
	if(fEnergy >= 0.0f)
	{
		bAlive = true;
		//Regen Tick Upgrade
		if(cGame_Timer.bRegenTimer)
		{
			if (*NetAiType == 0)///Player and offline bikes only.
			{
				fEnergy += cGame_Upgrades.fEnergyTickRegen[Player_ID];
			}
		}
		//Cap Energy to Max
		if(fEnergy >= cGame_Upgrades.fEnergyMax[Player_ID])
		{
			fEnergy = cGame_Upgrades.fEnergyMax[Player_ID];
			bEnergyPickedUp = false;
			bEnergyRegenActive = false;
			bRegenFade = false;
		}
		//Collision
		if(abs(*fCollision_pz_in) > 0.1f)///Front Collision
		{
			fEnergy -= *fCollision_pz_in;
		}
		else if(abs(*fCollision_px_in) > 1.0f)///Side Collision
		{
			fEnergy -= abs(*fCollision_px_in) * 3.0f;// / 2.0f
		}
		else if(*HardCollision_In)
		{
			fEnergy -= 1.0f;
		}
		//Boost
		if(*InputSpeedState==2)
		{
			/// Players who hold boost down will loose out
			/// Promote 1 second button tap/hold boost system
			if(BoostScaleTimer < 180)
			{
				BoostScaleTimer++;
			}
			float fBoostRemove = iFloatInterpolate((float)BoostScaleTimer,0.0f,180.0f,0.3f,0.6f);
			fEnergy -= fBoostRemove;
		}
		else ///reset boost timer
		{
			BoostScaleTimer = 0;
		}
		//Energy Regen System
		if(bEnergyRegenActive)
		{
			bRegenFade = true;
			fRegenFade = 1.0f;
			fEnergy += fEnergyRegenRate;
		}
		else if(bRegenFade)
		{
			if(fRegenFade < 4.0f && 
				fEnergy < cGame_Upgrades.fEnergyMax[Player_ID])
			{
				fRegenFade += 0.05f;
				fEnergy += fEnergyRegenRate / fRegenFade;
			}
			else///Reset fade
			{
				bRegenFade = false;
				fRegenFade = 1.0f;
			}
		}
	}
	//-------------------------------------------------------------
	//Dead
	else
	{
		//Whoops
		fEnergy = -1.0f;
		bAlive = false;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - ENERGY - PLAYER
///*****************************************************************
void Game_Bike_Energy::UpdatePlayer(float* fCollision_px_in, 
									float* fCollision_pz_in,
									float* fRotation_x_in, 
									float xInputAxis,
									int* InputSpeedState,
									bool* HardCollision_In,
									int* NetAiType)
{
	//-------------------------------------------------------------
	bEnergyRegenActive = false;
	NetEnergyRegen = 0;
	//-------------------------------------------------------------
	//Energy Pickup
	if(bEnergyPickedUp)
	{
		if(EnergyPickedUpTimer < 30)
		{
			NetEnergyRegen = 2;
			bEnergyRegenActive = true;
			EnergyPickedUpTimer++;
		}
		else
		{
			bEnergyPickedUp = false;
			EnergyPickedUpTimer = 0;
		}
	}
	//Player Rotation/Y_Axis energy regen check
	else if(*InputSpeedState != 2 &&
			abs(*fRotation_x_in) >= 0.2f)
	{
		if((*fRotation_x_in <= -0.2f && xInputAxis <= -0.3f) ||
			(*fRotation_x_in >= 0.2f && xInputAxis >= 0.3f))
		{
			bEnergyRegenActive = true;
			NetEnergyRegen = 1;
		}
	}
	//-------------------------------------------------------------
	//Apply updates
	if(gBikesGo && 
		gRaceState>=1 &&
		cGame_RaceTracker.bBikeRacing[Player_ID])
	{
		Update(fCollision_px_in, fCollision_pz_in, InputSpeedState, HardCollision_In, NetAiType);
	}
	//Disable Regen Fade at end of race.
	else if(bRegenFade)
	{
		bRegenFade = false;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - ENERGY - Ai
///*****************************************************************
void Game_Bike_Energy::UpdateAi(float* fCollision_px_in, 
								float* fCollision_pz_in,
								float* fRotation_x_in, 
								int* InputSpeedState,
								bool* HardCollision_In,
								int* NetAiType)
{
	//-------------------------------------------------------------
	bEnergyRegenActive = false;
	//-------------------------------------------------------------
	//Offline
	if (*NetAiType == 0)
	{
		NetEnergyRegen = 0;
		//Energy Pickup
		if(bEnergyPickedUp)
		{
			if(EnergyPickedUpTimer < 30)
			{
				NetEnergyRegen = 2;
				bEnergyRegenActive = true;
				EnergyPickedUpTimer++;
			}
			else
			{
				bEnergyPickedUp = false;
				EnergyPickedUpTimer = 0;
			}
		}
		//simple Regen
		else if(abs(*fRotation_x_in) > 0.75f && 
			*InputSpeedState != 2)
		{
			NetEnergyRegen = 1;
			bEnergyRegenActive = true;
		}
		///Null Front Collision Damage for AI bikes
		//fCollision_pz_in = 0.0f;
	}
	//-------------------------------------------------------------
	//Online
	else
	{
		if (*NetAiType == 1)//player
		{
			fEnergyRegenRate = gEnergyRegenRate;
		}
		//else if (*NetAiType == -1)//ai
		//{
		//	///Null Front Collision Damage for AI bikes
		//	fCollision_pz_in = 0.0f;
		//}

		//Energy Pickup
		if(NetEnergyRegen==2)
		{
			if(EnergyPickedUpTimer < 30)
			{
				bEnergyRegenActive = true;
				EnergyPickedUpTimer++;
			}
			else
			{
				EnergyPickedUpTimer = 0;
			}
		}
		//simple Regen
		else if(NetEnergyRegen==1)
		{
			bEnergyRegenActive = true;
		}
	}
	//-------------------------------------------------------------
	//Apply updates
	if(gBikesGo && 
		gRaceState>=1 &&
		cGame_RaceTracker.bBikeRacing[Player_ID])
	{
		Update(fCollision_px_in, fCollision_pz_in, InputSpeedState, HardCollision_In, NetAiType);
	}
	//Disable Regen Fade at end of race.
	else if(bRegenFade)
	{
		bRegenFade = false;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - ENERGY - DESTROY
///*****************************************************************
void Game_Bike_Energy::Destroy(void)
{
	//-------------------------------------------------------------
	ResetData(0);
	//-------------------------------------------------------------
}

///*****************************************************************
///GAME - ENERGY - ZERO DATA
///*****************************************************************
void Game_Bike_Energy::ResetData(int PlayerID)
{
	//-------------------------------------------------------------
	Player_ID									= PlayerID;

	fRegenFade									= 1.0f;
	bRegenFade									= false;
	fEnergy										= cGame_Upgrades.fEnergyMax[PlayerID] / 2.0f;
	bEnergyRegenActive							= false;
	BoostScaleTimer								= 0;
	bAlive										= true;
	//Energy Pickup
	bEnergyPickedUp								= false;
	EnergyPickedUpTimer							= 0;
	//Regen Rate Player
	if(PlayerID==gAi_Max_Count)
	{
		fEnergyRegenRate						= gEnergyRegenRate;
	}
	//Regen Rate Ai
	else if(gAiDifficuty==0)
	{
		fEnergyRegenRate					= gEnergyRegenRate * 0.5f;
	}
	else if(gAiDifficuty==1)
	{
		fEnergyRegenRate					= gEnergyRegenRate * 0.7f;
	}
	else if(gAiDifficuty==2)
	{
		fEnergyRegenRate					= gEnergyRegenRate * 0.8f;
	}
	else if(gAiDifficuty==3)
	{
		fEnergyRegenRate					= gEnergyRegenRate * 0.9f;
	}
	else if(gAiDifficuty==4)
	{
		fEnergyRegenRate					= gEnergyRegenRate;
	}
	//-------------------------------------------------------------
	//Net Extras
	NetEnergyRegen							= 0;
	//-------------------------------------------------------------
}