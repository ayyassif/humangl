#ifndef HUMAN_HPP
#define HUMAN_HPP

#include "CordFrame.hpp"
#include "Part.hpp"
#include "Vec3.hpp"

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

class Human
{
private:
    CordFrame cordTree;
    
public:
    Human();
    
    BodyParts bodyParts;    
};

// CordFrame* createLimbs(Vec3 color)
// {
    
// }

Human::Human()
{
    bodyParts.torso = Part(
        Mat4::model(
            Vec3(0.0f),
            0.0f,
            Vec3(0.0f),
            Vec3(8.0f, 12.0f, 4.0f)
        ),
        Vec3(40.0f, 118.0f, 184.0f));
}

#endif