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

#include "Event.h"

class KeyEvent : public Event
{
protected:
	int mKeycode;
	KeyEvent(int keycode) : mKeycode(keycode) {}
public:
	inline int GetKeyCode() const { return mKeycode; }
};

class KeyPressed : public KeyEvent
{
public:
	KeyPressed(int keycode, int count) : KeyEvent(keycode), mCount(count) {}

	inline int GetCount() const { return mCount; }

	virtual EventType	GetEventType()		const override { return EventType::KeyPressed; }
	virtual const char* GetEventName()		const override { return "KeyPressed"; }
	virtual std::string GetEventNameStr()	const override { return "KeyPressed"; }
	virtual bool		IsHandled()			const override { return mHandled; }

	virtual std::string GetEventInfo() const override 
	{
		std::stringstream ss;
		ss << "KeyPressed: [Keycode(" << mKeycode << ") | Repetitions(" << mCount << ")]";
		return ss.str();
	}

	static EventType GetEventStaticType() { return EventType::KeyPressed; }

private:
	int mCount;
};

class KeyReleased : public KeyEvent
{
public:
	KeyReleased(int keycode) : KeyEvent(keycode) {}

	virtual EventType   GetEventType()		const override { return EventType::KeyReleased; }
	virtual const char* GetEventName()		const override { return "KeyReleased"; }
	virtual std::string GetEventNameStr()	const override { return "KeyReleased"; }
	virtual bool		IsHandled()			const override { return mHandled; }

	virtual std::string GetEventInfo() const override
	{
		std::stringstream ss;
		ss << "KeyReleased: [Keycode(" << mKeycode << ")]";
		return ss.str();
	}

	static EventType GetEventStaticType() { return EventType::KeyReleased; }
};
