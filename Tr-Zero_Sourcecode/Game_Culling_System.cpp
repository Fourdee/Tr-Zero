//-----------------------------------------------------------------
// About:
//
// name: "Game_Culling_System.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Culling_System.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - FONT - CONSTRUCTORS
///*****************************************************************
Game_Culling_System::Game_Culling_System(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Culling_System::~Game_Culling_System(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CULLING - ZeroData
///*****************************************************************
void Game_Culling_System::ZeroData(void)
{
	//-------------------------------------------------------------
	//Active Mesh Triggers (for Game_Mesh)
	for(int i=0;i<40;i++)
	{
		bShell[i] = false;
		bGlow[i] = false;
		bRider[i] = false;
	}
	//Set player to always visable
	bShell[gAi_Max_Count] = true;
	bGlow[gAi_Max_Count] = true;
	bRider[gAi_Max_Count] = true;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - CULLING - CREATE
///*****************************************************************
void Game_Culling_System::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - CULLING - CullBikeAi
///*****************************************************************
void Game_Culling_System::CullBikeAi(void)
{
	////-------------------------------------------------------------
	////Optimize
	//if(gGameState>0)
	//{
	//	///Normal Running
	//	gMax_Culling_Bikes_Shown = 19;
	//	gMax_Culling_Bikes_Low_Detail = 14;
	//	gMax_Culling_Bikes_High_Detail = 4;
	//	///Auto reduce Draw Limits
	//	if(gET_DeltaTime>0.02f)
	//	{
	//		gMax_Culling_Bikes_Shown = 5;
	//		gMax_Culling_Bikes_Low_Detail = 2;
	//		gMax_Culling_Bikes_High_Detail = 1;
	//	}
	//}
	//-------------------------------------------------------------
	//  - BIKE AI Imposter culling sets -
	iMeshImposterAutoHide(cGame_Mesh.Bike.Shell[cGame_Mesh.Bike.ActiveModel_Ai],
							&cGame_Camera.vCamOutput,
							gCullRangeMax,
							gAi_Max_Count,
							gMax_Culling_Bikes_Shown);

	iMeshImposterAutoHide(cGame_Mesh.Bike.Glow[cGame_Mesh.Bike.ActiveModel_Ai],
							&cGame_Camera.vCamOutput,
							gCullRangeMax,
							gAi_Max_Count,
							gMax_Culling_Bikes_Low_Detail);

	iMeshImposterAutoHide(cGame_Mesh.Bike.Rider[cGame_Mesh.Bike.ActiveModel_Ai],
							&cGame_Camera.vCamOutput,
							gCullRangeMax,
							gAi_Max_Count,
							gMax_Culling_Bikes_High_Detail);
	//-------------------------------------------------------------
	//Cull Linked sets from their master.
	for(int i=0;i<gAi_Max_Count;i++)
	{
		//
		bShell[i] = iMeshImposterIsShown(cGame_Mesh.Bike.Shell[cGame_Mesh.Bike.ActiveModel_Ai],i);
		bGlow[i] = iMeshImposterIsShown(cGame_Mesh.Bike.Glow[cGame_Mesh.Bike.ActiveModel_Ai],i);
		bRider[i] = iMeshImposterIsShown(cGame_Mesh.Bike.Rider[cGame_Mesh.Bike.ActiveModel_Ai],i);

		//Hide
		if(!bRider[i])
		{
			iMeshImposterHide(cGame_Mesh.Bike.Helmet[cGame_Mesh.Bike.ActiveModel_Ai],i,false);
			iMeshImposterHide(cGame_Mesh.Bike.HelmetGlow[cGame_Mesh.Bike.ActiveModel_Ai],i,false);
			iMeshImposterHide(cGame_Mesh.Bike.RiderGlow[cGame_Mesh.Bike.ActiveModel_Ai],i,false);
			iMeshImposterHide(cGame_Mesh.Bike.Shield[cGame_Mesh.Bike.ActiveModel_Ai],i,false);
			iMeshImposterHide(cGame_Mesh.Bike_Headlight.Headlight[cGame_Mesh.Bike_Headlight.ActiveModel_Ai],i,false);

			iMeshImposterHide(cGame_Mesh.Bike_Engine.EngineL,i,false);
			iMeshImposterHide(cGame_Mesh.Bike_Engine.EngineR,i,false);
			iMeshImposterHide(cGame_Mesh.Bike_Engine.EngineL_Glow,i,false);
			iMeshImposterHide(cGame_Mesh.Bike_Engine.EngineR_Glow,i,false);

			iMeshImposterHide(cGame_Mesh.Bike_Tire.Front_Glow[cGame_Mesh.Bike_Tire.ActiveModel_Ai],i,false);
			iMeshImposterHide(cGame_Mesh.Bike_Tire.Front_Glow_In[cGame_Mesh.Bike_Tire.ActiveModel_Ai],i,false);
			iMeshImposterHide(cGame_Mesh.Bike_Tire.Back_Glow_In[cGame_Mesh.Bike_Tire.ActiveModel_Ai],i,false);

			iMeshImposterHide(cGame_Mesh.Bike_Weapons.Energy_A,i,false);
			iMeshImposterHide(cGame_Mesh.Bike_Weapons.Secondary_Charging,i,false);
		}
		if(!bGlow[i])
		{
			iMeshImposterHide(cGame_Mesh.Bike_Shadow.Shadow_A,i,false);
			iMeshImposterHide(cGame_Mesh.Bike_Tire.Front[cGame_Mesh.Bike_Tire.ActiveModel_Ai],i,false);
			iMeshImposterHide(cGame_Mesh.Bike_Tire.Back_Glow[cGame_Mesh.Bike_Tire.ActiveModel_Ai],i,false);
		}
		if(!bShell[i])
		{
			iMeshImposterHide(cGame_Mesh.Bike_Tire.Back[cGame_Mesh.Bike_Tire.ActiveModel_Ai],i,false);
			//iMeshImposterHide(cGame_Mesh.Bike_Weapons.Targeting,i,false);
		}
	}
	//-------------------------------------------------------------
	//  - WEAPONS Imposter Hide culling sets -
	///Primary
	const int gMax_Culling_Primary_Shown = 20;
	iMeshImposterAutoHide(cGame_Mesh.Bike_Weapons.P_Primary_Glow,
								&cGame_Camera.vCamOutput,
								gCullRangeMax,
								cGame_Mesh.Bike_Weapons.TOTAL_CREATE_PRIMARY_PROJECTILE,
								gMax_Culling_Primary_Shown);

	///Secondarys
	const int gMax_Culling_Secondary_Shown = 2;
	iMeshImposterAutoHide(cGame_Mesh.Bike_Weapons.P_EMBurst_Projectile,
								&cGame_Camera.vCamOutput,
								gCullRangeMax,
								cGame_Mesh.Bike_Weapons.TOTAL_CREATE_ALL,
								gMax_Culling_Secondary_Shown);

	for(int i=0;i<2;i++)
	{
		iMeshImposterAutoHide(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[i],
									&cGame_Camera.vCamOutput,
									gCullRangeMax,
									cGame_Mesh.Bike_Weapons.TOTAL_CREATE_ALL,
									gMax_Culling_Secondary_Shown);

		iMeshImposterAutoHide(cGame_Mesh.Bike_Weapons.P_Missile_Explosion[i],
									&cGame_Camera.vCamOutput,
									gCullRangeMax,
									cGame_Mesh.Bike_Weapons.TOTAL_CREATE_ALL,
									gMax_Culling_Secondary_Shown);
	}

	iMeshImposterAutoHide(cGame_Mesh.Bike_Weapons.P_Shockwave_Projectile,
								&cGame_Camera.vCamOutput,
								gCullRangeMax,
								cGame_Mesh.Bike_Weapons.TOTAL_CREATE_ALL,
								gMax_Culling_Secondary_Shown);

	iMeshImposterAutoHide(cGame_Mesh.Bike_Weapons.Rail_Projectile,
								&cGame_Camera.vCamOutput,
								gCullRangeMax,
								cGame_Mesh.Bike_Weapons.TOTAL_CREATE_ALL,
								gMax_Culling_Secondary_Shown);

	//-------------------------------------------------------------
}
//*****************************************************************
//GAME - CULLING - iMeshImposterAutoHide
//*****************************************************************
void Game_Culling_System::iMeshImposterAutoHide(MD5MESH* Mesh,
													D3DXVECTOR3* Location,
													float fDistanceMax,
													int ImposterCount,
													int MaxViewableMeshes)
{
    //-------------------------------------------------------------
	//Modified Version of iMeshImposterDistanceBasedGroupAutoCulling
	// - "Shown meshes" are the activator (eg: in use)
	// - This version only hides meshes.
    //-----------------------------------------------------
    //data...
    if(MaxViewableMeshes > ImposterCount){MaxViewableMeshes = ImposterCount;}
    D3DXVECTOR3* Imposter_Loc = new D3DXVECTOR3[ImposterCount];
    float* fRange = new float[ImposterCount];
    float* fRange_Sorted = new float[ImposterCount];
    bool* bHide = new bool[ImposterCount];
	int TotalToSort = 0;
    //-----------------------------------------------------
    //get distance to camera
    for(int i=0;i<ImposterCount;i++)
    {
		//Null Values
        bHide[i] = true;
		fRange[i] = -1.0f;
        fRange_Sorted[i] = fDistanceMax;
		Imposter_Loc[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);

		//Meshes Shown are inuse - So only process active meshes
		if(iMeshImposterIsShown(Mesh,i) &&
			//!iMeshImposterIsCulled(Mesh,i)) //Have to wait for next render loop when using this.
			iMeshImposterBoundingSphereCheck(Mesh,i,gCamera,&D3DXVECTOR3(0.0f,0.0f,0.0f))) //works on the same loop
		{
			iMeshImposterLocation(Mesh,i,&Imposter_Loc[i]);
			fRange[i] = iVectorLength(&(*Location-Imposter_Loc[i]));
			fRange_Sorted[TotalToSort] = fRange[i];
			TotalToSort++;
		}
    }
    //-----------------------------------------------------
    //Sort Ranges (Optimized, only sorts the total shown/needed)
    iFloatQsort(fRange_Sorted,TotalToSort);
    //-----------------------------------------------------
    //find the (MaxViewableMeshes) closest to the camera prep them for manual culling (hiding).
    int TotalShown = 0;
    for(int i=0;i<TotalToSort;i++)
    {
        for(int j=0;j<ImposterCount;j++)
        {
            if(fRange_Sorted[i]==fRange[j])
            {
                if(TotalShown < MaxViewableMeshes && 
					fRange_Sorted[i] <= fDistanceMax)
                 {
                    bHide[j] = false;
                    TotalShown++;
                 }
                 fRange[j] = -1.0f;///clear from pool
                 break;
            }
        }
	}
	//Hide
	for(int i=0;i<ImposterCount;i++)
	{
		//Hide the meshes over draw limit.
        if(bHide[i])
        {
            iMeshImposterHide(Mesh,i,false);
        }
	}
    //-----------------------------------------------------
    //free memory
    SAFE_DELETE_ARRAY(Imposter_Loc);
    SAFE_DELETE_ARRAY(fRange);
    SAFE_DELETE_ARRAY(fRange_Sorted);
    SAFE_DELETE_ARRAY(bHide);
    //-------------------------------------------------------------
}
///*****************************************************************
//GAME - CULLING - Update
///*****************************************************************
void Game_Culling_System::Update(void)
{
	//-------------------------------------------------------------
	//Cull Bikes
	CullBikeAi();
	//-------------------------------------------------------------
}