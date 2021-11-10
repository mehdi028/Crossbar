#include "Window.h"

#include<sstream>


Window::Window(const wchar_t* gameName)
	:wWidth(800), wHeight(600), name(gameName), hinstance(GetModuleHandle(nullptr))
{

	const wchar_t* className = L"main";
	WNDCLASSEX wnd = { 0 };
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.style = CS_OWNDC;
	wnd.lpfnWndProc = WindowProcStarter;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hinstance;
	wnd.hIcon = NULL;
	wnd.hCursor = NULL;
	wnd.hbrBackground = (HBRUSH)(COLOR_GRAYTEXT + 1);
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = className;
	wnd.hIconSm = NULL;
	RegisterClassEx(&wnd);
	RECT wr;
	wr.left = 100;
	wr.right = wr.left + wWidth;
	wr.top = 100;
	wr.bottom = wr.top + wHeight;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw GetWindowLastError;
	}
	
	//throw WindowError(ERROR_ARENA_TRASHED);
	hwnd = CreateWindowEx(0, className, gameName, WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX| WS_SYSMENU,
		200, 200, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, hinstance, this);
	if (hwnd == nullptr) {
		//SetLastError(0);
		throw GetWindowLastError;

	}
	pgfx = std::make_unique<Graphics>(hwnd);
	ShowWindow(hwnd, SW_SHOW);

	
	
	
}
void Window::Test()
{
	
	OutputDebugString(name);
}
std::optional<int> Window::WindowLoop()
{
	MSG  msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			return (int) msg.wParam;
		}
	}
	return std::optional<int>();
}
LRESULT CALLBACK Window::WindowProcStarter(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE)
	{

		auto create_structd = reinterpret_cast<CREATESTRUCT*>(lParam);
		

		Window* pwnd = static_cast<Window*>(create_structd->lpCreateParams);
		pwnd->Test();
		// install the window class in the windows api side

		SetLastError(0);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pwnd));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::WindowProcSender));
		return  pwnd->MainWindProc(hwnd, uMsg, wParam, lParam);
		


		
	}
	/*else if(uMsg == WM_CREATE)
	{
		auto hi = reinterpret_cast<CREATESTRUCT*>(lParam);

		Window* pwnds = reinterpret_cast<Window*>(hi->lpCreateParams);
		pwnds->Test();

	}*/

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Window::WindowProcSender(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	Window* pwnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	//pwnd->Test();
	return pwnd->MainWindProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Window::MainWindProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	POINTS pt;
	switch (uMsg) 
	{
	case WM_KEYDOWN:
		kb.OnPressed((unsigned char)wParam); break;
	case WM_KEYUP:
		kb.OnKeyUp((unsigned char)wParam); break;
	case WM_CHAR:
		
		kb.AllowRepeat();
		if (kb.RepeatAllowed || !(0x40000000 & lParam))
		{
			kb.OnChar((unsigned char)wParam);
			break;
		}
	case WM_MOUSEMOVE:
		pt = MAKEPOINTS(lParam);
		mouse.OnMouseMove(pt.x, pt.y);
		break;
	case WM_LBUTTONDOWN:
		pt = MAKEPOINTS(lParam);
		mouse.OnMouseLclick(pt.x, pt.y);
		break;
	case WM_LBUTTONUP:
		pt = MAKEPOINTS(lParam);
		mouse.OnMouseLup(pt.x, pt.y);
		break;
	case WM_RBUTTONDOWN:
		pt = MAKEPOINTS(lParam);
		mouse.OnMouseRclick(pt.x, pt.y);
		break;



	case WM_CLOSE: PostQuitMessage(10); break;

	}
	return DefWindowProc(hwnd, uMsg,wParam, lParam);
}

Window::WindowException::WindowException(DWORD dword, std::string file, int line) noexcept
	:ExceptionRoot(file, line), dwordCode(dword)
{
}

std::string Window::WindowException::GetType() const 
{
	return  "Window Error !";
}

const char* Window::WindowException::what() const
{
	;
	//OutputDebugStringA(WhatMessage.c_str());
	std::ostringstream ss;
	ss << GetType() << "\n";
	ss << File << "\n";
	ss << Line << "\n";
	ss << MessageWndFormatter() << "\n";
	WhatMessage = ss.str();
	return WhatMessage.c_str();
}


std::string Window::WindowException::MessageWndFormatter() const
{
	char* lpMessage = nullptr;
	DWORD length = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS
		, 0, dwordCode, LANG_SYSTEM_DEFAULT, reinterpret_cast<LPSTR>(&lpMessage), 0, nullptr);
	if(length == 0)
	{
		return "go";
	}
	std::string holder;
	
	holder  = lpMessage;
	LocalFree(lpMessage);
	OutputDebugStringA(holder.c_str());

	return holder;
}
