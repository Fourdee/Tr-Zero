#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Mode_WeaponsPickup
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Pickup Data
		bool						bPickupsEnable;
		bool						PickupReady[MAX_WEAPON_PICKUPS];
		D3DXVECTOR3					vPickup[MAX_WEAPON_PICKUPS];
		D3DXQUATERNION				qPickup[MAX_WEAPON_PICKUPS];
		//Reset Timer
		int							PickupResetTimer[MAX_WEAPON_PICKUPS];
		//---------------------------------------------------------
		//constructors
		Game_Mode_WeaponsPickup(void);
		~Game_Mode_WeaponsPickup(void);
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
