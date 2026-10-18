#include "Human.hpp"

namespace
{
    const Vec3 axisX(1.0f, 0.0f, 0.0f);
    const Vec3 axisY(0.0f, 1.0f, 0.0f);
    const Vec3 axisZ(0.0f, 0.0f, 1.0f);

    Part makePart(const Vec3& pos, const Vec3& scale, const Vec3& color,
                 float rot = 0.0f,
                 const Vec3& axis = axisZ)
    {
        return Part(Mat4::model(pos, rot, axis, scale), color);
    }

    void applyLocalRotation(CordFrame& frame, float deg, const Vec3& axis)
    {
        frame.setModel(frame.getFirstModel() * Mat4::rotate(Math::radians(deg), axis));
    }
}

const Vec3 skinColor(70.0f, 42.0f, 28.0f);
const Vec3 tShirtColor(40.0f, 118.0f, 184.0f);
const Vec3 pantsColor(54.0f, 86.0f, 160.0f);

Vec3 tailColor(89, 31, 140);   // Purple
Vec3 wingColor(64, 166, 217);  // Sky blue
Vec3 hornColor(242, 191, 64);  // Golden yellow
Human::Human() : hasReset(false)
{
    bodyParts.head     = makePart(Vec3(0.0f, 1.0f, 0.25f), Vec3(2.0f, 2.0f, 2.0f), skinColor);
    bodyParts.torso    = makePart(Vec3(0.0f, 0.0f, 0.0f), Vec3(2.0f, 3.0f, 1.0f), tShirtColor);
    bodyParts.rUpArm   = makePart(Vec3(-0.5f, -0.25f, 0.0f), Vec3(1.0f, 1.5f, 1.0f), tShirtColor);
    bodyParts.rForearm = makePart(Vec3(0.0f, -0.75f, 0.5f), Vec3(0.999f, 1.499f, 0.999f), skinColor);
    bodyParts.lUpArm   = makePart(Vec3(0.5f, -0.25f, 0.0f), Vec3(1.0f, 1.5f, 1.0f), tShirtColor);
    bodyParts.lForearm = makePart(Vec3(0.0f, -0.75f, 0.5f), Vec3(0.999f, 1.499f, 0.999f), skinColor);
    bodyParts.rThigh   = makePart(Vec3(0.0f, -0.75f, 0.0f), Vec3(0.999f, 1.499f, 0.999f), pantsColor);
    bodyParts.rLowLeg  = makePart(Vec3(0.0f, -0.75f, -0.5f), Vec3(0.999f, 1.499f, 0.999f), pantsColor);
    bodyParts.lThigh   = makePart(Vec3(0.0f, -0.75f, 0.0f), Vec3(0.999f, 1.499f, 0.999f), pantsColor);
    bodyParts.lLowLeg  = makePart(Vec3(0.0f, -0.75f, -0.5f), Vec3(0.999f, 1.499f, 0.999f), pantsColor);

    bodyParts.tail1 = makePart(Vec3(0.0f, 0.0f, -0.8f), Vec3(0.65f, 0.65f, 1.6f), tailColor);
    bodyParts.tail2 = makePart(Vec3(0.0f, 0.0f, -0.65f), Vec3(0.5f, 0.5f, 1.3f), tailColor);
    bodyParts.tail3 = makePart(Vec3(0.0f, 0.0f, -0.5f), Vec3(0.38f, 0.38f, 1.0f), tailColor);

    bodyParts.rWing    = makePart(Vec3(-1.25f, 0.0f, -0.6f), Vec3(2.5f, 0.08f, 1.4f), wingColor);
    bodyParts.rWingTip = makePart(Vec3(-1.0f, 0.0f, -0.5f), Vec3(2.0f, 0.06f, 1.0f), wingColor);
    bodyParts.lWing    = makePart(Vec3(1.25f, 0.0f, -0.6f), Vec3(2.5f, 0.08f, 1.4f), wingColor);
    bodyParts.lWingTip = makePart(Vec3(1.0f, 0.0f, -0.5f), Vec3(2.0f, 0.06f, 1.0f), wingColor);

    bodyParts.rHorn = makePart(Vec3(0.0f, 0.3f, 0.0f), Vec3(0.25f, 0.6f, 0.25f), hornColor);
    bodyParts.lHorn = bodyParts.rHorn;

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

    // Tail: base at the lower back of the torso
    bodyFrames.tail1 = CordFrame(
        Mat4::translate(Vec3(0.0f, -1.2f, -0.5f)) *
        Mat4::rotate(Math::radians(10.0f), axisX),
        bodyParts.tail1
    );
    bodyFrames.tail2 = CordFrame(
        Mat4::translate(Vec3(0.0f, 0.0f, -1.6f)) *   // end of tail1
        Mat4::rotate(Math::radians(20.0f), axisX),
        bodyParts.tail2
    );
    bodyFrames.tail3 = CordFrame(
        Mat4::translate(Vec3(0.0f, 0.0f, -1.3f)) *   // end of tail2
        Mat4::rotate(Math::radians(25.0f), axisX),
        bodyParts.tail3
    );
    bodyFrames.tail1.addChild(&bodyFrames.tail2);
    bodyFrames.tail2.addChild(&bodyFrames.tail3);

    // Right wing: upper back, near the spine
    bodyFrames.rWing = CordFrame(
        Mat4::translate(Vec3(-0.5f, 0.8f, -0.55f)),
        bodyParts.rWing
    );
    bodyFrames.rWingTip = CordFrame(
        Mat4::translate(Vec3(-2.5f, 0.0f, 0.0f)),   // was -1.5
        bodyParts.rWingTip
    );
    bodyFrames.rWing.addChild(&bodyFrames.rWingTip);

    // Left wing
    bodyFrames.lWing = CordFrame(
        Mat4::translate(Vec3(0.5f, 0.8f, -0.55f)),
        bodyParts.lWing
    );
    bodyFrames.lWingTip = CordFrame(
        Mat4::translate(Vec3(2.5f, 0.0f, 0.0f)),    // was 1.5
        bodyParts.lWingTip
    );
    bodyFrames.lWing.addChild(&bodyFrames.lWingTip);

    // Horns: children of the head (head frame spans y 0..2, z -0.75..1.25)
    bodyFrames.rHorn = CordFrame(
        Mat4::translate(Vec3(-0.6f, 2.0f, 0.25f)),
        bodyParts.rHorn
    );
    bodyFrames.lHorn = CordFrame(
        Mat4::translate(Vec3(0.6f, 2.0f, 0.25f)),
        bodyParts.lHorn
    );
    bodyFrames.head.addChild(&bodyFrames.rHorn);
    bodyFrames.head.addChild(&bodyFrames.lHorn);

    bodyFrames.torso.addChild(&bodyFrames.head);
    bodyFrames.torso.addChild(&bodyFrames.rUpArm);
    bodyFrames.torso.addChild(&bodyFrames.lUpArm);
    bodyFrames.torso.addChild(&bodyFrames.rThigh);
    bodyFrames.torso.addChild(&bodyFrames.lThigh);
    bodyFrames.torso.addChild(&bodyFrames.tail1);
    bodyFrames.torso.addChild(&bodyFrames.rWing);
    bodyFrames.torso.addChild(&bodyFrames.lWing);
}

void Human::run()
{
    static float phase = 0.0f;
    phase += 0.12f;

    const float PI = 3.14159265f;

    // ---- Arms --------------------------------------------------------
    // rotation around X: positive = limb goes backward (-z), negative = forward (+z)
    const float armSwing  = std::sin(phase) * 45.0f;
    const float fArmSwing = std::sin(phase) * 15.0f - 15.0f;

    // ---- Legs --------------------------------------------------------
    // Right leg is opposite to the right arm, left leg is opposite to the left arm
    const float legSwing = std::sin(phase + PI) * 55.0f;

    // Knees bend only while the leg swings forward (recovery phase),
    // and stay almost straight while it pushes backward (stance phase).
    // The left leg is half a cycle behind the right one.
    const float rKnee = 10.0f + 80.0f * std::max(0.0f, std::cos(phase));
    const float lKnee = 10.0f + 80.0f * std::max(0.0f, std::cos(phase + PI));

    // ---- Body bob ----------------------------------------------------
    // Two bounces per cycle, body is lowest at mid-stance (when thighs are vertical)
    const float bob = -std::cos(phase * 2.0f) * 0.10f;

    bodyFrames.torso.setModel(Mat4::translate(Vec3(0.0f, bob, 0.0f)));
    bodyFrames.head.setModel(
        bodyFrames.head.getFirstModel() *
        Mat4::translate(Vec3(0.0f, bob * 0.5f, 0.0f))
    );

        // ---- Extras ------------------------------------------------------
    // Wings: flap twice per run cycle, around the Z axis.
    // Right wing extends toward -x, so a positive angle moves its tip DOWN.
    // The left wing is mirrored, so it gets the negated angle.
    // The tip lags behind the inner wing, which gives a whip-like flap.
    const float wingFlap = std::sin(phase * 2.0f) * 20.0f + 10.0f;
    const float tipFlap  = std::sin(phase * 2.0f - 0.8f) * 25.0f;

    // Tail: wags left/right (Y axis) and lifts slightly (X axis).
    // Each segment lags a bit more than the one before it.
    // Tail extends toward -z, so a positive X rotation lifts it.
    const float tail1Yaw = std::sin(phase)        * 15.0f;
    const float tail2Yaw = std::sin(phase - 0.6f) * 20.0f;
    const float tail3Yaw = std::sin(phase - 1.2f) * 25.0f;
    const float tailLift = 10.0f + std::sin(phase * 2.0f) * 5.0f;

    // Horns: tiny bounce that lags behind the head
    const float hornWobble = std::sin(phase * 2.0f - 1.0f) * 4.0f;

    // ---- Right arm ---------------------------------------------------
    applyLocalRotation(bodyFrames.rUpArm, armSwing, axisX);
    applyLocalRotation(bodyFrames.rForearm, fArmSwing, axisX);

    // ---- Left arm ----------------------------------------------------
    applyLocalRotation(bodyFrames.lUpArm, -armSwing, axisX);
    applyLocalRotation(bodyFrames.lForearm, -(fArmSwing + 30.0f), axisX);

    // ---- Right leg ---------------------------------------------------
    applyLocalRotation(bodyFrames.rThigh, legSwing, axisX);
    applyLocalRotation(bodyFrames.rLowLeg, rKnee, axisX);

    // ---- Left leg ----------------------------------------------------
    applyLocalRotation(bodyFrames.lThigh, -legSwing, axisX);
    applyLocalRotation(bodyFrames.lLowLeg, lKnee, axisX);

        // ---- Tail --------------------------------------------------------
    bodyFrames.tail1.setModel(
        bodyFrames.tail1.getFirstModel() *
        Mat4::rotate(Math::radians(tail1Yaw), axisY) *
        Mat4::rotate(Math::radians(tailLift), axisX)
    );
    bodyFrames.tail2.setModel(
        bodyFrames.tail2.getFirstModel() *
        Mat4::rotate(Math::radians(tail2Yaw), axisY)
    );
    bodyFrames.tail3.setModel(
        bodyFrames.tail3.getFirstModel() *
        Mat4::rotate(Math::radians(tail3Yaw), axisY)
    );

    // ---- Wings -------------------------------------------------------
    applyLocalRotation(bodyFrames.rWing, wingFlap, axisZ);
    applyLocalRotation(bodyFrames.rWingTip, tipFlap, axisZ);
    applyLocalRotation(bodyFrames.lWing, -wingFlap, axisZ);
    applyLocalRotation(bodyFrames.lWingTip, -tipFlap, axisZ);

    // ---- Horns -------------------------------------------------------
    applyLocalRotation(bodyFrames.rHorn, hornWobble, axisX);
    applyLocalRotation(bodyFrames.lHorn, hornWobble, axisX);
}

static float lerpf(float a, float b, float u)
{
    return a + (b - a) * u;
}

// ease-in / ease-out, u in [0, 1]
static float smoothf(float u)
{
    return u * u * (3.0f - 2.0f * u);
}

static float wrap01(float t)
{
    while (t < 0.0f)  t += 1.0f;
    while (t >= 1.0f) t -= 1.0f;
    return t;
}

// Wing angle (positive = tips down, negative = tips up)
static float wingAngle(float t)
{
    const float PI = 3.14159265f;
    t = wrap01(t);

    if (t < 0.30f)        // crouch: wings fold back and down a little
        return lerpf(10.0f, 30.0f, smoothf(t / 0.30f));

    if (t < 0.40f)        // take-off: wings snap up
        return lerpf(30.0f, -65.0f, smoothf((t - 0.30f) / 0.10f));

    if (t < 0.75f)        // flight: two flaps, getting smaller as the jump ends
    {
        const float u   = (t - 0.40f) / 0.35f;
        const float amp = 35.0f * (1.0f - u);
        return lerpf(-30.0f, 20.0f, u) - amp * std::cos(4.0f * PI * u);
    }

    if (t < 0.88f)        // landing: wings open up like an air brake
        return lerpf(20.0f, 0.0f, smoothf((t - 0.75f) / 0.13f));

    // recover
    return lerpf(0.0f, 10.0f, smoothf((t - 0.88f) / 0.12f));
}

// Tail lift (positive = tail goes up)
static float tailAngle(float t)
{
    t = wrap01(t);

    if (t < 0.30f)  return lerpf(10.0f, 25.0f, smoothf(t / 0.30f));
    if (t < 0.40f)  return lerpf(25.0f, -15.0f, smoothf((t - 0.30f) / 0.10f));
    if (t < 0.75f)  return lerpf(-15.0f, 20.0f, smoothf((t - 0.40f) / 0.35f));
    if (t < 0.88f)  return lerpf(20.0f, 35.0f, smoothf((t - 0.75f) / 0.13f));
    return lerpf(35.0f, 10.0f, smoothf((t - 0.88f) / 0.12f));
}

void Human::jump()
{
    // One jump cycle goes from t = 0 to t = 1, then it starts again.
    // 0.015 per call is about 1.1 s per jump at 60 fps.
    static float t = 0.0f;
    t += 0.015f;
    if (t >= 1.0f)
        t -= 1.0f;

    const float PI         = 3.14159265f;
    const float jumpHeight = 2.0f;   // how high the torso rises
    const float legLen     = 1.5f;   // thigh length = lower leg length (Y scale)
    const float maxKnee    = 90.0f;  // knee angle at full crouch

    float flex     = 0.0f;   // 0 = straight legs, 1 = full crouch
    float height   = 0.0f;   // height above the ground
    float arm      = 0.0f;   // upper arm angle (positive = back, negative = forward/up)
    bool  airborne = false;

    if (t < 0.30f)
    {
        // 1. Anticipation: crouch down, arms go back
        const float u = smoothf(t / 0.30f);
        flex = u;
        arm  = lerpf(0.0f, 50.0f, u);
    }
    else if (t < 0.40f)
    {
        // 2. Take-off: legs push (still on the ground), arms swing up
        const float u = smoothf((t - 0.30f) / 0.10f);
        flex = 1.0f - u;
        arm  = lerpf(50.0f, -160.0f, u);
    }
    else if (t < 0.75f)
    {
        // 3. Flight: parabola, knees tucked a little, arms up then coming down
        const float u = (t - 0.40f) / 0.35f;
        airborne = true;
        height   = 4.0f * jumpHeight * u * (1.0f - u);
        flex     = 0.35f * std::sin(PI * u);
        arm      = lerpf(-160.0f, -70.0f, smoothf(u));
    }
    else if (t < 0.88f)
    {
        // 4. Landing: absorb the impact
        const float u = smoothf((t - 0.75f) / 0.13f);
        flex = 0.8f * u;
        arm  = lerpf(-70.0f, 30.0f, u);
    }
    else
    {
        // 5. Recover: stand back up
        const float u = smoothf((t - 0.88f) / 0.12f);
        flex = 0.8f * (1.0f - u);
        arm  = lerpf(30.0f, 0.0f, u);
    }

    // ---- Angles ------------------------------------------------------
    // rotation around X: positive = limb goes backward (-z), negative = forward (+z)
    const float knee  = maxKnee * flex;
    const float thigh = -knee * (airborne ? 1.0f : 0.5f);   // thigh forward, knee back
    const float elbow = -15.0f - 25.0f * flex;

    // While the feet are on the ground, lower the torso so they stay planted:
    // foot height = 2 * legLen * cos(knee / 2) when thigh = -knee / 2
    const float drop = airborne
        ? 0.0f
        : 2.0f * legLen * (1.0f - std::cos(Math::radians(knee * 0.5f)));

    // ---- Torso and head ----------------------------------------------
    bodyFrames.torso.setModel(Mat4::translate(Vec3(0.0f, height - drop, 0.0f)));
    bodyFrames.head.setModel(bodyFrames.head.getFirstModel());

    // ---- Arms (both move together) -----------------------------------
    applyLocalRotation(bodyFrames.rUpArm, arm, axisX);
    applyLocalRotation(bodyFrames.lUpArm, arm, axisX);
    applyLocalRotation(bodyFrames.rForearm, elbow, axisX);
    applyLocalRotation(bodyFrames.lForearm, elbow, axisX);

    // ---- Legs (both move together) -----------------------------------
    applyLocalRotation(bodyFrames.rThigh, thigh, axisX);
    applyLocalRotation(bodyFrames.lThigh, thigh, axisX);
    applyLocalRotation(bodyFrames.rLowLeg, knee, axisX);
    applyLocalRotation(bodyFrames.lLowLeg, knee, axisX);

    // ---- Extras: each part uses a lagged copy of the motion ----------
    const float wing     = wingAngle(t);
    const float wingTip  = wingAngle(t - 0.03f) * 0.7f;   // tip trails the wing

    const float tail1Rot = tailAngle(t);
    const float tail2Rot = tailAngle(t - 0.04f) * 0.8f;   // each segment is later
    const float tail3Rot = tailAngle(t - 0.08f) * 0.8f;   // than the previous one

    const float horn     = wingAngle(t - 0.06f) * 0.3f;

    // ---- Wings (mirrored) --------------------------------------------
    applyLocalRotation(bodyFrames.rWing, wing, axisZ);
    applyLocalRotation(bodyFrames.rWingTip, wingTip, axisZ);
    applyLocalRotation(bodyFrames.lWing, -wing, axisZ);
    applyLocalRotation(bodyFrames.lWingTip, -wingTip, axisZ);

    // ---- Tail --------------------------------------------------------
    applyLocalRotation(bodyFrames.tail1, tail1Rot, axisX);
    applyLocalRotation(bodyFrames.tail2, tail2Rot, axisX);
    applyLocalRotation(bodyFrames.tail3, tail3Rot, axisX);

    // ---- Horns -------------------------------------------------------
    applyLocalRotation(bodyFrames.rHorn, horn, axisX);
    applyLocalRotation(bodyFrames.lHorn, horn, axisX);
}

void Human::fly()
{
    static float phase = 0.0f;
    phase += 0.15f;

    const float PI = 3.14159265f;

    // ---- Wing flap ---------------------------------------------------
    // positive = tips down, negative = tips up (same convention as run/jump)
    // Slightly biased upward so the down-stroke is the powerful one.
    const float wing    = std::sin(phase) * 45.0f - 10.0f;
    const float wingTip = std::sin(phase - 0.9f) * 35.0f - 5.0f;   // tip lags behind

    // ---- Body --------------------------------------------------------
    // The body is highest when the wings are fully down, so the bob uses the
    // same sine as the wing (the lift happens during the down-stroke).
    const float hover = 2.5f + std::sin(phase) * 0.3f;

    // Lean forward and rock a little with each flap
    // (positive X rotation moves the head toward +z)
    const float lean = 20.0f + std::sin(phase) * 4.0f;

    bodyFrames.torso.setModel(
        Mat4::translate(Vec3(0.0f, hover, 0.0f)) *
        Mat4::rotate(Math::radians(lean), axisX)
    );

    // Counter-rotate the head so it looks mostly forward
    bodyFrames.head.setModel(
        bodyFrames.head.getFirstModel() *
        Mat4::rotate(Math::radians(-lean * 0.7f), axisX)
    );

    // ---- Arms: swept back, with a small flutter ----------------------
    const float arm   = 30.0f + std::sin(phase - 0.5f) * 6.0f;
    const float elbow = -10.0f;

    applyLocalRotation(bodyFrames.rUpArm, arm, axisX);
    applyLocalRotation(bodyFrames.lUpArm, arm, axisX);
    applyLocalRotation(bodyFrames.rForearm, elbow, axisX);
    applyLocalRotation(bodyFrames.lForearm, elbow, axisX);

    // ---- Legs: trail behind and dangle, lagging behind the flap ------
    const float thigh = 15.0f + std::sin(phase - 0.8f) * 8.0f;
    const float knee  = 25.0f + std::sin(phase - 1.4f) * 12.0f;

    applyLocalRotation(bodyFrames.rThigh, thigh, axisX);
    applyLocalRotation(bodyFrames.lThigh, thigh, axisX);
    applyLocalRotation(bodyFrames.rLowLeg, knee, axisX);
    applyLocalRotation(bodyFrames.lLowLeg, knee, axisX);

    // ---- Wings (mirrored) --------------------------------------------
    applyLocalRotation(bodyFrames.rWing, wing, axisZ);
    applyLocalRotation(bodyFrames.rWingTip, wingTip, axisZ);
    applyLocalRotation(bodyFrames.lWing, -wing, axisZ);
    applyLocalRotation(bodyFrames.lWingTip, -wingTip, axisZ);

    // ---- Tail: streams behind, each segment lags more ----------------
    // Lift is lowered a bit (flying forward pushes the tail down),
    // and a small side-to-side wave travels along it.
    const float tailLift = -5.0f + std::sin(phase - 0.6f) * 8.0f;

    bodyFrames.tail1.setModel(
        bodyFrames.tail1.getFirstModel() *
        Mat4::rotate(Math::radians(std::sin(phase - 0.5f) * 8.0f),  axisY) *
        Mat4::rotate(Math::radians(tailLift),                        axisX)
    );
    bodyFrames.tail2.setModel(
        bodyFrames.tail2.getFirstModel() *
        Mat4::rotate(Math::radians(std::sin(phase - 1.1f) * 12.0f), axisY) *
        Mat4::rotate(Math::radians(tailLift * 0.8f),                 axisX)
    );
    bodyFrames.tail3.setModel(
        bodyFrames.tail3.getFirstModel() *
        Mat4::rotate(Math::radians(std::sin(phase - 1.7f) * 16.0f), axisY) *
        Mat4::rotate(Math::radians(tailLift * 0.8f),                 axisX)
    );

    // ---- Horns: bounce slightly against the head's motion ------------
    const float horn = std::sin(phase - 1.0f) * 5.0f;
    applyLocalRotation(bodyFrames.rHorn, horn, axisX);
    applyLocalRotation(bodyFrames.lHorn, horn, axisX);
}

// Add `void dance();` to the Human class in the header.
// Needs: #include <cmath> and #include <algorithm>

void Human::dance()
{
    static float phase = 0.0f;
    phase += 0.09f;   // one full left-right cycle is about 70 frames (~1.2 s at 60 fps)

    const float PI     = 3.14159265f;
    const float legLen = 1.5f;

    // side:  +1 = weight on the right side, -1 = on the left (one step per half cycle)
    // dip:   1 on every beat (the body is lowest), 0 between beats
    const float side = std::sin(phase);
    const float dip  = 0.5f + 0.5f * std::cos(phase * 2.0f);

    // How much each side is "active" (arm raised / leg lifted)
    const float rAct = std::max(0.0f,  side);
    const float lAct = std::max(0.0f, -side);

    // ---- Legs: bounce on the beat, lift the active leg ---------------
    const float knee  = 15.0f + 40.0f * dip;
    const float thigh = -knee * 0.5f;

    // Lower the torso so the feet stay planted (same formula as jump)
    const float drop = 2.0f * legLen * (1.0f - std::cos(Math::radians(knee * 0.5f)));

    bodyFrames.rThigh.setModel(
        bodyFrames.rThigh.getFirstModel() *
        Mat4::rotate(Math::radians(thigh - 20.0f * lAct), axisX)
    );
    bodyFrames.lThigh.setModel(
        bodyFrames.lThigh.getFirstModel() *
        Mat4::rotate(Math::radians(thigh - 20.0f * rAct), axisX)
    );
    bodyFrames.rLowLeg.setModel(
        bodyFrames.rLowLeg.getFirstModel() *
        Mat4::rotate(Math::radians(knee + 35.0f * lAct), axisX)
    );
    bodyFrames.lLowLeg.setModel(
        bodyFrames.lLowLeg.getFirstModel() *
        Mat4::rotate(Math::radians(knee + 35.0f * rAct), axisX)
    );

    // ---- Torso: hip sway, twist and roll -----------------------------
    bodyFrames.torso.setModel(
        Mat4::translate(Vec3(side * 0.15f, -drop, 0.0f)) *
        Mat4::rotate(Math::radians(-side * 14.0f), axisY) *   // twist
        Mat4::rotate(Math::radians(-side * 6.0f),  axisZ)     // roll
    );

    // ---- Head: nods on the beat, tilts against the hips --------------
    const float nod  = 6.0f + dip * 8.0f;
    const float tilt = side * 8.0f;
    const float look = side * 15.0f;

    bodyFrames.head.setModel(
        bodyFrames.head.getFirstModel() *
        Mat4::rotate(Math::radians(look), axisY) *
        Mat4::rotate(Math::radians(tilt), axisZ) *
        Mat4::rotate(Math::radians(nod),  axisX)
    );

    // ---- Arms: disco pose, they go up one at a time ------------------
    // Rotation around Z: the right arm needs a negative angle to go out and up,
    // the left arm a positive one. A small X rotation brings them a bit forward.
    const float rArmZ = -(15.0f + 110.0f * rAct);
    const float lArmZ =  (15.0f + 110.0f * lAct);
    const float armX  = -15.0f;

    // The forearm bends more when its arm is raised and waves a little
    const float rElbow = -20.0f - 40.0f * rAct + std::sin(phase * 4.0f) * 10.0f * rAct;
    const float lElbow = -20.0f - 40.0f * lAct + std::sin(phase * 4.0f) * 10.0f * lAct;

    bodyFrames.rUpArm.setModel(
        bodyFrames.rUpArm.getFirstModel() *
        Mat4::rotate(Math::radians(rArmZ), axisZ) *
        Mat4::rotate(Math::radians(armX),  axisX)
    );
    bodyFrames.lUpArm.setModel(
        bodyFrames.lUpArm.getFirstModel() *
        Mat4::rotate(Math::radians(lArmZ), axisZ) *
        Mat4::rotate(Math::radians(armX),  axisX)
    );
    bodyFrames.rForearm.setModel(
        bodyFrames.rForearm.getFirstModel() *
        Mat4::rotate(Math::radians(rElbow), axisX)
    );
    bodyFrames.lForearm.setModel(
        bodyFrames.lForearm.getFirstModel() *
        Mat4::rotate(Math::radians(lElbow), axisX)
    );

    // ---- Wings: flap on every beat, tips lag -------------------------
    // positive = tips down (same convention as the other animations)
    const float wing    = 15.0f + std::sin(phase * 2.0f - 0.3f) * 30.0f;
    const float wingTip = 10.0f + std::sin(phase * 2.0f - 1.0f) * 25.0f;

    bodyFrames.rWing.setModel(
        bodyFrames.rWing.getFirstModel() *
        Mat4::rotate(Math::radians(wing), axisZ)
    );
    bodyFrames.rWingTip.setModel(
        bodyFrames.rWingTip.getFirstModel() *
        Mat4::rotate(Math::radians(wingTip), axisZ)
    );
    bodyFrames.lWing.setModel(
        bodyFrames.lWing.getFirstModel() *
        Mat4::rotate(Math::radians(-wing), axisZ)
    );
    bodyFrames.lWingTip.setModel(
        bodyFrames.lWingTip.getFirstModel() *
        Mat4::rotate(Math::radians(-wingTip), axisZ)
    );

    // ---- Tail: swings opposite to the hips, wave travels to the tip --
    const float tailLift = 12.0f + dip * 6.0f;

    bodyFrames.tail1.setModel(
        bodyFrames.tail1.getFirstModel() *
        Mat4::rotate(Math::radians(std::sin(phase + PI)        * 25.0f), axisY) *
        Mat4::rotate(Math::radians(tailLift),                            axisX)
    );
    bodyFrames.tail2.setModel(
        bodyFrames.tail2.getFirstModel() *
        Mat4::rotate(Math::radians(std::sin(phase + PI - 0.6f) * 30.0f), axisY)
    );
    bodyFrames.tail3.setModel(
        bodyFrames.tail3.getFirstModel() *
        Mat4::rotate(Math::radians(std::sin(phase + PI - 1.2f) * 35.0f), axisY)
    );

    // ---- Horns: bounce on the beat, slightly behind the head ---------
    const float horn = std::sin(phase * 2.0f - 1.0f) * 8.0f;

    bodyFrames.rHorn.setModel(
        bodyFrames.rHorn.getFirstModel() *
        Mat4::rotate(Math::radians(horn), axisX)
    );
    bodyFrames.lHorn.setModel(
        bodyFrames.lHorn.getFirstModel() *
        Mat4::rotate(Math::radians(horn), axisX)
    );
}

void Human::idle()
{
    static float phase = 0.0f;
    phase += 0.03f;   // slow, calm motion

    // ---- Breathing ---------------------------------------------------
    // One breath is about 2 * PI / 0.03 = 210 frames (3.5 s at 60 fps)
    const float breath = std::sin(phase * 1.5f);

    // The torso rises slightly on the inhale. The amount is small so the
    // feet don't visibly leave the ground.
    bodyFrames.torso.setModel(
        Mat4::translate(Vec3(0.0f, breath * 0.03f, 0.0f))
    );

    // ---- Head: looks around slowly, nods a little --------------------
    const float lookYaw   = std::sin(phase * 0.4f) * 25.0f;           // left / right
    const float lookPitch = std::sin(phase * 0.7f + 1.0f) * 5.0f - 2.0f;

    bodyFrames.head.setModel(
        bodyFrames.head.getFirstModel() *
        Mat4::translate(Vec3(0.0f, breath * 0.02f, 0.0f)) *
        Mat4::rotate(Math::radians(lookYaw),   Vec3(0.0f, 1.0f, 0.0f)) *
        Mat4::rotate(Math::radians(lookPitch), Vec3(1.0f, 0.0f, 0.0f))
    );

    // ---- Arms: hang loosely and move slightly with the breath --------
    // The left arm is a little out of phase so they don't look mirrored.
    const float rArm = std::sin(phase * 1.5f - 0.4f) * 3.0f;
    const float lArm = std::sin(phase * 1.5f - 0.9f) * 3.0f;
    const float elbow = -8.0f + breath * 2.0f;

    bodyFrames.rUpArm.setModel(
        bodyFrames.rUpArm.getFirstModel() *
        Mat4::rotate(Math::radians(rArm), Vec3(1.0f, 0.0f, 0.0f))
    );
    bodyFrames.lUpArm.setModel(
        bodyFrames.lUpArm.getFirstModel() *
        Mat4::rotate(Math::radians(lArm), Vec3(1.0f, 0.0f, 0.0f))
    );
    bodyFrames.rForearm.setModel(
        bodyFrames.rForearm.getFirstModel() *
        Mat4::rotate(Math::radians(elbow), Vec3(1.0f, 0.0f, 0.0f))
    );
    bodyFrames.lForearm.setModel(
        bodyFrames.lForearm.getFirstModel() *
        Mat4::rotate(Math::radians(elbow), Vec3(1.0f, 0.0f, 0.0f))
    );

    // ---- Legs: stand still, with a very slight knee flex -------------
    const float knee = 3.0f + breath * 1.0f;

    bodyFrames.rThigh.setModel(bodyFrames.rThigh.getFirstModel());
    bodyFrames.lThigh.setModel(bodyFrames.lThigh.getFirstModel());
    bodyFrames.rLowLeg.setModel(
        bodyFrames.rLowLeg.getFirstModel() *
        Mat4::rotate(Math::radians(knee), Vec3(1.0f, 0.0f, 0.0f))
    );
    bodyFrames.lLowLeg.setModel(
        bodyFrames.lLowLeg.getFirstModel() *
        Mat4::rotate(Math::radians(knee), Vec3(1.0f, 0.0f, 0.0f))
    );

    // ---- Wings: folded and drooping, opening a little on each inhale -
    // positive = tips down (same convention as run/jump/fly)
    const float wing    = 28.0f - breath * 6.0f;
    const float wingTip = 20.0f - std::sin(phase * 1.5f - 0.7f) * 8.0f;   // tip lags

    bodyFrames.rWing.setModel(
        bodyFrames.rWing.getFirstModel() *
        Mat4::rotate(Math::radians(wing), Vec3(0.0f, 0.0f, 1.0f))
    );
    bodyFrames.rWingTip.setModel(
        bodyFrames.rWingTip.getFirstModel() *
        Mat4::rotate(Math::radians(wingTip), Vec3(0.0f, 0.0f, 1.0f))
    );
    bodyFrames.lWing.setModel(
        bodyFrames.lWing.getFirstModel() *
        Mat4::rotate(Math::radians(-wing), Vec3(0.0f, 0.0f, 1.0f))
    );
    bodyFrames.lWingTip.setModel(
        bodyFrames.lWingTip.getFirstModel() *
        Mat4::rotate(Math::radians(-wingTip), Vec3(0.0f, 0.0f, 1.0f))
    );

    // ---- Tail: slow lazy sway, a wave travels from base to tip -------
    const float tailLift = 5.0f + std::sin(phase * 0.8f) * 3.0f;

    bodyFrames.tail1.setModel(
        bodyFrames.tail1.getFirstModel() *
        Mat4::rotate(Math::radians(std::sin(phase * 1.2f)        * 10.0f), Vec3(0.0f, 1.0f, 0.0f)) *
        Mat4::rotate(Math::radians(tailLift),                               Vec3(1.0f, 0.0f, 0.0f))
    );
    bodyFrames.tail2.setModel(
        bodyFrames.tail2.getFirstModel() *
        Mat4::rotate(Math::radians(std::sin(phase * 1.2f - 0.7f) * 14.0f), Vec3(0.0f, 1.0f, 0.0f))
    );
    bodyFrames.tail3.setModel(
        bodyFrames.tail3.getFirstModel() *
        Mat4::rotate(Math::radians(std::sin(phase * 1.2f - 1.4f) * 18.0f), Vec3(0.0f, 1.0f, 0.0f))
    );

    // ---- Horns: occasional twitch ------------------------------------
    // The sine is raised to a high power, so it is nearly 0 most of the time
    // and spikes briefly, giving an occasional twitch instead of a constant wobble.
    const float twitchBase = std::sin(phase * 0.5f);
    const float twitch     = std::pow(std::max(0.0f, twitchBase), 12.0f);
    const float horn       = twitch * std::sin(phase * 25.0f) * 6.0f;

    bodyFrames.rHorn.setModel(
        bodyFrames.rHorn.getFirstModel() *
        Mat4::rotate(Math::radians(horn), Vec3(1.0f, 0.0f, 0.0f))
    );
    bodyFrames.lHorn.setModel(
        bodyFrames.lHorn.getFirstModel() *
        Mat4::rotate(Math::radians(-horn), Vec3(1.0f, 0.0f, 0.0f))
    );
}

void Human::reset()
{
    if (hasReset)
        return;
    hasReset = true;
    bodyFrames.head.setModel(bodyFrames.head.getFirstModel());
    bodyFrames.torso.setModel(bodyFrames.torso.getFirstModel());
    bodyFrames.rUpArm.setModel(bodyFrames.rUpArm.getFirstModel());
    bodyFrames.rForearm.setModel(bodyFrames.rForearm.getFirstModel());
    bodyFrames.lUpArm.setModel(bodyFrames.lUpArm.getFirstModel());
    bodyFrames.lForearm.setModel(bodyFrames.lForearm.getFirstModel());
    bodyFrames.rThigh.setModel(bodyFrames.rThigh.getFirstModel());
    bodyFrames.rLowLeg.setModel(bodyFrames.rLowLeg.getFirstModel());
    bodyFrames.lThigh.setModel(bodyFrames.lThigh.getFirstModel());
    bodyFrames.lLowLeg.setModel(bodyFrames.lLowLeg.getFirstModel());
    bodyFrames.tail1.setModel(bodyFrames.tail1.getFirstModel());
    bodyFrames.tail2.setModel(bodyFrames.tail2.getFirstModel());
    bodyFrames.tail3.setModel(bodyFrames.tail3.getFirstModel());
    bodyFrames.lHorn.setModel(bodyFrames.lHorn.getFirstModel());
    bodyFrames.rHorn.setModel(bodyFrames.rHorn.getFirstModel());
    bodyFrames.rWing.setModel(bodyFrames.rWing.getFirstModel());
    bodyFrames.lWing.setModel(bodyFrames.lWing.getFirstModel());
    bodyFrames.rWingTip.setModel(bodyFrames.rWingTip.getFirstModel());
    bodyFrames.lWingTip.setModel(bodyFrames.lWingTip.getFirstModel());
}

void Human::playAnimation(animations currAnim)
{
    switch (currAnim)
    {
        case NONE:
            reset();
            break;
        case IDLE:
            hasReset = false;
            idle();
            break;

        case RUN:
            hasReset = false;
            run();
            break;

        case JUMP:
            hasReset = false;
            jump();
            break;

        case FLY:
            hasReset = false;
            fly();
            break;

        case DANCE:
            hasReset = false;
            dance();
            break;
    }
}

void Human::drawHuman(const Shader &shader)
{
    drawHuman(shader, &bodyFrames.torso);
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

BodyFrames &Human::getBodyFrames()
{
    return bodyFrames;
}