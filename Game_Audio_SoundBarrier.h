#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Audio_SoundBarrier
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		float							fVolumeTarget[3];
		//---------------------------------------------------------
		//constructors
		Game_Audio_SoundBarrier(void);
		~Game_Audio_SoundBarrier(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Internal Volume
		float							fInternalVolume;
		//SFX
		SOUND*							s_SoundBarrier[3];
		float							fVolume[3];
		int								CurrentState;
		int								TimeInBarrier;
		//---------------------------------------------------------
		void ZeroData(void);
	//-------------------------------------------------------------
};
