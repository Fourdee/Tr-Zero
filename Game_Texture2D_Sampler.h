#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Texture2D_Sampler
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		//---------------------------------------------------------
		//constructors
		Game_Texture2D_Sampler(void);
		~Game_Texture2D_Sampler(void);
		//---------------------------------------------------------
		//functions
		void WrapSet(TEXTURE2D*);
		void ClampSet(TEXTURE2D*);
		void LinearMirrorSet(TEXTURE2D* );
		void LinearMirrorOnceSet(TEXTURE2D* );
		void LinearBorderSet(TEXTURE2D* ,D3DXVECTOR4* BorderColor);
		void AnisotropicMirrorSet(TEXTURE2D* );
		void AnisotropicMirrorOnceSet(TEXTURE2D* );
		void AnisotropicBorderSet(TEXTURE2D* ,D3DXVECTOR4* BorderColor);
		//Video Texture
		void VideoWrapSet(TEXTURE2DVIDEO*);
		void CubeWrapSet(TEXTURECUBE*);
	//-------------------------------------------------------------
};
