#include "Keyboard.h"
#include "..\Headers\Keyboard.h"

Keyboard::Event::Event(const unsigned char unicode, const Type& event_type) noexcept
	:Unicode(unicode), eventType(event_type)
{
}


bool Keyboard::IsQueueEmpty(const std::queue<Event>& Queue)
{
	return  Queue.size() == 0;
}

Keyboard::Event Keyboard::GetKeysEvent()
{
	if (!IsQueueEmpty(KeysQueue))
	{
		auto key = KeysQueue.front();
		KeysQueue.pop();
		return key;
	}
	else {
		return Keyboard::Event();
	}
	
}

Keyboard::Event Keyboard::GetCharEvent()
{
	if (!IsQueueEmpty(CharQueue))
	{
		auto key = CharQueue.front();
		CharQueue.pop();
		return key;
	}
	else {
		return Keyboard::Event();
	}
}

void Keyboard::AllowRepeat()
{
	count++;
	if (count >= 200)
	{
		RepeatAllowed = true;
	}
}

void Keyboard::OnPressed(const unsigned char& unicode)
{
	KeysQueue.push({ unicode, Event::Type::Key_Pressed });
	keyState[unicode] = true;
	TrimQueue(KeysQueue);
}

void Keyboard::OnKeyUp(const unsigned char& unicode)
{
	count = 0;
	keyState[unicode] = false;
	KeysQueue.push({ unicode, Event::Type::Key_UP });
	TrimQueue(KeysQueue);

}

void Keyboard::OnChar(const unsigned char& unicode)
{
	CharQueue.push({ unicode, Event::Type::Key_Char });
	TrimQueue(CharQueue);
}

void Keyboard::TrimQueue(std::queue<Event>& Queue)
{
	while (Queue.size() > QueueSize)
	{
		Queue.pop();
	}


}
