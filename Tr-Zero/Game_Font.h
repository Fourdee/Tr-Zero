#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Font
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		float									f12pt;
		float									f14pt;
		float									f16pt;
		float									f18pt;
		float									f20pt;
		float									f22pt;
		float									f24pt;
		float									f26pt;
		float									f28pt;
		float									f30pt;
		float									f32pt;
		float									f36pt;
		//---------------------------------------------------------
		//constructors
		Game_Font(void);
		~Game_Font(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Destroy(void);
		void ApplyFontScale(void);
		void ZeroData(void);
	//-------------------------------------------------------------
};
