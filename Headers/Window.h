#pragma once
#include<Windows.h>
#include<string>
#include<map>
#include<exception>
#include "ExceptionRoot.h"
#include"Keyboard.h"
#include "Mouse.h"
#include<optional>


class Window
{
public:
	friend class App;
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
	
	Window(const wchar_t* gameName);
	//Window(const Window& rhs) = delete;
	static LRESULT CALLBACK WindowProcStarter(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WindowProcSender(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MainWindProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Test();
	std::optional<int> WindowLoop();

private:
	
	HWND hwnd;
	int wWidth;
	int wHeight;
	const wchar_t* name;
	HINSTANCE hinstance;
	// window eliments
	Keyboard kb;
	Mouse mouse;
	
};

#define GetWindowLastError  Window::WindowException(GetLastError(), __FILE__, __LINE__)
#define WindowError(dword)  Window::WindowException(dword, __FILE__, __LINE__)
