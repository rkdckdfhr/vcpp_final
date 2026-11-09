#pragma once

#include <windows.h>
#include <stdlib.h>
#include <time.h>


#define HIT_SIZE                        400             /// 상대 객체와 마주치게 하는 히트박스 사이즈


typedef struct threadInfo
{
	HWND		hWnd;
	RECT		hitBox;


} TINFO, * PTINFO;

/// 상대 객체의 히트박스 360도 회전을 위한 함수 \
		
DWORD WINAPI MoveThread(LPVOID param);