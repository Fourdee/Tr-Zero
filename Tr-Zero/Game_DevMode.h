#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_DevMode
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		int						page;
		bool					bNewSelection;
		int						Current;
		//---------------------------------------------------------
		//constructors
		Game_DevMode(void);
		~Game_DevMode(void);
		//---------------------------------------------------------
		//functions
		void Update(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//functions
		void DevMode_Scanners(void);
		void DevMode_Visuals(void);
		void DevMode_Network(void);
		void DevMode_Controls(void);
		void DevMode_Camera(void);
		void DevMode_RaceTracker(void);
		void DevMode_AudioWeapons(void);
		void DevMode_AudioBikes(void);

		void Devmode_Save_Audio(void);
		void Devmode_Load_Audio(void);

		void DevMode_MeshAnimator(void);

		void DevMode_PointLight(void);
		void DevMode_DirectLight(void);

		void DevMode_Culling(void);

		void DevMode_Shadows(void);
	//-------------------------------------------------------------
};
