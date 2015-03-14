//-----------------------------------------------------------------
// About:
//
// name: "Global_Texture_Bike_Weapons.cpp:
//
// included in: "Game_Asset_Global_Textures.h"
//
// usage: 
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Global_Texture_Bike_Weapons.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - WEAPONS - CONSTRUCTORS
///*****************************************************************
Global_Texture_Bike_Weapons::Global_Texture_Bike_Weapons(void)
{
	//-------------------------------------------------------------
	Bike_Target_A					= NULL;
	NULL_Alpha						= NULL;
	Bike_Energy_B					= NULL;
	Bike_Energy_C					= NULL;
	Charge_B						= NULL;
	Charge_C						= NULL;
	P_EMBurst_emi					= NULL;

	P_Primary_em					= NULL;

	P_Missile_0_dm					= NULL;
	P_Missile_0_nm					= NULL;
	P_Missile_0_sm					= NULL;
	P_Missile_1_em					= NULL;

	P_Shoxwave_A					= NULL;
	P_Shoxwave_B					= NULL;
	P_Shoxwave_C					= NULL;

	P_Explosion_0_dm				= NULL;
	P_Explosion_0_nm				= NULL;
	P_Explosion_1_em				= NULL;

	U_Warp_0_dm						= NULL;
	U_Warp_0_nm						= NULL;
	U_Warp_1_em						= NULL;

	U_DoubleD_em					= NULL;

	U_AutoP_0_em					= NULL;
	U_AutoP_1_em					= NULL;

	Rail_Projectile					= NULL;
	Particle_Explosion				= NULL;
	Particle_WeaponEmission			= NULL;
	ShieldInv_B						= NULL;
	ShieldInv_C						= NULL;
	//-------------------------------------------------------------
}

Global_Texture_Bike_Weapons::~Global_Texture_Bike_Weapons(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - WEAPONS - CREATE
///*****************************************************************
void Global_Texture_Bike_Weapons::Create(void)
{
	//-------------------------------------------------------------
	Bike_Target_A = iTexture2DCreate("trzero_res\\textures\\shadow_map\\target_A.dds");
	NULL_Alpha = iTexture2DCreate("trzero_res\\textures\\emissive_map\\alpha_blank.dds");
	Bike_Energy_B = iTexture2DCreate("trzero_res\\textures\\shadow_map\\energy_B.dds");
	Bike_Energy_C = iTexture2DCreate("trzero_res\\textures\\shadow_map\\energy_C.dds");
	Charge_B = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\charge_B.dds");
	Charge_C = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\charge_C.dds");

	P_EMBurst_emi = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\P_EMBurst_emi.dds");

	P_Primary_em = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\P_Primary_emi.dds");

	P_Missile_0_dm = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\weapons\\P_Missile_0_dif.dds");
	P_Missile_0_nm = iTexture2DCreate("trzero_res\\textures\\normal_map\\weapons\\P_Missile_0_nor.dds");
	P_Missile_0_sm = iTexture2DCreate("trzero_res\\textures\\specular_map\\weapons\\P_Missile_0_spe.dds");
	P_Missile_1_em = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\P_Missile_1_emi.dds");

	P_Shoxwave_A = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\P_Shoxwave_emiA.dds");
	P_Shoxwave_B = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\P_Shoxwave_emiB.dds");
	P_Shoxwave_C = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\P_Shoxwave_emiC.dds");

	P_Explosion_0_dm = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\weapons\\P_Explosion_0_dif.dds");
	P_Explosion_0_nm = iTexture2DCreate("trzero_res\\textures\\normal_map\\weapons\\P_Explosion_0_nor.dds");
	P_Explosion_1_em = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\P_Explosion_1_emi.dds");

	U_Warp_0_dm = iTexture2DCreate("trzero_res\\textures\\diffuse_map\\weapons\\U_Warp_0_dif.dds");
	U_Warp_0_nm = iTexture2DCreate("trzero_res\\textures\\normal_map\\weapons\\U_Warp_0_nor.dds");
	U_Warp_1_em = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\U_Warp_1_emi.dds");

	U_DoubleD_em = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\U_DoubleD_emi.dds");

	U_AutoP_0_em = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\U_AutoP_0_emi.dds");
	U_AutoP_1_em = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\U_AutoP_1_emi.dds");

	Rail_Projectile = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\P_Rail_emi.dds");

	Particle_Explosion = iTexture2DCreate("trzero_res\\textures\\emissive_map\\particle\\explosion.dds");
	Particle_WeaponEmission = iTexture2DCreate("trzero_res\\textures\\emissive_map\\particle\\weaponemission.dds");
	ShieldInv_B = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\ShieldInv_B.dds");
	ShieldInv_C = iTexture2DCreate("trzero_res\\textures\\emissive_map\\weapons\\ShieldInv_C.dds");
	//-------------------------------------------------------------
	//apply samplers
	SamplerSet();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - WEAPONS - SAMPLER SET
///*****************************************************************
void Global_Texture_Bike_Weapons::SamplerSet(void)
{
	//-------------------------------------------------------------
	cGame_Texture2D_Sampler.ClampSet(Bike_Target_A);
	cGame_Texture2D_Sampler.WrapSet(NULL_Alpha);
	cGame_Texture2D_Sampler.WrapSet(Bike_Energy_B);
	cGame_Texture2D_Sampler.ClampSet(Bike_Energy_C);
	cGame_Texture2D_Sampler.WrapSet(Charge_B);
	cGame_Texture2D_Sampler.ClampSet(Charge_C);
	cGame_Texture2D_Sampler.WrapSet(P_EMBurst_emi);

	cGame_Texture2D_Sampler.WrapSet(P_Primary_em);

	cGame_Texture2D_Sampler.WrapSet(P_Missile_0_dm);
	cGame_Texture2D_Sampler.WrapSet(P_Missile_0_nm);
	cGame_Texture2D_Sampler.WrapSet(P_Missile_0_sm);
	cGame_Texture2D_Sampler.WrapSet(P_Missile_1_em);

	cGame_Texture2D_Sampler.WrapSet(P_Shoxwave_A);
	cGame_Texture2D_Sampler.WrapSet(P_Shoxwave_B);
	cGame_Texture2D_Sampler.WrapSet(P_Shoxwave_C);

	cGame_Texture2D_Sampler.WrapSet(P_Explosion_0_dm);
	cGame_Texture2D_Sampler.WrapSet(P_Explosion_0_nm);
	cGame_Texture2D_Sampler.ClampSet(P_Explosion_1_em);

	cGame_Texture2D_Sampler.WrapSet(U_Warp_0_dm);
	cGame_Texture2D_Sampler.WrapSet(U_Warp_0_nm);
	cGame_Texture2D_Sampler.ClampSet(U_Warp_1_em);

	cGame_Texture2D_Sampler.WrapSet(U_DoubleD_em);

	cGame_Texture2D_Sampler.WrapSet(U_AutoP_0_em);
	cGame_Texture2D_Sampler.ClampSet(U_AutoP_1_em);

	cGame_Texture2D_Sampler.WrapSet(Rail_Projectile);

	cGame_Texture2D_Sampler.ClampSet(Particle_Explosion);
	cGame_Texture2D_Sampler.ClampSet(Particle_WeaponEmission);
	
	cGame_Texture2D_Sampler.WrapSet(ShieldInv_B);
	cGame_Texture2D_Sampler.WrapSet(ShieldInv_C);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - TEXTURES - BIKE - WEAPONS - DESTROY
///*****************************************************************
void Global_Texture_Bike_Weapons::Destroy(void)
{
	//-------------------------------------------------------------
	iTexture2DDestroy(Bike_Target_A);
	iTexture2DDestroy(NULL_Alpha);
	iTexture2DDestroy(Bike_Energy_B);
	iTexture2DDestroy(Bike_Energy_C);
	iTexture2DDestroy(Charge_B);
	iTexture2DDestroy(Charge_C);
	iTexture2DDestroy(P_EMBurst_emi);

	iTexture2DDestroy(P_Primary_em);

	iTexture2DDestroy(P_Missile_0_dm);
	iTexture2DDestroy(P_Missile_0_nm);
	iTexture2DDestroy(P_Missile_0_sm);
	iTexture2DDestroy(P_Missile_1_em);

	iTexture2DDestroy(P_Shoxwave_A);
	iTexture2DDestroy(P_Shoxwave_B);
	iTexture2DDestroy(P_Shoxwave_C);

	iTexture2DDestroy(P_Explosion_0_dm);
	iTexture2DDestroy(P_Explosion_0_nm);
	iTexture2DDestroy(P_Explosion_1_em);

	iTexture2DDestroy(U_Warp_0_dm);
	iTexture2DDestroy(U_Warp_0_nm);
	iTexture2DDestroy(U_Warp_1_em);

	iTexture2DDestroy(U_DoubleD_em);

	iTexture2DDestroy(U_AutoP_0_em);
	iTexture2DDestroy(U_AutoP_1_em);

	iTexture2DDestroy(Rail_Projectile);

	iTexture2DDestroy(Particle_Explosion);
	iTexture2DDestroy(Particle_WeaponEmission);
	iTexture2DDestroy(ShieldInv_B);
	iTexture2DDestroy(ShieldInv_C);
	//-------------------------------------------------------------
}