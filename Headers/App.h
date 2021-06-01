#pragma once
#include "Window.h"
class App
{
private:
	Window mainWnd;
public:
	App(const wchar_t* gameName) ;
	int Run();


};

