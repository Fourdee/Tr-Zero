#pragma once
//-----------------------------------------------------------------
#include "Game_Audio_Music.h"
#include "Game_Audio_Menu.h"
#include "Game_Audio_Bike.h"
#include "Game_Audio_Weapons.h"
#include "Game_Audio_Voices.h"
#include "Game_Audio_SoundBarrier.h"
//-----------------------------------------------------------------
class Game_Audio
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//sound - Menu - Music - Bikes - Voices
		Game_Audio_Music						Music;
		Game_Audio_Menu							Menu;
		Game_Audio_Bike							Bike_Fx;
		Game_Audio_Weapons						Weapons;
		Game_Audio_SoundBarrier					SoundBarrier;
		Game_Audio_Voices						Voice;
		//---------------------------------------------------------
		//constructors
		Game_Audio(void);
		~Game_Audio(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void MenuFx(int index);
		void Stop(void);
		void Destroy(void);


		float Freq_Doppler(D3DXVECTOR3 vInput);
		float Freq_Doppler2(D3DXVECTOR3 vInput, float fMaxRange);
		//---------------------------------------------------------
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//---------------------------------------------------------
	//-------------------------------------------------------------
};
