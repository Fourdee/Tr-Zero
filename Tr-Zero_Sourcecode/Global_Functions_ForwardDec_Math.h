#pragma once
//-----------------------------------------------------------------
// About: 
//
// name: "Global_Functions_ForwardDec_Math.h"
// 
// included in: "Global_Params.h"
// 
//-----------------------------------------------------------------
///*****************************************************************
void iVector2TendTo(D3DXVECTOR2* vSource, D3DXVECTOR2* vTarget, const float fSpeed);
void iVector3TendTo(D3DXVECTOR3* vSource, D3DXVECTOR3* vTarget, const float fSpeed);
void iVector4TendTo(D3DXVECTOR4* vSource, D3DXVECTOR4* vTarget, const float fSpeed);
///*****************************************************************
void iPrint3(char* text,const float size,D3DXVECTOR2* vxy,D3DXVECTOR4* vcolour,FONT* font,const bool centre);
///*****************************************************************
void iFrameRate2(void);
///*****************************************************************
D3DXVECTOR3 HSVtoRGB(float h);
///*****************************************************************
bool iProjectile_Floor(D3DXVECTOR3 &vInput,D3DXQUATERNION &qInput,const float In_Speed, const float In_Height);
///*****************************************************************
bool iVectorInFront(D3DXQUATERNION &qSource,D3DXVECTOR3 &vSource,D3DXVECTOR3 &vTarget);
///*****************************************************************
void ZeroData_Global_Net_Packets(void);
///*****************************************************************
void iFloatCap(float &input, const float min, const float max);
///*****************************************************************
void iFloatDecimalCap(float &input);
///*****************************************************************
void iIntCap(int &input, const int min, const int max);
///*****************************************************************
float iScaleDurationAnimationFader(const int Input_Time, const int Input_Time_Max, const float fScale_Max);
///*****************************************************************
//*****************************************************************
//ODDITYENGINE - MATH - FLOAT TEND TO – ORIGINAL
//*****************************************************************
void iFloatTendTo2(float &TendValue, const float TargetValue, const float TendSpeed);
////*****************************************************************
////STRING REPLACE
////*****************************************************************
//extern std::string ReplaceString(std::string subject, const std::string& search,const std::string& replace);