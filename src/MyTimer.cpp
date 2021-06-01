#include "MyTimer.h"

namespace chrono = std::chrono;

MyTimer::MyTimer()
{
	start = chrono::system_clock::now();
}

float MyTimer::Peek()
{
	auto dur = chrono::system_clock::now() - start;
	return  dur.count();
}

float MyTimer::Mark()
{
	auto dur = chrono::system_clock::now() - start;
	start = chrono::system_clock::now();
	return dur.count();
}
