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

#include <imgui.h>
#include <imgui_internal.h>

#include "Application.h"
#include "Panels.h"
#include "Utils/Input.h"
#include "Utils/FileDialogs.h"

template<typename T>
T* GetPanelInternal(const std::string& name)
{
	auto panel = Application::Get().GetPanels()[name];
	return reinterpret_cast<T*>(panel);
}

void TextCentered(const std::string& text)
{
	auto& io = ImGui::GetIO();
	auto font = io.Fonts->Fonts[1];
	ImGui::PushFont(font);

	auto windowWidth = ImGui::GetWindowSize().x;
	auto windowHeight = ImGui::GetWindowSize().y;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;
	auto textHeight = ImGui::CalcTextSize(text.c_str()).y;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::SetCursorPosY((windowHeight - textHeight) * 0.5f);
	ImGui::TextWrapped(text.c_str());

	ImGui::PopFont();
}

void ViewportPanel::DrawUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
	ImGui::Begin("Viewport", &m_Active, m_WindowFlags);

	if (ImGui::IsWindowHovered())
	{
		auto window = Application::Get().GetWindow();
		auto width = window->GetWidth();
		auto height = window->GetHeight();

		width -= m_ViewportSize.x;
		height -= m_ViewportSize.y;

		ImVec2 mPos = ImGui::GetMousePos();
		m_MousePos = { mPos.x - width, mPos.y - height };
	}

	ImGui::End();
	ImGui::PopStyleVar();
}

void MenuBarPanel::DrawUI()
{
	ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_NoCloseButton;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("MenuBar", nullptr, m_WindowFlags);
	ImGui::PopStyleVar(3);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiID dockspace_id = ImGui::GetID("MenuBarDockspace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);

	auto& applicationInstance = Application::Get();
	
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if(ImGui::MenuItem("New", "Ctrl+N", nullptr, false))
			{
				
			}

			if (ImGui::MenuItem("Open", "Ctrl+O", nullptr, false))
			{

			}

			if (ImGui::MenuItem("Save", "Ctrl+S", nullptr, false))
			{

			}

			if (ImGui::MenuItem("Save As...", "Ctrl+Alt+S", nullptr, false))
			{
				
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Close File", "Shift+C", nullptr, false))
			{

			}

			ImGui::Separator();

			if (ImGui::MenuItem("Exit", "Alt+F4", nullptr))
			{
				applicationInstance.Close();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit", false))
		{		
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("?"))
		{
			if (ImGui::MenuItem("About", "Ctrl+H", nullptr))
			{
				auto aboutPanel = GetPanelInternal<AboutPanel>("About");
				aboutPanel->Activate(true);
			}
			
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::End();
}

void MenuBarPanel::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Emit<KeyPressed>([](KeyPressed& e) -> bool {

		Key keycode = (Key)e.GetKeyCode();

		bool shift = Input::GetKeyPress(Key::LeftShift) || Input::GetKeyPress(Key::RightShift);
		bool control = Input::GetKeyPress(Key::LeftControl) || Input::GetKeyPress(Key::RightControl);
		bool alt = Input::GetKeyPress(Key::LeftAlt) || Input::GetKeyPress(Key::RightAlt);

		auto& applicationInstance = Application::Get();

		switch (keycode)
		{
		case Key::N:
			if (control)
			{
			
			}
			break;
		case Key::O:
			if (control)
				
			break;
		case Key::S:
			if (control && alt)
			{
				
			}
			else if (control)
			{
				
			}
			break;

		case Key::C:
			if (shift)
			{
				
			}
			break;
		case Key::H:
			if (control)
			{
				auto aboutPanel = GetPanelInternal<AboutPanel>("About");
				aboutPanel->Activate(true);
			}
			break;
		case Key::F4:
			if (alt)
			{
				applicationInstance.Close();
			}
			break;
		case Key::F5:
			if (control)
			{
				
			}
			break;
		}

		return true;
	});
}

void AboutPanel::DrawUI()
{
	if (m_Active && !ImGui::IsPopupOpen("About"))
		ImGui::OpenPopup("About");

	if (ImGui::BeginPopupModal("About", &m_Active, m_WindowFlags))
	{
		ImGui::SetWindowSize({ 400, 200 });
		ImGui::TextWrapped("Default Template Application by Ciridev.\nVersion 1.0.0");

		ImGui::EndPopup();
	}
}