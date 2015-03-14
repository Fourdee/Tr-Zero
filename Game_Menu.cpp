//-----------------------------------------------------------------
// Game_Menu Class
//
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Menu.h"
//-----------------------------------------------------------------
///*****************************************************************
//MENU SYSTEM - CONSTRUCTORS
///*****************************************************************
Game_Menu::Game_Menu(void)
{
	//-------------------------------------------------------------
	///Sprite_TextMain
	Sprite_TextMain = NULL;
	Sprite_TextSetting = NULL;
	Sprite_TextSlider = NULL;
	Sprite_TopBanner = NULL;
	for(int i=0;i<4;i++)
	{
		Sprite_Upgrades[i] = NULL;
	}
	Sprite_Upgrades_Bottom = NULL;
	//Sprite_Controls
	Sprite_Controls_Xbox = NULL;
	Sprite_Controls_Keyboard = NULL;
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
Game_Menu::~Game_Menu(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//MENU SYSTEM - ZERODATA
///*****************************************************************
void Game_Menu::ZeroData(void)
{
	//-------------------------------------------------------------
	//Mouse
	fMouseValue = 0.0f;
	//slider
	fSliderOffsetMax = 2.0f;
	//SETTINGS - CONST
	vMainTarget									= D3DXVECTOR2(-13.0f,7.0f);
	Font_MenuHeightGap							= 2.0f;
	//-------------------------------------------------------------
	for(int i=0;i<10;i++)
	{
		//Main Font - Settings
		Font_MenuColour[i] = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
		Font_MenuLocation[i] = D3DXVECTOR2(0.0f,0.0f);
		Text_Main[i] = "";
		Font_MenuSize[i] = cGame_Font.f20pt;
		//Settings Font - Settings
		Text_Setting[i] = "";
		Font_SettingColour[i] = D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
		Font_SettingSize[i] = cGame_Font.f20pt;
		SettingType[i] = 0;
		SettingOffset[i] = 0.0f;
		vSprite_TextMainColour[i] = D3DXVECTOR4(0.1f,0.1f,0.1f,1.0f);
	}
	//Header - Settings
	Text_Header									= "";
	Font_HeaderColour							= D3DXVECTOR4(1.0f,1.0f,1.0f,0.0f);
	Font_HeaderLocation							= D3DXVECTOR2(-12.0f,10.0f);
	//Menu Timers - Data
	TimerExit									= 0;
	TimerDelay									= 0;
	//Menu States
	bInitMenu									= true;
	bTextReady									= false;
	bPlayAnimationOut 							= false;
	bPlayAnimationIn 							= true;
	//Text Lock input
	gTextInputLock								= false;
	//Max Menu Sub
	MenuSub_Max									= 1;
	//-------------------------------------------------------------
}
///*****************************************************************
///MENU SYSTEM - Update Controls
///*****************************************************************
void Game_Menu::Update_Controls(void)
{
	//-------------------------------------------------------------
	//Controller up/down
	if(cGame_Controls.Input_Menu_Action_Up())
	{
		cGame_Audio.Menu.MenuFx(0);
		gMenuSubId--;
	}
	else if(cGame_Controls.Input_Menu_Action_Down())
	{
		cGame_Audio.Menu.MenuFx(5);
		gMenuSubId++;
	}
	else if(gMouseEnabled)
	{
		D3DXVECTOR2 vMouse;
		MousePositionGet(&vMouse);
		if(gMousePosition_Current != vMouse)
		{
			for(int i=0;i<10;i++)
			{
				//-------------------------------------------
				//Mouse up/down
				//Mouse activation vector limits
				float left = Font_MenuLocation[i].x - 2.0f;
				float right = Font_MenuLocation[i].x + 12.0f;
				float upper = Font_MenuLocation[i].y + 0.95f;
				float lower = Font_MenuLocation[i].y - 0.95f;
				///Upgrade special menu
				if(gMenuId==7)
				{
					right = -9.5f;
				}
				///Global
				if((vMouse.y < upper && vMouse.y > lower) 
					&&(vMouse.x < right && vMouse.x > left)
					)
				{	
					if(!iMouseButtonDown(VK_LBUTTON) && (gMenuSubId != i && Text_Main[i] != ""))
					{
						//play sound
						if(i<=gMenuSubId){cGame_Audio.Menu.MenuFx(0);}
						else{cGame_Audio.Menu.MenuFx(5);}
						gMenuSubId = i;						
					}
				}
				//-------------------------------------------
			}
			gMousePosition_Current = vMouse;
		}
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//MENU SYSTEM - Init Menu
///*****************************************************************
void Game_Menu::InitMenu(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//Reset the setup flag
	bPlayAnimationIn = true;
	bTextReady = false;
	bInitMenu = false;
	//---------------------------------------------------------
	//Enable Mouse
	MouseActive(true);
	//play intro sound
	cGame_Audio.Menu.MenuFx(1);
	//-------------------------------------------------------------
}
///*****************************************************************
///MENU SYSTEM - Exit Menu
///*****************************************************************
void Game_Menu::Exit(void)
{
	//-------------------------------------------------------------
	//Exit Menu,
	if(TimerExit >= 7)
	{
		//---------------------------------------------------------
		//MODE 1: start game + exit fade
		if(gGameState != gGameStateChange || gExitWin || gResetLevel)
		{
			cGame_Gamma_Fade.bFadeOut = true;
		}
		//---------------------------------------------------------
		//MODE 2: Reset Pause
		else if((gPaused && TimerExit >= 55))
		{
			gBikesGo = true;
			gPaused = false;
		}
		TimerExit++;
	}
	//-------------------------------------------------------------
	else
	{
		//Prep text for exit
		for(int i=0;i<10;i++)
		{
			//Exit Locations
			if(i==gMenuSubId)
			{	
				iFloatTendTo2(Font_MenuLocation[i].x,vMainTarget.x,20.0f);
				//iFloatTendTo2(Font_MenuLocation[i].y,10.0f,10.0f);
				iFloatTendTo2(Font_MenuColour[i].w,1.0f,20.0f);
			}
			else
			{
				iFloatTendTo2(Font_MenuLocation[i].x,0.0f,20.0f + (float)i);
				iFloatTendTo2(Font_MenuLocation[i].y,0.0f,10.0f + (float)i);
				iFloatTendTo2(Font_MenuColour[i].w,0.0f,10.0f + (float)i);
			}
			iPrint((char*)Text_Main[i].c_str(),Font_MenuSize[i],&Font_MenuLocation[i],&Font_MenuColour[i],gFont,false);
		}
		//Header
		iFloatTendTo2(Font_HeaderColour.w,0.0f,15.0f);
		iPrint((char*)Text_Header.c_str(),cGame_Font.f30pt,&Font_HeaderLocation,&Font_HeaderColour,gFont,true);
		//---------------------------------------------------------
		//Disable Mouse
		MouseActive(false);
		//-------------------------------------------------------------
		TimerExit++;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///MENU SYSTEM - Text Animation Out
///*****************************************************************
void Game_Menu::TextAnimationOut(void)
{
	//-------------------------------------------------------------
	bTextReady = false;

	if(TimerDelay>=30)
	{
		TimerDelay = 0;
		bPlayAnimationOut = false;
		bPlayAnimationIn = true;
	}
	else
	{
		for(int i=0;i<10;i++)
		{
			iFloatTendTo2(Font_MenuLocation[i].x,0.0f,20.0f + (float)i);
			iFloatTendTo2(Font_MenuLocation[i].y,0.0f,10.0f + (float)i);
			iFloatTendTo2(Font_MenuColour[i].w,0.0f,8.0f + (float)i);
			iFloatTendTo2(Font_MenuSize[i],12.0f,25.0f);

			iFloatTendTo2(Font_SettingColour[i].w,0.0f,8.0f + (float)i);
			SettingType[i] = 0;
			SettingOffset[i] = 0.0f;
		}
		//Header Text
		iFloatTendTo2(Font_HeaderColour.w,0.0f,15.0f);
		TimerDelay++;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///MENU SYSTEM - Text Animation In
///*****************************************************************
void Game_Menu::TextAnimationIn(void)
{
	//-------------------------------------------------------------
	if(TimerDelay>=30)
	{
		bTextReady = true;
		TimerDelay = 0;
		bPlayAnimationIn = false;
	}
	else
	{
		for(int i=0;i<10;i++)
		{	
			//Set Locations
			iFloatTendTo2(Font_MenuLocation[i].x,vMainTarget.x,20.0f + (float)i);
			if(i==MenuSub_Max)///Last Menu Option (Move to bottom)
			{
				iFloatTendTo2(Font_MenuLocation[i].y,(vMainTarget.y - 1.0f) - ((float)i * Font_MenuHeightGap),10.0f + (float)i);
			}
			else
			{
				iFloatTendTo2(Font_MenuLocation[i].y,vMainTarget.y - ((float)i * Font_MenuHeightGap),10.0f + (float)i);
			}
			iFloatTendTo2(Font_MenuColour[i].w,1.0f,15.0f + (float)i);
			iFloatTendTo2(Font_MenuSize[i],cGame_Font.f20pt,25.0f);

			iFloatTendTo2(Font_SettingColour[i].w,1.0f,8.0f + (float)i);
			Text_Setting[i] = "";
			SettingType[i] = 0;
			SettingOffset[i] = 0.0f;
	}
		//Header Text
		iFloatTendTo2(Font_HeaderColour.w,1.0f,15.0f);
		TimerDelay++;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///MENU SYSTEM - Text Animations Finish
///*****************************************************************
void Game_Menu::TextAnimationFinish(void)
{
	//-------------------------------------------------------------
	//Finish off any text attributes
	for(int i=0;i<10;i++)
	{	
		//Set Locations
		iFloatTendTo2(Font_MenuLocation[i].x,vMainTarget.x,20.0f + (float)i);
		if(i==MenuSub_Max)///Last Menu Option (Move to bottom)
		{
			iFloatTendTo2(Font_MenuLocation[i].y,(vMainTarget.y - 1.0f) - ((float)i * Font_MenuHeightGap),10.0f + (float)i);
		}
		else
		{
			iFloatTendTo2(Font_MenuLocation[i].y,vMainTarget.y - ((float)i * Font_MenuHeightGap),10.0f + (float)i);
		}
		iFloatTendTo2(Font_MenuColour[i].w,1.0f,15.0f + (float)i);
		iFloatTendTo2(Font_SettingColour[i].w,1.0f,8.0f + (float)i);
	}
	//Header Text
	iFloatTendTo2(Font_HeaderColour.w,1.0f,15.0f);
	//-------------------------------------------------------------
}
///*****************************************************************
///MENU SYSTEM - Print Text
///*****************************************************************
void Game_Menu::PrintText(void)
{
	//-------------------------------------------------------------
	//Menu
	for(int i=0;i<10;i++)
	{
		//Highlight selected
		if(i==gMenuSubId)
		{
			iFloatTendTo2(Font_MenuSize[i],cGame_Font.f20pt + (4.0f * gFontScale),5.0f);
			iVector4TendTo(&vSprite_TextMainColour[i],&gMenuFontColour,5.0f);
			Font_MenuColour[i].x = Font_MenuColour[i].y = Font_MenuColour[i].z = 0.0f;
		}
		else
		{
			iFloatTendTo2(Font_MenuSize[i],cGame_Font.f20pt - (2.0f * gFontScale),5.0f);
			iVector4TendTo(&vSprite_TextMainColour[i],&D3DXVECTOR4(0.2f,0.2f,0.2f,1.0f),5.0f);
			Font_MenuColour[i].x = Font_MenuColour[i].y = Font_MenuColour[i].z = 1.0f;
		}

		//Print
		iPrint((char*)Text_Main[i].c_str(),Font_MenuSize[i],&Font_MenuLocation[i],&Font_MenuColour[i],gFont,false);
		//Text Setting
		Font_SettingSize[i] = cGame_Font.f18pt;
		D3DXVECTOR2 offset = Font_MenuLocation[i];
		offset.y = Font_MenuLocation[i].y + 0.5f;
		offset.x = Font_MenuLocation[i].x + 5.0f;
		iPrint((char*)Text_Setting[i].c_str(),Font_SettingSize[i],&offset,&Font_MenuColour[i],gFont,false);
		//slider
		if(SettingType[i]==1)
		{
			D3DXVECTOR2 offsetslider = Font_MenuLocation[i];
			offsetslider.y = Font_MenuLocation[i].y - 0.5f;
			offsetslider.x = offset.x + SettingOffset[i];
			iPrint3((char*)"<>",Font_SettingSize[i],&offsetslider,&Font_SettingColour[i],gFont,false);
		}
	}
	//Header
	iPrint((char*)Text_Header.c_str(),cGame_Font.f30pt,&Font_HeaderLocation,&Font_HeaderColour,gFont,true);
	//-------------------------------------------------------------
	//SPRITES
	for(int i=0;i<9;i++)
	{
		//Sprite_TextMain
		if(Text_Main[i]!="")
		{
			iSpriteImposterScaleSet(Sprite_TextMain,i,&D3DXVECTOR2(7.0f,2.0f * gScreenYScale));
			D3DXVECTOR2 vTextMainOffset = D3DXVECTOR2(vMainTarget.x + 1.5f,Font_MenuLocation[i].y + 0.3f);
			iSpriteImposterLocationSet(Sprite_TextMain,i,&vTextMainOffset);
			iSpriteImposterColorSet(Sprite_TextMain,i,&vSprite_TextMainColour[i]);
			iSpriteImposterShow(Sprite_TextMain,i);
		}
		//Sprite_TextSetting
		if(Text_Setting[i]!="")
		{
			iSpriteImposterScaleSet(Sprite_TextSetting,i,&D3DXVECTOR2(7.0f,2.0f * gScreenYScale));
			D3DXVECTOR2 vTextSettingOffset = Font_MenuLocation[i] + D3DXVECTOR2(7.0f,0.3f);
			iSpriteImposterLocationSet(Sprite_TextSetting,i,&vTextSettingOffset);
			iSpriteImposterColorSet(Sprite_TextSetting,i,&vSprite_TextMainColour[i]);
			iSpriteImposterShow(Sprite_TextSetting,i);
		}
		//Sprite_TextSlider
		if(SettingType[i]==1)
		{
			iSpriteImposterScaleSet(Sprite_TextSlider,i,&D3DXVECTOR2(7.0f,2.0f * gScreenYScale));
			D3DXVECTOR2 vTextSliderOffset = Font_MenuLocation[i] + D3DXVECTOR2(7.0f,0.3f);
			iSpriteImposterLocationSet(Sprite_TextSlider,i,&vTextSliderOffset);
			iSpriteImposterColorSet(Sprite_TextSlider,i,&vSprite_TextMainColour[i]);
			iSpriteImposterShow(Sprite_TextSlider,i);
		}
	}
	//Sprite_TopBanner
	iSpriteScaleSet(Sprite_TopBanner,&D3DXVECTOR2(32.0f,5.0f * gScreenYScale));
	iSpriteLocationSet(Sprite_TopBanner,&D3DXVECTOR2(0.0f,9.0f));
	D3DXVECTOR4 vSprite_TopBannerColour = gMenuFontColour;
	iSpriteColorSet(Sprite_TopBanner,&vSprite_TopBannerColour);
	iSpriteShow(Sprite_TopBanner);
	//Upgrade sprites
	if(gMenuId==7)///Only needs to update in upgrade menu. Save cycles
	{
		for(int i=0;i<MAX_UPGRADE_SPRITES;i++)
		{
			//Sprite_Upgrades
			D3DXVECTOR2 vUpgradeOffset = Font_MenuLocation[i] + D3DXVECTOR2(11.0f,0.3f);
			for(int j=0;j<4;j++)
			{
				iSpriteImposterScaleSet(Sprite_Upgrades[j],i,&D3DXVECTOR2(14.0f,2.0f * gScreenYScale));
				iSpriteImposterLocationSet(Sprite_Upgrades[j],i,&vUpgradeOffset);
				iSpriteImposterColorSet(Sprite_Upgrades[j],i,&gMenuFontColour);
			}
			//Sprite_Upgrades_Bottom
			iSpriteImposterScaleSet(Sprite_Upgrades_Bottom,i,&D3DXVECTOR2(14.0f,2.0f * gScreenYScale));
			iSpriteImposterLocationSet(Sprite_Upgrades_Bottom,i,&vUpgradeOffset);
		}
	}
	//-------------------------------------------------------------
	//Print Banner Info
	float BannerInfoFontSize = cGame_Font.f14pt;
	float BannerSeperatorFontSize = cGame_Font.f14pt;
	D3DXVECTOR4 vWhite = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	D3DXVECTOR4 vGrey = D3DXVECTOR4(0.5f,0.5f,0.5f,0.5f);
	D3DXVECTOR2 vBannerInfo = D3DXVECTOR2(-8.0f,11.4f);
	char BannerMSG[256];
	///-------
	iPrint((char*)"Name:",BannerInfoFontSize,&vBannerInfo,&vGrey,gFont,false);
	vBannerInfo.y -= 0.5f;
	iPrint(gPlayerName,BannerInfoFontSize,&vBannerInfo,&vWhite,gFont,false);
	vBannerInfo.y += 0.25f;
	vBannerInfo.x += 2.5f;
	iPrint((char*)"|",BannerSeperatorFontSize,&vBannerInfo,&gMenuFontColour,gFont,false);
	vBannerInfo.y = 11.4f;
	vBannerInfo.x += 0.5f;
	///-------
	iPrint((char*)"Level:",BannerInfoFontSize,&vBannerInfo,&vGrey,gFont,false);
	vBannerInfo.y -= 0.5f;
	sprintf_s(BannerMSG," %i",cGame_PlayerStats.Player_Level);
	iPrint(BannerMSG,BannerInfoFontSize,&vBannerInfo,&vWhite,gFont,false);
	vBannerInfo.y += 0.25f;
	vBannerInfo.x += 1.0f;
	iPrint((char*)"|",BannerSeperatorFontSize,&vBannerInfo,&gMenuFontColour,gFont,false);
	vBannerInfo.y = 11.4f;
	vBannerInfo.x += 0.5f;
	///-------
	iPrint((char*)"XP / Required:",BannerInfoFontSize,&vBannerInfo,&vGrey,gFont,false);
	vBannerInfo.y -= 0.5f;
	sprintf_s(BannerMSG,"%i / %i",cGame_PlayerStats.Player_XP,cGame_PlayerStats.XP_Required_Next_Level);
	iPrint(BannerMSG,BannerInfoFontSize,&vBannerInfo,&vWhite,gFont,false);
	vBannerInfo.y += 0.25f;
	vBannerInfo.x += 2.5f;
	iPrint((char*)"|",BannerSeperatorFontSize,&vBannerInfo,&gMenuFontColour,gFont,false);
	vBannerInfo.y = 11.4f;
	vBannerInfo.x += 0.5f;
	///-------
	iPrint((char*)"Points:",BannerInfoFontSize,&vBannerInfo,&vGrey,gFont,false);
	vBannerInfo.y -= 0.5f;
	sprintf_s(BannerMSG," %i",cGame_PlayerStats.Upgrade_Points_Remaining);
	iPrint(BannerMSG,BannerInfoFontSize,&vBannerInfo,&vWhite,gFont,false);
	vBannerInfo.y += 0.25f;
	vBannerInfo.x += 2.5f;
	iPrint((char*)"|",BannerSeperatorFontSize,&vBannerInfo,&gMenuFontColour,gFont,false);
	vBannerInfo.y = 11.4f;
	vBannerInfo.x += 0.5f;
	///-------
	iPrint((char*)"Master Server:",BannerInfoFontSize,&vBannerInfo,&vGrey,gFont,false);
	vBannerInfo.y -= 0.5f;
	if(gMasterServerOnline)
	{
		iPrint((char*)"Connected",BannerInfoFontSize,&vBannerInfo,&D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f),gFont,false);
	}
	else
	{
		iPrint((char*)"Failed",BannerInfoFontSize,&vBannerInfo,&D3DXVECTOR4(1.0f,0.3f,0.0f,1.0f),gFont,false);
	}
	vBannerInfo.y += 0.25f;
	vBannerInfo.x += 2.5f;
	iPrint((char*)"|",BannerSeperatorFontSize,&vBannerInfo,&gMenuFontColour,gFont,false);
	vBannerInfo.y = 11.4f;
	vBannerInfo.x += 0.5f;
	//Print MOTD
	iPrint3((char*)gMasterServerMOTD.c_str(),cGame_Font.f18pt,&D3DXVECTOR2(-8.0f,10.0f),&gFontWhite,gFont,false);
	
	//-------------------------------------------------------------
}
///*****************************************************************
///MENU SYSTEM - HideSprites
///*****************************************************************
void Game_Menu::HideSprites(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<9;i++)
	{
		//Sprite_TextMain
		iSpriteImposterHide(Sprite_TextMain,i);
		//Sprite_TextSetting
		iSpriteImposterHide(Sprite_TextSetting,i);
		//Sprite_TextSlider
		iSpriteImposterHide(Sprite_TextSlider,i);
	}
	//-------------------------------------------------------------
	//Sprite_Upgrade parts
	for(int i=0;i<MAX_UPGRADE_SPRITES;i++)
	{
		iSpriteImposterHide(Sprite_Upgrades_Bottom,i);
		for(int j=0;j<4;j++)
		{
			iSpriteImposterHide(Sprite_Upgrades[j],i);
		}
	}
	//-------------------------------------------------------------
	//Sprite_TopBanner
	iSpriteHide(Sprite_TopBanner);
	//-------------------------------------------------------------
	//Sprite_Controls_Xbox
	iSpriteHide(Sprite_Controls_Xbox);
	//-------------------------------------------------------------
	//Sprite_Controls_Keyboard
	iSpriteHide(Sprite_Controls_Keyboard);
	//-------------------------------------------------------------
}
///*****************************************************************
//MENU SYSTEM - UPDATE
///*****************************************************************
void Game_Menu::Update(void)
{
	//-------------------------------------------------------------
	//Hide all sprites each update loop
	HideSprites();
	//-------------------------------------------------------------
	if(gMenu_Active)
	{
		//Update Text Descriptions
		cGame_Global_Text_Description.Update();

		if(bInitMenu)
		{
			//Setup Menu before entering menu system
			InitMenu();
		}
		else if(bPlayAnimationIn)
		{
			TextAnimationIn();
		}
		else if(bPlayAnimationOut)
		{
			TextAnimationOut();
		}
		else if(bTextReady)
		{
			TextAnimationFinish();
		}

		//Update Sprites and Text
		if(!gDisable2D)
		{
			PrintText();
		}

		//Update Controls
		if(bTextReady && !gTextInputLock && gGfxOptimiserState!=1)
		{
			Update_Controls();
		}

		if(gMenuId==0) //Pause Menu
		{
			Menu_000();
			cGame_Camera.Mode_Menu = 0;
		}
		else if(gMenuId==1) //Settings
		{
			if(gGameState==0)
			{
				gBikesGo = true;
			}
			Menu_001();
			cGame_Camera.Mode_Menu = 0;
		}
		else if(gMenuId==2) //Main Menu
		{
			Menu_002();
			cGame_Camera.Mode_Menu = 0;
		}
		else if(gMenuId==3) //Video
		{
			Menu_003();
			cGame_Camera.Mode_Menu = 1;
			if(!iNetworkIsActive())
			{
				gBikesGo = false;
			}
			cGame_Camera.Timer_Mode = 2;
		}
		else if(gMenuId==4) //Audio
		{
			Menu_004();
			cGame_Camera.Mode_Menu = 0;
		}
		else if(gMenuId==5) //Ai Options
		{
			Menu_005();
			cGame_Camera.Mode_Menu = 0;
		}
		else if(gMenuId==6) //Game Select Screen
		{
			Menu_006();
			cGame_Camera.Mode_Menu = 0;
		}
		else if(gMenuId==7) // Upgrades
		{
			Menu_007();
			cGame_Camera.Mode_Menu = 2;
		}
		else if(gMenuId==8) // Personalise
		{
			if(gFirstRun)
			{
				gBikesGo = true;
			}
			cGame_Camera.Mode_Menu = 1;
			Menu_008();
		}
		else if(gMenuId==9) // Control Settings
		{
			Menu_009();
			cGame_Camera.Mode_Menu = 0;
		}
		else if(gMenuId==10) // Carrear Mode
		{
			Menu_010();
			cGame_Camera.Mode_Menu = 0;
		}
		else if(gMenuId==11) // Network Mode
		{
			gBikesGo = true;
			Menu_011();
			cGame_Camera.Mode_Menu = 0;
		}
		else if(gMenuId==12) // Network Host
		{
			gBikesGo = false;
			Menu_012();
			cGame_Camera.Mode_Menu = 4;
		}
		else if(gMenuId==13) // Network Client
		{
			gBikesGo = false;
			Menu_013();
			cGame_Camera.Mode_Menu = 4;
		}
		else if(gMenuId==14) //FEEDBACK
		{
			Menu_014();
			cGame_Camera.Mode_Menu = 0;
		}
		else if(gMenuId==15) //WORLD STATS
		{
			Menu_015();
			cGame_Camera.Mode_Menu = 0;
		}
	}
	else
	{
		Exit();
	}
	//-------------------------------------------------------------
	//Pause exit Reset
	if(!gPaused && !bInitMenu && gGameState > 0)
	{
		//Close menu, stop processing, reset menu catogories
		bInitMenu = true;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//MENU SYSTEM - CREATE
///*****************************************************************
void Game_Menu::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	//Sprite_Controls_Xbox
	Sprite_Controls_Xbox = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Controls_Xbox,gCamera);
	iSpriteScaleSet(Sprite_Controls_Xbox,&D3DXVECTOR2(32.0f,18.0f * gScreenYScale));
	iSpriteHide(Sprite_Controls_Xbox);
	//Sprite_Controls_Keyboard
	Sprite_Controls_Keyboard = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.Controls_Keyboard,gCamera);
	iSpriteScaleSet(Sprite_Controls_Keyboard,&D3DXVECTOR2(32.0f,18.0f * gScreenYScale));
	iSpriteHide(Sprite_Controls_Keyboard);
	//-------------------------------------------------------------
	//Sprite_TextMain
	Sprite_TextMain = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.BG_TextMain,gCamera);
	iSpriteScaleSet(Sprite_TextMain,&D3DXVECTOR2(7.0f,2.0f * gScreenYScale));
	iSpriteImpostersCreate(Sprite_TextMain,9);
	//Sprite_TextSetting
	Sprite_TextSetting = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.BG_TextSetting,gCamera);
	iSpriteScaleSet(Sprite_TextSetting,&D3DXVECTOR2(7.0f,2.0f * gScreenYScale));
	iSpriteImpostersCreate(Sprite_TextSetting,9);
	//Sprite_TextSlider
	Sprite_TextSlider = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.BG_TextSlider,gCamera);
	iSpriteScaleSet(Sprite_TextSlider,&D3DXVECTOR2(7.0f,2.0f * gScreenYScale));
	iSpriteImpostersCreate(Sprite_TextSlider,9);
	//Sprite_TopBanner
	Sprite_TopBanner = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.BG_TopBanner,gCamera);
	iSpriteScaleSet(Sprite_TopBanner,&D3DXVECTOR2(32.0f,5.0f * gScreenYScale));
	//-------------------------------------------------------------
	//Sprite_Upgrades
	for(int i=0;i<4;i++)
	{
		Sprite_Upgrades[i] = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.BG_Upgrades[i],gCamera);
		iSpriteScaleSet(Sprite_Upgrades[i],&D3DXVECTOR2(14.0f,2.0f * gScreenYScale));
		iSpriteImpostersCreate(Sprite_Upgrades[i],MAX_UPGRADE_SPRITES);
	}
	//Sprite_Upgrades_Bottom
	Sprite_Upgrades_Bottom = iSpriteCreate(cGame_Asset_Global_Texture.Menu_Main.BG_Upgrades_Bottom,gCamera);
	iSpriteScaleSet(Sprite_Upgrades_Bottom,&D3DXVECTOR2(14.0f,2.0f * gScreenYScale));
	iSpriteImpostersCreate(Sprite_Upgrades_Bottom,MAX_UPGRADE_SPRITES);
	//-------------------------------------------------------------
}
///*****************************************************************
//MENU SYSTEM - DESTROY
///*****************************************************************
void Game_Menu::Destroy(void)
{
	//-------------------------------------------------------------
	//Sprite_Controls_Xbox
	iSpriteDestroy(Sprite_Controls_Xbox);
	//Sprite_Controls_Keyboard
	iSpriteDestroy(Sprite_Controls_Keyboard);
	//Sprite_TextMain
	iSpriteImpostersDestroy(Sprite_TextMain);
	iSpriteDestroy(Sprite_TextMain);
	//Sprite_TextSetting
	iSpriteImpostersDestroy(Sprite_TextSetting);
	iSpriteDestroy(Sprite_TextSetting);
	//Sprite_TextSlider
	iSpriteImpostersDestroy(Sprite_TextSlider);
	iSpriteDestroy(Sprite_TextSlider);
	//Sprite_TopBanner
	iSpriteDestroy(Sprite_TopBanner);
	//-------------------------------------------------------------
	//Sprite_Upgrades
	for(int i=0;i<4;i++)
	{
		iSpriteImpostersDestroy(Sprite_Upgrades[i]);
		iSpriteDestroy(Sprite_Upgrades[i]);
	}
	//Sprite_Upgrades_Bottom
	iSpriteImpostersDestroy(Sprite_Upgrades_Bottom);
	iSpriteDestroy(Sprite_Upgrades_Bottom);
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
//******************************************************************
///PAUSE MENU
//******************************************************************
void Game_Menu::Menu_000(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Paused";
		Text_Main[0] = "Resume";
		Text_Main[1] = "Settings";
		Text_Main[2] = "Restart";
		Text_Main[3] = "Exit to Menu";
		Text_Main[4] = "";
		Text_Main[5] = "";
		Text_Main[6] = "";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		for(int i=0;i<10;i++)
		{
			//Settings Font - Settings
			Text_Setting[i] = "";
		}
		//Target Submenu
		gMenuSubId = 0;
	}
	
	//-------------------------------------------------------------
	MenuSub_Max = 3;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			gMenu_Active = false;
		}
	}
	else if(gMenuSubId==1)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 1;
		}
	}
	else if(gMenuSubId==2)
	{
		if(cGame_Controls.Input_Menu_Action_Select() && cGame_Network.Client.State==0)
		{
			if(cGame_Network.Server.State==2)//Restart level + keep server running
			{
				gServerState = -1;
			}
			cGame_Audio.Music.MusicStop();
			cGame_Audio.Menu.MenuFx(3);
			gResetLevel = true;
			gMenu_Active = false;
		}
	}
	else if(gMenuSubId==3)
	{
		//if(cGame_Controls.Input_Menu_Action_Select())
		//{
		//	//End Race - Apply exit loss
		//	gRaceState = 2;
		//	if(gGameMode!=0)///TT
		//	{
		//		gRaceWin = false;
		//	}
		//	gMenu_Active = false;
		//}
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			if(cGame_Network.Server.State==2)//Return Server to Menu with clients
			{
				gServerState = -1;
			}
			if(cGame_Network.Client.State==2)//Disconnect Client
			{
				cGame_Network.Client.State = -1;
			}
			gGameStateChange = 0;
			cGame_Audio.Music.MusicStop();
			cGame_Audio.Menu.MenuFx(3);
			gMenu_Active = false;
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///SETTINGS
//******************************************************************
void Game_Menu::Menu_001(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Settings";
		Text_Main[0] = "Video";
		Text_Main[1] = "Audio";
		Text_Main[2] = "Ai Options";
		Text_Main[3] = "Personalise";
		Text_Main[4] = "Controls";
		Text_Main[5] = "Back";
		Text_Main[6] = "";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		for(int i=0;i<10;i++)
		{
			//Settings Font - Settings
			Text_Setting[i] = "";
		}
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		if(cGame_Controls.Input_Menu_Action_Back())
		{
			bPlayAnimationOut = true;
			//Target Menu
			if(gPaused)
			{
				gMenuId = 0;
			}
			else
			{
				gMenuId = 2;
			}
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 5;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 3;
		}
	}
	else if(gMenuSubId==1)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 4;
		}
	}
	else if(gMenuSubId==2)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 5;
		}
	}
	else if(gMenuSubId==3)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 8;
		}
	}
	else if(gMenuSubId==4)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 9;
		}
	}
	else if(gMenuSubId==5)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			if(gPaused)
			{
				gMenuId = 0;
			}
			else
			{
				gMenuId = 2;
			}
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///MAIN MENU
//******************************************************************
void Game_Menu::Menu_002(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Tr-Zero";
		Text_Main[0] = "Upgrades";
		Text_Main[1] = "Single Player";
		Text_Main[2] = "Multi Player";
		Text_Main[3] = "Settings";
		Text_Main[4] = "Statistics";
		Text_Main[5] = "Exit Tr-Zero";
		Text_Main[6] = "";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";

		Text_Setting[0] = ""; 	
		Text_Setting[1] = "";	
		Text_Setting[2] = "";
		Text_Setting[3] = "";
		Text_Setting[4] = "";
		Text_Setting[5] = "";
		Text_Setting[6] = "";
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";
		//Target Submenu
		gMenuSubId = 0;
		gBikesGo = true;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		Text_Main[2] = "Multi Player";
		Text_Setting[2] = "";
		if(cGame_Optimiser.bOptimiseBypass)
		{
			Text_Main[2] = "Multi Player";
			Text_Setting[2] = "Off (GFX bypass)";
		}
	}

	MenuSub_Max = 5;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 7;
		}
	}
	else if(gMenuSubId==1)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 6;
		}
	}
	else if(gMenuSubId==2)
	{
		if(cGame_Controls.Input_Menu_Action_Select() && 
			!cGame_Optimiser.bOptimiseBypass)///Dont allow optimiser bypass users to fk up network games
		{
			bPlayAnimationOut = true;
			gMenuId = 11;
		}
	}
	else if(gMenuSubId==3)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 1;
		}
	}
	else if(gMenuSubId==4)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 10;
		}
	}
	//else if(gMenuSubId==5)
	//{
	//	if(cGame_Controls.Input_Menu_Action_Select())
	//	{
	//		bPlayAnimationOut = true;
	//		gMenuId = 14;
	//	}
	//}
	else if(gMenuSubId==5)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			gExitWin = true;
			cGame_Audio.Music.MusicStop();
			cGame_Audio.Menu.MenuFx(3);
			gMenu_Active = false;
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///VIDEO SETTINGS
//******************************************************************
void Game_Menu::Menu_003(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Video";
		Text_Main[0] = "Resolution";
		Text_Main[1] = "Gamma";
		Text_Main[2] = "AF";
		Text_Main[3] = "FXAA";
		Text_Main[4] = "Depth Of Field";
		Text_Main[5] = "Motion Blur";
		Text_Main[6] = "Glow";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		Text_Main[7] = "";
		if(gGfxOptimiserState!=1)
		{
			Text_Main[7] = "Force Bypass";
		}
		Text_Main[8] = "Apply";
		if(gGfxOptimiserState==1)
		{
			Text_Main[8] = "Please Wait";
		}

		//Print FPS
		sprintf_s(gCharBuffer,"fps: %i",gFps);
		D3DXVECTOR4 vColour = D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
		vColour.x = iFloatInterpolateSmooth((float)gFps,50.0f,60.0f,1.0f,0.0f);
		vColour.y = iFloatInterpolateSmooth((float)gFps,50.0f,60.0f,0.0f,1.0f);
		iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(12.0f,-11.0f),&vColour,gFont,false);

		Text_Setting[0] = Setting_000(Text_Setting[0],0); 	
		Text_Setting[1] = Setting_006(Text_Setting[1],1);//Setting_010(Text_Setting[1],1);	
		Text_Setting[2] = Setting_001(Text_Setting[2],2);
		Text_Setting[3] = Setting_On_Off(Text_Setting[3],3,gFxaaEnable);
		Text_Setting[4] = Setting_On_Off(Text_Setting[4],4,gDoFEnable);
		Text_Setting[5] = Setting_On_Off(Text_Setting[5],5,gBlurEnable);
		Text_Setting[6] = Setting_On_Off(Text_Setting[6],6,gGlowEnable);
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";
		if(gGfxOptimiserState==2)
		{
			Text_Setting[8] = "Run Optimiser";
		}
		else if(gGfxOptimiserState==1)
		{
			Text_Setting[8] = "Optimiser Running";
		}

		if(cGame_Controls.Input_Menu_Action_Back() &&
			!gFirstRun &&
			gGfxOptimiserState==0)
		{
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 1;
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 8;
	if(gGfxOptimiserState==1)
	{
		gMenuSubId = 8;
	}
	else if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
	}
	else if(gMenuSubId==1)
	{
	}
	else if(gMenuSubId==2)
	{
	}
	else if(gMenuSubId==3)
	{
	}
	else if(gMenuSubId==4)
	{
	}
	else if(gMenuSubId==5)
	{
	}
	else if(gMenuSubId==6)
	{
	}
	else if(gMenuSubId==7)
	{
		//Bypass
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			cGame_Optimiser.bBypass = true;
		}
	}
	else if(gMenuSubId==8)
	{
		//apply settings
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			if(gGfxOptimiserState==2)
			{
				cGame_Optimiser.bStart = true;
			}
			else
			{
				bPlayAnimationOut = true;
				if(gFirstRun)
				{
					gMenuId = 8;//Goto Colour Menu
				}
				else
				{
					gMenuId = 1;//Return to settings
				}
			}
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///AUDIO SETTINGS
//******************************************************************
void Game_Menu::Menu_004(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Audio";
		Text_Main[0] = "Music";
		Text_Main[1] = "SFX";
		Text_Main[2] = "HitSounds";
		Text_Main[3] = "Apply";
		Text_Main[4] = "";
		Text_Main[5] = "";
		Text_Main[6] = "";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		Text_Setting[0] = Setting_007(Text_Setting[0],0); 	
		Text_Setting[1] = Setting_008(Text_Setting[1],1,gVolumeFx);
		Text_Setting[2] = Setting_008(Text_Setting[2],2,gVolumeHitsound);
		Text_Setting[3] = "";
		Text_Setting[4] = "";
		Text_Setting[5] = "";
		Text_Setting[6] = "";
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back())
		{
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 1;
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 3;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
	}
	else if(gMenuSubId==1)
	{
	}
	else if(gMenuSubId==2)
	{
	}
	else if(gMenuSubId==3)
	{
		//apply settings
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 1;
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///Ai Options
//******************************************************************
void Game_Menu::Menu_005(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Ai Options";
		Text_Main[0] = "Ai - Count";
		Text_Main[1] = "Ai - Difficulty";
		Text_Main[2] = "Apply";
		Text_Main[3] = "";
		Text_Main[4] = "";
		Text_Main[5] = "";
		Text_Main[6] = "";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		Text_Setting[0] = Setting_011(Text_Setting[0],0);	
		Text_Setting[1] = Setting_012(1);
		Text_Setting[2] = "";
		Text_Setting[3] = "";
		Text_Setting[4] = "";
		Text_Setting[5] = "";
		Text_Setting[6] = "";
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back())
		{
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 1;
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 2;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
	}
	else if(gMenuSubId==1)
	{
	}
	else if(gMenuSubId==2)
	{
		//apply settings
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 1;
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///Single Player
//******************************************************************
void Game_Menu::Menu_006(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Single Player";
		Text_Main[0] = "Start";
		Text_Main[1] = "GameMode";
		Text_Main[2] = "Track";
		Text_Main[3] = "Reverse";
		Text_Main[4] = "Speed Class";
		Text_Main[5] = "Ai - Count";
		Text_Main[6] = "Ai - Difficulty";
		Text_Main[7] = "Back";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		Text_Setting[0] = "";
		Text_Setting[1] = Setting_015(1);
		Text_Setting[2] = Setting_016(2);
		Text_Setting[3] = Setting_017(3);
		Text_Setting[4] = Setting_013(4);
		Text_Setting[5] = Setting_011(Text_Setting[5],5);	
		Text_Setting[6] = Setting_012(6);
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back())
		{
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 2;
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 7;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			cGame_Audio.Music.MusicStop();
			cGame_Audio.Menu.MenuFx(3);
			gMenu_Active = false;
		}
	}
	else if(gMenuSubId==1)
	{
	}
	else if(gMenuSubId==2)
	{
	}
	else if(gMenuSubId==3)
	{
	}
	else if(gMenuSubId==4)
	{
	}
	else if(gMenuSubId==5)
	{
	}
	else if(gMenuSubId==6)
	{
	}
	else if(gMenuSubId==7)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 2;
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///UpgradePanel
//******************************************************************
void Game_Menu::UpgradePanel(const int index,int &upgradeID,const int upgradeINFO,const string &pretext,const string &desctext,const string &endtext)
{
	//-------------------------------------------------------------
	//Show sprites
	iSpriteImposterShow(Sprite_Upgrades[upgradeID],index);
	//bottom
	iSpriteImposterShow(Sprite_Upgrades_Bottom,index);
	//-------------------------------------------------------------
	//Cost to upgrade - level requirements, allow upgrade
	bool bAllowUp = false;
	int cost = 0;
	int levelreq = 0;
	if(upgradeID==0)
	{
		cost = 1;
		levelreq = 0;
	}
	else if(upgradeID==1)
	{
		cost = 2;
		levelreq = 6;
	}
	else if(upgradeID==2)
	{
		cost = 3;
		levelreq = 12;
	}
	//-------------------------------------------------------------
	//Print
	D3DXVECTOR2 offset = Font_MenuLocation[index];
	offset.y -= 0.5f;
	offset.x += 5.5f;
	iPrint3((char*)pretext.c_str(),Font_SettingSize[0],&offset,&gMenuFontColour,gFont,false);
	offset.x += 3.0f;
	iPrint3((char*)desctext.c_str(),Font_SettingSize[0],&offset,&gFontWhite,gFont,false);
	offset.x += 5.0f;
	sprintf_s(gCharBuffer,"%i",upgradeINFO);
	iPrint3(gCharBuffer,Font_SettingSize[0],&offset,&gMenuFontColour,gFont,false);
	offset.x += 0.75f;
	iPrint3((char*)endtext.c_str(),Font_SettingSize[0],&offset,&gFontWhite,gFont,false);
	//Print upgrade button
	offset.y += 1.0f;
	offset.x += 0.75f;
	if(upgradeID==3)
	{
		iPrint((char*)"Max",Font_SettingSize[0],&offset,&gFontWhite,gFont,false);
	}
	else if(levelreq > cGame_PlayerStats.Player_Level)
	{
		sprintf_s(gCharBuffer,"Level %i+",levelreq);
		iPrint(gCharBuffer,Font_SettingSize[0],&offset,&gFontBlack,gFont,false);
	}
	else if(cost > cGame_PlayerStats.Upgrade_Points_Remaining)
	{
		iPrint((char*)"-------",Font_SettingSize[0],&offset,&gFontBlack,gFont,false);
	}
	else
	{
		iPrint((char*)"Upgrade",Font_SettingSize[0],&offset,&gFontBlack,gFont,false);
		bAllowUp = true;
	}
	//Print Cost info
	offset.x -= 2.75f;
	if(cost>0)
	{
		iPrint3((char*)"Cost",Font_SettingSize[0],&offset,&gFontWhite,gFont,false);
		offset.x += 0.75f;
		sprintf_s(gCharBuffer,"%i",cost);
		iPrint(gCharBuffer,Font_SettingSize[0],&offset,&gFontWhite,gFont,false);
	}
	//Apply upgrades o0o0o00o0o
	if(bAllowUp)
	{
		float left = 1.2f;
		float right = 4.2f;
		float upper = Font_MenuLocation[index].y + 0.8f;
		float lower = Font_MenuLocation[index].y;
		///Mouse in zone
		if((gMousePosition_Current.y < upper && gMousePosition_Current.y > lower) &&
			(gMousePosition_Current.x < right && gMousePosition_Current.x > left) &&
			iMouseButtonClick(VK_LBUTTON))
		{
			///Check + apply 
			cGame_PlayerStats.Upgrade_Points_Remaining -= cost;
			cGame_PlayerStats.Upgrade_Points_Used += cost;
			upgradeID++;
			cGame_Audio.Menu.MenuFx(2);
		}
	}
	//-------------------------------------------------------------
}
//******************************************************************
///Upgrades
//******************************************************************
void Game_Menu::Menu_007(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Upgrades";
		Text_Main[0] = "Core Systems";
		Text_Main[1] = "Primary Weapon";
		Text_Main[2] = "Fusion Missile";
		Text_Main[3] = "Shox Wave";
		Text_Main[4] = "EM Burst";
		Text_Main[5] = "Lancer Rail";
		Text_Main[6] = "Utility";
		Text_Main[7] = "Back";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
		//Start showroom
		cGame_Track.Showroom_Start();
		cGame_Audio.Music.Showroom_Start();
		cGame_Camera.Mode_Menu = 1;//2
	}
	//-------------------------------------------------------------

	if(bTextReady)
	{
		Text_Setting[0] = "";	
		Text_Setting[1] = "";
		Text_Setting[2] = "";
		Text_Setting[3] = "";
		Text_Setting[4] = "";
		Text_Setting[5] = "";
		Text_Setting[6] = "";
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back())
		{
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 2;
			//Stop showroom
			cGame_Track.Showroom_Stop();
			cGame_Audio.Music.Showroom_Stop();
		}
	}
	//-------------------------------------------------------------
	//Hide master mesh (used in upgrade menu)

	iMeshHide(cGame_Mesh.Bike_Weapons.P_Primary_Glow,false);

	iMeshHide(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[0],false);
	iMeshHide(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[1],false);
	iMeshHide(cGame_Mesh.Bike_Weapons.P_Shockwave_Projectile,false);
	iMeshHide(cGame_Mesh.Bike_Weapons.P_EMBurst_Projectile,false);
	iMeshHide(cGame_Mesh.Bike_Weapons.Rail_Projectile,false);
	iMeshHide(cGame_Mesh.Bike_Weapons.Secondary_Charging,false);

	iMeshHide(cGame_Mesh.Bike_Weapons.Shield_Inv,false);
	//-------------------------------------------------------------
	//Enable colour changes
	iVector3TendTo(&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,&cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget,15.0f);
	//Set weapons
	// Uses master meshes for reflections.
	cGame_Bike[gAi_Max_Count].Weapons.vPrimaryProjectile[0] = D3DXVECTOR3(0.0f,-4998.0f,6.4f);
	cGame_Bike[gAi_Max_Count].Weapons.vSecondaryProjectile = D3DXVECTOR3(0.0f,-4997.0f,6.0f);

	iMeshScaleSet(cGame_Mesh.Bike_Weapons.P_Primary_Glow,&D3DXVECTOR3(0.75f,0.75f,0.75f),false);
	iMeshScaleSet(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[0],&D3DXVECTOR3(1.5f,1.5f,1.5f),false);
	iMeshScaleSet(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[1],&D3DXVECTOR3(1.5f,1.5f,1.5f),false);
	iMeshScaleSet(cGame_Mesh.Bike_Weapons.P_Shockwave_Projectile,&D3DXVECTOR3(1.25f,1.0f,1.0f),false);
	iMeshScaleSet(cGame_Mesh.Bike_Weapons.Rail_Projectile,&D3DXVECTOR3(0.5f,0.5f,2.0f),false);
	iMeshScaleSet(cGame_Mesh.Bike_Weapons.P_EMBurst_Projectile,&D3DXVECTOR3(0.3f,0.3f,0.3f),false);
	//-------------------------------------------------------------
	MenuSub_Max = 7;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		if(bTextReady)
		{
			//Core Systems
			cGame_Camera.Mode_Menu = 2;
			//speed class unlock
			UpgradePanel(0,cGame_Upgrades.uSpeedClassUnlockPlayer,
						cGame_Upgrades.Info_SpeedClassUnlock[cGame_Upgrades.uSpeedClassUnlockPlayer],
						"Speed Class:",
						"Currently Unlocked:",
						" cc");
			//uEnergyMaxPlayer
			UpgradePanel(1,cGame_Upgrades.uEnergyMaxPlayer,
						cGame_Upgrades.Info_EnergyMax[cGame_Upgrades.uEnergyMaxPlayer],
						"Energy - Max:",
						"Increases Max Capacity to:",
						"Energy");
			//uEnergyPickupPlayer
			UpgradePanel(2,cGame_Upgrades.uEnergyPickupPlayer,
						cGame_Upgrades.Info_EnergyPickup[cGame_Upgrades.uEnergyPickupPlayer],
						"Energy - Pickup:",
						"Increases Pickup Amount to:",
						"Energy");
			//uEnergyTickRegenPlayer
			UpgradePanel(3,cGame_Upgrades.uEnergyTickRegenPlayer,
						cGame_Upgrades.Info_EnergyTickRegen[cGame_Upgrades.uEnergyTickRegenPlayer],
						"Energy - Regen:",
						"Increases Regen Amount to:",
						"Energy/Second");
		}
	}
	else if(gMenuSubId==1)
	{
		//Primary Weapon
		cGame_Camera.Mode_Menu = 2;
		iMeshLocationSet(cGame_Mesh.Bike_Weapons.P_Primary_Glow,&cGame_Bike[gAi_Max_Count].Weapons.vPrimaryProjectile[0],false);
		iMeshOrientationSet(cGame_Mesh.Bike_Weapons.P_Primary_Glow,&cGame_Bike[gAi_Max_Count].Weapons.qPrimaryProjectile[0],false);
		iMeshColorSet(cGame_Mesh.Bike_Weapons.P_Primary_Glow,&cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget,false);
		//Show
		iMeshShow(cGame_Mesh.Bike_Weapons.P_Primary_Glow,false);
		if(bTextReady)
		{
			//uPrimaryDamage
			UpgradePanel(0,cGame_Upgrades.uPrimaryDamagePlayer,
						cGame_Upgrades.Info_PrimaryDamage[cGame_Upgrades.uPrimaryDamagePlayer],
						"Damage:",
						"Increases Damage by:",
						"%");
			//uPrimaryTravel
			UpgradePanel(1,cGame_Upgrades.uPrimaryTravelPlayer,
						cGame_Upgrades.Info_PrimaryTravel[cGame_Upgrades.uPrimaryTravelPlayer],
						"Travel Speed:",
						"Increases Velocity by:",
						"%");
		}
	}
	else if(gMenuSubId==2)
	{
		//Fusion Missile
		cGame_Camera.Mode_Menu = 2;
		iMeshLocationSet(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[0],&cGame_Bike[gAi_Max_Count].Weapons.vSecondaryProjectile,false);
		iMeshLocationSet(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[1],&cGame_Bike[gAi_Max_Count].Weapons.vSecondaryProjectile,false);
		iMeshColorSet(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[1],&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
		iMeshShow(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[0],false);
		iMeshShow(cGame_Mesh.Bike_Weapons.P_Missile_Projectile[1],false);
		//cGame_Bike[gAi_Max_Count].Weapons.vTrackingMeshColour = D3DXVECTOR3(3.0f,0.3f,0.0f);
		//cGame_Bike[gAi_Max_Count].Weapons.bBeingTracked = true;
		if(bTextReady)
		{
			//uMissileDamagePlayer
			UpgradePanel(0,cGame_Upgrades.uMissileDamagePlayer,
						cGame_Upgrades.Info_MissileDamage[cGame_Upgrades.uMissileDamagePlayer],
						"Damage:",
						"Increases Damage by:",
						"%");
			//uMissileLockTimePlayer
			UpgradePanel(1,cGame_Upgrades.uMissileLockTimePlayer,
						cGame_Upgrades.Info_MissileLockTime[cGame_Upgrades.uMissileLockTimePlayer],
						"Lock-on Time:",
						"Reduces Lock Time by:",
						"%");
			//uMissileRadiusPlayer
			UpgradePanel(2,cGame_Upgrades.uMissileRadiusPlayer,
						cGame_Upgrades.Info_MissileRadius[cGame_Upgrades.uMissileRadiusPlayer],
						"Explosion Radius:",
						"Increases Radius by:",
						"%");
			//uMissileTravelPlayer
			UpgradePanel(3,cGame_Upgrades.uMissileTravelPlayer,
						cGame_Upgrades.Info_MissileTravel[cGame_Upgrades.uMissileTravelPlayer],
						"Travel Speed:",
						"Increases Velocity by:",
						"%");
		}
	}
	else if(gMenuSubId==3)
	{
		//Shox Wave
		cGame_Camera.Mode_Menu = 2;
		iMeshLocationSet(cGame_Mesh.Bike_Weapons.P_Shockwave_Projectile,&cGame_Bike[gAi_Max_Count].Weapons.vSecondaryProjectile,false);
		iMeshColorSet(cGame_Mesh.Bike_Weapons.P_Shockwave_Projectile,&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
		iMeshShow(cGame_Mesh.Bike_Weapons.P_Shockwave_Projectile,false);

		if(bTextReady)
		{
			//uShoxwaveDamagePlayer
			UpgradePanel(0,cGame_Upgrades.uShoxwaveDamagePlayer,
						cGame_Upgrades.Info_ShoxwaveDamage[cGame_Upgrades.uShoxwaveDamagePlayer],
						"Damage:",
						"Increases Damage by:",
						"%");
			//uShoxwaveTravelPlayer
			UpgradePanel(1,cGame_Upgrades.uShoxwaveTravelPlayer,
						cGame_Upgrades.Info_ShoxwaveTravel[cGame_Upgrades.uShoxwaveTravelPlayer],
						"Travel Speed:",
						"Increases Velocity by:",
						"%");
			//uShoxwaveReductionPlayer
			UpgradePanel(2,cGame_Upgrades.uShoxwaveReductionPlayer,
						cGame_Upgrades.Info_ShoxwaveReduction[cGame_Upgrades.uShoxwaveReductionPlayer],
						"Slowdown Effect:",
						"Increases Slowdown by:",
						"%");
		}
	}
	else if(gMenuSubId==4)
	{
		//EM Burst
		cGame_Camera.Mode_Menu = 2;
		cGame_Bike[gAi_Max_Count].Weapons.vSecondaryProjectile = iVectorLocationOffset(&cGame_Bike[gAi_Max_Count].Manager.vTargetMesh,&cGame_Bike[gAi_Max_Count].Manager.qBikeOutput,&D3DXVECTOR3(0.0f,-1.0f,0.3f));
		iMeshLocationSet(cGame_Mesh.Bike_Weapons.P_EMBurst_Projectile,&cGame_Bike[gAi_Max_Count].Weapons.vSecondaryProjectile,false);
		iMeshColorSet(cGame_Mesh.Bike_Weapons.P_EMBurst_Projectile,&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
		iMeshShow(cGame_Mesh.Bike_Weapons.P_EMBurst_Projectile,false);
		if(bTextReady)
		{
			//uEmBurstDamagePlayer
			UpgradePanel(0,cGame_Upgrades.uEmBurstDamagePlayer,
						cGame_Upgrades.Info_EmBurstDamage[cGame_Upgrades.uEmBurstDamagePlayer],
						"Damage:",
						"Increases Damage by:",
						"%");
			//uEmBurstRadiusPlayer
			UpgradePanel(1,cGame_Upgrades.uEmBurstRadiusPlayer,
						cGame_Upgrades.Info_EmBurstRadius[cGame_Upgrades.uEmBurstRadiusPlayer],
						"Explosion Radius:",
						"Increases Radius by:",
						"%");
			//uEmBurstReductionPlayer
			UpgradePanel(2,cGame_Upgrades.uEmBurstReductionPlayer,
						cGame_Upgrades.Info_EmBurstReduction[cGame_Upgrades.uEmBurstReductionPlayer],
						"Slowdown Effect:",
						"Increases Slowdown by:",
						"%");
		}
	}
	else if(gMenuSubId==5)
	{
		//Lancer Rail
		cGame_Camera.Mode_Menu = 2;
		iMeshLocationSet(cGame_Mesh.Bike_Weapons.Rail_Projectile,&cGame_Bike[gAi_Max_Count].Weapons.vSecondaryProjectile,false);
		iMeshColorSet(cGame_Mesh.Bike_Weapons.Rail_Projectile,&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
		iMeshShow(cGame_Mesh.Bike_Weapons.Rail_Projectile,false);
		if(bTextReady)
		{
			//uRailDamagePlayer
			UpgradePanel(0,cGame_Upgrades.uRailDamagePlayer,
						cGame_Upgrades.Info_RailDamage[cGame_Upgrades.uRailDamagePlayer],
						"Damage:",
						"Increases Damage by:",
						"%");
			//uRailTravelPlayer
			UpgradePanel(1,cGame_Upgrades.uRailTravelPlayer,
						cGame_Upgrades.Info_RailTravel[cGame_Upgrades.uRailTravelPlayer],
						"Travel Speed:",
						"Increases Velocity by:",
						"%");
		}
	}
	else if(gMenuSubId==6)
	{
		//Utility
		cGame_Camera.Mode_Menu = 2;
		iMeshLocationSet(cGame_Mesh.Bike_Weapons.Shield_Inv,&cGame_Bike[gAi_Max_Count].Manager.vTargetMesh,false);
		iMeshColorSet(cGame_Mesh.Bike_Weapons.Shield_Inv,&cGame_Bike[gAi_Max_Count].Colour.vBikeColour,false);
		iMeshShow(cGame_Mesh.Bike_Weapons.Shield_Inv,false);
		if(bTextReady)
		{
			///uShieldInvTime
			UpgradePanel(0,cGame_Upgrades.uShieldInvTimePlayer,
						cGame_Upgrades.Info_ShieldInvTime[cGame_Upgrades.uShieldInvTimePlayer],
						"Shield:",
						"Increases Duration to:",
						"Seconds");
			///uShieldInvConvert
			UpgradePanel(1,cGame_Upgrades.uShieldInvConvertPlayer,
						cGame_Upgrades.Info_ShieldInvConvert[cGame_Upgrades.uShieldInvConvertPlayer],
						"Shield:",
						"Siphon Damage:",
						"% Energy");
			///uDoubleDamageTime
			UpgradePanel(2,cGame_Upgrades.uDoubleDamageTimePlayer,
						cGame_Upgrades.Info_DoubleDamageTime[cGame_Upgrades.uDoubleDamageTimePlayer],
						"Double Damage:",
						"Increases Duration to:",
						"Seconds");
			///uDoubleDamageConv
			UpgradePanel(3,cGame_Upgrades.uDoubleDamageConvPlayer,
						cGame_Upgrades.Info_DoubleDamageConv[cGame_Upgrades.uDoubleDamageConvPlayer],
						"Double Damage:",
						"Siphon Energy:",
						"% Damage");
			///uAutoPilotTime
			UpgradePanel(4,cGame_Upgrades.uAutoPilotTimePlayer,
						cGame_Upgrades.Info_AutoPilotTime[cGame_Upgrades.uAutoPilotTimePlayer],
						"Auto Pilot:",
						"Increases Duration to:",
						"Seconds");
			///uWarpDamageReducePlayer
			UpgradePanel(5,cGame_Upgrades.uWarpDamageReducePlayer,
						cGame_Upgrades.Info_WarpDamageReduce[cGame_Upgrades.uWarpDamageReducePlayer],
						"Warp:",
						"Incoming Damage Reduced:",
						"%");
		}
	}
	else if(gMenuSubId==7)
	{
		//apply settings
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 2;
			//Stop showroom
			cGame_Track.Showroom_Stop();
			cGame_Audio.Music.Showroom_Stop();
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///Personalise
//******************************************************************
void Game_Menu::Menu_008(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Personalise";
		Text_Main[0] = "Name";
		Text_Main[1] = "Bike Colour";
		Text_Main[2] = "Menu Colour";
		Text_Main[3] = "Camera Preset";
		Text_Main[4] = "Back";
		Text_Main[5] = "";
		Text_Main[6] = "";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		Text_Main[4] = "Apply";
		if((string)gPlayerName=="Player")
		{
			Text_Main[4] = "Invalid Name";
		}


		//Keep user bike colour active
		cGame_Bike[gAi_Max_Count].Colour.ColourSelector = 0;

		Text_Setting[0] = (string)gPlayerName;
		Text_Setting[1] = Setting_009(Text_Setting[1],1);
		Text_Setting[2] = Setting_014(Text_Setting[2],2);
		Text_Setting[3] = Setting_018(3);
		Text_Setting[4] = "";
		Text_Setting[5] = "";
		Text_Setting[6] = "";
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back() && 
			!gFirstRun &&
			!gTextInputLock &&
			(string)gPlayerName!="Player")
		{
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 1;
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 4;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		string InputString = (string)gPlayerName;
		InputString = TextInput(InputString);
		strcpy_s(gPlayerName,InputString.c_str());
	}
	else if(gMenuSubId==1)
	{
	}
	else if(gMenuSubId==2)
	{
	}
	else if(gMenuSubId==3)
	{
		if(bTextReady)
		{
			cGame_Camera.Mode_Menu = 5;
		}
	}
	else if(gMenuSubId==4)
	{
		//apply settings
		if(cGame_Controls.Input_Menu_Action_Select() &&
			(string)gPlayerName!="Player")
		{
			if(gFirstRun)
			{
				bPlayAnimationOut = true;
				gFirstRun = false;
				gMenuId = 2;//Return to main menu
			}
			else
			{
				bPlayAnimationOut = true;
				gMenuId = 1;
			}
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///Control Settings
//******************************************************************
void Game_Menu::Menu_009(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Controls";
		Text_Main[0] = "Keyboard";
		Text_Main[1] = "Xbox Controller";
		Text_Main[2] = "Xbox Vibrate";
		Text_Main[3] = "Back";
		Text_Main[4] = "";
		Text_Main[5] = "";
		Text_Main[6] = "";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		Text_Setting[0] = "";//Setting_018(Text_Setting[0],0);	
		Text_Setting[1] = "";//Setting_012(1);
		Text_Setting[2] = Setting_On_Off(Text_Setting[2],2,gXbox360Controller_Vibrate);
		Text_Setting[3] = "";
		Text_Setting[4] = "";
		Text_Setting[5] = "";
		Text_Setting[6] = "";
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back())
		{
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 1;
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 3;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		if(bTextReady)
		{
			iSpriteScaleSet(Sprite_Controls_Keyboard,&D3DXVECTOR2(32.0f,18.0f * gScreenYScale));
			iSpriteShow(Sprite_Controls_Keyboard);
		}
	}
	else if(gMenuSubId==1)
	{
		if(bTextReady)
		{
			iSpriteScaleSet(Sprite_Controls_Xbox,&D3DXVECTOR2(32.0f,18.0f * gScreenYScale));
			iSpriteShow(Sprite_Controls_Xbox);
		}
	}
	else if(gMenuSubId==2)
	{
		if(bTextReady)
		{
			iSpriteScaleSet(Sprite_Controls_Xbox,&D3DXVECTOR2(32.0f,18.0f * gScreenYScale));
			iSpriteShow(Sprite_Controls_Xbox);
		}
	}
	else if(gMenuSubId==3)
	{
		//apply settings
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 1;
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///STATS INFO
//******************************************************************
void Game_Menu::Menu_010(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Statistics";
		Text_Main[0] = "Level";
		Text_Main[1] = "Kills / Deaths";
		Text_Main[2] = "Wins / Loss";
		Text_Main[3] = "Playtime";
		Text_Main[4] = "World Ranking";
		if(!gMasterServerOnline)
		{
			Text_Main[4] = "MstSrv Offline";
		}
		Text_Main[5] = "Back";
		Text_Main[6] = "";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		//Settings Font - Settings
		char Convert[1024];
		sprintf_s(Convert,"%d",cGame_PlayerStats.Player_Level);
		Text_Setting[0] = Convert;

		sprintf_s(Convert,"%d / %d",cGame_PlayerStats.Kill_Total,cGame_PlayerStats.Death_Total);
		Text_Setting[1] = Convert;

		sprintf_s(Convert,"%d / %d",cGame_PlayerStats.Win_Total,cGame_PlayerStats.Loss_Total);
		Text_Setting[2] = Convert;

		unsigned long TotalSecondsInput = cGame_PlayerStats.PlayTime_Total;
		int Hours = 0;
		int Minutes = 0;
		int Seconds = 0;
		while(TotalSecondsInput >= 60)
		{
			Minutes++;
			TotalSecondsInput -= 60;

		}
		while(Minutes>= 60)
		{
			Hours++;
			Minutes -= 60;				
		}

		Seconds = (int)TotalSecondsInput;

		sprintf_s(Convert,"%dh : %dm : %ds",Hours,Minutes,Seconds);
		Text_Setting[3] = Convert;

		Text_Setting[4] = "";
		Text_Setting[5] = "";
		Text_Setting[6] = "";
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back())
		{
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 2;
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 5;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
	}
	else if(gMenuSubId==1)
	{
	}
	else if(gMenuSubId==2)
	{
	}
	else if(gMenuSubId==3)
	{
	}
	else if(gMenuSubId==4)
	{
		if(gMasterServerOnline &&
			cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 15;
		}
	}
	else if(gMenuSubId==5)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 2;
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///Multi Player
//******************************************************************
void Game_Menu::Menu_011(void)
{
	//-------------------------------------------------------------
	if(bPlayAnimationIn)
	{
		Text_Header = "Multi Player";
		Text_Main[0] = "Internet - Search";
		if(!gMasterServerOnline)
		{
			Text_Main[0] = "MasterSrv Offline";
		}
		Text_Main[1] = "Internet - Region";
		Text_Main[2] = "Lan - Host";
		Text_Main[3] = "Lan - Join";
		Text_Main[4] = "Back";
		Text_Main[5] = "";
		Text_Main[6] = "";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		//-------------------------------------------------------------
		Text_Setting[0] = "";	
		Text_Setting[1] = Setting_019(1);
		Text_Setting[2] = "";
		Text_Setting[3] = "";
		Text_Setting[4] = "";
		Text_Setting[5] = "";
		Text_Setting[6] = "";
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		//NAT ERRORED HOST AND NO GAMES INFORM
		if(cGame_Ftp.bHostNatFailed_NoGamesInform)
		{
			Text_Setting[0] = "No Games";	
			iPrint3((char*)"Warning: No Games Found - Unable to Host",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,6.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
			iPrint3((char*)"- - - - - - - - - - - - - - - - - - - -",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,5.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,false);
			iPrint3((char*)"There are currently no active games to join",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,4.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			iPrint3((char*)"Your hosting permissions have been revoked due to previous Firewall Failure",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,3.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			iPrint3((char*)"Please ensure ports 6001-6002 TCP+UDP are forwarded on your router",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,2.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			iPrint3((char*)"Then Restart the game",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,1.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			iPrint3((char*)"Note: You will no longer be allowed to Host Games",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,0.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
		}

		if(cGame_Controls.Input_Menu_Action_Back())
		{
			gTextInputLock = false;
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 2;
			Net_LobbyReset();
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 4;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		if(cGame_Controls.Input_Menu_Action_Select() &&
			gMasterServerOnline)
		{
			//Reset NatInform flag
			cGame_Ftp.bHostNatFailed_NoGamesInform = false;
			//Set Internet TickRate
			gNetworkTickRateMax = 3;
			///Lets check server for games !!!! wh0o0o0o0o
			gManualNetworkGame = false;
			if(cGame_Ftp.GameFound())///game found - goto client mode
			{
				cGame_Network.Client.State = 1;
				bPlayAnimationOut = true;
				gMenuId = 13;
			}
			else if(cGame_Ftp.bFtpOnline && ///FTP online but no games - Host Mode
				!cGame_Ftp.bHostNatFailed) ///Did NAT previously fail?
			{
				cGame_Network.Server.State = 1;
				bPlayAnimationOut = true;
				gMenuId = 12;
			}
			else///Error - No FTP or No games for NAT failed hosts.
			{
				if(cGame_Ftp.bHostNatFailed)
				{
					//inform user no games, unable to host.	
					cGame_Ftp.bHostNatFailed_NoGamesInform = true;
				}
				cGame_Ftp.ZeroData();
			}
		}
	}
	else if(gMenuSubId==1)///game region
	{
	}
	else if(gMenuSubId==2)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			//Set Lan TickRate
			gNetworkTickRateMax = 2;

			gManualNetworkGame = true;
			cGame_Network.Server.State = 1;
			bPlayAnimationOut = true;
			gMenuId = 12;
		}
	}
	else if(gMenuSubId==3)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			//Set Lan TickRate
			gNetworkTickRateMax = 2;

			gManualNetworkGame = true;
			bPlayAnimationOut = true;
			gMenuId = 13;
		}
	}
	else if(gMenuSubId==4)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 2;
			Net_LobbyReset();
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///NETWORK HOST
//******************************************************************
void Game_Menu::Menu_012(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Network Host";
		Text_Main[0] = "Start";
		Text_Main[1] = "GameMode";
		Text_Main[2] = "Track";
		Text_Main[3] = "Reverse";
		Text_Main[4] = "Speed Class";
		Text_Main[5] = "Ai - Count";
		Text_Main[6] = "Ai - Difficulty";
		Text_Main[7] = "Back";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		//-------------------------------------------------------------
		//Post Game
		if(!gManualNetworkGame)
		{
			//Check If file has been deleted by a client (EG: Nat failure)
			if(cGame_Ftp.bHostNatFailed)
			{
				gGammaMulti = 0.1f;
				iPrint3((char*)"Warning: Game Removed (Firewall Failure)",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,6.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
				iPrint3((char*)"- - - - - - - - - - - - - - - - - - - -",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,5.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,false);
				iPrint3((char*)"Your game has been deleted from the master server",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,4.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
				iPrint3((char*)"A Client was unable to connect to your game due to your firewall",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,3.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
				iPrint3((char*)"Please ensure ports 6001-6002 TCP+UDP are forwarded on your router",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,2.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
				iPrint3((char*)"Then Restart the game",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,1.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
				iPrint3((char*)"Note: You will no longer be allowed to Host Games",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,0.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			}
			else
			{
				///Update FTP with game
				if(gNumberOfClients<iNetServerMaxClientCount()-1)
				{
					cGame_Ftp.CreateGame();	
				}
				else///Delete game - server full
				{
					cGame_Ftp.DeleteGame();	
				}
			}
		}

		Text_Setting[0] = "";
		Text_Setting[1] = Setting_015(1);
		Text_Setting[2] = Setting_016(2);
		Text_Setting[3] = Setting_017(3);
		Text_Setting[4] = Setting_013(4);
		Text_Setting[5] = Setting_011(Text_Setting[5],5);	
		Text_Setting[6] = Setting_012(6);
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back() && 
			!gTextInputLock &&
			gNumberOfClients==0)
		{
			//FTP - Clear game, reset
			if(!gManualNetworkGame)
			{
				cGame_Ftp.DeleteGame();	
				cGame_Ftp.ZeroData();	
			}

			cGame_Network.Server.State = -1;
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 11;
			Net_LobbyReset();
		}
	}
	//-------------------------------------------------------------
	//Control Bikes - SERVER
	int SpawnId = 0;
	///Player
	cGame_Bike[gAi_Max_Count].Colour.vBikeColour = cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget;
	cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed = 0.0f;
	cGame_Bike[gAi_Max_Count].fSteering = 0.0f;
	cGame_Bike[gAi_Max_Count].InputSpeedState = -1;
	cGame_Bike[gAi_Max_Count].Manager.qBikeOrigin = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	cGame_Bike[gAi_Max_Count].Manager.vBikeOrigin = cGame_Spawn.vSpawnLocation[SpawnId];
	///Ai
	D3DXVECTOR3 vOffset = (0.0f,0.0f,0.0f);
	for(int i=0;i<gAi_Max_Count;i++)
	{
		if(i<gNumberOfClients)///Networked bike
		{
			cGame_Bike[i].Colour.vBikeColour = cGame_Bike[i].Colour.vBikeColourTarget;
			vOffset = (0.0f,0.0f,0.0f);
		}
		else
		{
			cGame_Bike[i].Colour.vBikeColourTarget = gBikeColourWhite;
			cGame_Bike[i].Colour.vBikeColour = gBikeColourWhite;
			vOffset = (0.0f,0.0f,0.0f);
			///Hide above Ai user count
			if(i>(gAi_UserChange-1))
			{
				vOffset = D3DXVECTOR3(0.0f,-5000.0f,0.0f);
			}
		}
		cGame_Bike[i].Manager.fAcceleration_Speed = 0.0f;
		cGame_Bike[i].fSteering = 0.0f;
		cGame_Bike[i].InputSpeedState = -1;
		///Locate
		cGame_Bike[i].Manager.qBikeOrigin = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
		cGame_Bike[i].Manager.vBikeOrigin = iVectorLocationOffset(&cGame_Spawn.vSpawnLocation[i+1],&cGame_Bike[i].Manager.qBikeOrigin,&vOffset);
	}
	//-------------------------------------------------------------
	if(gTextInputLock)
	{
		gMenuSubId = 2;
	}

	MenuSub_Max = 7;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		if(cGame_Controls.Input_Menu_Action_Select() && gNumberOfClients > 0)
		{
			//FTP - Clear game, reset
			if(!gManualNetworkGame)
			{
				cGame_Ftp.DeleteGame();	
				cGame_Ftp.ZeroData();	
			}

			gServerState = -1;
			cGame_Audio.Music.MusicStop();
			cGame_Audio.Menu.MenuFx(3);
			gMenu_Active = false;
		}
	}
	else if(gMenuSubId==1)
	{
	}
	else if(gMenuSubId==2)
	{
	}
	else if(gMenuSubId==3)
	{
	}
	else if(gMenuSubId==4)
	{
	}
	else if(gMenuSubId==5)
	{
	}
	else if(gMenuSubId==6)
	{
	}
	else if(gMenuSubId==7)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			//FTP - Clear game, reset
			if(!gManualNetworkGame)
			{
				cGame_Ftp.DeleteGame();	
				cGame_Ftp.ZeroData();	
			}

			cGame_Network.Server.State = -1;
			bPlayAnimationOut = true;
			gMenuId = 11;
			Net_LobbyReset();
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///NETWORK CLIENT
//******************************************************************
void Game_Menu::Menu_013(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Network Client";
		Text_Main[0] = "Connect";
		Text_Main[1] = "IP Address";
		Text_Main[2] = "GameMode";
		Text_Main[3] = "Track";
		Text_Main[4] = "Reverse";
		Text_Main[5] = "Speed Class";
		Text_Main[6] = "Ai - Count";
		Text_Main[7] = "Ai - Difficulty";
		Text_Main[8] = "Back";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		//if(iKeyClick(DIK_Y))
		//{
		//	cGame_Network.Client.State = 0;
		//}
		if(cGame_Network.Client.State==0)
		{
			Text_Setting[0] = "No Connection";
			//Nat Failure for Master Server Joined game - Delete the hosts file
			if(!gManualNetworkGame)
			{
				cGame_Ftp.ClientUnableToConnect();
				gGammaMulti = 0.1f;
				iPrint3((char*)"Warning: Unable to Connect (Host Failure)",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,6.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
				iPrint3((char*)"- - - - - - - - - - - - - - - - - - - -",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,5.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,false);
				iPrint3((char*)"The host of this game has: 1=Firewall issues, or, 2=No longer hosting",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,4.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
				iPrint3((char*)"This game has now been deleted from the Master Server",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,3.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
				iPrint3((char*)"The Host has been informed and had their ability to host revoked.",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,2.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
				iPrint3((char*)"Please click Back and try again",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,1.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
			}
		}
		else if(cGame_Network.Client.State==1)
		{
			Text_Setting[0] = "Connecting";
		}
		else if(cGame_Network.Client.State==2)
		{
			Text_Setting[0] = "Established";
		}

		Text_Setting[1] = gIpAddress;
		if(!gManualNetworkGame)
		{
			Text_Setting[1] = cGame_Ftp.IpAddressRecieved;
		}
		Text_Setting[2] = gInfoGameMode;
		Text_Setting[3] = gInfoTrack;
		Text_Setting[4] = gInfoTrackReverse;
		Text_Setting[5] = gInfoSpeedClass;
		char IntToString[16];
		sprintf_s(IntToString,"%i",gAi_UserChange);
		Text_Setting[6] = IntToString;

		Text_Setting[7] = gInfoAiDifficulty;
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back() && !gTextInputLock)
		{
			if(!gManualNetworkGame)
			{
				//FTP - Clear Data
				cGame_Ftp.ZeroData();
			}

			cGame_Network.Client.State = -1;
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 11;
			Net_LobbyReset();
		}
	}
	//-------------------------------------------------------------
	//Control Bikes
	int SpawnId = 1 + cGame_Network.Client.Client_ID;
	///Player
	cGame_Bike[gAi_Max_Count].Colour.vBikeColour = cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget;
	cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed = 0.0f;
	cGame_Bike[gAi_Max_Count].fSteering = 0.0f;
	cGame_Bike[gAi_Max_Count].InputSpeedState = -1;
	cGame_Bike[gAi_Max_Count].Manager.qBikeOrigin = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	cGame_Bike[gAi_Max_Count].Manager.vBikeOrigin = cGame_Spawn.vSpawnLocation[SpawnId];
	///Ai
	for(int i=0;i<gAi_Max_Count;i++)
	{
		if(i<gNumberOfClients)///Networked bike
		{
			cGame_Bike[i].Colour.vBikeColour = cGame_Bike[i].Colour.vBikeColourTarget;
		}
		else
		{
			cGame_Bike[i].Colour.vBikeColourTarget = gBikeColourWhite;
			cGame_Bike[i].Colour.vBikeColour = gBikeColourWhite;
		}
	}
	//-------------------------------------------------------------
	if(gTextInputLock && (gMenuSubId==8 || gMenuSubId==0))
	{
		gMenuSubId = 3;
	}

	MenuSub_Max = 8;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		//Connect
		if(gManualNetworkGame && cGame_Controls.Input_Menu_Action_Select() && cGame_Network.Client.State==0)
		{
			cGame_Network.Client.State = 1;
		}
			
	}
	else if(gMenuSubId==1)
	{
		if(gManualNetworkGame && cGame_Network.Client.State==0)
		{
			string InputString = gIpAddress;
			InputString = TextInput(InputString);
			strcpy_s(gIpAddress,InputString.c_str());
		}
	}
	else if(gMenuSubId==2)
	{
	}
	else if(gMenuSubId==3)
	{
	}
	else if(gMenuSubId==4)
	{
	}
	else if(gMenuSubId==5)
	{
	}
	else if(gMenuSubId==6)
	{
	}
	else if(gMenuSubId==7)
	{
	}
	else if(gMenuSubId==8)
	{
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			//FTP - Clear Data
			if(!gManualNetworkGame)
			{
				cGame_Ftp.ZeroData();
			}

			cGame_Network.Client.State = -1;
			bPlayAnimationOut = true;
			gMenuId = 11;
			Net_LobbyReset();
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
////******************************************************************
/////SEND FEEDBACK
////******************************************************************
//void Game_Menu::Menu_014(void)
//{
//	if(bPlayAnimationIn)
//	{
//		Text_Header = "FeedBack";
//		Text_Main[0] = "Overall";
//		Text_Main[1] = "Gameplay";
//		Text_Main[2] = "Performance";
//		Text_Main[3] = "Visuals";
//		Text_Main[4] = "Sound FX";
//		Text_Main[5] = "Music";
//		Text_Main[6] = "Difficulty";
//		Text_Main[7] = "Send >>";
//		if(!gMasterServerOnline)
//		{
//			Text_Main[7] = "MasterSrv Offline";
//		}
//		Text_Main[8] = "Back";
//		Text_Main[9] = "";
//		//Target Submenu
//		gMenuSubId = 0;
//	}
//	//-------------------------------------------------------------
//	if(bTextReady)
//	{
//		//Feedback Sent
//		if(gFeedback_Sent)
//		{
//			gGammaMulti = 0.1f;
//			iPrint3((char*)"Thank you for your Feedback",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,6.0f),&D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f),gFont,false);
//			iPrint3((char*)"- - - - - - - - - - - - - - - - - - - -",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,5.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,false);
//			iPrint3((char*)"We appricate you filling out the feedback form.",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,4.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
//			iPrint3((char*)"This information will help us find areas of the game that need work",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,3.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
//			iPrint3((char*)"Thanks again, From the team at Fuzon Designs!",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,2.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
//			iPrint3((char*)"Additional feedback can be left on the forums http://fuzon-uk.no-ip.biz",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,0.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
//		}
//		else
//		{
//			//Feedback Info
//			gGammaMulti = 0.1f;
//			iPrint3((char*)"Send Your Feedback on Tr-Zero",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,6.0f),&D3DXVECTOR4(1.0f,0.5f,0.0f,1.0f),gFont,false);
//			iPrint3((char*)"- - - - - - - - - - - - - - - - - - - -",cGame_Font.f24pt,&D3DXVECTOR2(-3.0f,5.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,0.5f),gFont,false);
//			iPrint3((char*)"All feedback is welcome and the team appricates your time!",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,4.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
//			iPrint3((char*)"Please rate the values from 0 to 10, click send when your done.",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,3.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
//			iPrint3((char*)"We will review all feedback, and, with your help, make Tr-Zero a better game!",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,2.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
//			iPrint3((char*)"Additional feedback can be left on the forums http://fuzon-uk.no-ip.biz",cGame_Font.f18pt,&D3DXVECTOR2(-3.0f,0.0f),&D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),gFont,false);
//		}
//
//		Setting_020(Text_Setting[0],0,gFeedback_Overall); 	
//		Setting_020(Text_Setting[1],1,gFeedback_Gameplay); 	
//		Setting_020(Text_Setting[2],2,gFeedback_Performance); 	
//		Setting_020(Text_Setting[3],3,gFeedback_Visuals); 	
//		Setting_020(Text_Setting[4],4,gFeedback_Sound); 	
//		Setting_020(Text_Setting[5],5,gFeedback_Music); 	
//		Setting_020(Text_Setting[6],6,gFeedback_Difficulty); 	
//		Text_Setting[7] = "";
//		Text_Setting[8] = "";
//		Text_Setting[9] = "";
//
//		if(cGame_Controls.Input_Menu_Action_Back())
//		{
//			bPlayAnimationOut = true;
//			//Target Menu
//			gMenuId = 2;
//		}
//	}
//	//-------------------------------------------------------------
//	MenuSub_Max = 8;
//	if(gMenuSubId < 0)
//	{
//		//Max MenuSub
//		gMenuSubId = MenuSub_Max;
//	}
//	else if(gMenuSubId==0)
//	{
//	}
//	else if(gMenuSubId==1)
//	{
//	}
//	else if(gMenuSubId==2)
//	{
//	}
//	else if(gMenuSubId==3)
//	{
//	}
//	else if(gMenuSubId==4)
//	{
//	}
//	else if(gMenuSubId==5)
//	{
//	}
//	else if(gMenuSubId==6)
//	{
//	}
//	else if(gMenuSubId==7)
//	{
//		//Send
//		if(gMasterServerOnline &&
//			!gFeedback_Sent &&
//			cGame_Controls.Input_Menu_Action_Select())
//		{
//			//Send data
//			cGame_Ftp.UploadFeedback();
//			gFeedback_Sent = true;
//		}
//	}
//	else if(gMenuSubId==8)
//	{
//		//apply settings
//		if(cGame_Controls.Input_Menu_Action_Select())
//		{
//			bPlayAnimationOut = true;
//			gMenuId = 2;
//		}
//	}
//	else
//	{
//		gMenuSubId = 0;
//	}
//	//-------------------------------------------------------------
//}
//******************************************************************
///Credits
//******************************************************************
void Game_Menu::Menu_014(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "Credits";
		Text_Main[0] = "Back";
		Text_Main[1] = "";
		Text_Main[2] = "";
		Text_Main[3] = "";
		Text_Main[4] = "";
		Text_Main[5] = "";
		Text_Main[6] = "";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		Text_Setting[0] = "";
		Text_Setting[1] = "";
		Text_Setting[2] = "";
		Text_Setting[3] = "";
		Text_Setting[4] = "";
		Text_Setting[5] = "";
		Text_Setting[6] = "";
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back())
		{
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 2;
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 0;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)
	{
		//apply settings
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 2;
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///PlayerStats
//******************************************************************
void Game_Menu::Menu_015(void)
{
	if(bPlayAnimationIn)
	{
		Text_Header = "World Ranking";
		Text_Main[0] = "Kills / Deaths";
		Text_Main[1] = "Wins / Losses";
		Text_Main[2] = "Playtime / Level";
		Text_Main[3] = "Lap Records";
		Text_Main[4] = "-";
		Text_Main[5] = "-";
		Text_Main[6] = "Back";
		Text_Main[7] = "";
		Text_Main[8] = "";
		Text_Main[9] = "";
		//Target Submenu
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
	if(bTextReady)
	{
		Text_Setting[0] = "";
		Text_Setting[1] = "";
		Text_Setting[2] = "";
		Text_Setting[3] = Setting_016(3);
		Text_Setting[4] = Setting_013(4);
		Text_Setting[5] = Setting_017(5);
		Text_Setting[6] = "";
		Text_Setting[7] = "";
		Text_Setting[8] = "";
		Text_Setting[9] = "";

		if(cGame_Controls.Input_Menu_Action_Back())
		{
			bPlayAnimationOut = true;
			//Target Menu
			gMenuId = 10;
		}
	}
	//-------------------------------------------------------------
	MenuSub_Max = 6;
	if(gMenuSubId < 0)
	{
		//Max MenuSub
		gMenuSubId = MenuSub_Max;
	}
	else if(gMenuSubId==0)//KILLS
	{
		//Set Gamma
		gGammaMulti = 0.1f;
		//Load Required Records into array
		if(cGame_Ftp.CurrentRecord_Loaded!=1)
		{
			gCurrentRecordViewed = 0;
			cGame_Ftp.LoadRecords(1);
			iPrint((char*)"Loading Data",cGame_Font.f18pt,&D3DXVECTOR2(0.0f,0.0f),&gMenuFontColour,gFont,true);
		}
		//Display Records
		else
		{
			DisplayRecords_Int((string)"Kills",(string)"Deaths",cGame_PlayerStats.Kill_Total,cGame_PlayerStats.Death_Total,false,false);
		}
	}
	else if(gMenuSubId==1)//Wins Losses
	{
		//Set Gamma
		gGammaMulti = 0.1f;
		//Load Required Records into array
		if(cGame_Ftp.CurrentRecord_Loaded!=2)
		{
			gCurrentRecordViewed = 0;
			cGame_Ftp.LoadRecords(2);
			iPrint((char*)"Loading Data",cGame_Font.f18pt,&D3DXVECTOR2(0.0f,0.0f),&gMenuFontColour,gFont,true);
		}
		//Display Records
		else
		{
			DisplayRecords_Int((string)"Wins",(string)"Losses",cGame_PlayerStats.Win_Total,cGame_PlayerStats.Loss_Total,false,false);
		}
	}
	else if(gMenuSubId==2)//Playtime
	{
		//Set Gamma
		gGammaMulti = 0.1f;
		//Load Required Records into array
		if(cGame_Ftp.CurrentRecord_Loaded!=3)
		{
			gCurrentRecordViewed = 0;
			cGame_Ftp.LoadRecords(3);
			iPrint((char*)"Loading Data",cGame_Font.f18pt,&D3DXVECTOR2(0.0f,0.0f),&gMenuFontColour,gFont,true);
		}
		//Display Records
		else
		{
			unsigned long PlayerLevelConversion = cGame_PlayerStats.Player_Level;
			DisplayRecords_Int((string)"Playtime",(string)"Level",cGame_PlayerStats.PlayTime_Total,PlayerLevelConversion,true,false);
		}
	}
	else if(gMenuSubId==3 ||
			gMenuSubId==4 ||
			gMenuSubId==5)
	{
		//Set GameMode
		gGameModeChange = 2;
		//Set Gamma
		gGammaMulti = 0.1f;
		//Load Required Records into array
		if(cGame_Ftp.CurrentRecord_Loaded!=4)
		{
			gCurrentRecordViewed = 0;
			cGame_Ftp.LoadRecords(4);
			iPrint((char*)"Loading Data",cGame_Font.f18pt,&D3DXVECTOR2(0.0f,0.0f),&gMenuFontColour,gFont,true);
		}
		//Display Records
		else
		{
			DisplayRecords_Float((string)"Fastest Lap");
		}
	}
	else if(gMenuSubId==6)
	{
		//apply settings
		if(cGame_Controls.Input_Menu_Action_Select())
		{
			bPlayAnimationOut = true;
			gMenuId = 10;
		}
	}
	else
	{
		gMenuSubId = 0;
	}
	//-------------------------------------------------------------
}
//******************************************************************
///NETWORK LOBBY RESET
//******************************************************************
void Game_Menu::Net_LobbyReset(void)
{
	//-------------------------------------------------------------
	///Player
	cGame_Bike[gAi_Max_Count].Colour.vBikeColour = cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget;
	cGame_Bike[gAi_Max_Count].Manager.fAcceleration_Speed = 0.0f;
	cGame_Bike[gAi_Max_Count].fSteering = 0.0f;
	cGame_Bike[gAi_Max_Count].InputSpeedState = -1;
	cGame_Bike[gAi_Max_Count].Manager.qBikeOrigin = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
	cGame_Bike[gAi_Max_Count].Manager.vBikeOrigin = cGame_Spawn.vSpawnLocation[0];
	///Ai
	D3DXVECTOR3 vOffset = (0.0f,0.0f,0.0f);
	for(int i=0;i<gAi_Max_Count;i++)
	{
		cGame_Bike[i].Colour.bSetupTargetColour = true;
		cGame_Bike[i].Manager.fAcceleration_Speed = 0.0f;
		cGame_Bike[i].fSteering = 0.0f;
		cGame_Bike[i].InputSpeedState = -1;
		///Locate
		cGame_Bike[i].Manager.qBikeOrigin = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
		cGame_Bike[i].Manager.vBikeOrigin = cGame_Spawn.vSpawnLocation[i+1];
	}
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_000 - Resolution
//******************************************************************
string Game_Menu::Setting_000(string &input,const int menusub)
{
	//-------------------------------------------------------------
	char Data[16];
	int Check = cGame_Settings.ResIndex;
	int min = 0;
	int max = cGame_Settings.DeviceResolutionsCount - 1;
	//-------------------------------------------------------------
	if(gGameState==0)
	{
		SettingSlider(menusub,(float)cGame_Settings.ResIndex,(float)min,(float)max);
		if(gMenuSubId==menusub)
		{
			if(cGame_Controls.Input_Menu_Action_Right()){cGame_Settings.ResIndex++;}
			else if(cGame_Controls.Input_Menu_Action_Left()){cGame_Settings.ResIndex--;}
			else if(MouseSliderFloat((float)min,(float)max)){cGame_Settings.ResIndex = (int)fMouseValue;}
		}	
	}

	if(cGame_Settings.ResIndex >= max){cGame_Settings.ResIndex = max;}
	else if(cGame_Settings.ResIndex <= min){cGame_Settings.ResIndex = min;}

	if(Check != cGame_Settings.ResIndex)
	{
		gGfxOptimiserState = 2;
		cGame_Audio.Menu.MenuFx(6);
	}
	sprintf_s(Data,"%dx%d",cGame_Settings.DisplayWidth[cGame_Settings.ResIndex],cGame_Settings.DisplayHeight[cGame_Settings.ResIndex]);
	input = Data;
	return input;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_001 - AntiStropic Filtering
//******************************************************************
string Game_Menu::Setting_001(string &input,const int menusub)
{
	//-------------------------------------------------------------
	//int Check = cGame_Settings.Anisotropic_Level;
	char Data[16];
	//int min = 1;
	//int max = cGame_Settings.Anisotropic_Max_Level;
	//-------------------------------------------------------------
	sprintf_s(Data,"x%i",cGame_Settings.Anisotropic_Level);
	if(!cGame_Settings.bUse_Anisotrpic_Filter){input = "Off";}
	else{input = Data;}

	//SettingSlider(menusub,(float)cGame_Settings.Anisotropic_Level,(float)min,(float)max);

	//if(gMenuSubId==menusub)
	//{
	//	if(cGame_Controls.Input_Menu_Action_Right() && cGame_Settings.Anisotropic_Level < max)
	//	{
	//		cGame_Settings.Anisotropic_Level *= 2;
	//	}
	//	else if(cGame_Controls.Input_Menu_Action_Left() && cGame_Settings.Anisotropic_Level > min)
	//	{
	//		cGame_Settings.Anisotropic_Level /= 2;
	//	}
	//	else if(MouseSliderFloat((float)min,(float)max))
	//	{
	//		cGame_Settings.Anisotropic_Level = (int)fMouseValue;
	//	}
	//}	

	//if(cGame_Settings.Anisotropic_Level <= min){cGame_Settings.Anisotropic_Level = min;cGame_Settings.bUse_Anisotrpic_Filter = false;}
	//else if(!cGame_Settings.bUse_Anisotrpic_Filter){cGame_Settings.bUse_Anisotrpic_Filter = true;}
	//else if(cGame_Settings.Anisotropic_Level >= max){cGame_Settings.Anisotropic_Level = max;}

	//if(Check != cGame_Settings.Anisotropic_Level)
	//{
	//	gGfxPreset = -1;
	//	cGame_Audio.Menu.MenuFx(0);
	//	cGame_Asset_Global_Texture.SamplerUpdate();
	//	cGame_Track.SamplerSet();
	//}
	return input;
	//-------------------------------------------------------------
}
//******************************************************************
///Setting_On_Off
//******************************************************************
string Game_Menu::Setting_On_Off(string &input,const int menusub,bool &InputBool)
{

	//-------------------------------------------------------------
	float min = 0.0f;
	float max = 1.0f;
	bool check = InputBool;
	//-------------------------------------------------------------
	if(gMenuId!=3)//Not gfx options, enable inputs
	{
		SettingSlider(menusub,(float)InputBool,min,max);
		if(gMenuSubId==menusub)
		{
			if(cGame_Controls.Input_Menu_Action_Right() || cGame_Controls.Input_Menu_Action_Left()){InputBool = !InputBool;}
			else if(MouseSliderFloat(min,max))
			{
				InputBool = true;
				if(fMouseValue<0.5f)
				{
					InputBool = false;
				}
			}
		}

		if(check != InputBool)
		{
			cGame_Audio.Menu.MenuFx(6);
			cGame_PostProcessing.Create();
		}
	}
	
	input = "Off";
	if(check){input = "Enabled";}

	return input;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_006 - Gamma Brightness
//******************************************************************
string Game_Menu::Setting_006(string &input,const int menusub)
{
	//-------------------------------------------------------------
	char Readout[16];
	float min = 0.6f;
	float max = 1.4f;
	float check = gUserGamma;
	SettingSlider(menusub,gUserGamma,min,max);
	//-------------------------------------------------------------
	int Value = (int)iFloatInterpolate(gUserGamma,min,max,-5.0f,5.0f);
	if(Value < -0){sprintf_s(Readout,"- %i",abs(Value));}
	else if(Value==0){sprintf_s(Readout,"  %i",abs(Value));}
	else{sprintf_s(Readout,"+ %i",abs(Value));}

	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right() && gUserGamma < max){gUserGamma += 0.02f;}
		else if(cGame_Controls.Input_Menu_Action_Left() && gUserGamma > min){gUserGamma -= 0.02f;}
		else if(MouseSliderFloat(min,max)){gUserGamma = fMouseValue;}
	}

	if(gUserGamma <= min){gUserGamma = min;}
	else if(gUserGamma >= max){gUserGamma = max;}


	if(check != gUserGamma)
	{
		cGame_Audio.Menu.MenuFx(6);
	}

	input = Readout;
	return input;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_007 - Music Volume
//******************************************************************
string Game_Menu::Setting_007(string &input,const int menusub)
{
	//-------------------------------------------------------------
	char Readout[16];
	float min = 0.0f;
	float max = 0.7f;
	float Value = iFloatInterpolate(gVolumeMusic,min,max,0.0f,10.0f);
	SettingSlider(menusub,gVolumeMusic,(float)min,(float)max);
	//-------------------------------------------------------------
	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right() && gVolumeMusic < max){cGame_Audio.Menu.MenuFx(6);gVolumeMusic += 0.05f;}
		else if(cGame_Controls.Input_Menu_Action_Left() && gVolumeMusic > min){cGame_Audio.Menu.MenuFx(6);gVolumeMusic -= 0.05f;}
		else if(MouseSliderFloat(min,max)){gVolumeMusic = fMouseValue;}
	}

	sprintf_s(Readout,"%0.0f",Value);
	input = Readout;

	if(gVolumeMusic <= min){input = "Disabled";gVolumeMusic = min;}
	else if(gVolumeMusic >= max){input = "Max";gVolumeMusic = max;}

	return input;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_008 - SoundFX Volume
//******************************************************************
string Game_Menu::Setting_008(string &input,const int menusub,float &in_value)
{
	//-------------------------------------------------------------
	char Readout[16];
	float min = 0.0f;
	float max = 0.95f;
	float check = in_value;
	float Value = iFloatInterpolate(in_value,min,max,0.0f,10.0f);
	SettingSlider(menusub,in_value,(float)min,(float)max);
	//-------------------------------------------------------------

	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right() && in_value < max){in_value += 0.05f;}
		else if(cGame_Controls.Input_Menu_Action_Left() && in_value > min){in_value -= 0.05f;}
		else if(MouseSliderFloat(min,max)){in_value = fMouseValue;}
	}

	sprintf_s(Readout,"%0.0f",Value);
	input = Readout;

	if(in_value <= min){input = "Disabled";in_value = min;}
	else if(in_value >= max){input = "Max";in_value = max;}

	if(check != in_value)
	{
		cGame_Audio.Menu.MenuFx(6);
	}

	return input;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_009 - Player Colour
//******************************************************************
string Game_Menu::Setting_009(string &input,const int menusub)
{
	//-------------------------------------------------------------
	char Readout[32];
	//-------------------------------------------------------------
	float min = 0.0f;
	float max = 359.9f;
	float Value = gBikeColourUserHSV;
	sprintf_s(Readout,"%0.0f",Value);
	SettingSlider(menusub,Value,min,max);

	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right()){cGame_Audio.Menu.MenuFx(6);gBikeColourUserHSV += 5.0f;}
		else if(cGame_Controls.Input_Menu_Action_Left()){cGame_Audio.Menu.MenuFx(6);gBikeColourUserHSV -= 5.0f;}
		//Mouse shizzle
		else if(MouseSliderFloat(min,max)){gBikeColourUserHSV = fMouseValue;}
		//cap
		if(gBikeColourUserHSV<min){gBikeColourUserHSV=min;}
		else if(gBikeColourUserHSV>max){gBikeColourUserHSV=max;}

		///Apply colour change
		static float check = 0.0f;
		if(check!=Value)
		{
			gBikeColourUser = HSVtoRGB(gBikeColourUserHSV);
			cGame_Bike[gAi_Max_Count].Colour.bSetupTargetColour = true;
			check = Value;
		}
	}

	input = Readout;

	return input;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_010 - Graphics Preset
//******************************************************************
//string Game_Menu::Setting_010(string &input,int &menusub)
//{
//	//-------------------------------------------------------------
//	int Check = gGfxPreset;
//	int min = 0;
//	int max = 4;
//	SettingSlider(menusub,(float)gGfxPreset,(float)min,(float)max);
//	//-------------------------------------------------------------
//
//	if(gMenuSubId==menusub)
//	{
//		if(cGame_Controls.Input_Menu_Action_Right() && gGfxPreset < 4){cGame_Audio.Menu.MenuFx(0);gGfxPreset++;}
//		else if(cGame_Controls.Input_Menu_Action_Left() && gGfxPreset > 0){cGame_Audio.Menu.MenuFx(0);gGfxPreset--;}
//		else if(MouseSliderFloat((float)min,(float)max)){gGfxPreset = (int)fMouseValue;}
//	}
//
//	if(gGfxPreset < 0)
//	{
//		input = "Custom";
//		gGfxPreset = -1;
//	}
//	else if(gGfxPreset==0)
//	{
//		input = "Minimal";
//		gGlowEnable = false;
//		gDoFEnable = false;
//		gBlurEnable = false;
//		gFxaaEnable = false;
//		cGame_Settings.Anisotropic_Level = 1;
//		cGame_Settings.bUse_Anisotrpic_Filter = false;
//	}
//	else if(gGfxPreset==1)
//	{
//		input = "Low";
//		gGlowEnable = true;
//		gDoFEnable = false;
//		gBlurEnable = false;
//		gHbaoEnable = false;
//		gFxaaEnable = false;
//		cGame_Settings.Anisotropic_Level = 1;
//		cGame_Settings.bUse_Anisotrpic_Filter = false;
//	}
//	else if(gGfxPreset==2)
//	{
//		input = "Normal";
//		gGlowEnable = true;
//		gDoFEnable = true;
//		gBlurEnable = false;
//		gHbaoEnable = false;
//		gFxaaEnable = false;
//		cGame_Settings.Anisotropic_Level = 2;
//		cGame_Settings.bUse_Anisotrpic_Filter = true;
//	}
//	else if(gGfxPreset==3)
//	{
//		input = "High";
//		gGlowEnable = true;
//		gDoFEnable = true;
//		gBlurEnable = true;
//		gHbaoEnable = false;
//		gFxaaEnable = true;
//		cGame_Settings.Anisotropic_Level = 2;
//		cGame_Settings.bUse_Anisotrpic_Filter = true;
//	}
//	else if(gGfxPreset==4)
//	{
//		input = "Max";
//		gGlowEnable = true;
//		gDoFEnable = true;
//		gBlurEnable = true;
//		gHbaoEnable = true;
//		gFxaaEnable = true;
//		if(cGame_Settings.Anisotropic_Max_Level >= 4){cGame_Settings.Anisotropic_Level = 4;}
//		cGame_Settings.bUse_Anisotrpic_Filter = true;
//	}
//	else
//	{
//		gGfxPreset = 4;
//	}
//
//	if(Check != gGfxPreset)
//	{
//		cGame_Audio.Menu.MenuFx(0);
//		cGame_Asset_Global_Texture.SamplerUpdate();
//		cGame_Track.SamplerSet();
//		cGame_PostProcessing.Reset();
//	}
//
//	return input;
//	//-------------------------------------------------------------
//}
//******************************************************************
///SETTING_011 - AI Total Active
//******************************************************************
string Game_Menu::Setting_011(string &input,const int menusub)
{
	//-------------------------------------------------------------
	//AI TOTAL NUMBER
	//-------------------------------------------------------------
	int Check = gAi_UserChange;
	char Readout[16];
	int min = 7;
	int max = MAX_BIKE_AI_COUNT;
	//Network cap to 19
	if(iNetworkIsActive())
	{
		max = MAX_BIKES_NET;
	}
	iIntCap(gAi_UserChange,min,max);
	SettingSlider(menusub,(float)gAi_UserChange,(float)min,(float)max);
	//-------------------------------------------------------------

	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right() && gAi_UserChange < max){gAi_UserChange++;}
		else if(cGame_Controls.Input_Menu_Action_Left() && gAi_UserChange > min){gAi_UserChange--;}
		else if(MouseSliderFloat((float)min,(float)max)){gAi_UserChange = (int)fMouseValue;}
		//-------------------------------------------------------------
		///Apply Sound
		if(Check != gAi_UserChange)
		{
			cGame_Audio.Menu.MenuFx(6);
		}
	}
	sprintf_s(Readout,"%i",gAi_UserChange);
	input = Readout;

	return input;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_012 - AI Difficulty Setting
//******************************************************************
string Game_Menu::Setting_012(const int menusub)
{
	//-------------------------------------------------------------
	int min = 0;
	int max = 4;
	int check = gAiDifficuty;
	SettingSlider(menusub,(float)gAiDifficuty,(float)min,(float)max);
	//-------------------------------------------------------------
	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right() && gAiDifficuty < max){gAiDifficuty++;}
		else if(cGame_Controls.Input_Menu_Action_Left() && gAiDifficuty > min){gAiDifficuty--;}
		else if(MouseSliderFloat((float)min,(float)max)){gAiDifficuty = (int)fMouseValue;}
		//-------------------------------------------------------------
		///Apply Sound/Text/Settings
		if(check != gAiDifficuty)
		{
			cGame_Audio.Menu.MenuFx(6);
		}
		if(gAiDifficuty <= min){gAiDifficutyMulti = 0.6f;}
		else if(gAiDifficuty==1){gAiDifficutyMulti = 0.8f;}
		else if(gAiDifficuty==2){gAiDifficutyMulti = 1.0f;}
		else if(gAiDifficuty==3){gAiDifficutyMulti = 1.1f;}
		else if(gAiDifficuty==max){gAiDifficutyMulti = 1.2f;}
		//if(gAiDifficuty <= min){gAiDifficutyMulti = 1.0f;}
		//else if(gAiDifficuty==1){gAiDifficutyMulti = 1.1f;}
		//else if(gAiDifficuty==2){gAiDifficutyMulti = 1.15f;}
		//else if(gAiDifficuty==3){gAiDifficutyMulti = 1.2f;}
		//else if(gAiDifficuty==max){gAiDifficutyMulti = 1.25f;}
	}
	
	return gInfoAiDifficulty;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_013 - Speed Class
//******************************************************************
string Game_Menu::Setting_013(const int menusub)
{
	//-------------------------------------------------------------
	int min = 0;
	int max = cGame_Upgrades.uSpeedClassUnlockPlayer;
	if(gGameModeChange==5)//arena cap to 250cc
	{
		max = 0;
		gSpeedClass = 0;
		SettingType[menusub] = 0;
	}
	int check = gSpeedClass;
	if(max>0)
	{
		SettingSlider(menusub,(float)gSpeedClass,(float)min,(float)max);
		//-------------------------------------------------------------
		if(gMenuSubId==menusub)
		{
			//-------------------------------------------------------------
			if(cGame_Controls.Input_Menu_Action_Right() && gSpeedClass < max){gSpeedClass++;}
			else if(cGame_Controls.Input_Menu_Action_Left() && gSpeedClass > min){gSpeedClass--;}
			else if(MouseSliderFloat((float)min,(float)max)){gSpeedClass = (int)fMouseValue;}
			//-------------------------------------------------------------
			///Apply Sound/Text/Settings
			if(check != gSpeedClass)
			{
				cGame_Audio.Menu.MenuFx(6);
				cGame_Ftp.CurrentRecord_Loaded = -1;
			}
		}
	}

	return gInfoSpeedClass;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_014 - Menu Colour
//******************************************************************
string Game_Menu::Setting_014(string &input,const int menusub)
{
	//-------------------------------------------------------------
	int min = 0;
	int max = 2;
	SettingSlider(menusub,(float)gMenuColour,(float)min,(float)max);
	//-------------------------------------------------------------
	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right() && gMenuColour < max){cGame_Audio.Menu.MenuFx(6);gMenuColour++;}
		else if(cGame_Controls.Input_Menu_Action_Left() && gMenuColour > min){cGame_Audio.Menu.MenuFx(6);gMenuColour--;}
		else if(MouseSliderFloat((float)min,(float)max)){gMenuColour = (int)fMouseValue;}
	}

	if(gMenuColour <= 0)
	{
		gMenuColour = 0; input = "Orange";
		gMenuFontColour	= D3DXVECTOR4(1.2f,0.5f,0.0f,1.0f);
		gMenuTrackColour = D3DXVECTOR3(1.76f,0.72f,0.48f);
	}
	else if(gMenuColour==1)
	{
		input = "Blue";
		gMenuFontColour	= D3DXVECTOR4(0.1f,0.7f,1.3f,1.0f);
		gMenuTrackColour = D3DXVECTOR3(0.48f,0.72f,1.76f);
	}
	else if(gMenuColour==2)
	{
		input = "Green";
		gMenuFontColour	= D3DXVECTOR4(0.4f,1.2f,0.4f,1.0f);
		gMenuTrackColour = D3DXVECTOR3(0.6f,1.33f,0.48f);
	}

	return input;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_015 - Race Mode Select
//******************************************************************
string Game_Menu::Setting_015(const int menusub)
{
	//-------------------------------------------------------------
	int min = 0;
	int max = 5;
	int check = gGameModeChange;
	SettingSlider(menusub,(float)gGameModeChange,(float)min,(float)max);
	//-------------------------------------------------------------
	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right() && gGameModeChange < max){gGameModeChange++;}
		else if(cGame_Controls.Input_Menu_Action_Left() && gGameModeChange > min){gGameModeChange--;}
		else if(MouseSliderFloat((float)min,(float)max)){gGameModeChange = (int)fMouseValue;}
		//-------------------------------------------------------------
		///Apply Sound/Text/Settings
		if(check != gGameModeChange)
		{
			cGame_Audio.Menu.MenuFx(6);
		}
	}

	return gInfoGameMode;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_016 - Track Select
//******************************************************************
string Game_Menu::Setting_016(const int menusub)
{
	//-------------------------------------------------------------
	int min = 1;
	int max = 3;//MAX_TRACK_POOL
	////Release build - remove phantom
	//if(gReleaseBuild)
	//{
	//	max = 2;
	//}
	//Arena Pool 10+
	if(gGameModeChange==5)
	{
		min = 10;
		max = 10;//MAX_ARENA_POOL
		gGameStateChange = 10;
		SettingType[menusub] = 0;
	}
	//Track Pool 1-10
	else if(gGameStateChange>=10)
	{
		gGameStateChange = 1;
	}

	int check = gGameStateChange;
	if((max-min)>0)
	{
		SettingSlider(menusub,(float)gGameStateChange,(float)min,(float)max);
		//-------------------------------------------------------------
		//Arena Override
		if(gMenuSubId==menusub)
		{
			if(cGame_Controls.Input_Menu_Action_Right() && gGameStateChange < max){gGameStateChange++;}
			else if(cGame_Controls.Input_Menu_Action_Left() && gGameStateChange > min){gGameStateChange--;}
			else if(MouseSliderFloat((float)min,(float)max)){gGameStateChange = (int)fMouseValue;}
			//-------------------------------------------------------------
			///Apply Sound/Text/Settings
			if(check != gGameStateChange)
			{
				cGame_Audio.Menu.MenuFx(6);
				cGame_Ftp.CurrentRecord_Loaded = -1;
			}
		}
	}

	return gInfoTrack;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_017 - Track Reverse
//******************************************************************
string Game_Menu::Setting_017(const int menusub)
{
	//-------------------------------------------------------------
	float min = 0.0f;
	float max = 1.0f;
	int check = gTrackReverse;
	SettingSlider(menusub,(float)gTrackReverse,min,max);
	//-------------------------------------------------------------
	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right() || cGame_Controls.Input_Menu_Action_Left()){gTrackReverse++; if(gTrackReverse>1){gTrackReverse=0;}}
		else if(MouseSliderFloat(min,max))
		{
			gTrackReverse = 1;
			if(fMouseValue<0.5f)
			{
				gTrackReverse = 0;
			}
		}
		//-------------------------------------------------------------
		///Apply Sound/Text/Settings
		if(check != gTrackReverse)
		{
			cGame_Audio.Menu.MenuFx(6);
			cGame_Ftp.CurrentRecord_Loaded = -1;
		}
	}

	return gInfoTrackReverse;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_018 - Prefered Camera
//******************************************************************
string Game_Menu::Setting_018(const int menusub)
{
	//-------------------------------------------------------------
	int min = 0;
	int max = 3;
	int check = gCam_PlayerPreset;
	SettingSlider(menusub,(float)gCam_PlayerPreset,(float)min,(float)max);
	//-------------------------------------------------------------
	if(gMenuSubId==menusub)
	{
		//-------------------------------------------------------------
		if(cGame_Controls.Input_Menu_Action_Right() && gCam_PlayerPreset < max){gCam_PlayerPreset++;}
		else if(cGame_Controls.Input_Menu_Action_Left() && gCam_PlayerPreset > min){gCam_PlayerPreset--;}
		else if(MouseSliderFloat((float)min,(float)max)){gCam_PlayerPreset = (int)fMouseValue;}
		//-------------------------------------------------------------
		///Apply Sound/Text/Settings
		if(check != gCam_PlayerPreset)
		{
			cGame_Audio.Menu.MenuFx(6);
		}
	}
	cGame_Camera.Mode_InGame = gCam_PlayerPreset;
	return gInfoPlayerCam;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_019 - Game Region
//******************************************************************
string Game_Menu::Setting_019(const int menusub)
{
	//-------------------------------------------------------------
	int min = 0;
	int max = gGameRegionMAX - 1;///eg: 2 regions = 0 or 1
	int check = gGameRegion;
	SettingSlider(menusub,(float)gGameRegion,(float)min,(float)max);
	//-------------------------------------------------------------
	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right() && gGameRegion < max){gGameRegion++;}
		else if(cGame_Controls.Input_Menu_Action_Left() && gGameRegion > min){gGameRegion--;}
		else if(MouseSliderFloat((float)min,(float)max)){gGameRegion = (int)fMouseValue;}
		//-------------------------------------------------------------
		///Apply Sound/Text/Settings
		if(check != gGameRegion)
		{
			cGame_Audio.Menu.MenuFx(6);
		}
	}

	return gGameRegionInfo;
	//-------------------------------------------------------------
}
//******************************************************************
///SETTING_020 - FeedBack 0-10
//******************************************************************
void Game_Menu::Setting_020(string &input,const int menusub,int &in_value)
{
	//-------------------------------------------------------------
	int min = 0;
	int max = 10;
	int check = in_value;
	SettingSlider(menusub,(float)in_value,(float)min,(float)max);
	//-------------------------------------------------------------
	if(gMenuSubId==menusub)
	{
		if(cGame_Controls.Input_Menu_Action_Right() && in_value < max){in_value++;}
		else if(cGame_Controls.Input_Menu_Action_Left() && in_value > min){in_value--;}
		else if(MouseSliderFloat((float)min,(float)max)){in_value = (int)fMouseValue;}
		//-------------------------------------------------------------
		///Apply Sound/Text/Settings
		if(check != in_value)
		{
			cGame_Audio.Menu.MenuFx(6);
		}
	}
	char buffer[24];
	if(in_value<=1)
	{
		sprintf_s(buffer,"%d | Poor",in_value);
	}
	else if(in_value<=3)
	{
		sprintf_s(buffer,"%d | Unhappy",in_value);
	}
	else if(in_value<=6)
	{
		sprintf_s(buffer,"%d | Average",in_value);
	}
	else if(in_value<=8)
	{
		sprintf_s(buffer,"%d | Great",in_value);
	}
	else if(in_value<=10)
	{
		sprintf_s(buffer,"%d | GlowTastic!",in_value);
	}
	//sprintf_s(buffer,"Rating - %d",in_value);
	input = buffer;
	//-------------------------------------------------------------
}
//******************************************************************
///TEXTINPUT
//******************************************************************
string Game_Menu::TextInput(string &input)
{
	//-------------------------------------------------------------
	//Lock Selection
	if(cGame_Controls.Input_Menu_Action_Select() && !gTextInputLock)
	{
		gTextInputLock = true;
	}
	else if(gTextInputLock)
	{
		int c = iTypedChar(true);
		//Enter Key
		if(c==-1)
		{
			cGame_Audio.Menu.MenuFx(2);
			gTextInputLock = false;
			if(input=="")
			{
				input = "Player";
			}
		}
		//Character Input
		if(c >= 40 && //http://www.theasciicode.com.ar/
			c <= 122 &&
			input.length() < 16)
		{
			cGame_Audio.Menu.MenuFx(0);

			input += " ";
			input[input.length()-1] = c;
		}
		//back-space
		if(iKeyClickAutoRepeat(VK_BACK,gMenu_Input_Init_Delay,gMenu_Input_Hold_Delay))
		{
			if(input.length() >= 1)
			{
				cGame_Audio.Menu.MenuFx(5);
				input.resize(input.length()-1);
			}
		}
	}
	return input;
	//-------------------------------------------------------------
}
///******************************************************************
///SETTING - SETTINGSLIDER
///******************************************************************
void Game_Menu::SettingSlider(const int index,const float value,const float min,const float max)
{
	//-------------------------------------------------------------
	//Return Offset for slider
	float scale = iFloatInterpolate(value,min,max,0.0f,fSliderOffsetMax);
	SettingType[index] = 1;
	iFloatTendTo2(SettingOffset[index],scale,7.0f);
	//-------------------------------------------------------------
}
///******************************************************************
///SETTING - DisplayRecords_Int
///******************************************************************
void Game_Menu::DisplayRecords_Int(string &value_1_name, 
								string &value_2_name, 
								unsigned long in_value_1_player, 
								unsigned long in_value_2_player,
								bool bTime_Value_1,
								bool bTime_Value_2)
{
	//-------------------------------------------------------------
	//Max Records Display
	const int MAX_RECORDS_DISPLAY = 20;
	//Location Data
	D3DXVECTOR2 vStartPos = D3DXVECTOR2(0.0f,7.0f);
	D3DXVECTOR2 vPosition = vStartPos;
	D3DXVECTOR4 vColour = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	bool bPlayerDisplayed = false;
	//-------------------------------------------------------------
	//Scroll up and down
	if(iKeyDown(VK_PRIOR))
	{
		gCurrentRecordViewed--;
	}
	else if(iKeyDown(VK_NEXT))
	{
		gCurrentRecordViewed++;
	}

	iIntCap(gCurrentRecordViewed,0,(MAX_RECORDS - MAX_RECORDS_DISPLAY));
	//-------------------------------------------------------------
	//Print Keys Info
	iPrint((char*)"Scroll Up   = Page_UP",cGame_Font.f16pt,&D3DXVECTOR2(5.0f,10.0f),&gFontGreyDark,gFont,false);
	iPrint((char*)"Scroll Down = Page_Down",cGame_Font.f16pt,&D3DXVECTOR2(5.0f,9.5f),&gFontGreyDark,gFont,false);
	iPrint((char*)"Find Me     = Page_Home",cGame_Font.f16pt,&D3DXVECTOR2(5.0f,9.0f),&gFontGreyDark,gFont,false);
	//-------------------------------------------------------------
	//Print Top Data
	iPrint((char*)"Rank",cGame_Font.f18pt,&vPosition,&gMenuFontColour,gFont,false);
	vPosition.x += 2.0f;
	iPrint((char*)"Name",cGame_Font.f18pt,&vPosition,&gMenuFontColour,gFont,false);
	vPosition.x += 5.0f;
	iPrint((char*)value_1_name.c_str(),cGame_Font.f18pt,&vPosition,&gMenuFontColour,gFont,false);
	vPosition.x += 3.0f;
	iPrint((char*)value_2_name.c_str(),cGame_Font.f18pt,&vPosition,&gMenuFontColour,gFont,false);
	//-------------------------------------------------------------
	//Print Bottom Data
	vStartPos.y -= 1.0f;
	vPosition = vStartPos;
	int DisplayIndex = 0;
	for(int i=0;i<MAX_RECORDS_DISPLAY;i++)
	{
		DisplayIndex = gCurrentRecordViewed + i;
		//Colour
		vColour = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
		if(cGame_PlayerStats.OnlineStats_Name[DisplayIndex]==(string)gPlayerName)
		{
			bPlayerDisplayed = true;
			vColour = D3DXVECTOR4(cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.x,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.y,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.z,1.0f);
		}
		//Position
		vPosition.x = vStartPos.x;
		sprintf_s(gCharBuffer,"- %d",DisplayIndex+1);
		iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);

		//Name
		vPosition.x += 2.0f;
		sprintf_s(gCharBuffer,"%s",(char*)cGame_PlayerStats.OnlineStats_Name[DisplayIndex].c_str());
		iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);

		//Value 1
		vPosition.x += 5.0f;
		if(bTime_Value_1)
		{
			unsigned long TotalSecondsInput = cGame_PlayerStats.OnlineStats_Int_Value_1[DisplayIndex];
			int Hours = 0;
			int Minutes = 0;
			while(TotalSecondsInput >= 60)
			{
				Minutes++;
				TotalSecondsInput -= 60;
			}
			while(Minutes>= 60)
			{
				Hours++;
				Minutes -= 60;				
			}
			sprintf_s(gCharBuffer,"%dh : %dm",Hours,Minutes);
			iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		}
		else
		{
			sprintf_s(gCharBuffer,"%d",cGame_PlayerStats.OnlineStats_Int_Value_1[DisplayIndex]);
			iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		}

		//Value 2
		vPosition.x += 3.0f;
		if(bTime_Value_2)
		{
			unsigned long TotalSecondsInput = cGame_PlayerStats.OnlineStats_Int_Value_2[DisplayIndex];
			int Hours = 0;
			int Minutes = 0;
			while(TotalSecondsInput >= 60)
			{
				Minutes++;
				TotalSecondsInput -= 60;
			}
			while(Minutes>= 60)
			{
				Hours++;
				Minutes -= 60;				
			}
			sprintf_s(gCharBuffer,"%dh : %dm",Hours,Minutes);
			iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		}
		else
		{
			sprintf_s(gCharBuffer,"%d",cGame_PlayerStats.OnlineStats_Int_Value_2[DisplayIndex]);
			iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		}
		///Nudge down
		vPosition.y -= 0.75f;
	}
	//Print player if not in scoreboard
	vPosition.y -= 0.75f;
	if(!bPlayerDisplayed)
	{
		vColour = D3DXVECTOR4(cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.x,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.y,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.z,1.0f);
		vPosition.x = vStartPos.x;

		//Try and find player record
		int PositionFound = -1;
		for(int i=0;i<MAX_RECORDS;i++)
		{
			if((string)gPlayerName==cGame_PlayerStats.OnlineStats_Name[i])
			{
				PositionFound = i;
				break;
			}
		}
		//Found
		if(PositionFound>=0)
		{
			sprintf_s(gCharBuffer,"- %d",PositionFound+1);
			iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
			//Press HOME to locate
			if(iKeyDown(VK_HOME))
			{
				gCurrentRecordViewed = PositionFound;
			}
		}
		//Not found
		else
		{
			iPrint((char*)"N/A",cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		}

		//Name
		vPosition.x += 2.0f;
		iPrint(gPlayerName,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		//value_1
		vPosition.x += 5.0f;
		if(bTime_Value_1)
		{
			unsigned long TotalSecondsInput = in_value_1_player;
			int Hours = 0;
			int Minutes = 0;
			while(TotalSecondsInput >= 60)
			{
				Minutes++;
				TotalSecondsInput -= 60;
			}
			while(Minutes>= 60)
			{
				Hours++;
				Minutes -= 60;				
			}
			sprintf_s(gCharBuffer,"%dh : %dm",Hours,Minutes);
			iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		}
		else
		{
			sprintf_s(gCharBuffer,"%d",in_value_1_player);
			iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		}
		//value_2
		vPosition.x += 3.0f;
		if(bTime_Value_2)
		{
			unsigned long TotalSecondsInput = in_value_2_player;
			int Hours = 0;
			int Minutes = 0;
			while(TotalSecondsInput >= 60)
			{
				Minutes++;
				TotalSecondsInput -= 60;
			}
			while(Minutes>= 60)
			{
				Hours++;
				Minutes -= 60;				
			}
			sprintf_s(gCharBuffer,"%dh : %dm",Hours,Minutes);
			iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		}
		else
		{
			sprintf_s(gCharBuffer,"%d",in_value_2_player);
			iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		}
	}
	//-------------------------------------------------------------
}
///******************************************************************
///SETTING - DisplayRecords_Float
///******************************************************************
void Game_Menu::DisplayRecords_Float(string &value_1_name)
{
	//-------------------------------------------------------------
	//Max Records Display
	const int MAX_RECORDS_DISPLAY = 20;
	//Location Data
	D3DXVECTOR2 vStartPos = D3DXVECTOR2(0.0f,7.0f);
	D3DXVECTOR2 vPosition = vStartPos;
	D3DXVECTOR4 vColour = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
	bool bPlayerDisplayed = false;
	//-------------------------------------------------------------
	//Scroll up and down
	if(iKeyDown(VK_PRIOR))
	{
		gCurrentRecordViewed--;
	}
	else if(iKeyDown(VK_NEXT))
	{
		gCurrentRecordViewed++;
	}

	iIntCap(gCurrentRecordViewed,0,(MAX_RECORDS - MAX_RECORDS_DISPLAY));
	//-------------------------------------------------------------
	//Print Keys Info
	iPrint((char*)"Scroll Up   = Page_UP",cGame_Font.f16pt,&D3DXVECTOR2(5.0f,10.0f),&gFontGreyDark,gFont,false);
	iPrint((char*)"Scroll Down = Page_Down",cGame_Font.f16pt,&D3DXVECTOR2(5.0f,9.5f),&gFontGreyDark,gFont,false);
	iPrint((char*)"Find Me     = Page_Home",cGame_Font.f16pt,&D3DXVECTOR2(5.0f,9.0f),&gFontGreyDark,gFont,false);
	//-------------------------------------------------------------
	//Print Top Data
	iPrint((char*)"Rank",cGame_Font.f18pt,&vPosition,&gMenuFontColour,gFont,false);
	vPosition.x += 2.0f;
	iPrint((char*)"Name",cGame_Font.f18pt,&vPosition,&gMenuFontColour,gFont,false);
	vPosition.x += 5.0f;
	iPrint((char*)value_1_name.c_str(),cGame_Font.f18pt,&vPosition,&gMenuFontColour,gFont,false);
	//-------------------------------------------------------------
	//Print Bottom Data
	vStartPos.y -= 1.0f;
	vPosition = vStartPos;
	int DisplayIndex = 0;
	for(int i=0;i<MAX_RECORDS_DISPLAY;i++)
	{
		DisplayIndex = gCurrentRecordViewed + i;
		//Colour
		vColour = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
		if(cGame_PlayerStats.OnlineStats_Name[DisplayIndex]==(string)gPlayerName)
		{
			bPlayerDisplayed = true;
			vColour = D3DXVECTOR4(cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.x,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.y,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.z,1.0f);
		}
		//Position
		vPosition.x = vStartPos.x;
		sprintf_s(gCharBuffer,"- %d",DisplayIndex+1);
		iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);

		//Name
		vPosition.x += 2.0f;
		sprintf_s(gCharBuffer,"%s",(char*)cGame_PlayerStats.OnlineStats_Name[DisplayIndex].c_str());
		iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);

		//Value 1
		vPosition.x += 5.0f;
		float fInput = cGame_PlayerStats.OnlineStats_Float_Value_1[DisplayIndex];
		int Minutes = 0;
		while(fInput >= 60.0f)
		{
			Minutes++;
			fInput -= 60.0f;
		}
		sprintf_s(gCharBuffer,"%d : %0.3f",Minutes,fInput);
		iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		///Nudge down
		vPosition.y -= 0.75f;
	}
	//Print player if not in scoreboard
	vPosition.y -= 0.75f;
	if(!bPlayerDisplayed)
	{
		vColour = D3DXVECTOR4(cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.x,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.y,cGame_Bike[gAi_Max_Count].Colour.vBikeColourTarget.z,1.0f);
		vPosition.x = vStartPos.x;

		//Try and find player record
		int PositionFound = -1;
		for(int i=0;i<MAX_RECORDS;i++)
		{
			if((string)gPlayerName==cGame_PlayerStats.OnlineStats_Name[i])
			{
				PositionFound = i;
				break;
			}
		}
		//Found
		if(PositionFound>=0)
		{
			sprintf_s(gCharBuffer,"- %d",PositionFound+1);
			iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
			//Press HOME to locate
			if(iKeyDown(VK_HOME))
			{
				gCurrentRecordViewed = PositionFound;
			}
		}
		//Not found
		else
		{
			iPrint((char*)"N/A",cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		}

		//Name
		vPosition.x += 2.0f;
		iPrint(gPlayerName,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
		//value_1
		vPosition.x += 5.0f;
		float fInput = cGame_PlayerStats.LapRecord[gGameStateChange][gSpeedClass][gTrackReverse];
		int Minutes = 0;
		while(fInput >= 60.0f)
		{
			Minutes++;
			fInput -= 60.0f;
		}
		sprintf_s(gCharBuffer,"%d : %0.3f",Minutes,fInput);
		iPrint(gCharBuffer,cGame_Font.f18pt,&vPosition,&vColour,gFont,false);
	}
	//-------------------------------------------------------------
}