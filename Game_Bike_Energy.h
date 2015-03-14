#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Bike_Energy
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Data
		float									fEnergy;
		float									fEnergyRegenRate;
		bool									bEnergyRegenActive;
		float									fRegenFade;
		bool									bRegenFade;
		//Energy Pickup
		bool									bEnergyPickedUp;
		int										EnergyPickedUpTimer;
		//Alive-dead status
		bool									bAlive;
		//Net Extras
		int										NetEnergyRegen;
		//---------------------------------------------------------
		//constructors
		Game_Bike_Energy(void);
		~Game_Bike_Energy(void);
		//---------------------------------------------------------
		//functions
		void Create(int PlayerID);
		void UpdateAi(float* fCollision_px_in,
					  float* fCollision_pz_in, 
					  float* fRotation_x_in, 
					  int* InputSpeedState,
					  bool* HardCollision_In,
					  int* NetAiType);
		void UpdatePlayer(float* fCollision_px_in, 
						  float* fCollision_pz_in,
						  float* fRotation_x_in, 
						  float xInputAxis,
						  int* InputSpeedState,
						  bool* HardCollision_In,
						  int* NetAiType);
		void ResetData(int PlayerID);
		void Destroy(void);
		//-------------------------------------------------------------
	private:
		//-------------------------------------------------------------
		//data
		int										Player_ID;
		int										BoostScaleTimer;
		//-------------------------------------------------------------
		void Update(float* fCollision_px_in, 
					float* fCollision_pz_in,
					int* InputSpeedState,
					bool* HardCollision_In,
					int* NetAiType);
		//-------------------------------------------------------------
};
