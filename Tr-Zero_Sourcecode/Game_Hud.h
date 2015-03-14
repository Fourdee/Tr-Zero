#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Hud
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Scoreboard
		bool							bScoreboard;
		//---------------------------------------------------------
		//constructors
		Game_Hud(void);
		~Game_Hud(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void ZeroData(void);
		void Destroy(void);

		void TimerReadOuts(char* name,float seconds,D3DXVECTOR2 vLocation);
		void Update_NetworkPlayerNamesHover(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Hud Sprites
		SPRITE*								Sprite;
		float								Sprite_Alpha;
		D3DXVECTOR2							vSprite;
		///Sprite_Utility_1
		SPRITE*								Sprite_Utility_0;
		SPRITE*								Sprite_Utility_1;
		///Sprite_Secondary_1
		SPRITE*								Sprite_Secondary_0;
		SPRITE*								Sprite_Secondary_1;
		//Weapon Icon Sprites
		SPRITE*								Sprite_Utility_Icon[4];
		SPRITE*								Sprite_Secondary_Icon[4];

		//Print Data
		float								fFontSize[4];
		float								fFontSizeTarget;
		//Player Crosshair
		SPRITE*								SpriteCrossHair;
		//Targeting
		SPRITE*								SpriteTar[2];
		float								SpriteTar_Orientation;
		D3DXVECTOR4							vSpriteTar_Colour[2];
		float								SpriteTar_Scale[2];
		D3DXVECTOR2							vSpriteTar;
		float								TendToTrackingSprite;
		//Kill Count 
		int									KillCountCheck;
		//Spectate Selector Data
		D3DXVECTOR2							vTarget_Crosshair;
		D3DXVECTOR3							vTarget_Colour;
		float								Target_Speed;
		float								Target_Energy;
		int									Target_Kills;
		int									Target_Deaths;
		int									Target_Position;
		int									Target_Laps;
		///Weapons
		int									Target_PrimaryHeat;
		int									Target_SecondaryWeaponType;
		int									Target_UtilityType;

		bool								Target_SecondaryCharging;
		int									Target_SecondaryChargingTime;
		int									Target_SecondaryChargingTimeMax;
		int									Target_UtilityTime;
		int									Target_UtilityTimeMax;
		//Killboard Data
		string								Killboard_Msg[4];
		int									Killboard_Timer[4];
		D3DXVECTOR3							vKillboard_Colour[4];
		//Fastest Lap
		int									Timer_FastestLap;
		//Scoreboard
		SPRITE*								Sprite_ScoreBoard;
		//---------------------------------------------------------
		//functions
		void Update_Hud_Sprite(bool bActive);
		void Update_Hud_Print(void);
		void Update_CrossHair(bool bActive);
		void Update_Targeting(bool bActive);
		void Update_Heat(bool bActive);
		void Update_SpectateSelector(void);
		void Update_WeaponsInfo(bool bActive);

		void KillBoard(void);

		void Update_LapTimers(void);

		void Update_Scoreboard(void);
		void Update_SpectateInfo(void);
	//-------------------------------------------------------------
};
