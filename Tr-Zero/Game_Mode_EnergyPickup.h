#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Mode_EnergyPickup
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Pickup Data
		bool						bPickupsEnable;
		bool						PickupReady[MAX_ENERGY_PICKUPS];
		D3DXVECTOR3					vPickup[MAX_ENERGY_PICKUPS];
		D3DXQUATERNION				qPickup[MAX_ENERGY_PICKUPS];
		//Reset Timer
		int							PickupResetTimer[MAX_ENERGY_PICKUPS];
		//---------------------------------------------------------
		//constructors
		Game_Mode_EnergyPickup(void);
		~Game_Mode_EnergyPickup(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		void ZeroData(void);
		void PickupTrackLocations(void);
	//-------------------------------------------------------------	
};
