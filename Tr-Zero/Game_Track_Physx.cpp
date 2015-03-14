//-----------------------------------------------------------------
// About:
//
// name: "Game_Track_Physx.cpp:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Track_Physx.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - TRACK - PHYSX - CONSTRUCTORS
///*****************************************************************
Game_Track_Physx::Game_Track_Physx(void)
{
	//-------------------------------------------------------------
	PhysxActor_Floor		= NULL;
	PhysxActor_Wall			= NULL;
	//-------------------------------------------------------------
}

Game_Track_Physx::~Game_Track_Physx(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TRACK - PHYSX - PHYSXACTOR CREATE
///*****************************************************************
void Game_Track_Physx::Create(void)
{
	//-------------------------------------------------------------
	if(gGameState==0)
	{
		//-------------------------------------------------------------
		//track physx actors create...triangle mesh - of static type
		PhysxActor_Floor = iPhysxActorTriangleMeshCreate("trzero_res\\physxactor\\tracks\\track_menu\\track_floor.bin",
														 true,
														 &D3DXVECTOR3(0.0f,0.0f,0.0f),
														 &D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
														 cGame_Physx_Material.Track,
														 cGame_Physx_Collision_Mask.Default,
														 false);
		PhysxActor_Wall = iPhysxActorTriangleMeshCreate("trzero_res\\physxactor\\tracks\\track_menu\\track_wall.bin",
														true,
													    &D3DXVECTOR3(0.0f,0.0f,0.0f),
													    &D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
													    cGame_Physx_Material.Track,
													    cGame_Physx_Collision_Mask.Default,
													    false);
	}
	else if(gGameState==1)
	{
		//-------------------------------------------------------------
		//track physx actors create...triangle mesh - of static type
		PhysxActor_Floor = iPhysxActorTriangleMeshCreate("trzero_res\\physxactor\\tracks\\track_volex\\track_floor.bin",
														 true,
														 &D3DXVECTOR3(0.0f,0.0f,0.0f),
														 &D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
														 cGame_Physx_Material.Track,
														 cGame_Physx_Collision_Mask.Default,
														 false);
		PhysxActor_Wall = iPhysxActorTriangleMeshCreate("trzero_res\\physxactor\\tracks\\track_volex\\track_wall.bin",
														 true,
													    &D3DXVECTOR3(0.0f,0.0f,0.0f),
													    &D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
													    cGame_Physx_Material.Track,
													    cGame_Physx_Collision_Mask.Default,
													    false);
	}
	else if(gGameState==2)
	{
		//-------------------------------------------------------------
		//track physx actors create...triangle mesh - of static type
		PhysxActor_Floor = iPhysxActorTriangleMeshCreate("trzero_res\\physxactor\\tracks\\track_silence\\track_floor.md5mesh",
														 false,
														 &D3DXVECTOR3(0.0f,0.0f,0.0f),
														 &D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
														 cGame_Physx_Material.Track,
														 cGame_Physx_Collision_Mask.Default,
														 false);
		PhysxActor_Wall = iPhysxActorTriangleMeshCreate("trzero_res\\physxactor\\tracks\\track_silence\\track_wall.md5mesh",
														 false,
													    &D3DXVECTOR3(0.0f,0.0f,0.0f),
													    &D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
													    cGame_Physx_Material.Track,
													    cGame_Physx_Collision_Mask.Default,
													    false);
	}
	else if(gGameState==3)
	{
		//-------------------------------------------------------------
		//track physx actors create...triangle mesh - of static type
		PhysxActor_Floor = iPhysxActorTriangleMeshCreate("trzero_res\\physxactor\\tracks\\track_phantom\\track_floor.md5mesh",
														 false,
														 &D3DXVECTOR3(0.0f,0.0f,0.0f),
														 &D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
														 cGame_Physx_Material.Track,
														 cGame_Physx_Collision_Mask.Default,
														 false);
		PhysxActor_Wall = iPhysxActorTriangleMeshCreate("trzero_res\\physxactor\\tracks\\track_phantom\\track_wall.md5mesh",
														 false,
													    &D3DXVECTOR3(0.0f,0.0f,0.0f),
													    &D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
													    cGame_Physx_Material.Track,
													    cGame_Physx_Collision_Mask.Default,
													    false);
	}
	else if(gGameState==10)
	{
		//-------------------------------------------------------------
		//track physx actors create...triangle mesh - of static type
		PhysxActor_Floor = iPhysxActorTriangleMeshCreate("trzero_res\\physxactor\\tracks\\track_rez\\track_floor.md5mesh",
														 false,
														 &D3DXVECTOR3(0.0f,0.0f,0.0f),
														 &D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
														 cGame_Physx_Material.Track,
														 cGame_Physx_Collision_Mask.Default,
														 false);
		PhysxActor_Wall = iPhysxActorTriangleMeshCreate("trzero_res\\physxactor\\tracks\\track_rez\\track_wall.md5mesh",
														 false,
													    &D3DXVECTOR3(0.0f,0.0f,0.0f),
													    &D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f),
													    cGame_Physx_Material.Track,
													    cGame_Physx_Collision_Mask.Default,
													    false);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - TRACK - PHYSX - DESTROY
///*****************************************************************
void Game_Track_Physx::Destroy(void)
{
	//-------------------------------------------------------------
	iPhysxActorDestroy(PhysxActor_Wall);
	iPhysxActorDestroy(PhysxActor_Floor);
	//-------------------------------------------------------------
}