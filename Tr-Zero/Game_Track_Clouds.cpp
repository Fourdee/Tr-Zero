//-----------------------------------------------------------------
// About:
//
// name: "Game_Track_Clouds.cpp:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Track_Clouds.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - ENVIRONMENT - TRACK - CONSTRUCTORS
///*****************************************************************
Game_Track_Clouds::Game_Track_Clouds(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<CLOUDS_MAX;i++)
	{	
		Cloud_Mesh[i] = NULL;
	}
	Cloud_A_Tex = NULL;
	Cloud_B_Tex = NULL;
	fCloud_Move = 0.0f;
	//-------------------------------------------------------------
}
Game_Track_Clouds::~Game_Track_Clouds(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ENVIRONMENT - CLOUDS - CREATE 
///*****************************************************************
void Game_Track_Clouds::Create(void)
{
	//-------------------------------------------------------------
	float startheight = 1.0f;
	if(gGameState==2)//silence
	{
		startheight = 250.0f;
	}
	else if(gGameState==3)//phantom
	{
		startheight = 400.0f;
	}
	//-------------------------------------------------------------
	//Texture
	Cloud_A_Tex = iTexture2DCreate("trzero_res\\textures\\clouds\\4.dds");
	Cloud_B_Tex = iTexture2DCreate("trzero_res\\textures\\clouds\\3.dds");
	//-------------------------------------------------------------
	//Mesh
	for(int i=0;i<CLOUDS_MAX;i++)
	{	
		float height = startheight - ((float)i * 25.0f);
		Cloud_Mesh[i] = iMeshCreate("trzero_res\\md5mesh\\clouds\\clouds.md5mesh",gMeshSmoothing);
		iMeshDirectionalLightEnableSet(Cloud_Mesh[i],false,false,false,false,false);
		iMeshPointLightEnableSet(Cloud_Mesh[i],false,false,0,false,1,false,2,false,3,false);
		iMeshShaderEmissiveSet(Cloud_Mesh[i],false);
		iMeshAlphaToleranceSet(Cloud_Mesh[i],0.025f,false);
		iMeshShow(Cloud_Mesh[i],false);
		iMeshLocationSet(Cloud_Mesh[i],&D3DXVECTOR3(0.0f,height,0.0f),false);
		iMeshScaleSet(Cloud_Mesh[i],&D3DXVECTOR3(1.0f,0.5f,1.0f),false);
		if(i==0)
		{
			iMeshColorSet(Cloud_Mesh[i],&D3DXVECTOR3(0.5f,0.5f,0.5f),false);
		}
		else if(i==1)
		{
			iMeshColorSet(Cloud_Mesh[i],&D3DXVECTOR3(2.0f,0.7f,0.5f),false);
			iMeshGlowEnable(Cloud_Mesh[i],gGlowMeshEnable,false);
			iMeshAlphaToleranceSet(Cloud_Mesh[i],0.05f,false);
		}
		else if(i==2)
		{
			iMeshColorSet(Cloud_Mesh[i],&D3DXVECTOR3(0.5f,0.5f,0.5f),false);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ENVIRONMENT - CLOUDS - UPDATE 
///*****************************************************************
void Game_Track_Clouds::Update(void)
{
	//-------------------------------------------------------------
	//Movement
	if(!gPaused)
	{
		fCloud_Move += 0.00005f;
		if(fCloud_Move > 1.0f)
		{
			fCloud_Move = 0.0f;
		}
		for(int i=0;i<CLOUDS_MAX;i++)
		{	
			if(i==0){iMeshTexturePanSet(Cloud_Mesh[i],&D3DXVECTOR2(fCloud_Move,fCloud_Move * 2.0f),&D3DXVECTOR2(0.0f,0.0f),true);}
			else if(i==1){iMeshTexturePanSet(Cloud_Mesh[i],&D3DXVECTOR2(fCloud_Move * 2.0f,-fCloud_Move * 5.0f),&D3DXVECTOR2(0.0f,0.0f),true);}
			else if(i==2){iMeshTexturePanSet(Cloud_Mesh[i],&D3DXVECTOR2(-fCloud_Move * 2.0f,-fCloud_Move),&D3DXVECTOR2(0.0f,0.0f),true);}
		}
	}
	//-------------------------------------------------------------
	//Shader
	ShaderUpdate();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ENVIRONMENT - CLOUDS - SHADERUPDATE 
///*****************************************************************
void Game_Track_Clouds::ShaderUpdate(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<CLOUDS_MAX;i++)
	{	
		//A
		if(i==0)
		{
			iMeshShaderEmissiveTextureUpdate(Cloud_Mesh[i],
											Cloud_A_Tex,
											&D3DXVECTOR2(4.0f,4.0f),
											false);
		}
		else if(i==1)
		{
			iMeshShaderEmissiveTextureUpdate(Cloud_Mesh[i],
											Cloud_B_Tex,
											&D3DXVECTOR2(4.0f,4.0f),
											false);
		}
		else if(i==2)
		{
			iMeshShaderEmissiveTextureUpdate(Cloud_Mesh[i],
											Cloud_A_Tex,
											&D3DXVECTOR2(2.0f,2.0f),
											false);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ENVIRONMENT - CLOUDS - SAMPLERSET 
///*****************************************************************
void Game_Track_Clouds::SamplerSet(void)
{
	//-------------------------------------------------------------
	cGame_Texture2D_Sampler.WrapSet(Cloud_A_Tex);
	cGame_Texture2D_Sampler.WrapSet(Cloud_B_Tex);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ENVIRONMENT - CLOUDS - DESTROY 
///*****************************************************************
void Game_Track_Clouds::Destroy(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<CLOUDS_MAX;i++)
	{	
		iMeshDestroy(Cloud_Mesh[i]);
	}
	iTexture2DDestroy(Cloud_A_Tex);
	iTexture2DDestroy(Cloud_B_Tex);
	fCloud_Move = 0.0f;
	//-------------------------------------------------------------
}
