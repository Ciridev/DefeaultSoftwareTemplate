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
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"

#include "Entity/EntityManager.h"

#include "Window.h"

#include "ImGuiPanel.h"
#include "Panels.h"

template<typename T>
T* GetPanel(const std::string& name);

class Application
{
public:
	Application(Entity& defaultEntity = Entity());
	~Application() = default;

	void RenderLoop();

	static Application& Get();

	std::shared_ptr<Window> GetWindow() const { return m_Window; }
	std::unordered_map<std::string, Panel*> GetPanels() const { return m_PanelsContainer; }

	//void NewFile();
	//void OpenFile(const std::string& filepath);
	//void SaveFile(const std::string& filepath = "");
	//void CloseFile();
	//void RestoreFile();

	void SelectEntity(Entity& entity);
	const Entity& GetSelectedEntity() const { return m_SelectedEntity; }
	Entity& GetSelectedEntity() { return m_SelectedEntity; }

	void ChangeEditorTheme(int theme);
	void Close();

private: 
	void OnEvent(Event&);
	bool OnKeyboardHit(KeyPressed&);
	bool OnWindowClosed(WindowClosed&);
	bool OnFilesDropped(FilesDropped&);
	bool OnWindowResized(WindowResized&);

	std::shared_ptr<Window> m_Window;
	std::shared_ptr<EntityManager> m_EntityManager;
	std::shared_ptr<Renderer> m_Renderer;
	std::unique_ptr<ImGuiPanel> m_ImGuiFrame;

	Entity& m_SelectedEntity;

	static Application* s_Instance;

	std::unordered_map<std::string, Panel*> m_PanelsContainer;

	bool m_Minimized;
	bool m_Running;
	float lastFrameTime = 0.0f;
};
