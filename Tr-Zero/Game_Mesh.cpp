//-----------------------------------------------------------------
// About:
//
// name: "Game_Mesh.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Mesh.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - ASSET - GLOBAL - MESH - CONSTRUCTORS
///*****************************************************************
Game_Mesh::Game_Mesh(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}

Game_Mesh::~Game_Mesh(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ASSET - GLOBAL - MESH - CREATE
///*****************************************************************
void Game_Mesh::Create(void)
{
	//-------------------------------------------------------------
	//Lighting
	//Light_Direct.Create();
	Light_Point.Create();
	//-------------------------------------------------------------
	//Mesh
	Animator.Create();
	Bike.Create();
	Bike_Tire.Create();
	Bike_Engine.Create();
	Bike_Shadow.Create();
	Bike_Headlight.Create();
	Bike_Weapons.Create();
	Bike_Trail.Create();
	Track_Pickup.Create();
	//Camera
	//Camera.Create();
	//-------------------------------------------------------------
	//Culling
	Culling.Create();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ASSET - GLOBAL - MESH - UPDATE
///*****************************************************************
void Game_Mesh::Update(void)
{
	//-------------------------------------------------------------
	//Mesh
	Animator.Update();
	Bike.Update();
	Bike_Tire.Update();
	Bike_Engine.Update();
	Bike_Shadow.Update();
	Bike_Headlight.Update();
	Track_Pickup.Update();
	Bike_Trail.Update();
	Bike_Weapons.Update();
	//-------------------------------------------------------------
	//Lighting
	Light_Direct.Update();
	Light_Point.Update();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ASSET - GLOBAL - MESH - Update_Globals
///*****************************************************************
void Game_Mesh::Update_Globals(void)
{
	//-------------------------------------------------------------
	if(gBikesGo ||
		gGameState==0)
	{
		//gTexturePan_Slow
		gTexturePan_Slow -= 0.005f;
		if(gTexturePan_Slow < -1.0f)
		{
			gTexturePan_Slow += 1.0f;
		}
		//gTexturePan_Med
		gTexturePan_Med -= 0.025f;
		if(gTexturePan_Med < -1.0f)
		{
			gTexturePan_Med += 1.0f;
		}
		//gTexturePan_Fast
		gTexturePan_Fast -= 0.1f;
		if(gTexturePan_Fast < -1.0f)
		{
			gTexturePan_Fast += 1.0f;
		}
		//gTexturePan_Vibrate
		float fVibrate_Target = iFloatRand(-0.1f,0.1f);
		iFloatTendTo2(gTexturePan_Vibrate,fVibrate_Target,6.0f);
		//-------------------------------------------------------------
		//gTextureRot_Slow
		gTextureRot_Slow += 1.0f;
		if(gTextureRot_Slow > 360.0f)
		{
			gTextureRot_Slow -= 360.0f;
		}
		//gTextureRot_Med
		gTextureRot_Med += 4.0f;
		if(gTextureRot_Med > 360.0f)
		{
			gTextureRot_Med -= 360.0f;
		}
		//gTextureRot_Fast
		gTextureRot_Fast += 6.0f;
		if(gTextureRot_Fast > 360.0f)
		{
			gTextureRot_Fast -= 360.0f;
		}
		//-------------------------------------------------------------
		//gMesh_UpDown
		float fUpDown_Target = iFloatRand(-0.5f,0.5f);
		iFloatTendTo2(gMesh_UpDown,fUpDown_Target,25.0f);
		//-------------------------------------------------------------
		//g_qMesh_XY_Spin
		iQuaternionFromEulerAngles(&g_qMesh_XY_Spin,gTextureRot_Slow,-gTextureRot_Slow,0.0f);
		//g_qMesh_XY_Spin_Inverse
		iQuaternionFromEulerAngles(&g_qMesh_XY_Spin_Inverse,-gTextureRot_Slow,gTextureRot_Slow,0.0f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ASSET - GLOBAL - MESH - DESTROY
///*****************************************************************
void Game_Mesh::Destroy(void)
{
	//-------------------------------------------------------------
	Animator.Destroy();
	Bike.Destroy();
	Bike_Tire.Destroy();
	Bike_Engine.Destroy();
	Bike_Shadow.Destroy();
	Bike_Headlight.Destroy();
	Track_Pickup.Destroy();
	Bike_Trail.Destroy();
	Bike_Weapons.Destroy();
	//Camera
	//Camera.Destroy();
	//-------------------------------------------------------------
}