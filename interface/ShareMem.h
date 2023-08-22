#pragma once
/*
#define ProControl_Stop			0
#define ProControl_Start		1
#define ProControl_Pause		2

#define ProState_Stop			0
#define ProState_Start			1
#define ProState_Pause			2
#define ProState_Error			3
*/
class CMainShareMem
{
public:
	int iState;
	int iControl;
	int iCount;//
	int SampleT;
	BOOL bWindowShow;
	BOOL bProStart;
	char szProName[128];
	PROCESS_INFORMATION pi;
	BOOL bExitProcess;
};