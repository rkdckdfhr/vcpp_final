#include "MoveThread.h"

int randNum = 0;			/// 랜덤으로 숫자를 받아 숫자로 방향 결정 1 = 상 ( x, y- ) , 2 = 하 ( x, y+ ) , 3 = 좌 ( x-, y ) , 4 = 우 ( x+, y )



DWORD WINAPI MoveThread(LPVOID param)
{
	/// 4방향으로 회전을 하기 위해 필요한 랜덤 변수 생성
	srand(time(NULL));
	randNum = rand() % 4 + 1;

	/// 스레드에 필요한 매개변수 구조체로 받기
	PTINFO ptrParam = (PTINFO)param;

	HDC hdc = GetDC(ptrParam->hWnd);

	while (true)
	{
		if (1 == randNum)
		{
			Rectangle(hdc, ptrParam->hitBox.left, ptrParam->hitBox.top - HIT_SIZE, ptrParam->hitBox.right, ptrParam->hitBox.top);
		}
		else if (2 == randNum)
		{
			break;
		}
		else if (3 == randNum)
		{
			break;
		}
		else
		{
			break;
		}
		Sleep(1500);
		randNum = rand() % 4 + 1;

		InvalidateRect(ptrParam->hWnd, NULL, TRUE);
	}

	ReleaseDC(ptrParam->hWnd, hdc);

	ExitThread(0);
	return 0;
}