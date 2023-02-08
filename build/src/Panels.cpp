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

#include "pxpch.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "Application.h"
#include "Renderer.h"
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
	if (auto shader = Renderer::GetRenderer()->GetShader())
	{
		if (shader->IsLinked())
		{
			ImVec2 viewportSize = ImGui::GetContentRegionAvail();
			if (m_ViewportSize != (*reinterpret_cast<glm::vec2*>(&viewportSize)))
			{
				m_FrameBuffer->Resize((unsigned int)viewportSize.x, (unsigned int)viewportSize.y);
				m_ViewportSize = { viewportSize.x, viewportSize.y };
			}

			size_t textureID = static_cast<size_t>(m_FrameBuffer->GetColorAttachment());
			ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

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
		}
		else
		{
			TextCentered("There is no world currently loaded!");
		}
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
			if (control) {}
				
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
		ImGui::TextWrapped("PhysX Application by Ciridev.\nVersion 1.0.0");

		ImGui::EndPopup();
	}
}

EntityInspectorPanel::EntityInspectorPanel(const std::string& name) : Panel(name) 
{
	m_SelectedEntity = 0;
	b_SetNameMode = false;
}

void EntityInspectorPanel::DrawUI()
{
	if(ImGui::Begin("Inspector", &m_Active, m_WindowFlags))
	{
		if (EntityManager::Get()->GetEntityMap().size() > 0)
		{
			Entity& entity = EntityManager::Get()->GetEntityAtLocation(m_SelectedEntity);

			if (entity != Entity())
			{
				if (b_SetNameMode)
				{
					ImGui::Text("Name: ");
					ImGui::SameLine();
					ImGui::InputText(
						"###NameEntry",
						(char*)entity.GetName().data(),
						entity.GetName().capacity() + 1,
						ImGuiInputTextFlags_CallbackResize,
						[](ImGuiInputTextCallbackData* data) -> int
						{
							if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
							{
								std::string* str = (std::string*)data->UserData;
								IM_ASSERT(data->Buf == str->c_str());
								str->resize((size_t)data->BufTextLen + 1ui64);
								data->Buf = (char*)str->c_str();
							}

							return 0;
						},
						reinterpret_cast<void*>((std::string*)&entity.GetName())
							);
					ImGui::SameLine();
					if (ImGui::Button("Save")) b_SetNameMode = false;
				}
				else
				{
					ImGui::Text("Name: %s", entity.GetName().c_str());
					ImGui::SameLine();
					if (ImGui::Button("Edit")) b_SetNameMode = true;
				}

				ImGui::Text("Id: %s", entity.GetId().c_str());
			}
		}
	}

	ImGui::End();
}

void EntityInspectorPanel::OnEvent(Event& e)
{

}

WorldViewPanel::WorldViewPanel(const std::string& name) : Panel(name)
{
	m_EntityManagerRef = EntityManager::Get();
}

void WorldViewPanel::DrawUI()
{
	if (ImGui::Begin("World View", &m_Active, m_WindowFlags))
	{
		EntityMap entityMap = m_EntityManagerRef->GetEntityMap();

		ImGui::Text("Entities {%d}", entityMap.size());
		for (auto it = entityMap.begin(); it != entityMap.end(); it++)
		{
			auto entity = *it;

			if (ImGui::Selectable(std::string(entity.GetName() + "###" + entity.GetId()).c_str()))
			{
				GetPanelInternal<EntityInspectorPanel>("Inspector")->m_SelectedEntity = it - entityMap.begin();
				GetPanelInternal<EntityInspectorPanel>("Inspector")->b_SetNameMode = false;
			}
		}
	}

	ImGui::End();
}

EntityMangerListener::EntityMangerListener(const std::string& name) : ListenerPanel(name)
{
	m_EntityManager = EntityManager::Get();
}

void EntityMangerListener::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Emit<KeyPressed>(BIND_FUNCTION(&EntityMangerListener::OnKeyboardHit, this));
}

bool EntityMangerListener::OnKeyboardHit(KeyPressed& e)
{
	if (GetPanelInternal<EntityInspectorPanel>("Inspector")->b_SetNameMode) return true;

	if (e.GetKeyCode() == (int)Key::Space)
	{
		std::cout << "Entity Map: (" << m_EntityManager->GetEntityMap().size() << ")\n";
		for (auto entt : m_EntityManager->GetEntityMap())
		{
			std::cout << entt.GetId() << ": " << entt.GetName() << std::endl;
		}
		return true;
	}
	else if (e.GetKeyCode() == (int)Key::A)
	{
		std::string name = "New Entity " + std::to_string(m_EntityManager->GetEntityMap().size() + 1);
		Entity entt = Entity::CreateEntity(name);
		return true;
	}

	return false;
}
