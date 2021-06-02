#include "Mouse.h"

Mouse::Event::Event(const int& x, const int& y, const Type& event_type) noexcept
	:coordinate(x,y), EventType(event_type)
{
}

bool Mouse::IsQueueEmpty()
{
	return MouseQueue.size() == 0;
}
Mouse::Event Mouse::GetMouseEvent()
{
	if (!IsQueueEmpty())
	{
		Event  mouse_event = MouseQueue.front();
		MouseQueue.pop();
		return mouse_event;
	}
	return Mouse::Event();
}

void Mouse::OnMouseLclick(const int& x, const int& y)
{
	MouseQueue.push({ x, y, Event::Type::MouseLPressed });
}
void Mouse::OnMouseLup(const int& x, const int& y)
{
	MouseQueue.push({ x, y, Event::Type::MouseLUp });
}



void Mouse::OnMouseRclick(const int& x, const int& y)
{
	MouseQueue.push({ x, y, Event::Type::MouseRPressed });
}

void Mouse::OnMouseRup(const int& x, const int& y)
{
	MouseQueue.push({ x, y, Event::Type::MouseRUp });
}

void Mouse::OnScrollUp(const int& x, const int& y)
{
	MouseQueue.push({ x, y, Event::Type::MouseScrollUp });
}

void Mouse::OnSCrollDown(const int& x, const int& y)
{
	MouseQueue.push({ x, y, Event::Type::MouseScrollDown});
}

void Mouse::OnMouseMove(const int& x, const int& y)
{
	MouseQueue.push({ x, y, Event::Type::MouseMove});
}
