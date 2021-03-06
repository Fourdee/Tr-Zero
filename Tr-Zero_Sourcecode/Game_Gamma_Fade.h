#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Gamma_Fade
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		float								fGamma;
		float								fGammaFade;
		bool								bFadeIn;
		bool								bFadeOut;
		bool								bFadeActive;
		//---------------------------------------------------------
		//constructors
		Game_Gamma_Fade(void);
		~Game_Gamma_Fade(void);
		//---------------------------------------------------------
		//functions
		void Update(void);
		void FadeOut(void);
		void FadeIn(void);
		void Reset(void);
		//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//---------------------------------------------------------
	//-------------------------------------------------------------
};
