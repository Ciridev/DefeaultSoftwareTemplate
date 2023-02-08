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

#include "Events/Event.h"

struct GLFWwindow;
using EventProcedure = std::function<void(Event&)>;

enum class RefreshRate
{
	Free,
	VSync
};

struct WindowSettings
{
	int windowSizex = 1280;
	int windowSizey = 720;
	int windowPosx = 250;
	int windowPosy = 250;

	RefreshRate refreshRate = RefreshRate::Free;
};

class Window
{
public:
	Window
	(
		WindowSettings settings,
		std::string title = "PhysX"
	) 
	{
		m_Data.m_Settings = settings;
		m_Data.m_Title = title;

		Init(settings);
	}

	~Window() = default;

	uint32_t	 GetWidth()			const { return m_Data.m_Settings.windowSizex; }
	uint32_t	 GetHeight()		const { return m_Data.m_Settings.windowSizey; }
	
	uint32_t	 GetPosX()		const { return m_Data.m_Settings.windowPosx; }
	uint32_t	 GetPosY()		const { return m_Data.m_Settings.windowPosy; }

	uint32_t	 GetCurrPosX();
	uint32_t	 GetCurrPosY();

	GLFWwindow*  GetNativeWindow()  const { return m_Window; }
	std::string  GetTitle()			const { return m_Data.m_Title; }
	RefreshRate  GetRefreshRate()	const { return m_Data.m_Settings.refreshRate; }

	bool		 IsVsync()		 const { return m_Data.m_Settings.refreshRate == RefreshRate::VSync; }
	bool		 IsActive()		 const { return m_Data.m_IsActive; }

	void SetRefreshRate(RefreshRate rrate);
	void SetTitle(std::string title);

	void SetEventCallbackProcedure(const EventProcedure& eventProcedure);

	void Update();
	void Clear();
	void Close();

private:
	void Init(WindowSettings settings);

	GLFWwindow* m_Window;
	
	struct WindowData
	{
		WindowSettings m_Settings = {};

		bool m_IsActive = false;
		std::string m_Title;
		EventProcedure m_Procedure;
	};

	WindowData m_Data;
};
