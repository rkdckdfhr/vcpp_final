#include "Function.h"



RECT CreateRect(RECT rectParam, int left, int top, int objType)
{

    rectParam.left = left;
    rectParam.top = top;

    if (1 == objType)
    {
        rectParam.right = left + OBJECT_CHAR;
        rectParam.bottom = top + OBJECT_CHAR;
    }
    else if (2 == objType)
    {
        rectParam.right = left + OBJECT_TRAP;
        rectParam.bottom = top + OBJECT_TRAP;
    }
    else
    {
        rectParam.right = left + OBJECT_ITEM;
        rectParam.bottom = top + OBJECT_ITEM;
    }
    return rectParam;
}


RECT CreateHit(RECT* enemy)
{
    RECT Area;

    /// 첫 생성시 적의 위치가 위면 아래를 보게 아래면 위를 보게 선언
    /// 맵의 Y 좌표를 반으로 나눴을 때 중간 = 500
    /// 500 보다 낮으면 객체가 위에 존재
    if (enemy->top < 500)
    {
        Area.left = enemy->left;
        Area.top = enemy->bottom;
        Area.right = enemy->right;
        Area.bottom = Area.top + HIT_SIZE;
    }
    else
    {
        Area.left = enemy->left;
        Area.top = enemy->top - HIT_SIZE;
        Area.right = enemy->right;
        Area.bottom = enemy->top;
    }

    return Area;
}

void PlayerMove(WPARAM wParam, HWND hWnd, RECT *player)
{
    /// 캐릭터가 끊어지지 않게 이동 할 수 있게 반복문으로 이동
    RECT startPoint = *player;            /// 이동하기 전 시작점을 담은 구조체 변수

    if (VK_UP == wParam)
    {
        for (int i = 1; i <= 15; i++)
        {
            player->top = startPoint.top - i;
            player->bottom = player->top + OBJECT_CHAR;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            Sleep(MOVE_SPEED);
        }
    }

    else if (VK_DOWN == wParam)
    {
        for (int i = 1; i <= 15; i++)
        {
            player->top = startPoint.top + i;
            player->bottom = player->top + OBJECT_CHAR;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            Sleep(MOVE_SPEED);
        }
    }

    else if (VK_LEFT == wParam)
    {
        for (int i = 1; i <= 15; i++)
        {
            player->left = startPoint.left - i;
            player->right = startPoint.right - i;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            Sleep(MOVE_SPEED);
        }
    }

    else if (VK_RIGHT == wParam)
    {
        for (int i = 1; i <= 15; i++)
        {
            player->left = startPoint.left + i;
            player->right = startPoint.right + i;
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
            Sleep(MOVE_SPEED);
        }
    }
}
