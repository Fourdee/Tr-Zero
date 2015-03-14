//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
#include "Mesh_Animator.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - ASSET - GLOBAL - ANIMATOR - CONSTRUCTORS
///*****************************************************************
Mesh_Animator::Mesh_Animator(void)
{
	//-------------------------------------------------------------
	Create();
	//-------------------------------------------------------------
}

Mesh_Animator::~Mesh_Animator(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ASSET - GLOBAL - ANIMATOR - CREATE
///*****************************************************************
void Mesh_Animator::Create(void)
{
	//-------------------------------------------------------------
	//Crash System
	for(int i=0;i<40;i++)
	{
		vBike[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		vBike_Offset[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		vTarget[i] = D3DXVECTOR3(0.0f,0.0f,0.0f); 
		vTarget_Previous[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);

		qBike[i] = D3DXQUATERNION(0.0f,0.0f,0.0f,1.0f);
		qBike_Offset[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		qTarget[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		qTarget_Previous[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);

		Mode_Segment[i] = 0;
		Mode[i] = 0;
		Timer[i] = 0;
		Timer_MAX[i] = 0;
	}
	//Creator
	for(int i=0;i<MAX_SEGMENTS;i++)
	{
		vTarget_Creator[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		qTarget_Creator[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
		Timer_Creator_MAX[i] = 10;
	}
	bPlay = false;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ASSET - GLOBAL - ANIMATOR - UPDATE
///*****************************************************************
void Mesh_Animator::Update(void)
{
	//-------------------------------------------------------------
	//Activate 
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		///Daytona Flip
		if(abs(cGame_Bike[i].Manager.fCollision_px)>3.0f &&
			cGame_Bike[i].Manager.fAcceleration_Speed>3.5f)
		{
			Mode[i] = 1;
		}
		///High Speed Death
		if(!cGame_Bike[i].Energy.bAlive &&
			cGame_Bike[i].Manager.fAcceleration_Speed>4.0f)
		{
			Mode[i] = 2;
		}
	}
	//-------------------------------------------------------------
	//debug
	if(gDevMode)
	{
		if(iKeyClick(DIK_J))
		{
			for(int i=0;i<=gAi_Max_Count;i++)
			{
				Mode[i] = 1;
			}
		}
		if(iKeyClick(DIK_K))
		{
			for(int i=0;i<=gAi_Max_Count;i++)
			{
				Mode[i] = 2;
			}
		}
	}
	//-------------------------------------------------------------
	//System
	if(gBikesGo)
	{
		for(int i=0;i<=gAi_Max_Count;i++)
		{
			//if(Mode[i]==-1)//CREATOR
			//{
			//	///t
			//	Timer_MAX[i] = Timer_Creator_MAX[Mode_Segment[i]];
			//	///v
			//	vTarget[i] = vTarget_Creator[Mode_Segment[i]];
			//	qTarget[i] = qTarget_Creator[Mode_Segment[i]];
			//	///
			//	//Update previous vects/quats
			//	if(Mode_Segment[i]==0)
			//	{
			//		vTarget_Previous[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
			//		qTarget_Previous[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
			//	}
			//	else
			//	{
			//		vTarget_Previous[i] = vTarget_Creator[Mode_Segment[i]-1];
			//		qTarget_Previous[i] = qTarget_Creator[Mode_Segment[i]-1];
			//	}
			//	//Play
			//	if(!bPlay)
			//	{
			//		Timer[i] = Timer_Creator_MAX[Mode_Segment[i]];
			//		//NextSegment(i);
			//		UpdateSegments(i);
			//	}
			//	else if(bPlay)
			//	{
			//		NextSegment(i);
			//		UpdateSegments(i);
			//		Timer[i]++;
			//		if(Mode_Segment[gAi_Max_Count]>=MAX_SEGMENTS-1)
			//		{
			//			Mode_Segment[i] = 0;
			//			if(i==gAi_Max_Count)
			//			{
			//				bPlay = false;
			//			}
			//		}
			//	}
			//}
			if(Mode[i]==0)//Disabled - Reset / clear
			{
				vBike_Offset[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
				vTarget[i] = D3DXVECTOR3(0.0f,0.0f,0.0f); 
				vTarget_Previous[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);

				qBike_Offset[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
				qTarget[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);
				qTarget_Previous[i] = D3DXVECTOR3(0.0f,0.0f,0.0f);

				Timer[i] = 0;
				Mode_Segment[i] = 0;
				Timer_MAX[i] = 0;
			}
			else if(Mode[i]==1)
			{
				Animate_DaytonaFlip(i);
			}
			else if(Mode[i]==2)
			{
				Animate_HighSpeedDeath(i);
			}
		}
	}
	//-------------------------------------------------------------
	//Update Locations
	for(int i=0;i<=gAi_Max_Count;i++)
	{
		vBike[i] = iVectorLocationOffset(&cGame_Bike[i].Manager.vTargetMesh,&cGame_Bike[i].Manager.qBikeOutputLean,&vBike_Offset[i]);
		iQuaternionFromEulerAngles(&qBike[i],qBike_Offset[i].x,qBike_Offset[i].y,qBike_Offset[i].z);
		iQuaternionMultiply(&qBike[i],&qBike[i],&cGame_Bike[i].Manager.qBikeOutputLean);
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ASSET - GLOBAL - ANIMATOR - DESTROY
///*****************************************************************
void Mesh_Animator::Destroy(void)
{
	//-------------------------------------------------------------
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ASSET - GLOBAL - ANIMATOR - NextSegment
///*****************************************************************
void Mesh_Animator::NextSegment(const int index)
{
	//-------------------------------------------------------------
	if(Timer[index]>=Timer_MAX[index])
	{
		vTarget_Previous[index].x = vTarget[index].x;
		vTarget_Previous[index].y = vTarget[index].y;
		vTarget_Previous[index].z = vTarget[index].z;

		qTarget_Previous[index].x = qTarget[index].x;
		qTarget_Previous[index].y = qTarget[index].y;
		qTarget_Previous[index].z = qTarget[index].z;

		Mode_Segment[index]++;
		Timer[index] = 0;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ASSET - GLOBAL - ANIMATOR - LastSegment
///*****************************************************************
void Mesh_Animator::LastSegment(const int index)
{
	//-------------------------------------------------------------
	if(Timer[index]>=Timer_MAX[index])
	{
		Mode[index] = 0;
	}
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ASSET - GLOBAL - ANIMATOR - UpdateSegments
///*****************************************************************
void Mesh_Animator::UpdateSegments(const int index)
{
	//-------------------------------------------------------------
	vBike_Offset[index].x = iFloatInterpolate((float)Timer[index],0.0f,(float)Timer_MAX[index],vTarget_Previous[index].x,vTarget[index].x);
	vBike_Offset[index].y = iFloatInterpolate((float)Timer[index],0.0f,(float)Timer_MAX[index],vTarget_Previous[index].y,vTarget[index].y);
	vBike_Offset[index].z = iFloatInterpolate((float)Timer[index],0.0f,(float)Timer_MAX[index],vTarget_Previous[index].z,vTarget[index].z);

	qBike_Offset[index].x = iFloatInterpolate((float)Timer[index],0.0f,(float)Timer_MAX[index],qTarget_Previous[index].x,qTarget[index].x);
	qBike_Offset[index].y = iFloatInterpolate((float)Timer[index],0.0f,(float)Timer_MAX[index],qTarget_Previous[index].y,qTarget[index].y);
	qBike_Offset[index].z = iFloatInterpolate((float)Timer[index],0.0f,(float)Timer_MAX[index],qTarget_Previous[index].z,qTarget[index].z);
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ASSET - GLOBAL - ANIMATOR - Animate_DaytonaFlip
///*****************************************************************
void Mesh_Animator::Animate_DaytonaFlip(const int index)
{
	//-------------------------------------------------------------
	if(Mode_Segment[index]==0)
	{
		Timer_MAX[index]= 4;
		vTarget[index]= D3DXVECTOR3(-0.5f,0.0f,0.0f);
		qTarget[index]= D3DXVECTOR3(0.0f,-23.5f,-26.0f);
		if(Timer[index]==(Timer_MAX[index]-1))
		{
			cGame_Particle.bExplosion_InUse[index] = true;
			cGame_Particle.Explosion_Intensity[index] = (int)(gParticle_Explosion_AnimatorMaxEmit / 2.0f);
		}
		NextSegment(index);
	}
	else if(Mode_Segment[index]==1)
	{
		Timer_MAX[index]= 14;
		vTarget[index]= D3DXVECTOR3(1.4f,0.0f,0.0f);
		qTarget[index]= D3DXVECTOR3(0.0f,-59.2f,-59.2f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==2)
	{
		Timer_MAX[index]= 2;
		vTarget[index]= D3DXVECTOR3(0.6f,1.2f,0.0f);
		qTarget[index]= D3DXVECTOR3(0.0f,-47.5f,-26.0f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==3)
	{
		Timer_MAX[index]= 15;
		vTarget[index]= D3DXVECTOR3(0.0f,9.6f,0.0f);
		qTarget[index]= D3DXVECTOR3(0.0f,-160.4f,393.5f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==4)
	{
		Timer_MAX[index]= 23;
		vTarget[index]= D3DXVECTOR3(-1.9f,0.2f,0.0f);
		qTarget[index]= D3DXVECTOR3(0.0f,-228.0f,645.0f);
		if(Timer[index]==(Timer_MAX[index]-1))
		{
			cGame_Particle.bExplosion_InUse[index] = true;
			cGame_Particle.Explosion_Intensity[index] = (int)gParticle_Explosion_AnimatorMaxEmit;
		}
		NextSegment(index);
	}
	else if(Mode_Segment[index]==5)
	{
		Timer_MAX[index]= 12;
		vTarget[index]= D3DXVECTOR3(0.1f,5.8f,0.0f);
		qTarget[index]= D3DXVECTOR3(6.8f,-271.4f,903.0f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==6)
	{
		Timer_MAX[index]= 19;
		vTarget[index]= D3DXVECTOR3(0.3f,-0.4f,0.0f);
		qTarget[index]= D3DXVECTOR3(0.0f,-337.6f,1035.0f);
		if(Timer[index]==(Timer_MAX[index]-1))
		{
			cGame_Particle.bExplosion_InUse[index] = true;
			cGame_Particle.Explosion_Intensity[index] = (int)(gParticle_Explosion_AnimatorMaxEmit / 2.0f);
		}
		NextSegment(index);
	}
	else if(Mode_Segment[index]==7)
	{
		Timer_MAX[index]= 11;
		vTarget[index]= D3DXVECTOR3(0.2f,3.4f,0.0f);
		qTarget[index]= D3DXVECTOR3(-10.0f,-338.5f,1080.4f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==8)
	{
		Timer_MAX[index]= 13;
		vTarget[index]= D3DXVECTOR3(-0.2f,0.3f,0.0f);
		qTarget[index]= D3DXVECTOR3(-5.5f,-341.5f,1107.9f);
		if(Timer[index]==12)
		{
			cGame_Particle.bExplosion_InUse[index] = true;
			cGame_Particle.Explosion_Intensity[index] = (int)(gParticle_Explosion_AnimatorMaxEmit / 4.0f);
		}
		NextSegment(index);
	}
	else if(Mode_Segment[index]==9)
	{
		Timer_MAX[index]= 5;
		vTarget[index]= D3DXVECTOR3(0.3f,0.3f,0.0f);
		qTarget[index]= D3DXVECTOR3(1.0f,-348.5f,1091.9f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==10)
	{
		Timer_MAX[index]= 5;
		vTarget[index]= D3DXVECTOR3(0.1f,0.3f,0.0f);
		qTarget[index]= D3DXVECTOR3(-4.5f,-356.0f,1084.4f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==11)
	{
		Timer_MAX[index]= 4;
		vTarget[index]= D3DXVECTOR3(0.0f,0.0f,0.0f);
		qTarget[index]= D3DXVECTOR3(0.0f,-360.0f,1080.0f);
		LastSegment(index);
	}
	//UPDATE TIMER + APPLY
	UpdateSegments(index);
	Timer[index]++;
	//-------------------------------------------------------------
}
///*****************************************************************
///GAME - ASSET - GLOBAL - ANIMATOR - Animate_HighSpeedDeath
///*****************************************************************
void Mesh_Animator::Animate_HighSpeedDeath(const int index)
{
	//-------------------------------------------------------------
	if(Mode_Segment[index]==0)
	{
		Timer_MAX[index]= 15;
		vTarget[index]= D3DXVECTOR3(0.0f,10.0f,0.0f);
		qTarget[index]= D3DXVECTOR3(86.0f,0.0f,0.0f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==1)
	{
		Timer_MAX[index]= 20;
		vTarget[index]= D3DXVECTOR3(0.0f,4.1f,0.0f);
		qTarget[index]= D3DXVECTOR3(266.5f,0.0f,0.0f);
		if(Timer[index]==(Timer_MAX[index]-1))
		{
			cGame_Particle.bExplosion_InUse[index] = true;
			cGame_Particle.Explosion_Intensity[index] = (int)gParticle_Explosion_AnimatorMaxEmit;
		}
		NextSegment(index);
	}
	else if(Mode_Segment[index]==2)
	{
		Timer_MAX[index]= 15;
		vTarget[index]= D3DXVECTOR3(0.0f,10.0f,0.0f);
		qTarget[index]= D3DXVECTOR3(407.0f,0.0f,0.0f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==3)
	{
		Timer_MAX[index]= 20;
		vTarget[index]= D3DXVECTOR3(0.0f,1.7f,0.0f);
		qTarget[index]= D3DXVECTOR3(545.0f,0.0f,0.0f);
		if(Timer[index]==(Timer_MAX[index]-1))
		{
			cGame_Particle.bExplosion_InUse[index] = true;
			cGame_Particle.Explosion_Intensity[index] = (int)(gParticle_Explosion_AnimatorMaxEmit / 2.0f);
		}
		NextSegment(index);
	}
	else if(Mode_Segment[index]==4)
	{
		Timer_MAX[index]= 14;
		vTarget[index]= D3DXVECTOR3(0.0f,8.3f,0.0f);
		qTarget[index]= D3DXVECTOR3(631.5f,55.0f,21.5f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==5)
	{
		Timer_MAX[index]= 12;
		vTarget[index]= D3DXVECTOR3(0.0f,1.7f,0.0f);
		qTarget[index]= D3DXVECTOR3(746.0f,100.0f,51.5f);
		if(Timer[index]==(Timer_MAX[index]-1))
		{
			cGame_Particle.bExplosion_InUse[index] = true;
			cGame_Particle.Explosion_Intensity[index] = (int)(gParticle_Explosion_AnimatorMaxEmit / 2.0f);
		}
		NextSegment(index);
	}
	else if(Mode_Segment[index]==6)
	{
		Timer_MAX[index]= 15;
		vTarget[index]= D3DXVECTOR3(0.0f,2.9f,0.0f);
		qTarget[index]= D3DXVECTOR3(716.0f,89.4f,-20.5f);
		NextSegment(index);
	}
	else if(Mode_Segment[index]==7)
	{
		Timer_MAX[index]= 11;
		vTarget[index]= D3DXVECTOR3(0.0f,-0.3f,0.0f);
		qTarget[index]= D3DXVECTOR3(718.0f,89.9f,-55.0f);
		cGame_Particle.bExplosion_InUse[index] = true;
		cGame_Particle.Explosion_Intensity[index] = 2;
		NextSegment(index);
	}
	else if(Mode_Segment[index]==8)
	{
		Timer_MAX[index]= 24;
		vTarget[index]= D3DXVECTOR3(0.0f,-0.3f,0.0f);
		qTarget[index]= D3DXVECTOR3(719.5f,65.4f,-62.8f);
		cGame_Particle.bExplosion_InUse[index] = true;
		cGame_Particle.Explosion_Intensity[index] = 1;
		NextSegment(index);
	}
	else if(Mode_Segment[index]==9)
	{
		Timer_MAX[index]= 75;
		vTarget[index]= D3DXVECTOR3(0.0f,-0.1f,0.0f);
		qTarget[index]= D3DXVECTOR3(721.0f,26.4f,-84.0f);
		cGame_Particle.bExplosion_InUse[index] = true;
		cGame_Particle.Explosion_Intensity[index] = 1;
		NextSegment(index);
	}
	else if(Mode_Segment[index]==10)
	{
		Timer_MAX[index]= 205;
		vTarget[index]= D3DXVECTOR3(0.0f,-0.1f,0.0f);
		qTarget[index]= D3DXVECTOR3(721.0f,26.4f,-84.0f);
		LastSegment(index);
	}
	//UPDATE TIMER + APPLY
	UpdateSegments(index);
	Timer[index]++;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ASSET - ANIMATOR - Save
///*****************************************************************
void Mesh_Animator::Save(void)
{
	//-------------------------------------------------------------
	HANDLE hFile; 
	DWORD dwDone; 
	char filepath[1024];

	strcpy_s(filepath,"trzero_res\\settings\\devanimator.bin");
	iGlobalPathMake(filepath);

	hFile = CreateFile(filepath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		//---------------------------------------------------------
		for(int i=0;i<MAX_SEGMENTS;i++)
		{
			WriteFile(hFile,&vTarget_Creator[i],sizeof(D3DXVECTOR3),&dwDone,NULL);
			WriteFile(hFile,&qTarget_Creator[i],sizeof(D3DXVECTOR3),&dwDone,NULL);
			WriteFile(hFile,&Timer_Creator_MAX[i],sizeof(int),&dwDone,NULL);
		}
		//---------------------------------------------------------
		CloseHandle(hFile); 
	}
	//-------------------------------------------------------------
	//Create ini
	char TempString[1024];
	char TempStringx[1024];
	for(int i=0;i<MAX_SEGMENTS;i++)
	{
		sprintf_s(TempStringx,"%d",i);

		sprintf_s(TempString," %d;",Timer_Creator_MAX[i]);
		WritePrivateProfileString(TempStringx,"Timer_MAX[i] ",TempString,"trzero_res\\settings\\devanimator.ini");
		
		sprintf_s(TempString," D3DXVECTOR3(%0.1ff,%0.1ff,%0.1ff);",vTarget_Creator[i].x,vTarget_Creator[i].y,vTarget_Creator[i].z);
		WritePrivateProfileString(TempStringx,"vTarget[i] ",TempString,"trzero_res\\settings\\devanimator.ini");
		sprintf_s(TempString," D3DXVECTOR3(%0.1ff,%0.1ff,%0.1ff);",qTarget_Creator[i].x,qTarget_Creator[i].y,qTarget_Creator[i].z);
		WritePrivateProfileString(TempStringx,"qTarget[i] ",TempString,"trzero_res\\settings\\devanimator.ini");
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - ASSET - ANIMATOR - Load
///*****************************************************************
void Mesh_Animator::Load(void)
{
	//-------------------------------------------------------------
	HANDLE hFile; 
	DWORD dwDone; 
	char filepath[1024];

	strcpy_s(filepath,"trzero_res\\settings\\devanimator.bin");
	iGlobalPathMake(filepath);

	hFile = CreateFile(filepath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		//---------------------------------------------------------
		for(int i=0;i<MAX_SEGMENTS;i++)
		{
			ReadFile(hFile,&vTarget_Creator[i],sizeof(D3DXVECTOR3),&dwDone,NULL);
			ReadFile(hFile,&qTarget_Creator[i],sizeof(D3DXVECTOR3),&dwDone,NULL);
			ReadFile(hFile,&Timer_Creator_MAX[i],sizeof(int),&dwDone,NULL);
		}
		//---------------------------------------------------------
		CloseHandle(hFile); 
	}
	//bNewSelection = true;
	//-------------------------------------------------------------
}