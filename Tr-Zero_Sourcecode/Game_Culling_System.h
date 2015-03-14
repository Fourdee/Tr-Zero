#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Culling_System
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Active Mesh Triggers (for Game_Mesh)
		bool							bShell[40];
		bool							bGlow[40];
		bool							bRider[40];
		//---------------------------------------------------------
		//constructors
		Game_Culling_System(void);
		~Game_Culling_System(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//Data
		//---------------------------------------------------------
		//functions
		void ZeroData(void);
		void CullBikeAi(void);

		void iMeshImposterAutoHide(MD5MESH* Mesh,
                                D3DXVECTOR3* Location,
                                float fDistanceMax,
								int ImposterCount,
                                int MaxViewableMeshes);

	//-------------------------------------------------------------
};