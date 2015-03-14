//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Spawn.h"
//-----------------------------------------------------------------
Game_Spawn::Game_Spawn(void)
{
	//-------------------------------------------------------------
	ResetData();
	//-------------------------------------------------------------
}

Game_Spawn::~Game_Spawn(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - SPAWN - CREATE
///*****************************************************************
void Game_Spawn::Create(void)
{
	//-------------------------------------------------------------
	ResetData();
	//-------------------------------------------------------------
}
///*****************************************************************
//BIKE - SPAWN - DESTROY
///*****************************************************************
void Game_Spawn::Destroy(void)
{
	//-------------------------------------------------------------
	ResetData();
	//-------------------------------------------------------------
}

///*****************************************************************
//BIKE - SPAWN - ZERO DATA
///*****************************************************************
void Game_Spawn::ResetData(void)
{
	//-------------------------------------------------------------
	float xnudge = 15.0f;
	float znudge = 4.0f;
	float znudgelarge = 8.0f;
	D3DXVECTOR3 vSpawnSet = D3DXVECTOR3(xnudge,2.0f,-10.0f);
	//-------------------------------------------------------------
	//Orientation
	qSpawnLocation = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	iQuaternionFromEulerAngles(&qSpawnLocation,0.0f,0.0f,0.0f);

	if(gTrackReverse==1)
	{
		iQuaternionFromEulerAngles(&qSpawnLocation,0.0f,180.0f,0.0f);
		znudge = -znudge;
		znudgelarge = -znudgelarge;
		vSpawnSet.z = 10.0f;
	}
	//-------------------------------------------------------------
	//Location
	vSpawnLocation[0] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[1] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[2] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[3] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[4] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[5] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[6] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[7] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[8] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[9] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[10] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[11] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[12] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[13] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[14] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[15] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[16] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[17] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[18] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[19] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[20] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[21] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[22] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[23] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[24] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[25] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[26] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[27] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[28] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[29] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[30] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[31] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[32] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[33] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[34] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[35] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[36] = vSpawnSet;
	vSpawnSet.x = 0.0f;vSpawnSet.z -= znudge;
	vSpawnLocation[37] = vSpawnSet;
	vSpawnSet.x = -xnudge;vSpawnSet.z -= znudge;
	vSpawnLocation[38] = vSpawnSet;
	//-----
	vSpawnSet.x = xnudge;vSpawnSet.z -= znudgelarge;
	vSpawnLocation[39] = vSpawnSet;
	//-------------------------------------------------------------
}