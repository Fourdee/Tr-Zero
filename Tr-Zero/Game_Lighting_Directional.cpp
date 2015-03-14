//-----------------------------------------------------------------
// About:
//
// name: "Game_Lighting_Directional.cpp:
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
#include "Game_Lighting_Directional.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - LIGHTING - DIRECTIONAL - CONSTRUCTORS
///*****************************************************************
Game_Lighting_Directional::Game_Lighting_Directional(void)
{
	//-------------------------------------------------------------
	fLight4Orientation = 0.0f;
	//-------------------------------------------------------------
}

Game_Lighting_Directional::~Game_Lighting_Directional(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - LIGHTING - DIRECTIONAL - UPDATE
///*****************************************************************
void Game_Lighting_Directional::Update(void)
{
	//-------------------------------------------------------------
	D3DXQUATERNION q1;
	iQuaternionFromEulerAngles(&q1,101.0f,0.0f,0.0f);//90.0f
	iQuaternionMultiply(&q1,&q1,&cGame_Camera.qCamOutput);
	//-------------------------------------------------------------
	//gDirectLight1
	iLightDirectionalSet(&q1,&gDirectLight1,0);

	//gDirectLight2
	iLightDirectionalSet(&q1,&gDirectLight2,1);

	//gDirectLight3
	iLightDirectionalSet(&q1,&gDirectLight3,2);

	//gDirectLight4
	if(gBikesGo)
	{
		fLight4Orientation += 3.0f;
		if(fLight4Orientation>=360.0f)
		{
			fLight4Orientation -= 360.0f;
		}
	}
	iQuaternionFromEulerAngles(&q1,0.0f,fLight4Orientation,0.0f);//90.0f
	iLightDirectionalSet(&q1,&gDirectLight4,3);
	//-------------------------------------------------------------
}