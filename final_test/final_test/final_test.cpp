// final_test.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "final_test.h"

#define MAX_LOADSTRING 100

#include "Function.h"
#include "MoveThread.h"
#include <time.h>



// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FINALTEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FINALTEST));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FINALTEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FINALTEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 1650, 920, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
// 





/// 움직이거나 이벤트가 발생하는 객체들 생성 ex ) 캐릭터, 풀숲 등

RECT player;            /// 게임을 플레이하는 자신 객체

RECT enemy;             /// 게임에 나오는 상대에 대한 객체
RECT enemy2;

RECT hitArea;           /// 상대의 시야 범위 ( 마주치면 배틀 )에 대한 객체
RECT hitArea2;         

RECT gameScreen;        /// 실제 게임이 이루어지는 화면
RECT statUi;            /// 캐릭터 정보가 나올 UI 화면



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
    {
        PlayerMove(wParam, hWnd, &player);
        InvalidateRect(hWnd, NULL, TRUE);
    }
        break;

    case WM_LBUTTONDOWN:
    {
        //TINFO threadInfo = { 0, };
        //threadInfo.hWnd = hWnd;
        //threadInfo.hitBox = enemy;

        TINFO threadInfo = { 0, };
        threadInfo.hWnd = hWnd;
        threadInfo.hitBox = enemy;

        CreateThread(NULL, 0, MoveThread, (LPVOID)&threadInfo, 0, NULL);
    }
        break;

    case WM_CREATE:
    {
        statUi.left = 0;
        statUi.top = 0;
        statUi.right = statUi.left + 2000;
        statUi.bottom = statUi.top + SCREEN_UI;

        player = CreateRect(player, 30, 700, 1);
        enemy = CreateRect(enemy, 250, 170, 1);
        enemy2 = CreateRect(enemy2, 1020, 750, 1);

        hitArea = CreateHit(&enemy);
        hitArea2 = CreateHit(&enemy2);



    }
        break;


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            HDC hdc = GetDC(hWnd);
            // TODO: 여기에 그리기 코드를 추가합니다...
            
            /// 게임 화면 객체들
            Rectangle(hdc, statUi.left, statUi.top, statUi.right, statUi.bottom);
            
            /// 내 객체
            Ellipse(hdc, player.left, player.top, player.right, player.bottom);
            
            /// 상대 객체
            Ellipse(hdc, enemy.left, enemy.top, enemy.right, enemy.bottom);
            Ellipse(hdc, enemy2.left, enemy2.top, enemy2.right, enemy2.bottom);
            
            /// 히트박스 객체
            //Rectangle(hdc, hitArea.left, hitArea.top, hitArea.right, hitArea.bottom);
            Rectangle(hdc, hitArea2.left, hitArea2.top, hitArea2.right, hitArea2.bottom);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
