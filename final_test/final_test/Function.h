#pragma once

#include <Windows.h>

#define OBJECT_CHAR                     80              /// 나, 적 등 캐릭터에 대한 크기값 ( 좌상단 + 80 )
#define OBJECT_TRAP                     60              /// 잔디나 함정에 대한 크기값 ( 좌상단 + 60 )
#define OBJECT_ITEM                     40              /// 아이템에 대한 크기값 ( 좌상단 + 40 )
#define SCREEN_UI                       150             /// 캐릭터 정보창 Y 좌표
#define SCREEN_GAME                     850             /// 게임 화면 Y 좌표

#define MOVE_SPEED                      1               /// 캐릭터 이동속도 ( Sleep 함수에 사용 )

#define HIT_SIZE                        400             /// 상대 객체와 마주치게 하는 히트박스 사이즈

/// 객체 생성을 지원해주는 함수 \
    인수 설명 : RECT rectParam = 생성하고자 하는 객체 \
               int left, top = 객체의 좌상단 값 지정 \
               int objType = 1: 캐릭터  2: 함정(잔디)  3: 아이템 ( 기본값 3 )
RECT CreateRect(RECT rectParam, int left, int top, int objType = 3);


/// 상대 객체를 받아와 히트스캔 생성
RECT CreateHit(RECT* enemy);


/// 플레이어 객체의 이동을 실행하는 함수 \
    윈도우프로시저에서 wParam ( 키보드 정보 ) \
                     hWnd ( 화면 정보 ) \
                     player ( 현재 캐릭터의 위치 정보 )
/// MOVE_SPEED로 이동속도 결정
void PlayerMove(WPARAM wParam, HWND hWnd, RECT *player);



