#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_LoadingScreen
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		SPRITE*								Sprite_LoadingScreen;
		string								LoadingStageInfo;
		bool								bLoadingScreen_Created;
		//---------------------------------------------------------
		Game_LoadingScreen(void);
		~Game_LoadingScreen(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		int									Tip_To_Display;
		//---------------------------------------------------------
		void ZeroData(void);
		void TipOfTheDay(void);
	//-------------------------------------------------------------
};
