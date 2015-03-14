#pragma once
//-----------------------------------------------------------------
//Part limits
#define MAX_SHOWROOM 4
#define MAX_TRACK_MESH 15
#define MAX_000 9
#define MAX_001 7
#define MAX_002 7
#define MAX_003 2
#define MAX_010 10

//Texture Limits
#define MAX_TEXTURES_TRACK 20
#define MAX_TEXTURES_TRACK_TYPES 4
#include "Game_Track_Clouds.h"
#include "Game_Track_Physx.h"
//-----------------------------------------------------------------
class Game_Track
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Class
		Game_Track_Clouds					Clouds;
		Game_Track_Physx					Physx;
		//---------------------------------------------------------
		//data
		MD5MESH*						Mesh_Track[MAX_TRACK_MESH];
		///Shadow controls
		int								Mesh_Track_ShadowType[MAX_TRACK_MESH];
		bool							Mesh_Track_ShadowDoubleSided[MAX_TRACK_MESH];
		//ShowRoom
		MD5MESH*						Mesh_ShowRoom[MAX_SHOWROOM];
		bool							bShowroom;
		//---------------------------------------------------------
		//constructors
		Game_Track(void);
		~Game_Track(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);

		void Showroom_Start(void);
		void Showroom_Stop(void);


		//-------------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Texture Pool
		TEXTURE2D*						Texture[MAX_TEXTURES_TRACK][MAX_TEXTURES_TRACK_TYPES];
												// (mesh)					(type) - 0=dm/em 1=nm 2=sm 3=rm
		//Video Texture
		TEXTURE2DVIDEO*					VideoTexture;
		//---------------------------------------------------------
		//functions
		void TexturesCreate(void);
		void TexturesDestroy(void);
		void SamplerSet(void);

		void Chapter_000_Menu_Main_Create(void);
		void Chapter_001_Volex_Create(void);
		void Chapter_002_Silence_Create(void);
		void Chapter_003_Phantom_Create(void);
		void Chapter_010_Rez_Create(void);

		void Chapter_000_Menu_Main_Update(void);
		void Chapter_001_Volex_Update(void);
		void Chapter_002_Silence_Update(void);
		void Chapter_003_Phantom_Update(void);
		void Chapter_010_Rez_Update(void);
	//-------------------------------------------------------------
};
