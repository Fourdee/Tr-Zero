//-----------------------------------------------------------------
// About:
//
// name: "Game_Physx_Collision_Mask.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
// usage: create the physx collision masks that will be used throughout the game.
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Physx_Collision_Mask.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - PHYSX - COLLISION MASKS - CONSTRUCTORS
///*****************************************************************
Game_Physx_Collision_Mask::Game_Physx_Collision_Mask(void)
{
	//-------------------------------------------------------------
	Default = NULL;
	//-------------------------------------------------------------
}

Game_Physx_Collision_Mask::~Game_Physx_Collision_Mask(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - PHYSX - COLLISION MASKS - CREATE
///*****************************************************************
void Game_Physx_Collision_Mask::Create(void)
{
	//-------------------------------------------------------------
	Default = iPhysxCollisionMaskCreate(1,1,1,1);
	
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - PHYSX - COLLISION MASKS - DESTROY
///*****************************************************************
void Game_Physx_Collision_Mask::Destroy(void)
{
	//-------------------------------------------------------------
	iPhysxCollisionMaskDestroy(Default);
	
	//-------------------------------------------------------------
}