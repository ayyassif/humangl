#ifndef BODY_EDITOR_HPP
#define BODY_EDITOR_HPP

#include <vector>
#include <string>

#include "Human.hpp"
#include "imgui.h"

struct PartUI {
    const char* name;
    CordFrame*  frame;                       // pointer to the actual body part
    float       color[3] = {1, 1, 1};        // RGB
    Vec3        size = Vec3(1.0f, 1.0f, 1.0f);        // X, Y, Z scale
    bool        uniform  = true;             // lock XYZ together
};

class BodyEditorUI {
public:
    std::vector<PartUI> parts;
    int  selected = 0;
    bool open     = true;

    // Call once after your model is created
    void Init(BodyFrames &bf);

    // ---- YOU IMPLEMENT THESE ----
    void ApplyColor(PartUI& p) {
        p.frame->getPart().setColor(p.color);
    }
    void ApplySize(PartUI& p) {
        p.frame->setScale(p.size);
        p.frame->setModel(p.frame->getFirstModel());
    }
    // -----------------------------

    animations Draw() {
    static int anim = IDLE;   // or make this a member if you need it elsewhere

    if (!open) return static_cast<animations>(anim);

    ImGui::SetNextWindowSize(ImVec2(520, 440), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Body Editor", &open)) {
        ImGui::End();
        return static_cast<animations>(anim);
    }

    // ---------- Top: animation mode ----------
    ImGui::Text("Animation Mode");
    ImGui::RadioButton("None",  &anim, NONE);  ImGui::SameLine();
    ImGui::RadioButton("Idle",  &anim, IDLE);  ImGui::SameLine();
    ImGui::RadioButton("Run",   &anim, RUN);   ImGui::SameLine();
    ImGui::RadioButton("Jump",  &anim, JUMP);  ImGui::SameLine();
    ImGui::RadioButton("Fly",   &anim, FLY);   ImGui::SameLine();
    ImGui::RadioButton("Dance", &anim, DANCE);

    ImGui::Separator();

    // ---------- Left: list of parts ----------
    ImGui::BeginChild("PartList", ImVec2(170, 0), true);
    for (int i = 0; i < (int)parts.size(); ++i) {
        ImVec4 c(parts[i].color[0], parts[i].color[1], parts[i].color[2], 1.0f);
        ImGui::ColorButton(("##sw" + std::to_string(i)).c_str(), c,
                           ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoPicker,
                           ImVec2(12, 12));
        ImGui::SameLine();
        if (ImGui::Selectable(parts[i].name, selected == i))
            selected = i;
    }
    ImGui::EndChild();

    ImGui::SameLine();

    // ---------- Right: editor for selected part ----------
    ImGui::BeginChild("PartEdit", ImVec2(0, 0), true);
    PartUI& p = parts[selected];
    ImGui::Text("%s", p.name);
    ImGui::Separator();

    if (ImGui::ColorEdit3("Color", p.color,
            ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreviewHalf))
        ApplyColor(p);

    ImGui::Spacing();

    // ---------- Size (per axis) ----------
    bool changed = false;
    changed |= ImGui::DragFloat("Size X", &p.size[0], 0.01f, 0.05f, 10.0f);
    changed |= ImGui::DragFloat("Size Y", &p.size[1], 0.01f, 0.05f, 10.0f);
    changed |= ImGui::DragFloat("Size Z", &p.size[2], 0.01f, 0.05f, 10.0f);
    if (changed) ApplySize(p);

    ImGui::Spacing();
    if (ImGui::Button("Reset this part")) {
        for (int i = 0; i < 3; ++i) p.color[i] = p.frame->getPart().getFirstColor()[i];
        for (int i = 0; i < 3; ++i) p.size[i]  = 1.0f;
        p.frame->setScale(Vec3(1.0f));
        p.frame->setModel(p.frame->getFirstModel());
        ApplyColor(p);
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset all")) {
        for (PartUI& part : parts) {
            for (int i = 0; i < 3; ++i) part.color[i] = part.frame->getPart().getFirstColor()[i];
            for (int i = 0; i < 3; ++i) part.size[i] = 1.0f;
            part.frame->setScale(Vec3(1.0f));
            part.frame->setModel(part.frame->getFirstModel());
            ApplyColor(part);
        }
    }

    ImGui::EndChild();
    ImGui::End();

    return static_cast<animations>(anim);
}
};

#endif