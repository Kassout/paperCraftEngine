#ifndef RENDERGUISYSTEM_H
#define RENDERGUISYSTEM_H

#include "../ECS/ECS.h"
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>

/// TODO: comments
class RenderGUISystem: public System {
public:
    /// TODO: comments
    RenderGUISystem() = default;

    /// TODO: comments
    void Update() {
        ImGui::NewFrame();

        if (ImGui::Begin("Spawn enemies")) {
            ImGui::
        }

        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());
    }
};


#endif // RENDERGUISYSTEM_H //
