//-----------------------------------------------------------------
// About:
//
// name: "Mesh_Camera.cpp:
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
#include "Mesh_Camera.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - MESH - CAMERA - CONSTRUCTORS
///*****************************************************************
Mesh_Camera::Mesh_Camera(void)
{
	//-------------------------------------------------------------
	//Camera_Speed = NULL;
	for(int i=0;i<MAX_CAMERA_QUADS;i++)
	{
		Camera_Quad[i] = NULL;
	}
	//-------------------------------------------------------------
}

Mesh_Camera::~Mesh_Camera(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - CAMERA - CREATE
///*****************************************************************
void Mesh_Camera::Create(void)
{
	//-------------------------------------------------------------
	////bike shadow
	//Camera_Speed = iMeshCreate("trzero_res\\md5mesh\\camera\\Camera_Speed.md5mesh",1.0f);
	//iMeshDirectionalLightEnableSet(Camera_Speed,false,false,false,false,true);
	//iMeshPointLightEnableSet(Camera_Speed,false,false,0,false,1,false,2,false,3,true);
	////iMeshLocationSet(Camera_Speed,&D3DXVECTOR3(0.0f,0.0f,0.0f),true);
	//iMeshShaderEmissiveSet(Camera_Speed,true);
	//iMeshScaleSet(Camera_Speed,&D3DXVECTOR3(2.0f,2.0f,5.0f),false);
	////-------------------------------------------------------------
	////Show Mesh
	//iMeshShow(Camera_Speed,true);




	for(int i=0;i<MAX_CAMERA_QUADS;i++)
	{
		Camera_Quad[i] = iMeshCreate("trzero_res\\md5mesh\\camera\\camera_quad.md5mesh",1.0f);
		iMeshDirectionalLightEnableSet(Camera_Quad[i],false,false,false,false,true);
		iMeshPointLightEnableSet(Camera_Quad[i],false,false,0,false,1,false,2,false,3,true);
		//iMeshLocationSet(Camera_Speed,&D3DXVECTOR3(0.0f,0.0f,0.0f),true);
		iMeshShaderEmissiveSet(Camera_Quad[i],true);
		iMeshShow(Camera_Quad[i],true);
		//iMeshScaleSet(Camera_Quad[i],&D3DXVECTOR3(2.0f,2.0f,1.0f),false);
		iMeshBlendModeSet(Camera_Quad[i],1,7,5);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - CAMERA - UPDATE
///*****************************************************************
void Mesh_Camera::Update(void)
{
	//-------------------------------------------------------------
	//Update Player
	//Player_Update(cGame_Camera.vCamOutput,cGame_Bike_Player.Manager.qBikeOutputLean);

		float monkeyshit = 3.0f;
	for(int i=0;i<MAX_CAMERA_QUADS;i++)
	{
		if(i==1){monkeyshit = -3.0f;}
		D3DXVECTOR3 FUCKOFF = iVectorLocationOffset(&cGame_Bike_Player.Manager.vTargetMesh,&cGame_Bike_Player.Manager.qBikeOutputLean,&D3DXVECTOR3(monkeyshit,2.0f,0.0f));
		iMeshLocationSet(Camera_Quad[i],&FUCKOFF,false);
		iMeshOrientationSet(Camera_Quad[i],&cGame_Bike_Player.Manager.qBikeOutputLean,false);
	}

	//iPrint("Tr-Zero",42.0f,&D3DXVECTOR2(0.0f,0.0f),&D3DXVECTOR4(1.0f,0.5f,0.1f,1.0f),gFont2,true);
	//-------------------------------------------------------------
	//Shaders
	ShaderUpdate();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - CAMERA - PLAYER UPDATE
///*****************************************************************
void Mesh_Camera::Player_Update(D3DXVECTOR3 v1,D3DXQUATERNION q1)
{
	//-------------------------------------------------------------
	////Shadow
	////iMeshBlendEnableSet(Camera_Speed ,false );
	//static int one = 1;
	//static int two = 1;
	//static int three = 1;

	//if(iKeyClick(VK_NUMPAD1))
	//{
	//	one++;
	//	if(one >5)
	//	{
	//		one = 1;
	//	}
	//}
	//if(iKeyClick(VK_NUMPAD2))
	//{
	//	two++;
	//	if(two >19)
	//	{
	//		two = 1;
	//	}
	//}
	//if(iKeyClick(VK_NUMPAD3))
	//{
	//	three++;
	//	if(three >19)
	//	{
	//		three = 1;
	//	}
	//}

	//D3DXVECTOR2 vDebug = D3DXVECTOR2(-10.0f,0.0f);
	//char Message[1024];
	//sprintf_s(Message,"one - %i",one);
	//iPrint2(Message,18.0f,&vDebug,&D3DXVECTOR4(1.0f,0.5f,0.1f,1.0f),gFont,false);
	//vDebug.y -= 0.5f;
	//sprintf_s(Message,"two - %i",two);
	//iPrint2(Message,18.0f,&vDebug,&D3DXVECTOR4(1.0f,0.5f,0.1f,1.0f),gFont,false);
	//vDebug.y -= 1.0f;
	//sprintf_s(Message,"three - %i",three);
	//iPrint2(Message,18.0f,&vDebug,&D3DXVECTOR4(1.0f,0.5f,0.1f,1.0f),gFont,false);

	//iMeshBlendModeSet(Camera_Speed,
	//					one,
	//					two ,
	//					three );
	////float speed = iFloatInterpolateSmooth(cGame_Bike_Player.Manager.fAcceleration_Speed,1.0f,2.0f,1.0f,0.99f);
	////iMeshAlphaToleranceSet(Camera_Speed,0.99f,false);
	////iMeshColorSet(Camera_Speed,&D3DXVECTOR3(speed,speed,speed),false);
	//iMeshLocationSet(Camera_Speed,&v1,false);
	//iMeshOrientationSet(Camera_Speed,&q1,false);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - GLOBAL - MESH - CAMERA - SHADER UPDATE
///*****************************************************************
void Mesh_Camera::ShaderUpdate(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - MESH - CAMERA - DESTROY
///*****************************************************************
void Mesh_Camera::Destroy(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<MAX_CAMERA_QUADS;i++)
	{
		iMeshDestroy(Camera_Quad[i]);
	}
	//-------------------------------------------------------------
}