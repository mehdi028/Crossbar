#pragma once
#include<utility>
#include<queue>

class Mouse
{
public:
	friend class Window;
	class Event {
	public:
		enum class Type {
			MouseLPressed=1,
			MouseLUp,
			MouseRPressed,
			MouseRUp,
			MouseMove,
			MouseScrollUp,
			MouseScrollDown,
			MouseInvalid
			
		};
		Event(const int& x = 0,const int& y = 0,const Type& event_type = Type::MouseInvalid) noexcept;
		std::pair<int, int> coordinate;
		Type EventType;

	};
	//check if the queue is empty
	bool IsQueueEmpty();
	
	// get event
	Mouse::Event GetMouseEvent();

private:
	// Queue for Mouse events
	std::queue<Event> MouseQueue;

	void OnMouseLclick(const int& x, const int& y );
	void OnMouseLup(const int& x, const int& y);
	void OnMouseRclick(const int& x, const int& y);
	void OnMouseRup(const int& x, const int& y);
	void OnScrollUp(const int& x, const int& y);
	void OnSCrollDown(const int& x, const int& y);
	void OnMouseMove(const int& x, const int& y);
};

