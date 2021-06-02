#pragma once
#include<queue>
#include<bitset>

class Keyboard
{
public:
	friend class Window;
	class Event {
	public:
		enum class Type {
			Key_Pressed= 1,
			Key_UP,
			Key_Char,
			Key_Invalid

		};
	public:
		Event(const unsigned char unicode=0, const Type& event_type=Type::Key_Invalid) noexcept;
		~Event() noexcept = default;
	
		const unsigned char Unicode;
		Type eventType;

	};

	Keyboard()noexcept;
	// check if a queue is empty
	bool  IsQueueEmpty(const std::queue<Event>& Queue);

	// get keypressed or key up event or get and invalid event if there's none
	Keyboard::Event GetKeysEvent();
	
	// get a keyChar get and invalid event if there's none
	Keyboard::Event GetCharEvent();
private:
	//
	int count = 0;
	unsigned int QueueSize = 16;
	bool RepeatAllowed = false;
	void AllowRepeat();

	// queue event  for key pressed and key up
	std::queue<Event>  KeysQueue;

	// queue for characters
	std::queue<Event> CharQueue;
	
	// pressed key state ;
	std::bitset<256> keyState = false;
	void OnPressed(const unsigned char& unicode);

	void OnKeyUp(const unsigned char& unicode);
	
	void OnChar(const unsigned char& unicode);
	


	// reset queue
	template<typename T>
	void resetQueue() {
		T = std::queue<Event>();
	}
	
	void TrimQueue(std::queue<Event>& Queue);
	




};

