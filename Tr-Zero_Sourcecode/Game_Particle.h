#pragma once
//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Game_Particle
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//Data
		bool						bExplosion_InUse[40];
		int							Explosion_Intensity[40];

		bool						bWeaponEmission_InUse[40];
		//---------------------------------------------------------
		//constructors
		Game_Particle(void);
		~Game_Particle(void);
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

		void Create_pExplosion(void);
		void Update_pExplosion(void);
		void Destroy_pExplosion(void);

		void Create_pWeaponEmission(void);
		void Update_pWeaponEmission(void);
		void Destroy_pWeaponEmission(void);

		void Create_pCTG_Quad(void);
		void Update_pCTG_Quad(void);
		void Destroy_pCTG_Quad(void);
		//---------------------------------------------------------
		//Data
		PARTICLE_CTG*				pCTG_Quad[40];
		D3DXVECTOR3					vCTG_Quad[40];

		MD5MESH*					pExplosion_Mesh;
		PARTICLE*					pExplosion[40];
		D3DXVECTOR3					vExplosion_Target[40];
		D3DXVECTOR3					vExplosion_TargetDirection[40];
		D3DXVECTOR4					vExplosion_Colour[40];
		D3DXVECTOR4					vExplosion_ColourEnd[40];

		PARTICLE*					pWeaponEmission[40];
		D3DXVECTOR3					vWeaponEmission_Target[40];
		D3DXVECTOR3					vWeaponEmission_TargetDirection[40];
		D3DXVECTOR4					vWeaponEmission_Colour[40];
		D3DXVECTOR4					vWeaponEmission_ColourEnd[40];

		//---------------------------------------------------------
	//-------------------------------------------------------------
};
