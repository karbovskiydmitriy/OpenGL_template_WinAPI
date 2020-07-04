#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#define CLASS_NAME "OpenGLTemplateClass"
#define WS_CUSTOM (WS_VISIBLE | WS_POPUP | WS_MAXIMIZE)
#define COLOR_DEPTH 24

void main();
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Init();
void Draw();
