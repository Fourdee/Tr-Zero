//-----------------------------------------------------------------
// Bike Colour class
// Dans version! :)
//
// Sets up: all required colour vectors for all current bikes
// Updates: colours using global_data vector targets 
//
// Updates applied in Game_Bike_Player/AI SHADER UPDATE
// 
// TODO:
// 
// - Admire 40 bikes with unique colours at 60fps! :)
// - 
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Bike_Colour.h"
//-----------------------------------------------------------------
Game_Bike_Colour::Game_Bike_Colour(void)
{
	//-------------------------------------------------------------
	ResetData(0);
	//-------------------------------------------------------------
}

Game_Bike_Colour::~Game_Bike_Colour(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - COLOUR - CREATE
///*****************************************************************
void Game_Bike_Colour::Create(int PlayerID)
{
	//-------------------------------------------------------------
	ResetData(PlayerID);
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - COLOUR - UPDATE
///*****************************************************************
void Game_Bike_Colour::Update(int* InputSpeedState, 
								float* Collision,
								float* Energy,
								bool* bEnergyRegenActive,
								bool* HardCollision_In)
{
	//-------------------------------------------------------------
	//Tend To Speeds Ingame
	TendToBike					= 60.0f;
	//Tend To Speeds Menu
	if(gMenuId==8)
	{
		TendToBike				= 3.0f;
	}
	TendToEngine				= 60.0f;
	TendToBreak					= 20.0f;
	TendToShield				= 40.0f;
	//-------------------------------------------------------------
	//Update Bike SpeedState (get global colours)
	//-------------------------------------------------------------
	if(*InputSpeedState==-1)//breaks
	{
		vEngineColourTarget = gColourEngineBreak;
		TendToBreak = 10.0f;
	}
	else if(*InputSpeedState==0)//Idle
	{
		vEngineColourTarget = gColourEngineIdle;
		TendToBreak = 45.0f;
	}
	else if(*InputSpeedState==1)//acceleration
	{
		vEngineColourTarget = gColourEngineAccel;//vBikeColourTarget
		TendToBreak = 45.0f;
	}
	else if(*InputSpeedState==2)//Boost
	{
		vEngineColourTarget = gColourEngineBoost;
		TendToBreak = 20.0f;
	}
	
	//-------------------------------------------------------------
	//Update Collision Changes
	//-------------------------------------------------------------
	float ColourColReduction = 0.0f;
	//Adjust Colours in a Collision
	if(abs(*Collision) > 1.0f || *HardCollision_In)
	{
		TendToBike = 20.0f;
		if(*HardCollision_In){ColourColReduction = 2.0f;}
		else{ColourColReduction = 2.0f + abs(*Collision * 5.0f);}
		vBikeColour /= ColourColReduction;

		//Shield scaled against energy pool remaining
		//eg: pure red at low health, white/orange at full etc.
		float ShieldTarget = iFloatInterpolate(*Energy,0.0f,cGame_Upgrades.fEnergyMax[Player_ID],0.1f,1.0f);
		iFloatTendTo2(vShieldColour.x,1.0f,2.0f);
		iFloatTendTo2(vShieldColour.y,ShieldTarget,2.0f);
		iFloatTendTo2(vShieldColour.z,ShieldTarget,2.0f);
	}
	//Warning Shield Animation
	else if(*Energy < gEnergyWarningLimit)
	{
		tEnergyWarning++;

		vBikeColour.x = 0.0f;
		vBikeColour.y = 0.0f;
		vBikeColour.z = 0.0f;

		if(tEnergyWarning < 25)
		{
			iFloatTendTo2(vShieldColour.x,1.5f,5.0f);
			iFloatTendTo2(vShieldColour.y,0.0f,5.0f);
			iFloatTendTo2(vShieldColour.z,0.0f,5.0f);
		}
		else if(tEnergyWarning >= 50)
		{
			tEnergyWarning = 0;
		}
	}
	//Regen Shield Animation
	else if(*bEnergyRegenActive)
	{
		iFloatTendTo2(vShieldColour.x,vBikeColour.x * 3.0f,20.0f);
		iFloatTendTo2(vShieldColour.y,vBikeColour.y * 3.0f,20.0f);
		iFloatTendTo2(vShieldColour.z,vBikeColour.z * 3.0f,20.0f);
	}

	//-------------------------------------------------------------
	//Update Colours
	//-------------------------------------------------------------
	//Update Bike Colour
	iVector3TendTo(&vBikeColour,&vBikeColourTarget,TendToBike);
	//Update EngineGlow (subpart) Colour
	iVector3TendTo(&vEngineColour,&vEngineColourTarget,TendToEngine);
	//Update Shield Colour
	iVector3TendTo(&vShieldColour,&vShieldColourTarget,TendToShield);
	//Update Shield Colour Total (for Mesh activation)
	fShieldColourTotal = (vShieldColour.x + vShieldColour.y + vShieldColour.z);
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - COLOUR - UPDATE PLAYER
///*****************************************************************
void Game_Bike_Colour::UpdatePlayer(int* InputSpeedState, 
									float* Collision,
									float* Energy,
									bool* bEnergyRegenActive,
									bool* HardCollision_In)
{
	//-------------------------------------------------------------
	//Update Bike Colour (Selector)
	//-------------------------------------------------------------
	//Toggle colours
	if(cGame_Controls.Input_Action_Colour())
	{
		ColourSelector++;
		if(ColourSelector>4)
		{
			ColourSelector = 0;
		}
		bSetupTargetColour = true;
	}
	//Apply
	else if(bSetupTargetColour)
	{
		///Define Select Colour Target (eg: player/pool colour)
		if(ColourSelector==0) //Player Colour
		{
			vBikeColourTarget = gBikeColourUser;
		}
		else if(ColourSelector==1)
		{
			vBikeColourTarget = gBikeColourGreen;
		}
		else if(ColourSelector==2)
		{
			vBikeColourTarget = gBikeColourOrange;
		}
		else if(ColourSelector==3)
		{
			vBikeColourTarget = gBikeColourBlue;
		}
		else if(ColourSelector==4)
		{
			vBikeColourTarget = gBikeColourPink;
		}
		bSetupTargetColour = false;
	}
	//-------------------------------------------------------------
	//Update Colour Tranisitions
	if(gBikesGo || gPaused)
	{
		Update(InputSpeedState,Collision,Energy,bEnergyRegenActive,HardCollision_In);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - COLOUR - UPDATE AI
///*****************************************************************
void Game_Bike_Colour::UpdateAi(int* InputSpeedState, 
								float* Collision,
								float* Energy,
								bool* bEnergyRegenActive,
								bool* HardCollision_In,
								int* NetAiType)
{
	//-------------------------------------------------------------
	//Setup colours
	if(bSetupTargetColour)
	{
		if(gBikeColourSelectAi==0)
		{
			///Create a Random Colour
			float h = iFloatRand(0.0f,359.0f);
			vBikeColourTarget = HSVtoRGB(h);
		}
		else if(gBikeColourSelectAi==1)
		{
			vBikeColourTarget = gBikeColourOrange;
		}
		else if(gBikeColourSelectAi==2)
		{
			vBikeColourTarget = gBikeColourBlue;
		}
		else if(gBikeColourSelectAi==3)
		{
			vBikeColourTarget = gBikeColourPink;
		}
		else if(gBikeColourSelectAi==4)
		{
			vBikeColourTarget = gBikeColourWhite;
		}
		//-------------------------------------------------------------
		//Net override
		if(*NetAiType==-1 || cGame_Network.Server.State==2)///Net Ai
		{
			vBikeColourTarget = gBikeColourWhite;
		}
		//Done
		bSetupTargetColour = false;
	}
	//-------------------------------------------------------------
	//Update Colour Tranisitions
	if(gBikesGo || gPaused)
	{
		Update(InputSpeedState,Collision,Energy,bEnergyRegenActive,HardCollision_In);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - COLOUR - Update_Replay
///*****************************************************************
void Game_Bike_Colour::Update_Replay(int* InputSpeedState, 
								float* Collision,
								float* Energy,
								bool* bEnergyRegenActive,
								bool* HardCollision_In)
{
	//-------------------------------------------------------------
	//Update Colour Tranisitions
	if(gBikesGo || gPaused)
	{
		Update(InputSpeedState,Collision,Energy,bEnergyRegenActive,HardCollision_In);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - COLOUR - DESTROY
///*****************************************************************
void Game_Bike_Colour::Destroy(void)
{
	//-------------------------------------------------------------
	ResetData(0);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - COLOUR - ZERO DATA
///*****************************************************************
void Game_Bike_Colour::ResetData(int PlayerID)
{
	//-------------------------------------------------------------
	Player_ID								= PlayerID;
	//Colour Data
	vBikeColour								= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vBikeColourTarget						= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vEngineColour							= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vEngineColourTarget						= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vShieldColour							= D3DXVECTOR3(0.0f,0.0f,0.0f);
	vShieldColourTarget						= D3DXVECTOR3(0.0f,0.0f,0.0f);
	fShieldColourTotal						= 0.0f;
	//Select
	ColourSelector							= 0;
	//Warning Timer
	tEnergyWarning							= 0;
	//Tend To Speeds
	TendToBike								= 90.0f;
	TendToEngine							= 60.0f;
	TendToBreak								= 20.0f;
	TendToShield							= 20.0f;
	//Apply colour
	bSetupTargetColour						= true;
	//---------------------------------------------------------
}