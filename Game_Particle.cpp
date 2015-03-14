//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Game_Particle.h"
//-----------------------------------------------------------------
Game_Particle::Game_Particle(void)
{
	//-------------------------------------------------------------
	pExplosion_Mesh = NULL;
	for(int i=0;i<40;i++)
	{
		//CTG triangle
		pCTG_Quad[i] = NULL;
		//Particles
		pExplosion[i] = NULL;
		pWeaponEmission[i] = NULL;
	}
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
}
Game_Particle::~Game_Particle(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - PARTICLE - CREATE
///*****************************************************************
void Game_Particle::Create(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	Create_pExplosion();
	Create_pCTG_Quad();		
	if(gWeaponsTrackEnable)
	{
		Create_pWeaponEmission();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - PARTICLE - UPDATE
///*****************************************************************
void Game_Particle::Update(void)
{
	//-------------------------------------------------------------
	Update_pCTG_Quad();
	Update_pExplosion();
	if(gWeaponsTrackEnable)
	{
		Update_pWeaponEmission();
	}
	//-------------------------------------------------------------
	////Optimise Particles
	//if(gET_DeltaTime>0.02f)
	//{
	//	for(int i=0;i<=gAi_Max_Count;i++)
	//	{
	//		///Kill
	//		iParticleReset(pExplosion[i]);
	//		iParticleReset(pWeaponEmission[i]);
	//	}
	//}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PARTICLE - CREATE pExplosion
///*****************************************************************
void Game_Particle::Create_pExplosion(void)
{
	//-------------------------------------------------------------
	D3DXQUATERNION qNull = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);

	pExplosion_Mesh = iMeshCreate("trzero_res\\md5mesh\\particle\\bike.md5mesh",gMeshSmoothing);
	iMeshScaleSet(pExplosion_Mesh,&D3DXVECTOR3(3.0f,1.0f,3.0f),false);
	//pExplosion_Mesh = iMeshFromBinaryCreate("trzero_res\\md5mesh\\bikes\\bike_carl\\shield_carl.bin");

	for(int i=0;i<=gAi_Max_Count;i++)
	{
		pExplosion[i] = iParticleCreate(gParticle_Explosion_MaxCreate,3,gTimeStep,true);
		iParticleLifeTimeSet(pExplosion[i],0.0f,0.8f,gTimeStep,true);
		iParticleGlowEnable(pExplosion[i],true);
		iParticleRenderModeSet(pExplosion[i],1,false);
		iParticleEmitterShapeMeshSet(pExplosion[i],
			pExplosion_Mesh,
			&qNull,0.6f);
		iParticleScaleSet(pExplosion[i],0.5f,0.15f);
		iParticleTextureSet(pExplosion[i],cGame_Asset_Global_Texture.Bike_Weapons.Particle_Explosion,NULL);
		iParticleAlphaToleranceSet(pExplosion[i],0.025f);
		iParticleDampingSet(pExplosion[i],0.7f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PARTICLE - CREATE pWeaponEmission
///*****************************************************************
void Game_Particle::Create_pWeaponEmission(void)
{
	//-------------------------------------------------------------
	D3DXQUATERNION qNull = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);

	for(int i=0;i<=gAi_Max_Count;i++)
	{
		pWeaponEmission[i] = iParticleCreate(35,2,gTimeStep,false);
		iParticleLifeTimeSet(pWeaponEmission[i],0.0f,0.5f,gTimeStep,true);
		iParticleGlowEnable(pWeaponEmission[i],true);
		iParticleRenderModeSet(pWeaponEmission[i],0,false);

		iParticleEmitterShapeSphereSet(pWeaponEmission[i],&qNull,&D3DXVECTOR3(0.0f,0.0f,0.0f),&D3DXVECTOR3(0.0f,0.0f,0.0f),0.0f,0.0f,0.0f);
		iParticleGravitySet(pExplosion[i],&D3DXVECTOR3(0.0f,0.0f,0.0f));
		iParticleScaleSet(pWeaponEmission[i],1.25f,0.25f);
		iParticleTextureSet(pWeaponEmission[i],cGame_Asset_Global_Texture.Bike_Weapons.Particle_WeaponEmission,NULL);
		iParticleAlphaToleranceSet(pWeaponEmission[i],0.025f);
		iParticleDampingSet(pWeaponEmission[i],0.0f);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PARTICLE - UPDATE pExplosion
///*****************************************************************
void Game_Particle::Update_pExplosion(void)
{
	//-------------------------------------------------------------
	//pExplosion (weapon hits etc)
	const float fParticleEmitForce = 1.25f;//0.65f
	const float fParticleGravityForce = -0.25f;//-0.5f 0.3f
	//-------------------------------------------------------------
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		///Doesnt need to be set each loop
		iParticlePauseSet(pExplosion[i],!gBikesGo);
		//Update particle system
		///Always update (location/direction etc)
		vExplosion_Target[i] = cGame_Mesh.Animator.vBike[i];
		vExplosion_TargetDirection[i] = D3DXVECTOR3(0.0f,fParticleGravityForce - (cGame_Bike[i].Manager.vRotations.x / 50.0f),cGame_Bike[i].Manager.fAcceleration_Speed / 1.75f);
		iVectorRotate(&vExplosion_TargetDirection[i],&vExplosion_TargetDirection[i],&cGame_Bike[i].Manager.qBikeOutputLean);
		iParticleGravitySet(pExplosion[i],&vExplosion_TargetDirection[i]);
		///Cancel If under culling system
		if(!cGame_Mesh.Culling.bRider[i])
		{
			bExplosion_InUse[i] = false;
		}
		///Single Updates (only applied once per "bExplosion_InUse = true")
		else if(bExplosion_InUse[i])
		{
			iParticleEmitterShapeMeshSet(pExplosion[i],
				pExplosion_Mesh,
				&cGame_Mesh.Animator.qBike[i],
				fParticleEmitForce);
			vExplosion_Colour[i] = D3DXVECTOR4(cGame_Bike[i].Colour.vBikeColourTarget.x,cGame_Bike[i].Colour.vBikeColourTarget.y,cGame_Bike[i].Colour.vBikeColourTarget.z,1.0f);
			vExplosion_ColourEnd[i] = vExplosion_Colour[i];
			vExplosion_ColourEnd[i].w = 0.25f;
			iParticleColorSet(pExplosion[i],&vExplosion_Colour[i],&vExplosion_ColourEnd[i]);
		}
		iParticleEmit(pExplosion[i],&vExplosion_Target[i],Explosion_Intensity[i],1.0f,bExplosion_InUse[i]);
		bExplosion_InUse[i] = false;
		Explosion_Intensity[i] = 0;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PARTICLE - UPDATE pWeaponEmission
///*****************************************************************
void Game_Particle::Update_pWeaponEmission(void)
{
	//-------------------------------------------------------------
	//pExplosion (weapon hits etc)
	//const float fParticleEmitForce = 0.0f;
	//const float fParticleGravityForce = 0.0f;
	//-------------------------------------------------------------
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		///Doesnt need to be set each loop
		iParticlePauseSet(pWeaponEmission[i],!gBikesGo);
		//Update particle system
		bWeaponEmission_InUse[i] = false;

		if(cGame_Bike[i].Weapons.bSecondaryInUse &&
			cGame_Bike[i].Weapons.SecondaryProjectileAliveTime > 10 &&
			iVectorLength(&(cGame_Bike[i].Weapons.vSecondaryProjectile-cGame_Camera.vCamOutput)) < 250.0f)
		{
			bWeaponEmission_InUse[i] = true;
			vExplosion_Target[i] = cGame_Bike[i].Weapons.vSecondaryProjectile;
			vWeaponEmission_Colour[i] = D3DXVECTOR4(cGame_Bike[i].Colour.vBikeColourTarget.x,cGame_Bike[i].Colour.vBikeColourTarget.y,cGame_Bike[i].Colour.vBikeColourTarget.z,0.85f);
			vWeaponEmission_ColourEnd[i] = vExplosion_Colour[i];
			vWeaponEmission_ColourEnd[i].w = 0.25f;
			iParticleColorSet(pWeaponEmission[i],&vWeaponEmission_Colour[i],&vWeaponEmission_ColourEnd[i]);
		}
		iParticleEmit(pWeaponEmission[i],&vExplosion_Target[i],1,4.0f,bWeaponEmission_InUse[i]);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PARTICLE - DESTROY pExplosion
///*****************************************************************
void Game_Particle::Destroy_pExplosion(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		iParticleDestroy(pExplosion[i]);
	}
	iMeshDestroy(pExplosion_Mesh);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PARTICLE - DESTROY pWeaponEmission
///*****************************************************************
void Game_Particle::Destroy_pWeaponEmission(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		iParticleDestroy(pWeaponEmission[i]);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PARTICLE - CREATE pCTG_Quad
///*****************************************************************
void Game_Particle::Create_pCTG_Quad(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		//CTG
		//iParticleCollisionTriangleGroupFileFromMeshCreate(cGame_Mesh.Bike_Weapons.Targeting,"trzero_res\\md5mesh\\particle\\CTG.bin",0.0f,10.0f *(1.0f/60.0f));
		pCTG_Quad[i] = iParticleCTGCreate("trzero_res\\md5mesh\\particle\\CTG.bin");
		iParticleCollisionTriangleEnable(pExplosion[i],true);
		iParticleCollisionTriangleGroupAdd(pExplosion[i],pCTG_Quad[i]);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PARTICLE - UPDATE pCTG_Quad
///*****************************************************************
void Game_Particle::Update_pCTG_Quad(void)
{
	//-------------------------------------------------------------
	//Update Particle Collision
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		vCTG_Quad[i] = iVectorLocationOffset(&cGame_Bike[i].Manager.vBikeOutput,&cGame_Bike[i].Manager.qBikeOutput,&D3DXVECTOR3(0.0f,-1.6f,0.0f));
		iParticleCTGLocationSet(pCTG_Quad[i],&vCTG_Quad[i]);
		iParticleCTGOrientationSet(pCTG_Quad[i],&cGame_Bike[i].Manager.qBikeOutput);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - PARTICLE - DESTROY pCTG_Quad
///*****************************************************************
void Game_Particle::Destroy_pCTG_Quad(void)
{
	//-------------------------------------------------------------
	//CTG triangle
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		iParticleCollisionTriangleGroupRemove(pExplosion[i],pCTG_Quad[i]);
		iParticleCTGDestroy(pCTG_Quad[i]);
	}
	//MessageBox(NULL,"Destroy Complete",NULL,NULL);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - PARTICLE - DESTROY
///*****************************************************************
void Game_Particle::Destroy(void)
{
	//-------------------------------------------------------------
	ZeroData();
	//-------------------------------------------------------------
	Destroy_pCTG_Quad();
	Destroy_pExplosion();
	if(gWeaponsTrackEnable)
	{
		Destroy_pWeaponEmission();
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - PARTICLE - ZERO DATA
///*****************************************************************
void Game_Particle::ZeroData(void)
{
	//-------------------------------------------------------------
	for(int i=0;i<40;i++)
	{
		vCTG_Quad[i]					= D3DXVECTOR3(0.0f,0.0f,0.0f);

		bExplosion_InUse[i]				= false;
		Explosion_Intensity[i]			= 1;
		vExplosion_Target[i]			= D3DXVECTOR3(0.0f,0.0f,0.0f);
		vExplosion_TargetDirection[i]	= D3DXVECTOR3(0.0f,0.0f,0.0f);
		vExplosion_Colour[i]			= D3DXVECTOR4(5.0f,0.0f,0.0f,1.0f);
		vExplosion_ColourEnd[i]			= D3DXVECTOR4(5.0f,1.0f,0.0f,0.25f);

		bWeaponEmission_InUse[i]			= false;
		vWeaponEmission_Target[i]			= D3DXVECTOR3(0.0f,0.0f,0.0f);
		vWeaponEmission_TargetDirection[i]	= D3DXVECTOR3(0.0f,0.0f,0.0f);
		vWeaponEmission_Colour[i]			= D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f);
		vWeaponEmission_ColourEnd[i]		= D3DXVECTOR4(0.0f,0.0f,0.0f,0.25f);
	}
	//-------------------------------------------------------------
}