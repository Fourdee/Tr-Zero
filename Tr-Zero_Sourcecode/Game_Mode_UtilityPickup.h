#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Mode_UtilityPickup
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Pickup Data
		bool						bPickupsEnable;
		bool						PickupReady[MAX_UTILITY_PICKUPS];
		D3DXVECTOR3					vPickup[MAX_UTILITY_PICKUPS];
		D3DXQUATERNION				qPickup[MAX_UTILITY_PICKUPS];
		//Reset Timer
		int							PickupResetTimer[MAX_UTILITY_PICKUPS];
		//---------------------------------------------------------
		//constructors
		Game_Mode_UtilityPickup(void);
		~Game_Mode_UtilityPickup(void);
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
