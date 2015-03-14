//-----------------------------------------------------------------
// About:
//
// name: "Game_Hud.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Hud.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - HUD - CONSTRUCTORS
///*****************************************************************
Game_Hud::Game_Hud(void)
{
	//-------------------------------------------------------------
	//Hud
	Sprite = NULL;
	///Utility
	Sprite_Utility_1 = NULL;
	///Sprite_Secondary_1
	Sprite_Secondary_1 = NULL;
	//Targeting System
	for(int i=0;i<2;i++)
	{
		SpriteTar[i] = NULL;
	}
	//Player Crosshair
	SpriteCrossHair = NULL;
	//Weapon Icon Sprites
	for(int i=0;i<4;i++)
	{
		Sprite_Utility_Icon[i] = NULL;
		Sprite_Secondary_Icon[i] = NULL;
	}
	//Scoreboard
	Sprite_ScoreBoard = NULL;
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Hud::~Game_Hud(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - HUD - CREATE
///*****************************************************************
void Game_Hud::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//Hud Parts
	Sprite = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Hud1,gCamera);
	iSpriteLocationSet(Sprite,&D3DXVECTOR2(0.0f,0.0f));
	iSpriteScaleSet(Sprite,&D3DXVECTOR2(5.0f,2.5f * gScreenYScale));
	iSpriteColorSet(Sprite,&D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f));
	iSpriteShow(Sprite);
	//imposters
	iSpriteImpostersCreate(Sprite,3);
	for(int i=0;i<3;i++)
	{
		iSpriteImposterShow(Sprite,i);
		iSpriteImposterColorSet(Sprite,i,&D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f));
	}
	///Utility
	Sprite_Utility_0 = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Hud_Utility_0,gCamera);
	iSpriteLocationSet(Sprite_Utility_0,&D3DXVECTOR2(-10.0f,-6.0f));
	iSpriteScaleSet(Sprite_Utility_0,&D3DXVECTOR2(2.0f,2.0f * gScreenYScale));
	Sprite_Utility_1 = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Hud_Utility_1,gCamera);
	iSpriteLocationSet(Sprite_Utility_1,&D3DXVECTOR2(-10.0f,-6.0f));
	iSpriteScaleSet(Sprite_Utility_1,&D3DXVECTOR2(8.0f,2.0f * gScreenYScale));
	///Secondary
	Sprite_Secondary_0 = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Hud_Secondary_0,gCamera);
	iSpriteLocationSet(Sprite_Secondary_0,&D3DXVECTOR2(-10.0f,-6.0f));
	iSpriteScaleSet(Sprite_Secondary_0,&D3DXVECTOR2(2.0f,2.0f * gScreenYScale));
	Sprite_Secondary_1 = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Hud_Secondary_1,gCamera);
	iSpriteLocationSet(Sprite_Secondary_1,&D3DXVECTOR2(-10.0f,-6.0f));
	iSpriteScaleSet(Sprite_Secondary_1,&D3DXVECTOR2(8.0f,2.0f * gScreenYScale));
	//Weapon Icon Sprites
	for(int i=0;i<4;i++)
	{
		Sprite_Utility_Icon[i] = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Hud_Utility_Icons[i],gCamera);
		Sprite_Secondary_Icon[i] = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Hud_Secondary_Icons[i],gCamera);
		iSpriteScaleSet(Sprite_Utility_Icon[i],&D3DXVECTOR2(2.0f,2.0f * gScreenYScale));
		iSpriteScaleSet(Sprite_Secondary_Icon[i],&D3DXVECTOR2(2.0f,2.0f * gScreenYScale));
	}
	//-------------------------------------------------------------
	//Tracking Sprites
	for(int i=0;i<2;i++)
	{
		SpriteTar[i] = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Target_Tex[i],gCamera);
		iSpriteScaleSet(SpriteTar[i],&D3DXVECTOR2(3.0f,3.0f));
		iSpriteColorSet(SpriteTar[i],&vSpriteTar_Colour[i]);
	}
	//-------------------------------------------------------------
	//Player Crosshair
	SpriteCrossHair = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Target_Tex[2],gCamera);
	iSpriteColorSet(SpriteCrossHair,&D3DXVECTOR4(1.0f,1.0f,1.0f,0.4f));
	iSpriteScaleSet(SpriteCrossHair,&D3DXVECTOR2(0.8f,0.8f));
	//-------------------------------------------------------------
	//Scoreboard
	Sprite_ScoreBoard = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Hud_Scoreboard,gCamera);
	iSpriteColorSet(Sprite_ScoreBoard,&D3DXVECTOR4(1.0f,1.0f,1.0f,0.4f));
	iSpriteScaleSet(Sprite_ScoreBoard,&D3DXVECTOR2(5.0f,5.0f * gScreenYScale));
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - HUD - UPDATE
///*****************************************************************
void Game_Hud::Update(void)
{
	//-------------------------------------------------------------
	if(gGameState==0)//menu
	{
		//Networked Player Names Hover
		Update_NetworkPlayerNamesHover();
	}
	//-------------------------------------------------------------
	else
	{
		//Spectate Selector (obtain data to use)
		Update_SpectateSelector();

		//HUD Main- Show
		if(!gMenu_Active && 
			!gResetLevel && 
			gGameState==gGameStateChange && 
			gRaceState==1 &&
			!bScoreboard &&
			!gDisable2D)
		{
			Update_Hud_Sprite(true);
			Update_Hud_Print();
			Update_LapTimers();
			///Enable weapons part of hud
			if(gBikesGo && gWeaponsEnable) 
			{
				Update_WeaponsInfo(true);
				Update_CrossHair(true);
				Update_Targeting(cGame_Bike[cGame_Camera.SpectateId].Weapons.bTrackingEnabled);
				Update_Heat(true);
				KillBoard();
			}
		}
		//HUD Main- Hide
		else
		{
			Update_Hud_Sprite(false);
			Update_WeaponsInfo(false);
			Update_CrossHair(false);
			Update_Targeting(false);
			Update_Heat(false);
		}

		if(!gDisable2D)
		{
			//Spectate Info
			Update_SpectateInfo();
			//Scoreboard
			Update_Scoreboard();
			//Networked Player Names Hover
			Update_NetworkPlayerNamesHover();
		}
		else
		{
			bScoreboard = false;
			Update_Scoreboard();
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - Update_SpectateSelector
///*****************************************************************
void Game_Hud::Update_SpectateSelector(void)
{
	//-------------------------------------------------------------
	vTarget_Crosshair				= cGame_Bike[cGame_Camera.SpectateId].Weapons.vPlayerCrosshair;
	vTarget_Colour					= cGame_Bike[cGame_Camera.SpectateId].Colour.vBikeColour;
	Target_PrimaryHeat				= cGame_Bike[cGame_Camera.SpectateId].Weapons.PrimaryHeat;
	Target_SecondaryWeaponType		= cGame_Bike[cGame_Camera.SpectateId].Weapons.SecondaryWeaponType;
	Target_UtilityType				= cGame_Bike[cGame_Camera.SpectateId].Weapons.UtilityType;
	Target_Speed					= cGame_Bike[cGame_Camera.SpectateId].Manager.fAcceleration_Speed * 230.0f;
	Target_Energy					= cGame_Bike[cGame_Camera.SpectateId].Energy.fEnergy;

	Target_SecondaryCharging			= cGame_Bike[cGame_Camera.SpectateId].Weapons.bSecondaryWeaponCharging;
	Target_SecondaryChargingTime		= cGame_Bike[cGame_Camera.SpectateId].Weapons.SecondaryWeaponChargeTime;
	Target_SecondaryChargingTimeMax		= cGame_Bike[cGame_Camera.SpectateId].Weapons.SecondaryWeaponChargeTimeMax;
	Target_UtilityTime					= cGame_Bike[cGame_Camera.SpectateId].Weapons.UtilityAliveTime;
	Target_UtilityTimeMax				= cGame_Bike[cGame_Camera.SpectateId].Weapons.UtilityAliveTimeMax;

	Target_Kills					= cGame_Bike[cGame_Camera.SpectateId].Weapons.TotalKills;
	Target_Deaths					= cGame_Bike[cGame_Camera.SpectateId].Weapons.TotalDeaths;
	Target_Position					= cGame_RaceTracker.Position_Current[cGame_Camera.SpectateId];
	Target_Laps						= cGame_RaceTracker.Lap_Current[cGame_Camera.SpectateId];
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - Update_Hud_Sprite
///*****************************************************************
void Game_Hud::Update_Hud_Sprite(bool bActive)
{
	//-------------------------------------------------------------
	//Hide all Sprites
	iSpriteHide(Sprite);
	for(int i=0;i<3;i++)
	{
		iSpriteImposterHide(Sprite,i);
	}
	//-------------------------------------------------------------
	//Show - Animate Sprites
	if(bActive)
	{
		iVector2TendTo(&vSprite,&D3DXVECTOR2(-12.0f,-10.0f),25.0f);
		if(cGame_Bike[cGame_Camera.SpectateId].Weapons.bBeingHit)
		{
			//wobble
			float fWobble = iFloatRand(-0.4f,0.4f);
			vSprite.x = vSprite.x + fWobble;
			fWobble = iFloatRand(-0.4f,0.4f);
			vSprite.y = vSprite.y + fWobble;
		}
		iFloatTendTo2(Sprite_Alpha,0.3f,25.0f);
		iSpriteColorSet(Sprite,&D3DXVECTOR4(vTarget_Colour.x,vTarget_Colour.y,vTarget_Colour.z,Sprite_Alpha));
		iSpriteLocationSet(Sprite,&vSprite);

		iSpriteShow(Sprite);
		for(int i=0;i<3;i++)
		{
			iSpriteImposterShow(Sprite,i);
			iSpriteImposterColorSet(Sprite,i,&D3DXVECTOR4(vTarget_Colour.x,vTarget_Colour.y,vTarget_Colour.z,Sprite_Alpha));
			if(i==0){iSpriteImposterLocationSet(Sprite,i,&D3DXVECTOR2(-vSprite.x,vSprite.y));}
			else if(i==1){iSpriteImposterLocationSet(Sprite,i,&D3DXVECTOR2(vSprite.x,-vSprite.y));}
			else if(i==2){iSpriteImposterLocationSet(Sprite,i,&D3DXVECTOR2(-vSprite.x,-vSprite.y));}
		}
	}
	//Fade Sprites
	else if(!gDisable2D && Sprite_Alpha >= 0.012f)
	{
		iVector2TendTo(&vSprite,&D3DXVECTOR2(0.0f,-5.0f),25.0f);
		iFloatTendTo2(Sprite_Alpha,0.0f,25.0f);
		iSpriteLocationSet(Sprite,&D3DXVECTOR2(vSprite.x,vSprite.y));
		iSpriteColorSet(Sprite,&D3DXVECTOR4(1.0f,1.0f,1.0f,Sprite_Alpha));

		iSpriteShow(Sprite);
		for(int i=0;i<3;i++)
		{
			iSpriteImposterShow(Sprite,i);
			iSpriteImposterColorSet(Sprite,i,&D3DXVECTOR4(1.0f,1.0f,1.0f,Sprite_Alpha));
			if(i==0){iSpriteImposterLocationSet(Sprite,i,&D3DXVECTOR2(-vSprite.x,vSprite.y));}
			else if(i==1){iSpriteImposterLocationSet(Sprite,i,&D3DXVECTOR2(vSprite.x,-vSprite.y));}
			else if(i==2){iSpriteImposterLocationSet(Sprite,i,&D3DXVECTOR2(-vSprite.x,-vSprite.y));}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - Update_WeaponsInfo
///*****************************************************************
void Game_Hud::Update_WeaponsInfo(bool bActive)
{
	//-------------------------------------------------------------
	//Hide
	iSpriteHide(Sprite_Utility_0);
	iSpriteHide(Sprite_Utility_1);
	iSpriteHide(Sprite_Secondary_0);
	iSpriteHide(Sprite_Secondary_1);
	///Weapon Icon Sprites
	for(int i=0;i<4;i++)
	{
		iSpriteHide(Sprite_Utility_Icon[i]);
		iSpriteHide(Sprite_Secondary_Icon[i]);
	}

	//Update
	if(bActive)
	{
		///loc
		D3DXVECTOR2 vSecondary = vSprite;
		vSecondary.y += 3.0f;
		vSecondary.x += 1.0f;
		D3DXVECTOR2 vUtility = vSecondary;
		vUtility.y += 2.5f;

		///Sprite text background
		iSpriteLocationSet(Sprite_Utility_1,&vUtility);
		iSpriteColorSet(Sprite_Utility_1,&D3DXVECTOR4(vTarget_Colour.x,vTarget_Colour.y,vTarget_Colour.z,0.1f));

		iSpriteLocationSet(Sprite_Secondary_1,&vSecondary);
		iSpriteColorSet(Sprite_Secondary_1,&D3DXVECTOR4(vTarget_Colour.x,vTarget_Colour.y,vTarget_Colour.z,0.1f));

		///Sprite Main circle
		vSecondary.x -= 3.0f;
		vUtility.x -= 3.0f;
		iSpriteLocationSet(Sprite_Secondary_0,&vSecondary);
		iSpriteColorSet(Sprite_Secondary_0,&D3DXVECTOR4(vTarget_Colour.x,vTarget_Colour.y,vTarget_Colour.z,0.1f));
		iSpriteLocationSet(Sprite_Utility_0,&vUtility);
		iSpriteColorSet(Sprite_Utility_0,&D3DXVECTOR4(vTarget_Colour.x,vTarget_Colour.y,vTarget_Colour.z,0.1f));
		iSpriteShow(Sprite_Utility_0);
		iSpriteShow(Sprite_Secondary_0);
		//Weapon Icon Sprites
		for(int i=0;i<4;i++)
		{
			iSpriteLocationSet(Sprite_Utility_Icon[i],&vUtility);
			iSpriteLocationSet(Sprite_Secondary_Icon[i],&vSecondary);
		}

		//activeate sprites
		if(Target_SecondaryWeaponType>=0)
		{
			iSpriteShow(Sprite_Secondary_Icon[Target_SecondaryWeaponType]);
			iSpriteShow(Sprite_Secondary_1);
		}
		if(Target_UtilityType>=0)
		{
			iSpriteShow(Sprite_Utility_Icon[Target_UtilityType]);
			iSpriteShow(Sprite_Utility_1);
		}


		//Text print
		vSecondary.x += 3.0f;
		vUtility.x += 3.0f;
		vSecondary.x -= 1.75f;
		vUtility.x -= 1.75f;
		vSecondary.y += 0.1f;
		vUtility.y -= 0.5f;

		///Print Weapon Names
		iPrint((char*)cGame_Global_Text_Description.Weapon_Secondary_Name(Target_SecondaryWeaponType).c_str(),cGame_Font.f14pt,&vSecondary,&gFontWhite,gFont2,false);
		iPrint((char*)cGame_Global_Text_Description.Weapon_Utility_Name(Target_UtilityType).c_str(),cGame_Font.f14pt,&vUtility,&gFontWhite,gFont2,false);

		//Print Duration/Change LCD
		const int MAX_DISPLAY = 12;
		float temp = 0.0f;
		int DisplayTotal = 0;
		///Print Duration on Secondary Charges
		if(Target_SecondaryCharging)
		{
			temp = iFloatInterpolate((float)Target_SecondaryChargingTime,0.0f,(float)Target_SecondaryChargingTimeMax,0.0f,(float)MAX_DISPLAY);
			DisplayTotal = (int)temp;
			vSecondary.y -= 0.75f;
			vSecondary.x -= 0.25f;
			for(int i=0;i<DisplayTotal;i++)
			{
				float fRed = iFloatInterpolate((float)i,0.0f,(float)MAX_DISPLAY,1.0f,0.0f);
				float fGreen = iFloatInterpolate((float)i,0.0f,(float)MAX_DISPLAY,0.0f,1.0f);
				iPrint((char*)"/",cGame_Font.f20pt,&vSecondary,&D3DXVECTOR4(fRed,fGreen,0.0f,1.0f),gFont2,false);
				vSecondary.x += 0.3f;
			}
		}
		///Print Duration on utilitys
		if(Target_UtilityType>=0)
		{
			temp = iFloatInterpolate((float)Target_UtilityTime,0.0f,(float)Target_UtilityTimeMax,(float)MAX_DISPLAY,1.0f);
			DisplayTotal = (int)temp;
			vUtility.y += 0.75f;
			vUtility.x -= 0.25f;
			for(int i=0;i<DisplayTotal;i++)
			{
				float fRed = iFloatInterpolate((float)i,0.0f,(float)MAX_DISPLAY,1.0f,0.0f);
				float fGreen = iFloatInterpolate((float)i,0.0f,(float)MAX_DISPLAY,0.0f,1.0f);
				iPrint((char*)"\\",cGame_Font.f20pt,&vUtility,&D3DXVECTOR4(fRed,fGreen,0.0f,1.0f),gFont2,false);
				vUtility.x += 0.3f;
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - Update_Hud_Print
///*****************************************************************
void Game_Hud::Update_Hud_Print(void)
{
	//-------------------------------------------------------------
	const float InfoOffset = -1.5f;//1.05f
	//-------------------------------------------------------------
	//Print Speed
	iPrint3((char*)"- Speed -",cGame_Font.f14pt,&D3DXVECTOR2(-vSprite.x,vSprite.y + InfoOffset),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont2,true);
	sprintf_s(gCharBuffer,"%0.0f",Target_Speed);
	iPrint(gCharBuffer,cGame_Font.f20pt,&D3DXVECTOR2(-vSprite.x,vSprite.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont2,true);
	//-------------------------------------------------------------
	//Print Energy (fFontSize[2])
	float EnergyAlpha = 1.0f;
	float EnergyColour = iFloatInterpolate(Target_Energy,0.0f,cGame_Upgrades.fEnergyMax[gAi_Max_Count],0.1f,1.0f);
	iPrint3((char*)"- Energy -",cGame_Font.f14pt,&D3DXVECTOR2(vSprite.x,vSprite.y + InfoOffset),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont2,true);
	sprintf_s(gCharBuffer,"%0.0f",Target_Energy);
	fFontSize[2] = fFontSizeTarget;
	if(Target_Energy < gEnergyWarningLimit)
	{
		EnergyAlpha = cGame_Bike[cGame_Camera.SpectateId].Colour.vShieldColour.x / 1.5f;
		fFontSize[2] = fFontSizeTarget * cGame_Bike[cGame_Camera.SpectateId].Colour.vShieldColour.x;
	}
	iPrint(gCharBuffer,fFontSize[2],&D3DXVECTOR2(vSprite.x,vSprite.y),&D3DXVECTOR4(1.0f,EnergyColour,EnergyColour,EnergyAlpha),gFont2,true);
	//-------------------------------------------------------------
	//Print Position (fFontSize[3])
	static int PositionCheck = gAi_Max_Count + 1;
	if(PositionCheck != cGame_RaceTracker.Position_Current[cGame_Camera.SpectateId])
	{
		fFontSize[3] = fFontSizeTarget * 1.75f;
		PositionCheck = cGame_RaceTracker.Position_Current[cGame_Camera.SpectateId];
	}
	iFloatTendTo2(fFontSize[3],fFontSizeTarget,15.0f);
	iPrint3((char*)"- Position -",cGame_Font.f14pt,&D3DXVECTOR2(vSprite.x,-vSprite.y - InfoOffset),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont2,true);
	iPrint((char*)"|",cGame_Font.f20pt,&D3DXVECTOR2(vSprite.x,-vSprite.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.3f),gFont2,true);
	sprintf_s(gCharBuffer,"%i",Target_Position);
	iPrint(gCharBuffer,fFontSize[3],&D3DXVECTOR2(vSprite.x - 0.75f,-vSprite.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont2,true);
	sprintf_s(gCharBuffer,"%i",cGame_RaceTracker.Total_AliveBikes);
	iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(vSprite.x + 0.75f,-vSprite.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont2,true);
	//-------------------------------------------------------------
	//Lap Print
	if(gLapMax==999)
	{
		//Print Infinite Laps
		iPrint3((char*)"- Lap -",cGame_Font.f14pt,&D3DXVECTOR2(-vSprite.x,-vSprite.y - InfoOffset),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.6f),gFont2,true);
		iPrint((char*)"Infinite",cGame_Font.f20pt,&D3DXVECTOR2(-vSprite.x,-vSprite.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont2,true);
	}
	else
	{
		//Print Laps
		iPrint3((char*)"- Lap -",cGame_Font.f14pt,&D3DXVECTOR2(-vSprite.x,-vSprite.y - InfoOffset),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.6f),gFont2,true);
		iPrint((char*)"|",cGame_Font.f20pt,&D3DXVECTOR2(-vSprite.x,-vSprite.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,true);
		sprintf_s(gCharBuffer,"%i",Target_Laps);
		iPrint(gCharBuffer,cGame_Font.f20pt,&D3DXVECTOR2(-vSprite.x - 0.75f,-vSprite.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont2,true);
		sprintf_s(gCharBuffer,"%i",gLapMax);
		iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(-vSprite.x + 0.75f,-vSprite.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.6f),gFont2,true);
	}
	//-------------------------------------------------------------
	//CountDown timers
	if(gRaceCountdown<3600 ||
		gGameMode==4 ||
		gGameMode==5)
	{
		///Print Countdown Timer
		D3DXVECTOR2 vKillTarget = D3DXVECTOR2(-vSprite.x - 5.0f,vSprite.y);
		int Minutes = 0;
		int Seconds = gRaceCountdown / 60;

		while(Seconds >= 60)
		{
			Minutes += 1;
			Seconds -= 60;
		}
		iPrint3((char*)"- Time Remaning -",cGame_Font.f14pt,&D3DXVECTOR2(-vKillTarget.x,vKillTarget.y - 1.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.6f),gFont,true);
		iPrint3((char*)":",cGame_Font.f20pt,&D3DXVECTOR2(-vKillTarget.x,vKillTarget.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,true);

		if(Minutes<10){sprintf_s(gCharBuffer,"0%i",Minutes);}
		else{sprintf_s(gCharBuffer,"%i",Minutes);}
		iPrint3(gCharBuffer,cGame_Font.f20pt,&D3DXVECTOR2(-vKillTarget.x  - 0.5f,vKillTarget.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,true);

		if(Seconds<10){sprintf_s(gCharBuffer,"0%i",Seconds);}
		else{sprintf_s(gCharBuffer,"%i",Seconds);}
		iPrint3(gCharBuffer,cGame_Font.f20pt,&D3DXVECTOR2(-vKillTarget.x  + 0.5f,vKillTarget.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,true);
	}
	//-------------------------------------------------------------
	//Print Kills/Deaths
	if(gWeaponsTrackEnable)
	{
		D3DXVECTOR2 vKillTarget = D3DXVECTOR2(-vSprite.x - 5.0f,vSprite.y);
		///KillCount Check (adds scale to fontsize on change)
		if(KillCountCheck != Target_Kills)
		{
			fFontSize[0] = fFontSizeTarget * 5.0f;
			KillCountCheck = Target_Kills;
		}
		iFloatTendTo2(fFontSize[0],fFontSizeTarget,25.0f);

		if(gGameMode==4)
		{
			///Print Kills Required
			iPrint3((char*)"- Kills Required -",cGame_Font.f14pt,&D3DXVECTOR2(vKillTarget.x,vKillTarget.y - 1.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.6f),gFont,true);
			iPrint((char*)"|",cGame_Font.f20pt,&D3DXVECTOR2(vKillTarget.x,vKillTarget.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,true);
			sprintf_s(gCharBuffer,"%i",Target_Kills);
			iPrint(gCharBuffer,fFontSize[0],&D3DXVECTOR2(vKillTarget.x - 0.75f,vKillTarget.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,true);
			sprintf_s(gCharBuffer,"%i",cGame_Mode_Controller.Annihilation.KillsRequired);
			iPrint(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(vKillTarget.x + 0.75f,vKillTarget.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.6f),gFont,true);
		}
		else
		{
			///Print Kills
			iPrint3((char*)"- Kills | Deaths -",cGame_Font.f14pt,&D3DXVECTOR2(vKillTarget.x,vKillTarget.y - 1.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.6f),gFont,true);
			iPrint3((char*)"|",cGame_Font.f20pt,&D3DXVECTOR2(vKillTarget.x,vKillTarget.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,true);
			sprintf_s(gCharBuffer,"%i",Target_Kills);
			iPrint3(gCharBuffer,fFontSize[0],&D3DXVECTOR2(vKillTarget.x - 0.75f,vKillTarget.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,true);
			sprintf_s(gCharBuffer,"%i",Target_Deaths);
			iPrint3(gCharBuffer,cGame_Font.f16pt,&D3DXVECTOR2(vKillTarget.x + 0.75f,vKillTarget.y),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.6f),gFont,true);
		}
	}
	//-------------------------------------------------------------
	//Respawn info
	if(cGame_Bike[cGame_Camera.SpectateId].bRespawning)
	{
		gGammaMulti = 0.8f;

		D3DXVECTOR2 vRespawn = D3DXVECTOR2(0.0f,8.0f);
		int DisplayTimer = 1 + ((gRespawnTimerMax - cGame_Bike[cGame_Camera.SpectateId].RespawnTimer) / 60);
		iPrint3((char*)"Respawning",cGame_Font.f24pt,&vRespawn,&D3DXVECTOR4(1.0f,1.0f,1.0f,0.8f),gFont,true);
		vRespawn.y -= 2.0f;
		sprintf_s(gCharBuffer,"%i",DisplayTimer);
		iPrint3(gCharBuffer,cGame_Font.f32pt,&vRespawn,&gMenuFontColour,gFont,true);
		vRespawn.y = -6.0f;
		///Wrong way
		if(cGame_RaceTracker.bWrongWay[cGame_Camera.SpectateId])
		{
			iPrint3((char*)"Direction Invalid",cGame_Font.f18pt,&vRespawn,&gMenuFontColour,gFont2,true);
		}
		///Killed By
		else
		{
			int Index = cGame_Bike[cGame_Camera.SpectateId].Weapons.KilledByID;

			iPrint3((char*)"Killed by:",cGame_Font.f18pt,&vRespawn,&D3DXVECTOR4(1.0f,1.0f,1.0f,0.8f),gFont,true);
			vRespawn.y -= 1.5f;

			if(Index<gNumberOfClients)//Net
			{
				sprintf_s(gCharBuffer,"%s",(char*)cGame_Bike[Index].Name.c_str());
				iPrint3(gCharBuffer,cGame_Font.f26pt,&vRespawn,&D3DXVECTOR4(cGame_Bike[Index].Colour.vBikeColourTarget.x,cGame_Bike[Index].Colour.vBikeColourTarget.y,cGame_Bike[Index].Colour.vBikeColourTarget.z,1.0f),gFont2,true);
			}
			else if(cGame_Bike[cGame_Camera.SpectateId].Weapons.KilledByID==cGame_Camera.SpectateId)//me?
			{
				iPrint3((char*)"Suicide?",cGame_Font.f26pt,&vRespawn,&D3DXVECTOR4(cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.x,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.y,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.z,1.0f),gFont2,true);
			}
			else//Offline AI
			{
				sprintf_s(gCharBuffer,"Ai #%i",cGame_Bike[cGame_Camera.SpectateId].Weapons.KilledByID);
				iPrint3(gCharBuffer,cGame_Font.f26pt,&vRespawn,&D3DXVECTOR4(cGame_Bike[Index].Colour.vBikeColourTarget.x,cGame_Bike[Index].Colour.vBikeColourTarget.y,cGame_Bike[Index].Colour.vBikeColourTarget.z,0.8f),gFont2,true);
			}
		}

	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - UPDATE CROSSHAIR
///*****************************************************************
void Game_Hud::Update_CrossHair(bool bActive)
{
	//-------------------------------------------------------------
	iSpriteHide(SpriteCrossHair);
	//-------------------------------------------------------------
	//Update
	if(bActive)
	{
		//Rotate Sprites
		SpriteTar_Orientation += 4.0f / SpriteTar_Scale[0];
		if(SpriteTar_Orientation > 360.0f)
		{
			SpriteTar_Orientation -= 360.0f;
		}
		iSpriteOrientationSet(SpriteCrossHair,-SpriteTar_Orientation);
		//locations
		iSpriteLocationSet(SpriteCrossHair,&vTarget_Crosshair);
		iSpriteShow(SpriteCrossHair);
		//-------------------------------------------------------------
		//tagging
		if(cGame_Bike[cGame_Camera.SpectateId].Weapons.TaggedTargetId>-1)
		{
			D3DXVECTOR2 vTagged;
			i3DLocationToScreen(&vTagged,&cGame_Bike[cGame_Bike[cGame_Camera.SpectateId].Weapons.TaggedTargetId].Manager.vBikeOutput,gCamera);
			///Print Energy
			if(cGame_Bike[cGame_Bike[cGame_Camera.SpectateId].Weapons.TaggedTargetId].Energy.bAlive)
			{
				float fEnergyPercent = iFloatInterpolate(cGame_Bike[cGame_Bike[cGame_Camera.SpectateId].Weapons.TaggedTargetId].Energy.fEnergy,0.0f,cGame_Upgrades.fEnergyMax[cGame_Bike[cGame_Camera.SpectateId].Weapons.TaggedTargetId],0.0f,100.0f);
				vTagged.y -= 1.0f;
				sprintf_s(gCharBuffer,"%0.0f",fEnergyPercent);
				iPrint3(gCharBuffer,cGame_Font.f16pt,&vTagged,&D3DXVECTOR4(0.0f,0.7f,1.0f,0.8f),gFont2,true);
			}
			///Print Finished race
			if(!cGame_RaceTracker.bBikeRacing[cGame_Bike[cGame_Camera.SpectateId].Weapons.TaggedTargetId])
			{
				vTagged.y -= 1.0f;
				iPrint3((char*)"Finished Race",cGame_Font.f14pt,&vTagged,&D3DXVECTOR4(1.0f,0.2f,0.0f,0.8f),gFont2,true);
			}
			///Print Destroyed
			else if(!cGame_Bike[cGame_Bike[cGame_Camera.SpectateId].Weapons.TaggedTargetId].Energy.bAlive)
			{
				vTagged.y -= 1.0f;
				iPrint3((char*)"Destroyed",cGame_Font.f14pt,&vTagged,&D3DXVECTOR4(1.0f,0.2f,0.0f,0.8f),gFont2,true);
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - UPDATE HEAT
///*****************************************************************
void Game_Hud::Update_Heat(bool bActive)
{
	//-------------------------------------------------------------
	//Update
	if(bActive)
	{
		D3DXVECTOR2 vPrintL = vTarget_Crosshair;
		D3DXVECTOR2 vPrintR = vTarget_Crosshair;

		vPrintL.x -= 0.75f;
		vPrintR.x += 0.75f;

		//Print Heat Indicators
		float Alpha = iFloatInterpolateSmooth((float)Target_PrimaryHeat,0.0f,(float)gPrimaryHeatMax,0.0f,0.6f);
		int DisplayTotal = (int)iFloatInterpolate((float)Target_PrimaryHeat,0.0f,(float)gPrimaryHeatMax,0.0f,5.0f);;
		for(int i=0;i<DisplayTotal;i++)
		{
			float Scale = iFloatInterpolate((float)i,0.0f,(float)DisplayTotal,2.0f,1.0f);
			///left
			iPrint((char*)"|",cGame_Font.f18pt / Scale,&vPrintL,&D3DXVECTOR4(1.0f,1.0f - Alpha,0.0f,Alpha),gFont2,true);
			///right
			iPrint((char*)"|",cGame_Font.f18pt / Scale,&vPrintR,&D3DXVECTOR4(1.0f,1.0f - Alpha,0.0f,Alpha),gFont2,true);
			vPrintL.x += 0.075f;
			vPrintR.x -= 0.075f;
		}
		//Print Overheat info
		if(Target_PrimaryHeat>=gPrimaryHeatMax)
		{
			vPrintL = vTarget_Crosshair;
			vPrintL.y += 1.0f;
			iPrint((char*)"OverHeat",cGame_Font.f14pt,&vPrintL,&D3DXVECTOR4(1.0f,0.5f,0.0f,0.6f),gFont2,true);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - UPDATE TARGETING
///*****************************************************************
void Game_Hud::Update_Targeting(bool bActive)
{
	//-------------------------------------------------------------
	//Update
	if(bActive)
	{
		//Missile lock
		if(cGame_Bike[cGame_Camera.SpectateId].Weapons.bTrackingInProgress)
		{
			//Sprite transistions
			D3DXVECTOR4 inner = D3DXVECTOR4(0.8f,0.4f,0.0f,0.1f);
			D3DXVECTOR4 out = D3DXVECTOR4(1.0f,1.0f,1.0f,0.1f);
			iFloatTendTo2(SpriteTar_Scale[0],2.0f,TendToTrackingSprite);
			iFloatTendTo2(SpriteTar_Scale[1],3.2f,TendToTrackingSprite);
			iVector4TendTo(&vSpriteTar_Colour[0],&inner,TendToTrackingSprite);
			iVector4TendTo(&vSpriteTar_Colour[1],&out,TendToTrackingSprite);
			//locations
			D3DXVECTOR2 Screen;
			i3DLocationToScreen(&Screen,&cGame_Bike[cGame_Bike[cGame_Camera.SpectateId].Weapons.CurrentTarget].Manager.vBikeOutput,gCamera);
			iVector2TendTo(&vSpriteTar,&Screen,1.5f);
			//Print info
			D3DXVECTOR2 vprint = vSpriteTar;
			vprint.x += 2.0f;
			if(!cGame_Bike[cGame_Camera.SpectateId].Weapons.bTargetLocked)
			{
				iPrint3((char*)"Tracking",cGame_Font.f18pt,&vprint,&D3DXVECTOR4(vSpriteTar_Colour[0].x,vSpriteTar_Colour[0].x,0.0f,0.5f),gFont,false);
			}
			else
			{
				vSpriteTar_Colour[0] = D3DXVECTOR4(1.0f,0.0f,0.0f,0.15f);
				iPrint3((char*)"Locked",cGame_Font.f18pt,&vprint,&D3DXVECTOR4(vSpriteTar_Colour[0].x,0.0f,0.0f,0.9f),gFont,false);
			}
		}
		else
		{
			//Sprite transistions
			D3DXVECTOR4 inner = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
			D3DXVECTOR4 out = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
			iFloatTendTo2(SpriteTar_Scale[0],3.5f,30.0f);
			iFloatTendTo2(SpriteTar_Scale[1],8.0f,30.0f);
			iVector4TendTo(&vSpriteTar_Colour[0],&inner,30.0f);
			iVector4TendTo(&vSpriteTar_Colour[1],&out,30.0f);
			//location
			D3DXVECTOR2 Screen;
			i3DLocationToScreen(&Screen,&cGame_Bike[cGame_Bike[cGame_Camera.SpectateId].Weapons.PreviousTarget].Manager.vBikeOutput,gCamera);
			iVector2TendTo(&vSpriteTar,&Screen,1.5f);
		}
		//-------------------------------------------------------------
		//Update Sprites
		iSpriteOrientationSet(SpriteTar[0],SpriteTar_Orientation * 2.0f);
		iSpriteOrientationSet(SpriteTar[1],-SpriteTar_Orientation * 2.0f);
		iSpriteScaleSet(SpriteTar[0],&D3DXVECTOR2(SpriteTar_Scale[0] * 2.0f,SpriteTar_Scale[0] * 2.0f));
		iSpriteScaleSet(SpriteTar[1],&D3DXVECTOR2(SpriteTar_Scale[1],SpriteTar_Scale[1]));
		iSpriteColorSet(SpriteTar[0],&vSpriteTar_Colour[0]);
		iSpriteColorSet(SpriteTar[1],&vSpriteTar_Colour[1]);
		iSpriteLocationSet(SpriteTar[0],&vSpriteTar);
		iSpriteLocationSet(SpriteTar[1],&vSpriteTar);

		iSpriteShow(SpriteTar[0]);
		iSpriteShow(SpriteTar[1]);
		//-------------------------------------------------------------
	}
	//-------------------------------------------------------------
	//Disable Sprites
	else if(iSpriteIsShown(SpriteTar[1]))
	{
		//Reset Scale/Colours
		D3DXVECTOR4 inner = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
		D3DXVECTOR4 out = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
		SpriteTar_Scale[0] = 3.5f;
		SpriteTar_Scale[1] = 8.0f;
		vSpriteTar_Colour[0] = inner;
		vSpriteTar_Colour[1] = out;
		iSpriteHide(SpriteTar[0]);
		iSpriteHide(SpriteTar[1]);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - KillBoard
///*****************************************************************
void Game_Hud::KillBoard(void)
{
	//-------------------------------------------------------------
	const float Offset = 0.75f;
	D3DXVECTOR2 vLocation = D3DXVECTOR2(0.0f,9.25f);
	const int MAX_KILLBOARD = 4;
	const int MAX_DISPLAY_TIME = 300;
	//-------------------------------------------------------------
	//Killboard - check for new kills
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		//Nudge new kills up
		if(cGame_Bike[i].Weapons.bKilledBySend)
		{
			const char *Buffer_Name_Killer = cGame_Bike[cGame_Bike[i].Weapons.KilledByID].Name.c_str();
			const char *Buffer_Name_Victim = cGame_Bike[i].Name.c_str();
			string GrabWeaponName = cGame_Global_Text_Description.Weapon_KilledBy_Name(cGame_Bike[i].Weapons.WeaponId_KilledBy);
			const char *Buffer_WeaponUsed = GrabWeaponName.c_str();

			sprintf_s(gCharBuffer,"%s >> (%s) >> %s",Buffer_Name_Killer,Buffer_Name_Victim,Buffer_WeaponUsed);

			Killboard_Msg[3] = Killboard_Msg[2];
			Killboard_Msg[2] = Killboard_Msg[1];
			Killboard_Msg[1] = Killboard_Msg[0];
			Killboard_Msg[0] = (string)gCharBuffer;

			Killboard_Timer[3] = Killboard_Timer[2];
			Killboard_Timer[2] = Killboard_Timer[1];
			Killboard_Timer[1] = Killboard_Timer[0];
			Killboard_Timer[0] = 0;

			//add colour, highlight player/network kills
			vKillboard_Colour[3] = vKillboard_Colour[2];
			vKillboard_Colour[2] = vKillboard_Colour[1];
			vKillboard_Colour[1] = vKillboard_Colour[0];
			vKillboard_Colour[0] = D3DXVECTOR3(0.5f,0.5f,0.5f);
			if(cGame_Bike[i].Weapons.KilledByID<gNumberOfClients || ///networked player
				cGame_Bike[i].Weapons.KilledByID==gAi_Max_Count) ///player
			{
				vKillboard_Colour[0] = cGame_Bike[cGame_Bike[i].Weapons.KilledByID].Colour.vBikeColourTarget;
			}
		}
	}
	//Update print
	for(int i=0;i<MAX_KILLBOARD;i++)
	{
		if(Killboard_Timer[i] < MAX_DISPLAY_TIME)
		{
			Killboard_Timer[i]++;
			float xLoc = iFloatInterpolateSmooth((float)Killboard_Timer[i],0.0f,5.0f,-10.0f,0.0f);
			D3DXVECTOR2 vOut = vLocation;
			vOut.x += xLoc;

			float alpha = iFloatInterpolateSmooth((float)Killboard_Timer[i],(float)MAX_DISPLAY_TIME / 2.0f,(float)MAX_DISPLAY_TIME,0.9f,0.0f);

			iPrint3((char*)Killboard_Msg[i].c_str(),cGame_Font.f16pt,
				   &vOut,
				   &D3DXVECTOR4(vKillboard_Colour[i].x,vKillboard_Colour[i].y,vKillboard_Colour[i].z,alpha),
				   gFont,true);
			vLocation.y += Offset;
		}
	}
	//-------------------------------------------------------------
	//MultiKill System
	vLocation = D3DXVECTOR2(0.0f,8.0f);
	if(cGame_Bike[cGame_Camera.SpectateId].Weapons.MultiKillType>=0)
	{
		//Slide in
		vLocation.x += iFloatInterpolateSmooth((float)cGame_Bike[cGame_Camera.SpectateId].Weapons.MultiKillTimer,0.0f,7.0f,10.0f,0.0f);
		float alpha = iFloatInterpolateSmooth((float)cGame_Bike[cGame_Camera.SpectateId].Weapons.MultiKillTimer,(float)gMaxMultiKillTimer / 2.0f,(float)gMaxMultiKillTimer,1.0f,0.0f);
		iPrint3((char*)cGame_Bike[cGame_Camera.SpectateId].Weapons.MultiKillName.c_str(),
			cGame_Font.f30pt,
				&vLocation,
				&D3DXVECTOR4(gMenuFontColour.x,gMenuFontColour.y,gMenuFontColour.z,alpha),
				gFont2,true);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - Update_SpectateInfo
///*****************************************************************
void Game_Hud::Update_SpectateInfo(void)
{
	//-------------------------------------------------------------
	if(cGame_Camera.bSpectate)
	{
		iPrint((char*)"-Spectating-",cGame_Font.f14pt,&D3DXVECTOR2(0.0f,-8.5f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,true);
		iPrint((char*)"[ = Disable",cGame_Font.f14pt,&D3DXVECTOR2(0.0f,-9.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,true);
		iPrint((char*)"] = Next  ",cGame_Font.f14pt,&D3DXVECTOR2(0.0f,-9.5f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,true);
		///status
		if(cGame_RaceTracker.bBikeRacing[cGame_Camera.SpectateId])
		{
			iPrint((char*)"Racing",cGame_Font.f18pt,&D3DXVECTOR2(0.0f,-8.0f),&D3DXVECTOR4(0.0f,1.0f,0.0f,0.5f),gFont,true);
		}
		else
		{
			iPrint((char*)"Finished",cGame_Font.f18pt,&D3DXVECTOR2(0.0f,-8.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,0.5f),gFont,true);
		}

		if(cGame_Camera.SpectateId<=gNumberOfClients-1)//Networked Player
		{
			iPrint((char*)cGame_Bike[cGame_Camera.SpectateId].Name.c_str(),cGame_Font.f18pt,&D3DXVECTOR2(0.0f,-10.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,true);
		}
		else///Ai
		{
			sprintf_s(gCharBuffer,"Ai #%i",cGame_Camera.SpectateId);
			iPrint(gCharBuffer,cGame_Font.f18pt,&D3DXVECTOR2(0.0f,-10.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,true);
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - Update_LapTimers
///*****************************************************************
void Game_Hud::Update_LapTimers(void)
{
	//-------------------------------------------------------------
	//Lap Timers
	if(gLapsUpdate)
	{
		//TT
		if(gGameMode==0)
		{
			D3DXVECTOR2 vLocation = D3DXVECTOR2(-6.75f,9.0f);

			TimerReadOuts("Previous",cGame_RaceTracker.Time_PrevLap[cGame_Camera.SpectateId],vLocation);
			vLocation.x = -1.0f;

			TimerReadOuts("Current",cGame_RaceTracker.Time_CurrentLap[cGame_Camera.SpectateId],vLocation);
			vLocation.x = 5.0f;

			TimerReadOuts("Personal Best",cGame_RaceTracker.Time_FastLap[cGame_Camera.SpectateId],vLocation);
		}

		//New lap record, inform player
		if(cGame_RaceTracker.bTime_FastLap_New[cGame_Camera.SpectateId])
		{
			Timer_FastestLap = 300;
		}
		else if(Timer_FastestLap>0)
		{
			//Location
			D3DXVECTOR2 vLocation = D3DXVECTOR2(-1.0f,-11.0f);
			vLocation.y = iFloatInterpolate((float)Timer_FastestLap,60.0f,0.0f,-11.5f,-15.0f);
			TimerReadOuts("New Personal Best",cGame_RaceTracker.Time_FastLap[cGame_Camera.SpectateId],vLocation);
			Timer_FastestLap--;		
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - Update_Scoreboard
///*****************************************************************
void Game_Hud::Update_Scoreboard(void)
{
	//-------------------------------------------------------------
	//Activate
	if(cGame_Controls.Input_Action_ScoreBoard())
	{
		bScoreboard = !bScoreboard;
	}
	//-------------------------------------------------------------
	//Scoreboard Sprite
	iSpriteColorSet(Sprite_ScoreBoard,&D3DXVECTOR4(1.0f,1.0f,1.0f,0.13f));
	iSpriteScaleSet(Sprite_ScoreBoard,&D3DXVECTOR2(19.0f,9.0f * gScreenYScale));
	iSpriteHide(Sprite_ScoreBoard);
	//-------------------------------------------------------------
	//Display - process Scoreboard
	if(bScoreboard && !gMenu_Active)
	{
		int MAX_DISPLAY_SCOREBOARD = 10;
		if(gAi_Max_Count<10)
		{
			MAX_DISPLAY_SCOREBOARD = gAi_Max_Count + 1;
		}


		const float fStartHeight = 5.0f;
		const float fYspacer = -1.0f;
		///locations
		D3DXVECTOR2 vPosition = D3DXVECTOR2(-8.0f,fStartHeight);
		D3DXVECTOR2 vName = D3DXVECTOR2(-6.0f,fStartHeight);
		D3DXVECTOR2 vLaps = D3DXVECTOR2(-1.0f,fStartHeight);
		D3DXVECTOR2 vKills = D3DXVECTOR2(1.0f,fStartHeight);
		D3DXVECTOR2 vDeaths = D3DXVECTOR2(3.0f,fStartHeight);
		D3DXVECTOR2 vRacing = D3DXVECTOR2(5.0f,fStartHeight);

		D3DXVECTOR4 vPlayerColours = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);

		iSpriteShow(Sprite_ScoreBoard);
		//Print Top Info
		iPrint((char*)"Position",cGame_Font.f16pt,&vPosition,&gMenuFontColour,gFont,false);
		iPrint((char*)"Name",cGame_Font.f16pt,&vName,&gMenuFontColour,gFont,false);
		iPrint((char*)"Lap",cGame_Font.f16pt,&vLaps,&gMenuFontColour,gFont,false);
		iPrint((char*)"Kills",cGame_Font.f16pt,&vKills,&gMenuFontColour,gFont,false);
		iPrint((char*)"Deaths",cGame_Font.f16pt,&vDeaths,&gMenuFontColour,gFont,false);
		iPrint((char*)"Status",cGame_Font.f16pt,&vRacing,&gMenuFontColour,gFont,false);

		///Nudge down
		vPosition.y += fYspacer - 0.25f;
		vName.y += fYspacer - 0.25f;
		vLaps.y += fYspacer - 0.25f;
		vKills.y += fYspacer - 0.25f;
		vDeaths.y += fYspacer - 0.25f;
		vRacing.y += fYspacer - 0.25f;

		//Print Bottom Data
		int Bike_Id = 0;
		bool bPlayerDisplayed = false;

		for(int i=0;i<MAX_DISPLAY_SCOREBOARD;i++)
		{
			///Input data
			Bike_Id = cGame_RaceTracker.Position_OrderedId[i];
			///Check if player is displayed - if not, allocate last display to them.
			if(i==MAX_DISPLAY_SCOREBOARD-1 &&
				!bPlayerDisplayed)
			{
				Bike_Id = gAi_Max_Count;
			}
			else if(Bike_Id==gAi_Max_Count)
			{
				bPlayerDisplayed = true;
			}

			//Position
			iPrint((char*)cGame_Global_Text_Description.PositionReadout(cGame_RaceTracker.Position_Current[Bike_Id]).c_str(),cGame_Font.f16pt,&vPosition,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont2,false);

			//Obtain Player Colours
			vPlayerColours = D3DXVECTOR4(0.5f,0.5f,0.5f,1.0f);
			if(Bike_Id<gNumberOfClients || ///networked player
				Bike_Id==gAi_Max_Count) ///player
			{
				vPlayerColours.x = cGame_Bike[Bike_Id].Colour.vBikeColourTarget.x;
				vPlayerColours.y = cGame_Bike[Bike_Id].Colour.vBikeColourTarget.y;
				vPlayerColours.z = cGame_Bike[Bike_Id].Colour.vBikeColourTarget.z;
				vPlayerColours.w = 1.0f;
			}

			//PlayerNames
			iPrint((char*)cGame_Bike[Bike_Id].Name.c_str(),cGame_Font.f14pt,&vName,&vPlayerColours,gFont2,false);

			//Lap
			if(gLapsUpdate)
			{
				sprintf_s(gCharBuffer,"%d",cGame_RaceTracker.Lap_Current[Bike_Id]);
				iPrint(gCharBuffer,cGame_Font.f18pt,&vLaps,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont2,false);
			}

			//Kills - Deaths
			if(gWeaponsTrackEnable)
			{
				///k
				sprintf_s(gCharBuffer,"%d",cGame_Bike[Bike_Id].Weapons.TotalKills);
				iPrint(gCharBuffer,cGame_Font.f18pt,&vKills,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont2,false);
				///d
				sprintf_s(gCharBuffer,"%d",cGame_Bike[Bike_Id].Weapons.TotalDeaths);
				iPrint(gCharBuffer,cGame_Font.f18pt,&vDeaths,&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont2,false);
			}
			//Status
			if(gRaceState==0)
			{
				iPrint((char*)"------",cGame_Font.f16pt,&vRacing,&D3DXVECTOR4(0.0f,1.0f,1.0f,1.0f),gFont2,false);
			}
			else if(cGame_RaceTracker.bBikeRacing[Bike_Id])
			{
				iPrint((char*)"Racing",cGame_Font.f16pt,&vRacing,&D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f),gFont2,false);
			}
			else
			{
				iPrint((char*)"Finished",cGame_Font.f16pt,&vRacing,&D3DXVECTOR4(1.0f,0.7f,0.0f,1.0f),gFont2,false);
			}

			//Nudge down
			vPosition.y += fYspacer;
			vName.y += fYspacer;
			vLaps.y += fYspacer;
			vKills.y += fYspacer;
			vDeaths.y += fYspacer;
			vRacing.y += fYspacer;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - TimerReadOuts
///*****************************************************************
void Game_Hud::TimerReadOuts(char* name,float Seconds,D3DXVECTOR2 vLocation)
{
	//-------------------------------------------------------------
	const float SeperatorX = 0.6f;
	//-------------------------------------------------------------
	//Lap Timers
	int Minutes = 0;
	while(Seconds >= 60.0f)
	{
		Minutes++;
		Seconds -= 60.0f;
	}
	int Seconds_Out = (int)Seconds;
	float fMili_Out = (Seconds - (float)Seconds_Out) * 1000.0f;

	///print Info
	vLocation.x += 1.25f;
	iPrint3(name,cGame_Font.f16pt,&vLocation,&gMenuFontColour,gFont2,true);
	vLocation.y += 0.75f;
	vLocation.x -= 1.25f;
	///Print Minutes
	sprintf_s(gCharBuffer,"%d",Minutes);
	iPrint3(gCharBuffer,cGame_Font.f20pt,&vLocation,&gFontWhite,gFont2,true);
	vLocation.x += SeperatorX / 1.5f;
	///Print :
	iPrint3((char*)":",cGame_Font.f18pt,&vLocation,&gMenuFontColour,gFont2,true);
	vLocation.x += SeperatorX;
	///Print Seconds
	sprintf_s(gCharBuffer,"%d",Seconds_Out);
	iPrint3(gCharBuffer,cGame_Font.f20pt,&vLocation,&gFontWhite,gFont2,true);
	vLocation.x += SeperatorX;
	///Print .
	iPrint3((char*)".",cGame_Font.f16pt,&vLocation,&gMenuFontColour,gFont2,true);
	vLocation.x += SeperatorX;
	///Print Mili
	if(fMili_Out<10.0f)
	{
		sprintf_s(gCharBuffer,"00%0.0f",fMili_Out);
	}
	else if(fMili_Out<100.0f)
	{
		sprintf_s(gCharBuffer,"0%0.0f",fMili_Out);
	}
	else
	{
		sprintf_s(gCharBuffer,"%0.0f",fMili_Out);
	}
	iPrint3(gCharBuffer,cGame_Font.f16pt,&vLocation,&gFontGreyDark,gFont2,true);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - Update_NetworkPlayerNamesHover
///*****************************************************************
void Game_Hud::Update_NetworkPlayerNamesHover(void)
{
	//-------------------------------------------------------------
	if(gNumberOfClients>0)
	{
		D3DXVECTOR2 vLocation = D3DXVECTOR2(0.0f,0.0f);
		for(int i=0;i<gNumberOfClients;i++)
		{
			if(i3DLocationToScreen(&vLocation,&cGame_Bike[i].Manager.vBikeOutput,gCamera))
			{
				float fDistance = iVectorLength(&(cGame_Bike[i].Manager.vBikeOutput-cGame_Camera.vCamOutput));
				float fInter = iFloatInterpolate(fDistance,1.0f,300.0f,4.0f,0.0f);
				float fScale = iFloatInterpolate(fDistance,1.0f,300.0f,1.0f,0.1f);
				vLocation.y += fInter;
				D3DXVECTOR4 vColour = D3DXVECTOR4(cGame_Bike[i].Colour.vBikeColourTarget.x,cGame_Bike[i].Colour.vBikeColourTarget.y,cGame_Bike[i].Colour.vBikeColourTarget.z,1.0f);
				iPrint3((char*)cGame_Bike[i].Name.c_str(),cGame_Font.f18pt * fScale,&vLocation,&vColour,gFont2,false);
			}
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - HUD - ZERODATA
///*****************************************************************
void Game_Hud::ZeroData(void)
{
	//-------------------------------------------------------------
	//Hud Data
	bScoreboard = false;
	Sprite_Alpha = 0.0f;
	vSprite = D3DXVECTOR2(0.0f,0.0f);
	for(int i=0;i<4;i++)
	{
		fFontSize[i] = cGame_Font.f20pt;
		fFontSizeTarget = cGame_Font.f20pt;
	}
	//-------------------------------------------------------------
	//Targeting Data
	for(int i=0;i<2;i++)
	{
		SpriteTar_Scale[i] = 4.0f;
		vSpriteTar_Colour[i] = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
	}
	SpriteTar_Orientation = 0.0f;
	vSpriteTar = D3DXVECTOR2(0.0f,0.0f);
	TendToTrackingSprite = ((float)cGame_Upgrades.MissileLockTime[gAi_Max_Count] / 2.0f) ;
	//-------------------------------------------------------------
	//Kill Count Check
	KillCountCheck = 0;
	//-------------------------------------------------------------
	//Spectate Selector Data
	vTarget_Crosshair					= D3DXVECTOR2(0.0f,0.0f);
	vTarget_Colour						= D3DXVECTOR3(0.0f,0.0f,0.0f);
	Target_Speed						= 0.0f;
	Target_Energy						= 0.0f;
	Target_Position						= 0;

	Target_Kills						= 0;
	Target_Deaths						= 0;
	Target_Laps							= 0;

	Target_SecondaryCharging			= false;
	Target_SecondaryChargingTime		= 0;
	Target_SecondaryChargingTimeMax		= 1;
	Target_UtilityTime					= 0;
	Target_UtilityTimeMax				= 1;

	Target_PrimaryHeat					= 0;
	Target_SecondaryWeaponType			= -1;
	Target_UtilityType					= -1;
	//-------------------------------------------------------------
	//Killboard Data
	for(int i=0;i<4;i++)
	{
		Killboard_Msg[i] = "";
		Killboard_Timer[i] = 0;
		vKillboard_Colour[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
	//-------------------------------------------------------------
	//Fastest Lap
	Timer_FastestLap					= 0;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - HUD - DESTROY
///*****************************************************************
void Game_Hud::Destroy(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//Hud
	iSpriteImpostersDestroy(Sprite);
	iSpriteDestroy(Sprite);
	///Utility
	iSpriteDestroy(Sprite_Utility_0);
	iSpriteDestroy(Sprite_Utility_1);
	///Sprite_Secondary_1
	iSpriteDestroy(Sprite_Secondary_0);
	iSpriteDestroy(Sprite_Secondary_1);
	//Weapon Icon Sprites
	for(int i=0;i<4;i++)
	{
		iSpriteDestroy(Sprite_Utility_Icon[i]);
		iSpriteDestroy(Sprite_Secondary_Icon[i]);
	}
	//-------------------------------------------------------------
	//PlayerCrosshair
	iSpriteDestroy(SpriteCrossHair);
	//-------------------------------------------------------------
	//Targeting
	for(int i=0;i<2;i++)
	{
		iSpriteDestroy(SpriteTar[i]);
	}
	//-------------------------------------------------------------
	//Scoreboard
	iSpriteDestroy(Sprite_ScoreBoard);
	//-------------------------------------------------------------
}