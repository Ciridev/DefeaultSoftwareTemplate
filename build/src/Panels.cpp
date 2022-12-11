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

#include <math.h> // fmodf

    // NB: You can use math functions/operators on ImVec2 if you #define IMGUI_DEFINE_MATH_OPERATORS and #include "imgui_internal.h"
    // Here we only declare simple +/- operators so others don't leak into the demo code.
static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

// Dummy data structure provided for the example.
// Note that we storing links as indices (not ID) to make example code shorter.
static void ShowExampleAppCustomNodeGraph(bool* opened)
{
    
}

static NodeEditor::EditorContext* g_Context = nullptr;

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

		if (ImGui::BeginMenu("Edit"))
		{		
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("?"))
		{
			if (ImGui::MenuItem("About", "Ctrl+H", nullptr, false))
			{

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

NodeEditorPanel::NodeEditorPanel(const std::string& name) : UIPanel(name) 
{
	g_Context = NodeEditor::CreateEditor();
}

NodeEditorPanel::~NodeEditorPanel() 
{
	NodeEditor::DestroyEditor(g_Context); 
}

void NodeEditorPanel::DrawUI()
{
    ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Example: Custom Node Graph", nullptr))
    {
        ImGui::End();
        return;
    }

    // Dummy
    struct Node
    {
        int     ID;
        char    Name[32];
        ImVec2  Pos, Size;
        float   Value;
        ImVec4  Color;
        int     InputsCount, OutputsCount;

        Node(int id, const char* name, const ImVec2& pos, float value, const ImVec4& color, int inputs_count, int outputs_count) { ID = id; strcpy(Name, name); Pos = pos; Value = value; Color = color; InputsCount = inputs_count; OutputsCount = outputs_count; }

        ImVec2 GetInputSlotPos(int slot_no) const { return ImVec2(Pos.x, Pos.y + Size.y * ((float)slot_no + 1) / ((float)InputsCount + 1)); }
        ImVec2 GetOutputSlotPos(int slot_no) const { return ImVec2(Pos.x + Size.x, Pos.y + Size.y * ((float)slot_no + 1) / ((float)OutputsCount + 1)); }
    };
    struct NodeLink
    {
        int     InputIdx, InputSlot, OutputIdx, OutputSlot;

        NodeLink(int input_idx, int input_slot, int output_idx, int output_slot) { InputIdx = input_idx; InputSlot = input_slot; OutputIdx = output_idx; OutputSlot = output_slot; }
    };

    // State
    static ImVector<Node> nodes;
    static ImVector<NodeLink> links;
    static ImVec2 scrolling = ImVec2(0.0f, 0.0f);
    static bool inited = false;
    static bool show_grid = true;
    static int node_selected = -1;

    // Initialization
    ImGuiIO& io = ImGui::GetIO();
    if (!inited)
    {
        nodes.push_back(Node(0, "MainTex", ImVec2(40, 50), 0.5f, ImColor(255, 100, 100), 1, 1));
        nodes.push_back(Node(1, "BumpMap", ImVec2(40, 150), 0.42f, ImColor(200, 100, 200), 1, 1));
        nodes.push_back(Node(2, "Combine", ImVec2(270, 80), 1.0f, ImColor(0, 200, 100), 2, 2));
        links.push_back(NodeLink(0, 0, 2, 0));
        links.push_back(NodeLink(1, 0, 2, 1));
        inited = true;
    }

    // Draw a list of nodes on the left side
    bool open_context_menu = false;
    int node_hovered_in_list = -1;
    int node_hovered_in_scene = -1;
    ImGui::BeginChild("node_list", ImVec2(100, 0));
    ImGui::Text("Nodes");
    ImGui::Separator();
    for (int node_idx = 0; node_idx < nodes.Size; node_idx++)
    {
        Node* node = &nodes[node_idx];
        ImGui::PushID(node->ID);
        if (ImGui::Selectable(node->Name, node->ID == node_selected))
            node_selected = node->ID;
        if (ImGui::IsItemHovered())
        {
            node_hovered_in_list = node->ID;
            open_context_menu |= ImGui::IsMouseClicked(1);
        }
        ImGui::PopID();
    }
    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginGroup();

    const float NODE_SLOT_RADIUS = 4.0f;
    const ImVec2 NODE_WINDOW_PADDING(8.0f, 8.0f);

    // Create our child canvas
    ImGui::Text("Hold middle mouse button to scroll (%.2f,%.2f)", scrolling.x, scrolling.y);
    ImGui::SameLine(ImGui::GetWindowWidth() - 100);
    ImGui::Checkbox("Show grid", &show_grid);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(60, 60, 70, 200));
    ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
    ImGui::PopStyleVar(); // WindowPadding
    ImGui::PushItemWidth(120.0f);

    const ImVec2 offset = ImGui::GetCursorScreenPos() + scrolling;
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // Display grid
    if (show_grid)
    {
        ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
        float GRID_SZ = 64.0f;
        ImVec2 win_pos = ImGui::GetCursorScreenPos();
        ImVec2 canvas_sz = ImGui::GetWindowSize();
        for (float x = fmodf(scrolling.x, GRID_SZ); x < canvas_sz.x; x += GRID_SZ)
            draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, canvas_sz.y) + win_pos, GRID_COLOR);
        for (float y = fmodf(scrolling.y, GRID_SZ); y < canvas_sz.y; y += GRID_SZ)
            draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(canvas_sz.x, y) + win_pos, GRID_COLOR);
    }

    // Display links
    draw_list->ChannelsSplit(2);
    draw_list->ChannelsSetCurrent(0); // Background
    for (int link_idx = 0; link_idx < links.Size; link_idx++)
    {
        NodeLink* link = &links[link_idx];
        Node* node_inp = &nodes[link->InputIdx];
        Node* node_out = &nodes[link->OutputIdx];
        ImVec2 p1 = offset + node_inp->GetOutputSlotPos(link->InputSlot);
        ImVec2 p2 = offset + node_out->GetInputSlotPos(link->OutputSlot);
        draw_list->AddBezierCurve(p1, p1 + ImVec2(+50, 0), p2 + ImVec2(-50, 0), p2, IM_COL32(200, 200, 100, 255), 3.0f);
    }

    // Display nodes
    for (int node_idx = 0; node_idx < nodes.Size; node_idx++)
    {
        Node* node = &nodes[node_idx];
        ImGui::PushID(node->ID);
        ImVec2 node_rect_min = offset + node->Pos;

        // Display node contents first
        draw_list->ChannelsSetCurrent(1); // Foreground
        bool old_any_active = ImGui::IsAnyItemActive();
        ImGui::SetCursorScreenPos(node_rect_min + NODE_WINDOW_PADDING);
        ImGui::BeginGroup(); // Lock horizontal position
        ImGui::Text("%s", node->Name);
        ImGui::SliderFloat("##value", &node->Value, 0.0f, 1.0f, "Alpha %.2f");
        ImGui::ColorEdit3("##color", &node->Color.x);
        ImGui::EndGroup();

        // Save the size of what we have emitted and whether any of the widgets are being used
        bool node_widgets_active = (!old_any_active && ImGui::IsAnyItemActive());
        node->Size = ImGui::GetItemRectSize() + NODE_WINDOW_PADDING + NODE_WINDOW_PADDING;
        ImVec2 node_rect_max = node_rect_min + node->Size;

        // Display node box
        draw_list->ChannelsSetCurrent(0); // Background
        ImGui::SetCursorScreenPos(node_rect_min);
        ImGui::InvisibleButton("node", node->Size);
        if (ImGui::IsItemHovered())
        {
            node_hovered_in_scene = node->ID;
            open_context_menu |= ImGui::IsMouseClicked(1);
        }
        bool node_moving_active = ImGui::IsItemActive();
        if (node_widgets_active || node_moving_active)
            node_selected = node->ID;
        if (node_moving_active && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            node->Pos = node->Pos + io.MouseDelta;

        ImU32 node_bg_color = (node_hovered_in_list == node->ID || node_hovered_in_scene == node->ID || (node_hovered_in_list == -1 && node_selected == node->ID)) ? IM_COL32(75, 75, 75, 255) : IM_COL32(60, 60, 60, 255);
        draw_list->AddRectFilled(node_rect_min, node_rect_max, node_bg_color, 4.0f);
        draw_list->AddRect(node_rect_min, node_rect_max, IM_COL32(100, 100, 100, 255), 4.0f);
        for (int slot_idx = 0; slot_idx < node->InputsCount; slot_idx++)
            draw_list->AddCircleFilled(offset + node->GetInputSlotPos(slot_idx), NODE_SLOT_RADIUS, IM_COL32(150, 150, 150, 150));
        for (int slot_idx = 0; slot_idx < node->OutputsCount; slot_idx++)
            draw_list->AddCircleFilled(offset + node->GetOutputSlotPos(slot_idx), NODE_SLOT_RADIUS, IM_COL32(150, 150, 150, 150));

        ImGui::PopID();
    }
    draw_list->ChannelsMerge();

    // Scrolling
    if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Right, 0.0f))
        scrolling = scrolling + io.MouseDelta;

    // Open context menu
    if (ImGui::IsKeyPressed(ImGuiKey_A, true))
        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) || !ImGui::IsAnyItemHovered())
        {
            node_selected = node_hovered_in_list = node_hovered_in_scene = -1;
            open_context_menu = true;
        }
    if (open_context_menu)
    {
        ImGui::OpenPopup("context_menu");
        if (node_hovered_in_list != -1)
            node_selected = node_hovered_in_list;
        if (node_hovered_in_scene != -1)
            node_selected = node_hovered_in_scene;
    }

    ImGui::PopItemWidth();
    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    ImGui::EndGroup();

    ImGui::End();
}
