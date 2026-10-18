#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <stack>
#include "Shader.hpp"
#include "CordFrame.hpp"
#include "Part.hpp"
#include "Math.hpp"

struct BodyParts
{
    Part head;
    Part torso;
    Part rUpArm;    // right upper arm
    Part rForearm;  // right forearm
    Part lUpArm;    // left  upper arm
    Part lForearm;  // left  forearm
    Part rThigh;    // right Thigh
    Part rLowLeg;   // right leg lower part
    Part lThigh;    // left  Thigh
    Part lLowLeg;   // left  leg lower part
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
};

#endif