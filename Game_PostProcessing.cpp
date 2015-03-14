//-----------------------------------------------------------------
// About:
//
// name: "Game_PostProcessing.cpp:
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
#include "Game_PostProcessing.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - POSTPROCESSING - CONSTRUCTORS
///*****************************************************************
Game_PostProcessing::Game_PostProcessing(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}

Game_PostProcessing::~Game_PostProcessing(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - POSTPROCESSING - Create
///*****************************************************************
void Game_PostProcessing::Create(void)
{
	//-------------------------------------------------------------
	//Load Shadow settings data files (per track)
	//Load_ShadowSettings();
	//-------------------------------------------------------------
	//Reset the Camera PP Stack
	///Clear the stack
	iCameraPostProcessRemove(gCamera,true);
	//-------------------------------------------------------------
	//Apply the Camera PP Stack
	//if(gLensFlareEnable)
	//{
		////Lumiance (OE2 = White only bloom...........)
		//iCameraPostProcess_LuminanceBloom_Use(gCamera);
		//iPostProcessLuminanceBloomSet(gCamera,gBloomThreshold,gBloomRadius,gBloomBlurCount);
		////-------------------------------------------------------------
		////Lens Flare test - Really need mesh level control (like object glow)
		//iCameraPostProcess_LensFlare_Use(gCamera);
		//iPostProcessLensFlareSet(gCamera,4,0.5f,0.5f,&D3DXVECTOR3(0.05f,0.05f,0.1f),2.0f);
		//iPostProcessLensFlareTextureSet(gCamera,NULL,NULL);
		//iPostProcessLensFlareEnable(gCamera,true);
	//}

	//Reflections Test
	//iMeshShaderNormalMapReflectSet(cGame_Track.Mesh_Track[0],NULL,gReflectRes,gReflectMipMap,0.5f,gReflectMaxRange,false,false);
	//for(int i=1;i<MAX_010;i++)
	//{
	//	iMeshCubicEnvironmentMapCasterAdd(cGame_Track.Mesh_Track[i],cGame_Track.Mesh_Track[0],false);
	//}
	//iMeshReflectionAmountSet(cGame_Track.Mesh_Track[0],0.5f,false);

	//iShadowMapCascadeDestroy();
	//if(gShadowsEnable)
	//{
	//	iCameraShadowMapCascadeEnable(gCamera,true);
	//	iShadowMapCascadeCreate(1,gShadowsResolution);

	//	D3DXQUATERNION qDown = D3DXQUATERNION(0.0f,0.0f,0.0,1.0f);
	//	iQuaternionFromEulerAngles(&qDown,gShadowsOrientation.x,gShadowsOrientation.y,gShadowsOrientation.z);
	//	iShadowMapCascadeFocusSet(gCamera,0,&gShadowsLocation,&qDown);

		//iShadowMapCascadeConfigureSet(gCamera,0,gShadowsSize.x,gShadowsSize.y);//side/depth

	//	iCameraShadowMapCascadeDensitySet(gCamera,gShadowDensity);
	//	iCameraShadowMapBlurSet(gCamera,1,gShadowBlur);
	//	iCameraShadowMapCascadeBiasSet(gCamera,0,gShadowBias);
	//	//iShadowMapCascadeDebugVisualShow();

	//	iCameraPostProcess_Shadows_Use(gCamera);

	//	for(int i=0;i<MAX_TRACK_MESH;i++)
	//	{
	//		if(cGame_Track.Mesh_Track[i]!=NULL &&
	//			cGame_Track.Mesh_Track_ShadowType[i] > -1)
	//		{
	//			iMeshShadowMapCascadeEnable(cGame_Track.Mesh_Track[i],true,false);
	//			iMeshShadowMapCascadeModeSet(cGame_Track.Mesh_Track[i],cGame_Track.Mesh_Track_ShadowType[i],false);
	//			if(cGame_Track.Mesh_Track_ShadowDoubleSided[i])
	//			{
	//				iMeshShadowCullModeSet(cGame_Track.Mesh_Track[i],D3D11_CULL_NONE);
	//			}
	//			else
	//			{
	//				iMeshShadowCullModeSet(cGame_Track.Mesh_Track[i],D3D11_CULL_BACK);
	//			}
	//		}
	//	}
	//	iMeshShadowMapCascadeEnable(cGame_Mesh.Bike.Shell[cGame_Mesh.Bike.ActiveModel_Player],true,false);
	//	iMeshShadowMapCascadeEnable(cGame_Mesh.Bike.Rider[cGame_Mesh.Bike.ActiveModel_Player],true,false);
	//	iMeshShadowMapCascadeModeSet(cGame_Mesh.Bike.Shell[cGame_Mesh.Bike.ActiveModel_Player],1,false);
	//	iMeshShadowMapCascadeModeSet(cGame_Mesh.Bike.Rider[cGame_Mesh.Bike.ActiveModel_Player],1,false);
	//}

	if(gGlowEnable)
	{
		//Object
		iCameraPostProcess_ObjectGlow_Use(gCamera,false,true);
		iPostProcessGlowSet(gCamera,gGlowValues.x,gGlowValues.y,gGlowValues.z,gGlowValues.w);//
	}
	if(gDoFEnable)
	{
		iCameraPostProcess_DOF_Blur_Use(gCamera,gDoFQuality,false,gDoFQuality);
		iPostProcessDepthOfFieldSet(gCamera,0.005f,0.15f,3.5f,26.0f);
	}
	if(gBlurEnable)
	{
		iCameraPostProcess_MotionBlur_Use(gCamera,true);
		iPostProcessMotionBlurSet(gCamera,gBlurCamera,gBlurObject,gBlurSamples);
	}
	//iCameraPostProcess_XPro_Use(gCamera,NULL);
	//iPostProcessXProBlendSet(gCamera,0.25f);
	//iCameraPostProcess_XProCrush_Use(gCamera,NULL);
	//iPostProcessXProCrushSet(gCamera,-0.45f);
	//-------------------------------------------------------------
	//Apply stack
	//iCameraPostProcess_GodRays_Use(gCamera,2 );
	//iCameraPostProcess_Cartoon_Use(gCamera);
	iCameraPostProcess_BleachBypass_Use(gCamera);
	iPostProcessBleachBypassIntensitySet(gCamera,0.5f);//0.6f

	iCameraPostProcess_Vignette_Use(gCamera);
	iPostProcessVignetteSet(gCamera,2.0f,0.2f);

	iCameraPostProcessApply(gCamera);
	iPostProcessColorCorrectionSet(gCamera,0.0f,gColourCorrection.y,gColourCorrection.z,gColourCorrection.w);

	//fxaa
	iCameraFXAAEnable(gCamera,gFxaaEnable);
	iCameraFXAALevelSet(gCamera,gFxaaQuality);
	//iCameraFXAAEnable(gCamera,true);
	//iCameraFXAALevelSet(gCamera,4);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - POSTPROCESSING - UPDATE
///*****************************************************************
void Game_PostProcessing::Update(void)
{
	//-------------------------------------------------------------
	//Motion Blur Update
	gBlurCamera = 0.0f;
	//gBlurObject = 0.0f;
	if(gBlurEnable)
	{
		//Update Mask Origin
		iPostProcessCameraMotionBlurMaskUpdate(gCamera,&cGame_Bike[cGame_Camera.SpectateId].Manager.vTargetMesh,250.0f);
		//Update Camera Blur 
		if(gMenu_Active)
		{
			gBlurCamera = 50.0f;
		}
		else if(gRaceState==1)
		{
			gBlurCamera = iFloatInterpolateSmooth(abs(cGame_Bike[cGame_Camera.SpectateId].Manager.fAcceleration_Speed),2.0f,10.0f,0.0f,5.0f);
			//Sound Barrier
			if(gSoundBarrier)
			{
				gBlurCamera = iFloatInterpolate(abs(cGame_Bike[cGame_Camera.SpectateId].Manager.fAcceleration_Speed),7.0f,8.0f,100.0f,200.0f);
			}
		}
		iPostProcessMotionBlurSet(gCamera,gBlurCamera,gBlurObject,gBlurSamples);
	}
	//-------------------------------------------------------------
	//Update Gamma
	cGame_Gamma_Fade.Update();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - POSTPROCESSING - Save_ShadowSettings
///*****************************************************************
void Game_PostProcessing::Save_ShadowSettings(void)
{
	//-------------------------------------------------------------
	HANDLE hFile; 
	DWORD dwDone; 

	sprintf_s(gCharBuffer,"trzero_res\\settings\\#shadows\\cascade_%d.bin",gGameState);
	iGlobalPathMake(gCharBuffer);

	hFile = CreateFile(gCharBuffer,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		//---------------------------------------------------------
		WriteFile(hFile,&gShadowsOrientation,sizeof(D3DXVECTOR3),&dwDone,NULL);
		WriteFile(hFile,&gShadowsLocation,sizeof(D3DXVECTOR3),&dwDone,NULL);
		WriteFile(hFile,&gShadowsSize,sizeof(D3DXVECTOR2),&dwDone,NULL);
		WriteFile(hFile,&gShadowBlur,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&gShadowBias,sizeof(float),&dwDone,NULL);
		WriteFile(hFile,&gShadowDensity,sizeof(float),&dwDone,NULL);
		//---------------------------------------------------------
		CloseHandle(hFile); 
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - POSTPROCESSING - Load_ShadowSettings
///*****************************************************************
void Game_PostProcessing::Load_ShadowSettings(void)
{
	//-------------------------------------------------------------
	sprintf_s(gCharBuffer,"trzero_res\\settings\\#shadows\\cascade_%d.bin",gGameState);
	iGlobalPathMake(gCharBuffer);

	if(iFileExists(gCharBuffer))
	{
		HANDLE hFile; 
		DWORD dwDone; 

		hFile = CreateFile(gCharBuffer,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			//-----------------------------------------------------
			ReadFile(hFile,&gShadowsOrientation,sizeof(D3DXVECTOR3),&dwDone,NULL);
			ReadFile(hFile,&gShadowsLocation,sizeof(D3DXVECTOR3),&dwDone,NULL);
			ReadFile(hFile,&gShadowsSize,sizeof(D3DXVECTOR2),&dwDone,NULL);
			ReadFile(hFile,&gShadowBlur,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&gShadowBias,sizeof(float),&dwDone,NULL);
			ReadFile(hFile,&gShadowDensity,sizeof(float),&dwDone,NULL);
			//-----------------------------------------------------
			CloseHandle(hFile); 
		}
	}
	//-------------------------------------------------------------
}