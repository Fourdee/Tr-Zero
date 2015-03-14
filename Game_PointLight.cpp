//-----------------------------------------------------------------
// About:
//
// name: "Game_PointLight.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
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
#include "Game_PointLight.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - LIGHTING - POINT - CONSTRUCTORS
///*****************************************************************
Game_PointLight::Game_PointLight(void)
{
	//-------------------------------------------------------------
	MAX_POINTLIGHT = 0;
	//Headlights
	PointLight_HeadLight_Alpha				= 0.0f;
	PointLight_HeadLight_Range				= 8.0f;//100
	PointLight_HeadLight_Falloff			= 95.0f;//15
	PointLight_HeadLight_Multi				= 0.8f;
	PointLight_HeadLight_Offset				= D3DXVECTOR3(0.0f,7.0f,30.0f);
	//Shield
	PointLight_Shield_Alpha					= 0.0f;
	PointLight_Shield_Range					= 67.0f;
	PointLight_Shield_Falloff				= 9.0f;
	PointLight_Shield_Multi					= 1.0f;
	PointLight_Shield_Offset				= D3DXVECTOR3(0.0f,7.0f,2.0f);
	//-------------------------------------------------------------
}

Game_PointLight::~Game_PointLight(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - LIGHTING - POINT - Create
///*****************************************************************
void Game_PointLight::Create(void)
{
	//-------------------------------------------------------------
	//Create Pointlights
	MAX_POINTLIGHT = iLightPointCount();
	D3DXVECTOR3	v1 = D3DXVECTOR3(0.0f,10000.0f,0.0f);
	D3DXVECTOR4 Color = D3DXVECTOR4(0.1f,0.1f,0.1f,0.0f);
	D3DXQUATERNION q1 = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	for(int i=0;i<MAX_POINTLIGHT;i++)
	{
		iLightPointSet(&v1,&Color,i);
		iLightPointRangeSet(1.0f,i);
		iLightPointFallOffSet(1.0f,i);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - LIGHTING - POINT - Update
///*****************************************************************
void Game_PointLight::Update(void)
{
	//-------------------------------------------------------------
	D3DXVECTOR4 vPl_Colour = D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f);
	D3DXVECTOR3 vPl = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//-------------------------------------------------------------
	//PointLight - (Find Closest)
	int* SORT_Id = new int[MAX_POINTLIGHT];
	float* SORT_Range = new float[gAi_Max_Count+1];

	//Sort ranges
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		SORT_Range[i] = 600.0f;
		if(cGame_Mesh.Culling.bRider[i])
		{
			SORT_Range[i] = cGame_Bike[i].fDistanceToCam;
		}
	}
	iFloatQsort(SORT_Range,gAi_Max_Count+1);

	//Match data back up
	for(int i=0;i<MAX_POINTLIGHT;i++)
	{
		SORT_Id[i] = -1;
		for(int j=0;j<=gAi_Max_Count;j++)
		{
			if(SORT_Range[i]==cGame_Bike[j].fDistanceToCam)
			{
				SORT_Id[i] = j;
				break;
			}
		}
	}
	//-------------------------------------------------------------
	//Apply
	for(int i=0;i<MAX_POINTLIGHT;i++)
	{
		if(SORT_Id[i]>=0)//Assigned - inuse
		{
			///Shield
			if(cGame_Bike[SORT_Id[i]].Energy.fEnergy < gEnergyWarningLimit)
			{
				vPl_Colour = D3DXVECTOR4(cGame_Bike[SORT_Id[i]].Colour.vShieldColour.x * PointLight_Shield_Multi,
													cGame_Bike[SORT_Id[i]].Colour.vShieldColour.y * PointLight_Shield_Multi,
													cGame_Bike[SORT_Id[i]].Colour.vShieldColour.z * PointLight_Shield_Multi,
													PointLight_Shield_Alpha);
				vPl = iVectorLocationOffset(&cGame_Mesh.Animator.vBike[SORT_Id[i]],&cGame_Mesh.Animator.qBike[SORT_Id[i]],&PointLight_Shield_Offset);
				iLightPointRangeSet(PointLight_Shield_Range,i);
				iLightPointFallOffSet(PointLight_Shield_Falloff,i);
			}
			///Headlights
			else
			{
				vPl_Colour = D3DXVECTOR4(cGame_Bike[SORT_Id[i]].Colour.vBikeColour.x * PointLight_HeadLight_Multi,
													cGame_Bike[SORT_Id[i]].Colour.vBikeColour.y * PointLight_HeadLight_Multi,
													cGame_Bike[SORT_Id[i]].Colour.vBikeColour.z * PointLight_HeadLight_Multi,
													PointLight_HeadLight_Alpha);
				vPl = iVectorLocationOffset(&cGame_Mesh.Animator.vBike[SORT_Id[i]],&cGame_Mesh.Animator.qBike[SORT_Id[i]],&PointLight_HeadLight_Offset);
				iLightPointRangeSet(PointLight_HeadLight_Range,i);
				iLightPointFallOffSet(PointLight_HeadLight_Falloff,i);
			}
			iLightPointSet(&vPl,&vPl_Colour,i);
		}
		else//Not assigned - not inuse
		{
			vPl = D3DXVECTOR3(0.0f,10000.0f,0.0f);
			vPl_Colour = D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f);
			iLightPointSet(&vPl,&vPl_Colour,i);
		}
	}
	//Clear Temp Array
	SAFE_DELETE_ARRAY(SORT_Range);
	SAFE_DELETE_ARRAY(SORT_Id);
	//-------------------------------------------------------------
	//Player Seconday Weapons [4]
	//if(cGame_Bike[gAi_Max_Count].Weapons.SecondaryProjectileAliveTime>1)
	//{
	//	vPl_Colour = D3DXVECTOR4(cGame_Bike[gAi_Max_Count].Colour.vBikeColour.x * 2.0f,
	//											cGame_Bike[gAi_Max_Count].Colour.vBikeColour.y * 2.0f,
	//											cGame_Bike[gAi_Max_Count].Colour.vBikeColour.z * 2.0f,
	//											PointLight_HeadLight_Alpha);
	//	vPl = cGame_Bike[gAi_Max_Count].Weapons.vSecondaryProjectile;
	//	iLightPointRangeSet(PointLight_HeadLight_Range,4);
	//	iLightPointFallOffSet(PointLight_HeadLight_Falloff,4);
	//}
	//else
	//{
	//	vPl = D3DXVECTOR3(0.0f,10000.0f,0.0f);
	//	vPl_Colour = D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f);
	//}
	//iLightPointSet(&vPl,&vPl_Colour,4);
	//-------------------------------------------------------------
	//OE2 Lightpoint search
	iOddityEngine_LightPointSearch();
	//-------------------------------------------------------------
}