//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
///*****************************************************************
void iVector2TendTo(D3DXVECTOR2* vSource, D3DXVECTOR2* vTarget, const float fSpeed)
{
	//-------------------------------------------------------------
	iFloatTendTo2(vSource->x,vTarget->x,fSpeed);
	iFloatTendTo2(vSource->y,vTarget->y,fSpeed);
	//-------------------------------------------------------------
}
void iVector3TendTo(D3DXVECTOR3* vSource, D3DXVECTOR3* vTarget, const float fSpeed)
{
	//-------------------------------------------------------------
	iFloatTendTo2(vSource->x,vTarget->x,fSpeed);
	iFloatTendTo2(vSource->y,vTarget->y,fSpeed);
	iFloatTendTo2(vSource->z,vTarget->z,fSpeed);
	//-------------------------------------------------------------
}
void iVector4TendTo(D3DXVECTOR4* vSource, D3DXVECTOR4* vTarget, const float fSpeed)
{
	//-------------------------------------------------------------
	iFloatTendTo2(vSource->x,vTarget->x,fSpeed);
	iFloatTendTo2(vSource->y,vTarget->y,fSpeed);
	iFloatTendTo2(vSource->z,vTarget->z,fSpeed);
	iFloatTendTo2(vSource->w,vTarget->w,fSpeed);
	//-------------------------------------------------------------
}
///*****************************************************************
void iPrint3(char* text,const float size,D3DXVECTOR2* vxy,D3DXVECTOR4* vcolour,FONT* font,const bool centre)
{
	//-------------------------------------------------------------
	//black
	D3DXVECTOR4 vBlack = D3DXVECTOR4(0.0f, 0.0f, 0.0f, vcolour->w);
	//Offset background shadow vec
	D3DXVECTOR2 vBg = *vxy;
	vBg.x += 0.025f;
	vBg.y -= 0.025f;
	//Print
	iPrint(text,size,&vBg,&vBlack,font,centre);
	iPrint(text,size,vxy,vcolour,font,centre);
	//-------------------------------------------------------------
}
///*****************************************************************
void iFrameRate2(void)
{
	//-------------------------------------------------------------
	//System clock timer
	float time = (float)clock() / (float)CLOCKS_PER_SEC;
	//Time delta 
	static float oldTime = 0.0f;
	float dt = time - oldTime;
	float fps = 1.0f / dt;
	oldTime = time;
	//Average results
	static float FpsAverage = 60.0f;
	iFloatTendTo2(FpsAverage,fps,15.0f);

	//gFps = (int)fps;
	gFps = (int)FpsAverage;
	//-------------------------------------------------------------
	//Print Out?
	//sprintf_s(gCharBuffer,"dt %0.2f",dt);
	//iPrint(gCharBuffer,cGame_Font.f24pt,&D3DXVECTOR2(0.0f,0.0f),&D3DXVECTOR4(1.0f,0.0f,0.0f,1.0f),gFont,false);
	//-------------------------------------------------------------
}
///*****************************************************************
D3DXVECTOR3 HSVtoRGB(float h) 
{ 
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	iFloatCap(h,0.0f,360.0f);

	if(h<120.0f)
	{
		///red = 0 < 120
		///green = 0 > 120
		///blue = 0
		r = iFloatInterpolateSmooth(h,0.0f,120.0f,gHsvMax,gHsvMin);
		g = iFloatInterpolateSmooth(h,0.0f,120.0f,gHsvMin,gHsvMax);
		b = gHsvMin;
	}
	else if(h<240.0f)
	{
		///red = 0
		///green = 120 < 240
		///blue = 120 > 240
		r = gHsvMin;
		g = iFloatInterpolateSmooth(h,120.0f,240.0f,gHsvMax,gHsvMin);
		b = iFloatInterpolateSmooth(h,120.0f,240.0f,gHsvMin,gHsvMax);
	}
	else
	{
		///red = 240 > 360
		///green = 0
		///blue = 240 < 360
		r = iFloatInterpolateSmooth(h,240.0f,360.0f,gHsvMin,gHsvMax);
		g = gHsvMin;
		b = iFloatInterpolateSmooth(h,240.0f,360.0f,gHsvMax,gHsvMin);
	}

	return D3DXVECTOR3(r, g, b);
}
///*****************************************************************
bool iProjectile_Floor(D3DXVECTOR3 &vInput,D3DXQUATERNION &qInput,const float In_Speed, const float In_Height)
{
	bool bOutput = false;
	///Follow Track Floor
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,0.0f,1.0f);
	D3DXVECTOR3 vScanDownCp = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 vScanDownCn = D3DXVECTOR3(0.0f,0.0f,0.0f);
	float fScanDown_DistanceCp = 0.0f;

	D3DXQUATERNION qScanDown;
	iQuaternionFromEulerAngles(&qScanDown,90.0f,0.0f,0.0f);
	iQuaternionMultiply(&qScanDown,&qScanDown,&qInput);
	//Sample Scan at output location
	D3DXVECTOR3 vScanOrigin = iVectorLocationOffset(&vInput,&qInput,&D3DXVECTOR3(0.0f,0.0f,In_Speed));

	if(iPhysxActorRaycastClosestStaticShape(cGame_Track.Physx.PhysxActor_Floor,
											&vScanOrigin,
											&qScanDown,
											25.0f,
											&vScanDownCp,
											&vScanDownCn,
											fScanDown_DistanceCp,
											true))
	{
		///---------------------
		/// Get Rotations, apply
		iVectorRotate(&vUp,&vUp,&qInput);
		D3DXQUATERNION qNewRotation;
		iQuaternionLookAt(&qNewRotation,&vScanDownCp,&(vScanDownCp+vScanDownCn),&vUp);
		D3DXQUATERNION qForward;
		iQuaternionFromEulerAngles(&qForward,-90.0f,180.0f,0.0f);
		iQuaternionMultiply(&qInput,&qForward,&qNewRotation);
		///---------------------
		/// Apply New height and movement
		float fTargetHeight = In_Height - fScanDown_DistanceCp;
		vInput = iVectorLocationOffset(&vInput,&qInput,&D3DXVECTOR3(0.0f,fTargetHeight,In_Speed));
		///move
		bOutput = true;
	}
	return bOutput;
}
///*****************************************************************
bool iVectorInFront(D3DXQUATERNION &qSource,D3DXVECTOR3 &vSource,D3DXVECTOR3 &vTarget)
{
	bool bOutput = false;

	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f,1.0f,0.0f);
	iVectorRotate(&vUp,&vUp,&qSource);
	D3DXQUATERNION q1;
	iQuaternionLookAt(&q1,&vSource,&vTarget,&vUp);

	D3DXVECTOR3 vAngle = D3DXVECTOR3(0.0f,0.0f,0.0f);
	iQuaternionDelta(&q1,&qSource,&q1);
	iQuaternionToEulerAngles(&q1,&vAngle);

	if(abs(vAngle.x) < 35.0f &&
		abs(vAngle.y) < 25.0f)
	{
		bOutput = true;
	}

	return bOutput;
}
///*****************************************************************
void ZeroData_Global_Net_Packets(void)
{
	//Network Data Packets
	for(int i=0;i<2000;i++)
	{
		gNetworkIntValue[i] = -1000;
	}
	for(int i=0;i<100;i++)
	{
		gNetworkVector3Value[i] = D3DXVECTOR3(0.0f,-5000.0f,0.0f);
	}
	for(int i=0;i<10;i++)
	{
		gNetworkStringValue[i] = "";
		cGame_Bike[i].Name = "No Connection";
	}
	///Networked player ReadySTates
	gNetMeReady = 0;
	for(int i=0;i<10;i++)
	{
		gNetPlayerReady[i] = 0;
	}
}
///*****************************************************************
void iFloatCap(float &input, const float min, const float max)
{
	if(input > max)
	{
		input = max;
	}
	else if(input < min)
	{
		input = min;
	}
}
///*****************************************************************
void iFloatDecimalCap(float &input)
{
	//Just cut to 2 decimal places.

	int DecimalCap = (int)(input * 100.0f);
	input = (float)(DecimalCap / 100.0f);
}
///*****************************************************************
void iIntCap(int &input, const int min, const int max)
{
	if(input > max)
	{
		input = max;
	}
	else if(input < min)
	{
		input = min;
	}
}
///*****************************************************************
float iScaleDurationAnimationFader(const int Input_Time, const int Input_Time_Max, const float fScale_Max)
{
	float fOutput = 0.0f;
	if(Input_Time <= 25)
	{
		fOutput = iFloatInterpolate((float)Input_Time,0.0f,25.0f,0.0f,fScale_Max);
	}
	else
	{
		int timeleft = Input_Time_Max - Input_Time;
		fOutput = iFloatInterpolate((float)timeleft,0.0f,25.0f,0.0f,fScale_Max);
	}
	return fOutput;
}
///*****************************************************************
//D3DXVECTOR3 ReflectY(void)
//
//D3DXVECTOR3 EnvMapFocus = D3DXVECTOR3(0.0f,0.0f,0.0f);
//D3DXVECTOR3 forwardVector = D3DXVECTOR3(0.0f,0.0f,0.0f);
//         
//iMeshLocation(Mesh,&EnvMapFocus);   
//
//////flat plane Reflect +/- X                        
////forwardVector = D3DXVECTOR3(-CameraLocation.x+(EnvMapFocus.x+EnvMapFocus.x),CameraLocation.y,CameraLocation.z); //surface at model centre(normals +/- x)
////flat plane Reflect +/- Y                        
//forwardVector = D3DXVECTOR3(cGame_Camera.vCamOutput.x,-cGame_Camera.vCamOutput.y+(EnvMapFocus.y+EnvMapFocus.y),cGame_Camera.vCamOutput.z); //surface at model centre(normals +/- y)
//////flat plane Reflect +/- Z                           
////forwardVector = D3DXVECTOR3(CameraLocation.x,CameraLocation.y,-CameraLocation.z+(EnvMapFocus.z+EnvMapFocus.z)); //surface at model centre(normals +/- z)

//*****************************************************************
//ODDITYENGINE - MATH - FLOAT TEND TO – ORIGINAL
//*****************************************************************
void iFloatTendTo2(float &TendValue, float TargetValue, float TendSpeed)
{
    //-------------------------------------------------------------
	//TendValue += (TargetValue - TendValue)/TendSpeed;
	TendValue += (TargetValue - TendValue) / TendSpeed;
    //-------------------------------------------------------------
}
////*****************************************************************
////STRING REPLACE
////*****************************************************************
//std::string ReplaceString(std::string subject, const std::string& search,
//                          const std::string& replace) 
//{
//    size_t pos = 0;
//    while ((pos = subject.find(search, pos)) != std::string::npos) 
//	{
//         subject.replace(pos, search.length(), replace);
//         pos += replace.length();
//    }
//    return subject;
//}