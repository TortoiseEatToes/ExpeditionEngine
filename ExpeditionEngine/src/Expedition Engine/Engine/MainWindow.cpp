//--------------------------------------------------------------------------------------
// File: MainWindow.cpp
//
// Heavily inspired by http://msdn.microsoft.com/en-us/library/windows/apps/ff729718.aspx


#include "ExpeditionEngineAttorney.h"
#include "../../Expedition Resources/EngineSettings.h"
#include "../Scene Components/Input/Manager/InputManagerAttorney.h"

#include <windowsx.h>
#include <assert.h>

static class EmptyObject {
public:
	~EmptyObject() {};
} _EmptyObject;

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE               g_hInst = nullptr;
HWND                    g_hWnd = nullptr;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

	// Window initialization
	HRESULT hr = InitWindow(hInstance, nCmdShow);
	assert(SUCCEEDED(hr));  // We'll be doing a lot of this... 


	ExpeditionEngineAttorney::MainCalls::Initialize();
	ExpeditionEngineAttorney::MainCalls::RunGame(g_hWnd);
	ExpeditionEngineAttorney::MainCalls::Terminate();

    return 0;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_QUESTION);
    wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "MainlWindowClass";
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_QUESTION);
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, InitialWindowWidth, InitialWindowHeight }; // Initial window dimentions. 

    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindowW( L"MainlWindowClass", L"Main Window",
                           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
                           nullptr );
    if( !g_hWnd )
        return E_FAIL;

	// Note: We won't bother dealing with resizing/fullscreen, etc

	//g_hWnd = Resize

    ShowWindow( g_hWnd, nCmdShow );

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;
	
    switch( message )
    {
	
	// Early exit using ESC key: very useful during development
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
            ExpeditionEngine::Quit();
			PostQuitMessage(0);
			return 0;
		}
		break;
	
    case WM_PAINT:
        hdc = BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        break;
	
    case WM_DESTROY:
		ExpeditionEngine::Quit();
        PostQuitMessage( 0 );
        break;
    case WM_CREATE:
        ShowCursor(FALSE);
        break;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		SetCapture(g_hWnd);
		//g_dxapp->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		ReleaseCapture();
		//g_dxapp->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	
	case WM_MOUSEMOVE:
		//g_dxapp->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		
		
		//InputManagerAttorney::MainWindowControl::SetMousePosition(GET_X_LPARAM(lParam), static_cast<const int>(g_dxapp->getHeight()) - GET_Y_LPARAM(lParam));
		InputManagerAttorney::MainWindowControl::SetMousePosition(GET_X_LPARAM(lParam), static_cast<int>(ExpeditionEngine::GetHeight() - static_cast<float>(GET_Y_LPARAM(lParam))));
		break;
		
    default:
        return DefWindowProc( hWnd, message, wParam, lParam );
    }
    return 0;
}
