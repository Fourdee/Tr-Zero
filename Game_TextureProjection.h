#pragma once
//-----------------------------------------------------------------
#define MAX_TEXTURE_PROJECTION_SHADOW		1
//-----------------------------------------------------------------
class Game_TextureProjection
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		TEXTUREPROJECTION*				tpShadow[MAX_TEXTURE_PROJECTION_SHADOW];
		//---------------------------------------------------------
		//constructors
		Game_TextureProjection(void);
		~Game_TextureProjection(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
	//-------------------------------------------------------------
};
