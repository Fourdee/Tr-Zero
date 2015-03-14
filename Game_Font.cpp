//-----------------------------------------------------------------
// About:
//
// name: "Game_Font.cpp:
//
// included in: "Global_Data.cpp" accessed through "Global_Params.h"
//
// usage: Create our font for use in the game.
//		  Created at start up and destroyed on exit of the game.
//		  Accessed globaly with the handle gFont.
//
// device input: none.
//
// todo:
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Font.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - FONT - CONSTRUCTORS
///*****************************************************************
Game_Font::Game_Font(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}

Game_Font::~Game_Font(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FONT - CREATE
///*****************************************************************
void Game_Font::Create(void)
{
	//-------------------------------------------------------------
	gFont = iFontCreate("Ubuntu",
						DWRITE_FONT_WEIGHT_THIN,
						DWRITE_FONT_STYLE_NORMAL,
						DWRITE_FONT_STRETCH_ULTRA_CONDENSED,
						gCamera);

	gFont2 = iFontCreate("Neuropol",
						DWRITE_FONT_WEIGHT_NORMAL,
						DWRITE_FONT_STYLE_NORMAL,
						DWRITE_FONT_STRETCH_NORMAL,
						gCamera);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FONT - ApplyFontScale
///*****************************************************************
void Game_Font::ApplyFontScale(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	f12pt *= gFontScale;
	f14pt *= gFontScale;
	f16pt *= gFontScale;
	f18pt *= gFontScale;
	f20pt *= gFontScale;
	f22pt *= gFontScale;
	f24pt *= gFontScale;
	f26pt *= gFontScale;
	f28pt *= gFontScale;
	f30pt *= gFontScale;
	f32pt *= gFontScale;
	f36pt *= gFontScale;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - FONT - DESTROY
///*****************************************************************
void Game_Font::Destroy(void)
{
	//-------------------------------------------------------------
	iFontDestroy(gFont);
	iFontDestroy(gFont2);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - FONT - ZeroData
///*****************************************************************
void Game_Font::ZeroData(void)
{
	//-------------------------------------------------------------
	//Default Font scales
	f12pt = 12.0f;
	f14pt = 14.0f;
	f16pt = 16.0f;
	f18pt = 18.0f;
	f20pt = 20.0f;
	f22pt = 22.0f;
	f24pt = 24.0f;
	f26pt = 26.0f;
	f28pt = 28.0f;
	f30pt = 30.0f;
	f32pt = 32.0f;
	f36pt = 36.0f;
	//-------------------------------------------------------------
}