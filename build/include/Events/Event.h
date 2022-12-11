// | MIT License
// | 
// | Copyright (c) 2022 Ciridev
// | 
// | Permission is hereby granted, free of charge, to any person obtaining a copy
// | of this software and associated documentation files (the "Software"), to deal
// | in the Software without restriction, including without limitation the rights
// | to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// | copies of the Software, and to permit persons to whom the Software is
// | furnished to do so, subject to the following conditions:
// | 
// | The above copyright notice and this permission notice shall be included in all
// | copies or substantial portions of the Software.
// | 
// | THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// | IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// | FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// | AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// | LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// | OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// | SOFTWARE.

#pragma once

#include "mfxpch.h"

enum class EventType
{
	KeyPressed,
	KeyReleased,

	MouseMoved,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseWheelScrolled, 

	WindowResized,
	WindowMoved,
	WindowClosed,

	FilesDropped
};

class Event
{
protected:
	bool mHandled = false;

	friend class EventDispatcher;

public:
	virtual ~Event() {}

	virtual EventType	GetEventType()		const = 0;
	virtual const char* GetEventName()		const = 0;
	virtual std::string GetEventNameStr()   const = 0;
	virtual std::string GetEventInfo()		const = 0;

	virtual bool IsHandled() const = 0;

	inline operator bool() const { return IsHandled(); }
};

class EventDispatcher
{
private:
	template <typename T>
	using EventProcedure = std::function<bool(T&)>;

	Event& mEvent;
public:
	EventDispatcher(Event& e) : mEvent(e) {}

	template <typename T>
	bool Emit(EventProcedure<T> function)
	{
		if (mEvent.GetEventType() == T::GetEventStaticType())
		{
			mEvent.mHandled = function(*(T*)&mEvent);
			return true;
		}

		return false;
	}
};

#define BIND_FUNCTION(...) std::bind(__VA_ARGS__, std::placeholders::_1)