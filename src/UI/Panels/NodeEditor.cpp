#include "NodeEditor.h"

namespace Aero
{

    NodeEditor::NodeEditor(){}
    NodeEditor::~NodeEditor(){}

    void NodeEditor::render()
{

        ImGui::Begin("Node Editor");//"Node Editor");
        {


            io = ImGui::GetIO(); (void)io;

            //-----------------------------
            static ImVector<ImVec2> points;
            static ImVec2 panning(0.0f, 0.0f);
            static float scrolling = 0;
            static bool opt_enable_grid = true;

            //ImGui::Checkbox("Enable grid", &opt_enable_grid);

            // Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()

            ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
            ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
            if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
            if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
            ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

            // Draw border and background color
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
            draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

            // This will catch our interactions
            ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
            const bool is_hovered = ImGui::IsItemHovered(); // Hovered
            const bool is_active = ImGui::IsItemActive();   // Held
            const ImVec2 origin(canvas_p0.x + panning.x, canvas_p0.y + panning.y); // Lock scrolled origin
            const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);

            // Pan (we use a zero mouse threshold)
            if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right))
            {
                panning.x += io.MouseDelta.x;
                panning.y += io.MouseDelta.y;
            }

            // Draw grid + all lines in the canvas
            draw_list->PushClipRect(canvas_p0, canvas_p1, true);
            if (opt_enable_grid)
            {
                float GRID_STEP = 48.0f;
                for (float x = fmodf(panning.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
                draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
                for (float y = fmodf(panning.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
                draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 40));
            }


        }
        ImGui::End();
        }
}
