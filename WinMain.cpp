#include <Windows.h>

HWND ghMainWnd = 0;

class Windows
{
public:
	Windows();
	virtual ~Windows();
	Windows(const Windows& src) = delete;
	Windows& operator=(const Windows& rhs) = delete;
	bool InitWindowsApp(HINSTANCE instanceHandle, int show);
	int Run();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	WNDCLASS wc;
};

Windows::Windows()
{
	ghMainWnd = 0;
}

Windows::~Windows()
{
}

bool Windows::InitWindowsApp(HINSTANCE instanceHandle, int show)
{
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"BASIC WND CLASS";

	if (!RegisterClass(&wc)) {
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		return false;
	}

	ghMainWnd = CreateWindow(
		L"BASIC WND CLASS",
		L"WIN32 BASIC",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		instanceHandle,
		0
	);

	if (ghMainWnd == 0) {
		MessageBox(0, L"CreateWindow FAILED", 0, 0);
		return false;
	}

	ShowWindow(ghMainWnd, show);
	UpdateWindow(ghMainWnd);

	return true;
}

LRESULT CALLBACK Windows::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello, World!", L"Hello", MB_OK);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(ghMainWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int Windows::Run()
{
	MSG msg = { 0 };

	BOOL bRet = 1;

	while (bRet = GetMessage(&msg, 0, 0, 0) != 0) {
		if (bRet == -1) {
			MessageBox(0, L"Get Message FAILED", L"Error", MB_OK);
			break;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
	Windows windows;
	if (!windows.InitWindowsApp(hInstance, nShowCmd)) {
		return 0;
	}

	return windows.Run();
}