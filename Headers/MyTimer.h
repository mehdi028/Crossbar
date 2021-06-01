#pragma once
#include<chrono>
class MyTimer
{
private:
	std::chrono::system_clock::time_point start;
	float end;
public:
	MyTimer();
	float Peek();
	float Mark();


};


