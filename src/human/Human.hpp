#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <stack>
#include <cmath>
#include <algorithm>
#include "Shader.hpp"
#include "CordFrame.hpp"
#include "Part.hpp"
#include "Math.hpp"

struct BodyParts
{
    Part head;
    Part torso;
    Part rUpArm;    // right  upper arm
    Part rForearm;  // right  forearm
    Part lUpArm;    // left   upper arm
    Part lForearm;  // left   forearm
    Part rThigh;    // right  Thigh
    Part rLowLeg;   // right  leg lower part
    Part lThigh;    // left   Thigh
    Part lLowLeg;   // left   leg lower part
    Part tail1;     // base   tail
    Part tail2;     // middle tail
    Part tail3;     // end    tail
    Part lHorn;     // left   horn
    Part rHorn;     // right  horn
    Part rWing;     // right  wing
    Part lWing;     // left   wing
    Part rWingTip;  // right  wing tip
    Part lWingTip;  // left   wing tip
};

struct BodyFrames
{
    CordFrame head;
    CordFrame torso;
    CordFrame rUpArm;   // right upper arm
    CordFrame rForearm; // right forearm
    CordFrame lUpArm;   // left upper arm
    CordFrame lForearm; // left forearm
    CordFrame rThigh;   // right thigh
    CordFrame rLowLeg;  // right lower leg
    CordFrame lThigh;   // left thigh
    CordFrame lLowLeg;  // left lower leg
    CordFrame tail1;    // base   tail
    CordFrame tail2;    // middle tail
    CordFrame tail3;    // end    tail
    CordFrame lHorn;    // left   horn
    CordFrame rHorn;    // right  horn
    CordFrame rWing;    // right  wing
    CordFrame lWing;    // left   wing
    CordFrame rWingTip; // right  wing tip
    CordFrame lWingTip; // left   wing tip
};

class Human
{
private:
    std::stack<Mat4> matrixS;
    BodyParts        bodyParts;
    BodyFrames       bodyFrames;
    
    void drawHuman(const Shader &shader,
        const CordFrame *frame);
public:
    Human();

    void drawHuman(const Shader &shader);
    void run();
    void jump();
    void fly();
    void dance();
};

#endif