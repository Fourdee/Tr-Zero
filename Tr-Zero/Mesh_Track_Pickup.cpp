//-----------------------------------------------------------------
// About:
//
// name: "Mesh_Track_Pickup.cpp:
//
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Mesh_Track_Pickup.h"
//-----------------------------------------------------------------
///*****************************************************************
//GLOBAL - MESH - TRACK - PICKUP - CONSTRUCTORS
///*****************************************************************
Mesh_Track_Pickup::Mesh_Track_Pickup(void)
{
	//-------------------------------------------------------------
	Pickup_Weapon = NULL;
	Pickup_Energy = NULL;
	Pickup_Utility = NULL;
	//-------------------------------------------------------------
}

Mesh_Track_Pickup::~Mesh_Track_Pickup(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GLOBAL - MESH - TRACK - PICKUP - CREATE
///*****************************************************************
void Mesh_Track_Pickup::Create(void)
{
	//-------------------------------------------------------------
	//Pickup Weapon
	Pickup_Weapon = iMeshCreate("trzero_res\\md5mesh\\pickup\\weapon_pickup.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(Pickup_Weapon,false,false,false,false,true);
	iMeshPointLightEnableSet(Pickup_Weapon,false,false,0,false,1,false,2,false,3,true);
	iMeshLocationSet(Pickup_Weapon,&D3DXVECTOR3(0.0f,-5000.0f,0.0f),true);
	iMeshShaderEmissiveSet(Pickup_Weapon,true);
	iMeshAlphaToleranceSet(Pickup_Weapon,0.1f,true);
	//iMeshScaleSet(Pickup_Weapon,&D3DXVECTOR3(6.0f,6.0f,6.0f),true);
	iMeshColorSet(Pickup_Weapon,&D3DXVECTOR3(1.7f,0.5f,0.0f),true);
	iMeshGlowEnable(Pickup_Weapon,gGlowMeshEnable,false);
//iMeshBlendModeSet(Pickup_Weapon,2,7,1);
iMeshBlendEnableSet(Pickup_Weapon,false);

	//-------------------------------------------------------------
	//Pickup Energy
	Pickup_Energy = iMeshCreate("trzero_res\\md5mesh\\pickup\\energy_pickup.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(Pickup_Energy,false,false,false,false,true);
	iMeshPointLightEnableSet(Pickup_Energy,false,false,0,false,1,false,2,false,3,true);
	iMeshLocationSet(Pickup_Energy,&D3DXVECTOR3(0.0f,-5000.0f,0.0f),true);
	iMeshShaderEmissiveSet(Pickup_Energy,true);
	iMeshAlphaToleranceSet(Pickup_Energy,0.1f,true);
	//iMeshScaleSet(Pickup_Energy,&D3DXVECTOR3(6.0f,6.0f,6.0f),true);
	iMeshColorSet(Pickup_Energy,&D3DXVECTOR3(0.25f,0.8f,2.0f),true);
	iMeshGlowEnable(Pickup_Energy,gGlowMeshEnable,false);
//iMeshBlendModeSet(Pickup_Energy,2,7,1);
iMeshBlendEnableSet(Pickup_Energy,false);

	//-------------------------------------------------------------
	//Pickup Utility
	Pickup_Utility = iMeshCreate("trzero_res\\md5mesh\\pickup\\utility_pickup.md5mesh",gMeshSmoothing);
	iMeshDirectionalLightEnableSet(Pickup_Utility,false,false,false,false,true);
	iMeshPointLightEnableSet(Pickup_Utility,false,false,0,false,1,false,2,false,3,true);
	iMeshLocationSet(Pickup_Utility,&D3DXVECTOR3(0.0f,-5000.0f,0.0f),true);
	iMeshShaderEmissiveSet(Pickup_Utility,true);
	iMeshAlphaToleranceSet(Pickup_Utility,0.1f,true);
	//iMeshScaleSet(Pickup_Energy,&D3DXVECTOR3(6.0f,6.0f,6.0f),true);
	iMeshColorSet(Pickup_Utility,&D3DXVECTOR3(0.5f,1.7f,0.0f),true);
	iMeshGlowEnable(Pickup_Utility,gGlowMeshEnable,false);
//iMeshBlendModeSet(Pickup_Utility,2,7,1);
iMeshBlendEnableSet(Pickup_Utility,false);

	//-------------------------------------------------------------
	ImpostersCreate_Weapon();
	ImpostersCreate_Energy();
	ImpostersCreate_Utility();
	//-------------------------------------------------------------
}
///*****************************************************************
//GLOBAL - MESH - TRACK - PICKUP - IMPOSTERS CREATE WEAPON
///*****************************************************************
void Mesh_Track_Pickup::ImpostersCreate_Weapon(void)
{
	//-------------------------------------------------------------
	//Imposters
	iMeshImpostersCreate(Pickup_Weapon,MAX_WEAPON_PICKUPS);
	for(int i=0;i<MAX_WEAPON_PICKUPS;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(Pickup_Weapon,i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterLocationSet(Pickup_Weapon,i,&D3DXVECTOR3(0.0f,-5000.0f,0.0f),true);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GLOBAL - MESH - TRACK - PICKUP - IMPOSTERS CREATE ENERGY
///*****************************************************************
void Mesh_Track_Pickup::ImpostersCreate_Energy(void)
{
	//-------------------------------------------------------------
	//Imposters
	iMeshImpostersCreate(Pickup_Energy,MAX_ENERGY_PICKUPS);
	for(int i=0;i<MAX_ENERGY_PICKUPS;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(Pickup_Energy,i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterLocationSet(Pickup_Energy,i,&D3DXVECTOR3(0.0f,-5000.0f,0.0f),true);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GLOBAL - MESH - TRACK - PICKUP - IMPOSTERS CREATE UTILITY
///*****************************************************************
void Mesh_Track_Pickup::ImpostersCreate_Utility(void)
{
	//-------------------------------------------------------------
	//Imposters
	iMeshImpostersCreate(Pickup_Utility,MAX_UTILITY_PICKUPS);
	for(int i=0;i<MAX_UTILITY_PICKUPS;i++)
	{
		iMeshImposterAABBAutoFrustumCullingEnable(Pickup_Utility,i,true,gFrustCullScale,gFrustCullRadius,false);
		iMeshImposterLocationSet(Pickup_Utility,i,&D3DXVECTOR3(0.0f,-5000.0f,0.0f),true);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GLOBAL - MESH - TRACK - PICKUP - IMPOSTERS DESTROY WEAPON
///*****************************************************************
void Mesh_Track_Pickup::ImpostersDestroy_Weapon(void)
{
	//-------------------------------------------------------------
	iMeshImpostersDestroy(Pickup_Weapon);
	//-------------------------------------------------------------
}
///*****************************************************************
//GLOBAL - MESH - TRACK - PICKUP - IMPOSTERS DESTROY ENERGY
///*****************************************************************
void Mesh_Track_Pickup::ImpostersDestroy_Energy(void)
{
	//-------------------------------------------------------------
	iMeshImpostersDestroy(Pickup_Energy);
	//-------------------------------------------------------------
}
///*****************************************************************
//GLOBAL - MESH - TRACK - PICKUP - IMPOSTERS DESTROY UTILITY
///*****************************************************************
void Mesh_Track_Pickup::ImpostersDestroy_Utility(void)
{
	//-------------------------------------------------------------
	iMeshImpostersDestroy(Pickup_Utility);
	//-------------------------------------------------------------
}
///*****************************************************************
//GLOBAL - MESH - TRACK - PICKUP - UPDATE
///*****************************************************************
void Mesh_Track_Pickup::Update(void)
{
	//-------------------------------------------------------------
	ShaderUpdate();
	//-------------------------------------------------------------
}
///*****************************************************************
///GLOBAL - MESH - TRACK - PICKUP - SHADERUPDATE
///*****************************************************************
void Mesh_Track_Pickup::ShaderUpdate(void)
{
	//-------------------------------------------------------------
	//Update Texture Pan
	Update_TexturePan();
	//Update Mesh Spin
	Update_MeshSpin();
	//-------------------------------------------------------------
	//Pickup_Weapon
	iMeshShaderEmissiveTextureUpdate(Pickup_Weapon,
									 cGame_Asset_Global_Texture.Track_Pickup.Pickup_Energy,
									 &D3DXVECTOR2(1.0f,1.0f),
									 true);
	//-------------------------------------------------------------
	//Pickup_Energy
	iMeshShaderEmissiveTextureUpdate(Pickup_Energy,
									 cGame_Asset_Global_Texture.Track_Pickup.Pickup_Energy,
									 &D3DXVECTOR2(1.0f,1.0f),
									 true);
	//-------------------------------------------------------------
	//Pickup_Utility
	iMeshShaderEmissiveTextureUpdate(Pickup_Utility,
									 cGame_Asset_Global_Texture.Track_Pickup.Pickup_Energy,
									 &D3DXVECTOR2(1.0f,1.0f),
									 true);
	//-------------------------------------------------------------
}
///*****************************************************************
///GLOBAL - MESH - TRACK - PICKUP - UPDATE TEXTURE PAN
///*****************************************************************
void Mesh_Track_Pickup::Update_TexturePan(void)
{
	//-------------------------------------------------------------
	//Apply to master mesh
	if(gBikesGo)
	{
		iMeshTexturePanSet(Pickup_Energy,&D3DXVECTOR2(0.0f,-gTexturePan_Med),&D3DXVECTOR2(0.0f,0.0f),true);
		iMeshTexturePanSet(Pickup_Weapon,&D3DXVECTOR2(0.0f,-gTexturePan_Med),&D3DXVECTOR2(0.0f,0.0f),true);
		iMeshTexturePanSet(Pickup_Utility,&D3DXVECTOR2(0.0f,-gTexturePan_Med),&D3DXVECTOR2(0.0f,0.0f),true);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GLOBAL - MESH - TRACK - PICKUP - UPDATE MESH SPIN
///*****************************************************************
void Mesh_Track_Pickup::Update_MeshSpin(void)
{
	//-------------------------------------------------------------
	//Work out spin for all pickups
	if(gBikesGo)
	{
		D3DXQUATERNION q1 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
		D3DXQUATERNION qSpin = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
		iQuaternionFromEulerAngles(&qSpin,0.0f,gTextureRot_Med,0.0f);
		//Apply Spin to All pickups
		//Weapons
		if(gWeaponsTrackEnable)
		{
			for(int i=0;i<MAX_WEAPON_PICKUPS;i++)
			{
				q1 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
				iQuaternionMultiply(&q1,&qSpin,&cGame_Mode_Controller.WeaponsPickup.qPickup[i]);
				iMeshImposterOrientationSet(Pickup_Weapon,i,&q1,false);
			}
			//Utility
			for(int i=0;i<MAX_UTILITY_PICKUPS;i++)
			{
				q1 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
				iQuaternionMultiply(&q1,&qSpin,&cGame_Mode_Controller.UtilityPickup.qPickup[i]);
				iMeshImposterOrientationSet(Pickup_Utility,i,&q1,false);
			}
		}

		//Boost
		if(gBoostTrackEnable)
		{
			for(int i=0;i<MAX_ENERGY_PICKUPS;i++)
			{
				q1 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
				iQuaternionMultiply(&q1,&qSpin,&cGame_Mode_Controller.EnergyPickup.qPickup[i]);
				iMeshImposterOrientationSet(Pickup_Energy,i,&q1,false);
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GLOBAL - MESH - TRACK - PICKUP - DESTROY
///*****************************************************************
void Mesh_Track_Pickup::Destroy(void)
{
	//-------------------------------------------------------------
	ImpostersDestroy_Weapon();
	ImpostersDestroy_Energy();
	ImpostersDestroy_Utility();
	//-------------------------------------------------------------
	iMeshDestroy(Pickup_Weapon);
	iMeshDestroy(Pickup_Energy);
	iMeshDestroy(Pickup_Utility);
	//-------------------------------------------------------------
}