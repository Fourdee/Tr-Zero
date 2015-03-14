//-----------------------------------------------------------------
// About:
//
// name: "Game_Optimiser.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Optimiser.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - FONT - CONSTRUCTORS
///*****************************************************************
Game_Optimiser::Game_Optimiser(void)
{
	//-------------------------------------------------------------
	bOptimiseBypass = false;
	ZeroData();
	//-------------------------------------------------------------
}

Game_Optimiser::~Game_Optimiser(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - OPTIMISER - ZeroData
///*****************************************************************
void Game_Optimiser::ZeroData(void)
{
	//-------------------------------------------------------------
	bStart = false;
	bBypass = false;
	Timer_AutoOptimise = 0;
	MissedFrames = 0;
	PreAutoDelay = 0;
	bOptimiseFailed = false;
	OptimiserResultScore = 0;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - OPTIMISER - CREATE
///*****************************************************************
void Game_Optimiser::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - OPTIMISER - Update
///*****************************************************************
void Game_Optimiser::Update(void)
{
	//-------------------------------------------------------------
	if(gGameState==0)//Menu Only
	{
		//AutoOptimise
		if(bStart)
		{
			StartOptimise();		
			bStart = false;
		}
		else if(bBypass)
		{
			ForceBypass();
			bBypass = false;
		}
		else if(gGfxOptimiserState==1)
		{
			cGame_Optimiser.AutoOptimise();
		}
		else if(bOptimiseFailed)
		{
			gGammaMulti = 0.1f;
			//Print error
			iPrint3((char*)"Optimiser Failed",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,-7.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
			iPrint3((char*)"- - - - - - - - - - - - - - - - ",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,-8.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,false);
			iPrint3((char*)"Your system is unable to sustain the required framerate at this resolution",cGame_Font.f18pt,&D3DXVECTOR2(0.0f,-9.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			iPrint3((char*)"Please Lower your resolution, then try again.",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,-10.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			iPrint3((char*)"If consistent failures occur, use 'Force Bypass' as a last resort",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		}
		else if(gGfxOptimiserState==2)
		{
			gGammaMulti = 0.1f;
			//Print Info
			iPrint3((char*)"Optimiser Setup",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,-7.0f),&D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f),gFont,false);
			iPrint3((char*)"- - - - - - - - - - - - - - - - ",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,-8.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,false);
			iPrint3((char*)"Please select your resolution and click Apply to optimise.",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,-9.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			iPrint3((char*)"Please consider 1280x720, or lower, for optimal Performance/Quality Ratio",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,-10.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			iPrint3((char*)"on low/mid spec systems",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		}
		else if(bOptimiseBypass && gMenuId==3)
		{
			gGammaMulti = 0.1f;
			//Print bypass
			iPrint3((char*)"Optimiser Bypassed - Network Disabled",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,-7.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
			iPrint3((char*)"- - - - - - - - - - - - - - - - ",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,-8.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,false);
			iPrint3((char*)"Only use this setting if you experience issues optimising.",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,-9.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			iPrint3((char*)"This mode will skip the optimiser setup, and, allow you to play.",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,-10.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			iPrint3((char*)"Note: Network gameplay is disabled for this setting!",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,-11.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		}
		else if(gGfxOptimiserState==0 && gMenuId==3)
		{
			gGammaMulti = 0.1f;
			//Print finished
			iPrint3((char*)"Optimiser Finished",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,-7.0f),&D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f),gFont,false);
			iPrint3((char*)"- - - - - - - - - - - - - - - - ",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,-8.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,false);
			iPrint3((char*)"Click Apply to confirm setup, or, change resolution to run again",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,-9.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			
			sprintf_s(gCharBuffer,"Optimiser Score %i",OptimiserResultScore);
			iPrint3(gCharBuffer,cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,-10.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - OPTIMISER - START
///*****************************************************************
void Game_Optimiser::StartOptimise(void)
{
	//-------------------------------------------------------------
	bOptimiseBypass = false;
	ZeroData();
	//-------------------------------------------------------------
	///Setup for running of optimiser
	gGfxOptimiserState = 1;

	gGlowEnable = false;

	cGame_Settings.bUse_Anisotrpic_Filter = false;
	cGame_Settings.Anisotropic_Level = 1;

	gDoFEnable = false;
	gDoFQuality	= 2;

	gBlurEnable = false;

	gFxaaEnable = false;
	gFxaaQuality = 2;

	///Uprate some gfx settings to allow for tollerance
	gBlurSamples = 16;
	gMax_Culling_Bikes_Shown = 25;
	gMax_Culling_Bikes_Low_Detail = 14;
	gMax_Culling_Bikes_High_Detail = 7;

	cGame_Settings.ResolutionApply();
	cGame_Asset_Global_Texture.SamplerUpdate();
	cGame_PostProcessing.Create();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - OPTIMISER - STOP
///*****************************************************************
void Game_Optimiser::StopOptimise(void)
{
	//-------------------------------------------------------------
	//Finished
	gGfxOptimiserState = 0;
	///Downrate gfx back to default settings to allow for tollerance
	//gMax_Culling_Bikes_Shown = 25;
	//gMax_Culling_Bikes_Low_Detail = 14;
	//gMax_Culling_Bikes_High_Detail = 7;
	gMax_Culling_Bikes_Shown = 19;
	gMax_Culling_Bikes_Low_Detail = 14;
	gMax_Culling_Bikes_High_Detail = 4;

	gBlurSamples = 8;
	//Check for failed 60fps
	if(bOptimiseFailed)
	{
		OptimiserResultScore = 0;
		gGfxOptimiserState = 2;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - OPTIMISER - ForceBypass
///*****************************************************************
void Game_Optimiser::ForceBypass(void)
{
	//-------------------------------------------------------------
	//Finished
	bOptimiseBypass = true;
	gGfxOptimiserState = 0;
	///Downrate bike count
	gMax_Culling_Bikes_Shown = 9;
	gMax_Culling_Bikes_Low_Detail = 6;
	gMax_Culling_Bikes_High_Detail = 3;
	gBlurSamples = 8;
	//Check for failed 60fps
	bOptimiseFailed = false;
	//Default SEttings
	//-------------------------------------------------------------
	gFxaaEnable = false;
	gFxaaQuality = 2;

	gBlurEnable = false;

	gDoFQuality = 2;
	gDoFEnable = false;

	cGame_Settings.bUse_Anisotrpic_Filter = false;
	cGame_Settings.Anisotropic_Level = 1;

	gGlowEnable = true;

	cGame_Settings.ResolutionApply();
	cGame_Asset_Global_Texture.SamplerUpdate();
	cGame_PostProcessing.Create();
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - OPTIMISER - AutoOptimise
///*****************************************************************
void Game_Optimiser::AutoOptimise(void)
{
	//-------------------------------------------------------------
	//Reset Bike Movement
	//gBikesGo = true;
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		if(i==gAi_Max_Count)
		{
			cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed = 0.0f;
			cGame_Bike[gAi_Max_Count].fSteering = 0.0f;
			cGame_Bike[gAi_Max_Count].Manager.vBikeOrigin = cGame_Spawn.vSpawnLocation[gAi_Max_Count];
			cGame_Bike[gAi_Max_Count].Manager.qBikeOrigin = cGame_Spawn.qSpawnLocation;
		}
		else
		{
			cGame_Bike[i].Manager.fAcceleration_Speed = 0.0f;
			cGame_Bike[i].fSteering = 0.0f;
			cGame_Bike[i].Manager.vBikeOrigin = cGame_Spawn.vSpawnLocation[i];
			cGame_Bike[i].Manager.qBikeOrigin = cGame_Spawn.qSpawnLocation;
		}
	}
	//-------------------------------------------------------------
	//Print some data for optimising
	//for(int i=0;i<gAi_Max_Count;i++)
	//{
	//	D3DXVECTOR2 Ai2dLoc;
	//	if(i3DLocationToScreen(&Ai2dLoc,&cGame_Bike[i].Manager.vTargetMesh,gCamera))
	//	{
	//		iPrint((char*)"Optimiser",cGame_Font.f24pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,0.02f),gFont,false);
	//		Ai2dLoc.y -= 0.5f;
	//		iPrint((char*)"Running",cGame_Font.f24pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,0.0f,0.0f,0.02f),gFont,false);
	//		Ai2dLoc.y -= 0.5f;
	//		iPrint((char*)"------",cGame_Font.f24pt,&Ai2dLoc,&D3DXVECTOR4(1.0f,1.0f,1.0f,0.02f),gFont,false);
	//		Ai2dLoc.y -= 0.5f;
	//	}
	//}
	//-------------------------------------------------------------
	//Start Pre-Delay
	if(PreAutoDelay<300)
	{
		PreAutoDelay++;
	}
	//-------------------------------------------------------------
	else
	{
		//Calculate Missed frames
		if(gFps<57)
		{
			MissedFrames += 57 - gFps;
		}

		//Start Timer
		bool bApplyNewGfx = false;
		Timer_AutoOptimise++;
		if(Timer_AutoOptimise>=60)
		{
			if(MissedFrames <= 45)//Add graphics 
			{
				if(!gGlowEnable)
				{
					gGlowEnable = true;
					bApplyNewGfx = true;
				}
				else if(!cGame_Settings.bUse_Anisotrpic_Filter)
				{
					cGame_Settings.bUse_Anisotrpic_Filter = true;
					cGame_Settings.Anisotropic_Level = 2;
					bApplyNewGfx = true;
				}
				else if(!gDoFEnable)
				{
					gDoFEnable = true;
					gDoFQuality = 2;
					bApplyNewGfx = true;
				}
				else if(!gBlurEnable)
				{
					gBlurEnable = true;
					bApplyNewGfx = true;
				}
				else if(!gFxaaEnable)
				{
					gFxaaEnable = true;
					bApplyNewGfx = true;
				}
				else if(cGame_Settings.Anisotropic_Level<4)
				{
					cGame_Settings.bUse_Anisotrpic_Filter = true;
					cGame_Settings.Anisotropic_Level = 4;
					bApplyNewGfx = true;
				}
				//else if(!gHbaoEnable)
				//{
				//	gHbaoEnable = true;
				//	bApplyNewGfx = true;
				//}
				else if(gDoFQuality==2)
				{
					gDoFQuality = 1;
					bApplyNewGfx = true;
				}
				else if(gFxaaQuality==2)
				{
					gFxaaQuality = 3;
					bApplyNewGfx = true;
				}
				//else if(gFxaaQuality==3)
				//{
				//	gFxaaQuality = 4;
				//	bApplyNewGfx = true;
				//}
				else
				{
					//Finished
					StopOptimise();
				}
				OptimiserResultScore++;
			}
			else //FPS below Threshold! Reduce Last graphic option
			{
				//if(gFxaaQuality==4)
				//{
				//	gFxaaQuality = 3;
				//	bApplyNewGfx = true;
				//}
				if(gFxaaQuality==3)
				{
					gFxaaQuality = 2;
				}
				else if(gDoFQuality==1)
				{
					gDoFQuality = 2;
				}
				//else if(gHbaoEnable)
				//{
				//	gHbaoEnable = false;
				//	bApplyNewGfx = true;
				//}
				else if(cGame_Settings.Anisotropic_Level==4)
				{
					cGame_Settings.bUse_Anisotrpic_Filter = true;
					cGame_Settings.Anisotropic_Level = 2;
				}
				else if(gFxaaEnable)
				{
					gFxaaEnable = false;
				}
				else if(gBlurEnable)
				{
					gBlurEnable = false;
				}
				else if(gDoFEnable)
				{
					gDoFEnable = false;
				}
				else if(cGame_Settings.bUse_Anisotrpic_Filter)
				{
					cGame_Settings.bUse_Anisotrpic_Filter = false;
					cGame_Settings.Anisotropic_Level = 1;
				}
				else if(gGlowEnable)
				{
					gGlowEnable = false;
				}
				else
				{
					//User below 60fps on lowest settings
					//Prompt for lowering resolution
					bOptimiseFailed = true;
				}
				bApplyNewGfx = true;
				//Finished
				OptimiserResultScore--;
				StopOptimise();
			}

			if(bApplyNewGfx)
			{
				cGame_Asset_Global_Texture.SamplerUpdate();
				cGame_PostProcessing.Create();
			}
			PreAutoDelay = 260;
			MissedFrames = 0;
			Timer_AutoOptimise = 0;
		}
	}
	sprintf_s(gCharBuffer,"Dropped %i",MissedFrames);
	iPrint(gCharBuffer,cGame_Font.f22pt,&D3DXVECTOR2(8.0f,8.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	sprintf_s(gCharBuffer,"Timer %i",Timer_AutoOptimise);
	iPrint(gCharBuffer,cGame_Font.f22pt,&D3DXVECTOR2(8.0f,7.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
}
