#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Global_Texture_Bike_Weapons
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		TEXTURE2D*						Bike_Target_A;
		TEXTURE2D*						NULL_Alpha;
		TEXTURE2D*						Bike_Energy_B;
		TEXTURE2D*						Bike_Energy_C;
		TEXTURE2D*						Charge_B;
		TEXTURE2D*						Charge_C;
		TEXTURE2D*						P_EMBurst_emi;

		TEXTURE2D*						P_Primary_em;

		TEXTURE2D*						P_Missile_0_dm;
		TEXTURE2D*						P_Missile_0_nm;
		TEXTURE2D*						P_Missile_0_sm;
		TEXTURE2D*						P_Missile_1_em;

		TEXTURE2D*						P_Shoxwave_A;
		TEXTURE2D*						P_Shoxwave_B;
		TEXTURE2D*						P_Shoxwave_C;

		TEXTURE2D*						P_Explosion_0_dm;
		TEXTURE2D*						P_Explosion_0_nm;
		TEXTURE2D*						P_Explosion_1_em;

		TEXTURE2D*						U_Warp_0_dm;
		TEXTURE2D*						U_Warp_0_nm;
		TEXTURE2D*						U_Warp_1_em;

		TEXTURE2D*						U_DoubleD_em;

		TEXTURE2D*						U_AutoP_0_em;
		TEXTURE2D*						U_AutoP_1_em;

		TEXTURE2D*						Rail_Projectile;
		TEXTURE2D*						Particle_Explosion;
		TEXTURE2D*						Particle_WeaponEmission;
		TEXTURE2D*						ShieldInv_B;
		TEXTURE2D*						ShieldInv_C;
		//---------------------------------------------------------
		//constructors
		Global_Texture_Bike_Weapons(void);
		~Global_Texture_Bike_Weapons(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void SamplerSet(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
