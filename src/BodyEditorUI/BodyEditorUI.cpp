#include "BodyEditorUI.hpp"

void BodyEditorUI::Init(BodyFrames &bf)
{
    parts = {
        {"Head",             &bf.head},
        {"Torso",            &bf.torso},
        {"Right Upper Arm",  &bf.rUpArm},
        {"Right Forearm",    &bf.rForearm},
        {"Left Upper Arm",   &bf.lUpArm},
        {"Left Forearm",     &bf.lForearm},
        {"Right Thigh",      &bf.rThigh},
        {"Right Lower Leg",  &bf.rLowLeg},
        {"Left Thigh",       &bf.lThigh},
        {"Left Lower Leg",   &bf.lLowLeg},
        {"Tail 1 (base)",    &bf.tail1},
        {"Tail 2 (middle)",  &bf.tail2},
        {"Tail 3 (end)",     &bf.tail3},
        {"Left Horn",        &bf.lHorn},
        {"Right Horn",       &bf.rHorn},
        {"Right Wing",       &bf.rWing},
        {"Left Wing",        &bf.lWing},
        {"Right Wing Tip",   &bf.rWingTip},
        {"Left Wing Tip",    &bf.lWingTip},
    };
    for (PartUI &p : parts)
    {
        for (int i = 0; i < 3; ++i) p.color[i] = p.frame->getPart().getFirstColor()[i];
        ApplyColor(p);
    }
}