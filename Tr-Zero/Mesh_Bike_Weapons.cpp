//-----------------------------------------------------------------
// About:
//
// name: "Mesh_Bike_Weapons.cpp:
//
// included in: "Game_Asset_Global_Mesh.h"
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
#include "Mesh_Bike_Weapons.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE WEAPONS - CONSTRUCTORS
///*****************************************************************
Mesh_Bike_Weapons::Mesh_Bike_Weapons(void)
{
	//-------------------------------------------------------------
	TOTAL_CREATE_ALL = 0;
	TOTAL_CREATE_PRIMARY_PROJECTILE = 0;
	///Double Damage Cube global offsets
	vDoubleD_L						= D3DXVECTOR3(-4.0f,2.5f,1.0f);
	vDoubleD_R						= D3DXVECTOR3(4.0f,2.5f,1.0f);
	//-------------------------------------------------------------
	Energy_A = NULL;
	Targeting = NULL;
	//-------------------------------------------------------------
	//Primary Weapon Projectile
	P_Primary_Glow = NULL;
	//---------------------------------------------------------
	//Secondary Weapons Charging
	Secondary_Charging = NULL;
	//---------------------------------------------------------
	//Secondary Weapons (MISSILE)
	for(int i=0;i<2;i++)
	{
		P_Missile_Projectile[i] = NULL;
		P_Missile_Explosion[i] = NULL;
	}
	for(int i=0;i<40;i++)
	{
		ExplosionTimer[i] = 0;
		bExplosionInUse[i] = false;
		ExplosionUpgradeScale[i] = 0.0f;
		vExplosionColour[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
	//---------------------------------------------------------
	//Secondary Weapons Projectile (SHOCKWAVE)
	P_Shockwave_Projectile = NULL;
	//---------------------------------------------------------
	//Secondary Weapons Projectile (AOE BURST)
	P_EMBurst_Projectile = NULL;
	//---------------------------------------------------------
	//Secondary Weapons Projectile (Rail)
	Rail_Projectile = NULL;
	//---------------------------------------------------------
	//Utility Weapons (SHIELD)
	Shield_Inv = NULL;
	//---------------------------------------------------------
	//Utility Weapons (WARP)
	for(int i=0;i<2;i++)
	{
		U_Warp[i] = NULL;
	}
	//---------------------------------------------------------
	//Utility Weapons (DOUBLE DAMAGE)
	for(int i=0;i<2;i++)
	{
		U_DoubleD[i] = NULL;
	}
	//---------------------------------------------------------
	//Utility Weapons (AUTO PILOT)
	for(int i=0;i<2;i++)
	{
		U_AutoP[i] = NULL;
	}
	//-------------------------------------------------------------
}
Mesh_Bike_Weapons::~Mesh_Bike_Weapons(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE WEAPONS - CREATE
///*****************************************************************
void Mesh_Bike_Weapons::Create(void)
{
	//-------------------------------------------------------------
	//Energy Regen
	Energy_A = iMeshCreate("trzero_res\\md5mesh\\bikes\\shadow\\energy_regen.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(Energy_A,false,false,false,false,true);
	iMeshPointLightEnableSet(Energy_A,false,false,0,false,1,false,2,false,3,true);
	iMeshLocationSet(Energy_A,&D3DXVECTOR3(0.0f,0.0f,0.0f),true);
	iMeshShaderEmissiveABMapBlendSet(Energy_A,true);
	iMeshAlphaToleranceSet(Energy_A,0.04f,true);
	//iMeshDepthBiasSet(Energy_A,-10);
	//iMeshCullModeSet(Energy_A,D3D11_CULL_NONE);
	iMeshGlowEnable(Energy_A,gGlowMeshEnable,false);
	iMeshScaleSet(Energy_A,&gBikeScale,false);
	//iMeshBlendModeSet(Energy_A,2,7,2);
	//iMeshBlendEnableSet(Energy_A,false);
	//-------------------------------------------------------------
	//Targeting
	Targeting = iMeshCreate("trzero_res\\md5mesh\\bikes\\shadow\\quad_C.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(Targeting,false,false,false,false,true);
	iMeshPointLightEnableSet(Targeting,false,false,0,false,1,false,2,false,3,true);
	iMeshLocationSet(Targeting,&D3DXVECTOR3(0.0f,0.0f,0.0f),true);
	iMeshShaderEmissiveSet(Targeting,true);
	iMeshAlphaToleranceSet(Targeting,0.2f,true);
	iMeshGlowEnable(Targeting,gGlowMeshEnable,false);
	iMeshScaleSet(Targeting,&gBikeScale,false);
	//iMeshBlendModeSet(Targeting,2,7,2);
	iMeshBlendEnableSet(Targeting,false);
	//-------------------------------------------------------------
	//Primary Weapon Projectile
	P_Primary_Glow = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\P_Primary.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(P_Primary_Glow,false,false,false,false,false);
	iMeshPointLightEnableSet(P_Primary_Glow,false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveSet(P_Primary_Glow,false);
	iMeshAlphaToleranceSet(P_Primary_Glow,0.025f,false);
	iMeshCullModeSet(P_Primary_Glow,D3D11_CULL_NONE);
	iMeshScaleSet(P_Primary_Glow,&D3DXVECTOR3(1.25f,1.25f,1.25f),false);
	//iMeshDepthBiasSet(P_Primary_Glow,-4);
	//iMeshFresnelEdgeSet(P_Primary_Glow,0.0f,1.0f,0.4f,false);
	iMeshBlendEnableSet(P_Primary_Glow,false);
	iMeshGlowEnable(P_Primary_Glow,gGlowMeshEnable,false);
	//-------------------------------------------------------------
	//Secondary Weapons Charging
	Secondary_Charging = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\charge.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(Secondary_Charging,false,false,false,false,true);
	iMeshPointLightEnableSet(Secondary_Charging,false,false,0,false,1,false,2,false,3,true);
	iMeshLocationSet(Secondary_Charging,&D3DXVECTOR3(0.0f,0.0f,0.0f),true);
	iMeshShaderEmissiveABMapBlendSet(Secondary_Charging,true);
	iMeshAlphaToleranceSet(Secondary_Charging,0.04f,true);
	iMeshCullModeSet(Secondary_Charging,D3D11_CULL_NONE);
	iMeshGlowEnable(Secondary_Charging,gGlowMeshEnable,false);
	iMeshScaleSet(Secondary_Charging,&gBikeScale,false);
	iMeshBlendEnableSet(Secondary_Charging,false);
	//iMeshBlendModeSet(Secondary_Charging,2,7,2);
	//---------------------------------------------------------
	//Secondary Weapons Projectile (MISSILE)
	for (int i=0;i<2;i++)
	{
		if(i==0)
		{
			P_Missile_Projectile[i] = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\P_Missile_0.md5mesh",gMeshSmoothing);
			iMeshDirectionalLightEnableSet(P_Missile_Projectile[i],true,false,false,false,false);
			iMeshPointLightEnableSet(P_Missile_Projectile[i],false,false,0,false,1,false,2,false,3,false);
			iMeshShaderNormalMapSet(P_Missile_Projectile[i],false);
			iMeshBumpScaleSet(P_Missile_Projectile[i],3.0f,false);
			iMeshFresnelEdgeSet(P_Missile_Projectile[i],0.0f,1.0f,0.4f,false);
		}
		else if(i==1)
		{
			P_Missile_Projectile[i] = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\P_Missile_1.md5mesh",gMeshSmoothing);
			iMeshDirectionalLightEnableSet(P_Missile_Projectile[i],false,false,false,false,false);
			iMeshPointLightEnableSet(P_Missile_Projectile[i],false,false,0,false,1,false,2,false,3,false);
			iMeshShaderEmissiveSet(P_Missile_Projectile[i],false);
			iMeshCullModeSet(P_Missile_Projectile[i],D3D11_CULL_NONE);
			iMeshAlphaToleranceSet(P_Missile_Projectile[i],0.025f,false);
			iMeshGlowEnable(P_Missile_Projectile[i],gGlowMeshEnable,false);
			iMeshBlendEnableSet(P_Missile_Projectile[i],false);
		}
		iMeshScaleSet(P_Missile_Projectile[i],&D3DXVECTOR3(4.0f,4.0f,4.0f),false);
	}
	//---------------------------------------------------------
	//Secondary Weapons Projectile (SHOCKWAVE)
	P_Shockwave_Projectile = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\P_Shoxwave.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(P_Shockwave_Projectile,false,false,false,false,false);
	iMeshPointLightEnableSet(P_Shockwave_Projectile,false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveABMapBlendSet(P_Shockwave_Projectile,false);
	iMeshAlphaToleranceSet(P_Shockwave_Projectile,0.025f,false);
	iMeshScaleSet(P_Shockwave_Projectile,&D3DXVECTOR3(2.5f,2.0f,2.0f),false);
	iMeshGlowEnable(P_Shockwave_Projectile,gGlowMeshEnable,false);
	iMeshCullModeSet(P_Shockwave_Projectile,D3D11_CULL_NONE);
	iMeshBlendEnableSet(P_Shockwave_Projectile,false);
	//iMeshBlendModeSet(P_Shockwave_Projectile,2,7,2);
	//---------------------------------------------------------
	//Secondary Weapons Projectile (EM BURST)
	P_EMBurst_Projectile = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\P_EMBurst.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(P_EMBurst_Projectile,false,false,false,false,false);
	iMeshPointLightEnableSet(P_EMBurst_Projectile,false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveSet(P_EMBurst_Projectile,false);
	iMeshAlphaToleranceSet(P_EMBurst_Projectile,0.2f,false);
	iMeshCullModeSet(P_EMBurst_Projectile,D3D11_CULL_NONE);
	iMeshScaleSet(P_EMBurst_Projectile,&D3DXVECTOR3(0.0f,0.0f,0.0f),false);
	iMeshGlowEnable(P_EMBurst_Projectile,gGlowMeshEnable,false);
	//iMeshBlendEnableSet(P_EMBurst_Projectile,false);
	iMeshBlendModeSet(P_EMBurst_Projectile,2,7,2);
	//---------------------------------------------------------
	//Secondary Weapons Projectile (RAIL)
	Rail_Projectile = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\P_Rail.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(Rail_Projectile,false,false,false,false,false);
	iMeshPointLightEnableSet(Rail_Projectile,false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveSet(Rail_Projectile,false);
	iMeshAlphaToleranceSet(Rail_Projectile,0.2f,false);
	iMeshCullModeSet(Rail_Projectile,D3D11_CULL_NONE);
	iMeshScaleSet(Rail_Projectile,&D3DXVECTOR3(2.0f,2.0f,8.0f),false);
	iMeshBlendEnableSet(Rail_Projectile,false);
	iMeshGlowEnable(Rail_Projectile,gGlowMeshEnable,false);
	//-------------------------------------------------------------
	//Utility Weapons - (SHIELD)
	Shield_Inv = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\U_Shield.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(Shield_Inv,false,false,false,false,false);
	iMeshPointLightEnableSet(Shield_Inv,false,false,0,false,1,false,2,false,3,false);
	iMeshShaderEmissiveABMapBlendSet(Shield_Inv,false);
	iMeshAlphaToleranceSet(Shield_Inv,0.08f,false);
	iMeshGlowEnable(Shield_Inv,gGlowMeshEnable,false);
	iMeshScaleSet(Shield_Inv,&gBikeScale,false);
	iMeshBlendModeSet(Shield_Inv,2,7,2);
	//---------------------------------------------------------
	//Utility Weapons (AUTO PILOT)
	for(int i=0;i<2;i++)
	{
		if(i==0)
		{
			U_AutoP[i] = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\U_AutoP_0.md5mesh",gMeshSmoothing);

		}
		else if(i==1)
		{
			U_AutoP[i] = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\U_AutoP_1.md5mesh",gMeshSmoothing);
		}
		iMeshDirectionalLightEnableSet(U_AutoP[i],false,false,false,false,false);
		iMeshPointLightEnableSet(U_AutoP[i],false,false,0,false,1,false,2,false,3,false);
		iMeshShaderEmissiveSet(U_AutoP[i],false);
		iMeshAlphaToleranceSet(U_AutoP[i],0.025f,false);
		iMeshScaleSet(U_AutoP[i],&D3DXVECTOR3(3.5f,3.5f,3.5f),false);
		iMeshGlowEnable(U_AutoP[i],gGlowMeshEnable,false);
		iMeshBlendEnableSet(U_AutoP[i],false);
		//iMeshBlendModeSet(U_AutoP[i],2,7,2);
		iMeshCullModeSet(U_AutoP[i],D3D11_CULL_NONE);
	}
	//---------------------------------------------------------
	//Utility Weapons (DOUBLE DAMAGE)
	for(int i=0;i<2;i++)
	{
		U_DoubleD[i] = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\U_DoubleD.md5mesh",gMeshSmoothing);
		iMeshDirectionalLightEnableSet(U_DoubleD[i],false,false,false,false,false);
		iMeshPointLightEnableSet(U_DoubleD[i],false,false,0,false,1,false,2,false,3,false);
		iMeshShaderEmissiveSet(U_DoubleD[i],false);
		iMeshAlphaToleranceSet(U_DoubleD[i],0.025f,false);
		iMeshScaleSet(U_DoubleD[i],&D3DXVECTOR3(2.0f,2.0f,2.0f),false);
		iMeshGlowEnable(U_DoubleD[i],gGlowMeshEnable,false);
		iMeshBlendEnableSet(U_DoubleD[i],false);
		iMeshCullModeSet(U_DoubleD[i],D3D11_CULL_NONE);
	}
	//---------------------------------------------------------
	//Secondary Weapons Projectile (MISSILE_EXPLOSION) P_Missile_Explosion
	for(int i=0;i<2;i++)
	{
		if(i==0)
		{
			P_Missile_Explosion[i] = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\P_Explosion_0.md5mesh",gMeshSmoothing);
			iMeshDirectionalLightEnableSet(P_Missile_Explosion[i],true,false,false,false,false);
			iMeshPointLightEnableSet(P_Missile_Explosion[i],false,false,0,false,1,false,2,false,3,false);
			iMeshShaderNormalMapSet(P_Missile_Explosion[i],false);
			iMeshAlphaToleranceSet(P_Missile_Explosion[i],0.025f,false);
			iMeshCullModeSet(P_Missile_Explosion[i],D3D11_CULL_FRONT);
			iMeshBumpScaleSet(P_Missile_Explosion[i],5.0f,false);
			iMeshFresnelEdgeSet(P_Missile_Explosion[i],0.0f,1.0f,0.8f,false);
		}
		else if(i==1)
		{
			P_Missile_Explosion[i] = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\P_Explosion_1.md5mesh",gMeshSmoothing);
			iMeshDirectionalLightEnableSet(P_Missile_Explosion[i],false,false,false,false,false);
			iMeshPointLightEnableSet(P_Missile_Explosion[i],false,false,0,false,1,false,2,false,3,false);
			iMeshShaderEmissiveSet(P_Missile_Explosion[i],false);
			iMeshCullModeSet(P_Missile_Explosion[i],D3D11_CULL_FRONT);///lol whoops
			iMeshAlphaToleranceSet(P_Missile_Explosion[i],0.025f,false);
			iMeshGlowEnable(P_Missile_Explosion[i],gGlowMeshEnable,false);
		}
		//iMeshScaleSet(P_Missile_Explosion[i],&D3DXVECTOR3(4.0f,4.0f,4.0f),false);
	}
	//-------------------------------------------------------------
	//Utility Weapons - (WARP)
	for(int i=0;i<2;i++)
	{
		if(i==0)
		{
			U_Warp[i] = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\U_Warp_0.md5mesh",gMeshSmoothing);
			iMeshDirectionalLightEnableSet(U_Warp[i],true,false,false,false,false);
			iMeshPointLightEnableSet(U_Warp[i],false,false,0,false,1,false,2,false,3,false);
			iMeshShaderNormalMapSet(U_Warp[i],false);
			iMeshCullModeSet(U_Warp[i],D3D11_CULL_FRONT);
			iMeshBumpScaleSet(U_Warp[i],5.0f,false);
			iMeshFresnelEdgeSet(U_Warp[i],0.0f,1.0f,0.8f,false);
		}
		else if(i==1)
		{
			U_Warp[i] = iMeshCreate("trzero_res\\md5mesh\\bikes\\weapons\\U_Warp_1.md5mesh",gMeshSmoothing);
			iMeshDirectionalLightEnableSet(U_Warp[i],false,false,false,false,false);
			iMeshPointLightEnableSet(U_Warp[i],false,false,0,false,1,false,2,false,3,false);
			iMeshShaderEmissiveSet(U_Warp[i],false);
			iMeshCullModeSet(U_Warp[i],D3D11_CULL_FRONT);///lol whoops
			iMeshAlphaToleranceSet(U_Warp[i],0.025f,false);
			iMeshGlowEnable(U_Warp[i],gGlowMeshEnable,false);
		}
		//iMeshScaleSet(U_Warp[i],&D3DXVECTOR3(4.0f,4.0f,4.0f),false);
	}
	//-------------------------------------------------------------
	//Create AI Imposters
	ImpostersCreate();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE WEAPONS - UPDATE
///*****************************************************************
void Mesh_Bike_Weapons::Update(void)
{
	//-------------------------------------------------------------
	//Shared vars (eg: double damage offsets)
	Update_Shared();
	//-------------------------------------------------------------
	//Update Player extras
	Player_Update(&cGame_Bike[gAi_Max_Count].Manager.vBikeOutput,&cGame_Bike[gAi_Max_Count].Manager.qBikeOutput);
	//All
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		Update_Common(i,&cGame_Bike[i].Manager.vBikeOutput,&cGame_Bike[i].Manager.qBikeOutput);
		Energy_Regen(i,cGame_Bike[i].Energy.bRegenFade,&cGame_Mesh.Animator.vBike[i],&cGame_Mesh.Animator.qBike[i],&cGame_Bike[i].Colour.vShieldColour);
		Secondary_Charge(i,cGame_Bike[i].Weapons.bSecondaryWeaponCharging,&cGame_Bike[i].Weapons.SecondaryWeaponChargeTime,&cGame_Bike[i].Weapons.SecondaryWeaponChargeTimeMax,&cGame_Mesh.Animator.vBike[i],&cGame_Mesh.Animator.qBike[i]);
		Secondary(i,&cGame_Bike[i].Weapons.SecondaryWeaponType,&cGame_Bike[i].Weapons.SecondaryProjectileAliveTime,&cGame_Bike[i].Weapons.SecondaryProjectileAliveTimeMax,&cGame_Bike[i].Weapons.vSecondaryProjectile,&cGame_Bike[i].Weapons.qSecondaryProjectile,&cGame_Bike[i].Colour.vBikeColourTarget);
		Utility(i,cGame_Mesh.Culling.bGlow[i],&cGame_Bike[i].Weapons.UtilityType,&cGame_Bike[i].Weapons.UtilityAliveTime,&cGame_Bike[i].Weapons.UtilityAliveTimeMax,&cGame_Mesh.Animator.vBike[i],&cGame_Mesh.Animator.qBike[i],&cGame_Bike[i].Colour.vBikeColourTarget);
		Missile_Explosion(i,&cGame_Bike[i].Manager.vTargetMesh);
	}
	//-------------------------------------------------------------
	//Shaders
	ShaderUpdate();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - Update_Shared
///*****************************************************************
void Mesh_Bike_Weapons::Update_Shared(void)
{
	//-------------------------------------------------------------
	if(gBikesGo ||
		gGameState==0)
	{
		//Double Damage Cube offsets
		vDoubleD_L = D3DXVECTOR3(-3.75f,2.75f + gMesh_UpDown,4.0f);
		vDoubleD_R = D3DXVECTOR3(3.75f,2.75f + gMesh_UpDown,4.0f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - Energy_Regen
///*****************************************************************
void Mesh_Bike_Weapons::Energy_Regen(int Index, bool bActive, D3DXVECTOR3* v1, D3DXQUATERNION* q1, D3DXVECTOR3* vColour)
{
	//-------------------------------------------------------------
	//Hide all imposters
	iMeshImposterHide(Energy_A,Index,false);
	//-------------------------------------------------------------
	//Regen
	if(bActive)
	{
		D3DXVECTOR3 vEnergy = iVectorLocationOffset(v1,q1,&D3DXVECTOR3(0.0f,-1.64f,0.0f));
		//Update
		iMeshImposterLocationSet(Energy_A,Index,&vEnergy,false);
		iMeshImposterOrientationSet(Energy_A,Index,q1,false);
		iMeshImposterColorSet(Energy_A,Index,vColour,false);
		//Show
		iMeshImposterShow(Energy_A,Index,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - Secondary_Charge
///*****************************************************************
void Mesh_Bike_Weapons::Secondary_Charge(int Index, bool bCharge, int* Time, int* TimeMax, D3DXVECTOR3* v1, D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	//Hide all imposters
	iMeshImposterHide(Secondary_Charging,Index,false);
	//-------------------------------------------------------------
	//Secondary Weapon - Charging
	if(bCharge)///eg: from culling system
	{
		float Colour = iFloatInterpolate((float)*Time,0.0f,(float)*TimeMax,0.0f,1.0f);
		iMeshImposterLocationSet(Secondary_Charging,Index,v1,true);
		iMeshImposterOrientationSet(Secondary_Charging,Index,q1,false);
		iMeshImposterColorSet(Secondary_Charging,Index,&D3DXVECTOR3(Colour,1.2f - Colour,1.0f - Colour),false);
		iMeshImposterShow(Secondary_Charging,Index,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - Secondary
///*****************************************************************
void Mesh_Bike_Weapons::Secondary(int Index, int* Weapon, int* Time, int* TimeMax, D3DXVECTOR3* v1, D3DXQUATERNION* q1, D3DXVECTOR3* vColour)
{
	//-------------------------------------------------------------
	//Hide all imposters
	iMeshImposterHide(P_Missile_Projectile[0],Index,false);
	iMeshImposterHide(P_Missile_Projectile[1],Index,false);
	iMeshImposterHide(P_Shockwave_Projectile,Index,false);
	iMeshImposterHide(P_EMBurst_Projectile,Index,false);
	iMeshImposterHide(Rail_Projectile,Index,false);
	//-------------------------------------------------------------
	//Secondary Weapons
	if(*Time>0)
	{
		//Secondary Weapons - Fusion Missile
		if(*Weapon==0)
		{
			///Location - colour
			float fMissileRotation = iFloatInterpolate((float)*Time,10.0f,(float)*TimeMax,0.0f,5600.0f);
			D3DXQUATERNION qSpin;
			iQuaternionFromEulerAngles(&qSpin,0.0f,0.0f,fMissileRotation);
			iQuaternionMultiply(&qSpin,&qSpin,q1);

			iMeshImposterLocationSet(P_Missile_Projectile[0],Index,v1,false);
			iMeshImposterOrientationSet(P_Missile_Projectile[0],Index,&qSpin,false);

			iMeshImposterLocationSet(P_Missile_Projectile[1],Index,v1,false);
			iMeshImposterOrientationSet(P_Missile_Projectile[1],Index,&qSpin,false);
			iMeshImposterColorSet(P_Missile_Projectile[1],Index,vColour,false);

			///Show
			iMeshImposterShow(P_Missile_Projectile[0],Index,false);
			iMeshImposterShow(P_Missile_Projectile[1],Index,false);
		}
		//Secondary Weapons - ShoxWave
		else if(*Weapon==1)
		{
			//Location - colour
			iMeshImposterLocationSet(P_Shockwave_Projectile,Index,v1,false);
			iMeshImposterOrientationSet(P_Shockwave_Projectile,Index,q1,false);
			iMeshImposterColorSet(P_Shockwave_Projectile,Index,vColour,false);
			D3DXVECTOR3 vScale = D3DXVECTOR3(0.0f,0.0f,0.0f);
			vScale.x = iScaleDurationAnimationFader(*Time,*TimeMax,2.5f);
			vScale.y = iScaleDurationAnimationFader(*Time,*TimeMax,2.0f);
			vScale.z = vScale.y;
			iMeshImposterScaleSet(P_Shockwave_Projectile,Index,&vScale,false);
			//Show
			iMeshImposterShow(P_Shockwave_Projectile,Index,false);
		}
		//Secondary Weapons - EM Burst
		else if(*Weapon==2)
		{
			//Location - colour
			iMeshImposterLocationSet(P_EMBurst_Projectile,Index,v1,false);
			iMeshImposterOrientationSet(P_EMBurst_Projectile,Index,q1,false);
			iMeshImposterColorSet(P_EMBurst_Projectile,Index,vColour,false);
			float fEmBurstScale = iFloatInterpolate((float)*Time,0.0f,(float)*TimeMax,0.0f,3.0f);
			iMeshImposterScaleSet(P_EMBurst_Projectile,Index,&D3DXVECTOR3(fEmBurstScale,0.75f,fEmBurstScale),false);
			//Show
			iMeshImposterShow(P_EMBurst_Projectile,Index,false);
		}
		//Secondary Weapons - Lancer Rail
		else if(*Weapon==3)
		{
			//Location - colour
			iMeshImposterLocationSet(Rail_Projectile,Index,v1,false);
			iMeshImposterOrientationSet(Rail_Projectile,Index,q1,false);
			iMeshImposterColorSet(Rail_Projectile,Index,vColour,false);
			//Show
			iMeshImposterShow(Rail_Projectile,Index,false);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - Utility
///*****************************************************************
void Mesh_Bike_Weapons::Utility(int Index, bool bShow, int* Weapon, int* Time, int* TimeMax, D3DXVECTOR3* v1, D3DXQUATERNION* q1, D3DXVECTOR3* vColour)
{
	//-------------------------------------------------------------
	//Hide all imposters
	iMeshImposterHide(Shield_Inv,Index,false);

	iMeshImposterHide(U_Warp[0],Index,false);
	iMeshImposterHide(U_Warp[1],Index,false);

	iMeshImposterHide(U_DoubleD[0],Index,false);
	iMeshImposterHide(U_DoubleD[1],Index,false);
	//-------------------------------------------------------------
	//Utility Weapons
	if(*Time>0 &&
		bShow)
	{ 
		//Utility Weapons - (SHIELD)
		if(*Weapon==0)
		{
			iMeshImposterColorSet(Shield_Inv,Index,vColour,false);
			iMeshImposterLocationSet(Shield_Inv,Index,v1,false);
			iMeshImposterOrientationSet(Shield_Inv,Index,q1,false);
			//Show
			iMeshImposterShow(Shield_Inv,Index,false);
		}
		//Utility Weapons - (DOUBLE DAMAGE)
		else if(*Weapon==2)
		{
			//Update
			D3DXVECTOR3 vOffsetL = iVectorLocationOffset(v1,q1,&vDoubleD_L);
			D3DXVECTOR3 vOffsetR = iVectorLocationOffset(v1,q1,&vDoubleD_R);

			iMeshImposterLocationSet(U_DoubleD[0],Index,&vOffsetL,false);
			iMeshImposterLocationSet(U_DoubleD[1],Index,&vOffsetR,false);

			iMeshImposterOrientationSet(U_DoubleD[0],Index,&g_qMesh_XY_Spin,false);
			iMeshImposterOrientationSet(U_DoubleD[1],Index,&g_qMesh_XY_Spin_Inverse,false);

			float fScale = iScaleDurationAnimationFader(*Time,*TimeMax,2.0f);
			iMeshImposterScaleSet(U_DoubleD[0],Index,&D3DXVECTOR3(fScale,fScale,fScale),false);
			iMeshImposterScaleSet(U_DoubleD[1],Index,&D3DXVECTOR3(fScale,fScale,fScale),false);

			iMeshImposterColorSet(U_DoubleD[0],Index,vColour,false);
			iMeshImposterColorSet(U_DoubleD[1],Index,vColour,false);
			//Show
			iMeshImposterShow(U_DoubleD[0],Index,false);
			iMeshImposterShow(U_DoubleD[1],Index,false);
		}
		//Utility Weapons - (WARP)
		else if(*Weapon==3)
		{
			float warpscaler = 0.0f;
			///stage one
			if(*Time<24)
			{
				warpscaler = iFloatInterpolateSmooth((float)*Time,0.0f,24.0f,1.0f,0.05f);
				iMeshImposterLocationSet(U_Warp[0],Index,v1,false);
				iMeshImposterLocationSet(U_Warp[1],Index,v1,false);
				iMeshImposterScaleSet(U_Warp[0],Index,&D3DXVECTOR3(warpscaler,warpscaler,warpscaler),false);
				iMeshImposterScaleSet(U_Warp[1],Index,&D3DXVECTOR3(warpscaler,warpscaler,warpscaler),false);
				iMeshImposterColorSet(U_Warp[1],Index,vColour,false);
			}
			///Stage two (setup new location)
			else if(*Time==25)
			{
				warpscaler = 0.01f;
				iMeshImposterLocationSet(U_Warp[0],Index,v1,false);
				iMeshImposterLocationSet(U_Warp[1],Index,v1,false);
				iMeshImposterScaleSet(U_Warp[0],Index,&D3DXVECTOR3(warpscaler,warpscaler,warpscaler),false);
				iMeshImposterScaleSet(U_Warp[1],Index,&D3DXVECTOR3(warpscaler,warpscaler,warpscaler),false);
			}
			///Stage three (finish new location)
			else if(*Time<=52)
			{
				warpscaler = iFloatInterpolateSmooth((float)*Time,26.0f,52.0f,0.05f,0.6f);
				iMeshImposterLocationSet(U_Warp[0],Index,v1,false);
				iMeshImposterLocationSet(U_Warp[1],Index,v1,false);
				iMeshImposterScaleSet(U_Warp[0],Index,&D3DXVECTOR3(warpscaler,warpscaler,warpscaler),false);
				iMeshImposterScaleSet(U_Warp[1],Index,&D3DXVECTOR3(warpscaler,warpscaler,warpscaler),false);
			}
			else
			{
				warpscaler = 0.01f;
				iMeshImposterScaleSet(U_Warp[0],Index,&D3DXVECTOR3(warpscaler,warpscaler,warpscaler),false);
				iMeshImposterScaleSet(U_Warp[1],Index,&D3DXVECTOR3(warpscaler,warpscaler,warpscaler),false);
			}

			iMeshImposterOrientationSet(U_Warp[1],Index,&cGame_Camera.qCamOutput,false);

			//Show
			iMeshImposterShow(U_Warp[0],Index,false);
			iMeshImposterShow(U_Warp[1],Index,false);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - Missile_Explosion
///*****************************************************************
void Mesh_Bike_Weapons::Missile_Explosion(int Index, D3DXVECTOR3* v1)
{
	//-------------------------------------------------------------
	//Hide all imposters
	///Not for this - relies on the imposter being shown to fade
	//-------------------------------------------------------------
	//Secondary Weapons - Fusion Missle (EXPLOSION)
	if(bExplosionInUse[Index])
	{
		float explosionscaler = iFloatInterpolateSmooth((float)ExplosionTimer[Index],0.0f,14.0f,1.0f,ExplosionUpgradeScale[Index] / 5.0f);

		iMeshImposterLocationSet(P_Missile_Explosion[0],Index,v1,false);
		iMeshImposterLocationSet(P_Missile_Explosion[1],Index,v1,false);

		iMeshImposterOrientationSet(P_Missile_Explosion[1],Index,&cGame_Camera.qCamOutput,false);

		iMeshImposterScaleSet(P_Missile_Explosion[0],Index,&D3DXVECTOR3(explosionscaler,explosionscaler,explosionscaler),false);
		iMeshImposterScaleSet(P_Missile_Explosion[1],Index,&D3DXVECTOR3(explosionscaler,explosionscaler,explosionscaler),false);

		iMeshImposterColorSet(P_Missile_Explosion[0],Index,&vExplosionColour[Index],false);
		iMeshImposterColorSet(P_Missile_Explosion[1],Index,&vExplosionColour[Index],false);

		//Show
		iMeshImposterShow(P_Missile_Explosion[0],Index,false);
		iMeshImposterShow(P_Missile_Explosion[1],Index,false);

		if(gBikesGo)
		{
			ExplosionTimer[Index]++;
		}
		/// Reset - start fading stage
		if(ExplosionTimer[Index]>15)
		{
			ExplosionTimer[Index] = 0;
			bExplosionInUse[Index] = false;
		}
	}
	else if(iMeshImposterIsShown(P_Missile_Explosion[0],Index) || 
		iMeshImposterIsShown(P_Missile_Explosion[1],Index))
	{
		if(gBikesGo)///Fade colour
		{
			iVector3TendTo(&vExplosionColour[Index],&D3DXVECTOR3(0.0f,0.0f,0.0f),4.0f);
			iMeshImposterColorSet(P_Missile_Explosion[0],Index,&vExplosionColour[Index],false);
			iMeshImposterColorSet(P_Missile_Explosion[1],Index,&vExplosionColour[Index],false);
		}

		if(vExplosionColour[Index].x < 0.02f &&
			vExplosionColour[Index].y < 0.02f &&
			vExplosionColour[Index].z < 0.02f)
		{
			iMeshImposterHide(P_Missile_Explosion[0],Index,false);
			iMeshImposterHide(P_Missile_Explosion[1],Index,false);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - PLAYER UPDATE
///*****************************************************************
void Mesh_Bike_Weapons::Player_Update(D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	//Offsets
	D3DXVECTOR3 vTargeting = iVectorLocationOffset(v1,q1,&D3DXVECTOR3(0.0f,-1.66f,0.0f));
	//D3DXVECTOR3 vShadow = iVectorLocationOffset(&v1,&q1,&D3DXVECTOR3(0.0f,-1.65f,0.0f));
	//-------------------------------------------------------------
	//Hide master mesh (used in upgrade menu)
	iMeshHide(U_AutoP[0],false);
	iMeshHide(U_AutoP[1],false);
	//-------------------------------------------------------------
	//Utility Weapons (AUTO PILOT)
	if(cGame_Bike[gAi_Max_Count].Weapons.bUtilityProjectileSetup && 
		cGame_Bike[gAi_Max_Count].Weapons.UtilityType==1)
	{
		///vector
		D3DXVECTOR3 vOffset_AP = iVectorLocationOffset(&cGame_Bike[gAi_Max_Count].Manager.vTargetMesh,&cGame_Bike[gAi_Max_Count].Manager.qBikeOutput,&vDoubleD_L);
		///lookat
		//D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
		//iVectorRotate(&vUp,&vUp,&cGame_Bike[gAi_Max_Count].Manager.qBikeOutputLean);

		D3DXQUATERNION qRotate;
		iQuaternionFromEulerAngles(&qRotate,0.0f,-40.0f,0.0f);
		iQuaternionMultiply(&qRotate,&qRotate,&cGame_Bike[gAi_Max_Count].Manager.qBikeOutput);
		//D3DXQUATERNION qLookAt_L;
		//iQuaternionLookAt(&qLookAt_L,&vOffset_AP,&cGame_Bike[gAi_Max_Count].Weapons.vCrosshairOrigin,&vUp);
		///spin
		D3DXQUATERNION qSpin;
		iQuaternionFromEulerAngles(&qSpin,0.0f,0.0f,gTextureRot_Slow);
		iQuaternionMultiply(&qSpin,&qSpin,&qRotate);

		float fScale = iScaleDurationAnimationFader(cGame_Bike[gAi_Max_Count].Weapons.UtilityAliveTime,cGame_Bike[gAi_Max_Count].Weapons.UtilityAliveTimeMax,1.5f);
		for(int i=0;i<2;i++)
		{
			//Update
			iMeshColorSet(U_AutoP[i],&cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget,false);
			iMeshLocationSet(U_AutoP[i],&vOffset_AP,false);
			iMeshOrientationSet(U_AutoP[i],&qSpin,false);
			iMeshScaleSet(U_AutoP[i],&D3DXVECTOR3(fScale,fScale,fScale),false);
			//Show
			iMeshShow(U_AutoP[i],false);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - Update_Common
///*****************************************************************
void Mesh_Bike_Weapons::Update_Common(int Index,D3DXVECTOR3* v1,D3DXQUATERNION* q1)
{
	//-------------------------------------------------------------
	//Offsets
	D3DXVECTOR3 vTargeting = iVectorLocationOffset(v1,q1,&D3DXVECTOR3(0.0f,-1.66f,0.0f));
	//D3DXVECTOR3 vShadow = iVectorLocationOffset(&v1,&q1,&D3DXVECTOR3(0.0f,-1.65f,0.0f));
	//-------------------------------------------------------------
	//Targeting
	iMeshImposterHide(Targeting,Index,false);

	if(cGame_Bike[Index].Weapons.bBeingTracked)
	{
		iMeshImposterLocationSet(Targeting,Index,&vTargeting,false);
		iMeshImposterOrientationSet(Targeting,Index,q1,false);
		iMeshImposterColorSet(Targeting,Index,&cGame_Bike[Index].Weapons.vTrackingMeshColour,false);
		//Show
		iMeshImposterShow(Targeting,Index,false);
	}
	///Reset Targeting for next loop - Really dont like this here, but, 
	///only way to ensure mesh is updated after weapons math update, and, before flags are reset.
	if(gBikesGo)
	{
		cGame_Bike[Index].Weapons.bBeingTracked = false;
		cGame_Bike[Index].Weapons.vTrackingMeshColour = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
	//-------------------------------------------------------------
	//Primary Weapon Update
	const int ImposterTarget = Index * 10;
	for(int i=0;i<MAX_PRIMARY_PROJECTILES_PER_BIKE;i++)
	{
		//Hide
		iMeshImposterHide(P_Primary_Glow,ImposterTarget + i,false);
		//Update
		if(cGame_Bike[Index].Weapons.PrimaryProjectileAliveTime[i]>0)
		{
			iMeshImposterLocationSet(P_Primary_Glow,ImposterTarget + i,&cGame_Bike[Index].Weapons.vPrimaryProjectile[i],false);
			iMeshImposterOrientationSet(P_Primary_Glow,ImposterTarget + i,&cGame_Bike[Index].Weapons.qPrimaryProjectile[i],false);
			iMeshImposterColorSet(P_Primary_Glow,ImposterTarget + i,&cGame_Bike[Index].Colour.vBikeColourTarget,false);
			//Show
			iMeshImposterShow(P_Primary_Glow,ImposterTarget + i,false);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - SHADER UPDATE
///*****************************************************************
void Mesh_Bike_Weapons::ShaderUpdate(void)
{
	//-------------------------------------------------------------
	//Global Moving Textures
	Update_TexturePan();
	//-------------------------------------------------------------
	//Energy
	iMeshShaderEmissiveABMapBlendTextureUpdate(Energy_A,
									 cGame_Asset_Global_Texture.Bike_Weapons.NULL_Alpha,
								     &D3DXVECTOR2(1.0f,1.0f),
									 cGame_Asset_Global_Texture.Bike_Weapons.Bike_Energy_B,
								     &D3DXVECTOR2(1.0f,1.0f),
									 cGame_Asset_Global_Texture.Bike_Weapons.Bike_Energy_C,
								     false);
	//-------------------------------------------------------------
	//Targeting
	iMeshShaderEmissiveTextureUpdate(Targeting,
									 cGame_Asset_Global_Texture.Bike_Weapons.Bike_Target_A,
								     &D3DXVECTOR2(1.0f,1.0f),
								     false);
	//-------------------------------------------------------------
	//Primary Weapon Projectile
	iMeshShaderEmissiveTextureUpdate(P_Primary_Glow,
									cGame_Asset_Global_Texture.Bike_Weapons.P_Primary_em,
									 &D3DXVECTOR2(1.0f,1.0f),
									 false);
	//-------------------------------------------------------------
	//Secondary Weapons Charging
	iMeshShaderEmissiveABMapBlendTextureUpdate(Secondary_Charging,
									 cGame_Asset_Global_Texture.Bike_Weapons.NULL_Alpha,
								     &D3DXVECTOR2(1.0f,1.0f),
									 cGame_Asset_Global_Texture.Bike_Weapons.Charge_B,
								     &D3DXVECTOR2(1.0f,1.0f),
									 cGame_Asset_Global_Texture.Bike_Weapons.Charge_C,
								     false);
	//-------------------------------------------------------------
	//Secondary Weapons Projectile (MISSILE)
	iMeshShaderNormalMapTextureUpdate(P_Missile_Projectile[0],
									cGame_Asset_Global_Texture.Bike_Weapons.P_Missile_0_dm,
									cGame_Asset_Global_Texture.Bike_Weapons.P_Missile_0_nm,
									cGame_Asset_Global_Texture.Bike_Weapons.P_Missile_0_sm,
									&D3DXVECTOR2(1.0f,1.0f),
									false);
	iMeshShaderEmissiveTextureUpdate(P_Missile_Projectile[1],
									cGame_Asset_Global_Texture.Bike_Weapons.P_Missile_1_em,
									 &D3DXVECTOR2(1.0f,1.0f),
									 false);
	//-------------------------------------------------------------
	//Secondary Weapons Projectile (MISSILE_EXPLOSION) P_Missile_Explosion
	iMeshShaderNormalMapTextureUpdate(P_Missile_Explosion[0],
									cGame_Asset_Global_Texture.Bike_Weapons.P_Explosion_0_dm,
									cGame_Asset_Global_Texture.Bike_Weapons.P_Explosion_0_nm,
									NULL,
									&D3DXVECTOR2(2.0f,2.0f),
									false);
	iMeshShaderEmissiveTextureUpdate(P_Missile_Explosion[1],
									cGame_Asset_Global_Texture.Bike_Weapons.P_Explosion_1_em,
									 &D3DXVECTOR2(1.0f,1.0f),
									 false);
	//-------------------------------------------------------------
	//Secondary Weapons Projectile (SHOCKWAVE)
	iMeshShaderEmissiveABMapBlendTextureUpdate(P_Shockwave_Projectile,
										cGame_Asset_Global_Texture.Bike_Weapons.P_Shoxwave_A,
										&D3DXVECTOR2(1.0f,1.0f),
										cGame_Asset_Global_Texture.Bike_Weapons.P_Shoxwave_B,
										&D3DXVECTOR2(1.0f,1.0f),
										cGame_Asset_Global_Texture.Bike_Weapons.P_Shoxwave_C,
								     false);
	//-------------------------------------------------------------
	//Secondary Weapons Projectile (AOE BURST)
	iMeshShaderEmissiveTextureUpdate(P_EMBurst_Projectile,
									cGame_Asset_Global_Texture.Bike_Weapons.P_EMBurst_emi,
									 &D3DXVECTOR2(1.0f,1.0f),
									 false);
	//-------------------------------------------------------------
	//Secondary Weapons Projectile (RAIL)
	iMeshShaderEmissiveTextureUpdate(Rail_Projectile,
									cGame_Asset_Global_Texture.Bike_Weapons.Rail_Projectile,
									 &D3DXVECTOR2(1.0f,1.0f),
									 false);
	//-------------------------------------------------------------
	//Utility Weapons (SHIELD)
	iMeshShaderEmissiveABMapBlendTextureUpdate(Shield_Inv,
									 cGame_Asset_Global_Texture.Bike_Weapons.NULL_Alpha,
								     &D3DXVECTOR2(1.0f,1.0f),
									 cGame_Asset_Global_Texture.Bike_Weapons.ShieldInv_B,
								     &D3DXVECTOR2(1.0f,1.0f),
									 cGame_Asset_Global_Texture.Bike_Weapons.ShieldInv_C,
								     false);
	//-------------------------------------------------------------
	//Utility Weapons (WARP)
	iMeshShaderNormalMapTextureUpdate(U_Warp[0],
									cGame_Asset_Global_Texture.Bike_Weapons.U_Warp_0_dm,
									cGame_Asset_Global_Texture.Bike_Weapons.U_Warp_0_nm,
									NULL,
									&D3DXVECTOR2(2.0f,2.0f),
									false);
	iMeshShaderEmissiveTextureUpdate(U_Warp[1],
									cGame_Asset_Global_Texture.Bike_Weapons.U_Warp_1_em,
									 &D3DXVECTOR2(1.0f,1.0f),
									 false);
	//---------------------------------------------------------
	//Utility Weapons (DOUBLE DAMAGE)
	for(int i=0;i<2;i++)
	{
		iMeshShaderEmissiveTextureUpdate(U_DoubleD[i],
										cGame_Asset_Global_Texture.Bike_Weapons.U_DoubleD_em,
										 &D3DXVECTOR2(1.0f,1.0f),
										 false);
	}
	//---------------------------------------------------------
	//Utility Weapons (AUTO PILOT)
	iMeshShaderEmissiveTextureUpdate(U_AutoP[0],
										cGame_Asset_Global_Texture.Bike_Weapons.U_AutoP_0_em,
										&D3DXVECTOR2(1.0f,1.0f),
										false);
	iMeshShaderEmissiveTextureUpdate(U_AutoP[1],
										cGame_Asset_Global_Texture.Bike_Weapons.U_AutoP_1_em,
										&D3DXVECTOR2(1.0f,1.0f),
										false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - IMPOSTERS CREATE
///*****************************************************************
void Mesh_Bike_Weapons::ImpostersCreate(void)
{
	//-------------------------------------------------------------
	TOTAL_CREATE_ALL = gAi_Max_Count + 1;
	//-------------------------------------------------------------
	//Create
	iMeshImpostersCreate(Targeting,TOTAL_CREATE_ALL);
	
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		//frustum culling
		iMeshImposterAABBAutoFrustumCullingEnable(Targeting,i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
	//Energy Regen
	iMeshImpostersCreate(Energy_A,TOTAL_CREATE_ALL);
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(Energy_A,i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
	//Primary Projectile Imposters
	TOTAL_CREATE_PRIMARY_PROJECTILE = ((gAi_Max_Count + 1) * 10) + 10;
	iMeshImpostersCreate(P_Primary_Glow,TOTAL_CREATE_PRIMARY_PROJECTILE);
	for(int i=0;i<TOTAL_CREATE_PRIMARY_PROJECTILE;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(P_Primary_Glow,i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
	//Secondary Weapons (CHARGING)
	iMeshImpostersCreate(Secondary_Charging,TOTAL_CREATE_ALL);
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(Secondary_Charging,i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
	//Secondary Weapons Projectile Imposters (MISSILE)
	iMeshImpostersCreate(P_Missile_Projectile[0],TOTAL_CREATE_ALL);
	iMeshImpostersCreate(P_Missile_Projectile[1],TOTAL_CREATE_ALL);
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(P_Missile_Projectile[0],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(P_Missile_Projectile[1],i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
	//Secondary Weapons Projectile Imposters (MISSILE EXPLOSION)
	iMeshImpostersCreate(P_Missile_Explosion[0],TOTAL_CREATE_ALL);
	iMeshImpostersCreate(P_Missile_Explosion[1],TOTAL_CREATE_ALL);
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(P_Missile_Explosion[0],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(P_Missile_Explosion[1],i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
	//Secondary Weapons Projectile Imposters (SHOCKWAVE)
	iMeshImpostersCreate(P_Shockwave_Projectile,TOTAL_CREATE_ALL);
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(P_Shockwave_Projectile,i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
	//Secondary Weapons Projectile Imposters (AOE BURST)
	iMeshImpostersCreate(P_EMBurst_Projectile,TOTAL_CREATE_ALL);
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(P_EMBurst_Projectile,i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
	//Secondary Weapons Projectile Imposters (RAIL)
	iMeshImpostersCreate(Rail_Projectile,TOTAL_CREATE_ALL);
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(Rail_Projectile,i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
	//Utility Weapon (SHIELD)
	iMeshImpostersCreate(Shield_Inv,TOTAL_CREATE_ALL);
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(Shield_Inv,i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
	//Utility Weapon (WARP)
	iMeshImpostersCreate(U_Warp[0],TOTAL_CREATE_ALL);
	iMeshImpostersCreate(U_Warp[1],TOTAL_CREATE_ALL);
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(U_Warp[0],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(U_Warp[1],i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//---------------------------------------------------------
	//Utility Weapons (DOUBLE DAMAGE)
	iMeshImpostersCreate(U_DoubleD[0],TOTAL_CREATE_ALL);
	iMeshImpostersCreate(U_DoubleD[1],TOTAL_CREATE_ALL);
	for(int i=0;i<TOTAL_CREATE_ALL;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(U_DoubleD[0],i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterAABBAutoFrustumCullingEnable(U_DoubleD[1],i,true,gFrustCullScale,gFrustCullRadius,false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - IMPOSTERS DESTROY
///*****************************************************************
void Mesh_Bike_Weapons::ImpostersDestroy(void)
{
	//-------------------------------------------------------------
	iMeshImpostersDestroy(Energy_A);
	iMeshImpostersDestroy(Targeting);
	
	iMeshImpostersDestroy(P_Primary_Glow);
	iMeshImpostersDestroy(Secondary_Charging);

	for(int i=0;i<2;i++)
	{
		iMeshImpostersDestroy(P_Missile_Projectile[i]);
		iMeshImpostersDestroy(P_Missile_Explosion[i]);
		iMeshImpostersDestroy(U_Warp[i]);
		iMeshImpostersDestroy(U_DoubleD[i]);
	}

	iMeshImpostersDestroy(P_Shockwave_Projectile);
	iMeshImpostersDestroy(P_EMBurst_Projectile);
	iMeshImpostersDestroy(Rail_Projectile);
	iMeshImpostersDestroy(Shield_Inv);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - BIKE WEAPONS - DESTROY
///*****************************************************************
void Mesh_Bike_Weapons::Destroy(void)
{
	//-------------------------------------------------------------
	ImpostersDestroy();
	//-------------------------------------------------------------
	iMeshDestroy(Energy_A);
	iMeshDestroy(Targeting);
	
	iMeshDestroy(P_Primary_Glow);
	iMeshDestroy(Secondary_Charging);

	for(int i=0;i<2;i++)
	{
		iMeshDestroy(P_Missile_Projectile[i]);
		iMeshDestroy(P_Missile_Explosion[i]);
		iMeshDestroy(U_Warp[i]);
		iMeshDestroy(U_DoubleD[i]);
		iMeshDestroy(U_AutoP[i]);
	}

	for(int i=0;i<40;i++)
	{
		ExplosionTimer[i] = 0;
		bExplosionInUse[i] = false;
		ExplosionUpgradeScale[i] = 0.0f;
		vExplosionColour[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}

	iMeshDestroy(P_Shockwave_Projectile);
	iMeshDestroy(P_EMBurst_Projectile);
	iMeshDestroy(Rail_Projectile);
	iMeshDestroy(Shield_Inv);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - BIKE WEAPONS - UPDATE TEXTURE PAN
///*****************************************************************
void Mesh_Bike_Weapons::Update_TexturePan(void)
{
	//-------------------------------------------------------------
	//Apply to master mesh
	if(gBikesGo || 
		cGame_Track.bShowroom)
	{
		iMeshTexturePanSet(Energy_A,&D3DXVECTOR2(0.0f,0.0f),&D3DXVECTOR2(gTexturePan_Med,0.0f),false);
		iMeshTextureRotationSet(Targeting,gTextureRot_Med,false);
		iMeshTexturePanSet(Secondary_Charging,&D3DXVECTOR2(0.0f,0.0f),&D3DXVECTOR2(gTexturePan_Med,0.0f),false);


		iMeshTexturePanSet(P_Missile_Projectile[1],&D3DXVECTOR2(0.0f,gTexturePan_Slow),&D3DXVECTOR2(0.0f,0.0f),false);
		iMeshTextureRotationSet(P_Missile_Explosion[1],gTextureRot_Med,false);

		iMeshTexturePanSet(P_Shockwave_Projectile,&D3DXVECTOR2(0.0f,0.0f),&D3DXVECTOR2(gTexturePan_Vibrate,-gTexturePan_Med),false);

		iMeshTexturePanSet(P_EMBurst_Projectile,&D3DXVECTOR2(0.0f,gTexturePan_Med),&D3DXVECTOR2(0.0f,0.0f),false);

		iMeshTexturePanSet(Shield_Inv,&D3DXVECTOR2(0.0f,0.0f),&D3DXVECTOR2(-gTexturePan_Med,0.0f),false);
		iMeshTextureRotationSet(U_Warp[1],gTextureRot_Med,false);

		iMeshTextureRotationSet(U_AutoP[1],gTextureRot_Fast,false);
	}
	//-------------------------------------------------------------
}