#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Audio_Menu_Main
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//music
		SOUND*								BG_Music;
		//---------------------------------------------------------
		//constructors
		Game_Audio_Menu_Main(void);
		~Game_Audio_Menu_Main(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void MusicStart(void);
		void MusicStop(void);
		void Volume(void);
		void Destroy(void);
	//-------------------------------------------------------------
};
