#pragma once
#include<Windows.h>
#include<string>
#include<map>
#include<exception>
#include "ExceptionRoot.h"


class Window
{
public:
	class WindowException : public ExceptionRoot
	{
	public:
		WindowException(DWORD dword, std::string file, int line) noexcept;
		std::string GetType() const override;
		const char* what() const override;
		std::string MessageWndFormatter() const;


	private:
		DWORD dwordCode;

	};
	class WindowClass {
	private:
		 static std::map<const wchar_t*, int>countWinClasses;
		
	public:
		WindowClass(const HINSTANCE& hinstance, const wchar_t* className);
		

	};
	Window(const HINSTANCE& hinstance, const wchar_t* gameName);
	//Window(const Window& rhs) = delete;
	static LRESULT CALLBACK WindowProcStarter(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WindowProcSender(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MainWindProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Test();

private:
	HWND hwnd;
	int wWidth;
	int wHeight;
	const wchar_t* name;
	
};

#define GetWindowLastError  Window::WindowException(GetLastError(), __FILE__, __LINE__)
#define WindowError(dword)  Window::WindowException(dword, __FILE__, __LINE__)
