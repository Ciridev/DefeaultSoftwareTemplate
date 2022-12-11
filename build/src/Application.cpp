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

#include "defpch.h"

#include "Application.h"
#include "FrameBuffer.h"
#include "Utils/TimeStep.h"

template<typename T>
T* GetPanel(const std::string& name)
{
	auto panel = Application::Get().GetPanels()[name];
	return reinterpret_cast<T*>(panel);
}

Application* Application::s_Instance = nullptr;

Application::Application()
{
	s_Instance = this;
	WindowSettings windowSettings;

	m_Window = std::make_shared<Window>(windowSettings);
	m_Window->SetEventCallbackProcedure(BIND_FUNCTION(&Application::OnEvent, this));
	m_ImGuiFrame = std::make_unique<ImGuiPanel>();
	m_Minimized = (m_Window->GetWidth() == 0 && m_Window->GetHeight() == 0);
	m_Running = m_Window->IsActive();

	auto viewport = new ViewportPanel("Viewport");
	auto menuBar  = new MenuBarPanel("Menu Bar");
	auto about = new AboutPanel("About");

	m_PanelsContainer[menuBar->GetName()] = menuBar;
	m_PanelsContainer[viewport->GetName()] = viewport;
	m_PanelsContainer[about->GetName()] = about;
}

void Application::RenderLoop()
{
	TimeStep ts;
	auto viewport = GetPanel<ViewportPanel>("Viewport");
	viewport->SetFrameBuffer(std::make_shared<FrameBuffer>());

	while (m_Running)
	{
		m_Window->Update();
		if (m_Minimized || !m_Window->IsActive()) continue;

		m_Window->Clear();
		ts.Update();

		m_ImGuiFrame->Begin();
		for (auto& [k, panel] : m_PanelsContainer)
			if(panel->IsActive())
				panel->DrawUI();
		m_ImGuiFrame->End();
	}

	m_Window->Close();
}

Application& Application::Get()
{
	if (!s_Instance) new Application();
	return *s_Instance;
}

void Application::ChangeEditorTheme(int theme)
{
	m_ImGuiFrame->ChangeTheme(theme);
}

void Application::Close()
{
	m_Running = false;
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Emit<WindowResized>(BIND_FUNCTION(&Application::OnWindowResized, this));
	dispatcher.Emit<WindowClosed>(BIND_FUNCTION(&Application::OnWindowClosed, this));
	dispatcher.Emit<FilesDropped>(BIND_FUNCTION(&Application::OnFilesDropped, this));

	if(!e.IsHandled())
	{
		for (auto& [key, panel] : m_PanelsContainer)
			panel->OnEvent(e);
	}
}

bool Application::OnWindowClosed(WindowClosed& e)
{
	Close();
	return true;
}

bool Application::OnFilesDropped(FilesDropped& e)
{
	for (auto& files : e.GetFiles());

	return true;
}

bool Application::OnWindowResized(WindowResized& e)
{
	m_Minimized = (e.GetWidth() == 0 && e.GetHeigth() == 0);
	return true;
}

