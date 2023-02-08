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

#include <FrameBuffer.h>
#include <glm/glm.hpp>

#include "Events/Event.h"

class Panel
{
public:
	virtual void DrawUI() = 0;
	virtual void OnEvent(Event& e) = 0;

	std::string GetName() const { return m_Name; }

	bool IsActive() const { return m_Active; }
	void Activate(bool state) { m_Active = state; }

protected:
	Panel(const std::string& name, bool active = true) : m_Name(name), m_Active(active) 
	{ m_WindowFlags = ImGuiWindowFlags_NoCollapse; }

	std::string m_Name;
	bool m_Active;

	ImGuiWindowFlags m_WindowFlags;
};

class ListenerPanel : public Panel
{
public: 
	virtual void DrawUI() override {}
	virtual void OnEvent(Event& e) = 0;

protected:
	ListenerPanel(const std::string& name) : Panel(name, false) {}
};

class EntityMangerListener : public ListenerPanel
{
public:
	EntityMangerListener(const std::string& name);
	virtual void OnEvent(Event& e) override;

private:
	bool OnKeyboardHit(KeyPressed& e);

	std::shared_ptr<EntityManager> m_EntityManager;
};

class MenuBarPanel : public Panel
{
public:
	MenuBarPanel(const std::string& name) : Panel(name)
	{
		m_WindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		m_WindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		m_WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	virtual void DrawUI() override;
	virtual void OnEvent(Event& e);
};

class ViewportPanel : public Panel
{
public:
	ViewportPanel(const std::string& name) : Panel(name) {}

	virtual void DrawUI() override;
	virtual void OnEvent(Event& e) {}

	void SetFrameBuffer(std::shared_ptr<FrameBuffer> fb) { m_FrameBuffer = fb; }
	glm::vec2 GetMousePos() const { return m_MousePos; }
	glm::vec2 GetViewportSize() const { return m_ViewportSize; }

private:
	glm::vec2 m_ViewportSize = { 0, 0 };
	glm::vec2 m_MousePos = { 0,  0 };
	std::shared_ptr<FrameBuffer> m_FrameBuffer;
};

class DemoPanel : public Panel
{
public:
	DemoPanel(const std::string& name) : Panel(name) { }
	
	virtual void DrawUI() override { ImGui::ShowDemoWindow(); }
	virtual void OnEvent(Event& e) {}
};

class AboutPanel : public Panel
{
public:
	AboutPanel(const std::string& name) : Panel(name, false)
	{
		m_WindowFlags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking;
	}

	virtual void DrawUI() override;
	virtual void OnEvent(Event& e) {}
};

class EntityInspectorPanel : public Panel
{
public:
	EntityInspectorPanel(const std::string& name);

	virtual void DrawUI() override;
	virtual void OnEvent(Event& e) override;

private:
	unsigned int m_SelectedEntity;
	bool b_SetNameMode;
	friend class WorldViewPanel;
	friend class EntityMangerListener;
};

class WorldViewPanel : public Panel
{
public:
	WorldViewPanel(const std::string& name);

	virtual void DrawUI() override;
	virtual void OnEvent(Event& e) {}

private:
	std::shared_ptr<EntityManager> m_EntityManagerRef;
};