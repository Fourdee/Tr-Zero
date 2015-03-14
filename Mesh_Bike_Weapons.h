#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Mesh_Bike_Weapons
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		MD5MESH*					Energy_A;
		MD5MESH*					Targeting;
		int							TOTAL_CREATE_ALL; //total = one per bike, of active
		int							TOTAL_CREATE_PRIMARY_PROJECTILE;
		//---------------------------------------------------------
		//Primary Weapon
		MD5MESH*					P_Primary_Glow;
		//---------------------------------------------------------
		//Secondary Weapons Charging
		MD5MESH*					Secondary_Charging;
		//---------------------------------------------------------
		//Secondary Weapons Projectile (MISSILE)
		MD5MESH*					P_Missile_Projectile[2];
		//---------------------------------------------------------
		//Secondary Weapons Projectile (MISSILE_EXPLOSION)
		MD5MESH*					P_Missile_Explosion[2];
		bool						bExplosionInUse[40];///one for each bike
		int							ExplosionTimer[40];
		float						ExplosionUpgradeScale[40];
		D3DXVECTOR3					vExplosionColour[40];
		//---------------------------------------------------------
		//Secondary Weapons Projectile (SHOCKWAVE)
		MD5MESH*					P_Shockwave_Projectile;
		//---------------------------------------------------------
		//Secondary Weapons Projectile (AOE BURST)
		MD5MESH*					P_EMBurst_Projectile;
		//---------------------------------------------------------
		//Secondary Weapons Projectile (Rail)
		MD5MESH*					Rail_Projectile;
		//---------------------------------------------------------
		//Utility Weapons (SHIELD)
		MD5MESH*					Shield_Inv;
		//---------------------------------------------------------
		//Utility Weapons (WARP)
		MD5MESH*					U_Warp[2];
		//---------------------------------------------------------
		//Utility Weapons (DOUBLE DAMAGE)
		MD5MESH*					U_DoubleD[2];
		//---------------------------------------------------------
		//Utility Weapons (AUTO PILOT)
		MD5MESH*					U_AutoP[2];
		//---------------------------------------------------------
		//constructors
		Mesh_Bike_Weapons(void);
		~Mesh_Bike_Weapons(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Data
		///Shared Double Damage offsets
		D3DXVECTOR3					vDoubleD_L;
		D3DXVECTOR3					vDoubleD_R;

		//---------------------------------------------------------
		//functions
		void Player_Update(D3DXVECTOR3* v1, D3DXQUATERNION* q1);
		void Update_Common(int Index, D3DXVECTOR3* v1, D3DXQUATERNION* q1);

		void Energy_Regen(int Index, bool bActive, D3DXVECTOR3* v1, D3DXQUATERNION* q1, D3DXVECTOR3* vColour);
		void Secondary_Charge(int Index, bool bCharge, int* Time, int* TimeMax, D3DXVECTOR3* v1, D3DXQUATERNION* q1);
		void Secondary(int Index, int* Weapon, int* Time, int* TimeMax, D3DXVECTOR3* v1, D3DXQUATERNION* q1, D3DXVECTOR3* vColour);
		void Missile_Explosion(int Index, D3DXVECTOR3* v1);
		void Utility(int Index, bool bShow, int* Weapon, int* Time, int* TimeMax, D3DXVECTOR3* v1, D3DXQUATERNION* q1, D3DXVECTOR3* vColour);

		void ImpostersCreate(void);
		void ImpostersDestroy(void);
		void ShaderUpdate(void);
		void Update_TexturePan(void);
		void Update_Shared(void);
	//-------------------------------------------------------------
};
