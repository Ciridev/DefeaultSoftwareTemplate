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

class WindowResized : public Event 
{
public:
	WindowResized(unsigned int width, unsigned int height) : mWidth(width), mHeight(height) {}

	virtual EventType	GetEventType()		const override { return EventType::WindowResized; }
	virtual const char* GetEventName()		const override { return "WindowResized"; }
	virtual std::string GetEventNameStr()   const override { return "WindowResized"; }
	virtual std::string GetEventInfo()		const override 
	{ 
		std::stringstream ss;
		ss << "WindowResized: [x(" << mWidth << ") | y(" << mHeight << ")]";
		return ss.str(); 
	}

	unsigned int GetWidth()  const { return mWidth;  }
	unsigned int GetHeigth() const { return mHeight; }

	static EventType GetEventStaticType() { return EventType::WindowResized; }

	virtual bool IsHandled() const override { return mHandled; }

private:
	unsigned int mWidth;
	unsigned int mHeight;
};

class WindowMoved : public Event
{
public:
	WindowMoved(unsigned int posx, unsigned int posy) : mPosx(posx), mPosy(posy) {}

	virtual EventType	GetEventType()		const override { return EventType::WindowMoved; }
	virtual const char* GetEventName()		const override { return "WindowMoved"; }
	virtual std::string GetEventNameStr()   const override { return "WindowMoved"; }
	virtual std::string GetEventInfo()		const override
	{
		std::stringstream ss;
		ss << "WindowMoved: [x(" << mPosx << ") | y(" << mPosy << ")]";
		return ss.str();
	}

	unsigned int GetPosX() const { return mPosx; }
	unsigned int GetPosY() const { return mPosy; }

	static EventType GetEventStaticType() { return EventType::WindowMoved; }

	virtual bool IsHandled() const override { return mHandled; }

private:
	unsigned int mPosx;
	unsigned int mPosy;
};

class WindowClosed : public Event 
{ 
public:
	virtual EventType	GetEventType()		const override { return EventType::WindowClosed; }
	virtual const char* GetEventName()		const override { return "WindowClosed"; }
	virtual std::string GetEventNameStr()   const override { return "WindowClosed"; }
	virtual std::string GetEventInfo()		const override { return "WindowClosed [No info]"; }

	static EventType GetEventStaticType() { return EventType::WindowClosed; }

	virtual bool IsHandled() const override { return mHandled; }
};

class FilesDropped : public Event
{
public:
	FilesDropped(int number, const char* files[])
	{
		for (int i = 0; i < number; i++)
			mFiles.push_back(files[i]);
	}

	virtual EventType	GetEventType()		const override { return EventType::FilesDropped; }
	virtual const char* GetEventName()		const override { return "FilesDropped"; }
	virtual std::string GetEventNameStr()   const override { return "FilesDropped"; }
	virtual std::string GetEventInfo()		const override 
	{ 
		std::stringstream ss;
		ss << "FilesDropped: [number(" << mFiles.size() << ")]\n";
		for (auto& file : mFiles)
			ss << file << std::endl;
		return ss.str();
	}

	size_t GetCount() const { return mFiles.size(); }
	std::vector<std::string> GetFiles() const { return mFiles; }
	
	static EventType GetEventStaticType() { return EventType::FilesDropped; }
	
	virtual bool IsHandled() const override { return mHandled; }

private:
	std::vector<std::string> mFiles;
};
