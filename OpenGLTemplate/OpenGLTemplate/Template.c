#include "Template.h"

HWND hMainWindow;
HDC hdc;
HGLRC hrc;
RECT rect;
int clock;

float fov = 60.0f;
float zNear = 0.1f;
float zFar = 1000.0f;

// TODO are to filled with data

int verticesCount;

struct
{
	float red;
	float green;
	float blue;
} backColor = { 0.1f, 0.1f, 0.6f };

WNDCLASSEX wndClass =
{
	sizeof(WNDCLASSEX), 0, WindowProc, 0, 0, 0, 0, 0, 0, 0, CLASS_NAME, 0
};

PIXELFORMATDESCRIPTOR pfd =
{
	sizeof(PIXELFORMATDESCRIPTOR),
        1, PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW,
        PFD_TYPE_RGBA, COLOR_DEPTH, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, COLOR_DEPTH, 0, 0,
        PFD_MAIN_PLANE, 0, PFD_MAIN_PLANE, 0, 0
};

void main()
{
	MSG msg;

	RegisterClassEx(&wndClass);
	hMainWindow = CreateWindowEx(0, CLASS_NAME, 0, WS_CUSTOM, 0, 0, 0, 0, 0, 0, 0, 0);
	
	Init();

	while (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam != VK_ESCAPE)
		{
			break;
		}
	case WM_CLOSE:
		PostQuitMessage(0);

		return 0;
	case WM_PAINT:
		Draw();

		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Init()
{
	GetClientRect(hMainWindow, &rect);
	ShowCursor(0);

	clock = GetTickCount();

	hdc = GetDC(hMainWindow);
	SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);
	glViewport(0, 0, rect.right, rect.bottom);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (float)rect.right / rect.bottom, zNear, zFar);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// TODO init-stuff
}

void Draw()
{
	int time;

	time = GetTickCount();
	if (time - clock > 10)
	{
		clock = time;
		// TODO sth
	}

	glClearColor(backColor.red, backColor.green, backColor.blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// TODO camera placement and other transformations

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	// glDrawArrays/glDrawElements

	glDisableClientState(GL_VERTEX_ARRAY);
	
	SwapBuffers(hdc);
}