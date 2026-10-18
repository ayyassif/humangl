#include "Part.hpp"

Part::Part() {}

Part::Part(const Mat4& model, const Vec3& color) : model(model), color(color / 255) {}

Vec3 Part::getColor() const
{
    return color;
}

Mat4 Part::getModel() const
{
    return model;
}
