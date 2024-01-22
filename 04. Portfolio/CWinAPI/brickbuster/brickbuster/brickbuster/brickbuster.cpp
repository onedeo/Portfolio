// brickbuster.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

//#ifdef UNICODE
//#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
//#endif

//#include "framework.h"
#include <iostream>
#include "brickbuster.h"
#include"Class.h"
#include <ctime>

#define MAX_LOADSTRING 100

#define QUANT 60
// >>: global variable : brickbuster
int stage; //0 begin screen, 1 enter name, 2 game, 3 finish
int level;
int color[4];
int brick_count;
Bricks brick[QUANT];
static Paddle pad;
static Ball ball;
UI ui;
int point;
TCHAR name[10];
int name_count;
// <<: global variable : brickbuster 


// >>: declare functions : brickbuster 
void Create_Level();
void Next_Stage();
void Ball_Hit();
// <<: declare functions : brickbuster

void Updates();

//>>: double buffering
void DrawBitmapDoubleBuffering(HDC hdc);
//<< double buffering



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

    // >>: starting setting
    srand(time(NULL));
    //set location
    for (int i = 0; i < QUANT; i++)
    {
        brick[i].set_Location(i);
    }
    //set color
    for (int i = 0; i < 4; i++)
    {
        color[i] = QUANT / 4;
    }
    Create_Level();
    RECT area = { rectView.left + default_gap_x - 10, rectView.top + 40,
                         rectView.right - default_gap_x + 10, rectView.bottom - 30 };
    ball.set_Area(area);
    ui.set_Area(area);

    // <<: starting setting;
    static int direction;
    SHORT right = GetKeyState(VK_RIGHT);
    SHORT left = GetAsyncKeyState(VK_LEFT);
    SHORT space = GetAsyncKeyState(VK_SPACE);

    clock_t start = clock();
    clock_t reset;
    int lod = 3;


    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BRICKBUSTER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BRICKBUSTER));

    MSG msg;

    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            right = GetKeyState(VK_RIGHT);
            left = GetAsyncKeyState(VK_LEFT);
            space = GetAsyncKeyState(VK_SPACE);
            if (right & 0x8000)
            {
                direction = 1;
                pad.Move_Right(direction);
            }
            else if (left & 0x8000) 
            {
                direction = -1;
                pad.Move_Right(direction);
            }
            else direction = 0;

            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            reset = clock();
           if (reset - start >= lod)
            {
                start = reset;
                Updates();
            }
        }
    }


    return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BRICKBUSTER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BRICKBUSTER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

HWND hWnd;

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      300, 50, 670, 630, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    //SetTimer(hWnd, TIMER1,60, NULL);

    static Paddle pad;
    static int direction;
    
    switch (message)
    {
        case WM_CREATE:
            {
                break;
            }
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
        case WM_KEYDOWN:
            {
                if (wParam == VK_SPACE&&ball.get_Start()==false)
                {
                    if (stage == 2)
                    {
                        ball.Start(1);
                        ball.Update(pad.get_Points());
                    }
                    else if (stage == 0)
                    {
                        stage = 1;
                    }
                    else if (stage == 1)
                    {
                        for (int i = name_count; i < 10; i++)
                            name[i] = 0;
                        stage = 2;
                    }
                }
                break;
            }
        case WM_CHAR:
            if (stage == 1)
            {
                if (wParam == VK_RETURN)
                {
                    for (int i = name_count; i < 10; i++)
                        name[i] = 0;
                    stage = 2;
                }
                else if (wParam == VK_BACK && name_count > 0)
                {
                    name_count--;
                    for (int i = name_count; i < 9; i++)
                    {
                        name[i] = '_';
                    }
                }
                else if (name_count < 9)
                {
                    char temp = wParam;
                    if (temp >= 'a' && temp <= 'z')
                        temp -= 'a' - 'A';
                    name[name_count++] = temp;
                    for (int i = name_count; i < 9; i++)
                    {
                        name[i] = '_';
                    }
                }
            }
            if (stage == 3)
            {
                if (wParam == '1')
                {
                    stage = 0;
                    ball.set_Life(3);
                }
                else if (wParam == '2')
                {
                    exit(1);
                }
            }
                
            
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                DrawBitmapDoubleBuffering(hdc);

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

void Updates()
{
    if (brick_count == 0)
    {
        level++;
        Next_Stage();
        pad.to_Center();
        ball.Start(0);
    }
    if (level > 4)
    {
        //ADD: ending
    }
    if (ball.get_Life() < 0)
    {
        stage = 3;
    }
    
    ball.Update(pad.get_Points());
    Ball_Hit();

    InvalidateRect(hWnd, NULL, false);
  
}
// >>: functions definitions : brickbuster
void Create_Level()
{
    for (int i = 0; i < QUANT; i++)
        brick[i].re_Spawn();

        //copy collor array
    int temp_color[4];
    for (int i = 0; i < 4; i++)
    {
        temp_color[i] = color[i];
    }
        //set colors for each brick randomly
    int temp, repet;
    int i = 0;
    while (i < QUANT)
    {
        temp = rand() % 4; //: random color(0~3)
    
        if (temp_color[temp] == 0)
        {
            continue; //: check color quantity is availiable
        }
        
        brick_count += temp + 1;
        
        temp_color[temp]--; //count quantity of colors
        brick[i++].set_Color(temp);
    }
}

void Next_Stage()
{
    color[3] += color[level - 1];
    color[level - 1] = 0;
    Create_Level();
}

void Ball_Hit()
{
    if (ball.center.y < 240)
    {
        //check bricks collision with ball
        for (int i = 0; i < QUANT; i++)
        {
            if (brick[i].alive == false) continue;
            //hit bottom
            if (ball.center.x >= brick[i].p[0].x && ball.center.x <= brick[i].p[1].x &&
                ball.center.y - ball.radius == brick[i].p[3].y)
            {
                brick[i].Hit();
                ball.vector.y *= -1;
                brick_count--;
                point++;
            }
            //hit top
            else if (ball.center.x >= brick[i].p[0].x && ball.center.x <= brick[i].p[1].x &&
                     ball.center.y + ball.radius == brick[i].p[0].y)
            {
                brick[i].Hit();
                ball.vector.y *= -1;
                brick_count--;
                point++;
            }
            //hit right
            if (ball.center.y >= brick[i].p[0].y && ball.center.y <= brick[i].p[3].y &&
                ball.center.x + ball.radius == brick[i].p[0].x)
            {
                brick[i].Hit();
                ball.vector.x *= -1;
                brick_count--;
                point++;
            }
            //hit left
            else if (ball.center.y >= brick[i].p[0].y && ball.center.y <= brick[i].p[3].y &&
                     ball.center.x - ball.radius == brick[i].p[1].x)
            {
                brick[i].Hit();
                ball.vector.x *= -1;
                brick_count--;
                point++;
            }           
        }
    }
    else if (ball.center.y > 400 && ball.start == 1)
    {
         if (ball.center.y + ball.radius == pad.p[0].y&&ball.center.x >= pad.p[0].x && ball.center.x <= pad.p[1].x)
         {
             ball.vector.y *= -1;
        }
    }
}

// <<: functions definitions : brickbuster

//>>: double buffering function definition

void DrawBitmapDoubleBuffering(HDC hdc)
{
    if (stage == 2)
    {
        HDC hdcBuffer = CreateCompatibleDC(hdc);
        HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
        HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

        HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        FillRect(hdcBuffer, &rectView, hBrush);
        DeleteObject(hBrush);

        //>> 그리기 시작
        ui.Draw_Area(hdcBuffer);
        ui.Draw_Top(hdcBuffer, point, name);

        for (int i = 0; i < QUANT; i++)
        {
            brick[i].Draw(hdcBuffer);
        }

        pad.Draw(hdcBuffer);
        ball.Draw(hdcBuffer);
        ui.Draw_Bottom(hdcBuffer, ball.get_Life());

        BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hdcBuffer, 0, 0, SRCCOPY);

        SelectObject(hdcBuffer, hbmOldBuffer);
        DeleteObject(hbmBuffer);
        DeleteDC(hdcBuffer);
    }
    else if (stage == 0)
    {
        for (int i = 0; i < QUANT; i++)
        {
            brick[i].Draw(hdc);
        }
        ui.Draw_PressStart(hdc);
    }
    else if (stage == 1)
    {
        ui.Draw_TypeName(hdc, name);
    }
    else if (stage == 3)
    {
        ui.Draw_GameOver(hdc);
    }
}
//<<: double buffering function definition