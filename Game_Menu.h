#pragma once
//-----------------------------------------------------------------
//sub classes
//-----------------------------------------------------------------
class Game_Menu
{
	public:
		//---------------------------------------------------------
		//constructors
		Game_Menu(void);
		~Game_Menu(void);
		//---------------------------------------------------------
		//Sprite_TextMain
		SPRITE*								Sprite_TextMain;
		D3DXVECTOR4							vSprite_TextMainColour[10];
		//Sprite_TextSetting
		SPRITE*								Sprite_TextSetting;
		//Sprite_TextSlider
		SPRITE*								Sprite_TextSlider;
		//Sprite_TopBanner
		SPRITE*								Sprite_TopBanner;
		//Sprite_Upgrades
		SPRITE*								Sprite_Upgrades[4];
		//Sprite_Upgrades_Bottom
		SPRITE*								Sprite_Upgrades_Bottom;
		//Sprite_Controls
		SPRITE*								Sprite_Controls_Xbox;
		SPRITE*								Sprite_Controls_Keyboard;

		//Mouse
		float								fMouseValue;
		//Slider
		float								fSliderOffsetMax;
		//Menu States
		bool								bInitMenu;
		bool								bTextReady;
		bool								bPlayAnimationOut;
		bool								bPlayAnimationIn;
		//Main Font - 
		string								Text_Main[10];
		D3DXVECTOR4							Font_MenuColour[10];
		D3DXVECTOR2							Font_MenuLocation[10];
		float								Font_MenuHeightGap;
		float								Font_MenuSize[10];
		//Settings Font - 
		string								Text_Setting[10];
		D3DXVECTOR4							Font_SettingColour[10];
		float								Font_SettingSize[10];
		int									SettingType[10];
		float								SettingOffset[10];
		//---------------------------------------------------------
		//forward declarations
		void ZeroData(void);
		void Create(void);
		void Update(void);
		void Destroy(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Max Menu Sub
		int									MenuSub_Max;
		//Targets CONST
		D3DXVECTOR2							vMainTarget;
		//Header Text
		string								Text_Header;
		D3DXVECTOR4							Font_HeaderColour;
		D3DXVECTOR2							Font_HeaderLocation;
		//Menu Timers - Data
		int									TimerExit;
		int									TimerDelay;
		//---------------------------------------------------------
		//Functions
		void Update_Controls(void);
		void InitMenu(void);
		void Exit(void);
		void TextAnimationOut(void);
		void TextAnimationIn(void);
		void TextAnimationFinish(void);
		void PrintText(void);
		void HideSprites(void);
		void Net_LobbyReset(void);
		//Menu Pages
		void Menu_000(void);
		void Menu_001(void);
		void Menu_002(void);
		void Menu_003(void);
		void Menu_004(void);
		void Menu_005(void);
		void Menu_006(void);
		void Menu_007(void);
		void Menu_008(void);
		void Menu_009(void);
		void Menu_010(void);
		void Menu_011(void);
		void Menu_012(void);
		void Menu_013(void);
		void Menu_014(void);//Feedback Menu
		void Menu_015(void);//World Stats
		//Setting Readout
		string Setting_000(string &input,const int menusub);
		string Setting_001(string &input,const int menusub);
		string Setting_006(string &input,const int menusub);
		string Setting_007(string &input,const int menusub);
		string Setting_008(string &input,const int menusub,float &in_value);//Volumes
		string Setting_009(string &input,const int menusub);
		//string Setting_010(string &input,int &menusub);///Gfx preset
		string Setting_011(string &input,const int menusub);
		string Setting_012(const int menusub);
		string Setting_013(const int menusub);
		string Setting_014(string &input,const int menusub);
		string Setting_015(const int menusub);
		string Setting_016(const int menusub);
		string Setting_017(const int menusub);
		string Setting_018(const int menusub);
		string Setting_019(const int menusub);//Game Region
		void Setting_020(string &input,const int menusub,int &in_value);//Game Feedback 0-10
		string Setting_On_Off(string &input,const int menusub,bool &InputBool);
		//Setting Slider
		void SettingSlider(const int index,const float value,const float min,const float max);
		//Text Input
		string TextInput(string &input);
		//Upgrade Panels
		void UpgradePanel(const int index,int &upgradeID,const int upgradeINFO,const string &pretext,const string &desctext,const string &endtext);
		//Online Records
		///INT BASED
		void DisplayRecords_Int(string &value_1_name, 
								string &value_2_name, 
								unsigned long in_value_1_player, 
								unsigned long in_value_2_player,
								bool bTime_Value_1,
								bool bTime_Value_2);
		///FLOAT (EG: Laptimes)
		void DisplayRecords_Float(string &value_1_name);
		//---------------------------------------------------------
};