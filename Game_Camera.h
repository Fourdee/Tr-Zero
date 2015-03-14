#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Camera
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Location/orientations
		D3DXVECTOR3							vCamOutput;
		D3DXVECTOR3							vCamOffset;
		D3DXVECTOR3							vCamLookAt;
		D3DXQUATERNION						qCamOutput;
		//Player Camera Settings
		D3DXVECTOR4							vPlayerCam[4];
		//Modes
		int									Mode_InGame;
		int									Mode_Menu;
		int									Mode_Paused;
		//Intro Extras
		int									Timer_Selected;
		int									Timer_Mode;
		//Spectate
		int									SpectateId;
		bool								bSpectate;
		//---------------------------------------------------------
		//constructors
		Game_Camera(void);
		~Game_Camera(void);
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
		void Create(void);
		void Update(void);
		void Destroy(void);
	//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Bike data
		D3DXVECTOR3							vTarget;
		D3DXQUATERNION						qTarget;
		float								TargetSpeed;
		float								SpeedClassMax;
		float								TargetLean;
		float								TargetSteering;
		int									SpeedState;
		bool								TargetRespawning;
		//Cam data
		float								fFov;
		float								fFovBoostExtra;
		float								ClipDistance_Min;
		float								ClipDistance_Max;
		float								TendToCam;
		float								TendToFov;
		float								fRotation_px;
		float								fRotation_py;
		float								fRotation_pz;
		//Orbit data
		float								fOrbitAngle;
		float								fOrbitDistance;
		//Current Camera Info
		int									CamInfo_Timer;
		int									CamInfo_TimerMax;
		string								CamInfo_Text;
		//---------------------------------------------------------
		//Functions
		void Mode_Selector(void);
		void Spectate_Selector(void);
		void Camera_Menu_Intro(void);
		void Camera_MenuPause(void);
		void Camera_InGame(void);
		void User_FreeView(void);
		void User_Orbit(void);
		void Upgrade_View(void);
		void Intro_Volex(bool bCreate);
		void Replay_Camera(void);
		void Intro_Countdown(void);
		void Network_Lobby(void);
	//-------------------------------------------------------------
};
