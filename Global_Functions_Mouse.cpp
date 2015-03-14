//-----------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------
///*****************************************************************
//GAME - GLOBAL - FUNCTION - MOUSE - RESET MOUSE DATA
///*****************************************************************
void MouseResetData(void)
{
	//-------------------------------------------------------------
	iMouseReset(&D3DXVECTOR2(0.5f,0.5f));
	MousePositionGet(&gMousePosition_Current);
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - MOUSE - MOUSE POS GET
///*****************************************************************
void MousePositionGet(D3DXVECTOR2* Mp)
{
	//-------------------------------------------------------------
	Mp->x = iMouseX()*32.0f-16.0f;
	Mp->y = 12.0f-iMouseY()*24.0f;
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - MOUSE - MOUSE ACTIVE
///*****************************************************************
void MouseActive(bool bMouseShown)
{
	//-------------------------------------------------------------
	if(bMouseShown)
	{
		//Enable
		MouseResetData();	
		gMouseEnabled = true;
		gMouseIsHidden = false;
		iWindowsMouseHide(gMouseIsHidden);
	}
	else
	{
		//Disable
		gMouseEnabled = false;
		gMouseIsHidden = true;
		iWindowsMouseHide(gMouseIsHidden);
		MouseResetData();	
	}
	//-------------------------------------------------------------
}
///*****************************************************************
//GAME - GLOBAL - FUNCTION - MOUSE - Slider Float
///*****************************************************************
bool MouseSliderFloat(float min,float max)
{
	//-------------------------------------------------------------
	bool bState = false;
	float fMovementThreshold = 2.0f;
	float left = (cGame_Menu.Font_MenuLocation[0].x + 5.0f) - fMovementThreshold;
	float right = (cGame_Menu.Font_MenuLocation[0].x + 5.0f) + (fMovementThreshold + cGame_Menu.fSliderOffsetMax);
	if(gMousePosition_Current.x >= left && gMousePosition_Current.x <= right)
	{
		if(iMouseButtonDown(VK_LBUTTON))
		{
			cGame_Menu.fMouseValue = iFloatInterpolate(gMousePosition_Current.x,left + fMovementThreshold,right - fMovementThreshold,min,max);
			bState = true;
		}
	}
	return bState;
	//-------------------------------------------------------------
}