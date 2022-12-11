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

class MouseButtonPressed : public Event
{
public:
	MouseButtonPressed(int button) : mButton(button) {}

	virtual EventType	GetEventType()		const { return EventType::MouseButtonPressed; }
	virtual const char* GetEventName()		const { return "MouseButtonPressed"; }
	virtual std::string GetEventNameStr()   const { return "MouseButtonPressed"; }

	virtual std::string GetEventInfo() const {
		std::stringstream ss;
		ss << "MouseButtonPressed: [Button(" << mButton << ")]";
		return ss.str();
	}

	virtual bool IsHandled() const { return mHandled; }
	static EventType GetEventStaticType() { return EventType::MouseButtonPressed; }

private:
	int mButton;
};

class MouseButtonReleased : public Event
{
public:
	MouseButtonReleased(int button) : mButton(button) {}

	virtual EventType	GetEventType()		const { return EventType::MouseButtonReleased; }
	virtual const char* GetEventName()		const { return "MouseButtonReleased"; }
	virtual std::string GetEventNameStr()   const { return "MouseButtonReleased"; }

	virtual std::string GetEventInfo() const {
		std::stringstream ss;
		ss << "MouseButtonReleased: [Button(" << mButton << ")]";
		return ss.str();
	}

	virtual bool IsHandled() const { return mHandled; }
	static EventType GetEventStaticType() { return EventType::MouseButtonReleased; }

private:
	int mButton;
};

class MouseMoved : public Event
{
public:
	MouseMoved(float x, float y) : mX(x), mY(y) {}

	virtual EventType	GetEventType()		const { return EventType::MouseMoved; }
	virtual const char* GetEventName()		const { return "MouseMoved"; }
	virtual std::string GetEventNameStr()   const { return "MouseMoved"; }

	float GetHorizontalPosition() const { return mX; }
	float GetVerticalPosition()	  const { return mY; }

	virtual std::string GetEventInfo() const {
		std::stringstream ss;
		ss << "MouseMoved: [x(" << mX << ") | y(" << mY << ")]";
		return ss.str();
	}

	virtual bool IsHandled() const { return mHandled; }
	static EventType GetEventStaticType() { return EventType::MouseMoved; }

private:
	float mX;
	float mY;
};

class MouseWheelScrolled : public Event
{
public: 
	MouseWheelScrolled(float xoff, float yoff) : mWheel_xOffset(xoff), mWheel_yOffset(yoff) {}

	virtual EventType	GetEventType()		const { return EventType::MouseWheelScrolled; }
	virtual const char* GetEventName()		const { return "MouseWheelScrolled"; }
	virtual std::string GetEventNameStr()   const { return "MouseWheelScrolled"; }

	float GetHorizontalOffset() const { return mWheel_xOffset; }
	float GetVerticalOffset()	const { return mWheel_yOffset; }

	virtual std::string GetEventInfo() const {
		std::stringstream ss;
		ss << "MouseWheelScrolled: [x(" << mWheel_xOffset << ") | y(" << mWheel_yOffset << ")]";
		return ss.str();
	}

	virtual bool IsHandled() const { return mHandled; }
	static EventType GetEventStaticType() { return EventType::MouseButtonReleased; }

private:
	float mWheel_xOffset;
	float mWheel_yOffset;
};
