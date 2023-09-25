#include <Windows.h>

// Window size
RECT dimension = { 0, 0, 800, 800 };

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// On window destruction
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass;
	MSG message;

	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = L"Window";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&windowClass);

	AdjustWindowRectEx(&dimension, WS_OVERLAPPEDWINDOW, NULL, WS_EX_OVERLAPPEDWINDOW);

	HWND winHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"Window", L"Figure", WS_OVERLAPPEDWINDOW,
		100, 100, dimension.right - dimension.left, dimension.bottom - dimension.top, NULL, NULL, hInstance, 0);

	if (!winHandle) return -1;

	message.message = WM_NULL;

	ShowWindow(winHandle, nCmdShow);
	
	//App cycle
	while (message.message != WM_QUIT)
	{
		GetClientRect(winHandle, &dimension);

		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}

		InvalidateRect(winHandle, NULL, FALSE);
	}

	return 0;
}