#pragma once
//-----------------------------------------------------------------
// About: 
//
// name: "Global_Functions_ForwardDec_Mouse.h"
// 
// included in: "Global_Params.h"
// 
// usage: any function added to "Global_Functions_Mouse.cpp"
//		  we add the forward declarations here so the whole system can access them.
//
//-----------------------------------------------------------------
///*****************************************************************
//GLOBAL - FUNCTIONS - MOUSE
///*****************************************************************
void MouseResetData(void);
void MousePositionGet(D3DXVECTOR2* Mp);
void MouseActive(bool bMouseShown);
bool MouseSliderFloat(float min,float max);