#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Bike_Colour
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Colour Data
		D3DXVECTOR3							vBikeColour; 
		D3DXVECTOR3							vBikeColourTarget; 
		D3DXVECTOR3							vEngineColour;
		D3DXVECTOR3							vEngineColourTarget;
		D3DXVECTOR3							vShieldColour;
		D3DXVECTOR3							vShieldColourTarget;
		float								fShieldColourTotal;
		//Player Data
		int									ColourSelector;
		//Warning Timer
		int									tEnergyWarning;
		//Apply colour
		bool								bSetupTargetColour;
		//---------------------------------------------------------
		//constructors
		Game_Bike_Colour(void);
		~Game_Bike_Colour(void);
		//---------------------------------------------------------
		//functions
		void Create(int PlayerID);
		void UpdatePlayer(int* InputSpeedState, 
							float* Collision,
							float* Energy,
							bool* bEnergyRegenActive,
							bool* HardCollision_In);
		void UpdateAi(int* InputSpeedState, 
						float* Collision,
						float* Energy,
						bool* bEnergyRegenActive,
						bool* HardCollision_In,
						int* NetAiType);
		void Update_Replay(int* InputSpeedState, 
							float* Collision,
							float* Energy,
							bool* bEnergyRegenActive,
							bool* HardCollision_In);
		void Destroy(void);
	//-------------------------------------------------------------
	private:
		//-------------------------------------------------------------
		//data
		int									Player_ID;
		float								TendToBike;
		float								TendToEngine;
		float								TendToBreak;
		float								TendToShield;
		//---------------------------------------------------------
		//functions
		void Update(int* InputSpeedState, 
					float* Collision,
					float* Energy,
					bool* bEnergyRegenActive,
					bool* HardCollision_In);
		void ResetData(int PlayerID);
		//-------------------------------------------------------------
	//-------------------------------------------------------------
};
