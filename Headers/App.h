#pragma once
#include "Window.h"
#include "Enemy.h"
#include "LimitLine.h"
#include "Plate.h"
#include<vector>
#include<memory>
class App
{
private:
	Window mainWnd;
	std::vector<std::unique_ptr<Drawable>> Draw_eliments;
	std::unique_ptr<Plate> main_plate;
	std::unique_ptr<LimitLine> Limit_Bar;

public:
	App(const wchar_t* gameName) ;
	int Run();
	void DrawFrame();
	void UpdateFrame();



};

