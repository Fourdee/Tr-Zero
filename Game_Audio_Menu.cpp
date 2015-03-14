//-----------------------------------------------------------------
// About:
//
// name: "Game_Audio_Menu.cpp:
//
// included in: "Game_Audio.h"
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
#include "Game_Audio_Menu.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - AUDIO - MENU - CONSTRUCTORS
///*****************************************************************
Game_Audio_Menu::Game_Audio_Menu(void)
{
	//-------------------------------------------------------------
	//Menu FX
	Menu_Up = NULL;
	Menu_Up_Volume = 0.35f;

	Menu_Down = NULL;
	Menu_Down_Volume = 0.35f;

	Menu_ValueChange = NULL;
	Menu_ValueChange_Volume = 0.4f;

	Start_Select = NULL;
	Start_Select_Volume = 0.45f;

	MenuBack = NULL;
	MenuBack_Volume = 0.4f;

	MenuSelect = NULL;
	MenuSelect_Volume = 0.4f;

	ChatRecieve = NULL;
	ChatRecieve_Volume = 0.45f;
	//-------------------------------------------------------------
}

Game_Audio_Menu::~Game_Audio_Menu(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MENU - CREATE
///*****************************************************************
void Game_Audio_Menu::Create(void)
{
	//-------------------------------------------------------------
	//Menu FX
	Menu_Up = iSoundCreate("trzero_res\\sound\\menu_eddie\\menu_select_up.wav",false);
	Menu_Down = iSoundCreate("trzero_res\\sound\\menu_eddie\\menu_select_down.wav",false);

	Menu_ValueChange = iSoundCreate("trzero_res\\sound\\menu_eddie\\menu_change_value.wav",false);

	Start_Select = iSoundCreate("trzero_res\\sound\\menu_eddie\\menu_select.wav",false);

	MenuBack = iSoundCreate("trzero_res\\sound\\menu_eddie\\menu_select_back.wav",false);

	MenuSelect = iSoundCreate("trzero_res\\sound\\menu_eddie\\menu_select.wav",false);

	ChatRecieve = iSoundCreate("trzero_res\\sound\\menu_eddie\\chat_recieve.wav",false);
	//Apply Volume
	Volume();
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MENU - MENU FX Play
///*****************************************************************
void Game_Audio_Menu::MenuFx(int index)
{
	//-------------------------------------------------------------
	//Menu FX
	///apply volumes
	Volume();

	///Play Sound
	if(index==0){iSoundStop(Menu_Up);iSoundPlay(Menu_Up,0,false);}
	else if(index==1){iSoundStop(MenuBack);iSoundPlay(MenuBack,0,false);}
	else if(index==2){iSoundStop(MenuSelect);iSoundPlay(MenuSelect,0,false);}
	else if(index==3)
	{
		if(iSoundPlaying(MenuSelect))
		{
			iSoundStop(MenuSelect);
		}
		iSoundPlay(Start_Select,0,false);
	}
	else if(index==4){iSoundStop(ChatRecieve);iSoundPlay(ChatRecieve,0,false);}
	else if(index==5){iSoundStop(Menu_Down);iSoundPlay(Menu_Down,0,false);}
	else if(index==6){iSoundStop(Menu_ValueChange);iSoundPlay(Menu_ValueChange,0,false);}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MENU - MENU FX STOP
///*****************************************************************
void Game_Audio_Menu::Stop(void)
{
	//-------------------------------------------------------------
	//Menu FX
	iSoundStop(Menu_Up);
	iSoundStop(Menu_Down);
	iSoundStop(Menu_ValueChange);
	iSoundStop(Start_Select);
	iSoundStop(MenuBack);
	iSoundStop(MenuSelect);
	iSoundStop(ChatRecieve);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MENU - VOLUME
///*****************************************************************
void Game_Audio_Menu::Volume(void)
{
	//-------------------------------------------------------------
	//Menu FX
	iSoundVolumeSet(Menu_Up,Menu_Up_Volume * gVolumeFx);
	iSoundVolumeSet(Menu_Down,Menu_Down_Volume * gVolumeFx);
	iSoundVolumeSet(Menu_ValueChange,Menu_ValueChange_Volume * gVolumeFx);

	iSoundVolumeSet(Start_Select,Start_Select_Volume * gVolumeFx);
	iSoundVolumeSet(MenuBack,MenuBack_Volume * gVolumeFx);
	iSoundVolumeSet(MenuSelect,MenuSelect_Volume * gVolumeFx);
	iSoundVolumeSet(ChatRecieve,ChatRecieve_Volume * gVolumeFx);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - AUDIO - MENU - DESTROY
///*****************************************************************
void Game_Audio_Menu::Destroy(void)
{
	//-------------------------------------------------------------
	//fx
	Stop();	
	iSoundDestroy(Menu_Up);
	iSoundDestroy(Menu_Down);
	iSoundDestroy(Menu_ValueChange);
	iSoundDestroy(Start_Select);
	iSoundDestroy(MenuBack);
	iSoundDestroy(MenuSelect);
	iSoundDestroy(ChatRecieve);
	//-------------------------------------------------------------
}