#include "Human.hpp"


const Vec3 skinColor(70.0f, 42.0f, 28.0f);
const Vec3 tShirtColor(40.0f, 118.0f, 184.0f);
const Vec3 pantsColor(54.0f, 86.0f, 160.0f);


Human::Human()
{
   // Head
    bodyParts.head = Part(
        Mat4::model(
            Vec3(0.0f, 1.0f, 0.25f),
            0.0f,
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(2.0f, 2.0f, 2.0f)
        ),
        skinColor
    );

    // Torso
    bodyParts.torso = Part(
        Mat4::model(
            Vec3(0.0f, 0.0f, 0.0f),
            0.0f,
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(2.0f, 3.0f, 1.0f)
        ),
        tShirtColor
    );

    // Right upper arm
    bodyParts.rUpArm = Part(
        Mat4::model(
            Vec3(-0.5f, -0.25f, 0.0f),
            0.0f,
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(1.0f, 1.5f, 1.0f)
        ),
        tShirtColor
    );

    // Right forearm
    bodyParts.rForearm = Part(
        Mat4::model(
            Vec3(0.0f, -0.73f, 0.5f),
            0.0f,
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(0.9f, 1.4f, 0.9f)
        ),
        skinColor
    );

    // Left upper arm
    bodyParts.lUpArm = Part(
        Mat4::model(
            Vec3(0.5f, -0.25f, 0.0f),
            0.0f,
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(1.0f, 1.5f, 1.0f)
        ),
        tShirtColor
    );

    // Left forearm
    bodyParts.lForearm = Part(
        Mat4::model(
            Vec3(0.0f, -0.73f, 0.5f),
            0.0f,
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(0.9f, 1.4f, 0.9f)
        ),
        skinColor
    );

    // Right thigh
    bodyParts.rThigh = Part(
        Mat4::model(
            Vec3(0.0f, -0.75f, 0.0f),
            0.0f,
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(1.0f, 1.5f, 1.0f)
        ),
        pantsColor
    );

    // Right lower leg
    bodyParts.rLowLeg = Part(
        Mat4::model(
            Vec3(0.0f, -0.75f, -0.5f),
            0.0f,
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(1.0f, 1.5f, 1.0f)
        ),
        pantsColor
    );

    // Left thigh
    bodyParts.lThigh = Part(
        Mat4::model(
            Vec3(0.0f, -0.75f, 0.0f),
            0.0f,
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(1.0f, 1.5f, 1.0f)
        ),
        pantsColor
    );

    // Left lower leg
    bodyParts.lLowLeg = Part(
        Mat4::model(
            Vec3(0.0f, -0.75f, -0.5f),
            0.0f,
            Vec3(0.0f, 0.0f, 1.0f),
            Vec3(1.0f, 1.5f, 1.0f)
        ),
        pantsColor
    );

    bodyFrames.torso = CordFrame(
        Mat4::identity(),
        bodyParts.torso
    );

    bodyFrames.head = CordFrame(
        Mat4::translate(Vec3(0.0f, 1.5f, 0.0f)),
        bodyParts.head
    );

    bodyFrames.rUpArm = CordFrame(
        Mat4::translate(Vec3(-1.0f, 1.0f, 0.0f)),
        bodyParts.rUpArm
    );
    bodyFrames.rForearm = CordFrame(
        Mat4::translate(Vec3(-0.5f, -1.0f, -0.5f)),
        bodyParts.rForearm
    );
    bodyFrames.rUpArm.addChild(&bodyFrames.rForearm);

    bodyFrames.lUpArm = CordFrame(
        Mat4::translate(Vec3(1.0f, 1.0f, 0.0f)),
        bodyParts.lUpArm
    );
    bodyFrames.lForearm = CordFrame(
        Mat4::translate(Vec3(0.5f, -1.0f, -0.5f)),
        bodyParts.lForearm
    );
    bodyFrames.lUpArm.addChild(&bodyFrames.lForearm);

    bodyFrames.rThigh = CordFrame(
        Mat4::translate(Vec3(-0.5f, -1.5f, 0.0f)),
        bodyParts.rThigh
    );
    bodyFrames.rLowLeg = CordFrame(
        Mat4::translate(Vec3(0.0f,-1.5f, 0.5f)),
        bodyParts.rLowLeg
    );
    bodyFrames.rThigh.addChild(&bodyFrames.rLowLeg);

    bodyFrames.lThigh = CordFrame(
        Mat4::translate(Vec3(0.5f, -1.5f, 0.0f)),
        bodyParts.lThigh
    );
    bodyFrames.lLowLeg = CordFrame(
        Mat4::translate(Vec3(0.0f,-1.5f, 0.5f)),
        bodyParts.lLowLeg
    );
    bodyFrames.lThigh.addChild(&bodyFrames.lLowLeg);

    bodyFrames.torso.addChild(&bodyFrames.head);
    bodyFrames.torso.addChild(&bodyFrames.rUpArm);
    bodyFrames.torso.addChild(&bodyFrames.lUpArm);
    bodyFrames.torso.addChild(&bodyFrames.rThigh);
    bodyFrames.torso.addChild(&bodyFrames.lThigh);
}

void Human::drawHuman(const Shader &shader)
{
    drawHuman(shader, &bodyFrames.torso);
}

void Human::run()
{
    static float phase = 0.0f;
    phase += 0.12f;

    const float armSwing = std::sin(phase) * 45.0f;
    const float fArmSwing = std::sin(phase) * 15.0f - 15.0f;
    const float legSwing = std::sin(phase + 3.14159265f) * 55.0f;
    const float bob = std::sin(phase * 2.0f) * 0.10f;

    bodyFrames.torso.setModel(Mat4::translate(Vec3(0.0f, bob, 0.0f)));
    bodyFrames.head.setModel(Mat4::translate(Vec3(0.0f, 1.5f + bob * 0.5f, 0.0f)));

    bodyFrames.rUpArm.setModel(
        bodyFrames.rUpArm.getFirstModel() *
        Mat4::rotate(Math::radians(armSwing), Vec3(1.0f, 0.0f, 0.0f))
    );
    bodyFrames.rForearm.setModel(
        bodyFrames.rForearm.getFirstModel() *
        Mat4::rotate(Math::radians(fArmSwing), Vec3(1.0f, 0.0f, 0.0f))
    );

   bodyFrames.lUpArm.setModel(
        bodyFrames.lUpArm.getFirstModel() *
        Mat4::rotate(Math::radians(-armSwing), Vec3(1.0f, 0.0f, 0.0f))
    );
    bodyFrames.lForearm.setModel(
        bodyFrames.lForearm.getFirstModel() *
        Mat4::rotate(Math::radians(-(fArmSwing + 30)), Vec3(1.0f, 0.0f, 0.0f))
    );

    // bodyFrames.rThigh.setModel(
    //     Mat4::translate(Vec3(-0.5f, -1.5f, 0.0f)) *
    //     Mat4::rotate(Math::radians(-legSwing), Vec3(0.0f, 0.0f, 1.0f))
    // );
    // bodyFrames.rLowLeg.setModel(
    //     Mat4::translate(Vec3(0.0f, -1.5f, 0.5f)) *
    //     Mat4::rotate(Math::radians(-legSwing * 0.8f), Vec3(0.0f, 0.0f, 1.0f))
    // );

    // bodyFrames.lThigh.setModel(
    //     Mat4::translate(Vec3(0.5f, -1.5f, 0.0f)) *
    //     Mat4::rotate(Math::radians(legSwing), Vec3(0.0f, 0.0f, 1.0f))
    // );
    // bodyFrames.lLowLeg.setModel(
    //     Mat4::translate(Vec3(0.0f, -1.5f, 0.5f)) *
    //     Mat4::rotate(Math::radians(legSwing * 0.8f), Vec3(0.0f, 0.0f, 1.0f))
    // );
}

void Human::drawHuman(const Shader &shader, const CordFrame *frame)
{
    if (matrixS.empty())
        matrixS.push(frame->getModel());
    else
        matrixS.push(matrixS.top() * frame->getModel());

    const Mat4 model = frame->getPart().getModel();
    shader.setMat4("model", matrixS.top() * model);
    shader.setVec3("color", frame->getPart().getColor());
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    for (const CordFrame* child : frame->getChildren())
    {
        drawHuman(shader, child);
    }
    matrixS.pop();
}