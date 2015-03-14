#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Audio_Music
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//music
		SOUND*								BG_Music;
		SOUND*								Showroom_Music;
		bool								bShowroom;
		float								fInternal_Vol;
		//---------------------------------------------------------
		//constructors
		Game_Audio_Music(void);
		~Game_Audio_Music(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void MusicStart(void);
		void MusicStop(void);
		void Destroy(void);

		void Showroom_Start(void);
		void Showroom_Stop(void);

	//-------------------------------------------------------------
};
