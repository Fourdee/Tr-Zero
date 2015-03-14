//-----------------------------------------------------------------
// About:
//
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Gamma_Fade.h"
//-----------------------------------------------------------------
//*****************************************************************
//GAME - GAMMA FADE - CONSTRUCTORS
//*****************************************************************
Game_Gamma_Fade::Game_Gamma_Fade(void)
{
	//-------------------------------------------------------------
	fGammaFade = 0.0f;
	fGamma = 0.0f;
	bFadeIn = true;
	bFadeOut = false;
	bFadeActive = false;
	//-------------------------------------------------------------
}

Game_Gamma_Fade::~Game_Gamma_Fade(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
//*****************************************************************
//GAME - GAMMA FADE - UPDATE
//*****************************************************************
void Game_Gamma_Fade::Update(void)
{
	//-------------------------------------------------------------
	// Fade In
	if(bFadeOut)
	{
		FadeOut();	
	}
	else if(bFadeIn)
	{
		FadeIn();	
	}
	// Update Gamma runtime
	else
	{
		bFadeActive = false;
		iPostProcessColorCorrectionSet(gCamera,gUserGamma * gGammaMulti,gColourCorrection.y,gColourCorrection.z,gColourCorrection.w);
	}
	//-------------------------------------------------------------
}
//*****************************************************************
//GAME - GAMMA FADE - FADEOUT
//*****************************************************************
void Game_Gamma_Fade::FadeOut(void)
{
	//-------------------------------------------------------------
	//Setup fadeout data
	if(!bFadeActive)
	{
		fGammaFade = gUserGamma;
		bFadeActive = true;
	}
	//Being Fade
	else if(fGammaFade > 0.001f)
	{
		iFloatTendTo2(fGammaFade,0.0f,35.0f);
		iPostProcessColorCorrectionSet(gCamera,fGammaFade,gColourCorrection.y,gColourCorrection.z,gColourCorrection.w);
	}
	else
	{
		bFadeIn = true;
		bFadeOut = false;
		//Restart the loading process
		gDestroy = true;
	}
	//-------------------------------------------------------------
}
//*****************************************************************
//GAME - GAMMA FADE - FADEIN
//*****************************************************************
void Game_Gamma_Fade::FadeIn(void)
{
	//-------------------------------------------------------------
	//Setup fadein data
	if(!bFadeActive)
	{
		fGammaFade = 0.0f;
		bFadeActive = true;
	}
	//Being Fade in
	else if(fGammaFade < (gUserGamma * 0.95f))
	{
		iFloatTendTo2(fGammaFade,gUserGamma,50.0f);
		iPostProcessColorCorrectionSet(gCamera,fGammaFade,gColourCorrection.y,gColourCorrection.z,gColourCorrection.w);
	}
	else
	{
		bFadeOut = false;
		bFadeIn = false;
	}
	//-------------------------------------------------------------
}
//*****************************************************************
//GAME - GAMMA FADE - RESET
//*****************************************************************
void Game_Gamma_Fade::Reset(void)
{
	//-------------------------------------------------------------
	fGamma = 0.0f;
	//-------------------------------------------------------------
}